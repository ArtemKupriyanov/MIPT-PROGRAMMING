#ifndef VECTOR_H
#define VECTOR_H

#include "abstractarray.h"
#include <vector>

class Vector : public AbstractArray {
public:
    Vector();
    ~Vector();
    virtual int Sum( int l, int r );    // сумма на подотрезке
    virtual void Push( int index, int count );  // добавление в i-ую позицию
    virtual void Assign( int index, int count );    // обновление i-ого эл-та
    virtual bool NextPermutation( int l, int r );
//  void write();

private:
    std::vector< int > buffer;
};

#endif // VECTOR_H
