#include "Header.h"
#include <bits/stdc++.h>


using hrClock = std::chrono::high_resolution_clock;
std::mt19937 mt(static_cast<long unsigned int>(hrClock::now().time_since_epoch().count()));




string dif_targ = "00zsa65sf000000000000000000000000000000000000000000000000000000";
vector<block> blockChain;
string v = "34912576420"; //versija
vector<string> allHashes;

void generate_users(vector<users>& us_vec) {
	string name;
	string pk; //public key
	int balance;


	std::uniform_int_distribution<int> dist(1, 1000000);
	for (int i = 1; i <= 20; i++) { //1000
		name = "vardas" + to_string(i);
		balance = dist(mt);
		pk = to_string(balance) + name;
		pk = hash(pk);
		users User(name, pk, (double)balance);
		us_vec.push_back(User);
	}

	for (int o = 0; o < us_vec.size(); o++) {
		cout << us_vec[o].get_name() << " " << us_vec[o].get_pk() << " " << us_vec[o].get_b() << endl;
	}
}

void generate_trans(vector<transaction>& tr_vec, vector<users>& us_vec) {
	std::uniform_int_distribution<int> dist(0, 19);//999

	int rand1 = 0;
	int rand2 = 0;
	int s = 0;
	string us1;
	string us2;
	string trans_id;
	for (int i = 0; i < 100; i++) {//10000
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

	for (int t = 0; t < tr_vec.size(); t++) {
		cout << tr_vec[t].get_user1() << " " << tr_vec[t].get_user2() << " " << tr_vec[t].get_sum() << endl;
	}
	cout << "transactions done\n";
}



void extrans(vector<users>& us_vec, block& blo, string prevHash, vector<transaction>& tr_vec) {
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
			cout << "balansas pries pervedant:" << us_vec[v1].get_name() << " " << to_string(us_vec[v1].get_b()) << endl;
			cout << "balansas pries gaunant: " << us_vec[v2].get_name() << " " << to_string(us_vec[v2].get_b()) << endl;
			if ((us_vec[v1].get_b() - blo.get_transaction(i).get_sum()) >= 0) {
				us_vec[v1].set_b(us_vec[v1].get_b() - blo.get_transaction(i).get_sum());
				cout << "balansas pervedus: " << us_vec[v1].get_name() << " " << to_string(us_vec[v1].get_b()) << endl;
				us_vec[v2].set_b(us_vec[v2].get_b() + blo.get_transaction(i).get_sum());
				cout << "balansas gavaus: " << us_vec[v2].get_name() << " " << to_string(us_vec[v2].get_b()) << endl;
				cout << endl;
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
	//cout << "next prevHash  " << prevHash << endl;
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
	vector<int> howMany(5, 0);
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
				found = mining(blockHash, vecOfBlocks, firstNonce, rand);
			}
			if (found == true) break;
		}


	} while (found == false);

	//cout << "blockHash " << blockHash << endl; 
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
	allHashes.push_back(blockHash);
	extrans(us_vec, vecOfBlocks[rand], blockHash, tr_vec);

}

