#include "abstractarray.h"
#include "iktreap.h"
#include "interfacetester.h"
#include "tester.h"
//#include "tester.h"

#include <iostream>

int main() {
    int commandNumber;
    int commandRange;
/*	IKTreap treap;
    treap.Push(0, 0);
    treap.Push(1, 1);
    treap.Push(2, 2);
    treap.Push(3, 3);
    treap.Push(4, 4);
    treap.write();
*/ /*	IKTreap t1;
    IKTreap t2;
    treap.Split(treap.head, 2, t1.head, t2.head);
    t1.write();
    t2.write();
    treap.head = treap.Merge( t1.head, t2.head );
    treap.write();
    std::cout << treap.Sum(1, 3) << std::endl;
    treap.write();
*/
    std::cin >> commandNumber >> commandRange;
    //InterfaceTester tester( commandNumber, commandRange );
    Tester tester( commandNumber, commandRange );
    return 0;
}
