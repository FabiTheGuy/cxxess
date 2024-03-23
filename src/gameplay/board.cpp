#include "../../include/gameplay/board.hpp"
#include "../../include/gameplay/piece.hpp"


using namespace cxxess::gameplay;

Board::Board() {
  for (std::uint8_t y = 0; y < BOARD_HEIGHT; y++) {
    for (std::uint8_t x = 0; x < BOARD_WIDTH; x++) {
      Color color = (y == 0 || y == 1) ? BLACK : (y == 6 || y == 7) ? WHITE : NO_COLOR;
      Type type = NO_TYPE;

      if (y == 0 || y == 7) {
        switch (x) {
          case 1: { type = ROOK; break; }
          case 2: { type = KNIGHT; break; }
          case 3: { type = BISHOP; break; }
          case 4: { type = QUEEN; break; }
          case 5: { type = KING; break; }
          case 6: { type = BISHOP; break; }
          case 7: { type = KNIGHT; break; }
          case 8: { type = ROOK; break; }
        }
      } else if (y == 1 || y == 6) {
        type = PAWN;
      }

      this->board[y][x] = Piece(color, type);
    }
  }
}