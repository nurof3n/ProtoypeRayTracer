#include "Scene.h"

#include "CustomExcept.h"

void Scene::composeScene()
{
    parseFile( "scene6.test" );
    // objects.push_back( std::unique_ptr<Geometry>( new Sphere{ camera.getWorldPosition() + vec3{ -1.0f, 2.0f, -3.0f }, 1.0f, Material{ { 0.2f, 0.2f, 0.2f }, { 1.0f }, 80.0f, { 0.05f } } } ) );
    // objects.push_back( std::unique_ptr<Geometry>( new Sphere{ camera.getWorldPosition() + vec3{ -1.0f, -2.0f, -3.0f }, 1.0f, Material{ { 0.35f, 0.73f, 0.6f }, { 0.3f }, 80.0f, { 0.05f } } } ) );
    // objects.push_back( std::unique_ptr<Geometry>( new Sphere{ camera.getWorldPosition() + vec3{ -3.0f, -1.0f, -3.0f }, 1.0f, Material{ { 1.0f, 1.0f, 1.0f }, { 0.1f }, 10.0f, { 0.05f } } } ) );
    // objects.push_back( std::unique_ptr<Geometry>( new Sphere{ camera.getWorldPosition() + vec3{ 2.0f, 0.0f, 1.0f }, 0.5f, Material{ { 0.0f, 1.0f, 1.0f }, { 0.2f }, 14.0f, { 0.05f } } } ) );
    // auto square = new Mesh{
    //     std::vector<vec3>{
    //         { -1.0f, -1.0f, -1.0f },
    //         { 1.0f, -1.0f, -1.0f },
    //         { 1.0f, 1.0f, -1.0f },
    //         { -1.0f, 1.0f, -1.0f },
    //         { -1.0f, -1.0f, 1.0f },
    //         { 1.0f, -1.0f, 1.0f },
    //         { 1.0f, 1.0f, 1.0f },
    //         { -1.0f, 1.0f, 1.0f } },
    //     std::vector<vei3>{
    //         { 0, 1, 5 },
    //         { 0, 5, 4 },
    //         { 3, 7, 6 },
    //         { 3, 6, 2 },
    //         { 1, 2, 6 },
    //         { 1, 6, 5 },
    //         { 0, 7, 3 },
    //         { 0, 4, 7 },
    //         { 0, 3, 2 },
    //         { 0, 2, 1 },
    //         { 4, 5, 6 },
    //         { 4, 6, 7 } },
    //     Material{ { 0.1f, 0.2f, 0.6f }, { 0.2f }, 5.0f, { 0.05f } }
    // };
    // square->move( { 2.0f, 0.0f, -2.0f } );
    // objects.push_back( std::unique_ptr<Geometry>( square ) );

    // for( auto& object : objects )
    //     object->move( { 0.0f, 0.0f, -5.0f } );
    // /*
    // lights.push_back( std::unique_ptr<Light>( new PointLight{ camera.getWorldPosition() + vec3{ 2.0f, 0.0f, -8.0f }, 7.0f * vec3{ 0.9f, 0.9f, 0.9f }, 1.0f, 1.0f, 0.2f } ) );
    // lights.push_back( std::unique_ptr<Light>( new PointLight{ camera.getWorldPosition() + vec3{ 5.0f, -1.0f, 3.0f }, 4.0f * vec3{ 0.5f, 0.5f, 0.5f }, 1.0f, 1.0f, 0.2f } ) );
    // lights.push_back( std::unique_ptr<Light>( new PointLight{ camera.getWorldPosition() + vec3{ -5.0f, -1.0f, -3.0f }, 5.0f * vec3{ 0.5f, 0.5f, 0.5f }, 1.0f, 1.0f, 0.2f } ) );
    //*/
}

