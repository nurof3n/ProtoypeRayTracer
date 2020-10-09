#include "Camera.h"

Ray Camera::createRay( const vec2& sample )
{
    vec2  xy  = sample - static_cast<vec2>( vei2{ width, height } ) / 2.0f;  // the center of the screen becomes (0, 0)
    float z   = ( height / 2.0f ) / std::tan( NuroMath::radians( fov / 2.0f ) );
    Ray   ray = {
        vec3{ 0.0f },
        vec3( { xy.x, -xy.y, -z } ).getNormalized()  // x goes right, y goes up, z goes behind the camera
    };
    // transform the ray for camera
    return NuroMath::transformRay( ray, NuroMath::transpose( mat4{ vec4{ rightVector, 0.0f },
                                                                   vec4{ upVector, 0.0f },
                                                                   vec4{ -direction, 0.0f },
                                                                   vec4{ worldPosition, 1.0f } } ) );
}

vei2 Camera::getResolution() const
{
    return { width, height };
}

int Camera::getWidthSpan() const noexcept
{
    return width;
}

int Camera::getHeightSpan() const noexcept
{
    return height;
}

float Camera::getVerticalFov() const noexcept
{
    return fov;
}

vec3 Camera::getWorldPosition() const noexcept
{
    return worldPosition;
}

vec3 Camera::getDirection() const noexcept
{
    return direction;
}

vec3 Camera::getUpVector() const noexcept
{
    return upVector;
}

vec3 Camera::getRightVector() const noexcept
{
    return rightVector;
}

vei2 Camera::getScreenPosition() const noexcept
{
    return screenPosition;
}

void Camera::setResolution( const vei2& resolution )
{
    width  = resolution.x;
    height = resolution.y;
}

void Camera::setWidthSpan( int width ) noexcept
{
    this->width = width;
}

void Camera::setHeightSpan( int height ) noexcept
{
    this->height = height;
}

void Camera::setVerticalFov( float degrees ) noexcept
{
    fov = degrees;
}

void Camera::setWorldPosition( const vec3& worldPosition )
{
    this->worldPosition = worldPosition;
}

void Camera::setDirection( const vec3& direction )
{
    this->direction = direction;
}

void Camera::setUpVector( const vec3& upVector )
{
    this->upVector = upVector;
}

void Camera::setRightVector( const vec3& rightVector )
{
    this->rightVector = rightVector;
}

void Camera::setScreenPosition( const vei2& pixelPos )
{
    screenPosition = pixelPos;
}
