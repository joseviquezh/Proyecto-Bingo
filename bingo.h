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
		int nums[75];
	
	public:
		Bingo();
  
  public:
	int generate(int argc, char* argv[]);
	int simulate(int argc, char* argv[]);
	std::string get_number(int count);
  
};
