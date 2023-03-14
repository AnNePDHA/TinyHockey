#include "GUI_SDL.hpp"
#include <string>

GUI_SDL::GUI_SDL()
{
	if (SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO) < 0)
	{
		std::cerr << "SDL error: " << SDL_GetError() << std::endl;
		exit(1);
	}

	_win = SDL_CreateWindow("Space Hockey", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);
	if (!_win)
	{
		std::cerr << "SDL error: " << SDL_GetError() << std::endl;
		exit(1);
	}

	_rend = SDL_CreateRenderer(_win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!_rend)
	{
		std::cerr << "SDL error: " << SDL_GetError() << std::endl;
		exit(1);
	}

	load_ttf();
	load_img();
	load_sound();

	_src = { 0, 0, SIZE_PIECE, SIZE_PIECE };
}

void GUI_SDL::load_ttf()
{
	if (TTF_Init() < 0)
	{
		std::cerr << "TTF error: " << TTF_GetError() << std::endl;
		exit(3);
	}

	_font = TTF_OpenFont("res/Font.ttf", 45);

	if (!_font)
	{
		std::cerr << "TTF error: " << TTF_GetError() << std::endl;
		exit(3);
	}
}

void GUI_SDL::load_img()
{
	if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) || !(IMG_Init(IMG_INIT_JPG) & IMG_INIT_JPG))
	{
		std::cerr << "IMG error: " << IMG_GetError() << std::endl;
		exit(2);
	}

	_puck = IMG_LoadTexture(_rend, "res/ball.png");
	if (!_puck)
	{
		std::cerr << "IMG error: " << IMG_GetError() << std::endl;
		exit(2);
	}
	_bat = IMG_LoadTexture(_rend, "res/playerRed.png");
	if (!_bat)
	{
		std::cerr << "IMG error: " << IMG_GetError() << std::endl;
		exit(2);
	}
	_batOther = IMG_LoadTexture(_rend, "res/playerBlue.png");
	if (!_batOther)
	{
		std::cerr << "IMG error: " << IMG_GetError() << std::endl;
		exit(2);
	}
}

void GUI_SDL::load_sound()
{
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096))
	{
		std::cerr << "MIX error: " << Mix_GetError() << std::endl;
		exit(4);
	}

	_music = Mix_LoadMUS("res/bgm.mp3");
	if (!_music)
	{
		std::cerr << "MIX error: " << Mix_GetError() << std::endl;
		exit(4);
	}
	_board = Mix_LoadWAV("res/WallHit.mp3");
	if (!_board)
	{
		std::cerr << "MIX error: " << Mix_GetError() << std::endl;
		exit(4);
	}
	_hit = Mix_LoadWAV("res/BallHit.mp3");
	if (!_hit)
	{
		std::cerr << "MIX error: " << Mix_GetError() << std::endl;
		exit(4);
	}
	_goal = Mix_LoadWAV("res/Win.mp3");
	if (!_goal)
	{
		std::cerr << "MIX error: " << Mix_GetError() << std::endl;
		exit(4);
	}
	_buff = Mix_LoadWAV("res/Item.mp3");
	if (!_buff)
	{
		std::cerr << "MIX error: " << Mix_GetError() << std::endl;
		exit(4);
	}
	Mix_PlayMusic(_music, -1);
}

