#pragma once

#include "Light.h"

class PointLight : public Light
{
public:
    PointLight( const vec3& position, const vec3& intensity, float c = 1.0f, float l = 0.0f, float q = 1.0f )
        : position( position ),
          intensity( intensity ),
          attenuation_quadratic( q ),
          attenuation_linear( l ),
          attenuation_constant( c )
    {}
    ~PointLight() = default;

    void   move( const vec3& offset );
    Lights getType() const noexcept;
    float  computeAttenuation( float distance ) const;

public:
    vec3 position;
    vec3 intensity{ 1.0f };

private:
    float attenuation_quadratic{ 1.0f };
    float attenuation_linear{ 0.0f };
    float attenuation_constant{ 1.0f };
};
