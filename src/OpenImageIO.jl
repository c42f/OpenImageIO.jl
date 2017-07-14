module OpenImageIO

import Base: show, ==

using CxxWrap

wrap_module(
    joinpath(Pkg.dir("OpenImageIO"),
             joinpath("deps", "usr", "lib", "libJlOpenImageIO"))
)

export read_image, read_image!

#-------------------------------------------------------------------------------
# TypeDesc
function show(io::IO, desc::TypeDesc)
    print(io, "TypeDesc(\"$(_print(desc))\")")
end

# OIIO has its own simple type system for describing pixel types and short
# arrays thereof.  The following defines the machinery to convert between the
# OIIO type system and julia types.
#
# Note that OIIO treats integer types more like normalized fixed point numbers
# for the purposes of color channel conversion inside the OIIO library itself.
# For example, UInt8 is treated like FixedPointNumbers.Normed{UInt8,8}.

_type_to_basetype = Dict(
    (UInt8   => TypeDesc_UINT8),
    (Int8    => TypeDesc_INT8),
    (UInt16  => TypeDesc_UINT16),
    (Int16   => TypeDesc_INT16),
    (UInt32  => TypeDesc_UINT32),
    (Int32   => TypeDesc_INT32),
    (UInt64  => TypeDesc_UINT64),
    (Int64   => TypeDesc_INT64),
    (Float16 => TypeDesc_HALF),
    (Float32 => TypeDesc_FLOAT),
    (Float64 => TypeDesc_DOUBLE),
    (String  => TypeDesc_STRING),
    (Void    => TypeDesc_PTR),
)

_basetype_to_type = Dict(b=>a for (a,b) in _type_to_basetype)

const BaseType = Union{[a for (a,b) in _type_to_basetype]...}
const ColorChannelType = Union{UInt8,Int8,UInt16,Int16,UInt32,Int32,UInt64,Int64,Float16,Float32,Float64}

function TypeDesc(basetype, aggregate=TypeDesc_SCALAR,
                  vecsem=TypeDesc_NOXFORM, arraylen=0)
    TypeDesc(basetype, aggregate, vecsem, arraylen)
end

function TypeDesc(basetype::TypeDesc_BASETYPE, arraylen::Integer)
    TypeDesc(basetype, TypeDesc_SCALAR, TypeDesc_NOXFORM, arraylen)
end

TypeDesc(::Type{T}) where {T<:BaseType} = TypeDesc(_type_to_basetype[T])
TypeDesc(::Type{NTuple{N,T}}) where {N,T<:BaseType} = TypeDesc(_type_to_basetype[T], N)

# Get image channel type - 
function channeltype(desc::TypeDesc)
    if aggregate(desc) != TypeDesc_SCALAR || vecsemantics(desc) != TypeDesc_NOXFORM || arraylen(desc) > 0
        throw(ArgumentError("Cannot convert $desc to an image channel scalar"))
    end
    _basetype_to_type[basetype(desc)]
end

#channeltype(::Array{NTuple{<:Any,T}}) where {T} = T
#imageshape(::Array{NTuple{N,<:Any}, M}) where {N,M} = N
#nchannels(::Array{T,2}) where {N} = N

#-------------------------------------------------------------------------------
# ImageSpec
function show(io::IO, spec::ImageSpec)
    print(io, "ImageSpec$(serialize(spec, ImageSpec_SerialText, ImageSpec_SerialDetailedHuman))")
end


#-------------------------------------------------------------------------------
# Convenience functions for reading from ImageInput

# Compute native color tuple type for the image.  For now, we only allow
# homogenous color tuples.
function native_color_tuple_type(spec::ImageSpec)
    N = Int(nchannels(spec))
    NTuple{N, channeltype(format(spec))}
end

"""
    alloc_image(spec::ImageSpec)

Allocate an array to hold color data for an image described by `spec` with a
color channel type which is the same as the native image storage.  Elements of
the array are colors which are treated as simple tuples of the channel type.
The resulting array is either one, two, or three dimensional, depending on the
dimensionality of the underlying image data.
"""
function alloc_image(spec::ImageSpec)
    C = native_color_tuple_type(spec)
    if depth(spec) > 1
        Array{C,3}(height(spec), width(spec), depth(spec))
    elseif width(spec) > 1
        Array{C,2}(height(spec), width(spec))
    else
        # Is this sensible?  Would width=1 normally be used to
        # represent a one dimensional image, rather height=1?
        Array{C,1}(height(spec))
    end
end

"""
    read_image!(input::ImageInput, data)

Read pixel data for the current subimage of `input` into the array `data`
containing color tuples.  The size of `data` should match with the size of the
input image.  Supported color channel types are any subtypes of
`OIIO.ColorChannelType`.
"""
function read_image!(input::ImageInput,
                     data::Array{NTuple{Nchan,Tchan}}) where {Nchan,Tchan}
    s = spec(input)
    if nchannels(s) != Nchan
        throw(ArgumentError("Given number of color channels $Nchan is different number of image channels $(nchannels(s))"))
    end
    if !(Tchan <: ColorChannelType)
        throw(ArgumentError("Color channel type $Tchan is not supported by OpenImageIO"))
    end
    data_size = (size(data,1), size(data,2), size(data,3))
    expected_size = (height(s), width(s), depth(s))
    if data_size != expected_size
        throw(ArgumentError("Array size $data_size different from image size $expected_size"))
    end
    # Julia column-major array ordering is opposite from what would be computed
    # by OIIO's AutoStride mechanism.
    ystride = sizeof(NTuple{Nchan,Tchan})
    xstride = ystride*size(data,1)
    zstride = xstride*size(data,2)
    success = unsafe_read_image!(input, 0, Nchan, TypeDesc(Tchan),
                                 convert(Ptr{Void},pointer(data)),
                                 xstride, ystride, zstride)
    if !success
        throw(ErrorException(geterror(input)))
    end
    data
end

read_image(input::ImageInput) = read_image!(input, alloc_image(spec(input)))

end
