#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <random>
#include <algorithm>
#include <vector>

class Bingo
{
 private:
	const size_t nColumnas = 5;// Hay que cambiar el valor
	std::vector<int> nums;
	public:
		Bingo();
		~Bingo();

  public:
	int generate(int argc, char* argv[]);
	int simulate(int argc, char* argv[]);

};

