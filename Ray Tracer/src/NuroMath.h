#pragma once

#include <algorithm>
#include <cmath>
#include <optional>

#include "Mat4.h"
#include "Ray.h"
#include "Vec2.h"
#include "Vec3.h"
#include "Vec4.h"

#undef max
#undef min

class NuroMath
{
public:
    static float radians( float degrees )
    {
        return degrees / 180.0f * PI;
    }
    static float degrees( float radians )
    {
        return radians / PI * 180.0f;
    }

    template <typename T>
    static void clamp( T& value, T min, T max )
    {
        value = std::max( std::min( max, value ), min );
    }
    template <typename T>
    static void clamp( Vec2<T>& value, T min, T max )
    {
        value.x = std::max( std::min( max, value.x ), min );
        value.y = std::max( std::min( max, value.y ), min );
    }
    template <typename T>
    static void clamp( Vec3<T>& value, T min, T max )
    {
        value.x = std::max( std::min( max, value.x ), min );
        value.y = std::max( std::min( max, value.y ), min );
        value.z = std::max( std::min( max, value.z ), min );
    }
    template <typename T>
    static Color denormalizeRgb( Vec3<T> illuminance )
    {
        vei3 rgb = static_cast<vei3>( illuminance * 255.0f );
        clamp( rgb, 0, 255 );
        return static_cast<Color>( rgb );
    }
    static vec3 normalizeRgb( Color color )
    {
        return static_cast<vec3>( color ) / 255.0f;
    }
    // returns the solution as an ordered pair (x1 < x2), or std::nullopt if there are no real solutions
    static std::optional<std::pair<float, float>> solveQuadratic( float a, float b, float c )
    {
        float d = b * b - 4.0f * a * c;
        if( d < 0.0f )
            return std::nullopt;
        float x1, x2;
        if( d == 0.0f ) {
            x1 = x2 = -0.5f / a * b;
            return std::make_pair( x1, x2 );
        }
        d  = std::sqrt( d );
        x1 = -0.5f / a * ( b - d );
        x2 = -0.5f / a * ( b + d );
        if( x1 > x2 )
            std::swap( x1, x2 );
        return std::make_pair( x1, x2 );
    }
    template <typename T>
    static float computeArea( const Vec3<T>& v0, const Vec3<T>& v1, const Vec3<T>& v2 )
    {
        return std::abs( 0.5 * cross( v1 - v0, v2 - v0 ).length() );
    }
    // normal should be normalized
    static vec3 reflect( const vec3& direction, const vec3& normal )
    {
        return direction - 2.0f * dot( direction, normal ) * normal;
    }
    template <typename T>
    static Vec4<T> homogenize( const Vec3<T>& vertex )
    {
        return { vertex, 1.0f };
    }
    template <typename T>
    static Vec3<T> dehomogenize( const Vec4<T>& vertex )
    {
        if( vertex.w == 0.0f )
            throw EXCEPT( "Cannot dehomogenize a direction vector" );
        return Vec3<T>{ vertex.x, vertex.y, vertex.z } / vertex.w;
    }
    template <typename T>
    static Vec3<T> transformPoint( const Vec3<T>& point, const Mat4<T>& transform )
    {
        return NuroMath::dehomogenize( transform * NuroMath::homogenize( point ) );
    }
    template <typename T>
    static Vec3<T> transformDirection( const Vec3<T>& direction, const Mat4<T>& transform )
    {
        Vec4<T> result = transform * vec4{ direction, 0.0f };
        return Vec3<T>{ result.x, result.y, result.z }.getNormalized();
    }
    template <typename T>
    static Ray transformRay( const Ray& ray, const Mat4<T>& transform )
    {
        Ray transformedRay;
        transformedRay.origin    = NuroMath::transformPoint( ray.origin, transform );
        transformedRay.direction = NuroMath::transformDirection( ray.direction, transform );
        return transformedRay;
    }
    template <typename T>
    static Mat4<T> transpose( const Mat4<T>& m )
    {
        return {
            m( 0, 0 ), m( 1, 0 ), m( 2, 0 ), m( 3, 0 ),
            m( 0, 1 ), m( 1, 1 ), m( 2, 1 ), m( 3, 1 ),
            m( 0, 2 ), m( 1, 2 ), m( 2, 2 ), m( 3, 2 ),
            m( 0, 3 ), m( 1, 3 ), m( 2, 3 ), m( 3, 3 )
        };
    }

public:
    static constexpr float PI = 3.141592f;

private:
    static constexpr float EPS = 1e-6f;
};
