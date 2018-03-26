#ifndef HEADER_VECTOR
#define HEADER_VECTOR

#include <vector>

template <typename T>
class Vector : public std::vector<T>
{
public:
    // Remove item at index i.
    void remove(size_t i)
    {
        erase(begin() + i);
    }

    template <typename T>
    void removeitem(const T& item)
    {
        for (size_t i = 0; i < size(); ++i)
        {
            if (item == at(i))
            {
                remove(i);
            }
        }
    }
};

#endif
