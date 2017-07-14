using OpenImageIO

OIIO = OpenImageIO

input = ImageInput_open("image.jpg")

spec = OIIO.spec(input)
display(spec)

data = read_image(input)

using PyPlot
imshow(data)
#imshow(permutedims(data, [2,3,1]))
