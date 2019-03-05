#pragma once


#include "core/bases/material.h"
#include "core/bases/texture.h"
#include "core/data_types/vec3.h"
#include "core/data_types/hit_record.h"

class diffuse_light
    : public material
{
public:
    explicit
    diffuse_light(texture* a)
        : emit(a) {};

    virtual ~diffuse_light() override = default;;

    virtual bool
    scatter(
        const ray& r_in,
        const hit_record& rec,
        vec3& attenuation,
        ray& scattered) const override { return false; };

    virtual vec3
    emitted(
        float u,
        float v,
        const vec3& p) const override { return emit->value(u, v, p); }

    texture* emit;
};
