#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <fstream>
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

  public:
	int generate(int argc, char* argv[]);
	int simulate(int argc, char* argv[]);
	std::string get_number(int count);
	const char* generate_filename(std::string source,int filenumber, int number);
};

