#include <iostream>
using namespace std;

void findMinMax(int x, int y, int z) {
    int minval=min(min(x, y), z);
    int maxval=max(max(x, y), z);

    cout<<"min-"<<minval<<", max-"<<maxval<<endl;
}
int main(int argc, char* argv[]) {
    if(argc != 4) {
        cout<<"Usage: ./program_name x y z"<<endl;
        return 1;
    }
    int x=atoi(argv[1]);
    int y=atoi(argv[2]);
    int z=atoi(argv[3]);
    findMinMax(x, y, z);
    return 0;
}
