/*
    Resource.cpp

    Example of a class using the RAII idiom for a chunk of data

    * Only meant for discussion of an implementation of the RAII concept
    * Comments with NOTE are not good general program comments
*/

#include <string_view>
#include <iostream>
#include <cassert>

class Resource {
public:

    // constructor
    Resource(std::string_view s) : size(s.size()) {


        // allocate the data
        data = new char[size];

        // copy the string
        std::copy(s.cbegin(), s.cend(), data);
    }

    // copy constructor
    Resource(const Resource& r) {

        // allocate the data
        data = new char[r.size];

        // copy the string
        std::copy(r.data, r.data + r.size, data);
    }

    // disallow assignment
    void operator=(const Resource&) = delete;

    // bool conversion operator
    explicit operator bool() const {

        return data != nullptr;
    }

    // access data
    std::string_view get() {
        return data;
    }

    // remove data
    void clear() {

        if (data != nullptr)
            delete [] data;
        data = nullptr;
    }

    // destructor
    ~Resource() {

        clear();
    }

private:
    char* data = nullptr;
    int size = 0;
};

int main() {

    {
        // NOTE: automatic allocation of data in the constructor
        Resource r("Hello");

        // NOTE: automatic deallocation in the destructor
        //       remove possibility of memory leaks for data
    }

    {
        // NOTE: allocation of data is automatically
        //       performed in the constructor
        Resource r("Hello");

        // NOTE: checks validity of resource
        if (r) {

            // NOTE: access the data safely
            assert(r.get() == "Hello");
        }
    }

    {
        // NOTE: allocation of data is automatically
        //       performed in the constructor
        Resource r("Hello");

        // NOTE: clear() deallocates data early, but safely
        r.clear();

        // NOTE: should never be true because of previous clear()
        if (r) {
            assert(false);
        }
    }

    {
        Resource r("Hello");

        // NOTE: Proper copying of data
        Resource r2(r);
    }

    {
        Resource r("Hello");

        Resource r2("");

        // NOTE: Disallowed assignment
        // r2 = r;
    }

    return 0;
}
