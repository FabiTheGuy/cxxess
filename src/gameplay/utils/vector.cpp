#include "../../../include/gameplay/utils/vector.hpp"

#include <cstdlib>
#include <cmath>


using namespace cxxess::gameplay::utils;


Vector::Vector() : m_x(0), m_y(0) {}

Vector::Vector(std::int32_t x, std::int32_t y) : m_x(x), m_y(y) {}

void Vector::operator+(Vector& vector) {
  this->m_x = vector.get_x();
  this->m_y = vector.get_y();
}

Vector Vector::operator+=(Vector& vector) {
  return Vector(m_x + vector.get_x(), m_y + vector.get_y());
}

void Vector::operator-(Vector& vector) {
  this->m_x -= vector.get_x();
  this->m_y -= vector.get_y();
}

Vector Vector::operator-=(Vector& vector) {
  return Vector(m_x - vector.get_x(), m_y - vector.get_y());
}

Vector Vector::abs() {
  return Vector(std::abs(this->m_x), std::abs(this->m_y));
}

std::int32_t Vector::get_length() {
  return (std::int32_t) std::sqrt(std::pow(this->m_x, 2) + std::pow(this->m_y, 2));
}

std::int32_t Vector::get_x() const {
  return this->m_x;
}

std::int32_t Vector::get_y() const {
  return this->m_y;
}