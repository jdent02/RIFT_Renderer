#include "render_controller.h"

#include "core/image_writers/jpeg_writer.h"
#include "core/image_writers/png_writer.h"
#include "core/rendering/render_worker.h"
#include "utility/rng/xoroshiro128.h"

#include <fstream>
#include <iomanip>
#include <thread>
#include <vector>


render_controller::render_controller(
    const char* filename,
    const int   nx,
    const int   ny,
    const int   ns,
    icamera*    cam,
    ihitable*   world)
  : buffer_(new float[nx * ny * 3])
  , nx_(nx)
  , ny_(ny)
  , ns_(ns)
  , inv_ns_(1.f / ns)
  , cam_(cam)
  , world_(world)
  , image_writer_(new png_writer)
  , out_filename_(filename)
{}

void render_controller::do_render()
{
    const auto seed_1 = static_cast<uint64_t>(time(nullptr));

    random_generator_ = new xoro_128;
    random_generator_->seed_gen(seed_1);

    std::cout << "Generating Pixels..." << std::endl;

    std::vector<std::thread> threads;

    int samples_per_thread = ns_ / 8;

    threads.reserve(8);

    std::cout << "Number of samples per thread: " << samples_per_thread
              << std::endl;

    for (int i = 0; i < 8; i++)
    {
        threads.emplace_back(
            render_worker::run_thread,
            int(random_generator_->next()),
            nx_,
            ny_,
            samples_per_thread,
            buffer_,
            cam_,
            world_);
    }

    for (auto& thread : threads)
    {
        thread.join();
    }

    const int buffer_size = nx_ * ny_ * 3;

    for (int i = 0; i < buffer_size; i++)
    {
        buffer_[i] *= inv_ns_;
    }
}

void render_controller::cleanup() const
{
    delete[] buffer_;
    delete random_generator_;
    delete image_writer_;

    std::cout << "Renderer Deleted" << std::endl;
}
