
#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>   // sin and cos
#include <stdlib.h> // srand, rand
#include <time.h>   // time
#include <vector>

// ============================================================================
// CONSTANTS
// ============================================================================

const unsigned int ROW = 15; //= 15;
const unsigned int COL = 18; //= 20;

const unsigned int BOX_R = 20; // 16;

const unsigned int WIDTH = 600;
const unsigned int HEIGHT = 600;

// ============================================================================
// Hexa
// ============================================================================

/*
class Hexa {
public:

    float hexagon_r, hexagon_w2, hexagon_h2, hexagon_w, hexagon_h;

    Hexa(float hr){
        hexagon_r = hr;
        hexagon_w2  = hexagon_r;
        hexagon_h2  = sqrt(hexagon_w2*hexagon_w2*3.f/4.f);
        hexagon_w = 2 * hexagon_w2;
        hexagon_h = 2 * hexagon_h2;
    }

    enum HEXAGON_DIRECTION {
        HEXAGON_RIGHT,
        HEXAGON_RIGHT_UP,
        HEXAGON_LEFT_UP,
        HEXAGON_LEFT,
        HEXAGON_LEFT_DOWN,
        HEXAGON_RIGHT_DOWN
    };

    const float hexagon_trigo_offset[6][2] = {
        {+1   ,   0}, //      - right
        {+0.5 ,  +1}, // up   - right
        {-0.5 ,  +1}, // up   - left
        {-1   ,   0}, //      - left
        {-0.5 ,  -1}, // down - left
        {+0.5 ,  -1}  // down - right
    };

    const int double_quads_map[8] = {
        HEXAGON_RIGHT, HEXAGON_RIGHT_UP, HEXAGON_LEFT_UP, HEXAGON_LEFT,    //
top    quad HEXAGON_LEFT, HEXAGON_LEFT_DOWN, HEXAGON_RIGHT_DOWN, HEXAGON_RIGHT
// bottom quad
    };

private:


};
*/

// ============================================================================
// HexaMap
// ============================================================================

class HexaMap : public sf::Drawable, public sf::Transformable {
public:
  const sf::Color COLOR_MAP[3] = {sf::Color(187, 153, 221),
                                  sf::Color(221, 153, 187),
                                  sf::Color(153, 187, 221)};

  const sf::Color COLOR_MAP_SLAY[6] = {
      sf::Color(0, 255, 0),   // light green
      sf::Color(192, 192, 0), //
      sf::Color(0, 128, 0),   // green
      sf::Color(255, 255, 0), // yellow
      sf::Color(0, 192, 0),   //
      sf::Color(128, 128, 0)  // brown
  };

  unsigned int n_row, n_col;
  int *hexa_centers_x;
  int *hexa_centers_y;
  bool initialized = false;

  unsigned int hexagon_r, hexagon_w2, hexagon_h2, hexagon_w, hexagon_h;

  unsigned int width, height;

  HexaMap(unsigned int nr, unsigned int nc, float hr) {
    n_row = nr;
    n_col = nc;
    hexagon_r = hr;
  }

  void initialize() { initialize(n_row, n_col, hexagon_r); }

  void initialize(unsigned int nr, unsigned int nc, float hr) {
    n_row = nr;
    n_col = nc;
    hexagon_r = hr;
    // std::cout << "1 *********************" << std::endl;

    m_vertices.setPrimitiveType(sf::Quads);
    m_vertices.resize(8 * n_row * n_col); // 8 : double quad 2*4

    hexagon_w2 = hexagon_r;
    hexagon_w = 2 * hexagon_w2;

    hexagon_h2 = sqrt(hexagon_r * hexagon_r * 3.f / 4.f);
    hexagon_h = 2 * hexagon_h2;

    hexa_centers_x = new int[n_col];
    for (unsigned int c = 0; c < n_col; c++)
      hexa_centers_x[c] = c * (hexagon_w * 3.0 / 4.0) + hexagon_w2;

    hexa_centers_y = new int[n_row];
    for (unsigned int r = 0; r < n_row; r++)
      hexa_centers_y[r] = (hexagon_h * r) + hexagon_h2;

    std::cout << std::endl;

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    width = (hexagon_w / 4.f) * (nc > 0) + (nc * hexagon_w * 3.f / 4.f);
    height = (hexagon_h / 2.f) * (nc > 0) + (nr * hexagon_h);

    std::cout << "debug* width=" << width << std::endl;
    std::cout << "debug* height=" << height << std::endl;

    // sf::FloatRect tmp = m_vertices.getBounds();
    // std::cout << "debug*** width=" << tmp.width << std::endl;
    // std::cout << "debug*** height=" << tmp.height<< std::endl;

    // std::cout << "2 *********************" << std::endl;

    this->initialized = true;
  }

