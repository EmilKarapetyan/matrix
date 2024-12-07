#include<vector>
#include<iostream>
#include<exception>
#include<memory>

//Declare class as final, as you don't expect it to be derived from (or add virtual destructor)

//template arg should be only integral-typed (std::complex, double, int, etc.) due to my message via Telegram, fix this
template<typename T>
class Matrix {

	public:
		//m_matrix is not a pointer, this initialization is wrong
		Matrix() :  m_width{0}, m_height{0}, m_matrix{nullptr} {};
		
		//make width height and val const
		//you can add m_matrix resize in constructr initializer list as well - ": m_matrix(height)"
		Matrix(size_t width, size_t height, T val=0) : m_width{width}, m_height{height} {
			m_matrix.resize(m_height);
			for (size_t hIdx = 0; hIdx < m_height; ++hIdx) {
				//why do you keep pointers here? why not just vectors?
				m_matrix[hIdx] = std::make_shared<std::vector<T>>(m_width);
			}

			for (size_t hIdx = 0; hIdx < m_height; ++hIdx) {
				for (size_t wIdx = 0; wIdx <m_width ; ++wIdx) {
                                        //m_width is already checked, at is redundant
					m_matrix[hIdx]->at(wIdx) = val;
				}
			}
		}

		//Why do you call constructor here? 
		//the correct way would be to initialize members with passed object's members in constructor's initializer list
		Matrix(const Matrix& matr) : Matrix(matr.getWidth(), matr.getHeight()) {
			for (size_t hIdx = 0; hIdx < m_height; ++hIdx) {
				for (size_t wIdx = 0; wIdx <m_width ; ++wIdx) {
					//wIdx is checked and at is redundant
					m_matrix[hIdx]->at(wIdx) = matr.getCellValue(hIdx, wIdx);
				}
			}
		}

		Matrix(Matrix&& matr) noexcept {
			m_height = matr.getHeight();
			m_width = matr.getWidth();

			m_matrix.resize(m_height);
			//please use std::size_t everywhere instead of size_t
			
			for (size_t hIdx = 0; hIdx < m_height; ++hIdx) {
				m_matrix[hIdx] = matr[hIdx];
			}
		}
		
		Matrix& operator=(const Matrix& matr) {
			//This check is not always used as case where you assign some A to A itself is almost never happening case
			//in embedded systems for example this check can be quite expensive
			if (&matr != this) {
				//Here I believe you don't need this check, it may cause some logic error
				//you might want to make your assignments no matter what
				if (m_height != matr.getHeight() || m_width != matr.getWeight()) {
					m_height = matr.getHeight();
					m_width = matr.getWidth();

					m_matrix.resize(m_height);
					for (size_t hIdx = 0; hIdx < m_height; ++hIdx) {
						m_matrix[hIdx] = new std::vector<T>[m_width];
					}
				}
				for (size_t hIdx = 0; hIdx < m_height; ++hIdx) {
					for (size_t wIdx = 0; wIdx <m_width ; ++wIdx) {
						m_matrix[hIdx]->at(wIdx) = matr.getCellValue(hIdx, wIdx);
					}
				}
			}
			return *this;
		}

		//Destructor is redundant, it could be removed or default-initialized
		~Matrix() {
		//	delete[] m_matrix;
		}
		
		//arguments should be const
		const T& getCellValue(size_t height, size_t width) const {
			// at is obsolete - see explanation above
			return m_matrix[height]->at(width);
		}

		inline const size_t getWidth() const {
			return m_width;
		}

		inline const size_t getHeight() const {
			return m_height;
		}

		std::shared_ptr<std::vector<T>> operator[](size_t rowIdx) const {
			return m_matrix[rowIdx];
		}
		
		inline  std::vector<std::vector<T>*> getMatrix() const {
			return m_matrix;
		}
		//make argument constant
		inline void setWidth(size_t width) {
			m_width = width;
		}

		//make argument constant
		inline void setHeight(size_t height) {
			m_height = height;
		}

		//add braces for if statement, even if it's single-lined
		void print() {
			if (m_matrix.empty())
				return;
			for (size_t hIdx = 0; hIdx < m_height; ++hIdx) {
				for (size_t wIdx = 0; wIdx <m_width ; ++wIdx) {
					std::cout<< m_matrix[hIdx]->at(wIdx) << " ";
				}
				std::cout<<"\n";
			}
		}
	
	private:
		size_t m_width;
		size_t m_height;
		//your class is called matrix and you have a m_matrix member
		//this could be renamed to m_raw_data or m_data for better understanding of underlying structure
		std::vector<std::shared_ptr<std::vector<T>>> m_matrix;
};
