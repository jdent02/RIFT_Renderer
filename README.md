# RIFT Renderer
Just a personal toolbox for rendering experiments.  Originally started as an implementation of Peter Shirley's "Raytracing in One Weekend", because why not?

Name is an acronym for "Reduction in Free Time".

Compiles with all major compilers: VC++, GCC and Clang.  Clang seems to be the fastest.

Includes headers from the STB image library: https://github.com/nothings/stb

For OpenEXR reading and writing, OpenEXR 2.2 or later is needed.  If you do not intend to use this function, please pass "-DUSE_OPENEXR=OFF" to CMake.
