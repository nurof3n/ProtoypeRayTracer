#pragma once

#include "Light.h"

class DirectionalLight : public Light
{
public:
    DirectionalLight( const vec3& direction, const vec3& intensity )
        : direction( direction.getNormalized() ),
          intensity( intensity )
    {}
    ~DirectionalLight() = default;
    Lights getType() const noexcept;

public:
    vec3 direction;
    vec3 intensity{ 0.2f };
};
