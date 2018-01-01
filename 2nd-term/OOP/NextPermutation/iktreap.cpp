#include "iktreap.h"

#include <algorithm>
#include <cstdlib>
#include <iostream>

IKTreap::IKTreap() {
    MAX_PRIORITY = 1e+6;
    head = NULL;
}

IKTreap::IKTreap( int key, int priority ) {
    MAX_PRIORITY = 1e+6;
    head = new TreapNode( key, priority );
}

IKTreap::~IKTreap() {
    delete head;
}

// вырезаем нужное поддерево - после обновлений - в корне сумма на поддереве
// послеле этого - сливаем обратно
int IKTreap::Sum( int l, int r ) {
    TreapNode* right;
    TreapNode* left1;
    split( head, r + 1, left1, right );
    TreapNode* left;
    TreapNode* sumNode;
    split( left1, l, left, sumNode );
    int sum = sumNode->sum;
    left1 = Merge( left, sumNode );
    head = Merge( left1, right );
    return sum;
}

// отрезаем нужное кол-во эл-ов, слваем с двух сторон с деревом из одного эл-та
void IKTreap::Push( int index, int newKey ) {
    if( head == NULL ) {
        head = new TreapNode( newKey, rand() % MAX_PRIORITY );
        return;
    }

    TreapNode* left = NULL;
    TreapNode* right = NULL;
    split( head, index, left, right );

    TreapNode* nodeForInsert = new TreapNode( newKey, rand() % MAX_PRIORITY );
    TreapNode* newLeft = Merge( left, nodeForInsert );
    head = Merge( newLeft, right );
}

// вырезаем нужный эл-т, обновляем, вливаем обратно
void IKTreap::Assign( int index, int newKey ) {
    TreapNode* right;
    TreapNode* left1;
    split( head, index + 1, left1, right);
    TreapNode* left;
    TreapNode * mid;
    split(left1, index, left, mid );
    if (mid != NULL) {
        mid->key = newKey;
        postUpdate(mid);
    }
    left1 = Merge(left, mid);
    head = Merge(left1, right);
}

bool IKTreap::NextPermutation( int l, int r ) {
    // вырезаем дерево, в котором нужно сделать nextPerm
    TreapNode* right;
    TreapNode* left1;
    split( head, r + 1, left1, right);
    TreapNode* left;
    TreapNode * mid;
    split(left1, l, left, mid );
    bool ans = true;
    // если поддерево - не возрастающее - последняя перстановка - разворачиваем его
    if( mid->suffix == mid->C ) {
        mid->deferredReverse = !mid->deferredReverse;
        ans = false;
    } else {   // иначе
        // отрезаем постфикс
        TreapNode* postfix;
        TreapNode* unPostfix;
        split( mid, mid->C - mid->suffix, unPostfix, postfix );
        // элемент перед постфиксом - пивот
        TreapNode* pivot;
        split(unPostfix, unPostfix->C - 1, unPostfix, pivot);
        // разрезаем постфикс по ключу пивота
        TreapNode* leftPostfix;
        TreapNode* rightPostfix;
        keySplit( postfix, pivot->key, leftPostfix, rightPostfix );
        // отрезаем элемент, который меняем местами с пивотом
        TreapNode* swapPivot;
        if (leftPostfix != NULL) {
            split( leftPostfix, leftPostfix->C - 1, leftPostfix, swapPivot );
            std::swap( pivot, swapPivot );  // меняем пивот с нужным эл-ом местами
        // сливаем все обратно
        }
        leftPostfix = Merge( leftPostfix, swapPivot );
        postfix = Merge( leftPostfix, rightPostfix );
        postfix->deferredReverse = !postfix->deferredReverse;   // постфикс - разворачиваем
        unPostfix = Merge( unPostfix, pivot );
        mid = Merge( unPostfix, postfix );
    }
    // вливаем поддерево обратно
    postUpdate(mid);
    left1 = Merge(left, mid);
    head = Merge(left1, right);
    return ans;
}

// выполняем отложенный разворот - меняем местами детей,
// самое правое и самое левое значения, префикс и суффикс
void IKTreap::preUpdate( TreapNode* node ) {
    if( node == NULL )
        return;
    if( node->deferredReverse ) {
        std::swap(node->leftChild, node->rightChild);
        std::swap(node->leftmost, node->rightmost);
        std::swap(node->prefix, node->suffix);

        if(node->leftChild != NULL) {
            node->leftChild->deferredReverse = !node->leftChild->deferredReverse;
        }
        if(node->rightChild != NULL) {
            node->rightChild->deferredReverse = !node->rightChild->deferredReverse;
        }
        node->deferredReverse = false;
    }
}

