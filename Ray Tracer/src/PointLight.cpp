#include "PointLight.h"

void PointLight::move( const vec3& offset )
{
    position += offset;
}

Lights PointLight::getType() const noexcept
{
    return Lights::POINT;
}

float PointLight::computeAttenuation( float distance ) const
{
    return 1.0f / ( attenuation_quadratic * distance * distance + attenuation_linear * distance + attenuation_constant );
}
