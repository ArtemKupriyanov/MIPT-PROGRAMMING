#include <string>
#include <cstring>
#include <iostream>

#include "encode.h"
#include "decode.h"

using namespace std;

int main(int argc, char *argv[]) {
    string file_str;
    string way_str = "/home/artem/Desktop/Programming/archivator/";
    cout << "Write file name: ";
    cin >> file_str;
    way_str = way_str + file_str;
    Encode h1(way_str);
    h1.encoding();
    Decode h2(way_str);
    h2.decoding();
    return 0;
}
