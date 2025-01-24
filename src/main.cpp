// Includes from this project

// Includes from third-party projects (like Boost, Poco, etc.)

// Includes from C++ Standard Library

#include <iostream>
#include <random>

#include "matrix.h"

//#include <googletest/gtest.h>

bool test_copy_assignment_operator()
{
    Matrix<std::int32_t> mtx(4, 4, 1);
    Matrix<std::int32_t> mat_second;
    mat_second = mtx;

    bool failed = false;
    for (std::uint32_t i = 0; i < 4; ++i)
    {
        for (std::uint32_t j = 0; j < 4; ++j)
        {
            if (mtx[i][j] != mat_second[i][j])
            {
                std::cout << "TEST FAILED: mtx assignment operator"
                          << std::endl;
                return failed;
            }
        }
    }
    std::cout << "TEST SUCCEED: mtx assigmnet operaotr" << std::endl;
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
    for (std::uint32_t i = 0; i < 4; ++i)
    {
        for (std::uint32_t j = 0; j < 4; ++j)
        {
            if (mtx_copy[i][j] != mtx[i][j])
            {
                std::cout << "TEST FAILED: mtx move assignment operator"
                          << std::endl;
                return failed;
            }
        }
    }
    std::cout << "TEST SUCCEED: mtx move assigmnet operaotr" << std::endl;
    return true;
}

bool test_matrix_scalar_multiplication()
{
    const std::int32_t multiplier = 4;
    Matrix<std::int32_t> matr1(6, 6, 5);
    Matrix<std::int32_t> matr2 = matr1;
    matr2 *= multiplier;

    std::uint32_t mtxrow = matr1.getRow();
    std::uint32_t mtxcol = matr1.getColumn();
    bool failed = false;
    if (mtxrow != matr2.getRow() || mtxcol != matr2.getColumn())
    {
        std::cout << "TEST FAILED: mtx scalar multiplication" << std::endl;
        return failed;
    }

    for (std::uint32_t i = 0; i < mtxrow; ++i)
    {
        for (std::uint32_t j = 0; j < mtxcol; ++j)
        {
            if ((matr1[i][j]) * multiplier != matr2[i][j])
            {
                std::cout << "TEST FAILED: mtx multiplication" << std::endl;
                return failed;
            }
        }
    }
    std::cout << "TEST SUCCEED: mtx scalar multiplication" << std::endl;
    return true;
}

bool test_matrix_product()
{
    Matrix<std::int32_t> res;
    Matrix<std::int32_t> matr1(3, 3, {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}});

    Matrix<std::int32_t> matr2(3, 7,
                               {{1, 2, 3, 4, 5, 6, 7},
                                {8, 9, 10, 11, 12, 13, 14},
                                {15, 16, 17, 18, 19, 20, 21}});

    Matrix<std::int32_t> product_golden_1(
        3, 7,
        {{62, 68, 74, 80, 86, 92, 98},
         {134, 149, 164, 179, 194, 209, 224},
         {206, 230, 254, 278, 302, 326, 350}});

    matr1.matrixProduct(matr2, res);

    if (res != product_golden_1)
    {
        std::cout << "TEST FAILED: mtx product" << std::endl;
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

    Matrix<std::int32_t> product_golden_2(
        6, 8,
        {{335, 350, 365, 380, 395, 410, 425, 440},
         {760, 800, 840, 880, 920, 960, 1000, 1040},
         {1185, 1250, 1315, 1380, 1445, 1510, 1575, 1640},
         {1610, 1700, 1790, 1880, 1970, 2060, 2150, 2240},
         {2035, 2150, 2265, 2380, 2495, 2610, 2725, 2840},
         {2460, 2600, 2740, 2880, 3020, 3160, 3300, 3440}});

    matr3.matrixProduct(matr4, res);
    if (res != product_golden_2)
    {
        std::cout << "TEST FAILED: mtx product" << std::endl;
        return false;
    }

    std::cout << "TEST SUCCEED: mtx product" << std::endl;
    return true;
}

