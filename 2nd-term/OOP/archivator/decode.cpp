#include <string>
#include <stack>

#include "decode.h"
#include "read.h"
#include "write.h"

#include <limits.h>

const int CONST_BUFFER_SIZE = 1024;

using namespace std;

Decode::Decode(string file_name)
        : Write(file_name, false),
          Read(file_name, true) {
    _min_len_code = INT_MAX;
}

Decode::~Decode() {}

void Decode::makeHaffmanTree () {
    stack <Node*> st;
    int counter_new_symbols = 0;
    char bit;
    while (true) {
        if (counter_new_symbols == _count_of_word) {
            break;
        }
        bit = ReadBit();
        if (bit == 0) {
            char symbol = ReadByte();
            Node* element = new Node(symbol, 0);
            st.push(element);
            counter_new_symbols++;
        } else {
            Node* first = st.top();
            st.pop();
            Node* second = st.top();
            st.pop();
            Node* new_node = new Node(' ', 0);
            new_node->left = second;
            new_node->right = first;
            st.push(new_node);
        }
    }
    while (st.size() != 1) {
        bit = ReadBit();
        Node* first = st.top();
        st.pop();
        Node* second = st.top();
        st.pop();
        Node* new_node = new Node(' ', 0);
        new_node->left = second;
        new_node->right = first;
        st.push(new_node);
    }
    _Haffman_tree = st.top();
}

void Decode::readCountWord() {
    char tmp = ReadByte();
    _count_of_word = (int)((unsigned char)tmp) + 1;
    tmp = ReadByte();
    _bits_stay = (int)((unsigned char)tmp);
}

void Decode::decoding() {
    readCountWord();
    makeHaffmanTree();
    DFS(_Haffman_tree, "");
    read();
    fin.close();
    fout.close();
}

void Decode::DFS(Decode::Node* node, string way) {
    code += way;
    if ( is_list(node) == true) {
        _elements.push_back(node->symbol);
        _codes_elements.push_back(code);
        if (code.length() < _min_len_code) {
            _min_len_code = code.size();
        }
        code.erase(code.length() - 1, 1);
        return;
    }
    DFS(node->left, "0");
    DFS(node->right, "1");
    if (code.length() != 0) {
        code.erase(code.length() - 1, 1);
    }
}

bool Decode::is_list(Decode::Node* node) {
    if (node->left == NULL && node->right == NULL) {
        return true;
    }
    return false;
}

int Decode::find_code_in_arr(string code_now) {
    for (int i = 0; i < _codes_elements.size(); ++i) {
        if (_codes_elements[i] == code_now) {
            return i;
        }
    }
    return -1;
}

void Decode::read() {
    while (_end_file == false or _bits_stay != 0) {
        if ((_buffer_in_size != CONST_BUFFER_SIZE and _bits_count_read / 8 == _buffer_in_size - 1) or _buffer_in_size == -1) {
            _end_file = fin.eof();
        }
        code = "";
        while ( code.length() < _min_len_code) {
            if (ReadBit() == (char)0) {
                code += "0";
            } else {
                code += "1";
            }
            if ((_buffer_in_size != CONST_BUFFER_SIZE and _bits_count_read / 8 == _buffer_in_size - 1) or _buffer_in_size == -1) {
                _bits_stay--;
                if (_bits_stay == 0) {
                    break;
                }
            }
        }
        if (_bits_stay == 0) {
            break;
        }
        int place = find_code_in_arr(code);
        while (place == -1) {
            if (ReadBit() == (char)0) {
                code += "0";
            } else {
                code += "1";
            }
            place = find_code_in_arr(code);
            if ((_buffer_in_size != CONST_BUFFER_SIZE and _bits_count_read / 8 > _buffer_in_size - 1) or _buffer_in_size == -1) {
                _bits_stay--;
            }
            if (_bits_stay == 0) {
                break;
            }
        }
        WriteByte(_elements[place]);
        if (_bits_stay == 0) {
            break;
        }
    }
    FlushToFile();
    fin.close();
    fout.close();
}