void Scene::render()
{
    int  width      = camera.getWidthSpan();
    int  height     = camera.getHeightSpan();
    vei2 startPixel = camera.getScreenPosition();
    vei2 stopPixel  = startPixel + vei2{ width, height };
    stopPixel.x     = std::min( resolution.x, stopPixel.x );
    stopPixel.y     = std::min( resolution.y, stopPixel.y );
    for( int i = startPixel.x; i < stopPixel.x; ++i )
        for( int j = startPixel.y; j < stopPixel.y; ++j ) {
            std::vector<vec2> samples = sampler.getSamples( { i, j } );
            vec3              totalIlluminance;
            for( const auto& sample : samples ) {
                Ray ray = camera.createRay( sample );
                totalIlluminance += raytracer.computeIlluminance( 1, ray, camera.getWorldPosition(), objects, lights );
            }
            totalIlluminance /= static_cast<float>( samples.size() );
            renderOutput.setPixel( { i, j }, totalIlluminance );
        }
    renderOutput.drawToBmp();
}

void Scene::setCamera( Camera&& camera )
{
    this->camera = std::move( camera );
}

void Scene::changeResolution( const vei2& resolution )
{
    this->resolution = resolution;
    camera.setResolution( resolution );
    renderOutput.setResolution( resolution );
}

template <typename T>
bool Scene::readValues( std::stringstream& s, const int numvals, T* values )
{
    for( int i = 0; i < numvals; i++ ) {
        s >> values[i];
        if( s.fail() ) {
            std::cerr << "Failed reading value " << i << " will skip\n";
            return false;
        }
    }
    return true;
}

bool Scene::readString( std::stringstream& s, std::string& string )
{
    s >> string;
    if( s.fail() ) {
        std::cerr << "Failed reading string will skip\n";
        return false;
    }
    return true;
}

