#include "encode.h"

#include <vector>

#include "encode.h"
#include "read.h"
#include "write.h"
#include "encode.h"

using namespace std;

const int CONST_BUFFER_SIZE = 1024;

Encode::Encode(string file_name)
        : Read(file_name, false),
          Write(file_name, true)
{
    _arr_of_frequency.resize(256, 0);
    _bits_stay = 0;
}

Encode::~Encode() {}

void Encode::encoding() {
    frequency_counter();
    read_again();
    makeHeap();
    int size = _heap.size();
    makeHaffmanTree(size);
    _HaffmanTree = _heap[0];
    DFS(_HaffmanTree, "");
    countBits();
    flushCountAlphabet();
    flushCodeHaffmanTree();
    encode_file();
    fin.close();
    fout.close();
}

void Encode::frequency_counter() {
    int place;
    do {
        for (int i = 0; i < _buffer_in_size; ++i) {
            place = (int)((unsigned char)ReadByte());
            _arr_of_frequency[place]++;
        }
        read_next();
    } while (!fin.eof());
}

int Encode::leftChildren(int i) {
    return 2*i + 1;
}

int Encode::rightChildren(int i) {
    return 2*i + 2;
}

void Encode::siftDown(int i, int& size) {
    int lowest = i;
    int left_ch = leftChildren(i);
    int right_ch = rightChildren(i);
    if (left_ch < size && _heap[left_ch]->frequency < _heap[i]->frequency) {
        lowest = left_ch;
    }
    if (right_ch < size && _heap[right_ch]->frequency < _heap[lowest]->frequency) {
        lowest = right_ch;
    }
    if (lowest != i) {
        std::swap(_heap[i], _heap[lowest]);
        siftDown(lowest, size);
    }
}

void Encode::buildHeap() {
    int size = _heap.size();
    for (int i = size/2; i >= 0; --i) {
        siftDown(i, size);
    }
}

Encode::Node* Encode::extractMin(int& size) {
    Node* ans = _heap[0];
    std::swap(_heap[0], _heap[size - 1]);
    size--;
    siftDown(0, size);
    return ans;
}

void Encode::make_and_push_NewNode(int& size) {
    Node* first = extractMin(size);
    Node* second = _heap[0];
    unsigned char tmp = ' ';
    Node* result = new Node(tmp, first->frequency + second->frequency);
    result->left = first;
    result->right = second;
    _heap[0] = result;
    siftDown(0, size);
}

void Encode::makeHeap() {
    for (int i = 0; i < _arr_of_frequency.size(); ++i) {
        if (_arr_of_frequency[i] == 0) {
            continue;
        } else {
            Node* element = new Node(char(i), _arr_of_frequency[i]);
            _heap.push_back(element);
        }
    }
    _count_of_word = _heap.size() - 1;
    buildHeap();
}

void Encode::makeHaffmanTree(int& size) {
    while (size != 1) {
        make_and_push_NewNode(size);
    }
}


bool Encode::is_list(Encode::Node* node) {
    if (node->left == NULL && node->right == NULL) {
        return true;
    }
    return false;
}

void Encode::DFS(Encode::Node* node, string way) {
    code += way;
    if ( is_list(node) == true) {
        _code_Haffman_tree.push_back("is0");
        string tmp;
        tmp = node->symbol;
        _code_Haffman_tree.push_back(tmp);
        _elements.push_back(node->symbol);
        _codes_elements.push_back(code);
        code.erase(code.length() - 1, 1);
        return;
    }
    DFS(node->left, "0");
    DFS(node->right, "1");
    if (code.length() != 0) {
        code.erase(code.length() - 1, 1);
    }
    _code_Haffman_tree.push_back("is1");
}

void Encode::flushCodeHaffmanTree() {
    for (int i = 0; i < _code_Haffman_tree.size(); ++i) {
        if (_code_Haffman_tree[i] == "is0") {
            WriteBit((unsigned char)0);
        } else if (_code_Haffman_tree[i] == "is1") {
            WriteBit((unsigned char)1);
        } else {
            WriteByte(_code_Haffman_tree[i][0]);
        }
    }
}

void Encode::flushCountAlphabet() {
    unsigned char byte = (unsigned char)_count_of_word;
    WriteByte(byte);
    byte = (unsigned char)_bits_stay;
    WriteByte(byte);
}

void Encode::countBits() {
    for (int i = 0; i < _code_Haffman_tree.size(); ++i) {
        if (_code_Haffman_tree[i] == "is0" or _code_Haffman_tree[i] == "is1") {
            _bits_stay++;
            _bits_stay %= 8;
        }
    }
    read_again();
    char symbol;
    string code;
    while (_end_file == false) {
        symbol = ReadByte();
        if (fin.eof()) {
            _end_file = true;
            break;
        }
        int i;
        for (i = 0; i < _elements.size(); ++i) {
            if (_elements[i] == symbol) {
                break;
            }
        }
        code  = _codes_elements[i];
        _bits_stay += code.length();
        _bits_stay %= 8;
    }
}

void Encode::encode_file() {
    read_again();
    char symbol;
    string code;
    while (_end_file == false) {
        symbol = ReadByte();
        if (fin.eof() and _bits_count_read / 8 > _buffer_in_size) {
            _end_file = true;
            break;
        }
        int i;
        for (i = 0; i < _elements.size(); ++i) {
            if (_elements[i] == symbol) {
                break;
            }
        }
        code  = _codes_elements[i];
        for (int i = 0; i < code.length(); ++i) {
            if (code[i] == '0') {
                WriteBit((char)0);
            } else {
                WriteBit((char)1);
            }
        }
    }
    FlushToFile();
}
