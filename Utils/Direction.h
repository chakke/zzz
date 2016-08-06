#pragma once

namespace game {
	enum class Direction
	{
		CENTER, LEFT, TOP_LEFT, TOP, TOP_RIGHT, RIGHT, BOTTOM_RIGHT, BOTTOM, BOTTOM_LEFT
	};
	/*std::string getDirectionName(Direction direction) {
		std::string str = "";
		switch (direction)
		{
		case Direction::CENTER:
			str = "center";
			break;
		case Direction::LEFT:
			str = "left";
			break;
		case Direction::TOP_LEFT:
			str = "top_left";
			break;
		case Direction::TOP:
			str = "top";
			break;
		case Direction::TOP_RIGHT:
			str = "top_right";
			break;
		case Direction::RIGHT:
			str = "right";
			break;
		case Direction::BOTTOM_RIGHT:
			str = "bottom_right";
			break;
		case Direction::BOTTOM:
			str = "bottom";
			break;
		case Direction::BOTTOM_LEFT:
			str = "bottom_left";
			break;
		default:
			str = "noname";
			break;
		}
		return str;
	}

	int getDirectionValue(Direction direction) {
		int value = -1;
		switch (direction)
		{
		case Direction::CENTER:
			value = 0;
			break;
		case Direction::LEFT:
			value = 1;
			break;
		case Direction::TOP_LEFT:
			value = 2;
			break;
		case Direction::TOP:
			value = 3;
			break;
		case Direction::TOP_RIGHT:
			value = 4;
			break;
		case Direction::RIGHT:
			value = 5;
			break;
		case Direction::BOTTOM_RIGHT:
			value = 6;
			break;
		case Direction::BOTTOM:
			value = 7;
			break;
		case Direction::BOTTOM_LEFT:
			value = 8;
			break;
		default:
			break;
		}
		return value;
	}
	Direction getDirectionByValue(int value) {
		if (value == getDirectionValue(Direction::CENTER)) return Direction::CENTER;
		if (value == getDirectionValue(Direction::LEFT)) return Direction::LEFT;
		if (value == getDirectionValue(Direction::TOP_LEFT)) return Direction::TOP_LEFT;
		if (value == getDirectionValue(Direction::TOP)) return Direction::TOP;
		if (value == getDirectionValue(Direction::TOP_RIGHT)) return Direction::TOP_RIGHT;
		if (value == getDirectionValue(Direction::RIGHT)) return Direction::RIGHT;
		if (value == getDirectionValue(Direction::BOTTOM_RIGHT)) return Direction::BOTTOM_RIGHT;
		if (value == getDirectionValue(Direction::BOTTOM)) return Direction::BOTTOM;
		if (value == getDirectionValue(Direction::BOTTOM_LEFT)) return Direction::BOTTOM_LEFT;
		return Direction::CENTER;
	}

	Direction getClockwiseDirection(Direction current) {
		if (current == Direction::CENTER) return Direction::CENTER;
		if (current == Direction::BOTTOM_LEFT) return Direction::LEFT;
		return getDirectionByValue(getDirectionValue(current) + 1);
	}
	Direction getUnClockwiseDirection(Direction current) {
		if (current == Direction::CENTER) return Direction::CENTER;
		if (current == Direction::LEFT) return Direction::BOTTOM_LEFT;
		return getDirectionByValue(getDirectionValue(current) - 1);
	}
	Direction getOppositeDirection(Direction current) {
		switch (current)
		{
		case Direction::CENTER:
			return Direction::CENTER;
		case Direction::LEFT:
			return Direction::RIGHT;
		case Direction::TOP_LEFT:
			return Direction::BOTTOM_RIGHT;
		case Direction::TOP:
			return Direction::BOTTOM;
		case Direction::TOP_RIGHT:
			return Direction::BOTTOM_LEFT;
		case Direction::RIGHT:
			return Direction::LEFT;
		case Direction::BOTTOM_RIGHT:
			return Direction::TOP_RIGHT;
		case Direction::BOTTOM:
			return Direction::TOP;
		case Direction::BOTTOM_LEFT:
			return Direction::TOP_RIGHT;
		default:
			return Direction::CENTER;
		}
	}*/
}

