#include "bingo.h"
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <random>
#include <algorithm>
#include <vector>
#include <chrono>
		
Bingo::Bingo()
{
	nums.reserve(75);
	for(int i = 1; i <= 75; ++i)
	{

		nums.push_back(i);
	}
	random();
}

int Bingo::generate(int argc, char* argv[])
{
	size_t number = atoi(argv[2]);
	std::string filename = argv[3];
	std::string symbols_filename;
	if (argc > 4 && strcmp(argv[4], "-s") == 0)
	{
		symbols_filename = argv[5];
	}
	
	std::ifstream svg_file( filename );
	if ( ! svg_file )
	{
		std::cerr << "Generate: could not open " << filename << std::endl;
		return 1;
	}
	
	std::string line;
	for ( size_t i = 1; i <= number; ++i){
		std::ofstream myfile;
		myfile.open (generate_filename(filename, i, number), std::ios::out);
		int count=0;
		int vec_pos=1;		
		while ( std::getline(svg_file, line) ){
		
			size_t pos = line.rfind('$');
			size_t finalpos = line.rfind('}');
			if ( pos != std::string::npos && finalpos != std::string::npos )
			{
				line.replace(pos, ( (finalpos - pos) + 1 ),get_number(vec_pos+count));
				++count;
			}
			
			if (count == 5)
			{
				vec_pos+=15;
				count = 0;
			}
			
			myfile << line << '\n';
		}
		svg_file.clear();
		svg_file.seekg(0, std::ios_base::beg);
		myfile.close();
		random();
	}
	
	return 0;
}

std::string Bingo::get_number(int count)
{
	char temp[10];
	itoa ( nums[count], temp, 10);
	std::string number = temp;
	return number;
}

const char* Bingo::generate_filename(std::string source, int filenumber, int number)
{
	std::string target;
	size_t dot_pos = source.rfind('.');
	
	char num_c[number];
	itoa(filenumber, num_c, 10);	
	std::string string_number = num_c;
	int pivot;
	for (int i = 1; number > i; i*=10)
	{
		pivot = i;
	}
	for (int i = filenumber; i < pivot; i*=10)
	{
		string_number = "0" + string_number;
	}
	string_number = "-" + string_number;
	
	if ( dot_pos != std::string::npos )
	{
		target = source.substr(0, dot_pos) + string_number + source.substr(dot_pos);
	}
	return target.c_str();
}

void Bingo::random()
{
	std::random_device rd;
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	
	for (int i = 0; i < 75; i+=15 )
	{
		std::shuffle(this->nums.begin()+i, this->nums.begin() + (i + 15), std::default_random_engine(seed));
	}
}
int Bingo::simulate(int argc, char* argv[])
{
	return 0;
}


int main(int argc, char* argv[])
{
	for (int i = 0; i < argc; ++i){
		if ( strcmp(argv[i], "--help") == 0)
		{
			std::cout << "Create Bingo cards and simulate game sessions. Usage:" << std::endl;
			std::cout << "bingo action [options]" << std::endl;
			std::cout << std::endl;
			std::cout << "bingo generate NUMBER card.svg [-s symbols.txt]" << std::endl;
			std::cout << "bingo simulate [card.idx] [-t type] [-s symbols.txt]" << std::endl;
			return 0;	
		}
	}
	
	for (int i = 0; i < argc; ++i){
		if ( strcmp(argv[i], "--version") == 0)
		{
			std::cout << "version" << std::endl;
			return 0;	
		}
	}
	
	Bingo bingo;
	
	if (strcmp(argv[1], "generate") == 0)
	{
		
		bingo.generate(argc, argv);
	}
	else 
	{
		bingo.simulate(argc, argv);
	}
   
   return 0;
}
