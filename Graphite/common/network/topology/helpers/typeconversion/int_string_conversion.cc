/*
   int_string_conversion.cpp
	acknowledgment to René Nyffenegger for the implementation of Chameleon
	Alchemist converts between int and string
*/

#include "int_string_conversion.h"

Alchemist::Alchemist(std::string const& value)
{
    value_ = value;
}

Alchemist::Alchemist(const char* c)
{
    value_ = c;
}

Alchemist::Alchemist(int d)
{
    std::stringstream s;
    s << d;
    value_ = s.str();
}

Alchemist::Alchemist(Alchemist const& other)
{
    value_ = other.value_;
}

Alchemist& Alchemist::operator=(Alchemist const& other)
{
    value_ = other.value_;
    return *this;
}

Alchemist& Alchemist::operator=(int i)
{
    std::stringstream s;
    s << i;
    value_ = s.str();
    return *this;
}

Alchemist& Alchemist::operator=(std::string const& s)
{
    value_ = s;
    return *this;
}

Alchemist::operator std::string() const { return value_; }

Alchemist::operator int() const { return (int) atof(value_.c_str()); }
