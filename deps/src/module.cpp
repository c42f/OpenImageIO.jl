#include "jl_oiio.h"

using namespace jlcxx;
using namespace JlOpenImageIO;

JULIA_CPP_MODULE_BEGIN(registry)

jlcxx::Module& module = registry.create_module("OpenImageIO");

register_TypeDesc(module);
register_ImageSpec(module);
register_ImageInput(module);

JULIA_CPP_MODULE_END

