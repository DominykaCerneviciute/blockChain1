#include "Header.h"

using hrClock = std::chrono::high_resolution_clock;
std::mt19937 mt(static_cast<long unsigned int>(hrClock::now().time_since_epoch().count()));


string dif_targ = "00zsa65sf000000000000000000000000000000000000000000000000000000";
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
	for (int i = 0; i < 20; i++) {
		do {
			rand1 = dist(mt);
			rand2 = dist(mt);
		} while (rand1 == rand2);
		do {
		    std::uniform_int_distribution<int> dist(1, 1000000);
			s = dist(mt);
		} while (us_vec[rand1].get_b() < s);
		//cout << s << endl;
		us1 = us_vec[rand1].get_pk();
		us2 = us_vec[rand2].get_pk();
		trans_id = us1 + to_string(s) + us2;
		trans_id = hash(trans_id);
		transaction tr(trans_id, us1, us2, s);
		
		///cout << i << " " << tr.get_id() << "\n" << tr.get_user1() << "\n" << tr.get_user2() << "\n" << tr.get_sum() << endl;
		tr_vec.push_back(tr);
	}
}


void extrans(vector<users>& us_vec, block& blo) {
	users U;
	vector<int> del;
	int v1 = -1;
	int v2 = -1;
	for (int i = 0; i < blo.getsize(); i++) {
		
		string h = blo.get_transaction(i).get_user1();
		string v = blo.get_transaction(i).get_user2();

		for (int j = 0; j < us_vec.size(); j++) {
			if (us_vec[j].get_pk() == h) v1 = j;
			if (us_vec[j].get_pk() == v) v2 = j;

			if (v1 >= 0 && v2 >= 0) break;
		}



			if (v1 >= 0 && v2 >= 0) {
		
				cout << us_vec[v1].get_name() << " " << us_vec[v1].get_b() << endl;
				if ((us_vec[v1].get_b() - blo.get_transaction(i).get_sum()) >= 0) {
					us_vec[v1].set_b(us_vec[v1].get_b() - blo.get_transaction(i).get_sum());
				cout << us_vec[v1].get_name() << " " << us_vec[v1].get_b() << endl;

				cout << us_vec[v2].get_name() << " " << us_vec[v2].get_b() << endl;
					us_vec[v2].set_b(us_vec[v2].get_b() + blo.get_transaction(i).get_sum());
				cout << us_vec[v2].get_name() << " " << us_vec[v2].get_b() << endl;

				}
				else
					del.push_back(i);
			}
	

			v.clear();
			h.clear();

	}

	if (del.size() > 0) {
		for (int z = 0; z < del.size(); z++) {
			blo.removeTrans(del[z]);
		}
	}

}




void findBlock(block blo, vector<transaction>& tr_vec, vector<users>& us_vec) {
	string blockHash;
	string prevBlockHash;
	transaction T;
	transaction G;


	bool a = false;
	int i = blo.getNonce();
	blockHash = to_string(blo.getNonce()) + blo.getPrevHash() + blo.getMerkelHash() + blo.getVersion() + blo.getDifTarget() + blo.getTime();
	blockHash = hash(blockHash);
	while (blockHash >= blo.getDifTarget()) {
		blockHash.clear();
		blo.increaseNonce();
		blockHash = to_string(blo.getNonce()) + blo.getPrevHash() + blo.getMerkelHash() + blo.getVersion() + blo.getDifTarget() + blo.getTime(); 
		blockHash = hash(blockHash);
		i++;
	} 



	if (blockHash < blo.getDifTarget()) {
		prevBlockHash = blockHash;
		for (int l = 0; l < blo.getsize(); l++) {
			T = blo.get_transaction(l);
			for (int z = 0; z < tr_vec.size(); z++) {
				G = tr_vec[z];
				if (T.get_id() == G.get_id()) {
					tr_vec.erase(tr_vec.begin() + z);
					break;
				}
			}
			
		}
	}

	extrans(us_vec, blo);


}




void generate_block(vector<transaction>& tr_vec, string prevh, vector<users>& us_vec) {
	std::uniform_int_distribution<int> dist(0, 19);
	int rand = 0;
	string markel;
	transaction tmp;
	std::vector<int>::iterator it;
	vector<int> a;
	a.reserve(100);
	rand = dist(mt);
	a.push_back(rand);
	std::time_t t = std::time(0);
	string v = "34912576420";
	int n = 0;
	n = dist(mt);
	block blo(prevh, v, n, dif_targ , to_string(t));
	blo.push_back(tr_vec[rand]);
	// Idedamos transakcijos
	for (int i = 0; i < 9; i++) {
		bool q = false;
			while (q == false) {
				int r = 0;
				rand = dist(mt);
				for (int b = 0; b < a.size(); b++) {
					if (rand == a[b]) r++;

				}
				if (r == 0) q = true;
			}
	
		a.push_back(rand);
		blo.push_back(tr_vec[rand]);
	}

	for (int k = 0; k < 10; k++) {
		tmp = blo.get_transaction(k);
		markel += tmp.get_id();
	 }
	// Papildyty*
	blo.setMarkelHash(markel);	
	findBlock(blo, tr_vec, us_vec);
}
