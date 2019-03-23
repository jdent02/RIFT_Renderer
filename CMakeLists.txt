# Released under MIT License

# Copyright (c) 2018 Jonathan Dent.

# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:

# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.

# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

cmake_minimum_required(VERSION 3.0.0)

set (CMAKE_CONFIGURATION_TYPES "Debug;Release;Profile;Ship" CACHE STRING "" FORCE)

project(RIFT_renderer VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 14)

set (version_major    0)
set (version_minor    1)
set (version_patch    0)
set (version_maturity alpha)

configure_file (
    ${PROJECT_SOURCE_DIR}/src/utility/version/version.h.in
    ${PROJECT_SOURCE_DIR}/src/utility/version/version.h
)

# Options
option(USE_PLUGINS "Enable external plugins" Off)
set(RIFT_DEPENDENCIES_DIR "" CACHE PATH "Path to dependencies dirctory")

include_directories(
    SYSTEM
    src
)

if (USE_PLUGINS)
    add_definitions(-DRIFT_USE_PLUGINS)
    add_definitions(-DOIIO_STATIC_BUILD)
    set (Boost_USE_STATIC_LIBS TRUE)
    find_package (Boost 1.66 REQUIRED COMPONENTS chrono date_time filesystem regex system thread)
    include_directories(
        ${RIFT_DEPENDENCIES_DIR}/oiio-release/include
        ${RIFT_DEPENDENCIES_DIR}/ilmbase-release/include
        ${RIFT_DEPENDENCIES_DIR}/ilmbase-release/include/OpenEXR
        ${RIFT_DEPENDENCIES_DIR}/openexr-release/include
        ${RIFT_DEPENDENCIES_DIR}/openexr-release/include
        ${Boost_INCLUDE_DIRS}
    )
endif()

set (
    CAMERA_SOURCES
    src/objects/camera/i_camera.h
    src/objects/camera/thin_lens_camera.h
    src/objects/camera/thin_lens_camera.cpp
)

set (
    HITABLES_SOURCES
    src/objects/hitables/constant_medium.h
    src/objects/hitables/constant_medium.cpp
    src/objects/hitables/i_hitable.h
    src/objects/hitables/hitable_list.h
    src/objects/hitables/sphere.h
    src/objects/hitables/sphere.cpp
    src/objects/hitables/moving_sphere.h
    src/objects/hitables/moving_sphere.cpp
    src/objects/hitables/rect.cpp
    src/objects/hitables/rect.h
    src/objects/hitables/box.cpp
    src/objects/hitables/box.h
    src/objects/hitables/instancers.cpp
    src/objects/hitables/instancers.h
    src/objects/hitables/sky_sphere.h
)

set (
    CORE_SOURCES
    src/core/acceleration_structures/bvh_node.h
    src/core/acceleration_structures/bvh_node.cpp
    src/core/acceleration_structures/aabb.h
    src/core/acceleration_structures/aabb.cpp
    src/core/acceleration_structures/bvh_utils.h

    src/core/lighting_integrators/i_light_integrator.h
    src/core/lighting_integrators/direct_lighting.h
    src/core/lighting_integrators/direct_lighting.cpp
    src/core/lighting_integrators/light_sample_path.cpp
    src/core/lighting_integrators/light_sample_path.h
    src/core/lighting_integrators/path_tracer.h
    src/core/lighting_integrators/path_tracer.cpp
    src/core/rendering/render_controller.h
    src/core/rendering/render_controller.cpp
    src/core/rendering/render_worker.h
    src/core/rendering/render_worker.cpp
    src/core/rendering/color_functions.h

    src/core/image_writers/jpeg_writer.cpp
    src/core/image_writers/jpeg_writer.h
    src/core/image_writers/i_out_writer.h
    src/core/image_writers/png_writer.cpp
    src/core/image_writers/png_writer.h

    src/core/samplers/samplers/i_sampler.h
)

