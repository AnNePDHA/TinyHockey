#pragma once

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <vector>
#include "piece.h"

#define WIDTH 480
#define HEIGHT 840
#define SIZE_PIECE 542
#define SIZE_BAT 50
#define SIZE_PUCK 45
#define SIZE_ITEM 90
#define BLACK_COLOR 0,0,0
#define RED_COLOR 255,0,0
#define BLUE_COLOR 0,0,255
#define MAX_SPEED SIZE_PUCK/4
#define BOOT_SP 6
#define SCORE_TO_WIN 15

class GUI_SDL
{
public:
	GUI_SDL();
	~GUI_SDL();

	void new_game(bool hard);
	Event_en checkEvent(piece & pl, piece & plR, bool _hard, bool end) const;
	void end_game(const std::vector<piece>& pieces);
	void draw(const std::vector<piece> & pieces);
	bool change_noise();
	void play_sound(Collision s);
	void getItemTexture(const piece& item);
	void executeEffect(Item type, const piece& puck);

private:
	
	void load_ttf();
	void load_img();
	void load_sound();
	void draw_dynamic();
	void draw_item(const piece& item);

	bool _noise = true;
	SDL_Window *_win;
	SDL_Renderer *_rend;
	SDL_Surface *_ttf, *_tff;
	SDL_Texture *_background, *_bat, *_batOther, *_puck, *_text, *_dynamic, *_item;
	TTF_Font *_font;
	SDL_Color _color;
	SDL_Rect _src, _dst;
	Mix_Music *_music;
	Mix_Chunk *_board, *_hit, *_goal, *_buff;
};
