#include "vector.h"
#include <algorithm>
#include <assert.h>
#include <iostream>

Vector::Vector() {}

Vector::~Vector() {}

int Vector::Sum( int l, int r ) {
    int sum = 0;
    assert( 0 <= l && r < buffer.size() );
    for( int i = l; i <= r; ++i )
        sum += buffer[i];
    return sum;
}

void Vector::Push( int index, int count ) {
    buffer.insert(buffer.begin() + index, count);
}

void Vector::Assign( int index, int count ) {
    buffer[index] = count;
}

bool Vector::NextPermutation( int l, int r ) {
    return std::next_permutation( buffer.begin() + l, buffer.begin() + r + 1 );
}

/*
void Vector::write() {
    std::cout << "vectorArray:  ";
    for( int i = 0; i < buffer.size(); ++i )
    std::cout << buffer[i] << " ";
    std::cout << std::endl;
};
*/
