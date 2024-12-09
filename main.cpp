#include<iostream>
#include"matrix.h"

int main(){
	//I cannot see any matrix structure, this thing is called a vector (it's 1 dimensional)
	Matrix<int> matr1(1,2);
	Matrix<int> matr2(7,12,6);

	std::cout<<"Printing matrix 1\n";
	matr1.print();
	std::cout<<"Printing matrix 2\n";
	matr2.print();
	Matrix<int> matr3(matr2);//copy constructor

	std::cout<<"Printing matrix 3\n";
	matr3.print();

	//this is not a copy assignment, this is copy construction

	//Matrix<int>matr4;
	//matr4 = matr3 - this would be copy assignment

	Matrix<int> matr4 = matr3; //copy assignment
	std::cout<<"Printing matrix 4\n";
	matr4.print();
	
	Matrix<int> matr12(7,12,4);
	Matrix<int> matr5 = std::move(matr12);

	std::cout<<"Printing matrix 5\n";
	matr5.print();

	return 0;
}
