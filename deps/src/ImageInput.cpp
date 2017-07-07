#include "jl_oiio.h"

namespace JlOpenImageIO
{

void register_ImageInput(jlcxx::Module& mod)
{
    mod.set_const("AutoStride", AutoStride);

    mod.add_type<ImageInput>("ImageInput");
        //.method("read_scanline", &ImageInput::read_scanline);

    mod.method("unsafe_read_image!",
        [](ImageInput& input, int chbegin, int chend,
           TypeDesc format, void *data,
           stride_t xstride, stride_t ystride, stride_t zstride)
        {
            // TODO: Progress callback closure!
            return input.read_image(chbegin, chend, format, data,
                                    xstride, ystride, zstride, NULL, NULL);
        });

    mod.method("unsafe_read_scanline!",
        [](ImageInput& input, int y, int z, TypeDesc format,
           void *data, stride_t xstride)
        {
            return input.read_scanline(y, z, format, data, xstride);
        });

    mod.method("ImageInput_open",
        [](const std::string& filename) {
            return ImageInput::open(filename);
        });

    mod.export_symbols("unsafe_read_image!",
                       "unsafe_read_scanline!",
                       "ImageInput_open");
}

} // namespace JlOpenImageIO

