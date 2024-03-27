#pragma once

#include <cstdint>


namespace cxxess::gameplay::utils {

  class Vector {
    
    public:
      std::int32_t m_x, m_y;

    public:
      Vector();
      Vector(std::int32_t x, std::int32_t y);

    public:
      void operator+(Vector& vector);
      Vector operator+=(Vector& vector);
      void operator-(Vector& vector);
      Vector operator-=(Vector& vector);

    public:
      Vector abs();
      std::int32_t get_length();

    public:
      std::int32_t get_x() const;
      std::int32_t get_y() const;

  };

}