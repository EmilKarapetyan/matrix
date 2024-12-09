#include<vector>
#include<iostream>
#include<exception>
#include<memory>

template<typename T, typename = typename
	 std::enable_if_t<std::is_integral<T>::value>>
class Matrix final {

	public:
		Matrix() :  m_width{0}, m_height{0} {};
		Matrix(const size_t width, const size_t height, const T val=0) 
			: m_width{width}, m_height{height}, m_data(m_height) {
			m_data.resize(m_height);
			for (size_t hIdx = 0; hIdx < m_height; ++hIdx) {
				m_data[hIdx] = std::vector<T>(m_width);
			}

			for (size_t hIdx = 0; hIdx < m_height; ++hIdx) {
				for (size_t wIdx = 0; wIdx <m_width ; ++wIdx) {
					m_data[hIdx][wIdx] = val;
				}
			}
		}

		Matrix(const Matrix& matr)
			: m_width{matr.getWidth()}, m_height{matr.getHeight()}, m_data{m_height} {
			for (size_t hIdx = 0; hIdx < m_height; ++hIdx) {
				m_data[hIdx] = std::vector<T>(m_width);
				for (size_t wIdx = 0; wIdx <m_width ; ++wIdx) {
					m_data[hIdx][wIdx] = matr[hIdx][wIdx];
				}
			}
		}

		Matrix(Matrix&& matr) noexcept {
			m_height = matr.getHeight();
			m_width = matr.getWidth();

			m_data.resize(m_height);
			for (size_t hIdx = 0; hIdx < m_height; ++hIdx) {
				m_data[hIdx] = matr[hIdx];
			}
		}
		
		Matrix& operator=(const Matrix& matr) {
			if (&matr != this) {
				if (m_height != matr.getHeight() || m_width != matr.getWeight()) {
					m_height = matr.getHeight();
					m_width = matr.getWidth();

					m_data.resize(m_height);
					for (size_t hIdx = 0; hIdx < m_height; ++hIdx) {
						m_data[hIdx] = new std::vector<T>[m_width];
					}
				}
				for (size_t hIdx = 0; hIdx < m_height; ++hIdx) {
					for (size_t wIdx = 0; wIdx <m_width ; ++wIdx) {
						m_data[hIdx][wIdx] = matr[hIdx][wIdx];
					}
				}
			}
			return *this;
		}

		~Matrix() = default{
		//	delete[] m_data;
		}
		
		inline const size_t getWidth() const {
			return m_width;
		}

		inline const size_t getHeight() const {
			return m_height;
		}

		std::vector<T> operator[](size_t rowIdx) const {
			return m_data[rowIdx];
		}
		
		inline const std::vector<std::vector<T>*>& getData() const {
			return m_data;
		}
		inline void setWidth(const size_t width) {
			m_width = width;
		}

		inline void setHeight(const size_t height) {
			m_height = height;
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
