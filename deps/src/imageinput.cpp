#include "jl_oiio.h"

namespace JlOpenImageIO
{

void register_ImageInput(jlcxx::Module& mod)
{
    mod.add_type<ImageInput>("ImageInput");
        //.method("read_scanline", &ImageInput::read_scanline);
    mod.method("read_scanline!", [](ImageInput* input, int y, float* data) {
        return input->read_scanline(y, 0, data);
    });

    mod.method("ImageInput_open", [](const std::string& filename) {
        return std::unique_ptr<ImageInput>(ImageInput::open(filename));
    });
}

} // namespace JlOpenImageIO

