#pragma once

#include <vector>

#include "NuroMath.h"
#include "Options.h"
#include "Vec2.h"
#include "Vec3.h"
#include "bitmap_image.hpp"

class RenderOutput
{
public:
    RenderOutput() = delete;
    RenderOutput( int width, int height )
        : width( width ),
          height( height )
    {
        buffer.resize( width * height );
    }

    vei2 getResolution() const;
    int  getWidth() const noexcept;
    int  getHeight() const noexcept;
    void setPixel( vei2 pos, Color color );
    void setPixel( vei2 pos, vec3 illuminance );
    void setResolution( const vei2& resolution );
    void setWidth( int width ) noexcept;
    void setHeight( int height ) noexcept;
    void drawToBmp() const;
    void clearBuffer();

private:
    size_t getIndex( vei2 pos ) const;

private:
    int                width;
    int                height;
    std::vector<Color> buffer;
};
