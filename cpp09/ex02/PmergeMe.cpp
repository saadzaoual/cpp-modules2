#include "PmergeMe.hpp"
#include <utility>

/* ============================= OCF ============================= */

PmergeMe::PmergeMe() {}
PmergeMe::PmergeMe(const PmergeMe &copy) { *this = copy; }
PmergeMe &PmergeMe::operator=(const PmergeMe &other)
{
    if (this != &other) { _vec = other._vec; _deq = other._deq; }
    return (*this);
}
PmergeMe::~PmergeMe() {}

/* ======================= input parsing ======================= */

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
        if (ss.fail() || value > 2147483647 || value < 0)
            throw InvalidInputException();
        _vec.push_back(static_cast<int>(value));
        _deq.push_back(static_cast<int>(value));
    }
    if (_vec.empty())
        throw InvalidInputException();
}

/* ==================== Jacobsthal helper ==================== */

static size_t jacobsthal(size_t n)
{
    if (n == 0) return (0);
    if (n == 1) return (1);
    size_t a = 0, b = 1, c = 0;
    for (size_t i = 2; i <= n; i++) { c = b + 2 * a; a = b; b = c; }
    return (b);
}

/* =================================================================
** Generic Ford-Johnson on a container C of int.
** Implemented as a template-free pair of functions per container.
** Strategy that PRESERVES pairing:
**   - build pairs (big, small)
**   - sort the pairs by their 'big' value using merge-insertion on the bigs,
**     carrying the smalls along (so pairing is never broken)
**   - main chain = all bigs in sorted order
**   - pend = the smalls, in the SAME order as their bigs
**   - insert pend[0] free, then binary-insert the rest in Jacobsthal order
** ================================================================= */

// ---- VECTOR ----
static void fjVector(std::vector<int> &arr)
{
    size_t n = arr.size();
    if (n <= 1)
        return;

    std::vector<std::pair<int,int> > pairs;   // (big, small)
    bool hasLeftover = (n % 2 != 0);
    int  leftover = 0;
    if (hasLeftover)
        leftover = arr[n - 1];

    for (size_t i = 0; i + 1 < n; i += 2)
    {
        int a = arr[i], b = arr[i + 1];
        if (a > b) pairs.push_back(std::make_pair(a, b));
        else       pairs.push_back(std::make_pair(b, a));
    }

    // sort pairs by their big value (simple insertion sort keeps pairing intact)
    for (size_t i = 1; i < pairs.size(); i++)
    {
        std::pair<int,int> key = pairs[i];
        size_t j = i;
        while (j > 0 && pairs[j - 1].first > key.first)
        {
            pairs[j] = pairs[j - 1];
            j--;
        }
        pairs[j] = key;
    }

    // main chain = sorted bigs ; pend = corresponding smalls
    std::vector<int> main;
    std::vector<int> pend;
    for (size_t i = 0; i < pairs.size(); i++)
    {
        main.push_back(pairs[i].first);
        pend.push_back(pairs[i].second);
    }

    // pend[0] (partner of smallest big) goes to the front — free
    main.insert(main.begin(), pend[0]);

    // binary-insert the rest of pend in Jacobsthal order
    std::vector<bool> used(pend.size(), false);
    used[0] = true;
    size_t k = 3, inserted = 1;
    while (inserted < pend.size())
    {
        size_t jac = jacobsthal(k);
        size_t prevJac = jacobsthal(k - 1);
        if (jac > pend.size()) jac = pend.size();
        for (size_t idx = jac; idx > prevJac; idx--)
        {
            size_t index = idx - 1;
            if (index < pend.size() && !used[index])
            {
                std::vector<int>::iterator pos =
                    std::lower_bound(main.begin(), main.end(), pend[index]);
                main.insert(pos, pend[index]);
                used[index] = true;
                inserted++;
            }
        }
        k++;
        if (k > 64) break;
    }
    for (size_t i = 1; i < pend.size(); i++)
        if (!used[i])
        {
            std::vector<int>::iterator pos =
                std::lower_bound(main.begin(), main.end(), pend[i]);
            main.insert(pos, pend[i]);
        }

    if (hasLeftover)
    {
        std::vector<int>::iterator pos =
            std::lower_bound(main.begin(), main.end(), leftover);
        main.insert(pos, leftover);
    }
    arr = main;
}

