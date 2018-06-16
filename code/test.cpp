#include "util.h"
#include <memory>
#include <vector>
#include <iostream>

using namespace std;

int main(int argc, char const *argv[])
{
    int times = 150000;
    double t = 0;

    
    for (int i = 0; i < times; ++i)
    {
        timer();
        vector<int> v1(5000);
        t += timer();
    }
    cout << times << ": " << t << "s" << endl;

    return 0;
}
