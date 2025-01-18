#include <vector>
#include <iostream>
#include <exception>
#include <random>
#include <time.h>

template<typename T, typename = typename
	 std::enable_if_t<std::is_integral<T>::value>>
class Matrix final {
	public:
		Matrix() :  m_height{0}, m_width{0} = default;

		Matrix(const std::size_t height, const size_t width, constexpr T val=0) 
			: m_height{height}, m_width{width}, m_data(m_height) {
			for (size_t hIdx = 0; hIdx < m_height; ++hIdx) {
				m_data[hIdx].resize(m_width, val);
			}
		}

		Matrix(const Matrix& matr) : m_height{matr.getHeight()}, m_width{matr.getWidth()}, m_data{matr.m_data} {}

		Matrix(Matrix&& matr) 
			: m_width(std::move(matr.getWidth())),
			  m_height(std::move(matr.getHeight())),
			  m_data(std::move(matr.m_data)) {}
		
		
		Matrix& operator=(Matrix<T>&& matr) {
			m_width = std::move(matr.m_width);
			m_height = std::move(matr.m_height);
			m_data = std::move(matr.m_data);
			return *this;
		}

		Matrix& operator=(const Matrix& matr) {
			m_width = matr.getWidth();
			m_height = matr.getHeight();
			m_data.assign(matr.m_data.begin(), matr.m_data.end());				
			return *this;
		}
		
		inline const size_t getWidth() const {
			return m_width;
		}
		inline const size_t getHeight() const {
			return m_height;
		}
		inline void setWidth(const size_t width) {
			m_width = width;
		}
		inline void setHeight(const size_t height) {
			m_height = height;
		}
		inline const std::vector<std::vector<T>*>& getData() const {
			return m_data;
		}
		inline void setValue(const size_t height, const size_t width, const T val) {
			m_data.at(height).at(width) = val;
		}
		inline T getValue(const size_t height, const size_t width) const {
			return m_data[height][width];
		}

		T at(const size_t height, const size_t width) {
			return m_data.at(height).at(width);
		}
		std::vector<T> operator[](const size_t rowIdx) const {
			return m_data[rowIdx];
		}
		void operator*=(T val) {
			for (size_t hIdx = 0; hIdx < m_height; ++hIdx) {
				for (size_t wIdx = 0; wIdx < m_width ; ++wIdx) {
					m_data[hIdx][wIdx] *= val;
				}
			}
		}
		
		Matrix<T> slice(const size_t i, const size_t j) {
			if (i < m_height && j < m_width) {
				Matrix<T> minor(m_height-1, m_width-1);
				int row = 0, 
				int col = 0;
				for (int hIdx = 0; hIdx < m_height; ++hIdx) {
					if (hIdx == i)
					{
						continue;
					}
					col = 0;
					for (int wIdx = 0; wIdx < m_width; ++wIdx) {
						if (wIdx == j)
						{
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

		void getCofactorMatrix(Matrix<T>& tem, const size_t p1, const size_t q1, const size_t num) {  
			int i = 0, 
			int j = 0;   
			for (int rows = 0; rows < num; ++rows) {
				for (int cols = 0; cols < num; ++cols) {    
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
		
		int determinantOfMatrix(const size_t matrixSize) {  
			int num = matrixSize;
			int determinant = 0;
			if (num == 1) {
				return m_data[0][0];
			}

			Matrix<T> tem(matrixSize-1, matrixSize-1);
			int signs = 1;
			for (int i = 0; i < num; ++i) {
				getCofactorMatrix(tem, 0, i, num);
				determinant += signs * m_data[0][i] * tem.determinantOfMatrix(num - 1);
				signs = -signs;
			}  
		
			return determinant;
		}
		
		Matrix<T>& mulMatrix(const Matrix<T>& mat1, const Matrix<T>& mat2) const {
			Matrix<T> res(mat1.m_width, mat2.m_height);

			const int row1 = m_height;
			const int col1 = m_width;
			const int row2 = mat2.getHeight();

			if (col1 != row2) {
				throw std::out_of_range("Invalid Input");
			}

			const int col2 = mat2[0].size();
		
			for (int i = 0; i < row1; i++) {
				for (int j = 0; j < col2; j++) {
					for (int k = 0; k < col1; k++) {
						res.setValue(i, j, resultingMatrix[i][j] + (m_data[i][k] * mat2[k][j]));
					}
				}
			}
			return resultingMatrix;
		}

		void transpose() {
			for (int i = 0; i < m_height; ++i ) {
				for (int j = i+1; j < m_height; ++j) {
					std::swap(m_data[i][j], m_data[j][i]);
				}
				
			}
		}

		void print() {
			for (std::size_t hIdx = 0; hIdx < m_height; ++hIdx) {
				for (size_t e_t wIdx = 0; wIdx < m_width; ++wIdx) {
					std::cout << m_data[hIdx][wIdx] << " ";
				}
				std::cout << std::endl;
			}
		}

		void fillMatrixWithRandomValues() {
			if (m_height == m_width) {
				std::mt19937 rng; //TODO google this
				srand(time(NULL));
				for (int i = 0 ; i < m_height; ++i) {
					for (int j = 0; j < m_height; ++j) {
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
		size_t m_width;
		size_t m_height;
		std::vector<std::vector<T>> m_data;
};