  void fill_vertex(int r, int c, sf::Color col) {
    int offset = ((c % 2) == 1) ? hexagon_h2 : 0;
    int xc = hexa_centers_x[c];
    int yc = hexa_centers_y[r] + offset;
    int idx = 8 * (r * n_col + c);

    // first quad (up)
    m_vertices[idx + 0].position = sf::Vector2f(xc + hexagon_w2, yc);
    m_vertices[idx + 1].position =
        sf::Vector2f(xc + 0.5 * hexagon_w2, yc + hexagon_h2);
    m_vertices[idx + 2].position =
        sf::Vector2f(xc - 0.5 * hexagon_w2, yc + hexagon_h2);
    m_vertices[idx + 3].position = sf::Vector2f(xc - hexagon_w2, yc);
    // second quad (top)
    m_vertices[idx + 4].position = m_vertices[idx + 3].position;
    m_vertices[idx + 5].position =
        sf::Vector2f(xc - 0.5 * hexagon_w2, yc - hexagon_h2);
    m_vertices[idx + 6].position =
        sf::Vector2f(xc + 0.5 * hexagon_w2, yc - hexagon_h2);
    m_vertices[idx + 7].position = m_vertices[idx + 0].position;

    for (int i = 0; i < 8; i++) {
      m_vertices[idx + i].color = col;
    }
  }

  void change_color(int r, int c, sf::Color col) {
    int idx = 8 * (r * n_col + c);
    for (int i = 0; i < 8; i++) {
      m_vertices[idx + i].color = col;
    }
  }

  void update() {
    if (!initialized)
      initialize();

    sf::Color color;
    int ci = 0;

    for (unsigned int c = 0; c < n_col; c++) {
      for (unsigned int r = 0; r < n_row; r++) {

        // color = COLOR_MAP[(ci++)%3];
        /*
        color = sf::Color(
            rand() % 256 + 1,
            rand() % 256 + 1,
            rand() % 256 + 1
        );
        */
        color = COLOR_MAP_SLAY[(ci++) % 6];
        // color = sf::Color::White;
        // color = (((c+r*n_col)%2)==0) ?  sf::Color::Blue : sf::Color::Red;
        fill_vertex(r, c, color);
      }
    }
  }

  sf::Vector2u PointToCoord(double x, double y) {
    // swap x and y for column-odd ; hexagon_h2=hexagon_w2; hexagon_w=>hexagon_w
    y = (y - hexagon_h2) / hexagon_h;
    double t1 = x / hexagon_r;
    double t2 = floor(y + t1);
    int r = floor((floor(t1 - y) + t2) / 3.f);
    int q = floor((floor(2 * y + 1) + t2) / 3.f) - r;

    // cube to offset (q-odd)
    int cube_x = r, cube_z = q; // cube_y = -r - q
    int col = cube_x;
    int row = cube_z + (cube_x - (cube_x & 1)) / 2;
    return sf::Vector2u(row, col);
  }

private:
  virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform(); // apply the transform
    states.texture = &m_tileset;        // apply the tileset texture
    target.draw(m_vertices, states);    // draw the vertex array
  }

  sf::VertexArray m_vertices;
  sf::Texture m_tileset;
};

// ============================================================================

// ============================================================================

