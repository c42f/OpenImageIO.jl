using OpenImageIO
using Base.Test

import OpenImageIO: channeltype

@testset "TypeDesc" begin
    scalardesc(t) = TypeDesc(t, OpenImageIO.TypeDesc_SCALAR,
                             OpenImageIO.TypeDesc_NOXFORM, 0)
    tupledesc(t, n)  = TypeDesc(t, OpenImageIO.TypeDesc_SCALAR,
                                OpenImageIO.TypeDesc_NOXFORM, n)

    @test TypeDesc(UInt8)   == scalardesc(OpenImageIO.TypeDesc_UINT8)
    @test TypeDesc(Float64) == scalardesc(OpenImageIO.TypeDesc_DOUBLE)
    @test TypeDesc(Void)    == scalardesc(OpenImageIO.TypeDesc_PTR)

    @test TypeDesc(NTuple{2,Int16})   == tupledesc(OpenImageIO.TypeDesc_INT16,2)
    @test TypeDesc(NTuple{3,Float16}) == tupledesc(OpenImageIO.TypeDesc_HALF,3)

    @test channeltype(TypeDesc(OpenImageIO.TypeDesc_UINT32)) == UInt32
    @test channeltype(TypeDesc(OpenImageIO.TypeDesc_FLOAT))  == Float32

    @test string(TypeDesc(Int64)) == "TypeDesc(\"int64\")"
end

@testset "ImageInput" begin
    @test read_image(ImageInput_open("rgbw.png")) == [(0xff,0x00,0x00) (0x00,0xff,0x00);
                                                      (0x00,0x00,0xff) (0xff,0xff,0xff)]
end
