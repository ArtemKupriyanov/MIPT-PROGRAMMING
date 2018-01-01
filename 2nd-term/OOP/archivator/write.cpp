#include "write.h"

#include <vector>
#include <memory.h>
#include <fstream>

using namespace std;

const int CONST_BUFFER_SIZE = 1024;

Write::Write(string file_name, bool is_arch)
    : _bits_count(0),
      _buffer_out_size(CONST_BUFFER_SIZE)
{
    _file_name_str = file_name;
    _file_name = new char[128];
    if (is_arch) {
        make_arch_name();
    } else {
        make_new_file_name();
    }
    _buffer_out = new char[_buffer_out_size];
    memset(_buffer_out, 0, _buffer_out_size);
    fout.open(_file_name);
    _file_is_open = fout.is_open();
}

Write::~Write() {
    fout.close();
    delete[] _buffer_out;
    delete[] _file_name;
}

void Write::make_new_file_name() {
    int i = _file_name_str.length() - 1;
    while (_file_name_str[i] != '.') {
        --i;
    }
    ++i;
    string file_without_ext(_file_name_str, 0, i - 1);
    string ext(_file_name_str, i, _file_name_str.length() - i);
    _file_name_str = file_without_ext + "_new." + ext;
    strcpy(_file_name, _file_name_str.c_str());
}


void Write::make_arch_name() {
    string ext = "arch";
    int i = _file_name_str.length() - 1;
    while (_file_name_str[i] != '.') {
        --i;
    }
    ++i;
    for (int j = 0; j < ext.length(); ++j) {
        _file_name_str[i + j] = ext[j];
    }
    strcpy(_file_name, _file_name_str.c_str());
}

void Write::WriteBit(unsigned char bit) {
    if (_bits_count + 1 > _buffer_out_size * 8) {
        FlushToFile();
    }
    if (bit > 0) {
        int byte_pos = _bits_count / 8;
        int bit_pos = _bits_count % 8;
        _buffer_out[byte_pos] |= (1 << (7 - bit_pos) );
    }
    _bits_count++;
}

void Write::WriteByte(unsigned char byte) {
    if (_bits_count + 1 > _buffer_out_size * 8) {
        FlushToFile();
    }
    int byte_pos = _bits_count / 8;
    int bit_pos = _bits_count % 8;
    char mask1 = byte >> bit_pos;
    char mask2 = byte << (8 - bit_pos);
    _buffer_out[byte_pos] |= mask1;
    _buffer_out[byte_pos + 1] |= mask2;
    _bits_count += 8;
}

void Write::FlushToFile() {
    int size = _bits_count / 8 + ( _bits_count % 8 != 0 );
    for (int i = 0; i < size; ++i) {
        int checking = (int)((unsigned char)_buffer_out[i]);
        fout << _buffer_out[i];
    }
    update_out();
}

void Write::update_out() {
    delete[] _buffer_out;
    _bits_count = 0;
    _buffer_out = new char[_buffer_out_size];
    memset(_buffer_out, 0, _buffer_out_size);
}
