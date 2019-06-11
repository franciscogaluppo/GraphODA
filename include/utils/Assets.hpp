#ifndef ASSETS_H
#define ASSETS_H

#include <stdlib.h>
#include <string>

using namespace std;

// TODO: definir essas constantes pelo CMake
#define FONT_FILE "assets/CONSOLAB.TTF"
#define THEME_FILE "assets/TransparentGrey.txt"

const string get_theme_path();
const string get_font_path();

#endif // GRAPHODA_ASSETS_HPP
