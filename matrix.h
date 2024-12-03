#include<vector>
#include<iostream>
#include<exception>

template<typename T>
class Matrix {

	public:
		Matrix() :  m_width{0}, m_height{0}, m_matrix{nullptr} {};
		Matrix(size_t width, size_t height, T val=0) : m_width{width}, m_height{height} {
			if (m_width < 0 || m_height < 0) 
				throw std::invalid_argument("Invalid arguments.");

			m_matrix = new T*[m_height];
			for (size_t hIdx = 0; hIdx < m_height; ++hIdx) {
				m_matrix[hIdx] = new T[m_width];
			}

			for (size_t hIdx = 0; hIdx < m_height; ++hIdx) {
				for (size_t wIdx = 0; wIdx <m_width ; ++wIdx) {
					m_matrix[hIdx][wIdx] = val;
				}
			}
		}

		Matrix(const Matrix& matr) : Matrix(matr.getWidth(), matr.getHeight()) {
			for (size_t hIdx = 0; hIdx < m_height; ++hIdx) {
				for (size_t wIdx = 0; wIdx <m_width ; ++wIdx) {
					m_matrix[hIdx][wIdx] = matr.getCellValue(hIdx, wIdx);
				}
			}
		}

		Matrix(Matrix&& matr) noexcept {
			m_height = matr.getHeight();
			m_width = matr.getWidth();

			m_matrix = new T*[m_height];
			for (size_t hIdx = 0; hIdx < m_height; ++hIdx) {
				m_matrix[hIdx] = matr[hIdx];
			}
			std::cout<<__PRETTY_FUNCTION__<<" : "<<__LINE__<<"\n";
			if ( matr.getMatrix() == nullptr) 
				std::cout<<"WE HAVE NULLPTR HERE\n";
			delete [] matr.getMatrix();
			std::cout<<__PRETTY_FUNCTION__<<" : "<<__LINE__<<"\n";
		}
		
		Matrix& operator=(const Matrix& matr) {
			if (&matr != this) {
				if (m_height != matr.getHeight() || m_width != matr.getWeight()) {
					for (size_t hIdx = 0; hIdx < m_height; ++hIdx) {
						delete[] m_matrix[hIdx];
					}
					delete[] m_matrix;
					
					m_height = matr.getHeight();
					m_width = matr.getWidth();

					m_matrix = new T*[m_height];
					for (size_t hIdx = 0; hIdx < m_height; ++hIdx) {
						m_matrix[hIdx] = new T[m_width];
					}
				}
				for (size_t hIdx = 0; hIdx < m_height; ++hIdx) {
					for (size_t wIdx = 0; wIdx <m_width ; ++wIdx) {
						m_matrix[hIdx][wIdx] = matr.getCellValue(hIdx, wIdx);
					}
				}
			}
			return *this;
		}

		~Matrix() {
			for (size_t hIdx = 0; hIdx < m_height; ++hIdx) {
				delete[] m_matrix[hIdx];
			}
		//	delete[] m_matrix;
		}
		
		/*size_t getDet() {
			if (m_height != m_width)
				throw ...;

			for (size_t hIdx = 0; hIdx < m_height; ++hIdx) {
				for (size_t wIdx = 0; wIdx <m_width ; ++wIdx) {

				}
			}
		}*/

		const T& getCellValue(size_t height, size_t width) const {
			return m_matrix[height][width];
		}

		inline const size_t getWidth() const {
			return m_width;
		}

		inline const size_t getHeight() const {
			return m_height;
		}

		 T* operator[](size_t rowIdx) const {
			return m_matrix[rowIdx];
		}
		
		inline T** getMatrix() const {
			return m_matrix;
		}
		inline void setWidth(size_t width) {
			m_width = width;
		}

		inline void setHeight(size_t height) {
			m_height = height;
		}

		void print() {
			if (m_matrix == nullptr)
				return;
			for (size_t hIdx = 0; hIdx < m_height; ++hIdx) {
				for (size_t wIdx = 0; wIdx <m_width ; ++wIdx) {
					std::cout<< m_matrix[hIdx][wIdx] << " ";
				}
				std::cout<<"\n";
			}
		}
	
	private:
		size_t m_width;
		size_t m_height;
		T** m_matrix;
};
