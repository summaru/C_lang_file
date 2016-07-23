#include <iostream>
#include <vector>
using namespace std;

int main(int argc, char* argv[])
{
		vector<int>numberlist;
		numberlist.push_back(1);
		numberlist.push_back(2);
		numberlist.push_back(3);

		for(auto i : numberlist)
		{
				cout << i <<" * 10:" ;
				i *= 10;
				cout << i << endl;
		}

		for(auto i : numberlist)
		{
				cout << i <<  " ";
		}
		cout << endl << endl;

		for(auto &i : numberlist)
		{
				cout << i <<" * 10:";
				i *= 10;
				cout << i << endl;
		}

		for(auto i : numberlist)
		{
				cout << i << " " ;
		}
		cout << endl << endl;

		return 0;
}

