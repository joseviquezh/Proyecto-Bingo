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

int nums[75];
		
Bingo::Bingo()
{
	for (int i = 0; i < 75; ++i)
	{
		nums[i] = i+1;
	}
 
}

int Bingo::generate(int argc, char* argv[])
{
	size_t number = atoi(argv[2]);
	std::string filename = argv[3];
	std::string symbols_filename;
	if (argc > 4 && strcmp(argv[4], "-s") == 0)
	{
		symbols_filename,argv[5];
	}
	
	std::ifstream svg_file( filename );
	if ( ! svg_file )
	{
		std::cerr << "Generate: could not open " << filename << std::endl;
		return 1;
	}
	
	int count=0;
	int vec_pos=1;
	std::string line;
	for ( size_t i = 0; i < number; ++i){
		std::ofstream myfile;
		myfile.open ("example.txt", std::ios::out);		
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
		std::cout << std::endl;
		svg_file.clear();
		svg_file.seekg(0, std::ios_base::beg);
		myfile.close();
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