#include "FixedData.hpp"
#include "GameConstants.hpp"
#include "../Core/Math/Vector2.hpp"
FixedData* _fixed_data_instance = nullptr;
FixedData * FixedData::getInstance()
{
	if (!_fixed_data_instance) {
		_fixed_data_instance = new FixedData();
		_fixed_data_instance->preCalculateData();
	}
	return _fixed_data_instance;
}
FixedData::FixedData() {
	mTemp = new Vector2();
}
void FixedData::preCalculateData()
{
	/*Pre calculate position*/
	{
		Vector2* mRight = new Vector2(game::size::mCastleSize.width / 2, -game::size::mCastleSize.height / 2);
		Vector2* mLeft = new Vector2(-game::size::mCastleSize.width / 2, -game::size::mCastleSize.height / 2);
		mRight->scl(.2f);
		mLeft->scl(.2f);

		Vector2* mUnit = new Vector2();
		mTemp->setZero();
		// babarian
		{
			std::map<int, cocos2d::Vec2> positions;
			for (int i = 0; i < 200; i++) {
				mTemp->set(0, -game::size::mCastleSize.height / 2);
				mTemp->add(mRight);
				int row = i / 5;
				int col = i % 5;
				mUnit->set(mLeft)->scl(-1)->scl(col);
				mTemp->add(mUnit);
				mUnit->set(mRight)->scl(row);
				mTemp->add(mUnit);
				positions.insert(std::make_pair(i, mTemp->toVec2()));
			}

			_positions.insert(std::make_pair(game::troop::BABARIAN, positions));
		}

		// horse
		{
			std::map<int, cocos2d::Vec2> positions;
			for (int i = 0; i < 200; i++) {
				mTemp->set(0, -game::size::mCastleSize.height / 2);
				mTemp->add(mLeft);
				int row = i / 5;
				int col = i % 5;
				mUnit->set(mRight)->scl(-1)->scl(col);
				mTemp->add(mUnit);
				mUnit->set(mLeft)->scl(row);
				mTemp->add(mUnit);
				positions.insert(std::make_pair(i, mTemp->toVec2()));
			}

			_positions.insert(std::make_pair(game::troop::HORSE, positions));
		}
		mRight->scl(-1);
		mLeft->scl(-1);
		// archer
		{
			std::map<int, cocos2d::Vec2> positions;
			for (int i = 0; i < 200; i++) {
				mTemp->set(0, game::size::mCastleSize.height / 2);
				mTemp->add(mLeft);
				int row = i / 5;
				float col = i % 5;
				mUnit->set(mRight)->scl(-1)->scl(col);
				mTemp->add(mUnit);
				mUnit->set(mLeft)->scl(row);
				mTemp->add(mUnit);
				positions.insert(std::make_pair(i, mTemp->toVec2()));
			}

			_positions.insert(std::make_pair(game::troop::ARCHER, positions));
		}

	}


	/*Build time*/
	{
		setBuildTime(game::troop::BABARIAN, 3);
		setBuildTime(game::troop::HORSE, 5);
		setBuildTime(game::troop::ARCHER, 5);
	}
	/*Build troop*/
	{
		setBuildTroop(game::troop::BABARIAN, 5);
		setBuildTroop(game::troop::ARCHER, 10);
		setBuildTroop(game::troop::HORSE, 10);
		setBuildTroop(game::troop::FORTRESS, 8);
	}

	{

		{
			std::vector<int> aligns;
			aligns.push_back(0);
			aligns.push_back(0);
			_align_matrix.insert(std::make_pair(game::Align::CENTER, aligns));
		}
		{
			std::vector<int> aligns;
			aligns.push_back(-1);
			aligns.push_back(0);
			_align_matrix.insert(std::make_pair(game::Align::LEFT, aligns));
		}
		{
			std::vector<int> aligns;
			aligns.push_back(-1);
			aligns.push_back(1);
			_align_matrix.insert(std::make_pair(game::Align::TOP_LEFT, aligns));
		}

		{
			std::vector<int> aligns;
			aligns.push_back(0);
			aligns.push_back(1);
			_align_matrix.insert(std::make_pair(game::Align::TOP, aligns));
		}

		{
			std::vector<int> aligns;
			aligns.push_back(1);
			aligns.push_back(1);
			_align_matrix.insert(std::make_pair(game::Align::TOP_RIGHT, aligns));
		}
		{
			std::vector<int> aligns;
			aligns.push_back(1);
			aligns.push_back(0);
			_align_matrix.insert(std::make_pair(game::Align::RIGHT, aligns));
		}
		{
			std::vector<int> aligns;
			aligns.push_back(1);
			aligns.push_back(-1);
			_align_matrix.insert(std::make_pair(game::Align::BOTTOM_RIGHT, aligns));
		}
		{
			std::vector<int> aligns;
			aligns.push_back(0);
			aligns.push_back(-1);
			_align_matrix.insert(std::make_pair(game::Align::BOTTOM, aligns));
		}
		{
			std::vector<int> aligns;
			aligns.push_back(-1);
			aligns.push_back(-1);
			_align_matrix.insert(std::make_pair(game::Align::BOTTOM_LEFT, aligns));
		}
	}

	{
		while (_temps.size() < 10) {
			_temps.push_back(new Vector2());
		}
	}

}

cocos2d::Vec2 FixedData::findPosition(cocos2d::Vec2 root, int troop_index, int troop_type)
{
	mTemp->set(root)->add(_positions.at(troop_type).at(troop_index));
	return mTemp->toVec2();
}

float FixedData::getBuildTime(int buiderType)
{
	return _build_times.at(buiderType);
}

void FixedData::setBuildTime(int builderType, float time)
{
	_build_times.insert(std::make_pair(builderType, time));
}

int FixedData::getBuildTroop(int builderType)
{
	return _build_troops.at(builderType);
}

void FixedData::setBuildTroop(int builderType, int numTroop)
{
	_build_troops.insert(std::make_pair(builderType, numTroop));
}

std::vector<int> FixedData::getAlignMatrix(game::Align align)
{
	return _align_matrix.at(align);
}

Vector2 * FixedData::getTempVector2(int index)
{
	if (index < _temps.size()) {
		return _temps.at(index);
	}
	return nullptr;
}

std::string FixedData::getCastleTag(int castleID)
{
	if (_castle_tags.find(castleID) == _castle_tags.end()) {
		_castle_tags.insert(std::make_pair(castleID,cocos2d::StringUtils::format("castle_%d",castleID)));
	}
	return _castle_tags.at(castleID);
}
