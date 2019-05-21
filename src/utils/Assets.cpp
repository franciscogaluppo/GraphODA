#include "Assets.hpp"

const string get_font_path() {
  const char *s = getenv("APPDIR");
  printf("Environ: %s", s);
  return s == nullptr ? FONT_FILE
                      : string(s) + "/usr/share/graphODA/" FONT_FILE;
}

const string get_theme_path() {
  const char *s = getenv("APPDIR");
  return s == nullptr ? THEME_FILE
                      : string(s) + "/usr/share/graphODA/" THEME_FILE;
}
