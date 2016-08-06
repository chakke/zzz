
#include "Graph.hpp"
#include "../../Utils/pugixml.hpp"
#include "../../Config/FixedData.hpp"
namespace graph {
	Grid::Type parseType(const pugi::char_t* value) {
		int type = atoi(value);
		if (type == 0) return Grid::Type::DYNAMIC;
		if (type == 1) return Grid::Type::STATIC;
		return Grid::Type::DYNAMIC;
	}


}
std::unordered_map<std::string, pugi::xml_document*> _cache_graphs;
Graph * Graph::createFromFile(const std::string & xmlFile)
{
	pugi::xml_document* doc = nullptr;

	if (_cache_graphs.find(xmlFile) == _cache_graphs.end()) {
		_cache_graphs.insert(std::make_pair(xmlFile, new pugi::xml_document()));
		doc = _cache_graphs[xmlFile];

		std::string fullPath = cocos2d::FileUtils::getInstance()->fullPathForFilename(xmlFile).c_str();
		doc->load_string(cocos2d::FileUtils::getInstance()->getStringFromFile(xmlFile).c_str());
	}
	else doc = _cache_graphs[xmlFile];
	auto graph = doc->child("graph");
	auto map = Graph::create();
	map->setDefaultValue(0);
	for (pugi::xml_attribute attr : graph.attributes())
	{
		if (strcmp(attr.name(), "width") == 0)
		{
			map->setWorldWidth(atoi(attr.value()));
		}
		else if (strcmp(attr.name(), "height") == 0)
		{
			map->setWorldHeight(atoi(attr.value()));
		}
		else if (strcmp(attr.name(), "cell_width") == 0)
		{
			map->setCellWidth(atoi(attr.value()));
		}
		else if (strcmp(attr.name(), "cell_height") == 0)
		{
			map->setCellHeight(atoi(attr.value()));
		}
		else if (strcmp(attr.name(), "default_value") == 0)
		{
			map->setDefaultValue(atof(attr.value()));
		}
	}
	map->setupDefault();


	for (pugi::xml_node cell : graph.children("cell"))
	{
		for (pugi::xml_attribute attr : cell.attributes())
		{
			for (pugi::xml_attribute attr : cell.attributes())
			{
				int x = -1;
				int y = -1;
				Grid::Type type = Grid::Type::DYNAMIC;
				float value = -1;
				for (pugi::xml_attribute attr : cell.attributes())
				{
					if (strcmp(attr.name(), "x") == 0)
					{
						x = atoi(attr.value());
					}
					else if (strcmp(attr.name(), "y") == 0)
					{
						y = atoi(attr.value());
					}
					else if (strcmp(attr.name(), "type") == 0)
					{
						type = graph::parseType(attr.value());
					}
					else if (strcmp(attr.name(), "value") == 0)
					{
						value = atof(attr.value());
					}
				}

				if (x != -1 && y != -1) {
					auto grid = map->get(x, y);
					if (grid) {
						grid->setValue(value);
						grid->setType(type);
					}
				}
			}
		}
	}


	//for (pugi::xml_node cell = graph.first_child(); cell; cell = cell.next_sibling()) {
	//	if (strcmp(cell.name(), "cell") == 0) {
	//		for (pugi::xml_attribute attr : cell.attributes())
	//		{
	//			for (pugi::xml_attribute attr : cell.attributes())
	//			{
	//				int x = -1;
	//				int y = -1;
	//				Grid::Type type = Grid::Type::DYNAMIC;
	//				float value = -1;
	//				for (pugi::xml_attribute attr : cell.attributes())
	//				{
	//					if (strcmp(attr.name(), "x") == 0)
	//					{
	//						x = atoi(attr.value());
	//					}
	//					else if (strcmp(attr.name(), "y") == 0)
	//					{
	//						y = atoi(attr.value());
	//					}
	//					else if (strcmp(attr.name(), "type") == 0)
	//					{
	//						type = graph::parseType(attr.value());
	//					}
	//					else if (strcmp(attr.name(), "value") == 0)
	//					{
	//						value = atof(attr.value());
	//					}
	//				}

	//				if (x != -1 && y != -1) {
	//					auto grid = map->get(x, y);
	//					if (grid) {
	//						grid->setValue(value);
	//						grid->setType(type);
	//					}
	//				}
	//			}
	//		}
	//	}
	//}

	return map;
}
Graph * Graph::create()
{
	auto map = new Graph();
	map->autorelease();
	map->retain();
	return map;
}
Graph * Graph::create(float width, float height, int cell_width, int cell_height, float default_value)
{
	auto map = new (std::nothrow) Graph(width, height, cell_width, cell_height, default_value);
	map->autorelease();
	map->retain();
	return map;
}
int UNIQUE_MAP_ID;
Graph::Graph(float width, float height, int cell_width, int cell_height, float default_value) {
	mWorldWidth = width / cell_width;
	mWorldHeight = height / cell_height;
	mCellWidth = cell_width;
	mCellHeight = cell_height;
	mDefaultValue = default_value;

	for (auto j = 0; j < mWorldHeight; j++) {
		for (auto i = 0; i < mWorldWidth; i++) {
			_grids.push_back(new Grid(i, j, default_value));
		}
	}
	setName(cocos2d::StringUtils::format("map-%d", UNIQUE_MAP_ID++));
}
Graph::Graph() {
	setName(cocos2d::StringUtils::format("map-%d", UNIQUE_MAP_ID++));
}
void Graph::setupDefault()
{
	_grids.clear();
	for (auto j = 0; j < mWorldHeight; j++) {
		for (auto i = 0; i < mWorldWidth; i++) {
			_grids.push_back(new Grid(i, j, mDefaultValue));
		}
	}
}

