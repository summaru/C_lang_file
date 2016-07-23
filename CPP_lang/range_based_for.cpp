#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc,char* argv[])
{
		int numberlist[5] = {1,2,3,4,5};

		cout << "using for" << endl;

		for(int i = 0; i< 5; i++)
		{
				cout << numberlist[i] << endl;
		}

/*		cout << "using for each (VC++) << endl;
		
		for each(int i in numberlist)
		{
				cout << i << endl;
		}
*/

		cout <<"using range based for" << endl;

		for(auto i : numberlist)
		{
				cout << i << endl;
		}

		return 0;
}


