#include "../../src/client/render.h"
#include <SFML/Graphics.hpp>
#include <boost/test/unit_test.hpp>

using namespace render;

BOOST_AUTO_TEST_CASE(TestStaticAssert) { BOOST_CHECK(1); }

BOOST_AUTO_TEST_CASE(TestSFML) {
  {
    ::sf::Texture texture;
    BOOST_CHECK(texture.getSize() == ::sf::Vector2<unsigned int>{});
    BOOST_CHECK(1);
  }
}

BOOST_AUTO_TEST_CASE(TestRender) {
  {
    state::State state;
    sf::RenderWindow window(sf::VideoMode(state.getBoard().getNCol() * 32 + 256,
                                          state.getBoard().getNRow() * 32 + 32,
                                          32),
                            "SLAY - RENDER");
    StateLayer sl(state, window);

    BOOST_CHECK_EQUAL(sl.getTileHeight(), 84);
  }
}

/* vim: set sw=2 sts=2 et : */
