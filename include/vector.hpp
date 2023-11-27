#pragma once

#include <array>
#include <cmath>
#include <ostream>

namespace GLRT {

template <size_t N>
class Vector {
   public:
	Vector();
	Vector(const std::array<double, N>&);
	Vector(const Vector<N>&);
	Vector(const Vector<N - 1>&, double);
	~Vector();

	double& operator[](int);
	const double& operator[](int) const;

	Vector<N> operator+(const Vector<N>&) const;
	Vector<N> operator-(const Vector<N>&) const;
	Vector<N> operator*(const Vector<N>&) const;
	Vector<N> operator/(const Vector<N>&) const;

	Vector<N> operator+(const double&) const;
	Vector<N> operator-(const double&) const;
	Vector<N> operator*(const double&) const;
	Vector<N> operator/(const double&) const;

	Vector<N>& operator+=(const Vector<N>&);
	Vector<N>& operator-=(const Vector<N>&);
	Vector<N>& operator*=(const Vector<N>&);
	Vector<N>& operator/=(const Vector<N>&);

	Vector<N>& operator+=(const double&);
	Vector<N>& operator-=(const double&);
	Vector<N>& operator*=(const double&);
	Vector<N>& operator/=(const double&);

	std::string to_string() const;
	double* data() { return m_data.data(); }

	double dot(const Vector<N>&) const;
	Vector<N> cross(const Vector<N>&) const;
	double length() const;

	void normalize();
	Vector<N> normalized() const;

   private:
	std::array<double, N> m_data;
};

template <size_t N>
Vector<N>::Vector() {
	for(int i = 0; i < N; ++i) {
		m_data[i] = 0;
	}
}

template <size_t N>
Vector<N>::Vector(const Vector<N>& other) {
	for(int i = 0; i < N; ++i) {
		m_data[i] = other.m_data[i];
	}
}

template <size_t N>
Vector<N>::Vector(const Vector<N - 1>& other, double value) {
	for(int i = 0; i < N - 1; ++i) {
		m_data[i] = other[i];
	}
	m_data[N - 1] = value;
}

template <size_t N>
Vector<N>::Vector(const std::array<double, N>& data) {
	for(int i = 0; i < N; ++i) {
		m_data[i] = data[i];
	}
}

template <size_t N>
Vector<N>::~Vector() {}

template <size_t N>
double& Vector<N>::operator[](int index) {
	return m_data[index];
}

template <size_t N>
const double& Vector<N>::operator[](int index) const {
	return m_data[index];
}

template <size_t N>
Vector<N> Vector<N>::operator+(const Vector<N>& other) const {
	Vector<N> result;
	for(int i = 0; i < N; ++i) {
		result[i] = m_data[i] + other.m_data[i];
	}
	return result;
}

template <size_t N>
Vector<N> Vector<N>::operator-(const Vector<N>& other) const {
	Vector<N> result;
	for(int i = 0; i < N; ++i) {
		result[i] = m_data[i] - other.m_data[i];
	}
	return result;
}

template <size_t N>
Vector<N> Vector<N>::operator*(const Vector<N>& other) const {
	Vector<N> result;
	for(int i = 0; i < N; ++i) {
		result[i] = m_data[i] * other.m_data[i];
	}
	return result;
}

template <size_t N>
Vector<N> Vector<N>::operator/(const Vector<N>& other) const {
	Vector<N> result;
	for(int i = 0; i < N; ++i) {
		result[i] = m_data[i] / other.m_data[i];
	}
	return result;
}

template <size_t N>
Vector<N> Vector<N>::operator+(const double& value) const {
	Vector<N> result;
	for(int i = 0; i < N; ++i) {
		result[i] = m_data[i] + value;
	}
	return result;
}

template <size_t N>
Vector<N> Vector<N>::operator-(const double& value) const {
	Vector<N> result;
	for(int i = 0; i < N; ++i) {
		result[i] = m_data[i] - value;
	}
	return result;
}

template <size_t N>
Vector<N> Vector<N>::operator*(const double& value) const {
	Vector<N> result;
	for(int i = 0; i < N; ++i) {
		result[i] = m_data[i] * value;
	}
	return result;
}

template <size_t N>
Vector<N> Vector<N>::operator/(const double& value) const {
	Vector<N> result;
	for(int i = 0; i < N; ++i) {
		result[i] = m_data[i] / value;
	}
	return result;
}

template <size_t N>
Vector<N>& Vector<N>::operator+=(const Vector<N>& other) {
	for(int i = 0; i < N; ++i) {
		m_data[i] += other.m_data[i];
	}
	return *this;
}

template <size_t N>
Vector<N>& Vector<N>::operator-=(const Vector<N>& other) {
	for(int i = 0; i < N; ++i) {
		m_data[i] -= other.m_data[i];
	}
	return *this;
}

template <size_t N>
Vector<N>& Vector<N>::operator*=(const Vector<N>& other) {
	for(int i = 0; i < N; ++i) {
		m_data[i] *= other.m_data[i];
	}
	return *this;
}

template <size_t N>
Vector<N>& Vector<N>::operator/=(const Vector<N>& other) {
	for(int i = 0; i < N; ++i) {
		m_data[i] /= other.m_data[i];
	}
	return *this;
}

template <size_t N>
Vector<N>& Vector<N>::operator+=(const double& value) {
	for(int i = 0; i < N; ++i) {
		m_data[i] += value;
	}
	return *this;
}

template <size_t N>
Vector<N>& Vector<N>::operator-=(const double& value) {
	for(int i = 0; i < N; ++i) {
		m_data[i] -= value;
	}
	return *this;
}

template <size_t N>
Vector<N>& Vector<N>::operator*=(const double& value) {
	for(int i = 0; i < N; ++i) {
		m_data[i] *= value;
	}
	return *this;
}

template <size_t N>
Vector<N>& Vector<N>::operator/=(const double& value) {
	for(int i = 0; i < N; ++i) {
		m_data[i] /= value;
	}
	return *this;
}

template <size_t N>
std::string Vector<N>::to_string() const {
	std::string result = "[";
	for(int i = 0; i < N; ++i) {
		result += std::to_string(m_data[i]);
		if(i != N - 1) {
			result += ", ";
		}
	}
	result += "]";
	return result;
}

template <size_t N>
double Vector<N>::dot(const Vector<N>& other) const {
	double result = 0;
	for(int i = 0; i < N; ++i) {
		result += m_data[i] * other.m_data[i];
	}
	return result;
}

template <size_t N>
Vector<N> Vector<N>::cross(const Vector<N>& other) const {
	Vector<N> result;
	result[0] = m_data[1] * other.m_data[2] - m_data[2] * other.m_data[1];
	result[1] = m_data[2] * other.m_data[0] - m_data[0] * other.m_data[2];
	result[2] = m_data[0] * other.m_data[1] - m_data[1] * other.m_data[0];
	return result;
}

template <size_t N>
double Vector<N>::length() const {
	double result = 0;
	for(int i = 0; i < N; ++i) {
		result += m_data[i] * m_data[i];
	}
	return sqrt(result);
}

template <size_t N>
void Vector<N>::normalize() {
	double len = length();
	for(int i = 0; i < N; ++i) {
		m_data[i] /= len;
	}
}

template <size_t N>
Vector<N> Vector<N>::normalized() const {
	Vector<N> result;
	double len = length();
	for(int i = 0; i < N; ++i) {
		result[i] = m_data[i] / len;
	}
	return result;
}

template <size_t N>
std::ostream& operator<<(std::ostream& os, const Vector<N>& v) {
	os << v.to_string();
	return os;
}

}  // namespace GLRT
