cmake_minimum_required(VERSION 3.10)
project(paperrenderer)

set(CMAKE_CXX_STANDARD 20)

# Include GLFW library
add_subdirectory(third/glfw)
add_subdirectory(third/OpenString-CMake)

SET(CMAKE_C_FLAGS_DEBUG "-D_DEBUG")

# Only used for Skia library linking
set(MSVC_USE_MT_RUNTIME_LIBRARY OFF)
set(MSVC_USE_MD_RUNTIME_LIBRARY OFF)
set(MSVC_USE_MTd_RUNTIME_LIBRARY OFF)
set(MSVC_USE_MDd_RUNTIME_LIBRARY ON)

if(CMAKE_SYSTEM_NAME MATCHES "Windows")
    add_compile_options(/wd4244 /wd4819 /wd4005)
    message("PaperRenderer : Building under Windows")
elseif()
    message("PaperRenderer : Building under Linux/Unix")
endif()

add_library(LibPRenderer STATIC include/base/test/vTest.h
        include/base/event/vEvent.h
        source/base/vtest/vTest.cpp
        include/base/binding/vBindingType.h
        source/base/binding/vBindingType.cpp
        include/base/command/vCommand.h
        source/base/command/vCommand.cpp
        source/base/command/vCommand.cpp
        include/base/vBase.h
        include/renderer/vRendererBase.h
        include/renderer/vSurface.h
        source/renderer/vSurface.cpp
        source/renderer/vSurface.cpp
        include/renderer/vRenderTarget.h
        source/renderer/vRenderTarget.cpp
        third/glad/src/glad.c
        source/renderer/vRenderContext.cpp
        include/renderer/vRenderContext.h
        include/renderer/vRenderInterface.h
        source/renderer/vRenderInterface.cpp
        include/base/geometry/vPoint.h
        include/base/geometry/vRect.h
        include/base/object/vObject.h
        source/base/object/vObject.cpp
        include/base/object/vObjectProperty.h
        source/base/object/vObjectProperty.cpp
        include/renderer/vColorFactory.h
        source/renderer/vColorFactory.cpp
        include/base/message/vMessage.h
        source/base/message/vMessage.cpp
        include/renderer/vGLHeader.h
        include/base/message/vKeyMap.h
)

add_library(WinToast STATIC third/winToast/include/wintoastlib.h
        third/winToast/src/wintoastlib.cpp)

set(UnitTestSrc tool/vcommit/third/include/cmdparser.hpp
        third/SimpleJson/sJSON.h
        third/SimpleJson/sJSON.cpp
        unitTest/base/base.command.h
        unitTest/base/base.command.h
        unitTest/base/base.command.cpp
        unitTest/base/base.binding.h
        unitTest/base/base.binding.cpp
        unitTest/base/base.event.h
        unitTest/base/base.event.cpp
        unitTest/base/base.geometry.cpp
        unitTest/base/base.geometry.h
        unitTest/base/base.object.property.h
        unitTest/base/base.object.property.cpp
        unitTest/renderer/renderer.color.factory.h
        unitTest/renderer/renderer.color.factory.cpp
        unitTest/parser/parser.html.lexer.h
        unitTest/parser/parser.html.lexer.cpp
        unitTest/parser/parser.html.ast.h
        unitTest/parser/pasrser.html.ast.cpp)

target_include_directories(LibPRenderer PUBLIC ./include)
target_include_directories(LibPRenderer PUBLIC ./)
target_include_directories(LibPRenderer PUBLIC ./third)
target_include_directories(LibPRenderer PUBLIC ./third/SkiaM101Binary)
target_include_directories(LibPRenderer PUBLIC ./third/glad/include)
target_include_directories(LibPRenderer PUBLIC ./third/OpenString-CMake)

