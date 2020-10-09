#include "Mesh.h"

std::optional<std::pair<float, vec3>> Mesh::intersect( const Ray& ray ) const
{
    float                  minDistance = 1000.0f;
    std::pair<float, vec3> closestPair( -1.0f, {} );
    Ray                    transformedRay = NuroMath::transformRay( ray, getInverseTransformMatrix() );
    for( const auto& triangle : triangles ) {
        auto result = intersectTriangle( transformedRay, triangle );
        if( !result )
            continue;

        auto pair              = result.value();
        vec3 intersectionPoint = transformedRay.origin + pair.first * transformedRay.direction;
        intersectionPoint      = NuroMath::transformPoint( intersectionPoint, getTransformMatrix() );
        pair.first             = ( intersectionPoint - ray.origin ).length();
        pair.second            = NuroMath::transformDirection( pair.second, NuroMath::transpose( getInverseTransformMatrix() ) );
        if( pair.first < minDistance ) {
            minDistance = pair.first;
            closestPair = pair;
        }
    }

    if( minDistance == 1000.0f )
        return std::nullopt;
    return closestPair;
}

std::optional<std::pair<float, vec3>> Mesh::intersectTriangle( const Ray& ray, const vei3& triangle ) const
{
    const auto& v0     = vertices[triangle.x];
    const auto& v1     = vertices[triangle.y];
    const auto& v2     = vertices[triangle.z];
    vec3        normal = 0.5f * cross( v1 - v0, v2 - v0 );
    float       area   = normal.length();
    normal.normalize();
    float cosine = dot( normal, ray.direction );
    if( std::abs( cosine ) < 1e-6f )  // ray is parallel to the triangle's plane
        return std::nullopt;
    if( cosine > 0.0f )  // backface culling
        return std::nullopt;

    float distance = dot( normal, v0 - ray.origin ) / cosine;
    if( distance < 0.0f )  // triangle is behind ray
        return std::nullopt;

    vec3  point   = ray.origin + distance * ray.direction;
    float areaSum = NuroMath::computeArea( point, v0, v1 ) + NuroMath::computeArea( point, v0, v2 ) + NuroMath::computeArea( point, v1, v2 );
    if( std::abs( areaSum - area ) >= 1e-6f )  // the point is not inside the triangle
        return std::nullopt;

    return std::pair<float, vec3>( distance, normal );
}

void Mesh::move( const vec3& offset )
{
    for( auto& vertex : vertices ) {
        vertex += offset;
    }
}

void Mesh::reserveVerticesNumber( const size_t n )
{
    vertices.reserve( n );
}

void Mesh::putVertex( size_t index, const vec3& vertex )
{
    vertices[index] = vertex;
}

void Mesh::pushVertex( const vec3& vertex )
{
    vertices.push_back( vertex );
}

void Mesh::pushTriangle( const vei3& triangle )
{
    triangles.push_back( triangle );
}

void Mesh::applyTransform()
{
    const mat4& transform = getTransformMatrix();
    for( auto& vertex : vertices ) {
        vertex = NuroMath::transformPoint( vertex, transform );
    }
}
