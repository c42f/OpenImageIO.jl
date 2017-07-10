using OpenImageIO

OIIO = OpenImageIO

f = ImageInput_open("image.jpg")

spec = OIIO.spec(f)
display(spec)

OIIO.channel_name(spec, 0)

width  = OIIO.width(spec)
height = OIIO.height(spec)
nchannels = OIIO.nchannels(spec)
data = zeros(UInt8, nchannels, width, height)

unsafe_read_image!(f, 0, nchannels, TypeDesc(UInt8), convert(Ptr{Void},pointer(data)),
                   OIIO.AutoStride, OIIO.AutoStride, OIIO.AutoStride)

using PyPlot
imshow(permutedims(data, [3,2,1]))

