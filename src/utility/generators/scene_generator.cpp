// Released under MIT License

// Copyright (c) 2018 Jonathan Dent.

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "scene_generator.h"

#include "core/acceleration_structures/bvh_node.h"
#include "materials/dielectric.h"
#include "materials/lambertian.h"
#include "materials/metal.h"
#include "objects/camera/thin_lens_camera.h"
#include "objects/hitables/box.h"
#include "objects/hitables/constant_medium.h"
#include "objects/hitables/hitable_list.h"
#include "objects/hitables/instancers.h"
#include "objects/hitables/moving_sphere.h"
#include "objects/hitables/rect.h"
#include "objects/hitables/sky_sphere.h"
#include "objects/hitables/sphere.h"
#include "textures/checker_tex.h"
#include "textures/constant_tex.h"
#include "utility/containers/render_settings.h"

#define STB_IMAGE_IMPLEMENTATION
#include "third_party/stb_image.h"

#include <random>
#include "textures/image_texture.h"

// Class implementation
void SceneGenerator::make_random_scene(
    Scene*                in_scene,
    const RenderSettings& settings)
{
    const int n = 500;

    auto** list = new IHitable*[n + 1];

    std::mt19937_64 random_generator;

    const auto seed_val = static_cast<uint_fast64_t>(time(nullptr));

    random_generator.seed(seed_val);

    // Ground
    list[0] = new Sphere(
        Vec3(0.f, -1000.f, 0.f),
        1000.f,
        new Lambertian(new CheckerTexture(
            new ConstantTexture(Vec3(0.2f, 0.3f, 0.1f)),
            new ConstantTexture(Vec3(0.9f, 0.9f, 0.9f)))));

    int i = 1;

    for (int a = -11; a < 11; a++)
    {
        for (int b = -11; b < 11; b++)
        {
            const float choose_mat = random_generator();
            Vec3        center(
                a + 0.9f * (random_generator()),
                0.2f,
                b + 0.9f * (random_generator()));
            if ((center - Vec3(4.f, 0.2f, 0.f)).length() > 0.9f)
            {
                if (choose_mat < 0.8f)
                {
                    list[i++] = new MovingSphere(
                        center,
                        center + Vec3(0.f, 0.5f * random_generator(), 0.f),
                        0.f,
                        0.5f,
                        0.2f,
                        new Lambertian(new ConstantTexture(Vec3(
                            random_generator() * random_generator(),
                            random_generator() * random_generator(),
                            random_generator() * random_generator()))));
                }
                else if (choose_mat < 0.95f)
                {
                    list[i++] = new Sphere(
                        center,
                        0.2f,
                        new Metal(
                            Vec3(
                                0.5f * (1 + random_generator()),
                                0.5f * (1 + random_generator()),
                                0.5f * (1 + random_generator())),
                            random_generator()));
                }
                else
                {
                    list[i++] = new Sphere(center, 0.2f, new Dielectric(1.5f));
                }
            }
        }
    }

    list[i++] = new Sphere(Vec3(0.f, 1.f, 0.f), 1.f, new Dielectric(1.5f));

    list[i++] = new Sphere(
        Vec3(-1.f, 1.f, -2.f),
        1.f,
        new Lambertian(new ConstantTexture(Vec3(0.4f, 0.2f, 0.1f))));

    list[i++] = new Sphere(
        Vec3(1.f, 1.f, 2.f), 1.f, new Metal(Vec3(0.7f, 0.6f, 0.5f), 0.03f));

    list[i++] = new FlipNormals(new SkySphere(
        new SkyGradient(Vec3(1.f, 1.f, 1.f), Vec3(0.3f, 0.6f, 1.f))));

    const Vec3  lookfrom(0.f, 2.f, 8.f);
    const Vec3  lookat(0.f, 1.f, 0.f);
    const float dist_to_focus = (lookfrom - lookat).length();
    const float aperture = 0.05f;

    in_scene->m_cam = new ThinLensCamera(
        lookfrom,
        lookat,
        Vec3(0.f, 1.f, 0.f),
        40.f,
        float(settings.m_resolution_x) / float(settings.m_resolution_y),
        aperture,
        dist_to_focus,
        0.f,
        0.5f);
    in_scene->m_world = new BVHNode(list, i, 0.f, 0.5f);
    in_scene->m_light_source = nullptr;
}
/*
IHitable* SceneGenerator::two_spheres()
{
    auto** list = new IHitable*[2];
    list[0] = new Sphere(
        Vec3(0.f, -1000.f, 0.f),
        1000.f,
        new Lambertian(new NoiseTexture(3.f)));

    list[1] = new Sphere(
        Vec3(0.f, 2.f, 0.f), 2.f, new Lambertian(new NoiseTexture(3.f)));
    return new HitableList(list, 2);
}
*/
void* SceneGenerator::earth_sphere(Scene* in_scene, const RenderSettings& settings)
{
    int            m_nx, m_ny, nn;
    unsigned char* tex_data = stbi_load(
        "../m_world.topo.bathy.200401.3x5400x2700.jpg", &m_nx, &m_ny, &nn, 0);

    IHitable* earth_sphere = new Sphere(
        Vec3(0.f, 1.f, 0.f),
        2.f,
        new Lambertian(new ImageTexture(tex_data, m_nx, m_ny)));

    const Vec3  lookfrom(0.f, 2.f, 8.f);
    const Vec3  lookat(0.f, 1.f, 0.f);
    const float dist_to_focus = (lookfrom - lookat).length();
    const float aperture = 0.05f;

    ICamera* m_cam = new ThinLensCamera(
        lookfrom,
        lookat,
        Vec3(0.f, 1.f, 0.f),
        40.f,
        float(settings.m_resolution_x) / float(settings.m_resolution_y),
        aperture,
        dist_to_focus,
        0.f,
        0.5f);

    return new Scene{m_cam, earth_sphere};
}
/*
Scene* SceneGenerator::rect_light(int m_nx, int m_ny)
{
    auto** list = new IHitable*[3];
    list[0] = new Sphere(
        Vec3(0.f, -1000.f, 0.f),
        1000.f,
        new Lambertian(new NoiseTexture(4.f)));

    list[1] = new Sphere(
        Vec3(0.f, 2.f, 0.f), 2.f, new Lambertian(new NoiseTexture(4.f)));

    list[2] = new XYRect(
        3.f,
        5.f,
        1.f,
        3.f,
        -2.f,
        new DiffuseLight(new ConstantTexture(Vec3(4.f, 4.f, 4.f))));

    //    list[3] = new Sphere(
    //        Vec3(0.f, 7.f, 0.f),
    //        2.f,
    //        new DiffuseLight(
    //            std::make_unique<ConstantTexture>(
    //                Vec3(4.f, 4.f, 4.f))));

    const Vec3  lookfrom(8.f, 2.f, 9.f);
    const Vec3  lookat(1.f, 1.f, 0.f);
    const float dist_to_focus = (lookfrom - lookat).length();
    const float aperture = 0.05f;

    ICamera* m_cam = new ThinLensCamera(
        lookfrom,
        lookat,
        Vec3(0.f, 1.f, 0.f),
        40.f,
        float(m_nx) / float(m_ny),
        aperture,
        dist_to_focus,
        0.f,
        0.5f);

    return new Scene{m_cam, new HitableList(list, 3)};
}
*/

