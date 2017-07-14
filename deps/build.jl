# Build OpenImageIO

# Set env MAKEFLAGS for parallel build ?

oiio_version = "1.7.15"
oiio_src = "oiio-$oiio_version"
if !isdir(oiio_src)
    download("https://github.com/OpenImageIO/oiio/archive/Release-$oiio_version.tar.gz")
    run(`tar -xv -C $oiio_src `)
    #run(`git clone https://github.com/OpenImageIO/oiio.git`)
    cd(oiio_src) do
        run(`make`)
    end
end

#cmake_prefix = joinpath(
#oiio_root = joinpath(pwd(), "oiio/dist/linux64")
#
#if isfile("")
#end
#
#if isfile("oiio_build")
#end
#
#run(`cmake -DCMAKE_PREFIX_PATH= `)


# Thoughts
# - Binary packages
#   - Hunter package manager for deps ?
#   - vs custom binary packages based on OpenImageIO CI artifacts + cmake external_package + github releases ?