Event_en GUI_SDL::checkEvent(piece & pl, piece & plR, bool _hard, bool end) const
{
	SDL_Event event;
	const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
	if (currentKeyStates[SDL_SCANCODE_UP]) {
		if (_hard == false) {
			plR.xp = plR.x;
			plR.yp = plR.y;
			plR.y = plR.y - plR.ys;
			std::cout << plR.ys << " " << plR.xs;
			plR.xs *= 1.2;
			plR.ys *= 1.2;
		}
	}
	if (currentKeyStates[SDL_SCANCODE_LEFT]) {
		if (_hard == false) {
			plR.xp = plR.x;
			plR.yp = plR.y;
			plR.x = plR.x - plR.xs;
			plR.xs *= 1.2;
			plR.ys *= 1.2;
		}
	}
	if (currentKeyStates[SDL_SCANCODE_RIGHT]) {
		if (_hard == false) {
			plR.xp = plR.x;
			plR.yp = plR.y;
			plR.x = plR.x + plR.xs;
			plR.xs *= 1.2;
			plR.ys *= 1.2;
		}
	}
	if (currentKeyStates[SDL_SCANCODE_DOWN]) {
		if (_hard == false) {
			plR.xp = plR.x;
			plR.yp = plR.y;
			plR.y = plR.y + plR.ys;
			plR.xs *= 1.2;
			plR.ys *= 1.2;
		}
	}

	if (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			return esc;
		case SDL_KEYDOWN:
		{
			switch (event.key.keysym.sym)
			{

			//case SDLK_LEFT:
				//return dific;

			case SDLK_q:
				return esc;

			case SDLK_ESCAPE:
				return menu;

			case SDLK_KP_ENTER:

			case SDLK_RETURN:
				return play;

			case SDLK_m:
				return mus;

			case SDLK_UP:
				pl.xp = pl.x;
				pl.yp = pl.y;
				pl.y = pl.y - pl.ys;
				pl.xs *= 1.2;
				pl.ys *= 1.2;
				break;

			case SDLK_DOWN:
				pl.xp = pl.x;
				pl.yp = pl.y;
				pl.y = pl.y + pl.ys;
				pl.xs *= 1.2;
				pl.ys *= 1.2;
				break;

			case SDLK_LEFT:
				pl.xp = pl.x;
				pl.yp = pl.y;
				pl.x = pl.x - pl.xs;
				pl.xs *= 1.2;
				pl.ys *= 1.2;
				break;

			case SDLK_RIGHT:
				pl.xp = pl.x;
				pl.yp = pl.y;
				pl.x = pl.x + pl.xs;
				pl.xs *= 1.2;
				pl.ys *= 1.2;
				break;
			}


		}
		//case SDL_MOUSEMOTION:
		//{
			//pl.xp = pl.x;
			//pl.yp = pl.y;
			//pl.x = event.motion.x - SIZE_BAT / 2;
			//pl.y = event.motion.y - SIZE_BAT / 2;
			//break;
		//}//

		case SDL_MOUSEBUTTONUP:
		{
			if (event.button.button == SDL_BUTTON_LEFT)
			{
				if (end) {
					if (event.button.y > HEIGHT / 2 - 100 && event.button.y < HEIGHT / 2 + 100
						&& event.button.x > WIDTH / 2 - 100 && event.button.x < WIDTH / 2 + 100)
						return menu;
				}
				if (event.button.y > HEIGHT / 2 - 30 && event.button.y < HEIGHT / 2 + 30)
					return dific;
				if (event.button.y > HEIGHT / 2 + 70 && event.button.y < HEIGHT / 2 + 115
					&& event.button.x > 140 && event.button.x < 340)
					return play;
				if (event.button.y > HEIGHT - 54 && event.button.x < 54)
					return mus;
			}
			if (event.button.button == SDL_BUTTON_RIGHT)
				return menu;
			break;
		}
		}
	}
	return nothing;
}

void GUI_SDL::draw(const std::vector<piece> & pieces)
{
	SDL_RenderClear(_rend);
	SDL_RenderCopy(_rend, _background, NULL, NULL);

	_color = { RED_COLOR };
	_dst.x = 450;
	_dst.y = HEIGHT / 2 - 40;
	_dst.h = 39;
	_dst.w = 21;
	_ttf = TTF_RenderText_Solid(_font, std::to_string(pieces[0].score).c_str(), _color);
	_text = SDL_CreateTextureFromSurface(_rend, _ttf);
	SDL_RenderCopy(_rend, _text, 0, &_dst);
	SDL_FreeSurface(_ttf);
	SDL_DestroyTexture(_text);

	_dst.y = HEIGHT / 2;
	_ttf = TTF_RenderText_Solid(_font, std::to_string(pieces[1].score).c_str(), _color);
	_text = SDL_CreateTextureFromSurface(_rend, _ttf);
	SDL_RenderCopy(_rend, _text, 0, &_dst);
	SDL_FreeSurface(_ttf);
	SDL_DestroyTexture(_text);

	_dst.h = _dst.w = SIZE_PUCK;
	_dst.x = pieces[2].x;
	_dst.y = pieces[2].y;
	SDL_RenderCopy(_rend, _puck, &_src, &_dst);

	_dst.h = _dst.w = SIZE_BAT;
	_dst.x = pieces[0].x;
	_dst.y = pieces[0].y;

	SDL_RenderCopy(_rend, _bat, &_src, &_dst);

	_dst.x = pieces[1].x;
	_dst.y = pieces[1].y;
	SDL_RenderCopy(_rend, _batOther, &_src, &_dst);

	draw_item(pieces[3]);
	draw_dynamic();
	SDL_RenderPresent(_rend);
}

