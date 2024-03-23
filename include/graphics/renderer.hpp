#pragma once

#include <context.hpp>
#include <piece.hpp>

namespace cxxess::graphics {
using AnimationHandle = SlotmapHandle;

struct Animation {
   float targetTime;
   float elapsedTime;

   SpriteHandle sprite;
   sf::Vector2<float> startPos;
   sf::Vector2<float> targetPos;
};

class Renderer {
 public:
   Renderer();

   SpriteHandle generatePieceSprite(const cxxess::gameplay::Piece& piece, const gameplay::BoardPos& position);

   AnimationHandle newAnimation(SpriteHandle sprite);
   void move(AnimationHandle anim, float time, const gameplay::BoardPos& currentPos, const gameplay::BoardPos& targetPos);

   void tick();

   bool shouldClose() const { return m_context.shouldClose(); }

 private:
   Context m_context;

   Slotmap<Animation> m_animations;
   std::vector<sf::Texture> m_pieceTextures;

   sf::Clock m_animationClock;
};
}