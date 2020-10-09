#pragma once
#include <exception>
#include <sstream>
#include <string>

// macro to insert the filename and the code line where the exception originated from
#define EXCEPT( s ) ( CustomExcept( __FILE__, __LINE__, s ) )

// custom exception class derived from the standard exception class
class CustomExcept : public std::exception
{
public:
    CustomExcept() = delete;
    CustomExcept( const std::string& file, int line, const std::string& s );
    virtual const char* getType() const;
    // returns a message with details about the exception thrown
    const char* what() const override;

private:
    mutable std::string buffer;
    std::string         _file;
    int                 _line;
};
