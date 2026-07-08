#ifndef SPAN_HPP
#define SPAN_HPP

#include <iostream>
#include <vector>
#include <algorithm>
#include <exception>

class Span
{
    private:
        unsigned int _N;
        std::vector<int>	_v;
    public:
        Span();
        Span(unsigned int N);
        Span(const Span &copy);
        Span &operator=(const Span &other);
        ~Span();

        //methods;
        int shortestSpan();
	    int longestSpan();
        void    addNumber(int n);
        void    addNumber(std::vector<int>::iterator begin, std::vector<int>::iterator end);

        //exceptions;
        class FullContainerException : public std::exception
	    {
		    public:
			    virtual const char *what() const throw();
	    };

	    class NotEnoughNumbersException : public std::exception
	    {
		    public:
			    virtual const char *what() const throw();
	    };
};
#endif