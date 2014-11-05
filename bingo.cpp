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
		
Bingo::Bingo()
{
	nums.reserve(75);
	for(int i = 1; i <= 75; ++i)
	{
		nums.push_back(i);
	}
	std::random_device rd;
	std::mt19937 g(rd());

	std::shuffle(this->nums.begin(), this->nums.begin() + 15, g);
	for(int j = 0; j < 25; ++j)//este ciclo es para saber que aleatoriza bien
	{
		std::cout << this->nums[j] << std::endl;
	}
}
int Bingo::generate(int argc, char* argv[])
{
	size_t number = atoi(argv[2]);
	std::string filename = argv[3];
	/*std::string symbols_filename;
	if (argc > 4 && strcmp(argv[4], "-s") == 0)
	{
		symbols_filename,argv[5];
	}*/
	
	std::ifstream svg_file( filename );
	if ( ! svg_file )
	{
		std::cerr << "Generate: could not open " << filename << std::endl;
		return 1;
	}
	
	int count=1;
	int vec_pos=1;
	std::string line;
	for ( size_t i = 0; i < number; ++i){
		
		while ( std::getline(svg_file, line) ){
		
			size_t pos = line.rfind('$');
			size_t finalpos = line.rfind('}');
			if ( pos != std::string::npos && finalpos != std::string::npos )
			{
				line.replace(pos, ( (finalpos - pos) + 1 ),get_number(vec_pos+count));
			}
			
			if (count == 5)
			{
				vec_pos+=15;
				count = 1;
			}
			
			std::cout << line << std::endl;
			++count;
		}
		std::cout << std::endl;
		svg_file.clear();
		svg_file.seekg(0, std::ios_base::beg);
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
			return 0;	
		}
	}
	
	for (int i = 0; i < argc; ++i){
		if ( strcmp(argv[i], "--version") == 0)
		{
			std::cout << "version" << std::endl;
			std::cout << "" << std::endl;
			return 0;	
		}
	}
	/*std::string line = "111111111111111";
	std::string str = "22222";
	line.replace(5,5,str);
	std::cout << line << std::endl;*/
	
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
