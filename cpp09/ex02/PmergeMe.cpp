#include "PmergeMe.hpp"
#include <utility>

PmergeMe::PmergeMe() {}
PmergeMe::PmergeMe(const PmergeMe &copy) { *this = copy; }
PmergeMe &PmergeMe::operator=(const PmergeMe &other)
{
    if (this != &other) { _vec = other._vec; _deq = other._deq; }
    return (*this);
}
PmergeMe::~PmergeMe() {}

const char *PmergeMe::InvalidInputException::what() const throw()
{
    return ("Error");
}

void PmergeMe::parseInput(int argc, char **argv)
{
    for (int i = 1; i < argc; i++)
    {
        std::string arg(argv[i]);
        if (arg.empty())
            throw InvalidInputException();
        for (size_t j = 0; j < arg.size(); j++)
            if (!isdigit(arg[j]))
                throw InvalidInputException();
        std::istringstream ss(arg);
        long value;
        ss >> value;
        if (ss.fail() || value > 2147483647)
            throw InvalidInputException();
        _input.push_back(arg);
    }
}


static size_t jacobsthal(size_t n)
{
    if (n == 0) return (0);
    if (n == 1) return (1);
    size_t a = 0, b = 1, c = 0;
    for (size_t i = 2; i <= n; i++) { c = b + 2 * a; a = b; b = c; }
    return (b);
}

void PmergeMe::_insertVector(std::vector<int> &chain, std::vector<int> &pend)
{
    if (pend.empty())
        return;

    chain.insert(chain.begin(), pend[0]);

    size_t inserted = 1;
    size_t k = 3;
    while (inserted < pend.size())
    {
        size_t jac  = jacobsthal(k);
        size_t prev = jacobsthal(k - 1);
        if (jac > pend.size())
            jac = pend.size();

        for (size_t idx = jac; idx > prev; idx--)
        {
            size_t index = idx - 1;
            std::vector<int>::iterator end = chain.begin() + (index + inserted);
            std::vector<int>::iterator pos =
                std::lower_bound(chain.begin(), end, pend[index]);
            chain.insert(pos, pend[index]);
            inserted++;
        }
        k++;
    }
}

void PmergeMe::_sortVector(std::vector<int> &v)
{
    size_t n = v.size();
    if (n <= 1)
        return;

    bool hasOdd = (n % 2 != 0);
    int  odd = 0;
    if (hasOdd)
        odd = v[n - 1];

    std::vector<std::pair<int,int> > pairs;
    for (size_t i = 0; i + 1 < n; i += 2)
    {
        if (v[i] > v[i + 1]) pairs.push_back(std::make_pair(v[i], v[i + 1]));
        else                 pairs.push_back(std::make_pair(v[i + 1], v[i]));
    }

    std::vector<int> bigs;
    for (size_t i = 0; i < pairs.size(); i++)
        bigs.push_back(pairs[i].first);
    _sortVector(bigs);

    std::vector<int>  pend;
    std::vector<bool> used(pairs.size(), false);
    for (size_t i = 0; i < bigs.size(); i++)
    {
        for (size_t j = 0; j < pairs.size(); j++)
        {
            if (!used[j] && pairs[j].first == bigs[i])
            {
                pend.push_back(pairs[j].second);
                used[j] = true;
                break;
            }
        }
    }

    std::vector<int> chain = bigs;
    _insertVector(chain, pend);

    if (hasOdd)
    {
        std::vector<int>::iterator pos =
            std::lower_bound(chain.begin(), chain.end(), odd);
        chain.insert(pos, odd);
    }
    v = chain;
}

void PmergeMe::_insertDeque(std::deque<int> &chain, std::deque<int> &pend)
{
    if (pend.empty())
        return;

    chain.insert(chain.begin(), pend[0]);

    size_t inserted = 1;
    size_t k = 3;
    while (inserted < pend.size())
    {
        size_t jac  = jacobsthal(k);
        size_t prev = jacobsthal(k - 1);
        if (jac > pend.size())
            jac = pend.size();

        for (size_t idx = jac; idx > prev; idx--)
        {
            size_t index = idx - 1;
            std::deque<int>::iterator end = chain.begin() + (index + inserted);
            std::deque<int>::iterator pos =
                std::lower_bound(chain.begin(), end, pend[index]);
            chain.insert(pos, pend[index]);
            inserted++;
        }
        k++;
    }
}

void PmergeMe::_sortDeque(std::deque<int> &d)
{
    size_t n = d.size();
    if (n <= 1)
        return;

    bool hasOdd = (n % 2 != 0);
    int  odd = 0;
    if (hasOdd)
        odd = d[n - 1];

    std::vector<std::pair<int,int> > pairs;
    for (size_t i = 0; i + 1 < n; i += 2)
    {
        if (d[i] > d[i + 1]) pairs.push_back(std::make_pair(d[i], d[i + 1]));
        else                 pairs.push_back(std::make_pair(d[i + 1], d[i]));
    }

    std::deque<int> bigs;
    for (size_t i = 0; i < pairs.size(); i++)
        bigs.push_back(pairs[i].first);
    _sortDeque(bigs);

    std::deque<int>   pend;
    std::vector<bool> used(pairs.size(), false);
    for (size_t i = 0; i < bigs.size(); i++)
    {
        for (size_t j = 0; j < pairs.size(); j++)
        {
            if (!used[j] && pairs[j].first == bigs[i])
            {
                pend.push_back(pairs[j].second);
                used[j] = true;
                break;
            }
        }
    }

    std::deque<int> chain = bigs;
    _insertDeque(chain, pend);

    if (hasOdd)
    {
        std::deque<int>::iterator pos =
            std::lower_bound(chain.begin(), chain.end(), odd);
        chain.insert(pos, odd);
    }
    d = chain;
}

void PmergeMe::run()
{
    std::cout << "Before:";
    for (size_t i = 0; i < _input.size(); i++)
        std::cout << " " << _input[i];
    std::cout << std::endl;

    clock_t startV = clock();
    for (size_t i = 0; i < _input.size(); i++)
        _vec.push_back(std::atoi(_input[i].c_str()));
    _sortVector(_vec);
    clock_t endV = clock();
    double timeV = static_cast<double>(endV - startV) / CLOCKS_PER_SEC * 1000000.0;

    clock_t startD = clock();
    for (size_t i = 0; i < _input.size(); i++)
        _deq.push_back(std::atoi(_input[i].c_str()));
    _sortDeque(_deq);
    clock_t endD = clock();
    double timeD = static_cast<double>(endD - startD) / CLOCKS_PER_SEC * 1000000.0;

    std::cout << "After:";
    for (size_t i = 0; i < _vec.size(); i++)
        std::cout << " " << _vec[i];
    std::cout << std::endl;

    std::cout << "Time to process a range of " << _vec.size()
              << " elements with std::vector : " << timeV << " us" << std::endl;
    std::cout << "Time to process a range of " << _deq.size()
              << " elements with std::deque  : " << timeD << " us" << std::endl;
}