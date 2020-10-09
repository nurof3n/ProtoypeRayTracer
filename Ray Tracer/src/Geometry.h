#pragma once

#include <algorithm>
#include <optional>

#include "Mat4.h"
#include "Material.h"
#include "Ray.h"
#include "Vec3.h"

class Geometry
{
public:
    Geometry() = default;
    Geometry( const Material& material )
        : material( material )
    {}
    Geometry( Material&& material )
        : material( std::move( material ) )
    {}
    virtual ~Geometry() = default;
    // returns an optional pair: the distance between the ray origin
    // and intersection point, and the normal at that point on the surface
    virtual std::optional<std::pair<float, vec3>> intersect( const Ray& ray ) const = 0;
    // translates the object with the offset translation
    virtual void move( const vec3& offset ) = 0;

    Material     getMaterial() const noexcept;
    mat4         getTransformMatrix() const noexcept;
    mat4         getInverseTransformMatrix() const noexcept;
    void         setMaterial( const Material& material );
    void         setTransformMatrix( const mat4& transform );
    void         setInverseTransformMatrix( const mat4& transform );
    virtual void applyTransform() = 0;

private:
    Material material;
    mat4     transformMatrix        = mat4::identity();
    mat4     inverseTransformMatrix = mat4::identity();
};