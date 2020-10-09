#pragma once

#include "NuroMath.h"
#include "Ray.h"
#include "Vec2.h"
#include "Vec3.h"

class Camera
{
public:
    Camera() = delete;
    Camera( int width, int height, const vec3& worldPosition = { 0.0f, 0.0f, 0.0f }, const vei2& screenPosition = { 0, 0 }, float fov = 45.0f )
        : worldPosition( worldPosition ),
          screenPosition( screenPosition ),
          width( width ),
          height( height ),
          fov( fov )
    {}
    // creates a normalized direction from the camera to the projected sample in screen space
    Ray  createRay( const vec2& sample );
    vei2 getResolution() const;
    // returns the number of pixels the camera spans in width
    int getWidthSpan() const noexcept;
    // returns the number of pixels the camera spans in height
    int getHeightSpan() const noexcept;
    // returns the vertical fov in degrees
    float getVerticalFov() const noexcept;
    vec3  getWorldPosition() const noexcept;
    vec3  getDirection() const noexcept;
    vec3  getUpVector() const noexcept;
    vec3  getRightVector() const noexcept;
    // returns the position on the screen (top-left pixel coords)
    vei2 getScreenPosition() const noexcept;
    void setResolution( const vei2& resolution );
    // sets the number of pixels the camera spans in width
    void setWidthSpan( int pixelWidth ) noexcept;
    // sets the number of pixels the camera spans in height
    void setHeightSpan( int pixelHeight ) noexcept;
    // sets the vertical fov in degrees
    void setVerticalFov( float degrees ) noexcept;
    void setWorldPosition( const vec3& worldPosition );
    void setDirection( const vec3& direction );
    void setUpVector( const vec3& upVector );
    void setRightVector( const vec3& rightVector );
    // sets the position on the screen (top-left pixel coords)
    void setScreenPosition( const vei2& pixelPos );

private:
    float fov;
    int   width;
    int   height;
    vec3  worldPosition;
    vec3  direction{ 0.0f, 0.0f, -1.0f };
    vec3  upVector{ 0.0f, 1.0f, 0.0f };
    vec3  rightVector{ 1.0f, 0.0f, 0.0f };
    vei2  screenPosition;
};
