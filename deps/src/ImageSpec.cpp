#include "jl_oiio.h"

namespace jlcxx {
template<> struct IsBits<OIIO::ImageSpec::SerialFormat> : std::true_type {};
template<> struct IsBits<OIIO::ImageSpec::SerialVerbose> : std::true_type {};
}

namespace JlOpenImageIO
{

void register_ImageSpec(jlcxx::Module& mod)
{
    // FIXME - jlcxx error
    // mod.add_type<imagesize_t>("imagesize_t");

    mod.add_bits<ImageSpec::SerialFormat>("ImageSpec_SerialFormat");
    mod.set_const("ImageSpec_SerialText", ImageSpec::SerialText);
    mod.set_const("ImageSpec_SerialXML", ImageSpec::SerialXML);
    mod.add_bits<ImageSpec::SerialVerbose>("ImageSpec_SerialVerbose");
    mod.set_const("ImageSpec_SerialBrief", ImageSpec::SerialBrief);
    mod.set_const("ImageSpec_SerialDetailed", ImageSpec::SerialDetailed);
    mod.set_const("ImageSpec_SerialDetailedHuman", ImageSpec::SerialDetailedHuman);

    mod.add_type<ImageSpec>("ImageSpec")
        .constructor<TypeDesc>()
        .constructor<int,int,int,TypeDesc>()
        //.method("attribute", &ImageSpec::attribute)
        //.method("find_attribute", &ImageSpec::find_attribute)
        .method("size_t_safe", &ImageSpec::size_t_safe)
        .method("serialize", &ImageSpec::serialize)
        .method("channel_name", &ImageSpec::channel_name)
        .method("channelformat", &ImageSpec::channelformat)
        .method("channelindex", &ImageSpec::channelindex);

    // Ugly set of methods to get standard image metadata from an ImageSpec.
    // Potentially we'd just have a julia version of this instead?
    mod.method("x",              [](ImageSpec& spec) { return spec.x;              });
    mod.method("y",              [](ImageSpec& spec) { return spec.y;              });
    mod.method("z",              [](ImageSpec& spec) { return spec.z;              });
    mod.method("width",          [](ImageSpec& spec) { return spec.width;          });
    mod.method("height",         [](ImageSpec& spec) { return spec.height;         });
    mod.method("depth",          [](ImageSpec& spec) { return spec.depth;          });
    mod.method("full_x",         [](ImageSpec& spec) { return spec.full_x;         });
    mod.method("full_y",         [](ImageSpec& spec) { return spec.full_y;         });
    mod.method("full_z",         [](ImageSpec& spec) { return spec.full_z;         });
    mod.method("full_width",     [](ImageSpec& spec) { return spec.full_width;     });
    mod.method("full_height",    [](ImageSpec& spec) { return spec.full_height;    });
    mod.method("full_depth",     [](ImageSpec& spec) { return spec.full_depth;     });
    mod.method("tile_width",     [](ImageSpec& spec) { return spec.tile_width;     });
    mod.method("tile_height",    [](ImageSpec& spec) { return spec.tile_height;    });
    mod.method("tile_depth",     [](ImageSpec& spec) { return spec.tile_depth;     });
    mod.method("nchannels",      [](ImageSpec& spec) { return spec.nchannels;      });
    mod.method("format",         [](ImageSpec& spec) { return spec.format;         });
    mod.method("channelformats", [](ImageSpec& spec) { return spec.channelformats; });
    mod.method("channelnames",   [](ImageSpec& spec) { return spec.channelnames;   });
    mod.method("alpha_channel",  [](ImageSpec& spec) { return spec.alpha_channel;  });
    mod.method("z_channel",      [](ImageSpec& spec) { return spec.z_channel;      });
    mod.method("deep",           [](ImageSpec& spec) { return spec.deep;           });
    mod.method("extra_attribs",  [](ImageSpec& spec) { return spec.extra_attribs;  });

    //mod.method("find_attribute", [](ImageSpec& spec, 
}

}
