#pragma once

#include "Vec3.h"

enum class Lights
{
    POINT,
    DIRECTIONAL
};

class Light
{
public:
    virtual ~Light()         = default;
    virtual Lights getType() const noexcept = 0;
};