bc::hash_digest create_merkle(bc::hash_list& merkle){
	// Stop if hash list is empty or contains one element
	if(merkle.empty())
		return bc::null_hash;
	else if(merkle.size()==1)
		return merkle[0];// While there is more than 1 hash in the list, keep looping...
	while(merkle.size()>1){// If number of hashes is odd, duplicate last hash in the list.
		if(merkle.size()%2!=0)            
			merkle.push_back(merkle.back());// List size is now even.
		assert(merkle.size()%2==0);// New hash list.        
		bc::hash_list new_merkle;// Loop through hashes 2 at a time.
		for(auto it = merkle.begin(); it != merkle.end(); it +=2){// Join both current hashes together (concatenate).            
			bc::data_chunk concat_data(bc::hash_size *2);
			auto concat = bc::serializer<decltype(concat_data.begin())>(concat_data.begin());
	        concat.write_hash(*it);            
			concat.write_hash(*(it +1));// Hash both of the hashes.            
			bc::hash_digest new_root = bc::bitcoin_hash(concat_data);// Add this to the new list.            
			new_merkle.push_back(new_root);}// This is the new list.        
		merkle = new_merkle;// DEBUG output -------------------------------------        
		std::cout <<"Current merkle hash list:"<< std::endl;
		for(const auto& hash: merkle)            
			std::cout <<"  "<< bc::encode_base16(hash)<< std::endl;
		std::cout << std::endl;// --------------------------------------------------
	}// Finally we end up with a single item.
	return merkle[0];
}
/*
string merkleTree(block blo) {
	vector<string> hashes;
	vector<string> tmpr;
	string hashOfTwo;
	string hashOne;
	string hashTwo;
	//sudedami visu transakciju hash
	for (int i = 0; i < blo.getsize(); i++) {
		hashes.push_back(hash(blo.get_transaction(i).get_id()));
	}
	//cout << "firstHashSize: " << hashes.size() << endl; 
	while (hashes.size() != 1) {
		for (int j = 0; j < hashes.size(); j++) {
			int k = j + 1;
			if (j % 2 == 0) {
				hashTwo = hashes[j];
			}
			if (j % 2 != 0) {
				hashOne = hashes[j];
			}
			if (k == hashes.size() && j % 2 == 0 && hashes.size() % 2 != 0) {
				hashOne = hashTwo;
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
		//cout << "hashSize: " << hashes.size() << " ";
	}
	///cout << endl;  
	//grazinamas root
	if (hashes.size() == 1) {
		return hashes[0];
	}
	else return "0";
}
*/
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
	int sum = tr_vec[rand].get_sum();
	checkHash = tr_vec[rand].get_user1() + to_string(sum) + tr_vec[rand].get_user2();
	checkHash = hash(checkHash);

	//tikrinama ar siunciama suma nevirsija turimos sumos bei ar atitinka transakcijos hash
	if (tr_vec[rand].get_sum() < us_vec[whichUser].get_b() && checkHash == tr_vec[rand].get_id()) {
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
	if (tr_vec.size() >= 50) {//1000
		vector<block> vecOfBlocks;
		for (int i = 0; i < 5; i++) {
			std::uniform_int_distribution<int> dist(0, tr_vec.size() - 1);
			int deleted = 0;
			int rand = 0; //random skaicius
			transaction tmp; //laikinas
			bool validation = false;
			vector<int> added; //kurios transakcijos jau idetos
			added.reserve(100);
			std::time_t t = std::time(0);
			int n = 0; //random nonce reiksme
			//n = dist(mt);
			block blo(prevh, v, n, dif_targ, to_string(t));
			//pirmos transakcijos idejimas
			do {
				std::uniform_int_distribution<int> dist(0, tr_vec.size() - 1);
				rand = dist(mt);
				validation = checkTransaction(tr_vec, rand, us_vec);
				if (validation == true) {
					blo.push_back(tr_vec[rand]);
					added.push_back(rand);
				}
				else if (deleted < 50) {//100
					deleted++;
				}
			} while (validation == false);
			// Idedamos transakcijos i bloka, jei jau nebuvo ideta tokia pati
			for (int j = 101; j < 106; j++) { //200
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
				else if (deleted < 50) {
					j--;
					deleted++;
				}
			}

			///blo.setMerkelHash(merkleTree(blo));
			bc::hash_list tx_hashes;    
			for(int q = 0; q<blo.getsize(); q++){
				auto b = blo.get_transaction(q);
				char char_array[65];
				strcpy(char_array,b.get_id().c_str());
				tx_hashes.push_back(bc::hash_literal(char_array));
			}

			const bc::hash_digest merkle_root =create_merkle(tx_hashes);    
			auto root = bc::encode_base16(merkle_root);
			blo.setMerkelHash(root);
			// std::cout <<"Merkle Root Hash: "<< bc::encode_base16(merkle_root)<< std::endl;
			// std::cout << "Merkle Root Hash-2: " << bc::encode_hash(merkle_root) << std::endl;
			vecOfBlocks.push_back(blo);
		}
		findBlock(vecOfBlocks, tr_vec, us_vec);
	}
	else {
		/*	int equal = 0;
		for (int p = 0; p < blockChain.size(); p++) {
			for (int k = 0; k < blockChain.size(); k++) {
				if (blockChain[p].getPrevHash() == blockChain[k].getPrevHash() && p != k) equal++;
			}
		}
		cout << equal;*/
		const string lastHash = prevh;

		//cout << lastHash << endl; 
		cout << blockChain.size();
		for (int r = blockChain.size() - 1; r >= 0; r--) {
			cout << endl;
			cout << "Previous hash: " << blockChain[r].getPrevHash() << endl;
			cout << "Block hash: " << allHashes[r] << endl;
			cout << "Difficulty target: " << blockChain[r].getDifTarget() << endl;
			cout << "Nonce: " << blockChain[r].getNonce() << endl;
			cout << "Number of transactions: " << blockChain[r].getsize() << endl;
			cout << "Timestamp: " << blockChain[r].getTime() << endl;
			cout << "Version: " << blockChain[r].getVersion() << endl;
			cout << "Merkle root hash: " << blockChain[r].getMerkelHash() << endl;
			for (int g = 0; g < 5; g++) {
				cout << endl;
				cout << "siuntejas: " << blockChain[r].get_transaction(g).get_user1() << endl;
				for (int p = 0; p < us_vec.size(); p++) {
					if (us_vec[p].get_pk() == blockChain[r].get_transaction(g).get_user1()) {
						cout << us_vec[p].get_name() << endl;
					}
				}
				cout << "gavejas: " << blockChain[r].get_transaction(g).get_user2() << endl;
				for (int p = 0; p < us_vec.size(); p++) {
					if (us_vec[p].get_pk() == blockChain[r].get_transaction(g).get_user2()) {
						cout << us_vec[p].get_name() << endl;
					}
				}
				cout << "suma: " << blockChain[r].get_transaction(g).get_sum() << endl;
			}
			cout << endl;
		}

	}
}
