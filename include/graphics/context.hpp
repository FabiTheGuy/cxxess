#pragma once

#include <SFML/Graphics.hpp>
#include <Slotmap.hpp>
#include <board.hpp>

namespace cxxess::graphics {
constexpr unsigned int BOARD_SLOT_SIZE = 100;

using SpriteHandle = SlotmapHandle;

class Context {
 public:
   Context();

   void update();

   bool shouldClose() const;

   Slotmap<sf::Sprite> m_drawables;

 private:
   bool m_shouldClose;

   sf::RenderWindow m_window;
   sf::RectangleShape m_background[gameplay::BOARD_WIDTH][gameplay::BOARD_HEIGHT];
};

} // namespace cxxess::graphics