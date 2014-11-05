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
	/*for(int j = 0; j < 25; ++j)//este ciclo es para saber que aleatoriza bien
	{
		std::cout << this->nums[j] << std::endl;
	}*/
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
		myfile.open (generate_filename(filename), std::ios::out);		
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

const char* Bingo::generate_filename(std::string source)
{
	std::string target;
	size_t dot_pos = source.rfind('.');
	if ( dot_pos != std::string::npos )
	{
		target = source.substr(0, dot_pos) + "-1000" + source.substr(dot_pos);
	}
	return target.c_str();
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
