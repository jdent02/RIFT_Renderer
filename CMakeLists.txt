cmake_minimum_required(VERSION 3.0.0)
project(FARTS_renderer VERSION 0.1.0)

include_directories(
    src
)

set (CAMERA_SOURCES
    src/camera/camera.h
    src/camera/camera.cpp
)

set (HITABLES_SOURCES
    src/hitables/hitable_list.h
    src/hitables/hitable.h
    src/hitables/sphere.h
)

set (MATERIAL_SOURCES
    src/materials/dielectric.h
    src/materials/dielectric.cpp
    src/materials/edf.h
    src/materials/lambertian.h
    src/materials/material.h
    src/materials/metal.h
)

set (RENDERING_SOURCES
    src/rendering/render.h
    src/rendering/render.cpp
)

set (TEXTURE_SOURCES
    src/textures/constant_tex.h
    src/textures/texture.h
    src/textures/checker_tex.h
    src/textures/checker_tex.cpp
)

set (UTILITY_SOURCES
	src/utility/rng/xoroshiro128.h
	src/utility/rng/xoroshiro128.cpp
	src/utility/generators/scene_generator.h
	src/utility/generators/scene_generator.cpp
	src/utility/data_types/ray.h
	src/utility/utility_functions.h
	src/utility/data_types/vec3.h src/utility/scatter_functions.h)

set (MAIN_SOURCE
    main.cpp
)

set (CPP_SOURCES
    ${MAIN_SOURCE}
    ${CAMERA_SOURCES}
    ${HITABLES_SOURCES}
    ${MATERIAL_SOURCES}
    ${RENDERING_SOURCES}
    ${TEXTURE_SOURCES}
    ${UTILITY_SOURCES}
	${RNG_SOURCES}
)

source_group("src\\" FILES
    ${MAIN_SOURCE}
)

source_group("src\\cameras" FILES
    ${CAMERA_SOURCES}
)

source_group("src\\hitables" FILES
    ${HITABLES_SOURCES}
)

source_group("src\\materials" FILES
    ${MATERIAL_SOURCES}
)

source_group("src\\rendering" FILES
    ${RENDERING_SOURCES}
)

source_group("src\\textures" FILES
    ${TEXTURE_SOURCES}
)

source_group("src\\utilities" FILES
    ${UTILITY_SOURCES}
)
 
add_executable(FARTS_renderer
    ${CPP_SOURCES}    
)
