#include <SFML/Graphics.hpp>
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(TestStaticAssert) { BOOST_CHECK(1); }

BOOST_AUTO_TEST_CASE(TestSFML) {
  {
    ::sf::Texture texture;
    BOOST_CHECK(texture.getSize() == ::sf::Vector2<unsigned int>{});
  }
}

BOOST_AUTO_TEST_CASE(TestClient) {
  { BOOST_CHECK(1); }
}
/* vim: set sw=2 sts=2 et : */
