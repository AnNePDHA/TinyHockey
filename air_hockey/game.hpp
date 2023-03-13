#pragma once

#include "GUI_SDL.hpp"

class AirHockey
{
public:
	int extrudeCount;
	AirHockey();
	~AirHockey();
	void start();

private:
	void begin_pos();
	void behav_bot();
	void behav_puck();
	void behav_pl();
	void hit_puck(type_piece type);
	void confines(type_piece type);
	void extrude();
	void spawn_item();
	void behav_item(piece& puck);
	void execute_item(Item type, piece& puck);
	std::unique_ptr<GUI_SDL> _lib;
	std::vector<piece> _pieces;
	bool _hard = false, _play = false, _end = false, _mute = false, _effectStart = false;
	Uint32 _startItemTime = 0, _coolDownTime = 0, _effectDuration = -1;
	Item _puckStatus = none;
	Event_en _event;

};
