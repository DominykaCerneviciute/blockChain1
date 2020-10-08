#include <string>
#include <bitset>
#include <iostream>
#include <cmath>
#include <vector>

using std::cout;
using std::string;
using std::bitset;
using std::endl;
using std::vector;
using std::hex;




int ascii(char c) {
	int d = 0;
	d = int(c);
	return d;
}

char hex(string sh) {
	if (sh == "0000") return '0';
	if (sh == "0001") return '1';
	if (sh == "0010") return '2';
	if (sh == "0011") return '3';
	if (sh == "0100") return '4';
	if (sh == "0101") return '5';
	if (sh == "0110") return '6';
	if (sh == "0111") return '7';
	if (sh == "1000") return '8';
	if (sh == "1001") return '9';
	if (sh == "1010") return 'a';
	if (sh == "1011") return 'b';
	if (sh == "1100") return 'c';
	if (sh == "1101") return 'd';
	if (sh == "1110") return 'e';
	if (sh == "1111") return 'f';
	else return 0;
}

void procesas(string& kzn, string hash, string& done) {
	for (std::size_t i = 0; i < kzn.size(); ++i) {
		hash.push_back(kzn[i]);
		if (hash.size() == 4)
		{
			char z = hex(hash);
			done.push_back(z);
			hash.clear();
		}
	}
}

char bitwiseOr(char p, char k) {
	if (p == '0' && k == '0') return '0';
	if (p == '1' && k == '0') return '1';
	if (p == '0' && k == '1') return '1';
	if (p == '1' && k == '1') return '1';
	else return 0;
}

char bitwiseXor(char p, char k) {
	if (p == '0' && k == '0') return '0';
	if (p == '1' && k == '0') return '1';
	if (p == '0' && k == '1') return '1';
	if (p == '1' && k == '1') return '0';
	else return 0;
}

char bitwiseAnd(char p, char k) {
	if (p == '0' && k == '0') return '0';
	if (p == '1' && k == '0') return '0';
	if (p == '0' && k == '1') return '0';
	if (p == '1' && k == '1') return '1';
	else return 0;
}

void stringas(string& hashString, string& laikinas, char kazkas, int& sk) {
	char v = bitwiseXor(hashString[sk], kazkas);
	if (sk <= 63) laikinas.push_back(v);
	if (sk == 64) {
		hashString.clear();
		sk = 0;
		for (int i = 0; i < 64; i++) {
			hashString.push_back(laikinas[i]);
		}
		laikinas.clear();
	}
}

