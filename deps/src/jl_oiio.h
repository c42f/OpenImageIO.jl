#ifndef JLOPENIMAGEIO_JL_OIIO_H
#define JLOPENIMAGEIO_JL_OIIO_H

#include <jlcxx/jlcxx.hpp>

#include <OpenImageIO/imageio.h>
#include <OpenImageIO/typedesc.h>

namespace JlOpenImageIO
{

using namespace OIIO;

void register_TypeDesc(jlcxx::Module& mod);
void register_ImageSpec(jlcxx::Module& mod);
void register_ImageInput(jlcxx::Module& mod);

} // namespace JlOpenImageIO

//------------------------------------------------------------------------------
// CxxWrap type conversion machinery for OIIO types

namespace jlcxx {

// string_view

template<> struct IsValueType<OIIO::string_view> : std::true_type { };

template<>
struct static_type_mapping<OIIO::string_view>
{
    typedef jl_value_t* type;
    static jl_datatype_t* julia_type()
    {
        return (jl_datatype_t*)jl_get_global(jl_base_module,
                                             jl_symbol("AbstractString"));
    }
};

template<>
struct ConvertToJulia<OIIO::string_view, false, false, false>
{
    jl_value_t* operator()(const OIIO::string_view& str) const
    {
        return jl_pchar_to_string(str.data(), str.length());
    }
};

template<>
struct ConvertToCpp<OIIO::string_view, false, false, false>
{
    OIIO::string_view operator()(jl_value_t* jstr) const
    {
        if (!jl_is_string(jstr))
            throw std::runtime_error("Type to convert to string is not a string but a " + julia_type_name((jl_datatype_t*)jl_typeof(jstr)));
        return OIIO::string_view(jl_string_data(jstr), jl_string_len(jstr));
    }
};

} // namespace jlcxx

#endif // JLOPENIMAGEIO_JL_OIIO_H
