#ifndef DECODE_H
#define DECODE_H

#include <stack>
#include <string>
#include <vector>
#include <string>

#include "write.h"
#include "read.h"

using namespace std;

class Decode : public Read, public Write {
public:
    Decode(string file_name);
    ~Decode();
    void decoding();

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

    int _count_of_word;
    int _bits_stay;

    Node* _Haffman_tree;
    vector <string> _codes_elements;
    vector <char> _elements;
    string code;
    int _min_len_code;

    void makeHaffmanTree();
    void readCountWord();
    void DFS(Decode::Node* node, string way);
    int find_code_in_arr(string code_now);
    bool is_list(Decode::Node* node);
    void read();
};

#endif // DECODE_H