// ---- DEQUE ----
static void fjDeque(std::deque<int> &arr)
{
    size_t n = arr.size();
    if (n <= 1)
        return;

    std::vector<std::pair<int,int> > pairs;
    bool hasLeftover = (n % 2 != 0);
    int  leftover = 0;
    if (hasLeftover)
        leftover = arr[n - 1];

    for (size_t i = 0; i + 1 < n; i += 2)
    {
        int a = arr[i], b = arr[i + 1];
        if (a > b) pairs.push_back(std::make_pair(a, b));
        else       pairs.push_back(std::make_pair(b, a));
    }

    for (size_t i = 1; i < pairs.size(); i++)
    {
        std::pair<int,int> key = pairs[i];
        size_t j = i;
        while (j > 0 && pairs[j - 1].first > key.first)
        {
            pairs[j] = pairs[j - 1];
            j--;
        }
        pairs[j] = key;
    }

    std::deque<int> main;
    std::deque<int> pend;
    for (size_t i = 0; i < pairs.size(); i++)
    {
        main.push_back(pairs[i].first);
        pend.push_back(pairs[i].second);
    }

    main.insert(main.begin(), pend[0]);

    std::vector<bool> used(pend.size(), false);
    used[0] = true;
    size_t k = 3, inserted = 1;
    while (inserted < pend.size())
    {
        size_t jac = jacobsthal(k);
        size_t prevJac = jacobsthal(k - 1);
        if (jac > pend.size()) jac = pend.size();
        for (size_t idx = jac; idx > prevJac; idx--)
        {
            size_t index = idx - 1;
            if (index < pend.size() && !used[index])
            {
                std::deque<int>::iterator pos =
                    std::lower_bound(main.begin(), main.end(), pend[index]);
                main.insert(pos, pend[index]);
                used[index] = true;
                inserted++;
            }
        }
        k++;
        if (k > 64) break;
    }
    for (size_t i = 1; i < pend.size(); i++)
        if (!used[i])
        {
            std::deque<int>::iterator pos =
                std::lower_bound(main.begin(), main.end(), pend[i]);
            main.insert(pos, pend[i]);
        }

    if (hasLeftover)
    {
        std::deque<int>::iterator pos =
            std::lower_bound(main.begin(), main.end(), leftover);
        main.insert(pos, leftover);
    }
    arr = main;
}

void PmergeMe::_sortVector(std::vector<int> &v) { fjVector(v); }
void PmergeMe::_insertVector(std::vector<int> &m, std::vector<int> &p) { (void)m; (void)p; }
void PmergeMe::_sortDeque(std::deque<int> &d) { fjDeque(d); }
void PmergeMe::_insertDeque(std::deque<int> &m, std::deque<int> &p) { (void)m; (void)p; }

/* ======================= run + timing ======================= */

void PmergeMe::run()
{
    std::cout << "Before:";
    for (size_t i = 0; i < _vec.size(); i++)
        std::cout << " " << _vec[i];
    std::cout << std::endl;

    clock_t startV = clock();
    _sortVector(_vec);
    clock_t endV = clock();
    double timeV = static_cast<double>(endV - startV) / CLOCKS_PER_SEC * 1000000.0;

    clock_t startD = clock();
    _sortDeque(_deq);
    clock_t endD = clock();
    double timeD = static_cast<double>(endD - startD) / CLOCKS_PER_SEC * 1000000.0;

    std::cout << "After: ";
    for (size_t i = 0; i < _vec.size(); i++)
        std::cout << " " << _vec[i];
    std::cout << std::endl;

    std::cout << "Time to process a range of " << _vec.size()
              << " elements with std::vector : " << timeV << " us" << std::endl;
    std::cout << "Time to process a range of " << _deq.size()
              << " elements with std::deque  : " << timeD << " us" << std::endl;
}