#include "aabb.h"

bool aabb::hit(const ray& r, float tmin, float tmax) const {
    for (int a = 0; a < 3; a++) {
        float inv_d = 1.f / r.direction()[a];
        float t0 = (_min[a] - r.origin()[a]) * inv_d;
        float t1 = (_max[a] - r.origin()[a]) * inv_d;
        if (inv_d < 0.f)
        {
            std::swap(t0, t1);
        }
        tmin = (t0 > tmin) ? t0 : tmin;
        tmax = (t1 < tmax) ? t1 : tmax;
//        float t0 = ffmin((_min[a] - r.origin()[a]) / r.direction()[a],
//                         (_max[a] - r.origin()[a]) / r.direction()[a]);
//        float t1 = ffmax((_min[a] - r.origin()[a]) / r.direction()[a],
//                         (_max[a] - r.origin()[a]) / r.direction()[a]);
//        tmin = ffmax(t0, tmin);
//        tmax = ffmin(t1, tmax);
        if (tmax <= tmin)
            return false;
    }
    return true;
}