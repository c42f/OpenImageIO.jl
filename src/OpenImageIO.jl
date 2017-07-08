module OpenImageIO

import Base: show

using CxxWrap

wrap_modules(
    joinpath(Pkg.dir("OpenImageIO"),
             joinpath("deps", "usr", "lib", "libJlOpenImageIO"))
)

#-------------------------------------------------------------------------------
# TypeDesc
function show(io::IO, desc::TypeDesc)
    print(io, "TypeDesc(\"$(_print(desc))\")")
end

# OIIO has its own simple type system for describing pixel types and short
# arrays thereof.  The following defines the machinery to convert between the
# OIIO type system and julia types.

const BaseType = Union{UInt8,Int8,UInt16,Int16,UInt32,Int32,UInt64,Int64,Float16,Float32,Float64,String,Void}

_basetype(::Type{UInt8})   = TypeDesc_UINT8;
_basetype(::Type{Int8})    = TypeDesc_INT8;
_basetype(::Type{UInt16})  = TypeDesc_UINT16;
_basetype(::Type{Int16})   = TypeDesc_INT16;
_basetype(::Type{UInt32})  = TypeDesc_UINT32;
_basetype(::Type{Int32})   = TypeDesc_INT32;
_basetype(::Type{UInt64})  = TypeDesc_UINT64;
_basetype(::Type{Int64})   = TypeDesc_INT64;
_basetype(::Type{Float16}) = TypeDesc_HALF;
_basetype(::Type{Float32}) = TypeDesc_FLOAT;
_basetype(::Type{Float64}) = TypeDesc_DOUBLE;
_basetype(::Type{String})  = TypeDesc_STRING;
_basetype(::Type{Void})    = TypeDesc_PTR;

function TypeDesc(basetype=TypeDesc_UNKNOWN, aggregate=TypeDesc_SCALAR,
                  vecsem=TypeDesc_NOXFORM, arraylen=0)
    TypeDesc(basetype, aggregate, vecsem, arraylen)
end

function TypeDesc(basetype::TypeDesc_BASETYPE, arraylen=0)
    TypeDesc(basetype, TypeDesc_SCALAR, TypeDesc_NOXFORM, arraylen)
end

TypeDesc(::Type{T}) where {T<:BaseType} = TypeDesc(_basetype(T))
# TODO: Use StaticVector here?
TypeDesc(::Type{NTuple{N,T}}) where {N,T<:BaseType} = TypeDesc(_basetype(T), N)


# Map from TypeDesc back to julia types?
#function Type(desc::TypeDesc) = 

end
