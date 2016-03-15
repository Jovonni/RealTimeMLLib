#include <iostream>
#include <fstream> 
using namespace std;
int main(int argc, char **argv) {
    ofstream file("data.dat");
    file << "#x y" << endl;
    for(int i=0; i<10; i++){
        file << i << ' ' << i*i << endl;
    }
    file.close();
    return 0;
}
