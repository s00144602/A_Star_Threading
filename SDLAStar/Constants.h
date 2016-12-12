#pragma once
#include "BasicTypes.h"

namespace Constants
{
	int const WIN_WIDTH = 1000;
	int const WIN_HEIGHT = 700;
	const int SCREEN_FPS = 160;
	const int SCREEN_TICKS_PER_FRAME = 1000 / SCREEN_FPS;

	const int MAP_SIZES[] = 
	{
		600, // used for the small 30X30 map
		1000,// used for the medium 100X100 map
		1000 // used for the large 1000X1000 map
	};

	const int CELL_SIZES[] =
	{
		20,
		10,
		1
	};

	const Point NPC_START_RANGE[] =
	{
		Point(25,28),
		Point(45,98),
		Point(750,990)
	};
}