Grid* Graph::get(int cell_x, int cell_y, game::Align align)
{
	auto offset = FixedData::getInstance()->getAlignMatrix(align);
	cell_x += offset.at(0);
	cell_y += offset.at(1);
	if (isInMap(cell_x, cell_y)) {
		return _grids.at(cell_x + cell_y*mWorldWidth);
	}
	return nullptr;
}

Grid* Graph::get(float x, float y, game::Align align)
{
	return get((int)(x / mCellWidth), (int)(y / mCellHeight), align);
}

bool Graph::isInMap(float x, float y)
{
	return isInMap((int)(x / mCellWidth), (int)(y / mCellHeight));
}

bool Graph::isInMap(int cell_x, int cell_y)
{
	return cell_x >= 0 && cell_x < mWorldWidth && cell_y >= 0 && cell_y < mWorldHeight;
}

int Graph::getCellWidth()
{
	return mCellWidth;
}

int Graph::getCellHeight()
{
	return mCellHeight;
}

int Graph::getWorldWidth()
{
	return mWorldWidth;
}

int Graph::getWorldHeight()
{
	return mWorldHeight;
}

void Graph::setDefaultValue(float value)
{
	this->mDefaultValue = value;
}

void Graph::setWorldWidth(int world_width)
{
	this->mWorldWidth = world_width;
}

void Graph::setWorldHeight(int world_height)
{
	this->mWorldHeight = world_height;
}

void Graph::setCellWidth(int cell_width)
{
	this->mCellWidth = cell_width;
}

void Graph::setCellHeight(int cell_height)
{
	this->mCellHeight = cell_height;
}

void Graph::setName(std::string name)
{
	mName = name;
}

std::string Graph::getName()
{
	return mName;
}

int Graph::getIndex(int cell_x, int cell_y)
{
	return cell_x + cell_y + mWorldWidth;
}

Graph::~Graph() {
	while (getReferenceCount() > 0) release();
}

void Graph::debug(cocos2d::DrawNode * drawnode)
{
	drawnode->clear();
	float worldWidth = mWorldWidth*mCellWidth;
	float worldHeight = mWorldHeight*mCellHeight;

	for (int i = 0; i <= mWorldWidth; i++) {
		drawnode->drawLine(cocos2d::Vec2(i*mCellWidth, 0), cocos2d::Vec2(i*mCellWidth, worldHeight), cocos2d::Color4F::GRAY);
	}
	for (int i = 0; i <= mWorldHeight; i++) {
		drawnode->drawLine(cocos2d::Vec2(0, i*mCellHeight), cocos2d::Vec2(worldWidth, i*mCellHeight), cocos2d::Color4F::GRAY);
	}
	cocos2d::Size size(mCellWidth, mCellHeight);
	for (auto grid : _grids) {
		if (grid->getValue() != mDefaultValue) {
			auto color = cocos2d::Color4F::BLACK;
			drawnode->drawSolidRect(cocos2d::Vec2(grid->getX()*mCellWidth, grid->getY()*mCellHeight), cocos2d::Vec2((grid->getX() + 1)*mCellWidth, (grid->getY() + 1)*mCellHeight), color);
		}
	}
}

void Graph::console()
{
	CCLOG("<graph  name=\"%s\" cell_width=\"%d\" cell_height=\"%d\" width=\"%d\" height=\"%d\" default_value=\"%f\">", getName().c_str(), mCellWidth, mCellHeight, mWorldWidth, mWorldHeight, mDefaultValue);
	for (int j = 0; j < mWorldHeight; j++) {
		for (int i = 0; i < mWorldWidth; i++) {
			auto grid = get(i, j);
			if (grid->getValue() != mDefaultValue)	CCLOG("		<cell x=\"%d\" y=\"%d\" value=\"%d\" type=\"%d\"></cell>", i, j, (int)grid->getValue(), grid->getType() == Grid::Type::STATIC ? 1 : 0);
		}
	}
	CCLOG("</graph>");
}

void Graph::removeDynamicEntities()
{
	for (auto grid : _grids) {
		if (grid->hasEntities()) grid->removeAllEntities();
	}
}

void Graph::addDynamicEntity(cocos2d::Vec2 position, int id, bool fillneighbor)
{
	int cx = position.x / getCellWidth();
	int cy = position.y / getCellHeight();
	addDynamicEntity(cx, cy, id, fillneighbor);
}

void Graph::addDynamicEntity(int cx, int cy, int id, bool fillneighbor)
{
	if (isInMap(cx, cy)) {
		get(cx, cy)->addEntity(id);
		if (fillneighbor) {
			addDynamicEntity(cx - 1, cy, id, false);
			addDynamicEntity(cx - 1, cy + 1, id, false);
			addDynamicEntity(cx, cy + 1, id, false);
			addDynamicEntity(cx + 1, cy + 1, id, false);
			addDynamicEntity(cx + 1, cy, id, false);
			addDynamicEntity(cx + 1, cy - 1, id, false);
			addDynamicEntity(cx, cy - 1, id, false);
		}
	}
}

void Graph::fillRange(cocos2d::Vec2 position, float rw, float rh, int value)
{
	int minx = (position.x - rw) / getCellWidth();
	int miny = (position.y - rh) / getCellHeight();
	int maxx = (position.x + rw) / getCellWidth();
	int maxy = (position.y + rh) / getCellHeight();

	for (int j = miny; j <= maxy; j++) {
		for (int i = minx; i <= maxx; i++) {
			auto grid = get(i, j);
			if (grid) {
				grid->setValue(value);
			}
		}
	}
}
