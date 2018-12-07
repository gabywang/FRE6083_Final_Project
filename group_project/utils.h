#ifndef utils_h
#define utils_h

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "configure.h"

template <typename VectorLike, typename T>
VectorLike read_col_from_csv(std::ifstream& file , unsigned int start_row, unsigned int data_col)
{
	file.clear();
	file.seekg(0, std::ios::beg);

	std::string rol_str;
	VectorLike result(0);
	
	T one_cell;
	char * str_ptr;

	unsigned int row(0), col;
	while (getline(file, rol_str))
	{
		col = 0;
		str_ptr = strtok((char *)rol_str.c_str(), ",");
		while (str_ptr)
		{
			if (strcmp(str_ptr, ""))
			{
				if (col == data_col && row >= start_row)
				{
					std::stringstream ss;
					ss << std::string(str_ptr);
					ss >> one_cell;
					result.push_back(one_cell);
				}

				++col;
			}
			str_ptr = strtok(NULL, ",");
		}
		++row;
	}
	return result;
}
#endif