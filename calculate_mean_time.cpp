#include <fstream>
#include <iostream>
#include <string>
using namespace std;

int main(int argc, char const *argv[])
{
	ifstream fin("RESULT.txt");

	if (!fin.is_open())
	{
		cout << "Fail to open " << "RESULT.txt" << endl; 
		exit(1);
	}

	double sum = 0;
	double item = 0;
	string line;
	int count = 0;

	while (!fin.eof() && !fin.fail() && !fin.bad())
	{
		getline(fin, line);
		getline(fin, line);
		fin >> line >> line >> item >> line >> line;
		sum += item;
		count++;
		getline(fin, line);
	}
	cout << count << endl;

	ofstream fout("MEAN.txt");
	if (!fout.is_open())
	{
		cout << "Fail to open " << "MEAN.txt" << endl; 
		exit(1);
	}

	fout << "## mean time: " << (sum/count) << "s ##" << endl;
	return 0;
}