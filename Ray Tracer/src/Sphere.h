#pragma once

#include "Geometry.h"
#include "NuroMath.h"
#include "Vec4.h"

class Sphere : public Geometry
{
public:
    Sphere() = default;
    Sphere( const vec3& center, float radius, const Material& M = {} )
        : Geometry( M ),
          center( center ),
          radius( radius )
    {}
    ~Sphere() = default;
    std::optional<std::pair<float, vec3>> intersect( const Ray& ray ) const override;

    void move( const vec3& offset );

    float getRadius() const noexcept;
    vec3  getCenter() const noexcept;
    void  setRadius( float radius ) noexcept;
    void  setCenter( const vec3& center ) noexcept;

    void applyTransform() override;

private:
    vec3  center{ 0.0f };
    float radius{ 0.0f };
};
