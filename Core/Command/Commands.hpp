#pragma once
#include "cocos2d.h"

namespace command
{
	/*
	Server event : 00x;
	*/

	extern int INIT_MAP;
	extern int INIT_MATRIX_TRANSFER;
	extern int ON_NEW_MATCH;
	extern int ON_RESET_MATCH;
	extern int ON_FINISH_MATCH;

	extern int ON_ANIMATION_NEW_MATCH;
	extern int ON_GAME_OVER;

	/*INPUT : 40x*/

	extern int ON_TAP_ITEM;
	extern int ON_MOVE_OVER_ITEM;
	extern int ON_TOUCH_END_CANCEL_ITEM;
	extern int ON_TAP_BACKGROUND;

	extern int ON_GLOBAL_TAP;
	extern int ON_GLOBAL_TOUCH_BEGIN;
	extern int ON_GLOBAL_TOUCH_MOVE;
	extern int ON_GLOBAL_TOUCH_END;
	extern int ON_GLOBAL_FLING;
	extern int ON_GLOBAL_ZOOM;

	extern int ON_MOVE_GAME_CAMERA;
	extern int ON_FLING_GAME_CAMERA;
	extern int ON_ZOOM_CAMERA;
	extern int ON_UNZOOM_CAMERA;
	extern int STOP_FLING_GAME_CAMERA;
	/* Process : 60x*/
	extern int MOVE_TROOP;
	extern int ON_CLICK_GENERATE_CASTLE_HOUSE;
	extern int REQUEST_MOVE_TROOP;

	/*UI Event : 80x*/
	extern int SHOW_HUD_BUILD_TROOP;
	extern int HIDE_HUD_BUILD_TROOP;
	extern int RESET_HUD_TRANSFER;
	extern int HUD_UPDATE_TROOP;

	/*Ask for data : 100x*/
	extern int ASK_HUD_TROOP_TRANSFER_CONFIG;
	extern int ASK_GAME_RESULT;

};


