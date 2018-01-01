#ifndef Read_H
#define Read_H

#include <string>
#include <vector>
#include <fstream>

using namespace std;

class Read {
public:
    Read(string file_name, bool is_arch);
    ~Read();

protected:
    unsigned char* _buffer_in;

    char* _file_name;

    string _file_name_str;

    ifstream fin;

    int _buffer_in_size;
    int _bits_count_read;

    bool _end_file;
    bool _file_open;

    char ReadByte();
    char ReadBit();

    void make_file_name();

    void read_next();

    void read_again();
};

#endif // Read_H
