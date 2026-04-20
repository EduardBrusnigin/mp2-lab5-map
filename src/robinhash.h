// Hash table ("Хеш Робин Гуд")
// Brusnigin
#include "hash1.h"

using std::vector, std::pair, std::cout, std::endl;


template <typename TKey, typename TValue>
class RobinTable : public OAHashTable<TKey, TValue> {
public:
	using OAHashTable<TKey, TValue>::OAHashTable;


	void Insert(const TKey& key, const TValue& value) {
		int dist = 0;
		int ind = this->h1(key);
		
		auto new_entry = this->Table[0];
		new_entry.status = 1;
		new_entry.key = key;
		new_entry.value = value;
		
		while (true) {
			if (this->Table[ind].status != 1) {
				this->Table[ind] = new_entry;
				this->N++;
				if ((double)this->N / this->M > 0.5) {
					this->Rehashing();
				}
				return;
			}
			
			if (this->Table[ind].key == key) {
				this->Table[ind].value = value;
				return;
			}
			
			int old_ideal = this->h1(this->Table[ind].key);
			int old_dist = (ind - old_ideal + this->M) % this->M;
			
			if (dist < old_dist) {
				std::swap(this->Table[ind], new_entry);
			}
			
			dist++;
			ind = (this->h1(key) + dist) % this->M;
			
			if (dist == this->M) {
				throw "Hash table is overflow!";
			}
		}
	}
};