if(USE_PLUGINS)
    list(APPEND CORE_SOURCES
        src/core/image_writers/oiio_writer.h
        src/core/image_writers/oiio_writer.cpp
    )
endif()

set (
    MATERIAL_SOURCES
    src/materials/i_material.h
    src/materials/dielectric.h
    src/materials/dielectric.cpp
    src/materials/diffuse_light.h
    src/materials/lambertian.h
    src/materials/lambertian.cpp
    src/materials/metal.h
    src/materials/metal.cpp
)

set (
    TEXTURE_SOURCES
    src/textures/i_texture.h
    src/textures/constant_tex.h
    src/textures/checker_tex.h
    src/textures/checker_tex.cpp
    src/textures/noise_texture.h
    src/textures/image_texture.cpp
    src/textures/image_texture.h
    src/textures/sky_gradient.cpp
    src/textures/sky_gradient.h)

set (
    UTILITY_SOURCES
    src/utility/generators/scene_generator.h
    src/utility/generators/scene_generator.cpp
    src/utility/math_functions/maths.h
    src/utility/math_functions/scalars.h
    src/utility/noises/perlin.h
    src/utility/containers/scene.h
    src/utility/containers/render_settings.h
    src/utility/version/version.h
    src/utility/data_types/ray.h
    src/utility/data_types/vec3.h
    src/utility/data_types/hit_record.h
    src/utility/data_types/scatter_record.h
    src/utility/math_functions/pdfs/pdf.h
    src/utility/math_functions/utility_functions.h
    src/utility/math_functions/pdfs/cosine_pdf.h
    src/utility/math_functions/pdfs/hitable_pdf.h
    src/utility/math_functions/pdfs/mixture_pdf.h
    src/utility/math_functions/onb.h
    src/utility/math_functions/scatter_functions.h
    src/utility/rng/xoroshiro128.h
    src/utility/rng/xoroshiro128.cpp
    src/utility/rng/i_rand_generator.h
    src/utility/rng/drand48.cpp
    src/utility/rng/drand48.h
    src/utility/buffers/i_buffer.h
    src/utility/buffers/pixel_buffer.h
    src/utility/buffers/pixel_buffer.cpp
)

set (
    MAIN_SOURCE
    applications/RIFT_cli/main.cpp
    applications/RIFT_cli/command_line_parser.h
    applications/RIFT_cli/command_line_parser.cpp
)

set (
    CPP_SOURCES
    ${MAIN_SOURCE}
    ${CAMERA_SOURCES}
    ${CORE_SOURCES}
    ${HITABLES_SOURCES}
    ${MATERIAL_SOURCES}
    ${RENDERING_SOURCES}
    ${TEXTURE_SOURCES}
    ${UTILITY_SOURCES}
)

if (MSVC)
    add_definitions(
        -D_USE_MATH_DEFINES
    )

    set(
        CMAKE_C_FLAGS_RELEASE
        "/Zi /O2 /Ob2 /Oi /Ot /Oy /MD /GS- /GL"
    )

    set(
        CMAKE_CXX_FLAGS_RELEASE
        "/Zi /O2 /Ob2 /Oi /Ot /Oy /MD /GS- /GL"
    )

    set(
        CMAKE_EXE_LINKER_FLAGS_RELEASE
        "/OPT:REF /OPT:ICF /LTCG /INCREMENTAL:NO"
    )
endif()

add_executable(
    RIFT
    ${CPP_SOURCES}
)

