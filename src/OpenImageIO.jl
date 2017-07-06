module OpenImageIO

import Base: show

using CxxWrap
wrap_modules(
    joinpath(Pkg.dir("OpenImageIO"),
             joinpath("deps", "usr", "lib", "libJlOpenImageIO")))


function show(io::IO, desc::TypeDesc)
    print(io, "TypeDesc(\"$(_print(desc))\")")
end

end
