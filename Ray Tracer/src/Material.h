#pragma once

#include "Vec3.h"

class Material
{
public:
    Material() = default;
    Material( const vec3& diffuse, const vec3& specular, float specularPower, const vec3& ambient = {}, const vec3& emission = {} )
        : diffuse( diffuse ),
          specular( specular ),
          specularPower( specularPower ),
          emission( emission ),
          ambient( ambient )
    {}

    vec3  getDiffuse() const noexcept;
    vec3  getSpecular() const noexcept;
    float getSpecularPower() const noexcept;
    vec3  getEmission() const noexcept;
    vec3  getAmbient() const noexcept;
    void  setDiffuse( const vec3& diffuse );
    void  setSpecular( const vec3& specular );
    void  setSpecularPower( float specularPower );
    void  setEmission( const vec3& emission );
    void  setAmbient( const vec3& ambient );

private:
    vec3  diffuse{ 1.0f };
    vec3  specular{ 1.0f };
    float specularPower{ 25.0f };
    vec3  emission;
    vec3  ambient;
};
