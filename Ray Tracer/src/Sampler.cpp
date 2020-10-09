#include "Sampler.h"

std::vector<vec2> Sampler::getSamples( vei2 pixelPos )
{
    vec2 center = static_cast<vec2>( pixelPos ) + vec2{ 0.5f };
#ifdef AA
    return std::vector<vec2>{
        center + vec2{ 0.0f, 0.25f },
        center + vec2{ 0.0f, -0.25f },
        center + vec2{ 0.25f, 0.0f },
        center + vec2{ -0.25f, 0.0f }
    };
#else
    return std::vector<vec2>{ center };
#endif
}
