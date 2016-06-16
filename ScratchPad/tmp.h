#pragma once

#include <iostream>
using namespace std;

template <typename T>
class Base
{
public:
    //CRTP user function
    T& getD()
    {
        return *static_cast<T*>(this);
    }
    void interface();
};
class DerivedA : public Base<DerivedA>
{
public:
    void implementation();
};

class DerivedB : public Base<DerivedB>
{
public:
    void implementation();
};

void TestTraits();