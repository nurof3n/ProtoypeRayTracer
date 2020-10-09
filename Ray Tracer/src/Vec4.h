#pragma once

#include "Vec3.h"

template <typename T>
class Vec4
{
public:
    Vec4() = default;
    Vec4( T val )
        : Vec4( val, val, val, val )
    {}
    Vec4( T x, T y, T z, T w )
        : x( x ),
          y( y ),
          z( z ),
          w( w )
    {}
    Vec4( Vec3<T> vec, T w = {} )
        : x( vec.x ),
          y( vec.y ),
          z( vec.z ),
          w( w )
    {}

    template <typename T2>
    explicit operator Vec4<T2>() const
    {
        return {
            static_cast<T2>( x ), static_cast<T2>( y ), static_cast<T2>( z ), static_cast<T2>( w )
        };
    }

    float lengthSq() const
    {
        return x * x + y * y + z * z + w * w;
    }

    float length() const
    {
        return std::sqrt( lengthSq() );
    }

    void normalize()
    {
        *this /= length();
    }

    Vec4 getNormalized() const
    {
        Vec4<T> vec = *this;
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
            case 3:
                return w;
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
            case 3:
                return w;
            default:
                throw EXCEPT( "Bad Vec2 access" );
        }
    }

    Vec4 operator-() const
    {
        return { -x, -y, -z, -w };
    }

    Vec4& operator=( const Vec4& rhs )
    {
        x = rhs.x;
        y = rhs.y;
        z = rhs.z;
        w = rhs.w;
        return *this;
    }

    Vec4& operator+=( const Vec4& rhs )
    {
        x += rhs.x;
        y += rhs.y;
        z += rhs.z;
        w += rhs.w;
        return *this;
    }

    Vec4& operator-=( const Vec4& rhs )
    {
        x -= rhs.x;
        y -= rhs.y;
        z -= rhs.z;
        w -= rhs.w;
        return *this;
    }

    Vec4& operator*=( const Vec4& rhs )
    {
        x *= rhs.x;
        y *= rhs.y;
        z *= rhs.z;
        w *= rhs.w;
        return *this;
    }

    Vec4& operator*=( const T& alpha )
    {
        x *= alpha;
        y *= alpha;
        z *= alpha;
        w *= alpha;
        return *this;
    }

    Vec4& operator/=( const Vec4& rhs )
    {
        x /= rhs.x;
        y /= rhs.y;
        z /= rhs.z;
        w /= rhs.w;
        return *this;
    }

    Vec4& operator/=( const T& alpha )
    {
        x /= alpha;
        y /= alpha;
        z /= alpha;
        w /= alpha;
        return *this;
    }

    friend Vec4 operator+( const Vec4& lhs, const Vec4& rhs )
    {
        return Vec4( lhs ) += rhs;
    }

    friend Vec4 operator-( const Vec4& lhs, const Vec4& rhs )
    {
        return Vec4( lhs ) -= rhs;
    }

    // hadamard (not dot!) product, matches operator in glsl
    friend Vec4 operator*( const Vec4& lhs, const Vec4& rhs )
    {
        return Vec4( lhs ) *= rhs;
    }

    friend Vec4 operator*( const T& alpha, const Vec4& vec )
    {
        return Vec4( vec ) *= alpha;
    }

    friend Vec4 operator*( const Vec4& vec, const T& alpha )
    {
        return Vec4( vec ) *= alpha;
    }

    friend Vec4 operator/( const Vec4& lhs, const Vec4& rhs )
    {
        return Vec4( lhs ) /= rhs;
    }

    friend Vec4 operator/( const Vec4& vec, const T& alpha )
    {
        return Vec4( vec ) /= alpha;
    }

    friend bool operator==( const Vec4& lhs, const Vec4& rhs )
    {
        return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z && lhs.w == rhs.w;
    }

    friend bool operator!=( const Vec4& lhs, const Vec4& rhs )
    {
        return !( lhs == rhs );
    }

    friend T dot( const Vec4& lhs, const Vec4& rhs )
    {
        return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z + lhs.w * rhs.w;
    }

public:
    T x{};
    T y{};
    T z{};
    T w{};
};

using vec4 = Vec4<float>;
using vei4 = Vec4<int>;
using ved4 = Vec4<double>;