void Scene::parseFile( const std::string& filename )
{
    std::ifstream in( filename );
    if( in ) {
        vec3              ambient{ 0.2f }, diffuse, specular, emission, attenuation{ 1.0f, 0.0f, 0.0f };
        float             shininess{};
        bool              constructingMesh = false;
        std::vector<vec3> vertices;
        Mesh*             mesh = nullptr;

        std::stack<mat4> transformStack;
        std::stack<mat4> inverseTransformStack;
        transformStack.push( mat4::identity() );
        inverseTransformStack.push( mat4::identity() );

        std::string str, cmd;
        std::getline( in, str );
        while( in ) {
            if( ( str.find_first_not_of( " \t\r\n" ) != std::string::npos ) && ( str[0] != '#' ) ) {
                std::stringstream s( str );
                s >> cmd;
                int         i;
                float       floats[10];
                int         ints[3];
                std::string param;

                if( cmd == "maxdepth" ) {
                    if( readValues( s, 1, ints ) ) {
                        Options::RAY_RECURSION_MAX_DEPTH = static_cast<size_t>( ints[0] );
                    }
                }
                else if( cmd == "output" ) {
                    if( readString( s, param ) ) {
                        Options::outputFile = std::move( param );
                    }
                }

                // Light commands
                else if( cmd == "point" ) {
                    if( readValues( s, 6, floats ) ) {
                        lights.push_back( std::unique_ptr<Light>( new PointLight{
                            { floats[0], floats[1], floats[2] },
                            { floats[3], floats[4], floats[5] },
                            attenuation.x,
                            attenuation.y,
                            attenuation.z } ) );
                    }
                }
                else if( cmd == "directional" ) {
                    if( readValues( s, 6, floats ) ) {
                        lights.push_back( std::unique_ptr<Light>( new DirectionalLight{
                            -vec3{ floats[0], floats[1], floats[2] },
                            { floats[3], floats[4], floats[5] } } ) );
                    }
                }
                else if( cmd == "attenuation" ) {
                    if( readValues( s, 3, floats ) ) {
                        attenuation = { floats[0], floats[1], floats[2] };
                    }
                }

                // Material commands
                else if( cmd == "ambient" ) {
                    if( readValues( s, 3, floats ) ) {
                        ambient = { floats[0], floats[1], floats[2] };
                    }
                }
                else if( cmd == "diffuse" ) {
                    if( readValues( s, 3, floats ) ) {
                        diffuse = { floats[0], floats[1], floats[2] };
                    }
                }
                else if( cmd == "specular" ) {
                    if( readValues( s, 3, floats ) ) {
                        specular = { floats[0], floats[1], floats[2] };
                    }
                }
                else if( cmd == "emission" ) {
                    if( readValues( s, 3, floats ) ) {
                        emission = { floats[0], floats[1], floats[2] };
                    }
                }
                else if( cmd == "shininess" ) {
                    if( readValues( s, 1, floats ) )
                        shininess = floats[0];
                }

                // Camera commands
                else if( cmd == "size" ) {
                    if( readValues( s, 2, ints ) ) {
                        resolution = { ints[0], ints[1] };
                        camera.setResolution( resolution );
                        renderOutput.setResolution( resolution );
                    }
                }
                else if( cmd == "camera" ) {
                    if( readValues( s, 10, floats ) ) {
                        camera.setWorldPosition( { floats[0], floats[1], floats[2] } );
                        camera.setDirection( ( vec3{ floats[3], floats[4], floats[5] } - camera.getWorldPosition() ).getNormalized() );
                        camera.setUpVector( { floats[6], floats[7], floats[8] } );
                        camera.setRightVector( cross( camera.getDirection(), camera.getUpVector() ).getNormalized() );
                        camera.setUpVector( cross( camera.getRightVector(), camera.getDirection() ) );
                        camera.setVerticalFov( floats[9] );
                    }
                }

                // Geometry commands
                else if( cmd == "maxverts" || cmd == "maxvertnorms" ) {  // ignore
                    readValues( s, 1, ints );
                }
                else if( cmd == "sphere" ) {
                    if( readValues( s, 4, floats ) ) {
                        Sphere* sphere = new Sphere{ { floats[0], floats[1], floats[2] }, floats[3], Material{ diffuse, specular, shininess, emission, ambient } };
                        sphere->setTransformMatrix( transformStack.top() );
                        sphere->setInverseTransformMatrix( inverseTransformStack.top() );
                        objects.push_back( std::unique_ptr<Geometry>( sphere ) );
                    }
                }
                else if( cmd == "vertex" ) {
                    if( readValues( s, 3, floats ) ) {
                        vertices.push_back( { floats[0], floats[1], floats[2] } );
                    }
                }
                else if( cmd == "tri" ) {
                    if( readValues( s, 3, ints ) ) {
                        mesh = new Mesh( { vertices[ints[0]], vertices[ints[1]], vertices[ints[2]] }, { { 0, 1, 2 } }, Material{ diffuse, specular, shininess, emission, ambient } );
                        mesh->setTransformMatrix( transformStack.top() );
                        mesh->setInverseTransformMatrix( inverseTransformStack.top() );
                        objects.push_back( std::unique_ptr<Geometry>( mesh ) );
                    }
                }

                // Transformations commands
                else if( cmd == "translate" ) {
                    if( readValues( s, 3, floats ) ) {
                        transformStack.top() = mat4::translationMatrix( { floats[0], floats[1], floats[2] } ) * transformStack.top();
                        inverseTransformStack.top() *= mat4::translationMatrix( { -floats[0], -floats[1], -floats[2] } );
                    }
                }
                else if( cmd == "scale" ) {
                    if( readValues( s, 3, floats ) ) {
                        transformStack.top() = mat4::scaleMatrix( { floats[0], floats[1], floats[2] } ) * transformStack.top();
                        inverseTransformStack.top() *= mat4::scaleMatrix( { 1.0f / floats[0], 1.0f / floats[1], 1.0f / floats[2] } );
                    }
                }
                else if( cmd == "rotate" ) {
                    if( readValues( s, 4, floats ) ) {
                        transformStack.top() = mat4::rotationMatrix( { floats[0], floats[1], floats[2] }, floats[3] ) * transformStack.top();
                        inverseTransformStack.top() *= mat4::rotationMatrix( { floats[0], floats[1], floats[2] }, -floats[3] );
                    }
                }
                else if( cmd == "pushTransform" ) {
                    transformStack.push( transformStack.top() );
                    inverseTransformStack.push( inverseTransformStack.top() );
                }
                else if( cmd == "popTransform" ) {
                    if( transformStack.size() <= 1 ) {
                        std::cerr << "Stack has no elements. Cannot Pop\n";
                    }
                    else {
                        transformStack.pop();
                        inverseTransformStack.pop();
                    }
                }
                else {
                    std::cerr << "Unknown Command: " << cmd << " Skipping \n";
                }
            }
            std::getline( in, str );
        }
    }
    else {
        throw EXCEPT( "Unable to Open Input Data File " + filename );
    }
}