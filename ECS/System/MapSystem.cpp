#include "MapSystem.h"
#include "../Component/Components.hpp"
#include "../../Config/GameConstants.hpp"
MapSystem::MapSystem()
{
	addComponentType<PositionComponent>();
	addComponentType<PlaySideComponent>();
	addComponentType<TypeComponent>();

}

void MapSystem::begin()
{
	for (auto map : _maps) {
		map.second->removeDynamicEntities();
	}
}

void MapSystem::initialize()
{

}

void MapSystem::processEntities(artemis::ImmutableBag<artemis::Entity*>& bag, float accumulatedDelta)
{
	for (auto i = 0; i < bag.getCount(); i++) {
		processEntity(*bag.get(i), accumulatedDelta);
	}

}

void MapSystem::processEntity(artemis::Entity & e, float accumulatedDelta)
{
	int entityType = getComponent<TypeComponent>(e)->getEntityType();
	if (entityType == game::entity::TROOP) {
		int playSide = getComponent<PlaySideComponent>(e)->getSide();
		if (_maps.find(playSide) != _maps.end()) {
			auto pos = getComponent<PositionComponent>(e)->getPosition()->toVec2();
			_maps.at(playSide)->addDynamicEntity(pos, e.getId(), true);
		}
	}
}


void MapSystem::addMapMask(int playSide, Graph * mapMask)
{
	_maps.insert(std::make_pair(playSide, mapMask));
}

Graph * MapSystem::getMapMask(int playSide)
{
	if (_maps.find(playSide) != _maps.end()) {
		return _maps.at(playSide);
	}
	return nullptr;
}

void MapSystem::addCustomMask(int type, Graph * graph)
{
	_custom_maps.insert(std::make_pair(type, graph));
}

Graph * MapSystem::getCustomMask(int type)
{
	if (_custom_maps.find(type) != _custom_maps.end()) {
		return _custom_maps.at(type);
	}
	return nullptr;
}

std::vector<int> MapSystem::getEntitiesAroundPosition(cocos2d::Vec2 position, int playSide)
{

	std::vector<int> result;
	if (playSide == game::side::ALL) {
		for (auto x : _maps) {
			auto sideEntities = getEntitiesAroundPosition(position, x.first);
			for (auto e : sideEntities) {
				result.push_back(e);
			}
		}
		return result;
	}

	auto map = getMapMask(playSide);
	if (map) {
		auto grid = map->get(position.x, position.y);
		if (grid) {
			int c_x = grid->getX();
			int c_y = grid->getY();
			if (grid->hasEntities()) {
				for (auto entityID : grid->getEntities()) result.push_back(entityID);
			}

			//{
			//	auto neighbor = map->get(c_x, c_y, game::Align::LEFT);
			//	if (neighbor && neighbor->hasEntities()) {
			//		for (auto entityID : neighbor->getEntities()) result.push_back(entityID);
			//	}
			//}

			//{
			//	auto neighbor = map->get(c_x, c_y, game::Align::TOP_LEFT);
			//	if (neighbor && neighbor->hasEntities()) {
			//		for (auto entityID : neighbor->getEntities()) result.push_back(entityID);
			//	}
			//}

			//{
			//	auto neighbor = map->get(c_x, c_y, game::Align::TOP);
			//	if (neighbor && neighbor->hasEntities()) {
			//		for (auto entityID : neighbor->getEntities()) result.push_back(entityID);
			//	}
			//}

			//{
			//	auto neighbor = map->get(c_x, c_y, game::Align::TOP_RIGHT);
			//	if (neighbor && neighbor->hasEntities()) {
			//		for (auto entityID : neighbor->getEntities()) result.push_back(entityID);
			//	}
			//}
			//{
			//	auto neighbor = map->get(c_x, c_y, game::Align::RIGHT);
			//	if (neighbor && neighbor->hasEntities()) {
			//		for (auto entityID : neighbor->getEntities()) result.push_back(entityID);
			//	}
			//}
			//{
			//	auto neighbor = map->get(c_x, c_y, game::Align::BOTTOM_RIGHT);
			//	if (neighbor && neighbor && neighbor->hasEntities()) {
			//		for (auto entityID : neighbor->getEntities()) result.push_back(entityID);
			//	}
			//}
			//{
			//	auto neighbor = map->get(c_x, c_y, game::Align::BOTTOM_LEFT);
			//	if (neighbor && neighbor->hasEntities()) {
			//		for (auto entityID : neighbor->getEntities()) result.push_back(entityID);
			//	}
			//}
		}
	}
	return result;
}

std::vector<int> MapSystem::getEntitiesInPosition(cocos2d::Vec2 position, int playSide)
{
	std::vector<int> result;
	if (playSide == game::side::ALL) {
		for (auto x : _maps) {
			auto sideEntities = getEntitiesInPosition(position, x.first);
			for (auto e : sideEntities) {
				result.push_back(e);
			}
		}
		return result;
	}

	auto map = getMapMask(playSide);
	if (map) {
		auto grid = map->get(position.x, position.y);
		if (grid) {
			int c_x = grid->getX();
			int c_y = grid->getY();
			if (grid->hasEntities()) {
				for (auto entityID : grid->getEntities()) result.push_back(entityID);
			}
		}
	}
	return result;
}

std::vector<int> MapSystem::getEntitiesInRange(cocos2d::Vec2 position, float rw, float rh, int playSide)
{
	std::vector<int> result;

	if (playSide == game::side::ALL) {
		for (auto x : _maps) {
			auto sideEntities = getEntitiesInRange(position, rw, rh, x.first);
			for (auto e : sideEntities) {
				result.push_back(e);
			}
		}
		return result;
	}
	auto map = getMapMask(playSide);
	if (map) {
		int minx = (position.x - rw) / map->getCellWidth();
		int miny = (position.y - rh) / map->getCellHeight();
		int maxx = (position.x + rw) / map->getCellWidth();
		int maxy = (position.y + rh) / map->getCellHeight();

		for (int j = miny; j <= maxy; j++) {
			for (int i = minx; i <= maxx; i++) {
				auto grid = map->get(i, j);
				if (grid && grid->hasEntities()) {
					for (auto id : grid->getEntities()) {
						result.push_back(id);
					}
				}
			}
		}
	}
	return result;
}
