#pragma once

#include <vector>
#include "options.h"
#include "Vec3.h"

class Sampler
{
public:
    std::vector<vec2> getSamples( vei2 pixelPos );
};
