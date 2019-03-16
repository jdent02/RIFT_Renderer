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
option(USE_OPENEXR "Enable OpenEXR file input and output" Off)
set(DEPENDENCIES_DIR "" CACHE PATH "Path to dependencies dirctory")

if (USE_OPENEXR)
    add_definitions(-DRIFT_USE_OPENEXR)
endif()
 
include_directories(
    src
)

if (USE_OPENEXR)
    include_directories(
        ${DEPENDENCIES_DIR}/openexr-release/include
        ${DEPENDENCIES_DIR}/ilmbase-release/include/OpenEXR
    )
endif()

set (
    CAMERA_SOURCES
    src/camera/i_camera.h
    src/camera/thin_lens_camera.h
    src/camera/thin_lens_camera.cpp
)

source_group(
    "src\\camera" REGULAR_EXPRESSION
    src/camera/.*
)

set (
    CORE_SOURCES
    src/core/acceleration_structures/bvh_node.h
    src/core/acceleration_structures/bvh_node.cpp
    src/core/acceleration_structures/aabb.h
    src/core/acceleration_structures/aabb.cpp
    src/core/acceleration_structures/bvh_utils.h

    src/core/lighting_integrators/direct_lighting.cpp
    src/core/lighting_integrators/direct_lighting.h
    src/core/lighting_integrators/i_light_integrator.h
    src/core/lighting_integrators/path_tracer.h
    src/core/lighting_integrators/path_tracer.cpp
    src/core/lighting_integrators/light_sample_path.cpp
    src/core/lighting_integrators/light_sample_path.h

    src/core/onb/onb.h

    src/core/rendering/utility_functions.h
    src/core/rendering/render_controller.h
    src/core/rendering/render_controller.cpp
    src/core/rendering/render_worker.h
    src/core/rendering/render_worker.cpp
    src/core/rendering/scatter_functions.h
    src/core/rendering/color_functions.h

    src/core/image_writers/jpeg_writer.cpp
    src/core/image_writers/jpeg_writer.h
    src/core/image_writers/i_out_writer.h
    src/core/image_writers/oiio_writer.h
    src/core/image_writers/oiio_writer.cpp
    src/core/image_writers/png_writer.cpp
    src/core/image_writers/png_writer.h

    src/core/data_types/ray.h
    src/core/data_types/vec3.h
    src/core/data_types/hit_record.h
    src/core/data_types/scatter_record.h

    src/core/pdfs/pdf.h
    src/core/pdfs/cosine_pdf.cpp
    src/core/pdfs/cosine_pdf.h
    src/core/pdfs/hitable_pdf.h
    src/core/pdfs/mixture_pdf.h
    
    src/core/samplers/rng/xoroshiro128.h
    src/core/samplers/rng/xoroshiro128.cpp
    src/core/samplers/rng/i_rand_generator.h
    src/core/samplers/rng/drand48.cpp
    src/core/samplers/rng/drand48.h
    src/core/samplers/samplers/i_sampler.h
)

if(USE_OPENEXR)
    list(APPEND CORE_SOURCES
         src/core/image_writers/open_exr_writer.h
         src/core/image_writers/open_exr_writer.cpp
    )
endif()

source_group(
    "src\\core\\pdfs" REGULAR_EXPRESSION
    src/core/pdfs/.*
)

source_group(
    "src\\core\\lighting_integrators"
    src/core/lighting_integrators/.*
)

source_group(
    "src\\core\\samplers\\QMC" REGULAR_EXPRESSION
    src/core/samplers/monte_carlo_sequences/.*
)

source_group(
    "src\\core\\samplers\\rng" REGULAR_EXPRESSION
    src/core/samplers/rng/.*
)

source_group(
    "src\\core\\samplers" REGULAR_EXPRESSION
    src/core/samplers/.*
)

source_group(
    "src\\core\\onb" REGULAR_EXPRESSION
    src/core/onb/.*
)

source_group(
    "src\\core\\acceleration_structures" REGULAR_EXPRESSION
    src/core/acceleration_structures/.*
)

source_group(
    "src\\core\\bases" REGULAR_EXPRESSION
    src/core/bases/.*
)

source_group(
    "src\\core\\rendering" REGULAR_EXPRESSION
    src/core/rendering/.*
)

source_group(
    "src\\core\\image_writers" REGULAR_EXPRESSION
    src/core/image_writers./*
)

source_group(
    "src\\core\\data_types" REGULAR_EXPRESSION
    src/core/data_types/.*
)

set (
    HITABLES_SOURCES
    src/hitables/i_hitable.h
    src/hitables/hitable_list.h
    src/hitables/sphere.h
    src/hitables/sphere.cpp
    src/hitables/moving_sphere.h
    src/hitables/moving_sphere.cpp
    src/hitables/rect.cpp
    src/hitables/rect.h
    src/hitables/box.cpp
    src/hitables/box.h
    src/hitables/instancers.cpp
    src/hitables/instancers.h
    src/hitables/sky_sphere.h
)

source_group(
    "src\\hitables" REGULAR_EXPRESSION
    src/hitables/.*
)

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

source_group(
    "src\\materials" REGULAR_EXPRESSION
    src/materials/.*
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

source_group(
    "src\\textures" REGULAR_EXPRESSION
    src/textures/.*
)

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
)

source_group(
    "src\\utilities\\math_functions" REGULAR_EXPRESSION
    src/utility/math_functions/.*
)

source_group(
    "src\\utilities\\version" FILES
    src/utility/version/version.h
    src/utility/version/version.h.in
)

source_group(
    "src\\utilities\\noises" REGULAR_EXPRESSION
    src/utility/noises/.*
)

source_group(
    "src\\utilities\\containers" REGULAR_EXPRESSION
    src/utility/containers/.*
)

source_group(
    "src\\utilities\\generators" REGULAR_EXPRESSION
    src/utility/generators/.*
)

source_group(
    "cmd_parser" FILES
    applications/RIFT_cli/command_line_parser.h
    applications/RIFT_cli/command_line_parser.cpp
)

source_group(
    "main" FILES
    applications/RIFT_cli/main.cpp
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

add_executable(
    RIFT
    ${CPP_SOURCES}
)


# Optional libraries for OpenEXR
if(USE_OPENEXR)
    set(OPEN_EXR_LIBS
        ${DEPENDENCIES_DIR}/openexr-release/lib/IlmImf-2_2.lib
        ${DEPENDENCIES_DIR}/openexr-release/lib/IlmImfUtil-2_2.lib
    )

    set(ILM_BASE_LIBS
        ${DEPENDENCIES_DIR}/ilmbase-release/lib/Half.lib
        ${DEPENDENCIES_DIR}/ilmbase-release/lib/IlmThread-2_2.lib
        ${DEPENDENCIES_DIR}/ilmbase-release/lib/Iex-2_2.lib
        ${DEPENDENCIES_DIR}/ilmbase-release/lib/IexMath-2_2.lib
        ${DEPENDENCIES_DIR}/ilmbase-release/lib/Imath-2_2.lib
    )

    set(ZLIB_LIBS
        ${DEPENDENCIES_DIR}/zlib-release/lib/zlibstatic.lib
    )

    target_link_libraries(
        RIFT
        ${OPEN_EXR_LIBS}
        ${ILM_BASE_LIBS}
        ${ZLIB_LIBS}
    )
endif()

add_executable(
    number_generator_test
    utility_apps/number_generator/main.cpp
    src/core/samplers/rng/xoroshiro128.cpp
)
