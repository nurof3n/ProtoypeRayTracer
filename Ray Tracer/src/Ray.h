#pragma once

#include "Vec3.h"

class Ray
{
public:
    Ray() = default;
    Ray( const vec3& origin, const vec3& direction )
        : origin( origin ),
          direction( direction )
    {}

public:
    vec3 origin;
    vec3 direction;
};
