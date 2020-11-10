#include "Header.h"

using hrClock = std::chrono::high_resolution_clock;
std::mt19937 mt(static_cast<long unsigned int>(hrClock::now().time_since_epoch().count()));




string dif_targ = "00zsa65sf000000000000000000000000000000000000000000000000000000";
vector<block> blockChain;

void generate_users(vector<users>& us_vec){
	string name;
	string pk; //public key
	int balance; 
	

		std::uniform_int_distribution<int> dist(1, 1000000);
	for (int i = 1; i <= 1000; i++) {
		name = "vardas" + to_string(i);
		balance = dist(mt);
		pk = to_string(balance) + name;
		pk = hash(pk);
		users User(name, pk, (double)balance);
		us_vec.push_back(User);
	}

	/*for (int o = 0; o < us_vec.size(); o++) {
		cout << us_vec[o].get_name() << " " << us_vec[o].get_pk() << " " << us_vec[o].get_b() << endl;
	}*/
}

void generate_trans(vector<transaction>& tr_vec, vector<users>& us_vec) {
		std::uniform_int_distribution<int> dist(0, 999);

		int rand1 = 0;
		int rand2 = 0;
		int s = 0;
		string us1;
		string us2;
		string trans_id;
	for (int i = 0; i < 10000; i++) {
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
		
		tr_vec.push_back(tr);
	}

	/*for (int t = 0; t < tr_vec.size(); t++) {
		cout << tr_vec[t].get_user1() << " " << tr_vec[t].get_user2() << " " << tr_vec[t].get_sum() << endl;
	}*/
	cout << "transactions done\n";
}



void extrans(vector<users>& us_vec, block& blo, string prevHash, vector<transaction>& tr_vec) {
	users U;
	vector<int> del;
	for (int i = 0; i < blo.getsize(); i++) {
		int v1 = -1;
		int v2 = -1;
		string h = blo.get_transaction(i).get_user1();
		string v = blo.get_transaction(i).get_user2();
		//randami du user, kuriu turimus balansus reiks atnaujinti 
		for (int j = 0; j < us_vec.size(); j++) {
			if (us_vec[j].get_pk() == h) v1 = j;
			if (us_vec[j].get_pk() == v) v2 = j;

			if (v1 >= 0 && v2 >= 0) break;
		}
			//transakciju ivykdymas
			if (v1 >= 0 && v2 >= 0) {
				//cout << us_vec[v1].get_name() << " " << us_vec[v1].get_b() << endl;
				if ((us_vec[v1].get_b() - blo.get_transaction(i).get_sum()) >= 0) {
					us_vec[v1].set_b(us_vec[v1].get_b() - blo.get_transaction(i).get_sum());
					//cout << us_vec[v1].get_name() << " " << us_vec[v1].get_b() << endl;

					//cout << us_vec[v2].get_name() << " " << us_vec[v2].get_b() << endl;
					us_vec[v2].set_b(us_vec[v2].get_b() + blo.get_transaction(i).get_sum());
					//cout << us_vec[v2].get_name() << " " << us_vec[v2].get_b() << endl;
				}
				else
				{
					blo.get_transaction(i).set_valid(false);
				}
			}
			v.clear();
			h.clear();

	}
	blockChain.push_back(blo);
	generate_block(tr_vec, prevHash, us_vec);
}


bool mining(string& blockHash, vector<block>& vecOfBlocks, int firstNonce, int rand) {
	//tikrinama ar hash tinkantis
	firstNonce += 100;
	do {
		blockHash.clear();
		blockHash = to_string(vecOfBlocks[rand].getNonce()) + vecOfBlocks[rand].getPrevHash() + vecOfBlocks[rand].getMerkelHash()
			+ vecOfBlocks[rand].getVersion() + vecOfBlocks[rand].getDifTarget() + vecOfBlocks[rand].getTime();
		blockHash = hash(blockHash);
		if (blockHash >= vecOfBlocks[rand].getDifTarget() && firstNonce == vecOfBlocks[rand].getNonce()) return false;
		vecOfBlocks[rand].increaseNonce();
	} while (blockHash >= vecOfBlocks[rand].getDifTarget());

	return true;
}


void findBlock(vector<block>& vecOfBlocks, vector<transaction>& tr_vec, vector<users>& us_vec) {
	string blockHash;
	transaction T;
	transaction G;
	std::uniform_int_distribution<int> dist(0, 4);
	//pirma karta hashuojama
	int counter = 0;
	int rand = 0;
	vector<int> howMany(5,0);
	bool found = false;
	do {
		counter++;
		for (int q = 0; q < 5; q++) {
			rand = dist(mt);
			while (howMany[rand] >= counter)
			{
				rand = dist(mt);
			}

			if (howMany[rand] < counter) {
				int firstNonce = vecOfBlocks[rand].getNonce();
				howMany[rand]++;
				found = mining(blockHash, vecOfBlocks, firstNonce,rand);
			}
			if (found == true) break;
		}
		

	} while (found == false);


	//Istrinamos idetos i bloka transakcijos
	if (blockHash < vecOfBlocks[rand].getDifTarget()) {
		for (int l = 0; l < vecOfBlocks[rand].getsize(); l++) {
			T = vecOfBlocks[rand].get_transaction(l);
			for (int z = 0; z < tr_vec.size(); z++) {
				G = tr_vec[z];
				if (T.get_id() == G.get_id()) {
					tr_vec.erase(tr_vec.begin() + z);
					break;
				}
			}
			
		}
	}
	extrans(us_vec, vecOfBlocks[rand],blockHash, tr_vec);


}


