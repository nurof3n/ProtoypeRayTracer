#pragma once

#include "Vec2.h"

template <typename T>
class Vec3
{
public:
    Vec3() = default;
    Vec3( const T& val )
        : Vec3( val, val, val )
    {}
    Vec3( const T& x, const T& y, const T& z )
        : x( x ),
          y( y ),
          z( z )
    {}
    Vec3( const Vec2<T>& vec, const T& z = {} )
        : x( vec.x ),
          y( vec.y ),
          z( z )
    {}

    template <typename T2>
    explicit operator Vec3<T2>() const
    {
        return {
            static_cast<T2>( x ), static_cast<T2>( y ), static_cast<T2>( z )
        };
    }

    float lengthSq() const
    {
        return x * x + y * y + z * z;
    }

    float length() const
    {
        return std::sqrt( lengthSq() );
    }

    void normalize()
    {
        *this /= length();
    }

    Vec3 getNormalized() const
    {
        Vec3<T> vec = *this;
        vec.normalize();
        return vec;
    }

    T operator[]( size_t index ) const
    {
        switch( index ) {
            case 0:
                return x;
            case 1:
                return y;
            case 2:
                return z;
            default:
                throw EXCEPT( "Bad Vec2 access" );
        }
    }

    T& operator[]( size_t index )
    {
        switch( index ) {
            case 0:
                return x;
            case 1:
                return y;
            case 2:
                return z;
            default:
                throw EXCEPT( "Bad Vec2 access" );
        }
    }

    Vec3 operator-() const
    {
        return { -x, -y, -z };
    }

    Vec3& operator=( const Vec3& rhs )
    {
        x = rhs.x;
        y = rhs.y;
        z = rhs.z;
        return *this;
    }

    Vec3& operator+=( const Vec3& rhs )
    {
        x += rhs.x;
        y += rhs.y;
        z += rhs.z;
        return *this;
    }

    Vec3& operator-=( const Vec3& rhs )
    {
        x -= rhs.x;
        y -= rhs.y;
        z -= rhs.z;
        return *this;
    }

    Vec3& operator*=( const Vec3& rhs )
    {
        x *= rhs.x;
        y *= rhs.y;
        z *= rhs.z;
        return *this;
    }

    Vec3& operator*=( const T& alpha )
    {
        x *= alpha;
        y *= alpha;
        z *= alpha;
        return *this;
    }

    Vec3& operator/=( const Vec3& rhs )
    {
        x /= rhs.x;
        y /= rhs.y;
        z /= rhs.z;
        return *this;
    }

    Vec3& operator/=( const T& alpha )
    {
        x /= alpha;
        y /= alpha;
        z /= alpha;
        return *this;
    }

    friend Vec3 operator+( const Vec3& lhs, const Vec3& rhs )
    {
        return Vec3( lhs ) += rhs;
    }

    friend Vec3 operator-( const Vec3& lhs, const Vec3& rhs )
    {
        return Vec3( lhs ) -= rhs;
    }

    // hadamard (not dot!) product, matches operator in glsl
    friend Vec3 operator*( const Vec3& lhs, const Vec3& rhs )
    {
        return Vec3( lhs ) *= rhs;
    }

    friend Vec3 operator*( const T& alpha, const Vec3& vec )
    {
        return Vec3( vec ) *= alpha;
    }

    friend Vec3 operator*( const Vec3& vec, const T& alpha )
    {
        return Vec3( vec ) *= alpha;
    }

    friend Vec3 operator/( const Vec3& lhs, const Vec3& rhs )
    {
        return Vec3( lhs ) /= rhs;
    }

    friend Vec3 operator/( const Vec3& vec, const T& alpha )
    {
        return Vec3( vec ) /= alpha;
    }

    friend bool operator==( const Vec3& lhs, const Vec3& rhs )
    {
        return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z;
    }

    friend bool operator!=( const Vec3& lhs, const Vec3& rhs )
    {
        return !( lhs == rhs );
    }

    friend T dot( const Vec3& lhs, const Vec3& rhs )
    {
        return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
    }

    friend Vec3 cross( const Vec3& lhs, const Vec3& rhs )
    {
        return {
            lhs.y * rhs.z - lhs.z * rhs.y,
            lhs.z * rhs.x - lhs.x * rhs.z,
            lhs.x * rhs.y - lhs.y * rhs.x
        };
    }

public:
    T x{};
    T y{};
    T z{};
};

using vec3  = Vec3<float>;
using vei3  = Vec3<int>;
using ved3  = Vec3<double>;
using Color = Vec3<unsigned char>;
