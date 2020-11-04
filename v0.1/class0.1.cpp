#include "Header0.1.h"

using hrClock = std::chrono::high_resolution_clock;
std::mt19937 mt(static_cast<long unsigned int>(hrClock::now().time_since_epoch().count()));

void generate_users(vector<users>& us_vec){
	string n;
	string pk;
	int b;
	

		std::uniform_int_distribution<int> dist(1, 1000000);
	for (int i = 1; i <= 10; i++) {
		n = "vardas" + to_string(i);
		b = dist(mt);
		pk = to_string(b) + n;
		pk = hash(pk);
		users User(n, pk, (double)b);
		cout << User.get_name() << " " << User.get_pk() << " " << User.get_b() << endl;
		us_vec.push_back(User);
	}
}

void generate_trans(vector<transaction>& tr_vec, vector<users>& us_vec) {
		std::uniform_int_distribution<int> dist(0, 9);

		int rand1 = 0;
		int rand2 = 0;
		int s = 0;
		string us1;
		string us2;
		string trans_id;
	for (int i = 0; i < 10; i++) {
		do {
			rand1 = dist(mt);
			rand2 = dist(mt);
		} while (rand1 == rand2);
		do {
			std::uniform_int_distribution<int> dist(1, 1000000);
			int s = dist(mt);
		} while (us_vec[rand1].get_b() < s);
		us1 = us_vec[rand1].get_pk();
		us2 = us_vec[rand2].get_pk();
		trans_id = us1 + to_string(s) + us2;
		trans_id = hash(trans_id);
		transaction tr(trans_id, us1, us2, s);
		
		///cout << i << " " << tr.get_id() << "\n" << tr.get_user1() << "\n" << tr.get_user2() << "\n" << tr.get_sum() << endl;
		tr_vec.push_back(tr);
	}
}