string markleTree(block blo) {
	vector<string> hashes;
	vector<string> tmpr;
	string hashOfTwo;
	string hashOne;
	string hashTwo;
	//sudedami visu transakciju hash
	for (int i = 0; i < blo.getsize(); i++) {
		hashes.push_back(hash(blo.get_transaction(i).get_id()));
	}

	while (hashes.size() != 1) {
		for(int j = 0; j<hashes.size(); j++){
		
			if (j % 2 != 0) {
				hashOne = hashes[j];
			}
			if (j % 2 == 0) {
				hashTwo = hashes[j];
			}
			//hash'uojama po dvi transakcijas(hash'us)
			if (hashOne.size() != 0 && hashTwo.size() != 0) {
				hashOfTwo = hashOne + hashTwo;
				hashOfTwo = hash(hashOfTwo);
				tmpr.push_back(hashOfTwo);
				hashOne.clear();
				hashTwo.clear();
			}
		}
		hashes = tmpr;
		while (tmpr.size() != 0) {
			tmpr.erase(tmpr.begin());
		}
	}
	//grazinamas root
	if (hashes.size() == 1) {
		return hashes[0];
	}
	else return "0";
}

bool checkTransaction(vector<transaction>& tr_vec, int rand, vector<users>& us_vec) {
	string user1 = tr_vec[rand].get_user1();
	string user2 = tr_vec[rand].get_user2();
	string checkHash;
	int whichUser = 0;
	//randamas user pagal transakcija
	for (int i = 0; i < us_vec.size(); i++) {
		if (user1 == us_vec[i].get_pk()) {
			whichUser = i;
		}
	}
	//hashuojama transakcijos informacija
	checkHash = tr_vec[rand].get_user1() + to_string(tr_vec[rand].get_sum()) + tr_vec[rand].get_user2();
	checkHash = hash(checkHash);

	//tikrinama ar siunciama suma nevirsija turimos sumos bei ar atitinka transakcijos hash
	if (tr_vec[rand].get_sum() < us_vec[whichUser].get_b() && checkHash != tr_vec[rand].get_id()) {
		return true;
	}

	//jei kazkas is dvieju salygu netenkinama, transakcija pasalinama is transakciju pool'o
	else
	{
		tr_vec.erase(tr_vec.begin() + rand);
		return false;
	}
}


void generate_block(vector<transaction>& tr_vec, string prevh, vector<users>& us_vec) {
	if(tr_vec.size() >= 500){
		vector<block> vecOfBlocks;
		for(int i = 0; i<5; i++){
		std::uniform_int_distribution<int> dist(0, tr_vec.size()-1);
		int rand = 0; //random skaicius
		transaction tmp; //laikinas
		bool validation = false; 
		vector<int> added; //kurios transakcijos jau idetos
		added.reserve(100);
		std::time_t t = std::time(0);
		string v = "34912576420"; //versija
		int n = 0; //random nonce reiksme
		//n = dist(mt);
		block blo(prevh, v, n, dif_targ , to_string(t));
		//pirmos transakcijos idejimas
		do {
			std::uniform_int_distribution<int> dist(0, tr_vec.size() - 1);
			rand = dist(mt);
			validation = checkTransaction(tr_vec, rand, us_vec);
			if (validation == true) {
				blo.push_back(tr_vec[rand]);
				added.push_back(rand);
			}
		} while (validation == false);
		// Idedamos transakcijos i bloka, jei jau nebuvo ideta tokia pati
		for (int i = 0; i < 99; i++) {
			std::uniform_int_distribution<int> dist(0, tr_vec.size() - 1);
			validation = false;
			bool newTransaction = false;
				while (newTransaction == false) {
					int repeat = 0;
					rand = dist(mt);
					for (int b = 0; b < added.size(); b++) {
						if (rand == added[b]) repeat++;

					}
					if (repeat == 0) newTransaction = true;
				}
			validation = checkTransaction(tr_vec, rand, us_vec);
			if (validation == true) {
				added.push_back(rand);
				blo.push_back(tr_vec[rand]);
			}
		}
	/*	for (int y = 0; y < blo.getsize(); y++) {
			cout << blo.get_transaction(y).get_sum() << endl;
		}
		*/
		blo.setMarkelHash(markleTree(blo));
		vecOfBlocks.push_back(blo);
		//findBlock(blo, tr_vec, us_vec);
		}
		findBlock(vecOfBlocks, tr_vec, us_vec);
	}
	/*else {
		int equal = 0;
		for (int p = 0; p < blockChain.size(); p++) {
			for (int k = 0; k < blockChain.size(); k++) {
				if (blockChain[p].getPrevHash() == blockChain[k].getPrevHash() && p != k) equal++;
			}
		}
		cout << equal;
	}*/
}
