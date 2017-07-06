#ifndef JLOPENIMAGEIO_JL_OIIO_H
#define JLOPENIMAGEIO_JL_OIIO_H

#include <jlcxx/jlcxx.hpp>

#include <OpenImageIO/imageio.h>
#include <OpenImageIO/typedesc.h>

namespace JlOpenImageIO
{

using namespace OIIO;

void register_TypeDesc(jlcxx::Module& mod);


} // namespace JlOpenImageIO

#endif // JLOPENIMAGEIO_JL_OIIO_H