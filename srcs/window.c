#include <stdlib.h>
#include "window.h"

t_fb		*c8_init_framebuffer(uint8_t width, uint8_t height) {
  t_fb		*fb;

  fb = malloc(sizeof(t_fb));
  if (!fb)
    return (NULL);
  fb->width = width;
  fb->height = height;
  fb->pixels = malloc(sizeof(sfUint8) * 4 * width * height);
  if (!fb->pixels) {
    free(fb);
    return (NULL);
  }
  return (fb);
}

void	c8_put_pixel(t_fb *fb, uint8_t x, uint8_t y, sfColor color)
{
  if (((y * fb->width + x) * 4) >= 0
      && ((y * fb->width + x) * 4 + 3) < (fb->width * fb->height * 4))
  {
    fb->pixels[(y * fb->width + x) * 4] = color.r;
    fb->pixels[(y * fb->width + x) * 4 + 1] = color.g;
    fb->pixels[(y * fb->width + x) * 4 + 2] = color.b;
    fb->pixels[(y * fb->width + x) * 4 + 3] = color.a;
  }
}

bool	c8_is_pixel_set(t_fb *fb, uint8_t x, uint8_t y) {
  if (fb->pixels[(y * fb->width + x) * 4] != BLACK_PIXEL
      || fb->pixels[(y * fb->width + x) * 4 + 1] != BLACK_PIXEL
      || fb->pixels[(y * fb->width + x) * 4 + 2] != BLACK_PIXEL)
    return (true);
  return (false);
}

void	c8_toggle_pixel(t_fb *fb, uint8_t x, uint8_t y) {
  sfColor	unset = {BLACK_PIXEL, BLACK_PIXEL, BLACK_PIXEL, 255};
  sfColor	set = {WHITE_PIXEL, WHITE_PIXEL, WHITE_PIXEL, 255};

  if (c8_is_pixel_set(fb, x, y))
    c8_put_pixel(fb, x, y, unset);
  else
    c8_put_pixel(fb, x, y, set);
}

void		c8_clear_framebuffer(t_fb *fb) {
  size_t	size = fb->width * fb->height * 4;

  for (size_t i = 0; i < size; i++)
    fb->pixels[i] = 0;
}

void		c8_destroy_framebuffer(t_fb **fb) {
  free((*fb)->pixels);
  free(*fb);
}

t_window	*c8_init_window() {
  t_window	*win;

  win = malloc(sizeof(t_window));
  if (!win)
    return (NULL);
  win->mode.width = WIDTH;
  win->mode.height = HEIGHT;
  win->mode.bitsPerPixel = 32;
  win->fb = c8_init_framebuffer(WIDTH, HEIGHT);
  win->texture = sfTexture_create(WIDTH, HEIGHT);
  win->sprite = sfSprite_create();
  win->window = sfRenderWindow_create(win->mode, "Chip8 - Display", sfClose, NULL);
  if (!win->texture || !win->window)
    return (NULL);
  sfSprite_setTexture(win->sprite, win->texture, sfTrue);
  return (win);
}
