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
          case 0: { type = ROOK; break; }
          case 1: { type = KNIGHT; break; }
          case 2: { type = BISHOP; break; }
          case 3: { type = QUEEN; break; }
          case 4: { type = KING; break; }
          case 5: { type = BISHOP; break; }
          case 6: { type = KNIGHT; break; }
          case 7: { type = ROOK; break; }
        }
      } else if (y == 1 || y == 6) {
        type = PAWN;
      }

      this->board[y][x] = Piece(color, type);
    }
  }
}

std::string Board::to_string() {
  constexpr char NEW_LINE = '\n';
  constexpr char EMPTY_PIECE[5] = "    ";
  std::string result;

  for (std::uint8_t y = 0; y < BOARD_HEIGHT; y++) {
    for (std::uint8_t x = 0; x < BOARD_WIDTH; x++) {
      Piece piece = this->board[y][x];

      if (!piece.is_playable()) {
        result += EMPTY_PIECE;
        continue;
      }

      result += (piece.get_color() == BLACK) ? " b" : " w";
      switch (piece.get_type()) {
        case KING: { result += "K "; break; }
        case QUEEN: { result += "Q "; break; }
        case ROOK: { result += "R "; break; }
        case BISHOP: { result += "B "; break; }
        case KNIGHT: { result += "k "; break; }
        case PAWN: { result += "P "; break; }        
      }
    }

    result += NEW_LINE;
  }

  return result;
}