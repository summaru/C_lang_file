#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int main(int argc,char* argv[])
{
		vector<int> moneys;
		moneys.push_back(100);
		moneys.push_back(1200);
		moneys.push_back(3000);

		int totalmoney1 = 0;
		int totalbigmoney = 0;

		for_each(moneys.begin(),moneys.end(), [&totalmoney1, &totalbigmoney](int money) {
						totalmoney1 += money;
						if(money > 1000) totalbigmoney += money;
						});

		cout << "total money1:" << totalmoney1 << endl;
		cout << "total big money :" << totalbigmoney << endl;

		return 0;
}
		
