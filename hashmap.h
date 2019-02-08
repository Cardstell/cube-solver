#pragma once
#include <vector>
#include <iostream>
#include <stdexcept>

template <typename T1, typename T2>
class hashmap {
private:
	std::vector<std::vector<std::pair<T1,T2> > > table;
	size_t sizemask = 0;

public:
	hashmap(size_t tablesize) {
		sizemask = 1;
		while (sizemask < tablesize) sizemask <<= 1;
		if (sizemask > tablesize) sizemask >>= 1;
		tablesize = sizemask;
		sizemask--;
		table.resize(tablesize, std::vector<std::pair<T1,T2> >());
	}

	hashmap() {
		sizemask = 0;
	}
	
	~hashmap() {
		table.clear();
		table.shrink_to_fit();
	}

	void insert(T1 key, T2 value) {
		auto hkey = hash(key);
		for (auto &i : table[hkey]) {
			if (i.first == key) {
				i.second = value;
				return;
			}
		}
		table[hkey].push_back({key,value});
	}

	bool find(T1 key) {
		auto hkey = hash(key);
		for (auto &i : table[hkey]) {
			if (i.first == key)
				return true;
		}
		return false;
	}

	T2& get(T1 key) {
		auto hkey = hash(key);
		for (auto &i : table[hkey]) {
			if (i.first == key) 
				return i.second;
		}
		table[hkey].push_back({key, NULL});
		return table[hkey].back().second;
	}

	void erase(T1 key) {
		auto hkey = hash(key);
		for (auto i = table[hkey].begin();i != table[hkey].end();++i) {
			if (i->first == key) {
				table[hkey].erase(i);
				return;
			}
		}
	}

	T2& operator[] (T1 key) {
        return get(key);
    }

private:

	size_t hash(std::pair<auto, auto> x) {
		return ((hash(x.first) << 2) ^ hash(x.second)) & sizemask;
	}

    template <typename T>
	size_t hash(T x) {
		std::hash<int> h;
		return h(x) & sizemask;
	}
};
