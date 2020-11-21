#include "Header.h"



string firstHash = hash("1");


// Merkle Root Hash
bc::hash_digest create_merkle(bc::hash_list& merkle)
{
	// Stop if hash list is empty or contains one element
	if (merkle.empty())
		return bc::null_hash;
	else if (merkle.size() == 1)
		return merkle[0];
	// While there is more than 1 hash in the list, keep looping...
	while (merkle.size() > 1)
	{
		// If number of hashes is odd, duplicate last hash in the list.
		if (merkle.size() % 2 != 0)
			merkle.push_back(merkle.back());
		// List size is now even.
		assert(merkle.size() % 2 == 0);
		// New hash list.
		bc::hash_list new_merkle;
		// Loop through hashes 2 at a time.
		for (auto it = merkle.begin(); it != merkle.end(); it += 2)
		{
			// Join both current hashes together (concatenate).
			bc::data_chunk concat_data(bc::hash_size * 2);
			auto concat = bc::serializer<
				decltype(concat_data.begin())>(concat_data.begin());
			concat.write_hash(*it);
			concat.write_hash(*(it + 1));
			// Hash both of the hashes.
			bc::hash_digest new_root = bc::bitcoin_hash(concat_data);
			// Add this to the new list.
			new_merkle.push_back(new_root);
		}
		// This is the new list.
		merkle = new_merkle;
		// DEBUG output -------------------------------------
		cout << "Current merkle hash list:" << std::endl;
		for (const auto& hash : merkle)
			cout << " " << bc::encode_base16(hash) << std::endl;
		cout << std::endl;
		// --------------------------------------------------
	}
	// Finally we end up with a single item.
	return merkle[0];
}



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
	/*
	vector<users> us_vec;
	vector<transaction> tr_vec;
	us_vec.reserve(1000);
	tr_vec.reserve(10000);
	generate_users(us_vec);
	generate_trans(tr_vec, us_vec);
	generate_block(tr_vec, firstHash,us_vec);
	*/
	bc::hash_list tx_hashes{ {
 bc::hash_literal("8c14f0db3df150123e6f3dbbf30f8b955a8249b62ac1d1ff16284aefa3d06d87"),
 bc::hash_literal("fff2525b8931402dd09222c50775608f75787bd2b87e56995a7bdd30f79702c4"),
 bc::hash_literal("6359f0868171b1d194cbee1af2f16ea598ae8fad666d9b012c8ed2b79a236ec4"),
 bc::hash_literal("e9a66845e05d5abc0ad04ec80f774a7e585c6e8db975962d069a522137b80c1d"),
 } };
	const bc::hash_digest merkle_root = create_merkle(tx_hashes);
	std::cout << "Merkle Root Hash: " << bc::encode_base16(merkle_root) << std::endl;
	// std::cout << "Merkle Root Hash-2: " << bc::encode_hash(merkle_root) << std::endl;
	return 0;
}