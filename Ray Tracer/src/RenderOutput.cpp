#include "RenderOutput.h"

void RenderOutput::setPixel( vei2 pos, Color color )
{
    buffer[getIndex( pos )] = color;
}

void RenderOutput::setPixel( vei2 pos, vec3 illuminance )
{
    setPixel( pos, NuroMath::denormalizeRgb( illuminance ) );
}

void RenderOutput::setResolution( const vei2& resolution )
{
    width  = resolution.x;
    height = resolution.y;
    buffer.resize( width * height );
}

size_t RenderOutput::getIndex( vei2 pos ) const
{
    return static_cast<size_t>( pos.x + pos.y * width );
}

vei2 RenderOutput::getResolution() const
{
    return { width, height };
}

int RenderOutput::getWidth() const noexcept
{
    return width;
}

void RenderOutput::setWidth( int width ) noexcept
{
    this->width = width;
    buffer.resize( width * height );
}

int RenderOutput::getHeight() const noexcept
{
    return height;
}

void RenderOutput::setHeight( int height ) noexcept
{
    this->height = height;
    buffer.resize( width * height );
}

void RenderOutput::drawToBmp() const
{
    bitmap_image bmp( width, height );
    for( int i = 0; i < width; ++i )
        for( int j = 0; j < height; ++j ) {
            Color color = buffer[getIndex( { i, j } )];
            bmp.set_pixel( i, j, color.x, color.y, color.z );
        }
    bmp.save_image( Options::outputFile );
}

void RenderOutput::clearBuffer()
{
    buffer.clear();
}
