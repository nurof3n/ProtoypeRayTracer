#pragma once

#include <memory>
#include <vector>

#include "Camera.h"
#include "DirectionalLight.h"
#include "Geometry.h"
#include "Light.h"
#include "NuroMath.h"
#include "Options.h"
#include "PointLight.h"
#include "Ray.h"
#include "Vec3.h"

class Raytracer
{
public:
    // computes the closest ray-object intersection, returning the object index, distance and normal
    std::optional<std::tuple<int, float, vec3>> computeIntersection( const Ray& ray, const std::vector<std::unique_ptr<Geometry>>& objects );
    // computes the illuminance value coming along the ray direction, in normalized rgb
    vec3 computeIlluminance( int depth, const Ray& ray, const vec3& eyePosition, const std::vector<std::unique_ptr<Geometry>>& objects, const std::vector<std::unique_ptr<Light>>& lights );
    // shades the point at the surface accounting for the point light (Blinn-Phong model)
    vec3 phongIlluminationForPointLight( const vec3& point, const vec3& normal, const vec3& eyePosition, const Material& material, const PointLight& pointLight );
    // shades the point at the surface accounting for the directional light (Blinn-Phong model)
    vec3 phongIlluminationForDirectionalLight( const vec3& point, const vec3& normal, const vec3& eyePosition, const Material& material, const DirectionalLight& directionalLight );
    // checks to see if the surface point is visible to the light
    bool isInShadow( const vec3& point, const vec3& normal, const PointLight& pointLight, const std::vector<std::unique_ptr<Geometry>>& objects );
    // checks to see if the surface point is visible to the light
    bool isInShadow( const vec3& point, const vec3& normal, const DirectionalLight& directionalLight, const std::vector<std::unique_ptr<Geometry>>& objects );
};
