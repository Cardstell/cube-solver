#include "solver.h"
#include <iostream>
#include <string>
#include <ctime>
#include <random>
#include <iomanip>
#include <chrono>
using namespace std;

const int N = 3;
mt19937 rng(time(NULL));
struct cube {
	char F = ' ', B = ' ';
	char L = ' ', R = ' ';
	char U = ' ', D = ' '; 
} cubes[N*N*N];


void fillcubes(cube *cubes) {
	for (int i = 0;i<N;++i) {
		for (int j = 0;j<N;++j) {
			for (int h = 0;h<N;++h) {
				int id = i*N*N + j*N + h;
				if (i == 0) cubes[id].U = 'U';
				if (i == N-1) cubes[id].D = 'D';
				if (j == 0) cubes[id].B = 'B';
				if (j == N-1) cubes[id].F = 'F';
				if (h == 0) cubes[id].L = 'L';
				if (h == N-1) cubes[id].R = 'R';
			}
		}
	}
}

void printcubes(cube *cubes) {
	for (int i = 0;i<N;++i) {
		for (int h = 0;h<N+1;++h) cout<<" ";
		for (int j = 0;j<N;++j) cout<<cubes[i*N+j].U;
		cout<<endl;
	}
	cout<<endl;
	for (int i = 0;i<N;++i) {
		for (int j = 0;j<N;++j) cout<<cubes[i*N*N + j*N].L;
		cout<<" ";
		for (int j = 0;j<N;++j) cout<<cubes[i*N*N + j + N*(N-1)].F;
		cout<<" ";
		for (int j = 0;j<N;++j) cout<<cubes[i*N*N + (N-j-1)*N + N-1].R;
		cout<<" ";
		for (int j = 0;j<N;++j) cout<<cubes[i*N*N + (N-j-1)].B;
		cout<<endl;
	}
	cout<<endl;
	for (int i = 0;i<N;++i) {
		for (int h = 0;h<N+1;++h) cout<<" ";
		for (int j = 0;j<N;++j) cout<<cubes[(N-i-1)*N+j+N*N*(N-1)].D;
			cout<<endl;
	}
}

cube rotateCube(cube curcube, char direction) {
	cube newcube;
	switch (direction) {
	case 'U':
		newcube.U = curcube.U;
		newcube.D = curcube.D;
		newcube.L = curcube.F;
		newcube.B = curcube.L;
		newcube.R = curcube.B;
		newcube.F = curcube.R;
		break;
	case 'D':
		newcube.U = curcube.U;
		newcube.D = curcube.D;
		newcube.F = curcube.L;
		newcube.L = curcube.B;
		newcube.B = curcube.R;
		newcube.R = curcube.F;
		break;
	case 'L':
		newcube.L = curcube.L;
		newcube.R = curcube.R;
		newcube.U = curcube.B;
		newcube.B = curcube.D;
		newcube.D = curcube.F;
		newcube.F = curcube.U;
		break;
	case 'R':
		newcube.L = curcube.L;
		newcube.R = curcube.R;
		newcube.B = curcube.U;
		newcube.D = curcube.B;
		newcube.F = curcube.D;
		newcube.U = curcube.F;
		break;
	case 'F':
		newcube.F = curcube.F;
		newcube.B = curcube.B;
		newcube.U = curcube.L;
		newcube.L = curcube.D;
		newcube.D = curcube.R;
		newcube.R = curcube.U;
		break;
	case 'B':
		newcube.F = curcube.F;
		newcube.B = curcube.B;
		newcube.L = curcube.U;
		newcube.D = curcube.L;
		newcube.R = curcube.D;
		newcube.U = curcube.R;
		break;
	}
	return newcube;
}

void copy(cube *cubes, cube *newcubes) {
	for (int i = 0;i<N*N*N;++i) {
		newcubes[i] = cubes[i];
	}
}

