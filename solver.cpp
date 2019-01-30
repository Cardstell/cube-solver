#include "solver.h"
#include <iostream>
#include <thread>
#include <string>

typedef std::pair<int, __int128> stateType;
#define dbg(x) std::cout << #x << " = " << x << std::endl;

/*
	URFDLB
*/

Solver::Solver() {
	cacheLoaded = loadCacheFromDisk();
}

Solver::~Solver() {
	states.clear();
}

bool Solver::loadCacheFromDisk() {

}

bool Solver::saveCacheToDisk() {

}

inline int getLetterPosition(char c) {
	switch (c) {
		case 'U': return 0;
		case 'R': return 1;
		case 'F': return 2;
		case 'D': return 3;
		case 'L': return 4;
		case 'B': return 5;
		default: return -1;
	}
}

stateType Solver::cubeToState(std::string cube) {
	stateType result = {0,0};
	if (cube.size() != 54) return result;
	int cnt = 0;
	for (int i = 0;i<54;++i) {
		if (i%9 == 4) continue;
		__int128 current = getLetterPosition(cube[i]);
		if (cnt >= 40) result.first |= current << ((cnt - 40) * 3);
		else result.second |= current << (cnt * 3);
		cnt++;
	} 
	return result;
}

std::string Solver::stateToCube(stateType state) {
	const std::string let = "URFDLB";
	std::string result(54, ' ');
	for (int i = 0;i<6;++i) 
		result[i*9 + 4] = let[i];
	for (int i = 0;i<40;++i) {
		int current = (state.second & ((__int128)7 << (i*3))) >> (i*3);
		result[i + (i+4)/8] = let[current];
	}
	for (int i = 0;i<8;++i) {
		int current = (state.first & ((__int128)7 << (i*3))) >> (i*3);
		result[i + 40 + (i+44)/8] = let[current];
	}
	return result;
}

inline int getColor(int x, int num) {
	return (x >> (num * 3)) & 7; 
}

inline void setColor(int &x, int num, int color) {
	x &= ~(7 << (num * 3));
	x |= color << (num * 3);
}

inline void swapColors(int &a, int a_num, int &b, int b_num, int &c, int c_num, int &d, int d_num) {
	int tmp = getColor(d, d_num);
	setColor(d, d_num, getColor(c, c_num));
	setColor(c, c_num, getColor(b, b_num));
	setColor(b, b_num, getColor(a, a_num));
	setColor(a, a_num, tmp);
}

inline void swapColors(int &x, int a, int b, int c, int d) {
	swapColors(x, a, x, b, x, c, x, d);
}

stateType Solver::rotateState(stateType state, int rotation) {
	int up = state.second & 0xFFFFFF;
	state.second >>= 24;
	int right = state.second & 0xFFFFFF;
	state.second >>= 24;
	int front = state.second & 0xFFFFFF;
	state.second >>= 24;
	int down = state.second & 0xFFFFFF;
	state.second >>= 24;
	int left = state.second;
	int back = state.first;
	switch (rotation) {
	case 0:
		swapColors(up, 0, 2, 7, 5);
		swapColors(up, 1, 4, 6, 3);
		swapColors(front, 0, left, 0, back, 0, right, 0);
		swapColors(front, 1, left, 1, back, 1, right, 1);
		swapColors(front, 2, left, 2, back, 2, right, 2);
		break;
	case 1:
		swapColors(right, 0, 2, 7, 5);
		swapColors(right, 1, 4, 6, 3);
		swapColors(front, 2, up, 2, back, 5, down, 2);
		swapColors(front, 4, up, 4, back, 3, down, 4);
		swapColors(front, 7, up, 7, back, 0, down, 7);
		break;
	case 2:
		swapColors(front, 0, 2, 7, 5);
		swapColors(front, 1, 4, 6, 3);
		swapColors(left, 2, up, 7, right, 5, down, 0);
		swapColors(left, 4, up, 6, right, 3, down, 1);
		swapColors(left, 7, up, 5, right, 0, down, 2);
		break;
	case 3:
		swapColors(down, 0, 2, 7, 5);
		swapColors(down, 1, 4, 6, 3);
		swapColors(front, 5, right, 5, back, 5, left, 5);
		swapColors(front, 6, right, 6, back, 6, left, 6);
		swapColors(front, 7, right, 7, back, 7, left, 7);
		break;
	case 4:
		swapColors(left, 0, 2, 7, 5);
		swapColors(left, 1, 4, 6, 3);
		swapColors(front, 0, down, 0, back, 7, up, 0);
		swapColors(front, 3, down, 3, back, 4, up, 3);
		swapColors(front, 5, down, 5, back, 2, up, 5);
		break;
	case 5:
		swapColors(back, 0, 2, 7, 5);
		swapColors(back, 1, 4, 6, 3);
		swapColors(up, 0, left, 5, down, 7, right, 2);
		swapColors(up, 1, left, 3, down, 6, right, 4);
		swapColors(up, 2, left, 0, down, 5, right, 7);
		break;

	}
	stateType result = {back,up};
	result.second |= (__int128)right << 24;
	result.second |= (__int128)front << 48;
	result.second |= (__int128)down << 72;
	result.second |= (__int128)left << 96;
	return result;
}

std::vector<std::string> Solver::split(std::string s) {
	std::vector<std::string> ans;
	int start = 0;
	for (int i = 0;i<s.size();++i) {
		if (s[i] == ' ') {
			std::string tmp = s.substr(start, i - start);
			if (tmp != "") ans.push_back(tmp);
			start = i + 1;
		}
	}
	if (start != s.size()) {
		std::string tmp = s.substr(start, s.size() - start);
		if (tmp != "") ans.push_back(tmp);
	}
	return ans;
}

stateType Solver::runAlgo(stateType state, std::string algo) {
	auto rotations = split(algo);
	for (auto i : rotations) {
		int count = 1, pos = getLetterPosition(i[0]);
		if (i.size() > 1 && i[1] == '\'') count = 3;
		else if (i.size() > 1 && i[1] == '2') count = 2;
		for (int j = 0;j<count;++j)
			state = rotateState(state, pos);
	}
	return state;
}

stateType Solver::getInitialState() {
	return cubeToState("UUUUUUUUURRRRRRRRRFFFFFFFFFDDDDDDDDDLLLLLLLLLBBBBBBBBB");
}