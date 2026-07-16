#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <algorithm>
#include <sstream>
#include <ctime>
#include <stdexcept>

class PmergeMe
{
    private:
        std::vector<int> _vec;
        std::deque<int>  _deq;

        // vector version
        void _sortVector(std::vector<int> &v);
        void _insertVector(std::vector<int> &main, std::vector<int> &pend);

        // deque version
        void _sortDeque(std::deque<int> &d);
        void _insertDeque(std::deque<int> &main, std::deque<int> &pend);

    public:
        PmergeMe();
        PmergeMe(const PmergeMe &copy);
        PmergeMe &operator=(const PmergeMe &other);
        ~PmergeMe();

        void parseInput(int argc, char **argv);
        void run();

        class InvalidInputException : public std::exception
        {
            public:
                virtual const char *what() const throw()
                {
                    return ("Error");
                }
        };
};

#endif