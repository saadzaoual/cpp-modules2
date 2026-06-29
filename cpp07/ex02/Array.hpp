#ifndef ARRAY_HPP
# define ARRAY_HPP

# include <iostream>
# include <exception>

template <typename T>
class Array
{
	private:
		T				*_arr;
		unsigned int	_size;
	public:
		// Constructors
		Array();
		Array(unsigned int n);
		Array(Array const &copy);
		~Array();

		// Operators
		Array			&operator=(Array const &copy);
		T				&operator[](unsigned int i);
		T const			&operator[](unsigned int i) const;

		// Methods
		unsigned int	size() const;
	
		// Exceptions
		class OutOfBoundsException : public std::exception
		{
			public:
				virtual const char *what() const throw();
		};

};
# include "Array.tpp"

#endif