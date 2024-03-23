#pragma once


namespace cxxess::gameplay {

  enum Color {
    BLACK,
    WHITE,
    NO_COLOR
  };

  enum Type {
    KING,
    QUEEN,
    ROOK,
    BISHOP,
    KNIGHT,
    PAWN,
    NO_TYPE
  };

  class Piece {

    private:
      Color color;
      Type type;

    public:
      Piece(); /* Empty Piece (NO_COLOR, NO_TYPE) */
      Piece(Color color, Type type);

    public:
      Color get_color() const;
      Type get_type() const;
      bool is_playable();

  };

};