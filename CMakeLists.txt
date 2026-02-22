cmake_minimum_required(VERSION 3.10)
project(BpmCli)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)
endif()

if(MSVC)
    add_compile_options(/O2 /Oi /Ot)
else()
    add_compile_options(-O2)
endif()

set(CMAKE_CXX_STANDARD 17)

include_directories(
        .
        lib
        src
        lib/libvorbis/include
        lib/libvorbis/src
)

set(BPMCLI_SOURCES
        src/Tools/BpmCli.cpp
        src/Editor/Sound.cpp
        src/Editor/LoadOgg.cpp
        src/Editor/FindTempo.cpp
        src/Editor/FindOnsets.cpp
        src/Editor/Aubio.cpp
        src/Editor/FFT.cpp
        src/System/File.cpp
        src/System/Debug.cpp
        src/System/Thread.cpp
        src/Core/String.cpp
        src/Core/StringUtils.cpp
        src/Core/WideString.cpp
        src/Core/Utils.cpp
)

set(VORBIS_SOURCES
        lib/libvorbis/src/bitwise.c
        lib/libvorbis/src/framing.c
        lib/libvorbis/src/mdct.c
        lib/libvorbis/src/smallft.c
        lib/libvorbis/src/block.c
        lib/libvorbis/src/envelope.c
        lib/libvorbis/src/window.c
        lib/libvorbis/src/lsp.c
        lib/libvorbis/src/lpc.c
        lib/libvorbis/src/analysis.c
        lib/libvorbis/src/synthesis.c
        lib/libvorbis/src/psy.c
        lib/libvorbis/src/info.c
        lib/libvorbis/src/floor1.c
        lib/libvorbis/src/floor0.c
        lib/libvorbis/src/res0.c
        lib/libvorbis/src/mapping0.c
        lib/libvorbis/src/registry.c
        lib/libvorbis/src/codebook.c
        lib/libvorbis/src/sharedbook.c
        lib/libvorbis/src/lookup.c
        lib/libvorbis/src/bitrate.c
        lib/libvorbis/src/vorbisfile.c
)

add_executable(BpmCli ${BPMCLI_SOURCES} ${VORBIS_SOURCES})

if(WIN32)
    target_link_libraries(BpmCli ws2_32 opengl32)
endif()