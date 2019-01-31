#pragma once
#include <boost/unordered_map.hpp>
#include <unordered_map>
#include "hashmap.h"

typedef std::pair<int, __int128> stateType;
const long blocksize = 1024 * 32 * 24;
const long tablesize = 1 << 30;

void runTests();

class solver {
private:
	bool cacheLoaded = 0;
	char memblock[blocksize];
	static std::vector<std::string> split(std::string s);

public:
	boost::unordered_map<stateType, int> states;
	solver();
	~solver();

	bool loadCacheFromDisk();
	bool saveCacheToDisk();

	static std::string stateToCube(stateType state);
	static stateType cubeToState(std::string cube);
	static stateType rotateState(stateType state, int rotation);
	static stateType runAlgo(stateType state, std::string algo);
	static stateType getInitialState();
};