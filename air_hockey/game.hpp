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
	void hit_puck(type_piece type);
	void confines(type_piece type);
	void extrude();
	void spawn_item();
	void behav_item(piece& puck);
	void execute_item(Item type, piece& puck);
	std::unique_ptr<GUI_SDL> _lib;
	std::vector<piece> _pieces;
	bool _hard = false, _play = false, _mute = false;
	Uint32 _startItemTime = 0, _coolDownTime = 0;
	Event_en _event;

};