void GUI_SDL::new_game(bool hard)
{
	SDL_DestroyTexture(_background);
	SDL_RenderClear(_rend);
	SDL_RenderCopy(_rend, _background, NULL, NULL);
	_background = IMG_LoadTexture(_rend, (hard ? "res/AI.png" : "res/normal.png"));
	if (!_background)
	{
		std::cerr << "IMG error: " << IMG_GetError() << std::endl;
		exit(2);
	}

	SDL_RenderClear(_rend);
	SDL_RenderCopy(_rend, _background, NULL, NULL);
	draw_dynamic();
	SDL_RenderPresent(_rend);

	SDL_DestroyTexture(_background);
	_background = IMG_LoadTexture(_rend, "res/background.png");
	if (!_background)
	{
		std::cerr << "IMG error: " << IMG_GetError() << std::endl;
		exit(2);
	}
}

void GUI_SDL::end_game(const std::vector<piece>& pieces) {
	//SDL_DestroyTexture(_background);
	SDL_RenderClear(_rend);
	SDL_RenderCopy(_rend, _background, NULL, NULL);
	_background = IMG_LoadTexture(_rend, "res/background.png");
	if (!_background)
	{
		std::cerr << "IMG error: " << IMG_GetError() << std::endl;
		exit(2);
	}

	_dst.w = 100;
	_dst.h = 100;
	_dst.x = (WIDTH - SIZE_BAT - _dst.w / 2) / 2;
	_dst.y = (HEIGHT - SIZE_BAT - _dst.h / 2) / 4;
	if (pieces[0].score > pieces[1].score) {
		_ttf = TTF_RenderText_Solid(_font, "WIN", { BLUE_COLOR });
		_text = SDL_CreateTextureFromSurface(_rend, _ttf);
		SDL_RenderCopy(_rend, _text, 0, &_dst);
		SDL_FreeSurface(_ttf);
		SDL_DestroyTexture(_text);

		_tff = TTF_RenderText_Solid(_font, "LOSE", { RED_COLOR });
	}
	else {
		_ttf = TTF_RenderText_Solid(_font, "LOSE", { RED_COLOR });
		_text = SDL_CreateTextureFromSurface(_rend, _ttf);
		SDL_RenderCopy(_rend, _text, 0, &_dst);
		SDL_FreeSurface(_ttf);
		SDL_DestroyTexture(_text);

		_tff = TTF_RenderText_Solid(_font, "WIN", { BLUE_COLOR });
	}
	
	_dst.y = _dst.y * 3;
	_text = SDL_CreateTextureFromSurface(_rend, _tff);
	SDL_RenderCopy(_rend, _text, 0, &_dst);
	SDL_FreeSurface(_tff);
	SDL_DestroyTexture(_text);

	_dst.w = 125;
	_dst.h = 125;
	_dst.x = (WIDTH - SIZE_BAT - _dst.w / 2) / 2;
	_dst.y = (HEIGHT - SIZE_BAT - _dst.h / 2) / 2;

	_ttf = TTF_RenderText_Solid(_font, "RETRY", { 255, 255, 255 });
	_text = SDL_CreateTextureFromSurface(_rend, _ttf);
	SDL_RenderCopy(_rend, _text, 0, &_dst);
	SDL_FreeSurface(_ttf);
	SDL_DestroyTexture(_text);

	_dst.w = 50;
	_dst.h = 50;
	_dst.x = (WIDTH - SIZE_BAT) / 2;
	_dst.y = (HEIGHT - SIZE_BAT - _dst.h / 2) / 4 + 75;

	_ttf = TTF_RenderText_Solid(_font, std::to_string(pieces[0].score).c_str(), { 255, 255, 255 });
	_text = SDL_CreateTextureFromSurface(_rend, _ttf);
	SDL_RenderCopy(_rend, _text, 0, &_dst);
	SDL_FreeSurface(_ttf);
	SDL_DestroyTexture(_text);

	_dst.y = _dst.y * 3 - 75*2;
	_ttf = TTF_RenderText_Solid(_font, std::to_string(pieces[1].score).c_str(), { 255, 255, 255 });
	_text = SDL_CreateTextureFromSurface(_rend, _ttf);
	SDL_RenderCopy(_rend, _text, 0, &_dst);
	SDL_FreeSurface(_ttf);
	SDL_DestroyTexture(_text);

	SDL_RenderPresent(_rend);
}

