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

#include "box.h"

#include "core/acceleration_structures/aabb.h"
#include "core/data_types/hit_record.h"
#include "hitables/hitable_list.h"
#include "hitables/rect.h"

bool Box::hit(
    const Ray&  r,
    const float t_min,
    const float t_max,
    HitRecord&  rec) const
{
    return m_list_ptr_->hit(r, t_min, t_max, rec);
}

bool Box::bounding_box(float t0, float t1, AABB& box) const
{
    box = AABB(m_pmin_, m_pmax_);
    return true;
}

Box::Box(const Vec3& p0, const Vec3& p1, IMaterial* ptr)
  : m_pmin_(p0)
  , m_pmax_(p1)
{
    auto** list = new IHitable*[6];
    list[0] = new XYRect(p0.x(), p1.x(), p0.y(), p1.y(), p1.z(), ptr);
    list[1] = new FlipNormals(
        new XYRect(p0.x(), p1.x(), p0.y(), p1.y(), p0.z(), ptr));
    list[2] = new XZRect(p0.x(), p1.x(), p0.z(), p1.z(), p1.y(), ptr);
    list[3] = new FlipNormals(
        new XZRect(p0.x(), p1.x(), p0.z(), p1.z(), p0.y(), ptr));
    list[4] = new YZRect(p0.y(), p1.y(), p0.z(), p1.z(), p1.x(), ptr);
    list[5] = new FlipNormals(
        new YZRect(p0.y(), p1.y(), p0.z(), p1.z(), p0.x(), ptr));
    m_list_ptr_ = new HitableList(list, 6);
}
