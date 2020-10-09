#include "CustomExcept.h"

CustomExcept::CustomExcept( const std::string& file, int line, const std::string& s )
    : buffer( s ),
      _line( line ),
      _file( file )
{}

const char* CustomExcept::getType() const
{
    return "Custom Exception";
}

const char* CustomExcept::what() const
{
    std::ostringstream output;
    output << "[File]: " << _file << "\n[Line]: " << _line << "\n[Exception]: " << buffer;
    buffer = output.str();
    return buffer.c_str();
}
