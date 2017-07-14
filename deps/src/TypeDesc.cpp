#include "jl_oiio.h"


namespace jlcxx {

template<> struct IsBits<OIIO::TypeDesc::BASETYPE> : std::true_type {};
template<> struct IsBits<OIIO::TypeDesc::AGGREGATE> : std::true_type {};
template<> struct IsBits<OIIO::TypeDesc::VECSEMANTICS> : std::true_type {};

}

namespace JlOpenImageIO {

void register_TypeDesc(jlcxx::Module& mod)
{
    mod.add_bits<TypeDesc::BASETYPE>("TypeDesc_BASETYPE");
    mod.set_const("TypeDesc_UNKNOWN", TypeDesc::UNKNOWN);
    mod.set_const("TypeDesc_NONE ", TypeDesc::NONE );
    mod.set_const("TypeDesc_UINT8", TypeDesc::UINT8);
    mod.set_const("TypeDesc_INT8", TypeDesc::INT8);
    mod.set_const("TypeDesc_UINT16", TypeDesc::UINT16);
    mod.set_const("TypeDesc_INT16", TypeDesc::INT16);
    mod.set_const("TypeDesc_UINT32", TypeDesc::UINT32);
    mod.set_const("TypeDesc_INT32", TypeDesc::INT32);
    mod.set_const("TypeDesc_UINT64", TypeDesc::UINT64);
    mod.set_const("TypeDesc_INT64", TypeDesc::INT64);
    mod.set_const("TypeDesc_HALF", TypeDesc::HALF);
    mod.set_const("TypeDesc_FLOAT", TypeDesc::FLOAT);
    mod.set_const("TypeDesc_DOUBLE", TypeDesc::DOUBLE);
    mod.set_const("TypeDesc_STRING", TypeDesc::STRING);
    mod.set_const("TypeDesc_PTR", TypeDesc::PTR);

    mod.add_bits<TypeDesc::AGGREGATE>("TypeDesc_AGGREGATE");
    mod.set_const("TypeDesc_SCALAR", TypeDesc::SCALAR);
    mod.set_const("TypeDesc_VEC2", TypeDesc::VEC2);
    mod.set_const("TypeDesc_VEC3", TypeDesc::VEC3);
    mod.set_const("TypeDesc_VEC4", TypeDesc::VEC4);
    mod.set_const("TypeDesc_MATRIX33", TypeDesc::MATRIX33);
    mod.set_const("TypeDesc_MATRIX44", TypeDesc::MATRIX44);

    mod.add_bits<TypeDesc::VECSEMANTICS>("TypeDesc_VECSEMANTICS");
    mod.set_const("TypeDesc_NOXFORM", TypeDesc::NOXFORM);
    mod.set_const("TypeDesc_COLOR", TypeDesc::COLOR);
    mod.set_const("TypeDesc_POINT", TypeDesc::POINT);
    mod.set_const("TypeDesc_VECTOR", TypeDesc::VECTOR);
    mod.set_const("TypeDesc_NORMAL", TypeDesc::NORMAL);
    mod.set_const("TypeDesc_TIMECODE", TypeDesc::TIMECODE);
    mod.set_const("TypeDesc_KEYCODE", TypeDesc::KEYCODE);
    mod.set_const("TypeDesc_RATIONAL", TypeDesc::RATIONAL);

    mod.add_type<TypeDesc>("TypeDesc")
        .constructor<TypeDesc::BASETYPE, TypeDesc::AGGREGATE, TypeDesc::VECSEMANTICS, int>()
        .method("_print", &TypeDesc::c_str);

    mod.method("basetype", [](const TypeDesc& desc) { return (TypeDesc::BASETYPE)desc.basetype; });
    mod.method("aggregate", [](const TypeDesc& desc) { return (TypeDesc::AGGREGATE)desc.aggregate; });
    mod.method("vecsemantics", [](const TypeDesc& desc) { return (TypeDesc::VECSEMANTICS)desc.vecsemantics; });
    mod.method("arraylen", [](const TypeDesc& desc) { return desc.arraylen; });
    mod.method("==", [](const TypeDesc& d1, const TypeDesc& d2) { return d1 == d2; });

    mod.export_symbols("TypeDesc");
}

}
