#ifndef EASYFIND_HPP
# define EASYFIND_HPP

# include<algorithm>
# include<exception>

class NotFoundException : public std::exception
{
	public:
		virtual const char* what() const throw()
		{
			return ("Number not found");
		}
	
};

template <typename T>
typename T::iterator easyfind(T &container, int n)
{
	typename T::iterator it; //we created the iterator that well check the value postion inside the container.

	it = std::find(container.begin(), container.end(), n);
	// itt = holds the find value.
	//find is STL algorithms that check the countainer and loop on it to find the value you want. 
	if (it == container.end())
		throw NotFoundException();
	//we throw a exception in case of the value is not found.
	return (it);
}

#endif