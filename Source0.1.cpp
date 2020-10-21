#include "Header0.1.h"

void gen_random(const int len, string c) {
	std::ofstream fd;
	char v;
	fd.open(c, std::ios_base::app);
	static const char alphanum[] =
		"0123456789"
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz";
	int p = len / 2;
	srand((unsigned)time(NULL) * _getpid());
	for (int j = 0; j < 2500; j++) 
	{	string g;
		string k;
		for (int i = 1; i < len + 1; ++i)
		{
			if (i == p) {
				do {
					g += alphanum[rand() % (sizeof(alphanum) - 1)];
					k += alphanum[rand() % (sizeof(alphanum) - 1)];
				} while (g == k);
			}
			else {
				v = alphanum[rand() % (sizeof(alphanum) - 1)];
				g += v;
				k += v;
			}
		}
		fd << g << "\n" << k;
		fd << "\n";

	}
		fd.close();
	
}

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

string binary(char v) {
	if (v == '0') return "0000";
	if (v == '1') return "0001";
	if (v == '2') return "0010";
	if (v == '3') return "0011";
	if (v == '4') return "0100";
	if (v == '5') return "0101";
	if (v == '6') return "0110";
	if (v == '7') return "0111";
	if (v == '8') return "1000";
	if (v == '9') return "1001";
	if (v == 'a') return "1010";
	if (v == 'b') return "1011";
	if (v == 'c') return "1100";
	if (v == 'd') return "1101";
	if (v == 'e') return "1110";
	if (v == 'f') return "1111";
	else return "0";
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


void full(string& hashString1, string& hashString2, char (*fun)(char,char)) {
	string hashString5;
	for (int i = 0; i < 64; i++) {
		char l = fun(hashString1[i], hashString2[i]);
		hashString5.push_back(l);
	}
	hashString1.clear();

	for (int i = 0; i < 64; i++) {
		hashString1.push_back(hashString5[i]);
	}
}
