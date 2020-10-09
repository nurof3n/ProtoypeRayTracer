#include "Sphere.h"

std::optional<std::pair<float, vec3>> Sphere::intersect( const Ray& ray ) const
{
    Ray transformedRay = NuroMath::transformRay( ray, getInverseTransformMatrix() );

    float a      = 1.0f;
    float b      = 2.0f * dot( transformedRay.direction, transformedRay.origin - center );
    float c      = ( transformedRay.origin - center ).lengthSq() - radius * radius;
    auto  result = NuroMath::solveQuadratic( a, b, c );
    if( !result ) {
        return std::nullopt;
    }

    float distance{};
    auto  pair = result.value();
    if( pair.first < 0.0f ) {
        if( pair.second < 0.0f )
            return std::nullopt;
        distance = pair.second;
    }
    else {
        distance = pair.first;
    }
    vec3 point  = transformedRay.origin + distance * transformedRay.direction;
    vec3 normal = ( point - center ).getNormalized();
    point       = NuroMath::transformPoint( point, getTransformMatrix() );
    distance    = ( point - ray.origin ).length();
    normal      = NuroMath::transformDirection( normal, NuroMath::transpose( getInverseTransformMatrix() ) );
    return std::make_pair( distance, normal );
}

void Sphere::move( const vec3& offset )
{
    center += offset;
}

float Sphere::getRadius() const noexcept
{
    return radius;
}

vec3 Sphere::getCenter() const noexcept
{
    return center;
}

void Sphere::setRadius( float radius ) noexcept
{
    this->radius = radius;
}

void Sphere::setCenter( const vec3& center ) noexcept
{
    this->center = center;
}

void Sphere::applyTransform()
{
    center = NuroMath::transformPoint( center, getTransformMatrix() );
}
