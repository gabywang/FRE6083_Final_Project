#include "pch.h"
#include <iostream>
#include "DataTypes.h"
#include "utils.h"
#include "configure.h"
#include <fstream>

#define VECTOR_TEST 1
#define SERIES_TEST 1
#define SERIES_FUNCS 1
#define EXCEL_INTERACT 1

int main()
{
	Vector vr(12);

	for (int i = -6; i < 6; ++i)
	{
		vr[i + 6] = -i;
	}

	//std::cout << vr;

	Vector vr2 = vr;

#if VECTOR_TEST
	std::cout << (vr += 1);
	std::cout << (vr += vr2);
	std::cout << std::endl;

	std::cout << (vr -= 23.4);
	std::cout << (vr -= vr2);
	std::cout << std::endl;

	std::cout << (vr *= 11.1);
	std::cout << (vr *= vr2);
	std::cout << std::endl;
	
	std::cout << (vr /= 6);
	std::cout << (vr /= vr2);
	std::cout << std::endl;
#endif
	
#if SERIES_TEST
	Series<int> se(std::move(vr2));

	Series<int> se2 = se;

	std::cout << se.get_values();

	std::cout << (se + 1).get_values();
	std::cout << (se + se2).get_values();

	std::cout << (se - 1).get_values();
	std::cout << (se - se2).get_values();

	std::cout << (se * 3).get_values();
	std::cout << (se * se2).get_values();

	std::cout << (se / 2).get_values();
	std::cout << (se / se2).get_values();
	
	std::cout << (se += 1).get_values();
	std::cout << (se += se2).get_values();

	std::cout << (se -= 1).get_values();
	std::cout << (se -= se2).get_values();

	std::cout << (se *= 2).get_values();
	std::cout << (se *= se2).get_values();

	std::cout << (se /= 1).get_values();
	std::cout << (se /= se2).get_values();
	std::cout << se2;
#endif

#if SERIES_FUNCS
	Series<int> see(std::move(vr2));
	see.sort_by_value();
	//std::cout << se.get_values();
	//std::cout << se.get_index();

	auto&& se3 = see.pct_change();
	//std::cout << se3.get_values();

	se3 = see.cumsum();
	//std::cout << se3.get_values();

	se3 = see.right_join(std::vector<int>{1, 2, 3});
	//std::cout << se3.get_values();
	std::cout << see;

#endif

#if EXCEL_INTERACT

	/*
	std::ifstream file;
	const std::string path("C:\\Users\\Rex Hoo\\Documents\\workspace\\financial_computing\\FRE6083_Final_Project\\SeriesUnitTest\\test.csv");
	file.open(path, std::ios::in);
	if (!file.is_open()) throw new std::runtime_error("Cannot open file.");

	Vector&& vec1 = read_col_from_csv<Vector, int>(file, 1, 0);
	Vector&& vec2 = read_col_from_csv<Vector, double>(file, 1, 1);
	std::cout << vec1;
	std::cout << vec2;

	file.close();
	*/
	Series<int> seee(std::move(EPS_FILE), 0, 1, 1);
	std::cout << seee;

#endif
	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
