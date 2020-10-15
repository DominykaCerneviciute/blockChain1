#include "Header2.h"
#include "stdlib.h"



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
	if (ascii_values.size() == 0) ascii_values.push_back(ascii(514));
	for (std::size_t i = 0; i < ascii_values.size(); i++) {
		asc_sum += ascii_values[i];
	}
	while (hashString.size() < 64) {
		if (count1.size() == 0) {
			bitset<8>b12('67');
			int d = b12.count();
			count1.push_back(d);}
		else k += count1[i];
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
	full(hashString4, hashString10, bitwiseOr);
	full(hashString3, hashString10, bitwiseAnd);
	full(hashString2, hashString10, bitwiseOr);

}

void hash(string myString) {

		
		std::stringstream buffer;
		std::ifstream open_f("test1.txt");
		buffer << open_f.rdbuf();
		open_f.close();
		string pirmas;
		string antras;
		string pirmas1;
		string antras1;
		int count = 1;
		int vienodi = 0;
		//auto start = std::chrono::high_resolution_clock::now();
		while (std::getline(buffer, myString)) {
			
			string done;

			string hashString1;
			string hashString2;
			string hashString3;
			string hashString4;

			vector<int> ascii_values;


			vector<int> count1;
			int k = 0;
			int i = 0;
			int sk = 5;
			int vz = 0;

			string hash;
			string laikinas;
			int lol = 0;
			
			

			cout << count << endl;
			//cout << myString << endl;
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
			maisymas(ascii_values, count1, hashString1, hashString2, hashString3, hashString4);
			full(hashString1, hashString3, bitwiseXor);
			full(hashString2, hashString3, bitwiseAnd);
			full(hashString3, hashString4, bitwiseXor);
			full(hashString4, hashString2, bitwiseXor);
			/*full(hashString1, hashString2, bitwiseAnd);
			full(hashString2, hashString4, bitwiseOr);
			full(hashString3, hashString1, bitwiseXor);
			full(hashString4, hashString2, bitwiseOr);*/


			procesas(hashString1, hash, done);
			procesas(hashString2, hash, done);
			procesas(hashString3, hash, done);
			procesas(hashString4, hash, done);

			/*cout << hashString1 << endl;
			cout << hashString2 << endl;
			cout << hashString3 << endl;
			cout << hashString4 << endl;*/

			std::ofstream fr;
			fr.open("test1rez.txt", std::ios_base::app); // append instead of overwrite
			fr << "hash       " << done << "\n";
			done.clear();
			fr.close();
			cout << "hash       " << done << "\n";
			if (pirmas.size() == 0 && antras.size() == 0) {
				pirmas = done;
				pirmas1 = myString;
				done.clear();
			}
			if (pirmas.size() != 0 && antras.size() == 0) {
				antras = done;
				antras1 = myString;
				done.clear();
			}
			if (pirmas.size() != 0 && antras.size() != 0) {
				if (pirmas == antras && pirmas1 != antras1) {
					vienodi++;
				}
				pirmas1.clear(); antras1.clear(); pirmas.clear(); antras.clear();
			}
			count++;

		}
		//auto end = std::chrono::high_resolution_clock::now(); // Stabdyti
		//std::chrono::duration<double> diff = end - start; // Skirtumas (s)
		//cout << diff.count() << endl;
		cout << "vienodu: " << vienodi << endl;
}

int main() {
	int a;
	int b;
	int failas;
	string myString;
	//gen_random(10);
	//gen_random(100);
	//gen_random(500);
	//gen_random(1000);
	cout << "Ivesti ranka ar skaityti is failo?\n 1-Ranka 2-Is failo: ";
	cin >> a;
	if (a == 1) {
		cout << "Iveskite duomenis" << endl;
		cin >> myString;
		//std::ofstream fd("abc2rez.txt");
		//fd << myString;
		//fd.close();
		hash(myString);
	}
	if (a == 2) {
		cout << "Generuoti atsitiktini faila? 1-Taip 2-Ne: ";
		cin >> b;
		if (b == 1) {
			cout << "keliu simboliu faila generuoti?: ";
			cin >> failas;
			gen_random(failas);
			hash(myString);
		}
		if (b == 2) {
			hash(myString);
		}
	}

}