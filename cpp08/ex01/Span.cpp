#include "Span.hpp"

Span::Span() : _N(0)
{
}

Span::Span(unsigned int N) : _N(N)
{
}

Span::Span(const Span &other)
{
	*this = other;
}

Span &Span::operator=(const Span &other)
{
	if (this != &other)
	{
		_N = other._N;
		_v = other._v;
	}
	return (*this);
}

Span::~Span()
{
}
//we add one number to our span.
void Span::addNumber(int n)
{
    if(_v.size() >= _N)
        throw FullContainerException();
    _v.push_back(n);
}
//we add a range of numbers to our span.
void Span::addNumber(std::vector<int>::iterator begin, std::vector<int>::iterator end)
{
    if(_v.size() + std::distance(begin, end) > _N)
        throw FullContainerException();
    _v.insert(_v.end(), begin, end);
}
//we find the shortest distance between two numbers in our span.
int Span::shortestSpan()
{
    if(_v.size() <= 1)
        throw NotEnoughNumbersException();
    std::vector<int> tmp = _v; //here we duplicate the countainer to a tmp one.
    std::sort(tmp.begin(),tmp.end());// then we sort its number.
    int min = tmp[1] - tmp[0]; // here we get the most min range.
    for (unsigned int i = 1; i < tmp.size(); i++)
	{
		if (tmp[i] - tmp[i - 1] < min)
			min = tmp[i] - tmp[i - 1];
	}//explain this loop more for me please.
	return (min);
}
// this get us the longspan i understand it its easy.
int		Span::longestSpan()
{
	if (_v.size() <= 1)
		throw NotEnoughNumbersException();
	std::vector<int> tmp = _v;
	std::sort(tmp.begin(), tmp.end());
	return (tmp[tmp.size() - 1] - tmp[0]); 
}
// exceptionsx
const char *Span::FullContainerException::what() const throw()
{
	return ("Container is full");
}

const char *Span::NotEnoughNumbersException::what() const throw()
{
	return ("Not enough numbers in container");
}

