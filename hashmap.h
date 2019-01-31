#pragma once
#include <vector>
#include <iostream>
#include <assert.h>

template <typename T1, typename T2>
class hashmap {
private:
	std::vector<std::vector<std::pair<T1,T2> > > table;
	size_t sizemask = 0;

public:
	hashmap(unsigned int tablesize) {
		sizemask = 1;
		while (sizemask < tablesize) sizemask <<= 1;
		if (sizemask > tablesize) sizemask >>= 1;
		tablesize = sizemask;
		sizemask--;
		std::vector<std::pair<T1,T2> > el;
		table.resize(tablesize, el);
	}

	hashmap() {
		sizemask = 0;
	}
	
	~hashmap() {
		table.clear();
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

	T2 operator[] (T1 key) {
        return get(key);
    }

private:
	size_t hash(int x) {
		x = (x ^ 61) ^ (x << 16);
		x += (x << 3);
		x ^= (x >> 4);
		x *= 0x27d4eb2d;
		x ^= x >> 15;
		return x & sizemask;
	}
	
	size_t hash(long long x) {
		return ((hash((int)(x >> 32)) << 2) ^ hash((int)x)) & sizemask;
	}

	size_t hash(__int128 x) {
		return ((hash((long long)(x >> 64)) << 2) ^ hash((long long)x)) & sizemask;
	}

	size_t hash(std::pair<auto, auto> x) {
		return ((hash(x.first) << 2) ^ hash(x.second)) & sizemask;
	}
};
