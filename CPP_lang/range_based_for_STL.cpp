#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
using namespace std;

int main(int argc,char* argv[])
{
		vector<int> numberlist;
		numberlist.push_back(1);
		numberlist.push_back(2);
		numberlist.push_back(3);

		for (auto i : numberlist)
		{
				cout << i << endl;
		}
		cout << endl;
		cout << "range based for - unordered_map" << endl;

		unordered_map<int, string> numstring;
		numstring.insert(make_pair<int , string>(1, "1"));
		numstring.insert(make_pair<int , string>(2, "2"));
		numstring.insert(make_pair<int , string>(3, "3"));

		for (auto i : numstring)
		{
				cout << "key : " << i.first <<", value : " << i.second << endl;
		}

		cout << endl;

		return 0;
}