bool test_determinant_calculation()
{
    std::int32_t matr1_det_golden = -21588;
    Matrix<int> matr1(3, 3, {{68, 46, 97}, {88, 21, 35}, {76, 9, 17}});

    if (matr1_det_golden != matr1.determinant())
    {
        std::cout << "TEST FAILED: mtx determinant" << std::endl;
        return false;
    }

    std::int32_t matr2_det_golden = -5730641;
    Matrix<int> matr2(4, 4,
                      {{71, 60, 42, 80},
                       {12, 90, 59, 12},
                       {19, 97, 63, 82},
                       {40, 27, 36, 9}});

    if (matr2_det_golden != matr2.determinant())
    {
        std::cout << "TEST FAILED: mtx determinant" << std::endl;
        return false;
    }

    std::int64_t matr3_det_golden = -45649600708;
    Matrix<std::int64_t> matr3(6, 6,
                               {{56, 89, 32, 71, 64, 43},
                                {22, 57, 88, 13, 45, 90},
                                {3, 78, 19, 67, 39, 24},
                                {94, 26, 59, 51, 12, 82},
                                {81, 68, 73, 36, 85, 21},
                                {47, 15, 92, 50, 34, 77}});

    if (matr3_det_golden != matr3.determinant())
    {
        std::cout << "TEST FAILED: mtx determinant" << std::endl;
        return false;
    }

    std::cout << "TEST SUCCEED: mtx determinant" << std::endl;
    return true;
}

bool test_matrix_transpose()
{
    Matrix<std::int32_t> res;
    Matrix<std::int32_t> matr1(4, 4,
                               {{11, 24, 35, 46},
                                {57, 68, 79, 80},
                                {91, 12, 23, 34},
                                {45, 56, 67, 78}});

    Matrix<std::int32_t> matr1_golden_transpose(4, 4,
                                                {{11, 57, 91, 45},
                                                 {24, 68, 12, 56},
                                                 {35, 79, 23, 67},
                                                 {46, 80, 34, 78}});

    matr1.transpose();
    if (matr1 != matr1_golden_transpose)
    {
        std::cout << "TEST FAILED: mtx transpose" << std::endl;
        return false;
    }

    Matrix<std::int32_t> matr2(5, 5,
                               {{12, 45, 78, 34, 56},
                                {67, 89, 23, 12, 45},
                                {90, 34, 67, 89, 12},
                                {56, 78, 90, 23, 34},
                                {45, 12, 34, 56, 78}});

    Matrix<std::int32_t> matr2_golden_transpose(5, 5,
                                                {{12, 67, 90, 56, 45},
                                                 {45, 89, 34, 78, 12},
                                                 {78, 23, 67, 90, 34},
                                                 {34, 12, 89, 23, 56},
                                                 {56, 45, 12, 34, 78}});

    matr2.transpose();

    if (matr2 != matr2_golden_transpose)
    {
        std::cout << "TEST FAILED: mtx transpose" << std::endl;
        return false;
    }

    Matrix<std::int32_t> matr3(8, 8,
                               {{12, 34, 56, 78, 90, 11, 22, 33},
                                {44, 55, 66, 77, 88, 99, 10, 20},
                                {21, 32, 43, 54, 65, 76, 87, 98},
                                {19, 28, 37, 46, 57, 68, 79, 80},
                                {81, 72, 63, 54, 45, 36, 27, 18},
                                {17, 26, 35, 44, 53, 62, 71, 82},
                                {83, 74, 65, 56, 47, 38, 29, 10},
                                {11, 22, 33, 44, 55, 66, 77, 88}});

    Matrix<std::int32_t> matr3_golden_transpose(
        8, 8,
        {{12, 44, 22, 19, 81, 17, 83, 11},
         {34, 55, 32, 28, 72, 26, 74, 22},
         {56, 66, 43, 37, 63, 35, 65, 33},
         {78, 77, 54, 46, 54, 44, 56, 44},
         {90, 88, 65, 57, 45, 53, 47, 55},
         {11, 99, 76, 68, 36, 62, 38, 66},
         {22, 10, 87, 79, 27, 71, 29, 77},
         {33, 20, 98, 80, 18, 82, 10, 88}});

    matr3.transpose();
    if (matr3 != matr3_golden_transpose)
    {
        std::cout << "TEST FAILED: mtx transpose" << std::endl;
        return false;
    }

    std::cout << "TEST SUCCEED: mtx transpose" << std::endl;
    return true;
}

bool test_functionality()
{
    return (test_copy_assignment_operator() & test_move_assignment_operator() &
            test_matrix_scalar_multiplication() & test_matrix_product() &
            test_determinant_calculation() & test_matrix_transpose());
}

int main()
{
    if (test_functionality())
    {
        std::cout << "####################" << std::endl;
        std::cout << "ALL THE TEST PASSED! Ibrahim ջան" << std::endl;
        std::cout << "####################" << std::endl;
    }

    return 0;
}
