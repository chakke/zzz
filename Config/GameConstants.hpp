#pragma once
#include "cocos2d.h"
namespace game {
	namespace map {
		const int SPRING = 1;
		const int SUMMER = 2;
		const int WINTER = 3;
		const int AUTUMN = 4;
	}
	namespace steering {
		const int NONE = -1;
		const int SEEK = 0;
		const int ARRIVE = 1;
		const int FLEE = 2;
		const int PURSUIT = 3;		
		const int EVADE = 4;
	}

	namespace side {
		const int NO_SIDE = -1;
		const int ALL = 0;
		const int SIDE_1 = 1;
		const int SIDE_2 = 2;
		const int SIDE_3 = 3;
		const int SIDE_4 = 4;
	}

	namespace layer {
		const int BACKGROUND = 0;
		const int STATIC_ENTITY = 1;
		const int DYNAMIC_ENTITY = 2;
		const int EFFECT = 3;
	}
	namespace group {
		const int TROOP = 0;
		const int CASTLE = 1;
	}
	namespace entity {
		const int DEFAULT = -1;
		const int TROOP = 0;
		const int CASTLE = 1;
		const int BUILDER = 2;
		const int PLAYER = 3;
		const int GROUP = 4;
		const int TRANSFER = 5;
		const int BATTLE = 6;
	}


	namespace troop {
		const int NONE = -2;
		const int ALL = -1;		
		const int BABARIAN = 0;
		const int HORSE = 1;
		const int ARCHER = 2;
		const int FORTRESS = 3;
	}

	namespace action {
		const int NONE = -1;
		const int MOVE_TO_TARGET = 0;

		const int CASTLE_SELECT = 100;
		const int CASTLE_UNSELECT = 101;
		const int CASTLE_SHOW_CIRCLE = 102;
		const int CASTLE_HIDE_CIRCLE = 103;
		const int CASTLE_SHOW_ATTACK_EFFECT = 104;
		const int CASTLE_SHOW_SHIELD_EFFECT = 105;
		const int CASTLE_SHOW_BROKEN_EFFECT = 106;


		const int BE_ATTACK = 201;
		const int DIE_ON_ATTACK = 202;
		const int KILLED_ENEMY = 203;
	}

	namespace scope {
		const int ATTACK = 0;
	}

	namespace state {
		const int FREE = -1;
		const int NONE = 0;
		const int DIE = 1;
		const int TROOP_MOVE = 2;
		const int TROOP_STAY = 3;
		const int TROOP_ATTACK = 4;
		
		const int CASTLE_BATTLE = 1;
		

		const int BATTLE_BEGIN = 1;
		const int BATTLE_END = 2;
	}
	namespace AnimationName {
		const int  NONE = 0;
		/*
		for player type 0;
		*/
		const int  IDLE_UP = 1;
		const int  IDLE_DOWN = 2;
		const int  MOVE_UP = 3;
		const int  MOVE_DOWN = 4;
		const int  ATTACK_UP = 5;
		const int  ATTACK_DOWN = 6;
		const int  DIE_UP = 7;
		const int  DIE_DOWN = 8;


		const int  BABARIAN_1_IDLE_UP = 1;
		const int  BABARIAN_1_IDLE_DOWN = 2;
		const int  BABARIAN_1_MOVE_UP = 3;
		const int  BABARIAN_1_MOVE_DOWN = 4;
		const int  BABARIAN_1_ATTACK_UP = 5;
		const int  BABARIAN_1_ATTACK_DOWN = 6;
		const int  BABARIAN_1_DIE_UP = 7;
		const int  BABARIAN_1_DIE_DOWN = 8;



		const int  HORSE_1_IDLE_UP = 21;
		const int  HORSE_1_IDLE_DOWN = 22;
		const int  HORSE_1_MOVE_UP = 23;
		const int  HORSE_1_MOVE_DOWN = 24;
		const int  HORSE_1_ATTACK_UP = 25;
		const int  HORSE_1_ATTACK_DOWN = 26;
		const int  HORSE_1_DIE_UP = 27;
		const int  HORSE_1_DIE_DOWN = 28;


		const int  ARCHER_1_IDLE_UP = 41;
		const int  ARCHER_1_IDLE_DOWN = 42;
		const int  ARCHER_1_MOVE_UP = 43;
		const int  ARCHER_1_MOVE_DOWN = 44;
		const int  ARCHER_1_ATTACK_UP = 45;
		const int  ARCHER_1_ATTACK_DOWN = 46;
		const int  ARCHER_1_DIE_UP = 47;
		const int  ARCHER_1_DIE_DOWN = 48;
		/*
		for player type 1;
		*/

