#include<iostream>
#include"matrix.h"
#include<random>

//#include <googletest/gtest.h>


int fib(int n) {
	if (n <= 1)
		return n;
	return fib(n-1) + fib(n-2);
}


int main() {
	const size_t size = 4;
	Matrix<int> matr(size, size); //default constructor
	matr.fillMatrix();

	matr.print();
	matr = matr.divide(2,3);
	std::cout<<"Minor of matrix \n";
	matr.print();

	Matrix<int> matr1(4,4);
	Matrix<int> matr2(4,4,6); //parametrised constructor

	std::cout<<"Printing matrix 1\n";
	matr1.print();
	std::cout<<"Printing matrix 2\n";
	matr2.print();
	Matrix<int> matr3(matr2); //copy constructor

	std::cout<<"Printing matrix 3\n";
	matr3.print();

	Matrix<int> matr4 = matr3; //copy assignment
	std::cout<<"Printing matrix 4\n";
	matr4.print();
	
	Matrix<int> matr12(4,4, 5);
	Matrix<int> matr5 = std::move(matr12); // move constructor
	
	std::cout<<"Printing matrix before move assignemnt\n";
	matr5.print();
	
	//matr5 = std::move(matr4); //move assignemnt

	std::cout<<"Printing matrix after move assignemnt\n";
	matr5.print();
	//matr4.print();

	std::cout<<"Printing matrix before Multiplication\n";
	matr5.print();
	std::cout<<"Printing matrix after Multiplication\n";
	matr5 *= 2;
	matr5.print();

	try {
	//	matr5.at(6, 2);
	}
	catch(std::exception& ex) {
		std::cout<<ex.what()<<"\n";
	}

	Matrix<int> matr6(4,4);
	matr6.fillMatrix();
	
	std::cout<<"Print matr Before Transposal \n";
	matr6.print();
	std::cout<<"\n############################################\n";
	matr6.transpose();
	matr6.print();

	int determinant = matr6.determinantOfMatrix(matr6.getHeight());
	std::cout<<"determinant of matr6 is "<< determinant << "\n";

	Matrix<int> res;
	matr5.mulMatrix(matr3, res);
	std::cout<<"\n############################################\n";
	res.print();

	return 0;
}