//  обновление всех вспомогательных величин после обработки веришны
void IKTreap::postUpdate( TreapNode* node ) {
    if( node == NULL )
        return;
    // выполняем отложенные развороты в вершине и детях
    preUpdate( node );
    preUpdate(node->leftChild);
    preUpdate(node->rightChild);
    // обновляем поля без учета детей
    node->C = 1;
    node->sum = node->key;
    node->leftmost = node->key;
    node->rightmost = node->key;
    node->prefix = 1;
    node->suffix = 1;
    // обновляем поля, связанные с левым ребенком
    if( node->leftChild != NULL ) {
        node->C += node->leftChild->C;
        node->sum += node->leftChild->sum;

        node->prefix = node->leftChild->prefix;
        node->leftmost = node->leftChild->leftmost;
        if( node->leftChild->C == node->leftChild->prefix && node->leftChild->rightmost <= node->key )
            ++node->prefix;
    }
    // проверяем обновление префикса
    if( node->rightChild != NULL && node->prefix == node->C - node->rightChild->C
        && node->key <= node->rightChild->leftmost )
        node->prefix += node->rightChild->prefix;
    // обновляем поля, связанные с правым ребенком
    if( node->rightChild != NULL ) {
        node->C += node->rightChild->C;
        node->sum += node->rightChild->sum;

        node->suffix = node->rightChild->suffix;
        node->rightmost = node->rightChild->rightmost;
        if( node->rightChild->C == node->rightChild->suffix && node->rightChild->leftmost <= node->key )
            ++node->suffix;
    }
    // проверяем обновление суффикса
    if( node->leftChild != NULL && node->suffix == node->C - node->leftChild->C
        && node->key <= node->leftChild->rightmost )
        node->suffix += node->leftChild->suffix;

}

// отрезаем заданное кол-во эл-тов
void IKTreap::split( TreapNode* nodeForSplit, int number, TreapNode*& left, TreapNode*& right ) {
    if( nodeForSplit == NULL) {
        left = NULL;
        right = NULL;
        return;
    }

    preUpdate( nodeForSplit );

    int leftkey = LeftSonSize( nodeForSplit );

    if( leftkey >= number ) {
        split( nodeForSplit->leftChild, number, left, nodeForSplit->leftChild );
        right = nodeForSplit;
        postUpdate( right );
        postUpdate( left );
    } else {
        split( nodeForSplit->rightChild, number - leftkey - 1, nodeForSplit->rightChild, right );
        left = nodeForSplit;
        postUpdate( left );
        postUpdate( right );
    }
}

// сливаем два поддерева, как в обычном дек-ом дереве
IKTreap::TreapNode* IKTreap::Merge( TreapNode* left, TreapNode* right ) {
    if( left == NULL )
        return right;
    if( right == NULL )
        return left;

    if( left->priority > right->priority ) {
        preUpdate(left);
        left->rightChild = Merge( left->rightChild, right );
        postUpdate( left );
        return left;
    } else {
        preUpdate(right);
        right->leftChild = Merge( left, right->leftChild );
        postUpdate( right );
        return right;
    }
}

// не возрастающий постфикс - обраное дек. дерево по ключам. Его можно разрезать по ключу
void IKTreap::keySplit( TreapNode* nodeForSplit, int splitKey, TreapNode*& left, TreapNode*& right ) {
    if( nodeForSplit == NULL ) {
        left = NULL;
        right = NULL;
        return;
    }
    preUpdate( nodeForSplit );
    if ( nodeForSplit->key > splitKey ) {
        keySplit( nodeForSplit->rightChild, splitKey, nodeForSplit->rightChild, right );
        left = nodeForSplit;
        postUpdate( left );
        postUpdate( right );
        return;
    } else {
        keySplit( nodeForSplit->leftChild, splitKey, left, nodeForSplit->leftChild );
        right = nodeForSplit;
        postUpdate( left );
        postUpdate( right );
    }

}

void IKTreap::inOrder( TreapNode* node ) {
    if( node == NULL )
        return;
    inOrder( node->leftChild );
    std::cout << node->key << " ";
    inOrder( node->rightChild );
}

/*
void IKTreap::write() {
    std::cout << "treapArray:  ";
    inOrder( head );
    std::cout << std::endl;
};
*/

int IKTreap::LeftSonSize( TreapNode* node ) {
    if( node->leftChild == NULL )
        return 0;
    return node->leftChild->C;
}
