#pragma once

#include <vector>

#include "Geometry.h"
#include "NuroMath.h"

class Mesh : public Geometry
{
public:
    Mesh() = default;
    Mesh( const std::vector<vec3>& vertices, const std::vector<vei3>& triangles, const Material& M = {} )
        : Geometry( M ),
          vertices( vertices ),
          triangles( triangles )
    {}
    Mesh( std::vector<vec3>&& vertices, std::vector<vei3>&& triangles, Material&& M = {} )
        : Geometry( std::move( M ) ),
          vertices( std::move( vertices ) ),
          triangles( std::move( triangles ) )
    {}
    ~Mesh() = default;

    std::optional<std::pair<float, vec3>> intersect( const Ray& ray ) const override;
    std::optional<std::pair<float, vec3>> intersectTriangle( const Ray& ray, const vei3& triangle ) const;

    void move( const vec3& offset );

    void reserveVerticesNumber( const size_t n );
    void putVertex( size_t index, const vec3& vertex );
    void pushVertex( const vec3& vertex );
    void pushTriangle( const vei3& triangle );
    void applyTransform() override;

private:
    std::vector<vec3> vertices;
    std::vector<vei3> triangles;
};
