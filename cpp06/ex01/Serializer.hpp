#ifndef SERIALIZER_HPP
#define SERIALIZER_HPP

#include <iostream>
#include <string>
#include <iostream>
#include <stdint.h> 

struct Data
{
    int n;
    std::string s;
};

class Serializer
{
    private:
        Serializer();
        Serializer(const Serializer& copy);
        Serializer& operator=(const Serializer& other);
        ~Serializer();
    public:
        static uintptr_t serialize(Data* ptr);
        static Data* deserialize(uintptr_t raw);
};
#endif