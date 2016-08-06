#include "GameConstants.hpp"

int game::AnimationName::getAnimationName(int playSide, int entityType, int animation)
{
	return (playSide-1)*100 + entityType*20 + animation;
}
