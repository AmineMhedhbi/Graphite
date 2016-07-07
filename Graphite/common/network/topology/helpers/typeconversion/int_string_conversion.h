#ifndef INT_STRING_CONVERSION_H
#define INT_STRING_CONVERSION_H

#include <string>
#include <sstream>
#include <iostream>
#include <stdlib.h>

/* 
 * Souce code taken as is from Chameleon with slight modifications
 * http://www.adp-gmbh.ch/cpp/chameleon.html
 * The modification make the conversion between string and int
 * 		instead of string and double.
 */

class Alchemist // "In order to obtain or create something,
                //     something of equal value must be lost or destroyed." 
{
    public:
        Alchemist() {};
        explicit Alchemist(const std::string&);
        explicit Alchemist(int);
        explicit Alchemist(const char*);

        Alchemist(const Alchemist&);
        Alchemist& operator=(Alchemist const&);

        Alchemist& operator=(int);
        Alchemist& operator=(std::string const&);

        operator std::string() const;
        operator int()         const;

    private:
        std::string value_;
};

#endif // INT_STRING_CONVERSION_H
