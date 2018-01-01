#ifndef ABSTRACTARRAY_H
#define ABSTRACTARRAY_H

class AbstractArray {
public:
    virtual ~AbstractArray() {}
    virtual int Sum( int l, int r ) = 0;    // сумма на подотрезке
    virtual void Push( int index, int newKey ) = 0 ;    // добавление в i-ую позицию
    virtual void Assign( int index, int newKey ) = 0;   // обновление i-ого эл-та
    virtual bool NextPermutation( int l, int r ) = 0;
};

#endif // ABSTRACTARRAY_H
