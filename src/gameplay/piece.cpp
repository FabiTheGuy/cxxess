#include "../../include/gameplay/piece.hpp"


using namespace cxxess::gameplay;

Piece::Piece() : color(NO_COLOR), type(NO_TYPE) {}

Piece::Piece(Color color, Type type) : color(color), type(type) {}

Color Piece::get_color() const {
  return this->color;
}

Type Piece::get_type() const {
  return this->type;
}

bool Piece::is_playable() {
  return !(this->color == NO_COLOR && this->type == NO_TYPE);
}