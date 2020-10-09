#pragma once

#include "Vec3.h"
#include "Vec4.h"

template <typename T>
class Mat4
{
public:
    Mat4() = default;
    Mat4( const T& value )
    {
        a[0][0] = a[1][1] = a[2][2] = a[3][3] = value;
    }
    Mat4( T const& x0, T const& y0, T const& z0, T const& w0, T const& x1, T const& y1, T const& z1, T const& w1, T const& x2, T const& y2,
          T const& z2, T const& w2, T const& x3, T const& y3, T const& z3, T const& w3 )
        : Mat4( { x0, y0, z0, w0 }, { x1, y1, z1, w1 }, { x2, y2, z2, w2 }, { x3, y3, z3, w3 } )
    {}
    Mat4( const Vec4<T>& v0, const Vec4<T>& v1, const Vec4<T>& v2, const Vec4<T>& v3 )
    {
        a[0][0] = v0.x, a[0][1] = v0.y, a[0][2] = v0.z, a[0][3] = v0.w;
        a[1][0] = v1.x, a[1][1] = v1.y, a[1][2] = v1.z, a[1][3] = v1.w;
        a[2][0] = v2.x, a[2][1] = v2.y, a[2][2] = v2.z, a[2][3] = v2.w;
        a[3][0] = v3.x, a[3][1] = v3.y, a[3][2] = v3.z, a[3][3] = v3.w;
    }

    static constexpr Mat4 identity()
    {
        return Mat4( static_cast<T>( 1 ) );
    }
    static Mat4 translationMatrix( const Vec3<T>& translation )
    {
        return { 1.0f, 0.0f, 0.0f, translation.x, 0.0f, 1.0f, 0.0f, translation.y, 0.0f, 0.0f, 1.0f, translation.z, 0.0f, 0.0f, 0.0f, 1.0f };
    }
    static Mat4 scaleMatrix( const Vec3<T>& scale )
    {
        return { scale.x, 0.0f, 0.0f, 0.0f, 0.0f, scale.y, 0.0f, 0.0f, 0.0f, 0.0f, scale.z, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f };
    }
    // angle is in degrees
    static Mat4 rotationMatrix( const Vec3<T>& axis, float angle )
    {
        Vec3<T> axisNorm = axis.getNormalized();
        float   radians  = angle / 180.0f * 3.1415f;
        float   cos      = std::cos( radians );
        float   sin      = std::sin( radians );

        Mat4 rotation = scaleMatrix( Vec3<T>{ cos } )
                        + ( 1.0f - cos ) * Mat4( axisNorm.x * axisNorm.x, axisNorm.x * axisNorm.y, axisNorm.x * axisNorm.z, 0.0f, 
                                                 axisNorm.x * axisNorm.y, axisNorm.y * axisNorm.y, axisNorm.y * axisNorm.z, 0.0f, 
                                                 axisNorm.x * axisNorm.z, axisNorm.y * axisNorm.z, axisNorm.z * axisNorm.z, 0.0f,
                                                 0.0f, 0.0f, 0.0f, 0.0f )
                        + sin * Mat4( 0.0f, -axisNorm.z, axisNorm.y, 0.0f, 
                                      axisNorm.z, 0.0f, -axisNorm.x, 0.0f, 
                                      -axisNorm.y, axisNorm.x, 0.0f, 0.0f, 
                                      0.0f, 0.0f, 0.0f, 0.0f );
        return rotation;
    }

    T operator()( size_t row, size_t column ) const
    {
        return a[row][column];
    }

    T& operator()( size_t row, size_t column )
    {
        return a[row][column];
    }

    Mat4& operator=( const Mat4& rhs )
    {
        for( size_t i = 0; i < 4; ++i )
            for( size_t j = 0; j < 4; ++j )
                a[i][j] = rhs.a[i][j];
        return *this;
    }

    Mat4 operator-() const
    {
        Mat4 result;
        for( size_t i = 0; i < 4; ++i )
            for( size_t j = 0; j < 4; ++j )
                result.a[i][j] = -a[i][j];
        return result;
    }

    Mat4& operator+=( const Mat4& rhs )
    {
        for( size_t i = 0; i < 4; ++i )
            for( size_t j = 0; j < 4; ++j )
                a[i][j] += rhs.a[i][j];
        return *this;
    }

    Mat4& operator-=( const Mat4& rhs )
    {
        for( size_t i = 0; i < 4; ++i )
            for( size_t j = 0; j < 4; ++j )
                a[i][j] -= rhs.a[i][j];
        return *this;
    }

    Mat4& operator*=( const Mat4& rhs )
    {
        Mat4 result;
        for( size_t i = 0; i < 4; ++i )
            for( size_t j = 0; j < 4; ++j )
                for( size_t k = 0; k < 4; ++k )
                    result.a[i][j] += a[i][k] * rhs.a[k][j];
        return *this = result;
    }

    Mat4& operator*=( const T& alpha )
    {
        for( size_t i = 0; i < 4; ++i )
            for( size_t j = 0; j < 4; ++j )
                a[i][j] *= alpha;
        return *this;
    }

    friend Mat4 operator+( const Mat4& lhs, const Mat4& rhs )
    {
        return Mat4( lhs ) += rhs;
    }

    friend Mat4 operator-( const Mat4& lhs, const Mat4& rhs )
    {
        return Mat4( lhs ) -= rhs;
    }

    friend Mat4 operator*( const Mat4& lhs, const Mat4& rhs )
    {
        return Mat4( lhs ) *= rhs;
    }

    friend Mat4 operator*( const Mat4& lhs, const T& alpha )
    {
        return Mat4( lhs ) *= alpha;
    }

    friend Mat4<T> operator*( const T& alpha, const Mat4<T>& rhs )
    {
        return Mat4( rhs ) *= alpha;
    }

    friend Vec4<T> operator*( const Mat4<T>& lhs, const Vec4<T>& rhs )
    {
        Vec4<T> result;
        for( size_t i = 0; i < 4; ++i )
            for( size_t j = 0; j < 4; ++j )
                result[i] += lhs( i, j ) * rhs[j];
        return result;
    }

    friend Vec4<T> operator*( const Vec4<T>& lhs, const Mat4<T>& rhs )
    {
        Vec4<T> result;
        for( size_t i = 0; i < 4; ++i )
            for( size_t j = 0; j < 4; ++j )
                result[i] += lhs[j] * rhs.a[j][i];
        return result;
    }

    friend bool operator!=( const Mat4& lhs, const Mat4& rhs )
    {
        for( size_t i = 0; i < 4; ++i )
            for( size_t j = 0; j < 4; ++j )
                if( lhs.a[i][j] != rhs.a[i][j] )
                    return true;
        return false;
    }

    friend bool operator==( const Mat4& lhs, const Mat4& rhs )
    {
        return !( lhs != rhs );
    }

private:
    T a[4][4]{};
};

using mat4 = Mat4<float>;
using mad4 = Mat4<double>;
using mai4 = Mat4<int>;
