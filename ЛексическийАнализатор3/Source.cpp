#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <iterator>
#include "analyzer.h"
#include "Hashtable.h"

using namespace std;
HashTable hassh(10);

void main() {
    string s;
    ifstream ifs("C://e//input.txt");

    if (ifs.is_open())
    {
        s.assign((istreambuf_iterator<char>(ifs.rdbuf())), istreambuf_iterator<char>());
        cout << s << endl;
        ifs.close();
    }
    else cerr << "Unable to open file" << endl;
    cout << endl;
    analyzer G(s);
    G.scan(hassh);
    int intf;

    hassh.displayHash();
}