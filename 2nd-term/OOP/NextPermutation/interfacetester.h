#ifndef INTERFACETESTER_H
#define INTERFACETESTER_H

#include "abstractarray.h"
#include <algorithm>
#include <ctime>
#include <vector>

class InterfaceTester {
public:
    InterfaceTester( int Number, int Range );
    ~InterfaceTester();
private:
    // команда
    enum testInterface {
        SUM,
        PUSH,
        ASSIGN,
        NEXTPERMUTATION
    };

    int commandNumber;  // количество команд
    int commandRange;   // диапазон значений
    void createCommands();  // создание команд
    std::vector< std::pair< testInterface, std::pair< int, int > > > Commands;   // вектор команд
    AbstractArray* Treap;
    AbstractArray* Vector;
    clock_t Testing( AbstractArray* arr , bool is_treap);
    std::vector< int > vectorAns;   // вектор ответов лобовой реализации
    std::vector< int > treapAns;    // вектор ответов реализации на дереве
};

#endif // INTERFACETESTER_H
