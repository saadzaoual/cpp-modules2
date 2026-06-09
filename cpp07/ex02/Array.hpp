#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <iostream>
#include <string>
#include <stdexcept>

template <typename T>
class Array
{
private:
    T* _data;
    size_t _size;

public:
    // Default constructor
    Array() : _data(NULL), _size(0) {}

    // Constructor with size
    Array(size_t n) : _size(n)
    {
        if (n > 0)
            _data = new T[n]();
        else
            _data = NULL;
    }

    // Copy constructor
    Array(const Array& other) : _size(other._size)
    {
        if (_size > 0)
        {
            _data = new T[_size];
            for (size_t i = 0; i < _size; i++)
                _data[i] = other._data[i];
        }
        else
            _data = NULL;
    }

    // Assignment operator
    Array& operator=(const Array& other)
    {
        if (this != &other)
        {
            delete[] _data;
            _size = other._size;
            if (_size > 0)
            {
                _data = new T[_size];
                for (size_t i = 0; i < _size; i++)
                    _data[i] = other._data[i];
            }
            else
                _data = NULL;
        }
        return *this;
    }

    // Destructor
    ~Array()
    {
        delete[] _data;
    }

    // Subscript operator with bounds checking
    T& operator[](size_t index)
    {
        if (index >= _size)
            throw std::out_of_range("Array index out of range");
        return _data[index];
    }

    // Const subscript operator
    const T& operator[](size_t index) const
    {
        if (index >= _size)
            throw std::out_of_range("Array index out of range");
        return _data[index];
    }

    // Size getter
    size_t size() const
    {
        return _size;
    }
};

#endif