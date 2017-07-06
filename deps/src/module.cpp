#include "jl_oiio.h"

using namespace jlcxx;
using namespace JlOpenImageIO;

JULIA_CPP_MODULE_BEGIN(registry)

jlcxx::Module& module = registry.create_module("OpenImageIO");

register_TypeDesc(module);

JULIA_CPP_MODULE_END

