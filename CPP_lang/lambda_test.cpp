#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

class user
{
		public:
			user() : m_die(false) {}
			~user() {}


			void setindex(int index) {m_index = index;}
			int getindex() {return m_index;}
			void setdie() { m_die = true;}
			bool isdie() {return m_die;}



		private:
			int m_index;
			bool m_die;
};

int main(int argc, char* argv[])
{
		vector<user> users;
		user tuser1;
		tuser1.setindex(1);
		users.push_back(tuser1);

		user tuser2;
		tuser2.setindex(2);
		tuser2.setdie();
		users.push_back(tuser2);
		user tuser3;
		tuser3.setindex(3);
		users.push_back(tuser3);

		auto iter = find_if(users.begin(), users.end(), [](user& tuser) -> bool {return true == tuser.isdie();});

		cout << "found die user index :" << iter->getindex() << endl;
		return 0;
}
