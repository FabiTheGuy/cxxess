#include <renderer.hpp>

int main() {
   cxxess::graphics::Renderer ctx;

   cxxess::gameplay::Piece white_pawns[8];
   cxxess::graphics::SpriteHandle white_pawn_sprites[8];
   cxxess::gameplay::Piece black_pawns[8];
   cxxess::graphics::SpriteHandle black_pawn_sprites[8];
   for (unsigned i = 0; i < 8; ++i) {
      white_pawns[i] = cxxess::gameplay::Piece(cxxess::gameplay::WHITE, cxxess::gameplay::PAWN);
      white_pawn_sprites[i] = ctx.generatePieceSprite(white_pawns[i], { i, 6 });
      black_pawns[i] = cxxess::gameplay::Piece(cxxess::gameplay::BLACK, cxxess::gameplay::PAWN);
      black_pawn_sprites[i] = ctx.generatePieceSprite(black_pawns[i], { i, 1 });
   }
   cxxess::gameplay::Piece white_rooks[2];
   cxxess::graphics::SpriteHandle white_rook_sprites[2];
   cxxess::gameplay::Piece black_rooks[2];
   cxxess::graphics::SpriteHandle black_rook_sprites[2];
   for (unsigned i = 0; i < 2; ++i) {
      white_rooks[i] = cxxess::gameplay::Piece(cxxess::gameplay::WHITE, cxxess::gameplay::ROOK);
      white_rook_sprites[i] = ctx.generatePieceSprite(white_rooks[i], { i * 7, 7 });
      black_rooks[i] = cxxess::gameplay::Piece(cxxess::gameplay::BLACK, cxxess::gameplay::ROOK);
      black_rook_sprites[i] = ctx.generatePieceSprite(black_rooks[i], { i * 7, 0 });
   }
   cxxess::gameplay::Piece white_knights[2];
   cxxess::graphics::SpriteHandle white_knight_sprites[2];
   cxxess::gameplay::Piece black_knights[2];
   cxxess::graphics::SpriteHandle black_knight_sprites[2];
   for (unsigned i = 0; i < 2; ++i) {
      white_knights[i] = cxxess::gameplay::Piece(cxxess::gameplay::WHITE, cxxess::gameplay::KNIGHT);
      white_knight_sprites[i] = ctx.generatePieceSprite(white_knights[i], { i * 5 + 1, 7 });
      black_knights[i] = cxxess::gameplay::Piece(cxxess::gameplay::BLACK, cxxess::gameplay::KNIGHT);
      black_knight_sprites[i] = ctx.generatePieceSprite(black_knights[i], { i * 5 + 1, 0 });
   }
   cxxess::gameplay::Piece white_bishops[2];
   cxxess::graphics::SpriteHandle white_bishop_sprites[2];
   cxxess::gameplay::Piece black_bishops[2];
   cxxess::graphics::SpriteHandle black_bishop_sprites[2];
   for (unsigned i = 0; i < 2; ++i) {
      white_bishops[i] = cxxess::gameplay::Piece(cxxess::gameplay::WHITE, cxxess::gameplay::BISHOP);
      white_bishop_sprites[i] = ctx.generatePieceSprite(white_bishops[i], { i * 3 + 2, 7 });
      black_bishops[i] = cxxess::gameplay::Piece(cxxess::gameplay::BLACK, cxxess::gameplay::BISHOP);
      black_bishop_sprites[i] = ctx.generatePieceSprite(black_bishops[i], { i * 3 + 2, 0 });
   }

   cxxess::gameplay::Piece white_queen = cxxess::gameplay::Piece(cxxess::gameplay::WHITE, cxxess::gameplay::QUEEN);
   cxxess::graphics::SpriteHandle white_queen_sprite = ctx.generatePieceSprite(white_queen, { 3, 7 });
   cxxess::gameplay::Piece black_queen = cxxess::gameplay::Piece(cxxess::gameplay::BLACK, cxxess::gameplay::QUEEN);
   cxxess::graphics::SpriteHandle black_queen_sprite = ctx.generatePieceSprite(black_queen, { 3, 0 });
   cxxess::gameplay::Piece white_king = cxxess::gameplay::Piece(cxxess::gameplay::WHITE, cxxess::gameplay::KING);
   cxxess::graphics::SpriteHandle white_king_sprite = ctx.generatePieceSprite(white_king, { 4, 7 });
   cxxess::gameplay::Piece black_king = cxxess::gameplay::Piece(cxxess::gameplay::BLACK, cxxess::gameplay::KING);
   cxxess::graphics::SpriteHandle black_king_sprite = ctx.generatePieceSprite(black_king, { 4, 0 });

   auto anim = ctx.newAnimation(white_pawn_sprites[3]);
   ctx.tick();
   sleep(3);
   ctx.tick();
   ctx.move(anim, 0.1, {3, 6}, {3, 4});

   while (!ctx.shouldClose())
      ctx.tick();
}

