#include "Header2.h"

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

void pildyti( string& hashString, vector<int>& ascii_values, int& k, vector<int>& count1, int& i) {
	int asc_sum = 0;
	for (std::size_t i = 0; i < ascii_values.size(); i++) {
		asc_sum += ascii_values[i];
	}
	while (hashString.size() < 64) {
		k += count1[i];
		int sum = ((k * ascii_values[i] * asc_sum) + 175)/13; 
		bitset<8> b2(sum);
		int d = b2.count();
		count1.push_back(d);
		ascii_values.push_back(ascii(sum));
		string kazkas = b2.to_string();
		for (int i = 0; kazkas[i] != '\0'; i++) {
			if (hashString.size() < 64) {
				hashString.push_back(kazkas[i]);
			}
		}
		i++;
	}
}

void maisymas(vector<int> ascii_values, vector<int> count1, string& hashString1, string& hashString2, string& hashString3, string& hashString4) {
	int asc_sum = 0;
	int v = 7;
	int suma;
	int sum;
	string hashString10;
	for (std::size_t i = 0; i < ascii_values.size(); i++) {
		asc_sum += ascii_values[i];
	}
	asc_sum = (asc_sum * 152)/13;
	bitset<8> b10(asc_sum);
	suma = b10.count();
	string tmpr = b10.to_string();
	for (int j = 0; tmpr[j] != '\0'; j++) {
		hashString10.push_back(tmpr[j]);
	}
	while (hashString10.size() < 64) {
		sum = (asc_sum * suma + 784)/v;
		v += 3;
		bitset<8>b11(sum);
		tmpr = b11.to_string();
		suma += b11.count();
		asc_sum += ascii(sum);
		for (int j = 0; tmpr[j] != '\0'; j++) {
			hashString10.push_back(tmpr[j]);
		}
	}
	full(hashString1, hashString10, bitwiseXor);
	full(hashString4, hashString1, bitwiseAnd);
	full(hashString2, hashString4, bitwiseXor);
	full(hashString4, hashString10, bitwiseAnd);
	full(hashString3, hashString2, bitwiseOr);
	full(hashString4, hashString10, bitwiseAnd);
	full(hashString1, hashString3, bitwiseXor);
	full(hashString2, hashString10, bitwiseOr);
	full(hashString3, hashString4, bitwiseXor);
}

void hash(string& myString, string& hashString1, string& hashString2, string& hashString3, string& hashString4, vector<int> count1, vector<int> ascii_values) {
	int k = 0;
	int i = 0;
	int sk = 5;
	int vz = 0;
	string done;
	string hash;
	string laikinas;
	int lol = 0;
	if (myString.size() == 0) {
		int g = (169 * 475 + 462) / 3;
		myString.push_back(g);
	}
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

	if (hashString1.size() < 64) {
		pildyti(hashString1, ascii_values, k, count1, i);
	}

	if (hashString2.size() < 64) {
		pildyti(hashString2, ascii_values, k, count1, i);
	}
	if (hashString3.size() < 64) {
		pildyti(hashString3, ascii_values, k, count1, i);
	}
	if (hashString4.size() < 64) {
		pildyti(hashString4, ascii_values, k, count1, i);
	}
	maisymas(ascii_values,count1, hashString1, hashString2, hashString3, hashString4);
	full(hashString1, hashString3, bitwiseXor);
	full(hashString2, hashString3, bitwiseAnd);
	full(hashString3, hashString4, bitwiseXor);
	full(hashString4, hashString2, bitwiseOr);


	procesas(hashString1, hash, done);
	procesas(hashString2, hash, done);
	procesas(hashString3, hash, done);
	procesas(hashString4, hash, done);
	cout << "hash       " << done << endl;

}

int main() {

	string hashString1;
	string hashString2;
	string hashString3;
	string hashString4;
	//string myString = "";
	string myString = "apsaugokViespatie";
	//tring myString = "nepadesCiaJauIrPatsPonasDievas:)";
	//string myString = "sdfd4bfgsDGkJSDgsDhfghg2jghdsgsd1g5s4h5d1fhd2f7j169za5K4a1h2y1ys5rVj48sy4jtsy1j45xfd4h1z2df1g3f8d4gh3fg5h4";
	vector<int> ascii_values;
	vector<int> count1;
	hash(myString, hashString1, hashString2, hashString3, hashString4, count1, ascii_values);

}