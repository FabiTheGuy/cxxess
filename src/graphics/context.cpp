#include <context.hpp>

namespace cxxess::graphics {

Context::Context() : m_window(sf::RenderWindow(sf::VideoMode({BOARD_SLOT_SIZE * gameplay::BOARD_WIDTH, BOARD_SLOT_SIZE * gameplay::BOARD_HEIGHT}), "Chess")) {
   sf::Color backdropColors[2] = {
      sf::Color(255, 204, 153),
      sf::Color(204, 102, 0),
   };

   for (unsigned i = 0; i < 8; ++i) {
      unsigned checkerboard_offset = i % 2;
      for (unsigned j = 0; j < 8; ++j) {
         m_background[i][j] = sf::RectangleShape({100, 100});
         m_background[i][j].setPosition({j * 100.0f, i * 100.0f});
         m_background[i][j].setFillColor(backdropColors[(j + checkerboard_offset) % 2]);
      }
   }
}
void Context::update() {
   assert(!m_shouldClose);

   sf::Event event;
   while (m_window.pollEvent(event)) {
      // "close requested" event: we close the window
      if (event.type == sf::Event::Closed) {
         m_window.close();
         m_shouldClose = true;
      }
   }
   m_window.clear(sf::Color::Black);

   for (const auto& row : m_background)
      for (const auto& shape : row)
         m_window.draw(shape);

   for (const auto& drawable : m_drawables)
      m_window.draw(drawable);

   m_window.display();
}
bool Context::shouldClose() const {
   return m_shouldClose;
}
}