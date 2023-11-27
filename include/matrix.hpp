#pragma once

#include <array>
#include <cstddef>
#include <string>

namespace GLRT {
template <size_t M, size_t N>
class Matrix {
   public:
	Matrix();
	Matrix(Matrix<M, N>&);
	Matrix(const Matrix<M, N>&);
	Matrix(std::array<std::array<double, N>, M>&);
	Matrix(const std::array<std::array<double, N>, M>&);
	~Matrix();

	std::array<double, N>& operator[](int i);
	const std::array<double, N>& operator[](int i) const;

	Matrix<M, N> operator+(const Matrix<M, N>&) const;
	Matrix<M, N> operator-(const Matrix<M, N>&) const;

	template <size_t P>
	Matrix<M, P> operator*(const Matrix<N, P>&) const;

	Matrix<M, N> operator+(const double&) const;
	Matrix<M, N> operator-(const double&) const;
	Matrix<M, N> operator*(const double&) const;
	Matrix<M, N> operator/(const double&) const;

	Matrix<M, N>& operator+=(const Matrix<M, N>&);
	Matrix<M, N>& operator-=(const Matrix<M, N>&);
	Matrix<M, N>& operator*=(const Matrix<M, N>&);
	Matrix<M, N>& operator/=(const Matrix<M, N>&);

	template <size_t P>
	Matrix<M, P>& operator*=(const Matrix<N, P>&);

	Matrix<M, N>& operator+=(const double&);
	Matrix<M, N>& operator-=(const double&);
	Matrix<M, N>& operator*=(const double&);
	Matrix<M, N>& operator/=(const double&);

	std::string to_string() const;

