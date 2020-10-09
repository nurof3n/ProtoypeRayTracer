#include "Geometry.h"

Material Geometry::getMaterial() const noexcept
{
    return material;
}

mat4 Geometry::getTransformMatrix() const noexcept
{
    return transformMatrix;
}

mat4 Geometry::getInverseTransformMatrix() const noexcept
{
    return inverseTransformMatrix;
}

void Geometry::setMaterial( const Material& material )
{
    this->material = material;
}

void Geometry::setTransformMatrix( const mat4& transform )
{
    this->transformMatrix = transform;
}

void Geometry::setInverseTransformMatrix( const mat4& transform )
{
    this->inverseTransformMatrix = transform;
}
