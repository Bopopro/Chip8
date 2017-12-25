#pragma once

#include <SFML/Graphics.h>
#include <stdint.h>
#include <stdbool.h>

#define WIDTH (64)
#define HEIGHT (32)
# define BLACK_PIXEL		(0)
# define WHITE_PIXEL		(255)

typedef struct	s_framebuffer {
  sfUint8	*pixels;
  uint8_t	width;
  uint8_t	height;
}		t_fb;

typedef struct	s_window {
  sfVideoMode		mode;
  t_fb			*fb;
  sfRenderWindow	*window;
  sfTexture		*texture;
  sfSprite		*sprite;
  sfEvent		event;
}		t_window;

t_window	*c8_init_window();

t_fb		*c8_init_framebuffer(uint8_t width, uint8_t height);
void		c8_destroy_framebuffer(t_fb **fb);
void		c8_clear_framebuffer(t_fb *fb);
void		c8_put_pixel(t_fb *fb, uint8_t x, uint8_t y, sfColor color);
bool		c8_is_pixel_set(t_fb *fb, uint8_t x, uint8_t y);
void		c8_toggle_pixel(t_fb *fb, uint8_t x, uint8_t y);
