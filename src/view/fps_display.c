#include "cub3d.h"

#define FPS_DISPLAY_X 10
#define FPS_DISPLAY_Y 250
#define DIGIT_WIDTH 8
#define DIGIT_HEIGHT 12

static void	draw_digit(t_renderer *renderer, int digit, int x, int y, int color)
{
	int	patterns[10][12] = {
		{0x3C, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x3C}, // 0
		{0x18, 0x38, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x7E}, // 1
		{0x3C, 0x66, 0x06, 0x06, 0x0C, 0x18, 0x30, 0x60, 0x60, 0x60, 0x66, 0x7E}, // 2
		{0x3C, 0x66, 0x06, 0x06, 0x1C, 0x06, 0x06, 0x06, 0x06, 0x06, 0x66, 0x3C}, // 3
		{0x0C, 0x1C, 0x2C, 0x4C, 0x4C, 0x4C, 0x7E, 0x0C, 0x0C, 0x0C, 0x0C, 0x0C}, // 4
		{0x7E, 0x60, 0x60, 0x60, 0x7C, 0x06, 0x06, 0x06, 0x06, 0x06, 0x66, 0x3C}, // 5
		{0x3C, 0x66, 0x60, 0x60, 0x7C, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x3C}, // 6
		{0x7E, 0x06, 0x06, 0x0C, 0x18, 0x18, 0x30, 0x30, 0x30, 0x30, 0x30, 0x30}, // 7
		{0x3C, 0x66, 0x66, 0x66, 0x3C, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x3C}, // 8
		{0x3C, 0x66, 0x66, 0x66, 0x66, 0x66, 0x3E, 0x06, 0x06, 0x06, 0x66, 0x3C}  // 9
	};
	int	row;
	int	col;
	int	pattern;

	if (digit < 0 || digit > 9)
		return ;
	row = 0;
	while (row < DIGIT_HEIGHT)
	{
		pattern = patterns[digit][row];
		col = 0;
		while (col < DIGIT_WIDTH)
		{
			if (pattern & (1 << (7 - col)))
				renderer_put_pixel(renderer, x + col, y + row, color);
			col++;
		}
		row++;
	}
}

static void	draw_fps_background(t_renderer *renderer, int x, int y, int width, int height)
{
	int	bg_x;
	int	bg_y;

	bg_y = y - 2;
	while (bg_y < y + height + 2)
	{
		bg_x = x - 2;
		while (bg_x < x + width + 2)
		{
			renderer_put_pixel(renderer, bg_x, bg_y, 0x000000);
			bg_x++;
		}
		bg_y++;
	}
}

static void	draw_fps_text(t_renderer *renderer, int x, int y)
{
	int	fps_pattern[12] = {0x7E, 0x60, 0x60, 0x60, 0x7C, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60}; // F
	int	p_pattern[12] = {0x7C, 0x66, 0x66, 0x66, 0x7C, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x60}; // P
	int	s_pattern[12] = {0x3C, 0x66, 0x60, 0x60, 0x3C, 0x06, 0x06, 0x06, 0x06, 0x06, 0x66, 0x3C}; // S
	int	colon_pattern[12] = {0x00, 0x00, 0x18, 0x18, 0x00, 0x00, 0x00, 0x00, 0x18, 0x18, 0x00, 0x00}; // :
	int	row;
	int	col;

	row = 0;
	while (row < DIGIT_HEIGHT)
	{
		col = 0;
		while (col < DIGIT_WIDTH)
		{
			if (fps_pattern[row] & (1 << (7 - col)))
				renderer_put_pixel(renderer, x + col, y + row, COLOR_WHITE);
			if (p_pattern[row] & (1 << (7 - col)))
				renderer_put_pixel(renderer, x + DIGIT_WIDTH + 1 + col, y + row, COLOR_WHITE);
			if (s_pattern[row] & (1 << (7 - col)))
				renderer_put_pixel(renderer, x + 2 * (DIGIT_WIDTH + 1) + col, y + row, COLOR_WHITE);
			if (colon_pattern[row] & (1 << (7 - col)))
				renderer_put_pixel(renderer, x + 3 * (DIGIT_WIDTH + 1) + col, y + row, COLOR_WHITE);
			col++;
		}
		row++;
	}
}

void	render_fps_display(t_renderer *renderer)
{
	double	current_fps;
	int		fps_int;
	int		fps_tens;
	int		fps_units;
	int		display_width;

	current_fps = perf_get_current_fps();
	if (current_fps > 999.0)
		current_fps = 999.0;
	fps_int = (int)current_fps;
	fps_tens = fps_int / 10;
	fps_units = fps_int % 10;
	display_width = 4 * (DIGIT_WIDTH + 1) + 2 * DIGIT_WIDTH;
	draw_fps_background(renderer, FPS_DISPLAY_X, FPS_DISPLAY_Y, display_width, DIGIT_HEIGHT);
	draw_fps_text(renderer, FPS_DISPLAY_X, FPS_DISPLAY_Y);
	if (fps_tens > 0)
		draw_digit(renderer, fps_tens, FPS_DISPLAY_X + 4 * (DIGIT_WIDTH + 1), FPS_DISPLAY_Y, COLOR_GREEN);
	draw_digit(renderer, fps_units, FPS_DISPLAY_X + 4 * (DIGIT_WIDTH + 1) + DIGIT_WIDTH + 1, FPS_DISPLAY_Y, COLOR_GREEN);
}