void rotate(cube *cubes, string direction) {
	int count = 1;
	if (direction[1] == '2') count = 2;
	else if (direction[1] == '\'') count = 3;
	for (int cnt = 0;cnt<count;++cnt) {
		cube newcubes[N*N*N];
		copy(cubes, newcubes);
		switch (direction[0])
		{
			case 'F':
				for (int i = 0;i<N;++i) {
					for (int j = 0;j<N;++j) {
						int id1 = i*N*N + j + N*(N-1);
						int id2 = (N-i-1) + j*N*N + N*(N-1);
						newcubes[id2] = rotateCube(cubes[id1], direction[0]);
					}
				}
				break;
			case 'f':
				for (int i = 0;i<N;++i) {
					for (int j = 0;j<N;++j) {
						int id1 = i*N*N + j + N*(N-1) - N;
						int id2 = (N-i-1) + j*N*N + N*(N-1) - N;
						newcubes[id2] = rotateCube(cubes[id1], direction[0] + 'A' - 'a');
					}
				}
				break;
			case 'B':
				for (int i = 0;i<N;++i) {
					for (int j = 0;j<N;++j) {
						int id1 = i*N*N + (N-j-1);
						int id2 = j*N*N + i;
						newcubes[id2] = rotateCube(cubes[id1], direction[0]);
					}
				}
				break;
			case 'b':
				for (int i = 0;i<N;++i) {
					for (int j = 0;j<N;++j) {
						int id1 = i*N*N + (N-j-1) + N;
						int id2 = j*N*N + i + N;
						newcubes[id2] = rotateCube(cubes[id1], direction[0] + 'A' - 'a');
					}
				}
				break;
			case 'L':
				for (int i = 0;i<N;++i) {
					for (int j = 0;j<N;++j) {
						int id1 = i*N*N + j*N;
						int id2 = j*N*N + (N-i-1)*N;
						newcubes[id2] = rotateCube(cubes[id1], direction[0]);
					}
				}
				break;
			case 'l':
				for (int i = 0;i<N;++i) {
					for (int j = 0;j<N;++j) {
						int id1 = i*N*N + j*N + 1;
						int id2 = j*N*N + (N-i-1)*N + 1;
						newcubes[id2] = rotateCube(cubes[id1], direction[0] + 'A' - 'a');
					}
				}
				break;
			case 'R':
				for (int i = 0;i<N;++i) {
					for (int j = 0;j<N;++j) {
						int id1 = i*N*N + (N-j-1)*N + N-1;
						int id2 = j*N*N + i*N + N-1;
						newcubes[id2] = rotateCube(cubes[id1], direction[0]);
					}
				}
				break;
			case 'r':
				for (int i = 0;i<N;++i) {
					for (int j = 0;j<N;++j) {
						int id1 = i*N*N + (N-j-1)*N + N-1 - 1;
						int id2 = j*N*N + i*N + N-1 - 1;
						newcubes[id2] = rotateCube(cubes[id1], direction[0] + 'A' - 'a');
					}
				}
				break;
			case 'U':
				for (int i = 0;i<N;++i) {
					for (int j = 0;j<N;++j) {
						int id1 = i*N + j;
						int id2 = j*N + (N-i-1);
						newcubes[id2] = rotateCube(cubes[id1], direction[0]);
					}
				}
				break;
			case 'u':
				for (int i = 0;i<N;++i) {
					for (int j = 0;j<N;++j) {
						int id1 = i*N + j + N*N;
						int id2 = j*N + (N-i-1) + N*N;
						newcubes[id2] = rotateCube(cubes[id1], direction[0] + 'A' - 'a');
					}
				}
				break;
			case 'D':
				for (int i = 0;i<N;++i) {
					for (int j = 0;j<N;++j) {
						int id1 = (N-i-1)*N + j + N*N*(N-1);
						int id2 = (N-j-1)*N + (N-i-1) + N*N*(N-1);
						newcubes[id2] = rotateCube(cubes[id1], direction[0]);
					}
				}
				break;
			case 'd':
				for (int i = 0;i<N;++i) {
					for (int j = 0;j<N;++j) {
						int id1 = (N-i-1)*N + j + N*N*(N-2);
						int id2 = (N-j-1)*N + (N-i-1) + N*N*(N-2);
						newcubes[id2] = rotateCube(cubes[id1], direction[0] + 'A' - 'a');
					}
				}
				break;


		}
		copy(newcubes, cubes);
	}
}

vector<string> split(string s) {
	vector<string> ans;
	int start = 0;
	for (int i = 0;i<s.size();++i) {
		if (s[i] == ' ') {
			string tmp = s.substr(start, i-start);
			if (tmp != "") ans.push_back(tmp);
			start = i + 1;
		}
	}
	if (start != s.size()) {
		string tmp = s.substr(start, s.size()-start);
		if (tmp != "") ans.push_back(tmp);
	}
	return ans;
}

void run(cube *cubes, string algo) {
	vector<string> rotations = split(algo);
	for (string i:rotations) {
		if (i.size() == 1) i += ' ';
		rotate(cubes, i);
	}
}

string getStringCube(cube *cubes) {
	string ans = "";
	for (int i = 0;i<N;++i) {
		for (int j = 0;j<N;++j) ans += cubes[i*N + j].U;
	}
	for (int i = 0;i<N;++i) {
		for (int j = 0;j<N;++j) ans += cubes[i*N*N + (N-j-1)*N + N-1].R;
	}
	for (int i = 0;i<N;++i) {
		for (int j = 0;j<N;++j) ans += cubes[i*N*N + j + N*(N-1)].F;
	}
	for (int i = 0;i<N;++i) {
		for (int j = 0;j<N;++j) ans += cubes[(N-i-1)*N + j + N*N*(N-1)].D;
	}
	for (int i = 0;i<N;++i) {
		for (int j = 0;j<N;++j) ans += cubes[i*N*N + j*N].L;
	}
	for (int i = 0;i<N;++i) {
		for (int j = 0;j<N;++j) ans += cubes[i*N*N + (N-j-1)].B;
	}
	return ans;
}

