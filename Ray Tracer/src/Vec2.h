#pragma once

#include <cmath>

#include "CustomExcept.h"

template <typename T>
class Vec2
{
public:
    Vec2() = default;
    Vec2( T val )
        : Vec2( val, val )
    {}
    Vec2( T x, T y )
        : x( x ),
          y( y )
    {}
    Vec2( const Vec2& vec )
        : x( vec.x ),
          y( vec.y )
    {}

    template <typename T2>
    explicit operator Vec2<T2>() const
    {
        return {
            static_cast<T2>( x ), static_cast<T2>( y )
        };
    }

    float lengthSq() const
    {
        return x * x + y * y;
    }

    float length() const
    {
        return std::sqrt( lengthSq() );
    }

    void normalize()
    {
        *this /= length();
    }

    Vec2 getNormalized() const
    {
        Vec2 vec = *this;
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
            default:
                throw EXCEPT( "Bad Vec2 access" );
        }
    }

    Vec2 operator-() const
    {
        return { -x, -y };
    }

    Vec2& operator=( const Vec2& rhs )
    {
        x = rhs.x;
        y = rhs.y;
        return *this;
    }

    Vec2& operator+=( const Vec2& rhs )
    {
        x += rhs.x;
        y += rhs.y;
        return *this;
    }

    Vec2& operator-=( const Vec2& rhs )
    {
        x -= rhs.x;
        y -= rhs.y;
        return *this;
    }

    Vec2& operator*=( const Vec2& rhs )
    {
        x *= rhs.x;
        y *= rhs.y;
        return *this;
    }

    Vec2& operator*=( const T& alpha )
    {
        x *= alpha;
        y *= alpha;
        return *this;
    }

    Vec2& operator/=( const Vec2& rhs )
    {
        x /= rhs.x;
        y /= rhs.y;
        return *this;
    }

    Vec2& operator/=( const T& alpha )
    {
        x /= alpha;
        y /= alpha;
        return *this;
    }

    friend Vec2 operator+( const Vec2& lhs, const Vec2& rhs )
    {
        return Vec2( lhs ) += rhs;
    }

    friend Vec2 operator-( const Vec2& lhs, const Vec2& rhs )
    {
        return Vec2( lhs ) -= rhs;
    }

    // hadamard (not dot!) product, matches operator in glsl
    friend Vec2 operator*( const Vec2& lhs, const Vec2& rhs )
    {
        return Vec2( lhs ) *= rhs;
    }

    friend Vec2 operator*( const T& alpha, const Vec2& vec )
    {
        return Vec2( vec ) *= alpha;
    }

    friend Vec2 operator*( const Vec2& vec, const T& alpha )
    {
        return Vec2( vec ) *= alpha;
    }

    friend Vec2 operator/( const Vec2& lhs, const Vec2& rhs )
    {
        return Vec2( lhs ) /= rhs;
    }

    friend Vec2 operator/( const Vec2& vec, const T& alpha )
    {
        return Vec2( vec ) /= alpha;
    }

    friend bool operator==( const Vec2& lhs, const Vec2& rhs )
    {
        return lhs.x == rhs.x && lhs.y == rhs.y;
    }

    friend bool operator!=( const Vec2& lhs, const Vec2& rhs )
    {
        return !( lhs == rhs );
    }

    friend T dot( const Vec2& lhs, const Vec2& rhs )
    {
        return lhs.x * rhs.x + lhs.y * rhs.y;
    }

public:
    T x{};
    T y{};
};

using vec2 = Vec2<float>;
using vei2 = Vec2<int>;
using ved2 = Vec2<double>;