# Optional libraries for OpenImageIO
if(USE_PLUGINS)
    set(
        OPEN_EXR_LIBS
        ${RIFT_DEPENDENCIES_DIR}/openexr-release/lib/IlmImf-2_2.lib
        ${RIFT_DEPENDENCIES_DIR}/openexr-release/lib/IlmImfUtil-2_2.lib
        ${RIFT_DEPENDENCIES_DIR}/ilmbase-release/lib/Half.lib
        ${RIFT_DEPENDENCIES_DIR}/ilmbase-release/lib/IlmThread-2_2.lib
        ${RIFT_DEPENDENCIES_DIR}/ilmbase-release/lib/Iex-2_2.lib
        ${RIFT_DEPENDENCIES_DIR}/ilmbase-release/lib/IexMath-2_2.lib
        ${RIFT_DEPENDENCIES_DIR}/ilmbase-release/lib/Imath-2_2.lib
    )

    set(
        ZLIB_LIBS
        ${RIFT_DEPENDENCIES_DIR}/zlib-release/lib/zlibstatic.lib
    )

    set(
        OIIO_LIBS
        ${RIFT_DEPENDENCIES_DIR}/oiio-release/lib/OpenImageIO.lib
        ${RIFT_DEPENDENCIES_DIR}/oiio-release/lib/OpenImageIO_Util.lib
    )

    set(
        TIFF_LIB
        ${RIFT_DEPENDENCIES_DIR}/libtiff-release/lib/libtiff.lib
        )

    set(
        PNG_LIB
        ${RIFT_DEPENDENCIES_DIR}/libpng-release/lib/libpng16_static.lib
    )

    set(
        JPEG_LIB
        ${RIFT_DEPENDENCIES_DIR}/libjpeg-turbo-release/lib/jpeg-static.lib
    )

    target_link_libraries(
        RIFT
        ${OPEN_EXR_LIBS}
        ${ZLIB_LIBS}
        ${TIFF_LIB}
        ${Boost_LIBRARIES}
        ${OIIO_LIBS}
        ${PNG_LIB}
        ${JPEG_LIB}
    )
endif()

# Visual Studio folder layout
source_group(
    "src\\core\\acceleration_structures" REGULAR_EXPRESSION
    src/core/acceleration_structures/.*
)

source_group(
    "src\\core\\image_writers" REGULAR_EXPRESSION
    src/core/image_writers/.*
)

source_group(
    "src\\core\\lighting_integrators" REGULAR_EXPRESSION
    src/core/lighting_integrators/.*
)

source_group(
    "src\\core\\rendering" REGULAR_EXPRESSION
    src/core/rendering/.*
)

source_group(
    "src\\core\\samplers" REGULAR_EXPRESSION
    src/core/samplers/.*
)

source_group(
    "src\\materials" REGULAR_EXPRESSION
    src/materials/.*
)

source_group(
    "src\\object\\cameras" REGULAR_EXPRESSION
    src/objects/camera/.*
)

source_group(
    "src\\object\\hitables" REGULAR_EXPRESSION
    src/objects/hitables/.*
)

source_group(
    "src\\textures" REGULAR_EXPRESSION
    src/textures/.*
)

source_group(
    "src\\third_party" REGULAR_EXPRESSION
    src/third_party/.*
)

source_group(
    "src\\utility\\containers" REGULAR_EXPRESSION
    src/utility/containers/.*
)

source_group(
    "src\\utility\\buffers" REGULAR_EXPRESSION
    src/utility/buffers/.*
)

source_group(
    "src\\utility\\data_types" REGULAR_EXPRESSION
    src/utility/data_types/.*
)

source_group(
    "src\\utility\\generators" REGULAR_EXPRESSION
    src/utility/generators/.*
)

source_group(
    "src\\utility\\math_functions" REGULAR_EXPRESSION
    src/utility/math_functions/.*
)

source_group(
    "src\\utility\\math_functions\\pdf" REGULAR_EXPRESSION
    src/utility/math_functions/pdfs.*
)

source_group(
    "src\\utility\\noises" REGULAR_EXPRESSION
    src/utility/noises/.*
)

source_group(
    "src\\utility\\rng" REGULAR_EXPRESSION
    src/utility/rng/.*
)

source_group(
    "src\\utility\\qmc" REGULAR_EXPRESSION
    src/utility/qmc/.*
)

source_group(
    "src\\utility\\version" REGULAR_EXPRESSION
    src/utility/version/.*
)