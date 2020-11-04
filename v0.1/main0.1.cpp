#include "Header0.1.h"







int main() {
	int a;
	int b;
	string c;
	int failas;
	string myString;
	//gen_random(10, "random11.txt");
	//gen_random(100, "random11.txt");
	//gen_random(500, "random11.txt");
	//gen_random(1000, "random11.txt");



	/*cout << "Ivesti ranka ar skaityti is failo?\n 1-Ranka 2-Is failo: ";
	cin >> a;
	if (a == 1) {
		cout << "Iveskite duomenis" << endl;
		cin >> myString;
		std::ofstream fd("random.txt");
		c = "random.txt";
		fd << myString;
		fd.close();
		hash(myString, c);
	}
	if (a == 2) {
		cout << "Generuoti atsitiktini faila? 1-Taip 2-Ne: ";
		cin >> b;
		cout << "Nurodykite failo pavadinima: ";
		cin >> c;
		if (b == 1) {
			cout << "keliu simboliu faila generuoti?: ";
			cin >> failas;
			gen_random(failas, c);
			hash(myString, c);
		}
		if (b == 2) {
			hash(myString, c);
		}
	}
	*/

	vector<users> us_vec;
	vector<transaction> tr_vec;
	us_vec.reserve(1000);
	tr_vec.reserve(10000);
	generate_users(us_vec);
	generate_trans(tr_vec, us_vec);
}