#ifndef ENCODE_H
#define ENCODE_H

#include <vector>
#include <string>

#include "read.h"
#include "write.h"

using namespace std;

class Encode : public Read, public Write {
public:
    Encode(string file_name);
    ~Encode();

    void encoding();

private:
    struct Node {
    public:
        Node(unsigned char symbol_, int frequency_)
                : symbol(symbol_),
                  frequency(frequency_),
                  left(NULL),
                  right(NULL) {}

        Node* left;
        Node* right;
        unsigned char symbol;
        int frequency;
    };

    vector <int> _arr_of_frequency;
    vector <Node*> _heap;
    Node* _HaffmanTree;

    string code;

    vector <string> _codes_elements;
    vector <char> _elements;

    vector <string> _code_Haffman_tree;
    int _count_of_word;
    int _bits_stay;

    int leftChildren(int i);
    int rightChildren(int i);

    void siftDown(int i, int& size);

    void buildHeap();
    void makeHeap ();

    Node* extractMin(int& size);
    void make_and_push_NewNode(int& size);

    void makeHaffmanTree(int& size);

    bool is_list(Node* node);

    void DFS(Node* node, string way);

    void flushCodeHaffmanTree();
    void flushCountAlphabet();
    void countBits();

    void encode_file();
    void frequency_counter();
};

#endif // ENCODE_H
