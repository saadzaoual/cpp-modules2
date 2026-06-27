#include "Serializer.hpp"

int main(void)
{
    Data        original;

    original.id = 42;
    original.name = "Saad";
    original.value = 3.14f;

    std::cout << "=== Before serialization ===" << std::endl;
    std::cout << "Object address: " << &original << std::endl;
    std::cout << "id:    " << original.id << std::endl;
    std::cout << "name:  " << original.name << std::endl;
    std::cout << "value: " << original.value << std::endl;
    std::cout << std::endl;

    // pointer -> integer
    uintptr_t   raw = Serializer::serialize(&original);
    std::cout << "=== Serialized ===" << std::endl;
    std::cout << "raw (uintptr_t): " << raw << std::endl;
    std::cout << "raw (in hex):    " << std::hex << raw << std::dec << std::endl;
    std::cout << std::endl;

    // integer -> pointer
    Data*       restored = Serializer::deserialize(raw);
    std::cout << "=== Deserialized ===" << std::endl;
    std::cout << "Restored address: " << restored << std::endl;
    std::cout << std::endl;

    // proofs
    std::cout << "=== Verification ===" << std::endl;
    std::cout << "Same address?  "
              << (restored == &original ? "YES" : "NO") << std::endl;
    std::cout << "Data intact?   "
              << ((restored->id == original.id
                   && restored->name == original.name
                   && restored->value == original.value) ? "YES" : "NO")
              << std::endl;
    std::cout << std::endl;

    // proof we point at the SAME object, not a copy:
    // mutate through the restored pointer, original sees it
    restored->id = 99;
    std::cout << "After restored->id = 99, original.id = "
              << original.id << " (expect 99)" << std::endl;

    return 0;
}