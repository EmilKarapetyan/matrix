#include<vector>
#include<iostream>
#include<exception>
#include<random>
 
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

		Matrix(const Matrix& matr)
			: m_height{matr.getHeight()}, m_width{matr.getWidth()}, m_data{m_height} {
			for (size_t hIdx = 0; hIdx < m_height; ++hIdx) {
				m_data[hIdx] = std::vector<T>(m_width);
				for (size_t wIdx = 0; wIdx <m_width ; ++wIdx) {
					m_data[hIdx][wIdx] = matr[hIdx][wIdx];
				}
			}
		}

		Matrix(Matrix&& matr) noexcept {
			m_width = matr.getWidth();
			m_height = matr.getHeight();
			m_data.resize(m_height);
			
			for (size_t hIdx = 0; hIdx < m_height; ++hIdx) {
				m_data[hIdx] = matr[hIdx];
			}
		}
		
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

		~Matrix() = default;

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

		inline void setValue(const size_t height, const size_t width, const T val) {
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

		void operator*=(T val) {
			for (size_t hIdx = 0; hIdx < m_height; ++hIdx) {
				for (size_t wIdx = 0; wIdx < m_width ; ++wIdx) {
					m_data[hIdx][wIdx] *= val;
				}
			}
		}

		void fillMatrix() {
			if (m_height == m_width) {
				for (int i = 0 ; i < m_height; ++i) {
					for (int j = 0; j < m_height; ++j) {
						m_data[i][j] = rand() % 10;
					}
				}
			}
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
