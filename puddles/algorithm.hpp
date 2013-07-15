#pragma once

class Algorithm {

public:
	std::vector<std::vector<int> > execute(std::vector<std::vector<int> >& matrix
										   , std::vector<std::tuple<int, int, int>& tuples);

private:
	int walk(int x, int y);

	inline bool checkLeft(int x, int y) {

	}

	inline bool checkUpper(int x, int y) {

	}

	inline bool checkRight(int x, int y) {

	}

	inline bool checkLower(int x, int y) {

	}

	std::vector<std::vector<int> > used;
	int mark;


};
