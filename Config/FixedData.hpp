/*class này chứa những data đã được tính toán trước nhằm giảm thiểu tính toán trước trong game*/

#pragma once

#include "cocos2d.h"
#include "../Core/Math/Vector2.hpp"
#include "../Core/Enums.hpp"
class FixedData {
public :
	static FixedData* getInstance();	
	cocos2d::Vec2 findPosition(cocos2d::Vec2 root, int troop_index, int troop_type);
	float getBuildTime(int buiderType);
	void setBuildTime(int builderType, float time);

	int getBuildTroop(int builderType);
	void setBuildTroop(int builderType, int numTroop);
	std::vector<int> getAlignMatrix(game::Align align);
	Vector2* getTempVector2(int index);
	std::string getCastleTag(int castleID);
private :
	void preCalculateData();
	Vector2* mTemp;
	FixedData();
	std::map<int, std::map<int, cocos2d::Vec2>> _positions;
	std::map<int, float> _build_times;
	std::map<int, float> _build_troops;
	std::map<int, std::string> _castle_tags;
	std::map<game::Align, std::vector<int>> _align_matrix;
	std::vector<Vector2*> _temps;
};