string generateRotations(int count = 20) {
	string z = "U U'U2D D'D2L L'L2R R'R2B B'B2F F'F2";
	string ans = "";
	for (int i = 0;i<count;++i) {
		int pos = rng()%18 * 2; 
		ans += z[pos];
		ans += z[pos+1];
		ans += " ";
	}
	return ans;
}

double check_time(auto call, bool print = 0, string text = "Test") {
	std::chrono::time_point<std::chrono::system_clock> start, end;
	start = std::chrono::system_clock::now();
	call();
	end = std::chrono::system_clock::now();
	double time = 1e-6 * std::chrono::duration_cast<std::chrono::microseconds>(end-start).count();
	if (print) std::cout<<text<<" finished in "<<fixed<<setprecision(3)<<time<<"s"<<std::endl;
	return time;
}

const int TESTS = 100;

void RotationStressTest() {
	for (int i = 0;i<TESTS;++i) {
		fillcubes(cubes);
		auto algo = generateRotations(100);
		run(cubes, algo);
		auto st = solver::getInitialState();
		st = solver::runAlgo(st, algo);
		string trueAnswer = getStringCube(cubes);
		string currentAnswer = solver::stateToCube(st);
		if (trueAnswer != currentAnswer) {
			cout<<"Wrong answer"<<endl;
			cout<<trueAnswer<<endl<<currentAnswer<<endl;
			return;
		}
	}
	cout<<"All tests passed"<<endl;
	
}

void RotationTest() {
	auto st = solver::getInitialState();
	for (int i = 0;i<1e7;++i) {
		st = solver::rotateState(st, 0);
	}
}

void CacheTest() {
	solver s1, s2;
	for (int i = 0;i<6e7;++i) {
		int t1 = rng(), t2 = rng(), t3 = rng(); 
		s1.states[{t1,t2}] = t3;
		s2.states[{t1,t2}] = t3;
	}
	s1.saveCacheToDisk();
	s1.loadCacheFromDisk();
	/*for (auto i : s1.states) cout<<i.first.first<<" "<<(long)i.first.second<<" "<<i.second<<endl;
		cout<<"-----------\n";
	for (auto i : s2.states) cout<<i.first.first<<" "<<(long)i.first.second<<" "<<i.second<<endl;
	*/
	cout << s1.states.size() << " " << s2.states.size() << endl;
	if (s1.states != s2.states) cout << "Caches not equal!" << endl;
	else cout << "Test passed" << endl;
}

void HashmapStressTest() {
	boost::unordered_map<stateType,int> s1, s2;
	hashmap<stateType,int> hs(1e5);
	const int N = 1e3;
	for (int i = 0;i<1e5;++i) {
		int a = rng()%N, b = rng()%N, c = rng()%N;
		s1[{a,b}] = c;
		hs[{a,b}] = c;
		a = rng()%N, b = rng()%N, c = rng()%N;
		s1.erase({a,b});
		hs.erase({a,b});
	}
	for (int i = 0;i<N;++i) {
		for (int j = 0;j<N;++j) {
			if (hs.find({i,j}))
				s2[{i,j}] = hs[{i,j}];
		}
	}
	if (s1 != s2) cout << "Hashmap stress test: maps not equal" << endl;
	else cout << "Hashmap stress test passed" << endl;
}

const int hN = 1e6;
const string shN = to_string(hN);
hashmap<stateType, int> hm(2*hN);
boost::unordered_map<stateType, int> um;

void HashmapInsertTest() {
	for (int i = 0;i<hN;++i) {
		hm[{rng(), 1}] = 2;
	}
}

void UnorderedMapInsertTest() {
	for (int i = 0;i<hN;++i) {
		um[{rng(), 1}] = 2;
	}	
}

void HashmapFindTest() {
	for (int i = 0;i<hN;++i) {
		hm.find({rng(), 1});
	}
}

void UnorderedMapFindTest() {
	for (int i = 0;i<hN;++i) {
		um.find({rng(), 1});
	}	
}

void runTests() {
	//RotationStressTest();
	//check_time(RotationTest, 1, "1e7 rotations");
	//check_time(CacheTest, "Cache test (1e5)");
	HashmapStressTest();
	check_time(HashmapInsertTest, 1, shN + " insertions in hash table");
	check_time(HashmapFindTest, 1, shN + " findings in hash table");
	check_time(UnorderedMapInsertTest, 1, shN + " insertions in unordered_map");
	check_time(UnorderedMapFindTest, 1, shN + " findings in unordered_map");
}