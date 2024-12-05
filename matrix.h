#include<vector>
#include<iostream>
#include<exception>
#include<memory>
template<typename T>
class Matrix {

	public:
		Matrix() :  m_width{0}, m_height{0}, m_matrix{nullptr} {};
		Matrix(size_t width, size_t height, T val=0) : m_width{width}, m_height{height} {
			m_matrix.resize(m_height);
			for (size_t hIdx = 0; hIdx < m_height; ++hIdx) {
				m_matrix[hIdx] = std::make_shared<std::vector<T>>(m_width);
			}

			for (size_t hIdx = 0; hIdx < m_height; ++hIdx) {
				for (size_t wIdx = 0; wIdx <m_width ; ++wIdx) {
					m_matrix[hIdx]->at(wIdx) = val;
				}
			}
		}

		Matrix(const Matrix& matr) : Matrix(matr.getWidth(), matr.getHeight()) {
			for (size_t hIdx = 0; hIdx < m_height; ++hIdx) {
				for (size_t wIdx = 0; wIdx <m_width ; ++wIdx) {
					m_matrix[hIdx]->at(wIdx) = matr.getCellValue(hIdx, wIdx);
				}
			}
		}

		Matrix(Matrix&& matr) noexcept {
			m_height = matr.getHeight();
			m_width = matr.getWidth();

			m_matrix.resize(m_height);
			for (size_t hIdx = 0; hIdx < m_height; ++hIdx) {
				m_matrix[hIdx] = matr[hIdx];
			}
		}
		
		Matrix& operator=(const Matrix& matr) {
			if (&matr != this) {
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

		~Matrix() {
		//	delete[] m_matrix;
		}
		
		const T& getCellValue(size_t height, size_t width) const {
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
		inline void setWidth(size_t width) {
			m_width = width;
		}

		inline void setHeight(size_t height) {
			m_height = height;
		}

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
		std::vector<std::shared_ptr<std::vector<T>>> m_matrix;
};
