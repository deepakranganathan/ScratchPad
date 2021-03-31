#include "tmp.h"

template <typename T>
void Base<T>::interface()
{
    cout << "This is the Base Interface" << endl;
}

template <>
void Base<DerivedA>::interface()
{
    cout << "This is the DerivedA Interface" << endl;
    getD().implementation();
}

template <>
void Base<DerivedB>::interface()
{
    cout << "This is the DerivedB Interface" << endl;
    getD().implementation();
}

void DerivedA::implementation()
{
    cout << "Derived A Implementation" << endl;
}

void DerivedB::implementation()
{
    cout << "Derived B Implementation" << endl;
}

void TestTraits()
{
    DerivedA dA;
    dA.interface();
    DerivedB dB;
    dB.interface();
}