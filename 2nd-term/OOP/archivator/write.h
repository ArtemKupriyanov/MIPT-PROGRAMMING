#ifndef WRITE_H
#define WRITE_H

#include <iostream>
#include <fstream>
#include <vector>
#include <memory.h>

using namespace std;

class Write {
public:
    Write(string file_name, bool is_arch);
    ~Write();

protected:
    char* _buffer_out;

    string _file_name_str;
    char* _file_name;
    int _buffer_out_size;
    int _bits_count;

    bool _file_is_open;

    ofstream fout;

    void WriteBit(unsigned char bit);
    void WriteByte(unsigned char byte);
    void FlushToFile();


    void update_out();

    void make_arch_name();
    void make_new_file_name();
};

#endif // WRITE_H
