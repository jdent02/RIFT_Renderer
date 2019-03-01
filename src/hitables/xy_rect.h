#ifndef FARTS_RENDERER_XY_RECT_H
#define FARTS_RENDERER_XY_RECT_H

#include "hitable.h"

class xy_rect
    :public hitable
{
  public:
    xy_rect() = default;
    xy_rect(
        float _x0,
        float _x1,
        float _y0,
        float _y1,
        float _k,
        material* mat);

    virtual bool hit(
        const ray& r,
        float t_min,
        float t_max,
        hit_record& rec) const override;

    virtual bool bounding_box(
        float t0,
        float t1,
        aabb& box) const override;

    material* mp;
    float x0, x1, y0, y1, k;

};


#endif //FARTS_RENDERER_XY_RECT_H