# Judge MSVC compile runtime
if(CMAKE_SYSTEM_NAME MATCHES "Windows")
    message("PaperRenderer : Build under Windows OS")
    message("PaperRenderer : Using MSVC/Clang-CL Compiler")

    # MSVC use different runtime in Debug(D/S) and Release(D/S), make them happy :)
    if (MSVC_USE_MT_RUNTIME_LIBRARY)
        target_link_directories(LibPRenderer PUBLIC libs/skia/Windows/MT)
        message("PaperRenderer(Skia Library) : Using MSVC MT Runtime")
        add_compile_options(
                $<$<CONFIG:>:/MT>
                $<$<CONFIG:Debug>:/MT>
                $<$<CONFIG:Release>:/MT>
        )
    endif()
    if (MSVC_USE_MD_RUNTIME_LIBRARY)
        target_link_directories(LibPRenderer PUBLIC libs/skia/Windows/MD)
        message("PaperRenderer(Skia Library) : Using MSVC MD Runtime")
        add_compile_options(
                $<$<CONFIG:>:/MD>
                $<$<CONFIG:Debug>:/MD>
                $<$<CONFIG:Release>:/MD>
        )
    endif()
    if (MSVC_USE_MTd_RUNTIME_LIBRARY)
        target_link_directories(LibPRenderer PUBLIC libs/skia/Windows/MTd)
        message("PaperRenderer(Skia Library) : Using MSVC MTd Runtime")
        add_compile_options(
                $<$<CONFIG:>:/MTd>
                $<$<CONFIG:Debug>:/MTd>
                $<$<CONFIG:Release>:/MTd>
        )
    endif()
    if (MSVC_USE_MDd_RUNTIME_LIBRARY)
        target_link_directories(LibPRenderer PUBLIC libs/skia/Windows/MDd)
        message("PaperRenderer(Skia Library) : Using MSVC MDd Runtime")
        add_compile_options(
                $<$<CONFIG:>:/MDd>
                $<$<CONFIG:Debug>:/MDd>
                $<$<CONFIG:Release>:/MDd>
        )
    endif()
endif()

# The behaviour of other OS will be written after PaperRenderer3 was done on Windows
if(WIN32)
    message("Link Skia Under Windows OS")
    target_link_libraries(LibPRenderer PUBLIC
            expat
            harfbuzz
            icu
            imgui
            libjpeg
            libmicrohttpd
            libpng
            libwebp
            libwebp_sse41
            nanobench
            particles
            pathkit
            skia
            skiaserve
            skottie
            skparagraph
            skresources
            sksg
            skshaper
            sktext
            skunicode
            svg
            zlib
            opengl32
            glfw
            libostr
    )
else()
    message("Link Skia Under Linux/UNix")
    target_link_directories(LibPRenderer PUBLIC ./libs/skia)
    target_link_libraries(LibPRenderer PUBLIC
            expat
            harfbuzz
            icu
            imgui
            jpeg
            microhttpd
            png
            webp
            webp_sse41
            particles
            pathkit
            skia
            skottie
            skparagraph
            skresources
            sksg
            skshaper
            sktext
            fontconfig
            skunicode
            svg
            freetype
            zlib
            GL
            GLX
            glfw
            libostr
    )
endif()

add_executable(Demo_TestSkia demo/TestSkia/main.cpp)

target_include_directories(Demo_TestSkia PUBLIC ./include)
target_include_directories(Demo_TestSkia PUBLIC ./)
target_include_directories(Demo_TestSkia PUBLIC ./third)
target_include_directories(Demo_TestSkia PUBLIC ./third/SkiaM101Binary)
target_include_directories(Demo_TestSkia PUBLIC ./third/glad/include)

target_link_libraries(Demo_TestSkia LibPRenderer)

add_executable(Demo_TestSkiaShader demo/TestSkiaShader/main.cpp)

target_include_directories(Demo_TestSkiaShader PUBLIC ./include)
target_include_directories(Demo_TestSkiaShader PUBLIC ./)
target_include_directories(Demo_TestSkiaShader PUBLIC ./third)
target_include_directories(Demo_TestSkiaShader PUBLIC ./third/SkiaM101Binary)
target_include_directories(Demo_TestSkiaShader PUBLIC ./third/glad/include)

target_link_libraries(Demo_TestSkiaShader LibPRenderer)