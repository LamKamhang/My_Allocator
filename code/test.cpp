#include "util.h"
#include <memory>
#include <vector>
#include <iostream>
#include "myAllocator.hpp"

using namespace std;
using namespace JJ;

int main(int argc, char const *argv[])
{
    int times = 150000;
    double t = 0;

    
    for (int i = 0; i < times; ++i)
    {
        timer();
        vector<int, myAllocator<int> > v1(50);
        t += timer();
    }
    cout << times << ": " << t << "s" << endl;

    return 0;
}
