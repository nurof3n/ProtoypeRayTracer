#include "Raytracer.h"

std::optional<std::tuple<int, float, vec3>> Raytracer::computeIntersection( const Ray& ray, const std::vector<std::unique_ptr<Geometry>>& objects )
{
    float minDistance = 1000.0f;
    int   ind         = -1;

    std::pair<float, vec3> closestPair( -1.0f, {} );
    for( size_t i = 0; i < objects.size(); ++i ) {
        auto result = objects[i]->intersect( ray );
        if( !result )
            continue;
        else {
            const auto& pair = result.value();
            if( pair.first < minDistance ) {
                minDistance = pair.first;
                ind         = i;
                closestPair = pair;
            }
        }
    }

    if( ind == -1 )
        return std::nullopt;
    return std::tuple<size_t, float, vec3>( ind, closestPair.first, closestPair.second );
}

vec3 Raytracer::computeIlluminance( int depth, const Ray& ray, const vec3& eyePosition, const std::vector<std::unique_ptr<Geometry>>& objects, const std::vector<std::unique_ptr<Light>>& lights )
{
    if( depth > Options::RAY_RECURSION_MAX_DEPTH )
        return {};

    auto result = computeIntersection( ray, objects );
    if( !result )
        return {};

    auto  tuple    = result.value();
    int   index    = std::get<0>( tuple );
    float distance = std::get<1>( tuple );
    vec3  normal   = std::get<2>( tuple );

    const Material& material    = objects[index]->getMaterial();
    vec3            illuminance = material.getAmbient() + material.getEmission();

    vec3 intersectionPoint = ray.origin + distance * ray.direction;
    for( const auto& light : lights ) {
        switch( light->getType() ) {
            case Lights::POINT: {
                auto pointLight = *static_cast<PointLight*>( light.get() );
                if( !isInShadow( intersectionPoint, normal, pointLight, objects ) ) {
                    illuminance += phongIlluminationForPointLight( intersectionPoint, normal, eyePosition,
                                                                   material, pointLight );
                }
                break;
            }
            case Lights::DIRECTIONAL: {
                auto directionalLight = *static_cast<DirectionalLight*>( light.get() );
                if( !isInShadow( intersectionPoint, normal, directionalLight, objects ) ) {
                    illuminance += phongIlluminationForDirectionalLight( intersectionPoint, normal, eyePosition,
                                                                         material, directionalLight );
                }
            }
        }
    }

    vec3 reflectedDir = NuroMath::reflect( ray.direction, normal );
    Ray  reflectedRay( intersectionPoint + 0.01f * reflectedDir, reflectedDir );

    return illuminance + objects[index]->getMaterial().getSpecular() * computeIlluminance( depth + 1, reflectedRay, reflectedRay.origin, objects, lights );
}

vec3 Raytracer::phongIlluminationForPointLight( const vec3& point, const vec3& normal, const vec3& eyePosition, const Material& material, const PointLight& pointLight )
{
    vec3  lightVector    = ( pointLight.position - point );
    vec3  lightDirection = lightVector.getNormalized();
    float attenuation    = pointLight.computeAttenuation( lightVector.length() );
    float cosine         = std::max( 0.0f, dot( lightDirection, normal ) );
    vec3  eyeDirection   = ( eyePosition - point ).getNormalized();
    vec3  specular;

    vec3 halfVector = ( lightDirection + eyeDirection ).getNormalized();

    specular = pointLight.intensity * material.getSpecular()
               * std::pow( std::max( 0.0f, dot( normal, halfVector ) ), material.getSpecularPower() ) * attenuation;


    vec3 diffuse = pointLight.intensity * material.getDiffuse() * cosine * attenuation;
    return diffuse + specular;
}

vec3 Raytracer::phongIlluminationForDirectionalLight( const vec3& point, const vec3& normal, const vec3& eyePosition, const Material& material, const DirectionalLight& directionalLight )
{
    vec3  lightVector    = -directionalLight.direction;
    vec3  lightDirection = lightVector.getNormalized();
    float cosine         = std::max( 0.0f, dot( lightDirection, normal ) );
    vec3  eyeDirection   = ( eyePosition - point ).getNormalized();
    vec3  specular;

    vec3 halfVector = ( lightDirection + eyeDirection ).getNormalized();

    specular = directionalLight.intensity * material.getSpecular()
               * std::pow( std::max( 0.0f, dot( normal, halfVector ) ), material.getSpecularPower() );


    vec3 diffuse = directionalLight.intensity * material.getDiffuse() * cosine;
    return diffuse + specular;
}

bool Raytracer::isInShadow( const vec3& point, const vec3& normal, const PointLight& pointLight, const std::vector<std::unique_ptr<Geometry>>& objects )
{
    auto directionToLight = ( pointLight.position - point ).getNormalized();
    if( dot( directionToLight, normal ) < 0.0f )
        return true;
    const auto& toLightTracingResult = computeIntersection( Ray( point + 0.01f * directionToLight, directionToLight ), objects );
    if( toLightTracingResult ) {
        const auto& tuple = toLightTracingResult.value();
        if( std::get<1>( tuple ) < ( pointLight.position - point ).length() )
            return true;
    }
    return false;
}

bool Raytracer::isInShadow( const vec3& point, const vec3& normal, const DirectionalLight& directionalLight, const std::vector<std::unique_ptr<Geometry>>& objects )
{
    if( dot( -directionalLight.direction, normal ) < 0.0f )
        return true;
    const auto& toLightTracingResult = computeIntersection( Ray( point - 0.01f * directionalLight.direction, -directionalLight.direction ), objects );
    if( toLightTracingResult )
        return true;
    return false;
}
