#include "render_controller.h"

#include "core/data_types/vec3.h"
#include "core/image_writers/jpeg_writer.h"
#include "utility_functions.h"
#include "camera/camera.h"

#include "render_unit.h"


#include <fstream>
#include <iomanip>
#include <thread>


render_controller::render_controller(
        const char* filename,
        int nx,
        int ny,
        int ns,
        camera* cam,
        hitable* world)
  : nx(nx)
  , out_filename(filename)
  , image_writer(new jpeg_writer)
  , buffer(new float[nx * ny *3])
  , ny(ny)
  , ns(ns)
  , inv_nx(1.f / nx)
  , inv_ny(1.f / ny)
  , inv_ns(1.f / ns)
  , cam(cam)
  , world(world)
{}

void render_controller::do_render()
{
    auto seed_1 = static_cast<uint64_t>(time(nullptr));

    random_generator = new xoro_128;
    random_generator->seed_gen(seed_1);

    std::cout << "Generating Pixels..." << std::endl;

    std::vector<std::thread> threads;

    int samples_per_thread = ns / 8;

    threads.reserve(8);

    std::cout << "Number of samples per thread: " << samples_per_thread << std::endl;

    for (int i = 0; i < 8; i++)
    {
        threads.push_back(
            std::thread(
                render_worker::run_thread,
                random_generator->next(),
                nx,
                ny,
                samples_per_thread,
                buffer,
                cam,
                world));
    }

    for (auto& thread : threads)
    {
        thread.join();
    }

    int buffer_size = nx * ny * 3;

    for (size_t i = 0; i <buffer_size; i++)
    {
        buffer[i] *= inv_ns;
    }
}

render_controller::~render_controller()
{

}

void render_controller::cleanup()
{
    delete[] buffer;
    delete cam;
    delete world;
    delete random_generator;
    delete image_writer;
    delete out_filename;

    std::cout << "Renderer Deleted" << std::endl;
}
