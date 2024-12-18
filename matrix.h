#include<vector>
#include<iostream>
#include<exception>
#include<random>
#include <time.h>

 
template<typename T, typename = typename
	 std::enable_if_t<std::is_integral<T>::value>>
class Matrix final {
	public:
		Matrix() :  m_height{0}, m_width{0} {};
		Matrix(const size_t height, const size_t width, const T val=0) 
			: m_height{height}, m_width{width}, m_data(m_height) {
			m_data.resize(m_height);
			for (size_t hIdx = 0; hIdx < m_height; ++hIdx) {
				m_data[hIdx] = std::vector<T>(m_width);
			}

			for (size_t hIdx = 0; hIdx < m_height; ++hIdx) {
				for (size_t wIdx = 0; wIdx < m_width; ++wIdx) {
					m_data[hIdx][wIdx] = val;
				}
			}
		}

		//copy constructor
		Matrix(const Matrix& matr)
			: m_height{matr.getHeight()}, m_width{matr.getWidth()}, m_data{m_height} {
			for (size_t hIdx = 0; hIdx < m_height; ++hIdx) {
				m_data[hIdx] = std::vector<T>(m_width);
				for (size_t wIdx = 0; wIdx <m_width ; ++wIdx) {
					m_data[hIdx][wIdx] = matr[hIdx][wIdx];
				}
			}
		}

		//move constructor
		Matrix(Matrix&& matr) noexcept {
			m_width = matr.getWidth();
			m_height = matr.getHeight();
			m_data.resize(m_height);
			
			for (size_t hIdx = 0; hIdx < m_height; ++hIdx) {
				m_data[hIdx] = matr[hIdx];
			}
		}
		
		//move assignment
		Matrix& operator=(Matrix<T>&& matr) {  // revisit
			if (&matr != this) {
				m_width = matr.getWidth();
				m_height = matr.getHeight();
				m_data.resize(m_height);
				for (size_t hIdx = 0; hIdx < m_height; ++hIdx) {
					m_data[hIdx] = std::move(matr[hIdx]);
				}
			}
			return *this;
		}

		//copy assignment
		Matrix& operator=(const Matrix& matr) {
			if (&matr != this) {
				if (m_height != matr.getHeight() || m_width != matr.getWeight()) {
					m_width = matr.getWidth();
					m_height = matr.getHeight();
					m_data.resize(m_height);

					for (size_t hIdx = 0; hIdx < m_height; ++hIdx) {
						m_data[hIdx] = new std::vector<T>[m_width];
					}
				}
				for (size_t hIdx = 0; hIdx < m_height; ++hIdx) {
					for (size_t wIdx = 0; wIdx < m_width ; ++wIdx) {
						m_data[hIdx][wIdx] = matr[hIdx][wIdx];
					}
				}
			}
			return *this;
		}

		//default destructor
		~Matrix() = default;
		
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
			if (height >= m_height || width >= m_width)
				throw std::out_of_range("index is out of range");
			m_data[height][width] = val;
		}
		inline T getValue(const size_t height, const size_t width) const {
			return m_data[height][width];
		}
		T at(const size_t height, const size_t width) {
			if (height >= m_height || width >= m_width) {
				throw std::out_of_range("index is out of range");
			}

			return m_data[height][width];
		}
		std::vector<T> operator[](size_t rowIdx) const {
			return m_data[rowIdx];
		}
		void operator*=(T val) {
			for (size_t hIdx = 0; hIdx < m_height; ++hIdx) {
				for (size_t wIdx = 0; wIdx < m_width ; ++wIdx) {
					m_data[hIdx][wIdx] *= val;
				}
			}
		}
		void fillMatrix() {
			if (m_height == m_width) {
				srand(time(NULL));
				for (int i = 0 ; i < m_height; ++i) {
					for (int j = 0; j < m_height; ++j) {
						m_data[i][j] = rand() % 10;
					}
				}
				
				//debugging
				/*m_data[0][0] = 4;
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
				m_data[3][3] = 1;*/
			}
		}

		Matrix<T> divide(const size_t i, const size_t j) {
			if (i < m_height && j < m_width) {
				Matrix<T> minor(m_height-1, m_width-1);
				int row = 0, col = 0;
				for (int hIdx = 0; hIdx < m_height; ++hIdx) {
					if ( hIdx == i)
						continue;
					col = 0;
					for (int wIdx = 0; wIdx < m_width; ++wIdx) {
						if (wIdx == j)
							continue;
						minor.setValue(row, col++, m_data[hIdx][wIdx]);
					}
					++row;
				}
				return minor;
			}
			return *this;
		}

		// Function for finding the cofactor  
		// matrix[p][q] in tem[][]. num is  
		// the current values of matrix[][]  
		void getCofactorMatrix(Matrix<T>& tem, int p1, int q1, int num) {  
			int i = 0, j = 0;  
			//Loop for iterating of the matrix  
			for (int rows = 0; rows < num; ++rows) {
				for (int cols = 0; cols < num; ++cols) {  
					// Transferring into a temporary matrix   
					// just those elements that are not in the supplied row and column  
					if (rows != p1 && cols != q1) {  
						tem.setValue(i, j++, m_data[rows][cols]);
		
						// Because the row is complete, increase the row index as well as reset the cols index.  
						if (j == num - 1) {  
							j = 0;  
							++i;  
						}  
					}  
				}  
			}  
		}  
		
		/* A recursive function for determining the determinant of a matrix, where num is the current length of the matrix[][].*/
		int determinantOfMatrix(const size_t matrixSize) {  
			int num = matrixSize;
			int determinant = 0;
			if (num == 1) {
				return m_data[0][0];
			}
		
			// for storing the co-factors  
			Matrix<T> tem(4, 4); // TODO need to deal with this asap.
			int signs = 1;
			for (int i = 0; i < num; ++i) { //iterating over each element
				getCofactorMatrix(tem, 0, i, num);
				determinant += signs * m_data[0][i] * tem.determinantOfMatrix(num - 1);
				signs = -signs;  
			}  
		
			return determinant;
		}   			

		void transpose() {
			for (int i = 0; i < m_height; ++i ) {
				for (int j = i+1; j < m_height; ++j) {
					std::swap(m_data[i][j], m_data[j][i]);
				}
				
			}
		}

		void print() {
			if (m_data.empty()) {
				return;
			}

			for (size_t hIdx = 0; hIdx < m_height; ++hIdx) {
				for (size_t wIdx = 0; wIdx <m_width ; ++wIdx) {
					std::cout<< m_data[hIdx][wIdx] << " ";
				}
				std::cout<<"\n";
			}
		}
	
	private:
		size_t m_width;
		size_t m_height;
		std::vector<std::vector<T>> m_data;
};
