#pragma once

#include <cstdint>
#include <string>
#include <cmath>

#include "piece.hpp"


namespace cxxess::gameplay {

  constexpr std::uint8_t BOARD_HEIGHT = 8;
  constexpr std::uint8_t BOARD_WIDTH = 8;

  class Board {

    private:
      Piece board[BOARD_HEIGHT][BOARD_WIDTH];
      Piece empty_tile;

    public:
      Board();
      bool move(std::uint8_t from_x, std::uint8_t from_y, std::uint8_t to_x, std::uint8_t to_y);

    public:
      std::string to_string();

    public:
      std::string to_string();

  };

};