void hash(string& myString, string& hashString1, string& hashString2, string& hashString3, string& hashString4, vector<int> count1, vector<int> ascii_values) {
	int k = 0;
	int i = 0;
	int random = 175;
	int sk = 5;
	int vz = 0;
	string done;
	string hash;
	string laikinas;
	int lol = 0;
	for (std::size_t i = 0; i < myString.size(); ++i) {
		bitset<8> b1(myString[i]);
		int d = b1.count(); //suskaiciuoja kiek yra 1
		count1.push_back(d);
		ascii_values.push_back(ascii(myString[i]));
		string kazkas = b1.to_string(); //pavercia i stringa


		for (int i = 0; kazkas[i] != '\0'; i++)
		{
			if (hashString1.size() < 64) {
				hashString1.push_back(kazkas[i]);
			}
			if (hashString1.size() == 64 && hashString2.size() < 64) {
				hashString2.push_back(kazkas[i]);
			}
			if (hashString1.size() == 64 && hashString2.size() == 64 && hashString3.size() < 64) {
				hashString3.push_back(kazkas[i]);
			}
			if (hashString1.size() == 64 && hashString2.size() == 64 && hashString3.size() == 64 && hashString4.size() < 64) {
				hashString4.push_back(kazkas[i]);
			}
			if (hashString1.size() == 64 && hashString2.size() == 64 && hashString3.size() == 64 && hashString4.size() == 64) {
				if (lol % 2 == 0) stringas(hashString2, laikinas, kazkas[i], vz);
				else stringas(hashString3, laikinas, kazkas[i], vz);
				vz++;
				if (vz == 64) {
					lol++;
					vz = 0;
				}
			}
		}

	}

	if (laikinas.size() < 64 && laikinas.size() != 0) {
		hashString1.clear();
		for (std::size_t i = 0; i < laikinas.size(); ++i) {
			hashString1.push_back(laikinas[i]);
		}
	}

	if (hashString1.size() == 64 && hashString2.size() == 64 && hashString3.size() == 64 && hashString4.size() == 64) {
		string hashString5;
		string hashString6;
		string hashString7;
		string hashString8;
		for (i = 0; i < 64; i++) {
			char g = bitwiseXor(hashString3[i], hashString2[i]);
			char l = bitwiseAnd(hashString1[i], hashString2[i]);
			char v = bitwiseOr(hashString4[i], hashString3[i]);
			char z = bitwiseOr(hashString1[i], hashString2[i]);
			hashString5.push_back(g);
			hashString6.push_back(l);
			hashString7.push_back(v);
			hashString8.push_back(z);
		}
		///cout << "alio" << hashString5 << endl << hashString6 << endl << hashString7 << endl << hashString8 << endl;
		hashString1.clear();
		hashString2.clear();
		hashString3.clear();
		hashString4.clear();

		for (i = 0; i < 64; i++) {
			char g = bitwiseOr(hashString7[i], hashString5[i]);
			char l = bitwiseXor(hashString6[i], hashString5[i]);
			char v = bitwiseAnd(hashString8[i], hashString7[i]);
			char z = bitwiseXor(hashString6[i], hashString8[i]);
			hashString1.push_back(g);
			hashString2.push_back(l);
			hashString3.push_back(v);
			hashString4.push_back(z);
		}
	}

	if (hashString1.size() < 64) {
		while (hashString1.size() < 64) {
			k += count1[i];
			int sum = (k * ascii_values[i]) + 175; ///nepamirst pritaikyti kai paduodamas tuscias failas
			bitset<8> b2(sum);
			int d = b2.count();
			count1.push_back(d);
			ascii_values.push_back(ascii(sum));
			string kazkas = b2.to_string();
			for (int i = 0; kazkas[i] != '\0'; i++) {
				if (hashString1.size() < 64) {
					hashString1.push_back(kazkas[i]);
				}
			}
			i++;
		}
	}
		if (hashString2.size() < 64) {
			while (hashString2.size() < 64) {
				if (hashString2.size() == 0) i--;
				k += count1[i];
				int sum = (k * ascii_values[i]) + 175; ///nepamirst pritaikyti kai paduodamas tuscias failas
				bitset<8> b2(sum);
				int d = b2.count();
				count1.push_back(d);
				ascii_values.push_back(ascii(sum));
				string kazkas = b2.to_string();
				for (int i = 0; kazkas[i] != '\0'; i++) {
					if (hashString2.size() < 64) {
						hashString2.push_back(kazkas[i]);
					}
				}
				i++;
			}
	}
		if (hashString3.size() < 64) {
			while (hashString3.size() < 64) {
				if (hashString3.size() == 0) i--;
				k += count1[i];
				int sum = (k * ascii_values[i]) + 175; ///nepamirst pritaikyti kai paduodamas tuscias failas
				bitset<8> b2(sum);
				int d = b2.count();
				count1.push_back(d);
				ascii_values.push_back(ascii(sum));
				string kazkas = b2.to_string();
				for (int i = 0; kazkas[i] != '\0'; i++) {
					if (hashString3.size() < 64) {
						hashString3.push_back(kazkas[i]);
					}
				}
				i++;
			}
		}
		if (hashString4.size() < 64) {
			while (hashString4.size() < 64) {
				if (hashString4.size() == 0) i--;
				k += count1[i];
				int sum = (k * ascii_values[i]) + 175; ///nepamirst pritaikyti kai paduodamas tuscias failas
				bitset<8> b2(sum);
				int d = b2.count();
				count1.push_back(d);
				ascii_values.push_back(ascii(sum));
				string kazkas = b2.to_string();
				for (int i = 0; kazkas[i] != '\0'; i++) {
					if (hashString4.size() < 64) {
						hashString4.push_back(kazkas[i]);
					}
				}
				i++;
			}
		}

		procesas(hashString1, hash, done);
		procesas(hashString2, hash, done);
		procesas(hashString3, hash, done);
		procesas(hashString4, hash, done);
	/*cout << "pirmas     " << hashString1 << endl;
	cout << "antras     " << hashString2 << endl;
	cout << "trecias    " << hashString3 << endl;
	cout << "ketvirtas  " << hashString4 << endl;*/
	cout << "hash       " << done << endl;

}

int main() {

	string hashString1;
	string hashString2;
	string hashString3;
	string hashString4;
	string myString = "apsaugokViespatie";
	//string myString = "nepadesCiaJauIrPatsPonasDievas:)";
	//string myString = "sdfd4bfd5h4f68hghfg2h4f54hs8dg4dfh21fg5jfg54hdf35g31df5hd3f8d4gh3fg5h4";
	vector<int> ascii_values;
	vector<int> count1;
	hash(myString, hashString1, hashString2, hashString3, hashString4, count1, ascii_values);

}