void SceneGenerator::cornell_box(
    Scene*                in_scene,
    const RenderSettings& settings)
{
    auto* list = new std::vector<IHitable*>;

    in_scene->m_textures.emplace(
        "red_rgb", new ConstantTexture(Vec3(0.65f, 0.05f, 0.05f)));
    in_scene->m_textures.emplace(
        "white_rgb", new ConstantTexture(Vec3(0.73f, 0.73f, 0.73f)));
    in_scene->m_textures.emplace(
        "green_rgb", new ConstantTexture(Vec3(0.12f, 0.45f, 0.15f)));
    in_scene->m_textures.emplace(
        "light_rgb", new ConstantTexture(Vec3(15.f, 15.f, 15.f)));

    in_scene->m_materials.emplace(
        "red", new Lambertian(in_scene->m_textures.find("red_rgb")->second));
    in_scene->m_materials.emplace(
        "white",
        new Lambertian(in_scene->m_textures.find("white_rgb")->second));
    in_scene->m_materials.emplace(
        "green",
        new Lambertian(in_scene->m_textures.find("green_rgb")->second));
    in_scene->m_materials.emplace(
        "light",
        new DiffuseLight(in_scene->m_textures.find("light_rgb")->second));

    list->emplace_back(new FlipNormals(new YZRect(
        0, 555, 0, 555, 555, in_scene->m_materials.find("green")->second)));

    list->emplace_back(new YZRect(
        0, 555, 0, 555, 0, in_scene->m_materials.find("red")->second));

    list->emplace_back(new FlipNormals(new XZRect(
        213, 343, 227, 332, 554, in_scene->m_materials.find("light")->second)));

    list->emplace_back(new FlipNormals(new XZRect(
        0, 555, 0, 555, 555, in_scene->m_materials.find("white")->second)));

    list->emplace_back(new XZRect(
        0, 555, 0, 555, 0, in_scene->m_materials.find("white")->second));

    list->emplace_back(new FlipNormals(new XYRect(
        0, 555, 0, 555, 555, in_scene->m_materials.find("white")->second)));

    list->emplace_back(new Translate(
        new RotateY(
            new Box(
                Vec3(0, 0, 0),
                Vec3(165, 165, 165),
                in_scene->m_materials.find("white")->second),
            -18),
        Vec3(130, 0, 65)));

    list->emplace_back(new Translate(
        new RotateY(
            new Box(
                Vec3(0, 0, 0),
                Vec3(165, 330, 165),
                in_scene->m_materials.find("white")->second),
            15),
        Vec3(265, 0, 295)));

    const Vec3  lookfrom(278.f, 278.f, -800.f);
    const Vec3  lookat(278.f, 278.f, 0.f);
    const float dist_to_focus = (lookfrom - lookat).length();
    const float aperture = 0.05f;

    in_scene->m_cam = new ThinLensCamera(
        lookfrom,
        lookat,
        Vec3(0.f, 1.f, 0.f),
        40.f,
        float(settings.m_resolution_x) / float(settings.m_resolution_y),
        aperture,
        dist_to_focus,
        0.f,
        0.5f);

    in_scene->m_world = new HitableList(list);
    in_scene->m_light_source =
        new XZRect(213.f, 343.f, 227.f, 332.f, 554.f, nullptr);
}
/*
void SceneGenerator::smoky_cornell_box(
    Scene*                in_scene,
    const RenderSettings& settings)
{
    auto** list = new IHitable*[8];
    int    i = 0;

    IMaterial* red =
        new Lambertian(new ConstantTexture(Vec3(0.65f, 0.05f, 0.05f)));
    IMaterial* white =
        new Lambertian(new ConstantTexture(Vec3(0.73f, 0.73f, 0.73f)));
    IMaterial* green =
        new Lambertian(new ConstantTexture(Vec3(0.12f, 0.45f, 0.15f)));
    IMaterial* light =
        new DiffuseLight(new ConstantTexture(Vec3(7.f, 7.f, 7.f)));
    IMaterial* aluminum = new Metal(Vec3(0.8f, 0.85f, 0.88f), 0.f);

    list[i++] = new FlipNormals(new YZRect(0, 555, 0, 555, 555, green));

    list[i++] = new YZRect(0, 555, 0, 555, 0, red);

    list[i++] = new FlipNormals(new XZRect(113, 443, 127, 432, 554, light));

    list[i++] = new FlipNormals(new XZRect(0, 555, 0, 555, 555, white));

    list[i++] = new XZRect(0, 555, 0, 555, 0, white);

    list[i++] = new FlipNormals(new XYRect(0, 555, 0, 555, 555, white));

    IHitable* b1 = new Translate(
        new RotateY(new Box(Vec3(0, 0, 0), Vec3(165, 165, 165), white), -18),
        Vec3(130, 0, 65));

    IHitable* b2 = new Translate(
        new RotateY(new Box(Vec3(0, 0, 0), Vec3(165, 330, 165), white), 15),
        Vec3(265, 0, 295));

    list[i++] =
        new ConstantMedium(b1, 0.01f, new ConstantTexture(Vec3(1.f, 1.f, 1.f)));

    list[i++] = new ConstantMedium(
        b2, 0.01f, new ConstantTexture(Vec3(0.3f, 0.3f, 0.3f)));

    const Vec3  lookfrom(278.f, 278.f, -800.f);
    const Vec3  lookat(278.f, 278.f, 0.f);
    const float dist_to_focus = (lookfrom - lookat).length();
    const float aperture = 0.05f;

    in_scene->m_cam = new ThinLensCamera(
        lookfrom,
        lookat,
        Vec3(0.f, 1.f, 0.f),
        40.f,
        float(settings.m_resolution_x) / float(settings.m_resolution_y),
        aperture,
        dist_to_focus,
        0.f,
        0.5f);
    in_scene->m_world = new HitableList(list, i);
    in_scene->m_light_source =
        new XZRect(213.f, 343.f, 227.f, 332.f, 554.f, nullptr);
}*/
