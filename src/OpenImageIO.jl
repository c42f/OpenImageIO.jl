module OpenImageIO

using CxxWrap
wrap_modules(
    joinpath(Pkg.dir("OpenImageIO"),
             joinpath("deps", "usr", "lib", "libJlOpenImageIO")))

end
