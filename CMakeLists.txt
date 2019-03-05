cmake_minimum_required(VERSION 3.0.0)
project(FARTS_renderer VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 14)

include_directories(
    ${STB_LIB}
    src
)

set (
    CAMERA_SOURCES
    src/camera/camera.h
    src/camera/camera.cpp
)

source_group(
    "src\\camera" REGULAR_EXPRESSION
    src/camera/.*
)

set (
    HITABLES_SOURCES
    src/hitables/hitable.h
    src/hitables/hitable_list.h
    src/hitables/sphere.h
    src/hitables/sphere.cpp
    src/hitables/moving_sphere.h
    src/hitables/moving_sphere.cpp
    src/hitables/bvh_node.h
    src/hitables/bvh_node.cpp
    src/hitables/rect.cpp
    src/hitables/rect.h
    src/hitables/box.cpp
    src/hitables/box.h
    src/hitables/instancers.cpp
    src/hitables/instancers.h)

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
    src/materials/material.h
    src/materials/metal.h
    src/materials/metal.cpp
)

source_group(
    "src\\materials" REGULAR_EXPRESSION
    src/materials/.*
)

set (
    RENDERING_SOURCES
    src/core/rendering/render.h
    src/core/rendering/render.cpp
    src/core/rendering/render_unit.h)

source_group(
    "src\\rendering" REGULAR_EXPRESSION
    src/rendering/.*
)

set (
    TEXTURE_SOURCES
    src/textures/constant_tex.h
    src/textures/texture.h
    src/textures/checker_tex.h
    src/textures/checker_tex.cpp
    src/textures/noise_texture.h
    src/textures/image_texture.cpp
    src/textures/image_texture.h)

source_group(
    "src\\textures" REGULAR_EXPRESSION
    src/textures/.*
)

set (
    UTILITY_SOURCES
    src/utility/data_types/ray.h
    src/utility/data_types/vec3.h
    src/utility/data_types/aabb.h
    src/utility/data_types/aabb.cpp
    src/utility/generators/scene_generator.h
    src/utility/generators/scene_generator.cpp
    src/utility/utility_functions.h
    src/utility/bvh_utils.h
    src/utility/scatter_functions.h
    src/utility/rng/xoroshiro128.h
    src/utility/rng/xoroshiro128.cpp
    src/utility/rng/igenerator.h
    src/utility/rng/drand48.cpp
    src/utility/rng/drand48.h
    src/utility/noises/perlin.h
)

source_group(
    "src\\utilities\\noises" REGULAR_EXPRESSION
    src/utility/noises/.*
)

source_group(
    "src\\utilities\\data_types" REGULAR_EXPRESSION
    src/utility/data_types/.*
)

source_group(
    "src\\utilities\\generators" REGULAR_EXPRESSION
    src/utility/generators/.*
)

source_group(
    "src\\utilities" REGULAR_EXPRESSION
    src/utility/.*
)

source_group(
    "src\\utilities\\rng" REGULAR_EXPRESSION
    src/utility/rng/.*
)

set (
    MAIN_SOURCE
    main.cpp
)

set (
    CPP_SOURCES
    ${MAIN_SOURCE}
    ${CAMERA_SOURCES}
    ${HITABLES_SOURCES}
    ${MATERIAL_SOURCES}
    ${RENDERING_SOURCES}
    ${TEXTURE_SOURCES}
    ${UTILITY_SOURCES}
    ${RNG_SOURCES}
)

source_group(
    "src\\" FILES
    ${MAIN_SOURCE}
)

add_executable(
    FARTS_renderer
    ${CPP_SOURCES}
)
