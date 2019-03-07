#include "aabb.h"

bool aabb::hit(
    const ray&  r, 
    float       tmin, 
    float       tmax) const
{
    for (int a = 0; a < 3; a++)
    {
        const float inv_d = 1.f / r.direction()[a];

        float t0 = (_min[a] - r.origin()[a]) * inv_d;
        float t1 = (_max[a] - r.origin()[a]) * inv_d;
        if (inv_d < 0.f)
        {
            std::swap(t0, t1);
        }
        tmin = (t0 > tmin) ? t0 : tmin;
        tmax = (t1 < tmax) ? t1 : tmax;
        if (tmax <= tmin)
        {
            return false;
        }
    }
    return true;
}
