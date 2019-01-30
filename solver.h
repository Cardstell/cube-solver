#pragma once
#include <boost/unordered_map.hpp>
typedef std::pair<int, __int128> stateType;

void runTests();

class Solver {
private:
	boost::unordered_map<stateType, int> states;
	bool cacheLoaded = 0;

	static std::vector<std::string> split(std::string s);

public:
	Solver();
	~Solver();

	bool loadCacheFromDisk();
	bool saveCacheToDisk();

	static std::string stateToCube(stateType state);
	static stateType cubeToState(std::string cube);
	static stateType rotateState(stateType state, int rotation);
	static stateType runAlgo(stateType state, std::string algo);
	static stateType getInitialState();
};