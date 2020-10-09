#pragma once

#include <iostream>
#include <sstream>
#include <stack>
#include <vector>

#include "Camera.h"
#include "Mat4.h"
#include "Mesh.h"
#include "PointLight.h"
#include "Raytracer.h"
#include "RenderOutput.h"
#include "Sampler.h"
#include "Sphere.h"
#include "Vec4.h"

class Scene
{
public:
    Scene()
        : renderOutput( resolution.x, resolution.y ),
          camera( resolution.x, resolution.y )
    {}
    void composeScene();
    template <typename T>
    bool readValues( std::stringstream& s, const int numvals, T* values );
    bool readString( std::stringstream& s, std::string& string );
    void parseFile( const std::string& filename );
    void render();
    void setCamera( Camera&& camera );
    void changeResolution( const vei2& resolution );

private:
    vei2                                   resolution = { 640, 360 };
    Camera                                 camera;
    Raytracer                              raytracer;
    Sampler                                sampler;
    RenderOutput                           renderOutput;
    std::vector<std::unique_ptr<Geometry>> objects;
    std::vector<std::unique_ptr<Light>>    lights;
};
