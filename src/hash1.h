// Hash table ("С открытой адресацией")
// Brusnigin
#include <vector>
#include <utility>
#include <iostream>

using std::vector, std::pair, std::cout, std::endl;


template <typename TKey, typename TValue>
class OAHashTable {
protected:
	struct Entry {
		signed char status;  // 0 - свободна, -1 - удалена, 1 - занята

		TKey key;
		TValue value;

		Entry() : status(0) {}
	};

	int N, M;
	Entry* Table;


	int h1(const TKey& k) {
		int hash = k % M;

		if (hash < 0) hash += M;
			return hash;
	}

	int h2(const TKey& k) {
		int hash = k % (M - 1);

		if (hash < 0) hash += (M - 1);
			return 1 + hash;
	}


	int Hash(const TKey& k, int i) {
		return (h1(k) + i*h2(k))%M;
	}


	void Rehashing() {
		const int primes[] = {17, 37, 79, 163, 331, 673, 1361, 2729, 5471, 10949, 21911, 43853, 87719, 175447};

		int old_M = M;
		Entry* new_Table;

		for (int i = 0; i < 13; i++)
			if (primes[i] == M)
				M = primes[i + 1];

		new_Table = new Entry[M];

		for (int i = 0; i < old_M; i++) {
			if (Table[i].status == 1) {
				int j = 0;
				int ind;

				do {
					ind = Hash(Table[i].key, j);

					if ((new_Table[ind].status == -1) || (new_Table[ind].status == 0)) {
						new_Table[ind].key = Table[i].key;
						new_Table[ind].value = Table[i].value;
						new_Table[ind].status = 1;
						break;
					}

					else
						j = j + 1;

				} 
				while (j != M);
			}
		}

		delete[] Table;
		Table = new_Table;
	}

	int SearchIndex(const TKey& key) {
		int i = 0;
		int ind;

		do {
			ind = Hash(key, i);

			if (Table[ind].status == 0)
				return -1;

			if (Table[ind].status == 1 && Table[ind].key == key)
				return ind;

			i = i + 1;
		} 
		while (i != M);

		return -1;
	}
	
public:
	OAHashTable() : M(17), N(0) {
		Table = new Entry[M];
	}


	OAHashTable(const vector<pair<TKey, TValue>>& vec) : M(17), N(0) {
		Table = new Entry[M];

		for (const auto& pair : vec) {
			Insert(pair.first, pair.second);
		}
	}


	~OAHashTable() {
		delete[] Table;
	}


	void Insert(const TKey& key, const TValue& value) {
		int i = 0;

		do {
			int ind = Hash(key, i);

			if (Table[ind].status == 1 && Table[ind].key == key) {
				Table[ind].value = value;
				return;
			}

			if ((Table[ind].status == -1) || (Table[ind].status == 0)) {
				Table[ind].key = key;
				Table[ind].value = value;
				Table[ind].status = 1;
				N++;
				
				if ((double) N / M > 0.5)
					Rehashing();

				return;
			}

			else
				i = i + 1;
		} 
		while (i != M);

		throw "Hash table is overflow!";
	}


	TValue& Search(const TKey& key) {
		int ind = SearchIndex(key);

		if (ind != -1)
			return Table[ind].value;

		throw "No entry with this key";
	}


	void Delete(const TKey& key) {
		int ind = SearchIndex(key);

		if (ind != -1) {
			Table[ind].status = -1;
			N--;
		}

		else
			throw "No entry with this key";
	}


	void Print() const {
		for (int i = 0; i < M; i++) {
			if (Table[i].status == 1) {
				cout << "[" << Table[i].key << ", " << Table[i].value << "]" << endl;
			}
		}
	}


	bool is_hash_table() {
		if (M <= 0 || N < 0 || N > M || Table == nullptr)
			return false;

		if ((double)N / M > 0.5)
			return false;

		int used = 0;

		for (int i = 0; i < M; i++) {
			if (Table[i].status != 0 && Table[i].status != -1 && Table[i].status != 1)
				return false;

			if (Table[i].status == 1)
				used++;
		}

		if (used != N)
			return false;


		for (int i = 0; i < M; i++) {
			if (Table[i].status == 1) {
				const TKey& key = Table[i].key;
				int j = 0;
				bool correct_pos = false;

				do {
					int ind = Hash(key, j);

					if (ind == i) {
						correct_pos = true;
						break;
					}

					if (Table[ind].status == 0)
						break;

					j++;

				} 
				while (j != M);

				if (!correct_pos)
					return false;
			}
		}

		return true;
	}
};