bool GUI_SDL::change_noise()
{
	_noise = !_noise;
	if (_noise)
		Mix_ResumeMusic();
	else
		Mix_PauseMusic();
	return _noise;
}

void GUI_SDL::draw_item(const piece& item) {
	if (item.score == 0) {
		SDL_DestroyTexture(_item);
		return;
	}

	getItemTexture(item);
	if (!_item)
	{
		std::cerr << "IMG error: " << IMG_GetError() << std::endl;
		exit(2);
	}
	_dst.h = _dst.w = SIZE_ITEM;
	_dst.x = item.x;
	_dst.y = item.y;
	SDL_RenderCopy(_rend, _item, &_src, &_dst);
	//SDL_DestroyTexture(_item);
	//SDL_RenderPresent(_rend);
}

void GUI_SDL::getItemTexture(const piece& item) {
	Item type = (Item)(item.score);
	switch (type) {
		case speedUp:
			_item = IMG_LoadTexture(_rend, "res/item/item_lightning.png");
			break;
		case slowDown:
			_item = IMG_LoadTexture(_rend, "res/item/item_ice.png");
			break;
		case stop:
			_item = IMG_LoadTexture(_rend, "res/item/item_stop.png");
			break;
		case invisible:
			_item = IMG_LoadTexture(_rend, "res/item/item_invisible.png");
			break;
		case turn:
			_item = IMG_LoadTexture(_rend, "res/item/item_turn.png");
			break;
		default:
			_item = IMG_LoadTexture(_rend, "res/item/item_stop.png");
			break;
	}
}

void GUI_SDL::executeEffect(Item type, const piece& puck) {
	switch (type) {
		case invisible:
			SDL_DestroyTexture(_puck);
			//_dst.h = _dst.w = SIZE_PUCK;
			//_dst.x = puck.x;
			//_dst.y = puck.y;
			_puck = IMG_LoadTexture(_rend, "res/ball_invisible.png");
			if (!_puck)
			{
				std::cerr << "IMG error: " << IMG_GetError() << std::endl;
				exit(2);
			}
			SDL_RenderCopy(_rend, _puck, &_src, &_dst);
			break;
		case none:
			SDL_DestroyTexture(_puck);
			//_dst.h = _dst.w = SIZE_PUCK;
			//_dst.x = puck.x;
			//_dst.y = puck.y;
			_puck = IMG_LoadTexture(_rend, "res/ball.png");
			if (!_puck)
			{
				std::cerr << "IMG error: " << IMG_GetError() << std::endl;
				exit(2);
			}
			//SDL_RenderCopy(_rend, _puck, &_src, &_dst);
			break;
		default:
			break;
	}
}


void GUI_SDL::draw_dynamic()
{
	_dynamic = IMG_LoadTexture(_rend, (_noise ? "res/on.png" : "res/mute.png"));
	if (!_dynamic)
	{
		std::cerr << "IMG error: " << IMG_GetError() << std::endl;
		exit(2);
	}
	_dst.h = _dst.w = SIZE_BAT;
	_dst.x = 2;
	_dst.y = HEIGHT - 50;
	SDL_RenderCopy(_rend, _dynamic, &_src, &_dst);
	SDL_DestroyTexture(_dynamic);
}

void GUI_SDL::play_sound(Collision s)
{
	if (!_noise)
		return;
	if (s == board)
		Mix_PlayChannel(-1, _board, 0);
	else if (s == hit)
		Mix_PlayChannel(-1, _hit, 0);
	else if (s == item) {
		Mix_PlayChannel(-1, _buff, 0);
	}
	else {
		Mix_PlayChannel(-1, _goal, 0);
		SDL_Delay(300);
	}
}

GUI_SDL::~GUI_SDL()
{
	SDL_DestroyTexture(_background);
	SDL_DestroyTexture(_puck);
	SDL_DestroyTexture(_bat);
	SDL_DestroyTexture(_batOther);
	SDL_DestroyTexture(_dynamic);
	SDL_DestroyTexture(_text);
	SDL_DestroyTexture(_item);
	TTF_CloseFont(_font);
	Mix_FreeMusic(_music);
	Mix_FreeChunk(_board);
	Mix_FreeChunk(_hit);
	Mix_FreeChunk(_goal);
	Mix_FreeChunk(_buff);
	SDL_DestroyRenderer(_rend);
	SDL_DestroyWindow(_win);
	Mix_CloseAudio();
	//Mix_Quit();
	TTF_Quit();
	SDL_Quit();
}
