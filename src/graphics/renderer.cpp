#include <renderer.hpp>

static const uint8_t king_white_png[] = {
#include <king_white.png.h>
};
static const uint8_t queen_white_png[] = {
#include <queen_white.png.h>
};
static const uint8_t bishop_white_png[] = {
#include <bishop_white.png.h>
};
static const uint8_t knight_white_png[] = {
#include <knight_white.png.h>
};
static const uint8_t rook_white_png[] = {
#include <rook_white.png.h>
};
static const uint8_t pawn_white_png[] = {
#include <pawn_white.png.h>
};
static const uint8_t king_black_png[] = {
#include <king_black.png.h>
};
static const uint8_t queen_black_png[] = {
#include <queen_black.png.h>
};
static const uint8_t bishop_black_png[] = {
#include <bishop_black.png.h>
};
static const uint8_t knight_black_png[] = {
#include <knight_black.png.h>
};
static const uint8_t rook_black_png[] = {
#include <rook_black.png.h>
};
static const uint8_t pawn_black_png[] = {
#include <pawn_black.png.h>
};

using namespace cxxess::gameplay;

namespace cxxess::graphics {

void validate(bool result) {
   if (!result)
      abort();
}

float calculateScaleFactor(const sf::Texture& texture) {
   auto textureSize = texture.getSize();
   auto aspectRatio = textureSize.x / textureSize.y;
   return aspectRatio >= 1 ? 100.0f / textureSize.x : 100.0f / textureSize.y;
}

sf::Vector2<float> calculatePixelSize(const sf::Texture& texture) {
   auto scaleFactor = calculateScaleFactor(texture);
   auto textureSize = texture.getSize();
   return sf::Vector2<float>(textureSize.x * scaleFactor, textureSize.y * scaleFactor);
}

sf::Vector2<float> centeredBoardPosition(const sf::Vector2<float>& slotTopLeft, const sf::Texture& texture) {
   auto boardSlotSize = sf::Vector2<float>(static_cast<float>(BOARD_SLOT_SIZE), static_cast<float>(BOARD_SLOT_SIZE));
   auto pixelSize = calculatePixelSize(texture);
   return slotTopLeft + (boardSlotSize - pixelSize) * 0.5f;
}

Renderer::Renderer() {
   /* Treat Type::NO_TYPE as the number of types (since it comes after all types).
    * Textures for Black are stored after textures for White. */
   m_pieceTextures.resize(Type::NO_TYPE * 2);
   validate(m_pieceTextures[Type::KING].loadFromMemory(king_white_png, sizeof(king_white_png)));
   validate(m_pieceTextures[Type::QUEEN].loadFromMemory(queen_white_png, sizeof(queen_white_png)));
   validate(m_pieceTextures[Type::ROOK].loadFromMemory(rook_white_png, sizeof(rook_white_png)));
   validate(m_pieceTextures[Type::BISHOP].loadFromMemory(bishop_white_png, sizeof(bishop_white_png)));
   validate(m_pieceTextures[Type::KNIGHT].loadFromMemory(knight_white_png, sizeof(knight_white_png)));
   validate(m_pieceTextures[Type::PAWN].loadFromMemory(pawn_white_png, sizeof(pawn_white_png)));
   validate(m_pieceTextures[Type::NO_TYPE + Type::KING].loadFromMemory(king_black_png, sizeof(king_black_png)));
   validate(m_pieceTextures[Type::NO_TYPE + Type::QUEEN].loadFromMemory(queen_black_png, sizeof(queen_black_png)));
   validate(m_pieceTextures[Type::NO_TYPE + Type::ROOK].loadFromMemory(rook_black_png, sizeof(rook_black_png)));
   validate(m_pieceTextures[Type::NO_TYPE + Type::BISHOP].loadFromMemory(bishop_black_png, sizeof(bishop_black_png)));
   validate(m_pieceTextures[Type::NO_TYPE + Type::KNIGHT].loadFromMemory(knight_black_png, sizeof(knight_black_png)));
   validate(m_pieceTextures[Type::NO_TYPE + Type::PAWN].loadFromMemory(pawn_black_png, sizeof(pawn_black_png)));
}

AnimationHandle Renderer::newAnimation(SpriteHandle sprite) {
   return m_animations.addElement(Animation{
      .targetTime = 0.0f,
      .elapsedTime = 0.0f,
      .sprite = sprite,
      .startPos = {},
      .targetPos = {},
   });
}

void Renderer::move(AnimationHandle anim, float time, const BoardPos& currentPos, const BoardPos& targetPos) {
   Animation& animToMove = m_animations[anim];

   auto& texture = m_context.m_drawables[animToMove.sprite].getTexture();

   auto currentSlotTopLeft = sf::Vector2<float>(currentPos.x, currentPos.y) * static_cast<float>(BOARD_SLOT_SIZE);
   auto targetSlotTopLeft = sf::Vector2<float>(targetPos.x, targetPos.y) * static_cast<float>(BOARD_SLOT_SIZE);

   animToMove.targetTime = time;
   animToMove.elapsedTime = 0.0f;
   animToMove.startPos = centeredBoardPosition(currentSlotTopLeft, texture);
   animToMove.targetPos = centeredBoardPosition(targetSlotTopLeft, texture);
}

SpriteHandle Renderer::generatePieceSprite(const Piece& piece, const BoardPos& position) {
   assert(piece.get_type() != Type::NO_TYPE);

   unsigned int sprite_index = piece.get_type();
   if (piece.get_color() == BLACK)
      sprite_index += Type::NO_TYPE;

   auto& texture = m_pieceTextures[sprite_index];
   auto sprite = sf::Sprite(texture);

   /* Center the sprite in the given board slot. Simply setting the sprite's position to the top left
    * corner will result in the sprite being off-center */
   auto slotTopLeft = sf::Vector2<float>(position.x, position.y) * static_cast<float>(BOARD_SLOT_SIZE);

   sprite.setPosition(centeredBoardPosition(slotTopLeft, texture));

   auto scaleFactor = calculateScaleFactor(texture);
   sprite.setScale({scaleFactor, scaleFactor});
   return m_context.m_drawables.addElement(std::move(sprite));
}
void Renderer::tick() {
   auto elapsedTime = m_animationClock.restart().asSeconds();
   for (auto& animation : m_animations) {
      if (animation.elapsedTime >= animation.targetTime)
         continue;
      animation.elapsedTime = std::min(animation.elapsedTime + elapsedTime, animation.targetTime);

      /* Just dumb linear interpolation for now. Switch to quadratic Bézier interpolation? */
      auto new_pos = animation.startPos +
                     (animation.targetPos - animation.startPos) * (animation.elapsedTime / animation.targetTime);
      m_context.m_drawables[animation.sprite].setPosition(new_pos);
   }

   m_context.update();
}
} // namespace cxxess::graphics
