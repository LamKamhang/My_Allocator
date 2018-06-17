#include "Header/util.h"
#include <memory>
#include <vector>
#include <iostream>
#include "Header/myAllocator.hpp"

using namespace std;
using namespace JJ;

int main(int argc, char const *argv[])
{
    int times = 150000;
    double t = 0;
	double t2 = 0;
    
	for (int i = 0; i < times; ++i)
	{
        int index = i% 32;
		timer();
		vector<int, myAllocator<int> > v1(index);
		t += timer();
		timer();
		vector<int> v2(index);
		t2 += timer();
	}
    cout << times << ": " << t << "s" << endl;
	cout << times << ": " << t2 << "s" << endl;

    return 0;
}
