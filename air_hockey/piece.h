#pragma once

enum type_piece
{
	tbot,
	tplayer,
	tpuck,
	titem
};

enum Collision
{
	board,
	hit,
	goal,
	item
};

enum Event_en
{
	nothing,
	esc,
	play,
	dific,
	mus,
	menu
};

enum Item {
	none = 0,
	speedUp = 1,
	slowDown = 2,
	stop = 3,
	invisible = 4,
	turn = 5
};

struct piece
{
	int8_t score;
	double x, y, xp, yp, xs, ys; // x,y | previous x,y | speed between previous and current 
};
