#include "jl_oiio.h"

namespace JlOpenImageIO
{

void register_ImageSpec(jlcxx::Module& mod)
{
    mod.add_type<ImageSpec>("ImageSpec");
}

}