void run() {

  std::cout << "HELLO WORLD" << std::endl;
  std::cout << std::endl;

  sf::ContextSettings settings;
  settings.antialiasingLevel = 8;

  sf::RenderWindow window({WIDTH, HEIGHT}, "Hexagons", sf::Style::Default,
                          settings);
  // window.setVerticalSyncEnabled(true);

  // view
  // sf::View view(sf::FloatRect(200.f, 200.f, 300.f, 200.f));
  // window.setView(view);
  // view.setRotation(20.f);

  // float fps;
  int frame = 0;
  sf::Clock clock;
  sf::Time time_curr; //, time_prev = clock.getElapsedTime();

  sf::Font font;
  if (!font.loadFromFile("../res/fonts/Square.ttf"))
    return;

  sf::Text text;
  text.setFont(font);
  text.setString("60");
  // sf::FloatRect blabla = text.getLocalBounds();
  text.setPosition(WIDTH - text.getLocalBounds().width - 10, 0);
  text.setCharacterSize(30); // in pixel !
  text.setFillColor(sf::Color::Yellow);
  // text.setStyle(sf::Text::Bold | sf::Text::Underlined);

  HexaMap hm = HexaMap(ROW, COL, BOX_R);
  hm.initialize();
  hm.update();
  // window.setSize(sf::Vector2u(hm.width, hm.height));

  int r = ROW, c = COL, hexa_r = BOX_R;

  /* -------------------------------------------------- */

  while (window.isOpen()) {

    // event loop
    sf::Event event;
    while (window.pollEvent(event)) {

      switch (event.type) {

      case sf::Event::Closed:
        window.close();
        break;

      case sf::Event::KeyPressed:
        // std::cout << "[KEY] ";

        if (event.key.code == sf::Keyboard::Right) {
          std::cout << "Right" << std::endl;
          hm.initialize(r, ++c, hexa_r);
          hm.update();
        } else if (event.key.code == sf::Keyboard::Left) {
          std::cout << "Left" << std::endl;
          hm.initialize(r, --c, hexa_r);
          hm.update();
        } else if (event.key.code == sf::Keyboard::Up) {
          std::cout << "Up" << std::endl;
          hm.initialize(--r, c, hexa_r);
          hm.update();
        } else if (event.key.code == sf::Keyboard::Down) {
          std::cout << "Down" << std::endl;
          hm.initialize(++r, c, hexa_r);
          hm.update();
        } else if (event.key.code == sf::Keyboard::Enter)
          std::cout << "OK" << std::endl;

        else if (event.key.code == sf::Keyboard::Add) {
          std::cout << "+" << std::endl;
          hm.initialize(r, c, ++hexa_r);
          hm.update();
        } else if (event.key.code == sf::Keyboard::Subtract) {
          std::cout << "-" << std::endl;
          hm.initialize(r, c, --hexa_r);
          hm.update();
        }

        else
          // std::cout << std::endl;
          break;

      case sf::Event::MouseButtonPressed:
        // sf::Event::MouseButtonPressed and sf::Event::MouseButtonReleased
        //  left, right, middle (wheel), extra #1 and extra #2 (side buttons)
        // std::cout << "[MOUSE] ";
        if (event.mouseButton.button == sf::Mouse::Right) {
          std::cout << "RIGHT (" << event.mouseButton.x << ", "
                    << event.mouseButton.y << ")" << std::endl;
        } else if (event.mouseButton.button == sf::Mouse::Left) {
          std::cout << "LEFT (" << event.mouseButton.x << ", "
                    << event.mouseButton.y << ")" << std::endl;
          sf::Vector2u coords =
              hm.PointToCoord(event.mouseButton.x, event.mouseButton.y);
          std::cout << "=>" << coords.x << "," << coords.y << std::endl;
          unsigned int r_click = coords.x, c_click = coords.y;
          if ((r_click >= 0 && r_click < hm.n_row) &&
              (c_click >= 0 && c_click < hm.n_col)) {
            std::cout << "!" << std::endl;
            hm.change_color(r_click, c_click, sf::Color(0, 0, 0));
          }
        } else
          // std::cout << std::endl;
          break;

        //
        // case sf::Event::MouseWheelEvent:
        //    break;
        //*/

      default:
        break;
      }
    }

    // hm.update();
    //
    // hm.change_color(
    //   rand() % r,
    //    rand() % c,

    //    sf::Color(
    //        rand() % 255,
    //        rand() % 255,
    //        rand() % 255
    //    )

    //   (rand() % 2) ? sf::Color::Black : sf::Color::White
    //);

    window.clear(sf::Color::Black);
    // DRAW : start -------------------------------------------------------

    window.draw(hm);
    window.draw(text);
    // hm.draw_grid(window);

    // DRAW : end   -------------------------------------------------------
    window.display();

    // performance measurement
    // time_curr = clock.getElapsedTime();
    // fps = 1.0f / (time_curr.asSeconds() - time_prev.asSeconds()); // the
    // asSeconds returns a float time_prev = time_curr;

    frame++;
    if (clock.getElapsedTime().asSeconds() > 1.f) {
      clock.restart();

      // std::cout << "[FPS] " << floor(frame) << std::endl; // flooring it will
      // make the frame rate a rounded number

      text.setString(std::to_string(frame));
      text.setPosition(WIDTH - text.getLocalBounds().width - 10, 0);
      frame = 0;
    }
  }

  std::cout << std::endl;
}
