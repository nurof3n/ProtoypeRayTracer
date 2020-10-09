#include "Material.h"

vec3 Material::getDiffuse() const noexcept
{
    return diffuse;
}

vec3 Material::getSpecular() const noexcept
{
    return specular;
}

float Material::getSpecularPower() const noexcept
{
    return specularPower;
}

vec3 Material::getEmission() const noexcept
{
    return emission;
}

vec3 Material::getAmbient() const noexcept
{
    return ambient;
}

void Material::setDiffuse( const vec3& diffuse ) 
{
    this->diffuse = diffuse;
}

void Material::setSpecular( const vec3& specular )
{
    this->specular = specular;
}

void Material::setSpecularPower( float specularPower )
{
    this->specularPower = specularPower;
}

void Material::setEmission( const vec3& emission )
{
    this->emission = emission;
}

void Material::setAmbient( const vec3& ambient )
{
    this->ambient = ambient;
}
