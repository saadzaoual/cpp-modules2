#include "Serializer.hpp"
#include <iostream>

int main(void)
{
    std::cout << "===== Serializer round-trip test =====" << std::endl;

    // 1. Create a Data object with some values
    Data original;
    original.n = 42;
    original.s = "Hello, serialization!";

    std::cout << "Original Data:" << std::endl;
    std::cout << "  Address: " << &original << std::endl;
    std::cout << "  n = " << original.n << std::endl;
    std::cout << "  s = " << original.s << std::endl;
    std::cout << std::endl;

    // 2. Serialize: pointer → uintptr_t
    uintptr_t raw = Serializer::serialize(&original);
    std::cout << "After serialize():" << std::endl;
    std::cout << "  raw (uintptr_t) = " << raw << std::endl;
    std::cout << std::endl;

    // 3. Deserialize: uintptr_t → pointer
    Data* recovered = Serializer::deserialize(raw);
    std::cout << "After deserialize():" << std::endl;
    std::cout << "  recovered (Data*) = " << recovered << std::endl;
    std::cout << "  recovered->n = " << recovered->n << std::endl;
    std::cout << "  recovered->s = " << recovered->s << std::endl;
    std::cout << std::endl;

    // 4. Verify round-trip
    std::cout << "===== Verification =====" << std::endl;
    if (recovered == &original)
        std::cout << "PASS: recovered pointer equals original" << std::endl;
    else
        std::cout << "FAIL: pointers don't match" << std::endl;

    if (recovered->n == original.n && recovered->s == original.s)
        std::cout << "PASS: fields preserved through round-trip" << std::endl;
    else
        std::cout << "FAIL: fields modified somehow" << std::endl;

    return (0);
}