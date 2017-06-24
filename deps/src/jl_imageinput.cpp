#include "jl_oiio.h"

namespace JlOpenImageIO
{

std::string greet()
{
       return "hello, world";
}


JULIA_CPP_MODULE_BEGIN(registry)

jlcxx::Module& module = registry.create_module("OpenImageIO");
module.method("greet", &greet);

JULIA_CPP_MODULE_END


} // namespace JlOpenImageIO

