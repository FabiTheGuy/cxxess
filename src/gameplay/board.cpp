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
  this->empty_tile = Piece();
}

bool Board::move(std::uint8_t from_x, std::uint8_t from_y, std::uint8_t to_x, std::uint8_t to_y) {
  if (to_x >= BOARD_WIDTH || to_y >= BOARD_HEIGHT || (to_x == from_x && to_y == from_y)) {
    return false;
  }
  switch (this->board[from_y][from_x].get_type()) {
    case KING: {
      /* if the king and the rook hasn't moved
          the king can castle
         the king can move to any field around him
      */
      for (uint8_t y = from_y - 1; y <= from_y + 1; y++) {
        for (uint8_t x = from_x - 1; x <= from_x + 1; x++) {
          if (to_y == y && to_x == x) {
            if(this->board[to_y][to_x].get_color() != board[from_y][from_x].get_color()) {
              this->board[to_y][to_x] = this->board[from_y][from_x];
              this->board[from_y][from_x] = this->empty_tile;
              return true;
            }
          }
        }
      }
      break;
    }
    case QUEEN: {
      break;
    }
    case ROOK: {
      if(to_x != from_x && to_y != from_y) {
        return false;
      }
      int8_t dir = (from_x < to_x ? 1 : -1) | (from_y < to_y ? 1 : -1);
      
      if (to_x == from_x) {
        for (uint8_t y = from_y + dir; y < BOARD_HEIGHT; y = (uint8_t)((int8_t) y + dir)) {
          if (this->board[y][from_x].get_type() != NO_TYPE) {
            if (y == to_y){
              if(this->board[y][from_x].get_color() != this->board[from_y][from_x].get_color()) {
                this->board[to_y][to_x] = this->board[from_y][from_x];
                this->board[from_y][from_x] = this->empty_tile;
                return true;
              }
            } else {
              return false;
            }
            break;
          }
        }
      } else {
        for (uint8_t x = from_x + dir; x < BOARD_WIDTH; x = (uint8_t)((int8_t) x + dir)) {
          if (this->board[from_y][x].get_type() != NO_TYPE) {
            if (x == to_x){
              if(this->board[from_y][x].get_color() != this->board[from_y][from_x].get_color()) {
                this->board[to_y][to_x] = this->board[from_y][from_x];
                this->board[from_y][from_x] = this->empty_tile;
                return true;
              }
            } else {
              return false;
            }
            break;
          }
        }
      }

      break;
    }
    case BISHOP: {
      if (to_x == from_x || to_y == from_y) {
        return false;
      }
      int8_t x_dir = from_x < to_x ? 1 : -1;
      int8_t y_dir = from_y < to_y ? 1 : -1;

      uint8_t x = from_x;
      uint8_t y = from_y;
      while (x < BOARD_WIDTH && y < BOARD_HEIGHT) {
        x = (uint8_t) ((int8_t)x + x_dir);
        y = (uint8_t) ((int8_t)y + y_dir);

        if (this->board[y][x].get_type() != NO_TYPE) {
          if (to_x == x && to_y == y) {
            if (this->board[to_y][to_x].get_color() != this->board[from_y][from_x].get_color()) {
              this->board[to_y][to_x] = this->board[from_y][from_x];
              this->board[from_y][from_x] = this->empty_tile;
              return true;
            }
            break;
          }
        }
      }

      break;
    }
    case KNIGHT: {
      uint8_t x_diff = abs((int8_t)to_x - (int8_t)from_x);
      uint8_t y_diff = abs((int8_t)to_y - (int8_t)from_y);
      if ((x_diff == 1 && y_diff == 2) || (x_diff == 2 && y_diff == 1)) {
        if(this->board[to_y][to_x].get_color() != this->board[from_y][from_x].get_color()) {
          this->board[to_y][to_x] = this->board[from_y][from_x];
          this->board[from_y][from_x] = this->empty_tile;
          return true;
        }
      }
      break;
    }
    case PAWN: {
      /* pawns can only move in one direction, so each color has
          a different movement direction
         only on first move they can move 2 steps
         if another piece is diagonally in front of them
          it can capture.
         when a pawn reaches the end it can be replaced with
          any other piece type
      */
      break;
    }
    default:
      return false;
  }
  return false;
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