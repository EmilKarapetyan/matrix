#include <vector>
#include <iostream>
#include <exception>
#include <algorithm>

#include <random>
#include <time.h>
#include <cmath>


template<typename T, typename = typename
	 std::enable_if_t<std::is_integral<T>::value>>
class Matrix final {
	public:
		Matrix() :  m_row{0}, m_col{0} {};
		Matrix(const std::size_t row, const std::size_t col, const T val=0) 
			: m_row{row}, m_col{col}, m_data(m_row) {
			for (std::size_t rIdx = 0; rIdx < m_row; ++rIdx) {
				m_data[rIdx].resize(m_col, val);
			}
		}

		Matrix(const std::size_t row, const std::size_t col,
			   const std::initializer_list<std::initializer_list<T>>& initList)
			   : m_row{row}, m_col{col} 
		{
			if (initList.size() != row) {
				throw std::invalid_argument("Number of rows in initializer_list does not match row.");
			}
			for (const auto& row : initList) {
				m_data.emplace_back(row.begin(), row.end());
			}
		}

		Matrix(const std::initializer_list<std::initializer_list<T>>& initList)
		{
			std::size_t expected_col_size = initList.begin()->size();
			m_row = initList.size();
			m_col = expected_col_size;
			for (const auto& row : initList) {
				if (row.size() != expected_col_size)
				{
					throw std::invalid_argument("Number of cols in initializer_list are differentS.");
				}
				m_data.emplace_back(row.begin(), row.end());
			}
		}

		Matrix(const Matrix& matr) : m_row{matr.getRow()}, m_col{matr.getColumn()}, m_data{matr.m_data} {}
		Matrix(Matrix&& matr) 
			: m_col(std::move(matr.getColumn())),
			  m_row(std::move(matr.getRow())),
			  m_data(std::move(matr.m_data)) {}
		
		Matrix& operator=(Matrix<T>&& matr) 
		{
			m_col = std::move(matr.m_col);
			m_row = std::move(matr.m_row);
			m_data = std::move(matr.m_data);
			return *this;
		}
		Matrix& operator=(const Matrix& matr)
		{
			m_col = matr.getColumn();
			m_row = matr.getRow();
			m_data.assign(matr.m_data.begin(), matr.m_data.end());				
			return *this;
		}

		bool operator==(const Matrix& matr) const
		{
			if (matr.getRow() != m_row || matr.getColumn() != m_col)
			{
				return false;
			}

			for (std::uint32_t rIdx = 0; rIdx < m_row; ++rIdx) {
				for (std::uint32_t cIdx = 0; cIdx < m_col; ++cIdx) {
					if (m_data[rIdx][cIdx] != matr[rIdx][cIdx])
					{
						return false;
					}
				}
			}
			return true;
		}
		bool operator!=(const Matrix<T>& matr) const 
		{
        	return !(*this == matr);
    	}
		inline const std::size_t getColumn() const
		{
			return m_col;
		}
		inline const std::size_t getRow() const 
		{
			return m_row;
		}
		inline void setcol(const std::size_t col) 
		{
			m_col = col;
		}
		inline void setrow(const std::size_t row) 
		{
			m_row = row;
		}
		inline const std::vector<std::vector<T>*>& getData() const 
		{
			return m_data;
		}
		inline void setValue(const std::size_t row, const std::size_t col, const T val) 
		{
			m_data.at(row).at(col) = val;
		}
		inline T getValue(const std::size_t row, const std::size_t col) const 
		{
			return m_data[row][col];
		}
		T at(const std::uint32_t row, const std::size_t col) 
		{
			return m_data.at(row).at(col);
		}
		std::vector<T>& operator[](const std::size_t rocIdx)  
		{
			return m_data.at(rocIdx);
		}
		std::vector<T> operator[](const std::size_t rocIdx) const 
		{
			return m_data.at(rocIdx);
		}
		void operator*=(T val) {
			for (size_t rIdx = 0; rIdx < m_row; ++rIdx) {
				for (size_t cIdx = 0; cIdx < m_col ; ++cIdx) {
					m_data[rIdx][cIdx] *= val;
				}
			}
		}
		
		Matrix<T> get_submatrix(const std::uint32_t row, const std::uint32_t col) 
		{
			if (row < m_row && col < m_col) {
				Matrix<T> minor(m_row-1, m_col-1);
				std::uint32_t row = 0;
				std::uint32_t col = 0;
				for (std::uint32_t rIdx = 0; rIdx < m_row; ++rIdx) {
					col = 0;
					if (rIdx == row) {
						continue;
					}
					for (std::uint32_t cIdx = 0; cIdx < m_col; ++cIdx) {
						if (cIdx == col) {
							continue;
						}
						minor.setValue(row, col++, m_data[rIdx][cIdx]);
					}
					++row;
				}
				return minor;
			}
			return *this;
		}
    
		T determinant() const {
			if (m_row == 1) {
				return m_data[0][0];
			} else if (m_row == 2) {
				return m_data[0][0] * m_data[1][1] - m_data[0][1] * m_data[1][0];
			}

			T det = 0;
			for (std::size_t i = 0; i < m_col; ++i) {
				Matrix<int> submatrix(m_col - 1, m_row - 1 );
				std::uint32_t sub_i = 0;
				for (std::size_t j = 1; j < m_row; ++j) { 
					std::size_t sub_j = 0;
					for (std::size_t k = 0; k < m_col; ++k) {
						if (k != i) { 
							submatrix[sub_j++][sub_i] = m_data[k][j]; 
						}
					}
					sub_i++; 
				}

				det += m_data[i][0] * pow(-1, i) * submatrix.determinant();
			}

			return det;
		}

		void matrixProduct(const Matrix<T>& mat2, Matrix<T>& result) const 
		{
			Matrix<T> res(m_row, mat2.getColumn());

			const std::uint32_t row1 = m_row;
			const std::uint32_t col1 = m_col;
			const std::uint32_t row2 = mat2.getRow();
			if (col1 != row2) {
				throw std::out_of_range("Invalid Input");
			}

			const std::uint32_t col2 = mat2[0].size();
			for (std::uint32_t i = 0; i < row1; i++) {
				for (std::uint32_t j = 0; j < col2; j++) {
					for (std::uint32_t k = 0; k < col1; k++) {
						res.setValue(i, j, res[i][j] + (m_data[i][k] * mat2[k][j]));
					}
				}
			}
			result = std::move(res);
		}

		void transpose() 
		{
			for (std::uint32_t i = 0; i < m_row; ++i ) {
				for (std::uint32_t j = i+1; j < m_row; ++j) {
					std::swap(m_data[i][j], m_data[j][i]);
				}
			}
		}

		void print()
		{
			for (std::size_t rIdx = 0; rIdx < m_row; ++rIdx) {
				for (std::size_t cIdx = 0; cIdx < m_col; ++cIdx) {
					std::cout << m_data[rIdx][cIdx] << " ";
				}
				std::cout << std::endl;
			}
		}

		void fillMatrixWithRandomValues() 
		{
			const std::size_t upperLimit = 1000;
			std::random_device rd;
    		std::mt19937 gen(rd());
    		std::uniform_int_distribution<> dist(0, upperLimit);
			
			std::size_t rows = m_row;
			std::size_t cols = m_col;

			if (rows != cols) {
				return;
			}
			for (std::size_t i = 0; i < rows; ++i) {
				for (std::size_t j = 0; j < cols; ++j) {
					m_data[i][j] = dist(gen);
				}
			}
		}
	
	private:
		std::size_t m_row;
		std::size_t m_col;
		std::vector<std::vector<T>> m_data;
};
