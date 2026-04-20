#include <vector>
#include <list>
#include <functional>

template<typename K, typename V>
class Hash_Table {
private:
    struct Node {
        K key;
        V value;
        Node(const K& k, const V& v) : key(k), value(v) {}
    };
    std::vector<std::list<Node>> HT;
    size_t filled;
    size_t sz;
    const double acc = 0.75;

    size_t Hash(const K& key) const
    {
        return std::hash<K>{}(key) % sz;
    }

    void Rehash()
    {
        size_t old_sz = sz;
        sz *= 2;
        std::vector<std::list<Node>> new_HT(sz);
        for (size_t i = 0; i < old_sz; i++)
        {
            for (typename std::list<Node>::iterator iter = HT[i].begin(); iter != HT[i].end(); iter++)
            {
                size_t new_index = std::hash<K>{}(iter->key) % sz;
                new_HT[new_index].push_back(*iter);
            }
        }
        HT = std::move(new_HT);
    }

public:
    Hash_Table(size_t zero_sz = 16) :HT(zero_sz), filled(0), sz(zero_sz) {}

    void Insert(const K& key, const V& value)
    {
        if (static_cast<double>(filled) / sz > acc)
        {
            Rehash();
        }
        size_t index = Hash(key);
        std::list<Node>& iHT = HT[index];

        for (typename std::list<Node>::iterator iter = iHT.begin(); iter != iHT.end(); iter++)
        {
            if (iter->key == key)
            {
                iter->value = value;
                return;
            }
        }

        iHT.push_front(Node(key, value));
        filled++;
    }

    V* Find(const K& key)
    {
        size_t index = Hash(key);
        std::list<Node>& iHT = HT[index];

        for (typename std::list<Node>::iterator iter = iHT.begin(); iter != iHT.end(); iter++)
        {
            if (iter->key == key)
            {
                return &(iter->value);
            }
        }
        return nullptr;
    }

    bool Remove(const K& key)
    {
        size_t index = Hash(key);
        std::list<Node>& iHT = HT[index];

        for (typename std::list<Node>::iterator iter = iHT.begin(); iter != iHT.end(); iter++)
        {
            if (iter->key == key)
            {
                iHT.erase(iter);
                filled--;
                return true;
            }
        }
        return false;
    }

    void Clear()
    {
        for (size_t i = 0; i < sz; i++)
        {
            HT[i].clear();
        }
        filled = 0;
    }
};