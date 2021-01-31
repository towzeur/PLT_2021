#include <sstream> // for ostringstream

#include "Render.h"
#include "RenderConfig.h"
#include "RightPanel.h"
#include "TerritoryInfo.h"

using namespace render;

char get_sign_char(int x) {
  if (x > 0)
    return '+';
  else if (x < 0)
    return '-';
  return ' ';
}

TerritoryInfo::TerritoryInfo() {}

TerritoryInfo::TerritoryInfo(Render *r) : r(r) {}

void TerritoryInfo::init(int x0, int y0, int width) {
  this->x0 = x0;
  this->y0 = y0;
  this->width = width;

  std::string label0_str = "Savings\nIncome\nWages\nBalance";
  label0 = createLabel(label0_str);
  label0->setText(label0_str);
  label0->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Left);

  std::string label1_str = "8\n+2\n0\n10";
  label1 = createLabel(label1_str);
  label1->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Right);

  tgui::Panel::Ptr layout = r->getPanel()->getLayout();
  layout->add(label0);
  layout->add(label1);
}

tgui::Label::Ptr TerritoryInfo::createLabel(std::string &str) {
  tgui::Theme::Ptr theme = r->getTheme();
  std::shared_ptr<RenderConfig> conf = r->getConfig();

  tgui::Label::Ptr l = theme->load("Label");
  std::shared_ptr<tgui::LabelRenderer> lRenderer = l->getRenderer();
  // lRenderer->setBackgroundColor(sf::Color::Red);
  lRenderer->setPadding(0, 0);
  l->setText(str);
  l->setTextSize(14);
  height = l->getSize().y;
  l->setTextColor(sf::Color::White);
  l->setSize(width, height);
  l->setPosition(x0, y0);
  l->setVerticalAlignment(tgui::Label::VerticalAlignment::Top);
  l->setFont(conf->window_right_panel_font);
  return l;
}

void TerritoryInfo::update(int savings, int income, int wages, int balance) {
  std::ostringstream out;
  out << savings << std::endl
      << income << std::endl
      << wages << std::endl
      << balance;
  label1->setText(out.str());
}

void TerritoryInfo::hide() {
  label0->setTextColor(sf::Color::Transparent);
  label1->setTextColor(sf::Color::Transparent);
}

void TerritoryInfo::show() {
  label0->setTextColor(sf::Color::White);
  label1->setTextColor(sf::Color::White);
}

void TerritoryInfo::reset() {
  label1->setText("-\n-\n-\n-");
  label0->setTextColor(sf::Color(130, 130, 130));
  label1->setTextColor(sf::Color(130, 130, 130));
}
