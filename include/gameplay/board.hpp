#pragma once

#include <cstdint>

#include "piece.hpp"


namespace cxxess::gameplay {

  constexpr std::uint8_t BOARD_HEIGHT = 8;
  constexpr std::uint8_t BOARD_WIDTH = 8;

  class Board {

    private:
      Piece board[BOARD_HEIGHT][BOARD_WIDTH];

    public:
      Board();

  };

};