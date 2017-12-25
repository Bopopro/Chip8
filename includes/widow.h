#pragma once

#include <SFML/Graphics.h>

typedef struct	s_window {
  sfVideoMode		mode;
  sfRenderWindow	*window;
  sfTexture		*texture;
  sfSprite		*sprite;
  sfEvent		event;
}		t_window;

t_window	*c8_init_window();
