#ifndef IKTREAP_H
#define IKTREAP_H

#include "abstractarray.h"
#include <algorithm>

class IKTreap : public AbstractArray {
    struct TreapNode {
        TreapNode();
        TreapNode( int newKey, int newPriority ) {
            key = newKey;
            priority = newPriority;
            C = 1;
            leftChild = NULL;
            rightChild = NULL;

            sum = newKey;

            leftmost = newKey;
            rightmost = newKey;
            deferredReverse = false;
            prefix = 1;
            suffix = 1;
        }

        ~TreapNode() {
            delete leftChild;
            delete rightChild;
        }

        int key;    // ключ
        int priority;   // приоритет
        int C;  // кол-во эл-ов в поддереве
        TreapNode* leftChild;
        TreapNode* rightChild;

        int sum;    // сумма в поддереве

        int leftmost;   // значение самого левого эл-та в поддереве
        int rightmost;  // значение самого правого эл-та в поддереве
        bool deferredReverse;   // отложеный разворот
        int prefix; // длинна нестрого возрастающего префикса
        int suffix; // длинна нестрого убывающего постфикса
    };
public:
    IKTreap();
    IKTreap( int key, int priority );
    ~IKTreap();
    virtual int Sum( int l, int r );    // сумма на подотрезке
    virtual void Push( int index, int newKey ); // добавление в i-ую позицию
    virtual void Assign( int index, int newKey );   // обновление i-ого эл-та
    virtual bool NextPermutation( int l, int r );
//  void write();

private:
    TreapNode* head;    // указатель на корень
    static void preUpdate( TreapNode* node );   // выполнение отложенного разворота
    static void postUpdate( TreapNode* node );  // обновление всех вспомогательных величин
    static void split( TreapNode* nodeForSplit, int number, TreapNode*& left, TreapNode*& right );  // отрезание number эл-ов
    static void keySplit( TreapNode* nodeForSplit, int splitKey, TreapNode*& left, TreapNode*& right ); // разрезание нестрого убывающего постфикса по ключу
    static TreapNode* Merge( TreapNode* left, TreapNode* right );   // слияние
    static int LeftSonSize( TreapNode* node );  // кол-во эл-ов в поддереве левого сына
    int MAX_PRIORITY;   // максимальный приоритет
    static void inOrder( TreapNode* node );
};

#endif // IKTREAP_H