   protected:
	std::array<std::array<double, N>, M> m_data;
};

template <size_t M, size_t N>
Matrix<M, N>::Matrix() {
	for(int i = 0; i < M; ++i) {
		for(int j = 0; j < N; ++j) {
			m_data[i][j] = 0;
		}
	}
}

template <size_t M, size_t N>
Matrix<M, N>::Matrix(Matrix<M, N>& other) {
	for(int i = 0; i < M; ++i) {
		for(int j = 0; j < N; ++j) {
			m_data[i][j] = other[i][j];
		}
	}
}

template <size_t M, size_t N>
Matrix<M, N>::Matrix(const Matrix<M, N>& other) {
	for(int i = 0; i < M; ++i) {
		for(int j = 0; j < N; ++j) {
			m_data[i][j] = other[i][j];
		}
	}
}

template <size_t M, size_t N>
Matrix<M, N>::Matrix(std::array<std::array<double, N>, M>& data) {
	for(int i = 0; i < M; ++i) {
		for(int j = 0; j < N; ++j) {
			m_data[i][j] = data[i][j];
		}
	}
}

template <size_t M, size_t N>
Matrix<M, N>::Matrix(const std::array<std::array<double, N>, M>& data) {
	for(int i = 0; i < M; ++i) {
		for(int j = 0; j < N; ++j) {
			m_data[i][j] = data[i][j];
		}
	}
}

template <size_t M, size_t N>
Matrix<M, N>::~Matrix() {
}

template <size_t M, size_t N>
std::array<double, N>& Matrix<M, N>::operator[](int i) {
	return m_data[i];
}

template <size_t M, size_t N>
const std::array<double, N>& Matrix<M, N>::operator[](int i) const {
	return m_data[i];
}

template <size_t M, size_t N>
Matrix<M, N> Matrix<M, N>::operator+(const Matrix<M, N>& other) const {
	Matrix<M, N> result;
	for(int i = 0; i < M; ++i) {
		for(int j = 0; j < N; ++j) {
			result[i][j] = m_data[i][j] + other[i][j];
		}
	}
	return result;
}

template <size_t M, size_t N>
Matrix<M, N> Matrix<M, N>::operator-(const Matrix<M, N>& other) const {
	Matrix<M, N> result;
	for(int i = 0; i < M; ++i) {
		for(int j = 0; j < N; ++j) {
			result[i][j] = m_data[i][j] - other[i][j];
		}
	}
	return result;
}

template <size_t M, size_t N>
template <size_t P>
Matrix<M, P> Matrix<M, N>::operator*(const Matrix<N, P>& other) const {
	Matrix<M, P> result;
	for(int i = 0; i < M; ++i) {
		for(int j = 0; j < P; ++j) {
			for(int k = 0; k < N; ++k) {
				result[i][j] += m_data[i][k] * other[k][j];
			}
		}
	}
	return result;
}

template <size_t M, size_t N>
Matrix<M, N> Matrix<M, N>::operator+(const double& other) const {
	Matrix<M, N> result;
	for(int i = 0; i < M; ++i) {
		for(int j = 0; j < N; ++j) {
			result[i][j] = m_data[i][j] + other;
		}
	}
	return result;
}

template <size_t M, size_t N>
Matrix<M, N> Matrix<M, N>::operator-(const double& other) const {
	Matrix<M, N> result;
	for(int i = 0; i < M; ++i) {
		for(int j = 0; j < N; ++j) {
			result[i][j] = m_data[i][j] - other;
		}
	}
	return result;
}

template <size_t M, size_t N>
Matrix<M, N> Matrix<M, N>::operator*(const double& other) const {
	Matrix<M, N> result;
	for(int i = 0; i < M; ++i) {
		for(int j = 0; j < N; ++j) {
			result[i][j] = m_data[i][j] * other;
		}
	}
	return result;
}

template <size_t M, size_t N>
Matrix<M, N> Matrix<M, N>::operator/(const double& other) const {
	Matrix<M, N> result;
	if(other != 0) {
		for(int i = 0; i < M; ++i) {
			for(int j = 0; j < N; ++j) {
				result[i][j] = m_data[i][j] / other;
			}
		}
	}
	return result;
}

template <size_t M, size_t N>
Matrix<M, N>& Matrix<M, N>::operator+=(const Matrix<M, N>& other) {
	*this = *this + other;
	return *this;
}

template <size_t M, size_t N>
Matrix<M, N>& Matrix<M, N>::operator-=(const Matrix<M, N>& other) {
	*this = *this - other;
	return *this;
}

template <size_t M, size_t N>
Matrix<M, N>& Matrix<M, N>::operator*=(const Matrix<M, N>& other) {
	*this = *this * other;
	return *this;
}

template <size_t M, size_t N>
Matrix<M, N>& Matrix<M, N>::operator/=(const Matrix<M, N>& other) {
	*this = *this / other;
	return *this;
}

template <size_t M, size_t N>
template <size_t P>
Matrix<M, P>& Matrix<M, N>::operator*=(const Matrix<N, P>& other) {
	*this = *this * other;
	return *this;
}

template <size_t M, size_t N>
Matrix<M, N>& Matrix<M, N>::operator+=(const double& other) {
	*this = *this + other;
	return *this;
}

template <size_t M, size_t N>
Matrix<M, N>& Matrix<M, N>::operator-=(const double& other) {
	*this = *this - other;
	return *this;
}

template <size_t M, size_t N>
Matrix<M, N>& Matrix<M, N>::operator*=(const double& other) {
	*this = *this * other;
	return *this;
}

template <size_t M, size_t N>
Matrix<M, N>& Matrix<M, N>::operator/=(const double& other) {
	*this = *this / other;
	return *this;
}

template <size_t M, size_t N>
Matrix<M, N> operator+(const double& lhs, const Matrix<M, N>& rhs) {
	return rhs + lhs;
}

template <size_t M, size_t N>
Matrix<M, N> operator-(const double& lhs, const Matrix<M, N>& rhs) {
	return rhs - lhs;
}

template <size_t M, size_t N>
Matrix<M, N> operator*(const double& lhs, const Matrix<M, N>& rhs) {
	return rhs * lhs;
}

template <size_t M, size_t N>
Matrix<M, N> operator/(const double& lhs, const Matrix<M, N>& rhs) {
	Matrix<M, N> result;
	if(rhs != 0) {
		for(int i = 0; i < M; ++i) {
			for(int j = 0; j < N; ++j) {
				result[i][j] = lhs / rhs[i][j];
			}
		}
	}
	return result;
}

template <size_t M, size_t N>
std::string Matrix<M, N>::to_string() const {
	std::string result = "[";
	for(int i = 0; i < M; ++i) {
		result += "[";
		for(int j = 0; j < N; ++j) {
			result += std::to_string(m_data[i][j]);
			if(j != N - 1) {
				result += ", ";
			}
		}
		result += "]";
		if(i != M - 1) {
			result += ", ";
		}
	}
	result += "]";
	return result;
}
}  // namespace GLRT
