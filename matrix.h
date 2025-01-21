#include <vector>
#include <iostream>
#include <exception>
#include <algorithm>

#include <random>
#include <time.h>

template<typename T, typename = typename
	 std::enable_if_t<std::is_integral<T>::value>>
class Matrix final {
	public:
		Matrix() :  m_row{0}, m_col{0} {};

		Matrix(const std::size_t row, const std::size_t col, const T val=0) 
			: m_row{row}, m_col{col}, m_data(m_row) {
			for (std::size_t hIdx = 0; hIdx < m_row; ++hIdx) {
				m_data[hIdx].resize(m_col, val);
			}
		}
		
		Matrix(const std::size_t row, const size_t col,
			   const std::initializer_list<std::initializer_list<int>>& initList)
			   : m_row{row}, m_col{col} 
		{

			if (initList.size() != row) {
				throw std::invalid_argument("Number of rows in initializer_list does not match row.");
			}
			for (const auto& row : initList) {
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

			for (int hIdx = 0; hIdx < m_row; ++hIdx) {
				for (int wIdx = 0; wIdx < m_col; ++wIdx) {
					if (m_data[hIdx][wIdx] != matr[hIdx][wIdx])
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

		inline const size_t getColumn() const
		{
			return m_col;
		}
		inline const size_t getRow() const 
		{
			return m_row;
		}
		inline void setcol(const size_t col) 
		{
			m_col = col;
		}
		inline void setrow(const size_t row) 
		{
			m_row = row;
		}
		inline const std::vector<std::vector<T>*>& getData() const 
		{
			return m_data;
		}
		inline void setValue(const size_t row, const size_t col, const T val) 
		{
			m_data.at(row).at(col) = val;
		}
		inline T getValue(const size_t row, const size_t col) const 
		{
			return m_data[row][col];
		}
		T at(const size_t row, const size_t col) 
		{
			return m_data.at(row).at(col);
		}
		std::vector<T>& operator[](const size_t rowIdx)  
		{
			return m_data.at(rowIdx);
		}
		std::vector<T> operator[](const size_t rowIdx) const 
		{
			return m_data.at(rowIdx);
		}
		void operator*=(T val) {
			for (size_t hIdx = 0; hIdx < m_row; ++hIdx) {
				for (size_t wIdx = 0; wIdx < m_col ; ++wIdx) {
					m_data[hIdx][wIdx] *= val;
				}
			}
		}
		
		Matrix<T> get_submatrix(const size_t row, const size_t col) 
		{
			if (row < m_row && col < m_col) {
				Matrix<T> minor(m_row-1, m_col-1);
				int row = 0;
				int col = 0;
				for (std::uint32_t hIdx = 0; hIdx < m_row; ++hIdx) {
					col = 0;
					if (hIdx == row) {
						continue;
					}
					for (std::uint32_t wIdx = 0; wIdx < m_col; ++wIdx) {
						if (wIdx == col) {
							continue;
						}
						minor.setValue(row, col++, m_data[hIdx][wIdx]);
					}
					++row;
				}
				return minor;
			}
			return *this;
		}

		void getCofactorMatrix(Matrix<T>& tem, const size_t p1, const size_t q1, const size_t num) 
		{  
			std::uint32_t i = 0;
			std::uint32_t j = 0;
			for (std::uint32_t rows = 0; rows < num; ++rows) {
				for (std::uint32_t cols = 0; cols < num; ++cols) {    
					if (rows != p1 && cols != q1) {  
						tem.setValue(i, j++, m_data[rows][cols]);
						if (j == num - 1) {  
							j = 0;  
							++i;  
						}  
					}  
				}  
			}  
		}  
		
		std::int32_t get_determinant() {
        if (m_row != m_col) {
            throw std::invalid_argument("Matrix must be square to calculate determinant.");
        }

        Matrix<int> matrix(*this);
        T det = 1;

        for (std::size_t i = 0; i < m_row; ++i) {
            std::size_t max_row = i;
            for (std::size_t j = i + 1; j < m_row; ++j) {
            if (std::abs(matrix[j][i]) > std::abs(matrix[max_row][i])) {
                    max_row = j;
                }
            }

            if (matrix[max_row][i] == 0) 
			{
                return 0;
            }

            if (max_row != i) 
			{
                std::swap(matrix[max_row], matrix[i]);
                det *= -1;
            }

            for (std::size_t j = i + 1; j < m_row; ++j) {
                double factor = matrix[j][i] / matrix[i][i];
                for (size_t k = i; k < m_row; ++k) {
                    matrix[j][k] -= factor * matrix[i][k];
                }
            }
        }

        // Multiply diagonal elements to get the determinant
        for (std::size_t i = 0; i < m_row; ++i) {
            det *= matrix[i][i];
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
			for (std::uint32_t hIdx = 0; hIdx < m_row; ++hIdx) {
				for (std::uint32_t wIdx = 0; wIdx < m_col; ++wIdx) {
					std::cout << m_data[hIdx][wIdx] << " ";
				}
				std::cout << std::endl;
			}
		}

		void fillMatrixWithRandomValues() 
		{
			if (m_row == m_col) {
				std::mt19937 rng; //TODO google this
				srand(time(NULL));
				for (int i = 0 ; i < m_row; ++i) {
					for (int j = 0; j < m_row; ++j) {
						m_data[i][j] = rand() % 10;
					}
				}
				
#ifdef DEBUG
				m_data[0][0] = 4;
				m_data[0][1] = 3;
				m_data[0][2] = 2;
				m_data[0][3] = 2;
				m_data[1][0] = 0;
				m_data[1][1] = 1;
				m_data[1][2] = -3;
				m_data[1][3] = 3;
				m_data[2][0] = 0;
				m_data[2][1] = -1;
				m_data[2][2] = 3;
				m_data[2][3] = 3;
				m_data[3][0] = 0;
				m_data[3][1] = 3;
				m_data[3][2] = 1;
				m_data[3][3] = 1;
#endif
			}
		}
	
	private:
		size_t m_col;
		size_t m_row;
		std::vector<std::vector<T>> m_data;
};
