#pragma once


inline bool refract(
    const vec3& v,
    const vec3& n,
    const float ni_over_nt,
    vec3& refracted)
{
    const vec3 uv = unit_vector(v);
    const float dt = dot(uv, n);
    const float discriminant = 1.f - ni_over_nt * ni_over_nt * (1 - dt * dt);
    if (discriminant > 0)
    {
        refracted = ni_over_nt * (uv - n * dt) - n * std::sqrt(discriminant);
        return true;
    }
    return false;
}

inline vec3 reflect(const vec3& v, const vec3& n)
{
    return v - 2 * dot(v, n) * n;
}

inline float schlick(const float cosine, const float ref_idx)
{
    float r0 = (1 - ref_idx) / (1 + ref_idx);
    r0 = r0 * r0;
    return static_cast<float>(r0 + (1 - r0) * pow((1 - cosine), 5));
}


