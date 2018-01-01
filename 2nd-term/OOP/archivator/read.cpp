#include "read.h"
#include <assert.h>

#include <memory.h>

const int CONST_BUFFER_SIZE = 1024;

Read::Read(string file_name, bool is_arch)
        : _bits_count_read(0),
          _end_file(false),
          _buffer_in_size(0)
{
    _file_name_str = file_name;
    _file_name = new char[128];
    if (is_arch) {
        make_file_name();
    } else {
        strcpy(_file_name, _file_name_str.c_str());
    }
    fin.open(_file_name);
    _file_open = fin.is_open();
    _buffer_in = new unsigned char[CONST_BUFFER_SIZE];
    char tmp[1];
    int i = 0;
    while (fin.eof() == false and i != CONST_BUFFER_SIZE) {
        fin.read(tmp, 1);
        _buffer_in[i] = (unsigned char)tmp[0];
        i++;
    }
    if (fin.eof()) {
        i--;
    }
    _buffer_in_size = i;
}

void Read::make_file_name() {
    string ext = ".arch";
    int i = _file_name_str.length() - 1;
    while (_file_name_str[i] != '.') {
        --i;
    }
    ++i;
    string file_name_without_ext(_file_name_str, 0, i - 1);
    _file_name_str = file_name_without_ext + ext;
    strcpy(_file_name, _file_name_str.c_str());
}

Read::~Read() {
    fin.close();
    delete[] _buffer_in;
    delete[] _file_name;
}

char Read::ReadBit() {
    if (_bits_count_read / 8 > _buffer_in_size - 1) {
        read_next();
    }
    int bit_pos = _bits_count_read % 8;
    int byte_pos = _bits_count_read / 8;
    if (bit_pos == 0) {
        unsigned char answ = _buffer_in[byte_pos] >> 7;
        _bits_count_read++;
        return answ;
    }
    unsigned char answ = _buffer_in[byte_pos] << bit_pos;
    answ = answ >> 7;
    _bits_count_read++;
    return answ;
}

char Read::ReadByte() {
    if (_bits_count_read / 8 > _buffer_in_size - 1) {
        read_next();
    }
    int bit_pos = _bits_count_read % 8;
    int byte_pos = _bits_count_read / 8;
    if (_bits_count_read % 8 == 0) {
        unsigned char answ = _buffer_in[byte_pos];
        _bits_count_read += 8;
        return answ;
    }
    unsigned char mask1 = _buffer_in[byte_pos] << bit_pos;
    unsigned char mask2 = _buffer_in[byte_pos + 1] >> (8 - bit_pos);
    unsigned char answ = mask1 | mask2;
    _bits_count_read += 8;
    return answ;
}

void Read::read_next() {
    delete[] _buffer_in;
    _buffer_in = new unsigned char[CONST_BUFFER_SIZE];
    char tmp[1];
    int i = 0;
    while (fin.eof() == false and i != CONST_BUFFER_SIZE) {
        fin.read(tmp, 1);
        _buffer_in[i] = (unsigned char)tmp[0];
        i++;
    }
    if (fin.eof()) {
        i--;
    }
    _buffer_in_size = i;
    _bits_count_read = 0;
}

void Read::read_again() {
    _buffer_in_size = 0;
    _bits_count_read = 0;
    _end_file = false;
    _buffer_in = new unsigned char[CONST_BUFFER_SIZE];
    fin.close();
    fin.open(_file_name);
    _file_open = fin.is_open();
}
