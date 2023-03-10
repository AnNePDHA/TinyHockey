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
	goal
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
	speedUp = 1,
	slowDown = 2,
	stop = 3
};

struct piece
{
	int8_t score;
	double x, y, xp, yp, xs, ys; // x,y | previous x,y | speed between previous and current 
};
