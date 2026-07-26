#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <iostream>
#include <string>
#include <vector>
#include <deque>
#include <algorithm>
#include <sstream>
#include <ctime>
#include <cctype>
#include <exception>

class PmergeMe
{
    private:
        std::vector<std::string> _input;
        std::vector<int> _vec;
        std::deque<int>  _deq;

        void _sortVector(std::vector<int> &v);
        void _sortDeque(std::deque<int> &d);

        void _insertVector(std::vector<int> &chain, std::vector<int> &pend);
        void _insertDeque(std::deque<int> &chain, std::deque<int> &pend);

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
                virtual const char *what() const throw();
        };
};

#endif