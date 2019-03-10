cmake_minimum_required(VERSION 3.0.0)
project(RIFT_renderer VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 14)

set (version_major    0)
set (version_minor    1)
set (version_patch    0)
set (version_maturity alpha)

configure_file (${PROJECT_SOURCE_DIR}/src/utility/version/version.h.in
                ${PROJECT_SOURCE_DIR}/src/utility/version/version.h)

include_directories(
    src
    applications/RIFT_cli
)

set (
    CAMERA_SOURCES
    src/camera/thin_lens_camera.h
    src/camera/thin_lens_camera.cpp
)

source_group(
    "src\\camera" REGULAR_EXPRESSION
    src/camera/.*
)

set (
    CORE_SOURCES
    src/core/bases/ihitable.h
    src/core/bases/icamera.h
    src/core/acceleration_structures/bvh_node.h
    src/core/acceleration_structures/bvh_node.cpp
    src/core/bases/imaterial.h
    src/core/rendering/onb.h
    src/core/rendering/render_controller.h
    src/core/rendering/render_controller.cpp
    src/core/rendering/render_worker.h
    src/core/rendering/render_worker.cpp
    src/core/image_writers/jpeg_writer.cpp
    src/core/image_writers/jpeg_writer.h
    src/core/image_writers/ioutput_writer.h
    src/core/bases/itexture.h
    src/core/data_types/ray.h
    src/core/data_types/vec3.h
    src/core/data_types/aabb.h
    src/core/data_types/aabb.cpp
    src/core/data_types/scene.h
    src/core/rendering/utility_functions.h
    src/core/acceleration_structures/bvh_utils.h
    src/core/rendering/scatter_functions.h
    src/core/data_types/hit_record.h
    src/core/image_writers/png_writer.cpp
    src/core/image_writers/png_writer.h
    src/core/pdfs/pdf.h
    src/core/pdfs/cosine_pdf.cpp
    src/core/pdfs/cosine_pdf.h
    src/core/pdfs/hitable_pdf.h
    src/core/pdfs/mixture_pdf.h
)

source_group(
    "src\\core\\pdfs" REGULAR_EXPRESSION
    src/core/pdfs/.*
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
    src/utility/rng/xoroshiro128.h
    src/utility/rng/xoroshiro128.cpp
    src/utility/rng/igenerator.h
    src/utility/rng/drand48.cpp
    src/utility/rng/drand48.h
    src/utility/noises/perlin.h
    src/utility/containers/render_settings.h
    applications/RIFT_cli/command_line_parser.h
    applications/RIFT_cli/command_line_parser.cpp
    src/utility/version/version.h
)

source_group(
    "src\\utilities\\version" FILES
    src/utility/version/version.h.in
)

source_group(
    "src\\utilities\\parsers" REGULAR_EXPRESSION
    src/utility/parsers/.*
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
    "src\\utilities\\rng" REGULAR_EXPRESSION
    src/utility/rng/.*
)

set (
    MAIN_SOURCE
    applications/RIFT_cli/main.cpp
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

add_executable(
    number_generator_test
    utility_apps/number_generator/main.cpp
    src/utility/rng/xoroshiro128.cpp
)
