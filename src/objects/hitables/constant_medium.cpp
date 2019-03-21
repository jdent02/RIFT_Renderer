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

#include "constant_medium.h"

#include "utility/math_functions/utility_functions.h"
// #include "materials/isotropic.h"

#include <cfloat>

ConstantMedium::ConstantMedium(IHitable* b, float d, ITexture* a)
  : m_boundary_(b)
  , m_density_(d)
{
    // m_phase_function_ = std::make_unique<Isotropic>(a);
}

bool ConstantMedium::hit(const Ray& r, float t_min, float t_max, HitRecord& rec)
    const
{
    bool db;
    db = false;

    HitRecord rec1, rec2;
    if (m_boundary_->hit(r, -FLT_MAX, FLT_MAX, rec1))
    {
        if (m_boundary_->hit(r, rec1.m_t + 0.0001f, FLT_MAX, rec2))
        {
            if (db)
                std::cerr << "Whoopsie\n";
            if (rec1.m_t < t_min)
                rec1.m_t = t_min;
            if (rec2.m_t > t_max)
                rec2.m_t = t_max;
            if (rec1.m_t >= rec2.m_t)
                return false;
            if (rec1.m_t < 0)
                rec1.m_t = 0;

            float distance_inside_boundary =
                (rec2.m_t = rec1.m_t) * r.direction().length();
            float hit_distance = -(1 / m_density_) * std::log(rand() * INV_RAND_MAX);
            if (hit_distance < distance_inside_boundary)
            {
                if (db)
                    std::cerr << "You suck\n";
                rec.m_t = rec1.m_t + hit_distance / r.direction().length();
                rec.m_p = r.point_at_parameter(rec.m_t);
                rec.m_normal = Vec3(1.f, 0.f, 0.f);
                rec.m_mat_ptr = m_phase_function_.get();
                return true;
            }
        }
    }

    return false;
}

bool ConstantMedium::bounding_box(float t0, float t1, AABB& box) const
{
    return m_boundary_->bounding_box(t0, t1, box);
}
