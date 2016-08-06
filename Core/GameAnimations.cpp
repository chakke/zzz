#include "GameAnimations.hpp"
#include "../UIParser/Atlas/AtlasCache.hpp"
#include "../Config/GameConstants.hpp"
namespace game {
	GameAnimations* instance = nullptr;
	GameAnimations* GameAnimations::getInstance() {
		if (!instance) {
			instance = new GameAnimations();
		}
		return instance;
	}
	GameAnimations::GameAnimations() {}

	void GameAnimations::loadAnimations() {
		for (auto playSide = 1; playSide < 5; playSide++) {
			loadAnimation(playSide, game::troop::BABARIAN, game::AnimationName::IDLE_UP);
			loadAnimation(playSide, game::troop::BABARIAN, game::AnimationName::IDLE_DOWN);
			loadAnimation(playSide, game::troop::BABARIAN, game::AnimationName::MOVE_UP);
			loadAnimation(playSide, game::troop::BABARIAN, game::AnimationName::MOVE_DOWN);
			loadAnimation(playSide, game::troop::BABARIAN, game::AnimationName::ATTACK_UP);
			loadAnimation(playSide, game::troop::BABARIAN, game::AnimationName::ATTACK_DOWN);
			loadAnimation(playSide, game::troop::BABARIAN, game::AnimationName::DIE_UP);
			loadAnimation(playSide, game::troop::BABARIAN, game::AnimationName::DIE_DOWN);

			loadAnimation(playSide, game::troop::HORSE, game::AnimationName::IDLE_UP);
			loadAnimation(playSide, game::troop::HORSE, game::AnimationName::IDLE_DOWN);
			loadAnimation(playSide, game::troop::HORSE, game::AnimationName::MOVE_UP);
			loadAnimation(playSide, game::troop::HORSE, game::AnimationName::MOVE_DOWN);
			loadAnimation(playSide, game::troop::HORSE, game::AnimationName::ATTACK_UP);
			loadAnimation(playSide, game::troop::HORSE, game::AnimationName::ATTACK_DOWN);
			loadAnimation(playSide, game::troop::HORSE, game::AnimationName::DIE_UP);
			loadAnimation(playSide, game::troop::HORSE, game::AnimationName::DIE_DOWN);

			//loadAnimation(playSide, game::troop::ARCHER, game::AnimationName::IDLE_UP);
			//loadAnimation(playSide, game::troop::ARCHER, game::AnimationName::IDLE_DOWN);
			//loadAnimation(playSide, game::troop::ARCHER, game::AnimationName::MOVE_UP);
			//loadAnimation(playSide, game::troop::ARCHER, game::AnimationName::MOVE_DOWN);
			//loadAnimation(playSide, game::troop::ARCHER, game::AnimationName::ATTACK_UP);
			//loadAnimation(playSide, game::troop::ARCHER, game::AnimationName::ATTACK_DOWN);
			//loadAnimation(playSide, game::troop::ARCHER, game::AnimationName::DIE_UP);
			//loadAnimation(playSide, game::troop::ARCHER, game::AnimationName::DIE_DOWN);
		}

	}
	void GameAnimations::releaseAllAnimations() {

	}

	cocos2d::Animation* GameAnimations::getAnimation(int name) {
		if (_animations.find(name) == _animations.end()) {
			CCLOG("GameAnimations : cannot find animation : %d", name);
		}
		return _animations.at(name)->clone();
	}


	bool GameAnimations::loadAnimation(int playSide, int troopType, int animation) {
		int animationName = game::AnimationName::getAnimationName(playSide, troopType, animation);
		if (_animations.find(animationName) != _animations.end()) return true;

		/*number of frames. Default is 6*/
		int numberFrames = 6;
		/*time scale of animation*/
		float time_scale = .1f;
		/*should be add to cached*/
		bool add = true;
		/*start frame index*/
		int startIndex = 0;

		std::string atlasName = cocos2d::StringUtils::format("atlas/troop-%d.plist", troopType + 1);
		std::string frameName = "";
		std::string entityName = "";

		if (troopType == game::troop::BABARIAN) {
			entityName = "babarian";
		}
		else if (troopType == game::troop::HORSE) {
			entityName = "horse";
		}
		else if (troopType == game::troop::ARCHER) {
			entityName = "archer";
		}

		switch (animation)
		{
		case game::AnimationName::IDLE_UP:
			frameName = "idle-b";
			break;
		case game::AnimationName::IDLE_DOWN:
			frameName = "idle-f";
			break;
		case game::AnimationName::MOVE_UP:
			frameName = "walk-b";
			break;
		case game::AnimationName::MOVE_DOWN:
			frameName = "walk-f";
			break;
		case game::AnimationName::ATTACK_UP:
			frameName = "attack-b";
			break;
		case game::AnimationName::ATTACK_DOWN:
			frameName = "attack-f";
			break;
		case game::AnimationName::DIE_UP:
			frameName = "die";
			break;
		case game::AnimationName::DIE_DOWN:
			frameName = "die";
			break;
		default:
			break;
		}


		if (troopType == game::troop::BABARIAN) {
			switch (animation)
			{
			case game::AnimationName::IDLE_UP:				
			case game::AnimationName::IDLE_DOWN:				
			case game::AnimationName::MOVE_UP:				
			case game::AnimationName::MOVE_DOWN:
				numberFrames = 16;
				break;
			case game::AnimationName::ATTACK_UP:
			case game::AnimationName::ATTACK_DOWN:
				numberFrames = 6;
				break;
			case game::AnimationName::DIE_UP:
			case game::AnimationName::DIE_DOWN:
				numberFrames = 8;
				break;
			default:
				break;
			}
		}
		else if (troopType == game::troop::HORSE) {
			switch (animation)
			{
			case game::AnimationName::IDLE_UP:
			case game::AnimationName::IDLE_DOWN:
				numberFrames = 10;
				break;
			case game::AnimationName::MOVE_UP:
			case game::AnimationName::MOVE_DOWN:
				numberFrames = 16;
				break;
			case game::AnimationName::ATTACK_UP:
			case game::AnimationName::ATTACK_DOWN:			
			case game::AnimationName::DIE_UP:
			case game::AnimationName::DIE_DOWN:
				numberFrames = 8;
				break;
			default:
				break;
			}
		}
		else if (troopType == game::troop::ARCHER) {

		}


		std::string name = cocos2d::StringUtils::format("%s-%d-%s", entityName.c_str(), playSide, frameName.c_str());
		if (add) {
			cocos2d::Vector<cocos2d::SpriteFrame*> frames(numberFrames);
			for (int i = 0; i < numberFrames; i++) {
				auto frame = atlas_cache::getSpriteFrame(atlasName, cocos2d::StringUtils::format("%s_%d.png", name.c_str(), (i + startIndex)));
				if (frame) {
					frames.pushBack(frame);
					CC_SAFE_RETAIN(frame);
				}
			}
			cocos2d::Animation* animation = cocos2d::Animation::createWithSpriteFrames(frames, time_scale, 1);
			_animations.insert(std::make_pair(animationName, animation));
			CC_SAFE_RETAIN(animation);
			return true;
		}
		return false;
	}
}


