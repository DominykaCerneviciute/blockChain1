#pragma once
#include <string>
#include <bitset>
#include <iostream>
#include <cmath>
#include <vector>
#include <ctime>
#include <fstream> 
#include <sstream>
#include <chrono>
#include <iomanip>
#include <random>
#include "stdlib.h"
#include <cstdlib>
#include <bitcoin/bitcoin.hpp>


using std::cout;
using std::string;
using std::bitset;
using std::endl;
using std::vector;
using std::hex;
using std::cin;
using std::to_string;





class users {
private:
	string name;
	string public_key;
	double balance;
public:
	users() { balance = 0; }
	users(string n, string pk, double b) { name = n; public_key = pk; balance = b; }
	string get_pk() { return public_key; }
	double get_b() { return balance; }
	string get_name() { return name; }
	void set_b(double b) { balance = b; }

};

class transaction {
private:
	string id;
	string user1;
	string user2;
	double sum;
	bool valid;
public:
	transaction() {};
	transaction(string id_, string us1, string us2, double s) { id = id_; user1 = us1; user2 = us2; sum = s; valid = true;}
	string get_id() { return id; }
	string get_user1() { return user1; }
	string get_user2() { return user2; }
	double get_sum() { return sum; }
	void set_valid(bool a) { valid = a; }
	bool get_valid() { return valid; }
};


class block {
private: 
	string prevBlockHash;
	string merkelRootHash;
	string version;
	int nonce;
	string difTarget;
	string timeStamp;
	vector<transaction> transactions;

public:
	block() {};
	block(string pbh, string ver, int non, string dt, string ts) { prevBlockHash = pbh; version = ver; nonce = non;
	difTarget = dt; timeStamp = ts; transactions.reserve(100); }
	void setMerkelHash(string hash) { merkelRootHash = hash; }
	void set_version(string v) { version = v; }
	void set_nonce(int n) { nonce = n; }
	string getPrevHash() { return prevBlockHash; }
	string getMerkelHash() { return  merkelRootHash; }
	string getVersion() { return version; }
	int getNonce() { return nonce; }
	string getDifTarget() { return difTarget; }
	string getTime() { return timeStamp; }
	transaction get_transaction(int i) { return transactions[i]; }
	int getsize() { return transactions.size(); }
	void removeTrans(int i) { transactions.erase(transactions.begin() + i); }
	void increaseNonce() { nonce = nonce + 1; }
	void push_back(transaction V) { transactions.push_back(V); }
};

// void gen_random(const int len, string c);
int ascii(char c);
char hex(string sh);
char bitwiseOr(char p, char k);
char bitwiseXor(char p, char k);
char bitwiseAnd(char p, char k);
void procesas(string& kzn, string hash, string& done);
void full(string& hashString1, string& hashString2, char (*fun)(char, char));
void test(string& pirmas, string& antras, string& done, string& myString, int& tokiepat, int& maziausiai, int& daugiausiai, int& vienodi);
void stringas(string& hashString, string& laikinas, char kazkas, int& sk);
void pildyti(string& hashString, vector<int>& ascii_values, int& k, vector<int>& count1, int& i);
void maisymas(vector<int> ascii_values, vector<int> count1, string& hashString1, string& hashString2, string& hashString3, string& hashString4);
string hash(string myString);
void generate_users(vector<users>& us_vec);
void generate_trans(vector<transaction>& tr_vec, vector<users>& us_vec);
void extrans(vector<users>& us_vec, block& blo, string prevHash, vector<transaction>& tr_vec);
bool mining(string& blockHash, vector<block>& vecOfBlocks, int firstNonce, int rand);
void findBlock(vector<block>& vecOfBlocks, vector<transaction>& tr_vec, vector<users>& us_vec);
bc::hash_digest create_merkle(bc::hash_list& merkle);
///void findBlock(block blo, vector<transaction>& tr_vec, vector<users>& us_vec);
///string merkleTree(block blo);
bool checkTransaction(vector<transaction>& tr_vec, int rand, vector<users>& us_vec);
void generate_block(vector<transaction>& tr_vec, string prevh, vector<users>& us_vec);