		const int  BABARIAN_2_IDLE_UP = 101;
		const int  BABARIAN_2_IDLE_DOWN = 102;
		const int  BABARIAN_2_MOVE_UP = 103;
		const int  BABARIAN_2_MOVE_DOWN = 104;
		const int  BABARIAN_2_ATTACK_UP = 105;
		const int  BABARIAN_2_ATTACK_DOWN = 106;
		const int  BABARIAN_2_DIE_UP = 107;
		const int  BABARIAN_2_DIE_DOWN = 108;

		const int  HORSE_2_IDLE_UP = 121;
		const int  HORSE_2_IDLE_DOWN = 122;
		const int  HORSE_2_MOVE_UP = 123;
		const int  HORSE_2_MOVE_DOWN = 124;
		const int  HORSE_2_ATTACK_UP = 125;
		const int  HORSE_2_ATTACK_DOWN = 126;
		const int  HORSE_2_DIE_UP = 127;
		const int  HORSE_2_DIE_DOWN = 128;

		const int  ARCHER_2_IDLE_UP = 141;
		const int  ARCHER_2_IDLE_DOWN = 142;
		const int  ARCHER_2_MOVE_UP = 143;
		const int  ARCHER_2_MOVE_DOWN = 144;
		const int  ARCHER_2_ATTACK_UP = 145;
		const int  ARCHER_2_ATTACK_DOWN = 146;
		const int  ARCHER_2_DIE_UP = 147;
		const int  ARCHER_2_DIE_DOWN = 148;
		/*
		for player type 2;
		*/

		const int  BABARIAN_3_IDLE_UP = 201;
		const int  BABARIAN_3_IDLE_DOWN = 202;
		const int  BABARIAN_3_MOVE_UP = 203;
		const int  BABARIAN_3_MOVE_DOWN = 204;
		const int  BABARIAN_3_ATTACK_UP = 205;
		const int  BABARIAN_3_ATTACK_DOWN = 206;
		const int  BABARIAN_3_DIE_UP = 207;
		const int  BABARIAN_3_DIE_DOWN = 208;

		const int  HORSE_3_IDLE_UP = 221;
		const int  HORSE_3_IDLE_DOWN = 222;
		const int  HORSE_3_MOVE_UP = 223;
		const int  HORSE_3_MOVE_DOWN = 224;
		const int  HORSE_3_ATTACK_UP = 225;
		const int  HORSE_3_ATTACK_DOWN = 226;
		const int  HORSE_3_DIE_UP = 227;
		const int  HORSE_3_DIE_DOWN = 228;

		const int  ARCHER_3_IDLE_UP = 241;
		const int  ARCHER_3_IDLE_DOWN = 242;
		const int  ARCHER_3_MOVE_UP = 243;
		const int  ARCHER_3_MOVE_DOWN = 244;
		const int  ARCHER_3_ATTACK_UP = 245;
		const int  ARCHER_3_ATTACK_DOWN = 246;
		const int  ARCHER_3_DIE_UP = 247;
		const int  ARCHER_3_DIE_DOWN = 248;


		/*
		for player type 3;
		*/
		const int  BABARIAN_4_IDLE_UP = 301;
		const int  BABARIAN_4_IDLE_DOWN = 302;
		const int  BABARIAN_4_MOVE_UP = 303;
		const int  BABARIAN_4_MOVE_DOWN = 304;
		const int  BABARIAN_4_ATTACK_UP = 305;
		const int  BABARIAN_4_ATTACK_DOWN = 306;
		const int  BABARIAN_4_DIE_UP = 307;
		const int  BABARIAN_4_DIE_DOWN = 308;

		const int  HORSE_4_IDLE_UP = 321;
		const int  HORSE_4_IDLE_DOWN = 322;
		const int  HORSE_4_MOVE_UP = 323;
		const int  HORSE_4_MOVE_DOWN = 324;
		const int  HORSE_4_ATTACK_UP = 325;
		const int  HORSE_4_ATTACK_DOWN = 326;
		const int  HORSE_4_DIE_UP = 327;
		const int  HORSE_4_DIE_DOWN = 328;

		const int  ARCHER_4_IDLE_UP = 341;
		const int  ARCHER_4_IDLE_DOWN = 342;
		const int  ARCHER_4_MOVE_UP = 343;
		const int  ARCHER_4_MOVE_DOWN = 344;
		const int  ARCHER_4_ATTACK_UP = 345;
		const int  ARCHER_4_ATTACK_DOWN = 346;
		const int  ARCHER_4_DIE_UP = 347;
		const int  ARCHER_4_DIE_DOWN = 348;

		extern int getAnimationName(int playSide, int entityType, int animation);
	}

	namespace size {
		const cocos2d::Size mCastleSize(300, 202);
		const cocos2d::Size mBuilderSize(150, 101);
	}


}