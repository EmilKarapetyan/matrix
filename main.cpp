// Includes from this project

// Includes from third-party projects (like Boost, Poco, etc.)

// Includes from C++ Standard Library

#include"matrix.h"

#include<iostream>

#include<random>

//#include <googletest/gtest.h>

bool test_copy_assignment_operator()
{
	Matrix<std::int32_t> mtx(4, 4, 1);
	Matrix<std::int32_t> mat_second;
	mat_second = mtx;

	bool failed = false;
	for(std::uint32_t i = 0; i < 4; ++i) {
		for(std::uint32_t j = 0; j < 4; ++j) {
			if(mtx[i][j] != mat_second[i][j]) {
				std::cout << "TEST FAILED: mtx assignment operator"<<std::endl;
				return failed;
			}
		}
	} 
	std::cout << "TEST SUCCEED: mtx assigmnet operaotr"<<std::endl;
	return true;
}

bool test_move_assignment_operator() 
{
	Matrix<std::int32_t> matr_orig(4, 4, 1);
	Matrix<std::int32_t> mtx_copy;
	mtx_copy = matr_orig;
	Matrix<std::int32_t> mtx;
	mtx = std::move(matr_orig);

	bool failed = false;
	for(std::uint32_t i = 0; i < 4; ++i) {
		for(std::uint32_t j = 0; j < 4; ++j) {
			if(mtx_copy[i][j] != mtx[i][j]) {
				std::cout << "TEST FAILED: mtx move assignment operator"<<std::endl;
				return failed;
			}
		}
	} 
	std::cout << "TEST SUCCEED: mtx move assigmnet operaotr"<<std::endl;
	return true;
}

bool test_matrix_scalar_multiplication()
{
	const std::int32_t multiplier = 4;
	Matrix<std::int32_t> matr1(6,6,5);
	Matrix<std::int32_t> matr2 = matr1;
	matr2 *= multiplier;

	std::uint32_t mtxrow = matr1.getRow();
	std::uint32_t mtxcol = matr1.getColumn();
	bool failed = false;
	if (mtxrow != matr2.getRow() || mtxcol != matr2.getColumn()) {
		std::cout << "TEST FAILED: mtx scalar multiplication"<<std::endl;
		return failed;
	}

	for(std::uint32_t i = 0; i < mtxrow; ++i) {
		for(std::uint32_t j = 0; j < mtxcol; ++j) {
			if((matr1[i][j]) * multiplier != matr2[i][j]) {
				std::cout << "TEST FAILED: mtx multiplication"<<std::endl;
				return failed;
			}
		}
	} 
	std::cout << "TEST SUCCEED: mtx scalar multiplication"<<std::endl;
	return true;
}

bool test_matrix_product()
{
	Matrix<std::int32_t> res;
	Matrix<std::int32_t> matr1(3, 3,
		{{1, 2, 3},
		{4, 5, 6},
		{7, 8, 9}});

	Matrix<std::int32_t> matr2(3, 7,
		{{1, 2, 3, 4, 5, 6, 7},
		{8, 9, 10, 11, 12, 13, 14},
		{15, 16, 17, 18, 19, 20, 21}});

	Matrix<std::int32_t> product_golden_1(3, 7,
		{{62, 68, 74, 80, 86, 92, 98},
		{134, 149, 164, 179, 194, 209, 224},
		{206, 230, 254, 278, 302, 326, 350}});

	matr1.matrixProduct(matr2, res);

	if (res != product_golden_1) 
	{
		std::cout << "TEST FAILED: mtx product"<<std::endl;
		return false;
	}

	Matrix<std::int32_t> matr3(6, 5,
		{{1, 2, 3, 4, 5},
        {6, 7, 8, 9, 10},
        {11, 12, 13, 14, 15},
        {16, 17, 18, 19, 20},
        {21, 22, 23, 24, 25},
        {26, 27, 28, 29, 30}});

	Matrix<std::int32_t> matr4(5, 8,
		{{1, 2, 3, 4, 5, 6, 7, 8},
        {9, 10, 11, 12, 13, 14, 15, 16},
        {17, 18, 19, 20, 21, 22, 23, 24},
        {25, 26, 27, 28, 29, 30, 31, 32},
        {33, 34, 35, 36, 37, 38, 39, 40}});

	Matrix<std::int32_t> product_golden_2(6, 8,
		{{335, 350, 365, 380, 395, 410, 425, 440},
        {760, 800, 840, 880, 920, 960, 1000, 1040},
        {1185, 1250, 1315, 1380, 1445, 1510, 1575, 1640},
        {1610, 1700, 1790, 1880, 1970, 2060, 2150, 2240},
        {2035, 2150, 2265, 2380, 2495, 2610, 2725, 2840},
        {2460, 2600, 2740, 2880, 3020, 3160, 3300, 3440}});


	matr3.matrixProduct(matr4, res);
	if (res != product_golden_2) 
	{
		std::cout << "TEST FAILED: mtx product"<<std::endl;
		return false;
	}	
	
	std::cout << "TEST SUCCEED: mtx product"<<std::endl;
	return true;
}

bool test_determinant_calculation()
{
	Matrix<int> matr1(8, 8,
		{{1045, 2201, 3204, 1492, 4310, 2823, 5172, 9985},
        {5732, 1938, 3014, 4102, 2111, 5074, 2357, 1753},
        {1212, 2013, 4010, 5383, 3022, 4832, 5245, 6111},
        {7310, 3820, 2276, 5992, 3404, 5599, 2035, 4927},
        {5156, 4281, 7321, 1837, 6740, 5493, 1832, 4602},
        {2842, 1021, 5067, 1049, 5317, 5273, 6130, 2536},
        {1933, 7230, 3829, 2976, 1892, 3278, 6032, 4111},
        {5194, 6723, 4555, 6148, 3960, 7282, 1549, 4389}});

	Matrix<int> matr2(4, 4,
		{{71, 60, 42, 80},
		{12, 90, 59, 12},
		{19, 97, 63, 82},
		{40, 27, 36, 9}});
		
	//std::cout<<"\nDeterminant of "<<matr2.get_determinant()<<std::endl;; //TODO Revisit
	return true;
}

bool test_functionality()
{
	return  (test_copy_assignment_operator() &
			test_move_assignment_operator() &
			test_matrix_scalar_multiplication() &
			test_matrix_product());
}

int main() {

	bool status = test_functionality();
	if (status) 
	{
		std::cout<<"####################"<<std::endl;
		std::cout<<"ALL THE TEST PASSED! Ibrahim ջան"<<std::endl;
		std::cout<<"####################"<<std::endl;
	}

	return 0;
}
