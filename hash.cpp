#include "Header.h"



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

void pildyti(string& hashString, vector<int>& ascii_values, int& k, vector<int>& count1, int& i) {
	int asc_sum = 0;
	if (ascii_values.size() == 0) ascii_values.push_back(ascii(514));
	for (std::size_t j = 0; j < ascii_values.size(); j++) {
		asc_sum += ascii_values[j];
	}
	while (hashString.size() < 64) {
		if (count1.size() == 0) {
			bitset<8>b12('67');
			int d = b12.count();
			count1.push_back(d);
		}
		else k += count1[i];
		int sum = ((k * ascii_values[i] * asc_sum) + 175) / 13;
		bitset<8> b2(sum);
		int d = b2.count();
		count1.push_back(d);
		ascii_values.push_back(ascii(sum));
		string kazkas = b2.to_string();
		for (int p = 0; kazkas[p] != '\0'; p++) {
			if (hashString.size() < 64) {
				hashString.push_back(kazkas[p]);
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
	asc_sum = (asc_sum * 152) / 13;
	bitset<8> b10(asc_sum);
	suma = b10.count();
	string tmpr = b10.to_string();
	for (int j = 0; tmpr[j] != '\0'; j++) {
		hashString10.push_back(tmpr[j]);
	}
	while (hashString10.size() < 64) {
		sum = (asc_sum * suma + 784) / v;
		v += 3;
		//int sum2 = sum >> 1;
		bitset<8>b11(sum);
		tmpr = b11.to_string();
		suma += b11.count();
		asc_sum += ascii(sum);
		for (int k = 0; tmpr[k] != '\0'; k++) {
			hashString10.push_back(tmpr[k]);
		}
	}
	full(hashString1, hashString10, bitwiseXor);
	full(hashString4, hashString10, bitwiseOr);
	full(hashString3, hashString10, bitwiseAnd);
	full(hashString2, hashString10, bitwiseOr);

}
string hash(string myString
	///, string c
) {

	vector<double>kiek;
	/*std::stringstream buffer;
	std::ifstream open_f(c);
	buffer << open_f.rdbuf();
	open_f.close();*/
	string pirmas;
	string antras;
	string pirmas1;
	string antras1;
	int maziausiai = 64; int maziausiai2 = 256;
	int daugiausiai = 0; int daugiausiai2 = 0;
	int count = 0;
	int skaiciavimai = 0;
	int vienodi = 0; int vienodi2 = 0;
	int tokiepat = 0; int tokiepat2 = 0;

	int vienodasStringas = 0;
	string pirmas2;
	string antras2;
	//std::getline(buffer, myString);
	//auto start = std::chrono::high_resolution_clock::now();

	//do {
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

		if (myString.size() == 0) {
			int g = (169 * 475 + 462) / 3;
			myString.push_back(g);
		}
		for (std::size_t j = 0; j < myString.size(); ++j) {
			bitset<8> b1(myString[j]);
			int d = b1.count(); //suskaiciuoja kiek yra 1
			count1.push_back(d);
			ascii_values.push_back(ascii(myString[j]));
			string kazkas = b1.to_string(); //pavercia i stringa


			for (int z = 0; kazkas[z] != '\0'; z++)
			{
				if (hashString1.size() < 64) {
					hashString1.push_back(kazkas[z]);
				}
				if (hashString1.size() == 64 && hashString2.size() < 64) {
					hashString2.push_back(kazkas[z]);
				}
				if (hashString1.size() == 64 && hashString2.size() == 64 && hashString3.size() < 64) {
					hashString3.push_back(kazkas[z]);
				}
				if (hashString1.size() == 64 && hashString2.size() == 64 && hashString3.size() == 64 && hashString4.size() < 64) {
					hashString4.push_back(kazkas[z]);
				}
				if (hashString1.size() == 64 && hashString2.size() == 64 && hashString3.size() == 64 && hashString4.size() == 64) {
					if (lol % 2 == 0) stringas(hashString1, laikinas, kazkas[z], vz);
					else stringas(hashString3, laikinas, kazkas[z], vz);
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


		procesas(hashString1, hash, done);
		procesas(hashString2, hash, done);
		procesas(hashString3, hash, done);
		procesas(hashString4, hash, done);


		string hashString;
		hashString.append(hashString1);
		hashString.append(hashString2);
		hashString.append(hashString3);
		hashString.append(hashString4);

		///test(pirmas, antras, done, myString, tokiepat, maziausiai, daugiausiai, vienodi);
		//test(pirmas2, antras2, hashString, myString, tokiepat2, maziausiai2, daugiausiai2, vienodi2);

		//std::cout << "hash " << done << endl;

		count++;
		return done;
	///} while (std::getline(buffer, myString));

	/*double kiekSkiriasi = 100.0 - ((vienodi * 100) / ((count / 2 - tokiepat) * 64));
	double min = 100.0 - (maziausiai * 100 / 64);
	double max = 100.0 - (daugiausiai * 100 / 64);
	cout << "hex avg " << std::setprecision(3) << kiekSkiriasi << endl;
	cout << "hex max " << std::setprecision(3) << min << endl;
	cout << "hex min " << std::setprecision(3) << max << endl;

	double kiekSkiriasi2 = 100.0 - ((vienodi2 * 100) / ((count / 2 - tokiepat2) * 256));
	double min2 = 100.0 - (maziausiai2 * 100 / 256);
	double max2 = 100.0 - (daugiauiai2 * 100 / 256);
	cout << "bin avg " << std::setprecision(3) << kiekSkiriasi2 << endl;
	cout << "bin max " << std::setprecision(3) << min2 << endl;
	cout << "bin min " << std::setprecision(3) << max2 << endl;*/

	//auto end = std::chrono::high_resolution_clock::now(); // Stabdyti
	//std::chrono::duration<double> diff = end - start; // Skirtumas (s)
	//cout << diff.count() << endl;
	///cout << "vienodu: " << vienodi << endl;
}