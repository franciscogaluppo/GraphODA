#ifndef BUTTONSH
#define BUTTONSH

#include "GraphCanvas.hpp"

#include <SFML/Graphics.hpp>
#include <TGUI/TGUI.hpp>

#include <vector>

using namespace std;

namespace buttons {
void init(vector<tgui::Button::Ptr>&, GraphCanvas&);
void update(tgui::Gui&, vector<tgui::Button::Ptr>&, GraphCanvas&);
} // namespace buttons

#endif
