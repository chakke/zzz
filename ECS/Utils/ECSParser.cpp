#include "ECSParser.hpp"
#include "../../ECS/Component/Components.hpp"
#include "../../ECSImplements/Component/IComponents.hpp"
#include "../../UIParser/UIParser.hpp"
#include "../../Core/Animations/SpineAnimation.hpp"
#include "../../Core/Animations/SpriteAnimation.hpp"
namespace ComponentParser {
	artemis::Component* parsePosition(const pugi::xml_node &xmlnode) {
		float x = 0;
		float y = 0;
		for (pugi::xml_attribute attr : xmlnode.attributes())
		{
			if (strcmp(attr.name(), "x") == 0) {
				x = atof(attr.value());
			}
			else if (strcmp(attr.name(), "y") == 0) {
				y = atof(attr.value());
			}
		}
		return new PositionComponent(x, y);
	}
	
	artemis::Component* parseVelocity(const pugi::xml_node &xmlnode) {
		auto velocity = new VelocityComponent(0, 0);
		for (pugi::xml_attribute attr : xmlnode.attributes())
		{
			if (strcmp(attr.name(), "x") == 0) {
				velocity->getVelocity()->setX(atof(attr.value()));
			}
			else if (strcmp(attr.name(), "y") == 0) {
				velocity->getVelocity()->setY(atof(attr.value()));
			}
			else if (strcmp(attr.name(), "max_velocity") == 0) {
				velocity->setMaxVelocity(atof(attr.value()));
			}
			else if (strcmp(attr.name(), "max_force") == 0) {
				velocity->setMaxForce(atof(attr.value()));
			}
		}
		return velocity;
	}
	
	artemis::Component* parseRender(const pugi::xml_node &xmlnode) {
		auto renderComponent = new RenderComponent();
		for (pugi::xml_attribute attr : xmlnode.attributes())
		{
			if (strcmp(attr.name(), "delay_time") == 0) {
				renderComponent->setDelayTime(atof(attr.value()));
			}
			else if (strcmp(attr.name(), "style") == 0) {
				auto renderNode = UIParser::parse(attr.value());
				CC_SAFE_RETAIN(renderNode);
				renderComponent->setView(renderNode);
			}
			else if (strcmp(attr.name(), "scale") == 0) {
				renderComponent->getView()->setScale(atof(attr.value()));
			}
		}
		renderComponent->getView()->setPosition(0, 0);
		return renderComponent;
	}
	
	artemis::Component* parseRenderSortable(const pugi::xml_node &xmlnode) {
		auto sortableComponent = new RenderSortableComponent();		
		return sortableComponent;
	}
	
	artemis::Component* parseState(const pugi::xml_node &xmlnode) {
		auto stateComponent = new StateComponent();
		for (pugi::xml_attribute attr : xmlnode.attributes())
		{
			if (strcmp(attr.name(), "state") == 0) {
				stateComponent->setState(atoi(attr.value()));
			}			
		}
		return stateComponent;
	}
	
	artemis::Component* parseEntityType(const pugi::xml_node &xmlnode) {
		auto typeComponent = new TypeComponent();
		for (pugi::xml_attribute attr : xmlnode.attributes())
		{
			if (strcmp(attr.name(), "type") == 0) {
				typeComponent->setEntityType(atoi(attr.value()));
			}
		}

		for (pugi::xml_node type : xmlnode.children("type")) {
			int key = -1;
			int value = -1;
			bool add = false;
			for (pugi::xml_attribute attr : type.attributes()) {				
				if (strcmp(attr.name(), "name") == 0) {
					key = atoi(attr.value());
					add = true;
				}else if(strcmp(attr.name(), "value") == 0) {
					value = atoi(attr.value());
					add = true;
				}				
			}			
			if(add)typeComponent->setType(key, value);
		}
		return typeComponent;
	}
	
	artemis::Component* parsePlaySide(const pugi::xml_node &xmlnode) {
		auto playSideComponent = new PlaySideComponent();
		for (pugi::xml_attribute attr : xmlnode.attributes())
		{
			if (strcmp(attr.name(), "side") == 0) {
				playSideComponent->setSide(atoi(attr.value()));
			}else if (strcmp(attr.name(), "index") == 0) {
				playSideComponent->setSideIndex(atoi(attr.value()));
			}
		}
		return playSideComponent;
	}
	
	artemis::Component* parseAnimation(const pugi::xml_node &xmlnode) {
		int typeAnimation = 1;
		int animationName = -1;
		//auto parseAnimation = new Animation();
		for (pugi::xml_attribute attr : xmlnode.attributes())
		{
			if (strcmp(attr.name(), "type") == 0) {
				typeAnimation = atoi(attr.value());
			}
			else if (strcmp(attr.name(), "animation") == 0) {
				animationName = atoi(attr.value());
			}
		}		
		AnimationComponent* animationComponent = new AnimationComponent((typeAnimation == 0) ? (EntityAnimation*)(new SpriteAnimation()) : (EntityAnimation*)(new SpineAnimation()));
		if(animationName != -1) animationComponent->animate(animationName);
		return animationComponent;
	}

	artemis::Component* parsePathFollow(const pugi::xml_node &xmlnode) {		
		return new PathFollowComponent();
	}

	artemis::Component* parseScope(const pugi::xml_node &xmlnode) {
		auto scopeComponent = new ScopeComponent();

		for (pugi::xml_node type : xmlnode.children("type")) {
			int key = -1;
			float value = -1;
			bool add = false;
			for (pugi::xml_attribute attr : type.attributes()) {
				if (strcmp(attr.name(), "name") == 0) {
					key = atoi(attr.value());
					add = true;
				}
				else if (strcmp(attr.name(), "value") == 0) {
					value = atof(attr.value());
					add = true;
				}
			}
			if (add)scopeComponent->setScope(key, value);
		}
		return scopeComponent;
	}

	artemis::Component* parseAttack(const pugi::xml_node &xmlnode) {
		auto attackComponent = new AttackComponent();

		for (pugi::xml_attribute attr : xmlnode.attributes())
		{
			if (strcmp(attr.name(), "damage") == 0) {
				attackComponent->setDamage(atof(attr.value()));
			}
			else if (strcmp(attr.name(), "time_per_attack") == 0) {
				attackComponent->setTimePerAttack(atof(attr.value()));				
			}
		}
		return attackComponent;
	}
	
	artemis::Component* parseHealth(const pugi::xml_node &xmlnode) {
		auto c = new HealthComponent();

		for (pugi::xml_attribute attr : xmlnode.attributes())
		{
			if (strcmp(attr.name(), "health") == 0) {
				c->setHealth(atof(attr.value()),true);
			}			
		}
		return c;
	}

	artemis::Component* parseAction(const pugi::xml_node &xmlnode) {
		auto c = new ActionComponent();
		for (pugi::xml_attribute attr : xmlnode.attributes())
		{

		}
		return c;
	}
	
	artemis::Component* parseTarget(const pugi::xml_node &xmlnode) {
		auto c = new TargetComponent();
		for (pugi::xml_attribute attr : xmlnode.attributes())
		{
			if (strcmp(attr.name(), "id") == 0) {
				c->setTargetID(atoi(attr.value()));
			}
			else if (strcmp(attr.name(), "group") == 0) {
				c->setGroup(attr.value());
			}
		}
		return c;
	}
	std::unordered_map<std::string, std::function<artemis::Component*(const pugi::xml_node&)>> _delegates;
	void setupDelegates() {
		_delegates.clear();
		_delegates.insert(std::make_pair("position_component", parsePosition));
		_delegates.insert(std::make_pair("velocity_component", parseVelocity));
		_delegates.insert(std::make_pair("render_component", parseRender));
		_delegates.insert(std::make_pair("rendersortable_component", parseRenderSortable));
		_delegates.insert(std::make_pair("state_component", parseState));
		_delegates.insert(std::make_pair("type_component", parseEntityType));
		_delegates.insert(std::make_pair("playside_component", parsePlaySide));
		_delegates.insert(std::make_pair("animation_component", parseAnimation));
		_delegates.insert(std::make_pair("pathfollow_component", parsePathFollow));
		_delegates.insert(std::make_pair("scope_component", parseScope));
		_delegates.insert(std::make_pair("attack_component", parseAttack));
		_delegates.insert(std::make_pair("health_component", parseHealth));
		_delegates.insert(std::make_pair("action_component", parseAction));
		_delegates.insert(std::make_pair("target_component", parseTarget));
	}

	artemis::Component * parseXmlnode(const pugi::xml_node & xmlnode)
	{
		if (_delegates.find(xmlnode.name()) != _delegates.end()) {
			return _delegates.at(xmlnode.name())(xmlnode);
		}
		return nullptr;
	}
};


namespace EntityParser {
	artemis::Entity * parseXmlnode(artemis::World * world, const pugi::xml_node & xmlnode)
	{

		artemis::Entity* e = &world->getEntityManager()->create();

		for (pugi::xml_attribute attr : xmlnode.attributes())
		{
			if (strcmp(attr.name(), "style") == 0) {
				e = EntityParser::parseFromFile(world, attr.value());
			}
			else if (strcmp(attr.name(), "tag") == 0) {
				e->setTag(attr.value());
			}
			else if (strcmp(attr.name(), "group") == 0) {
				e->setGroup(attr.value());
			}
		}

		for (pugi::xml_node node = xmlnode.first_child(); node; node = node.next_sibling()) {
			auto c = ComponentParser::parseXmlnode(node);
			if (c) {
				e->addComponent(c);
			}
			else {
				CCLOG("Cannot parse component : %s", node.name());
			}
		}
		e->refresh();
		return e;
	}

	artemis::Entity * parseFromFile(artemis::World * world, const std::string & file)
	{
		pugi::xml_document* doc = new pugi::xml_document();
		doc->load_string(cocos2d::FileUtils::getInstance()->getStringFromFile(file).c_str());
		return  EntityParser::parseXmlnode(world, doc->first_child());
	}
};



ECSParser * _ecs_instance = nullptr;
ECSParser * ECSParser::getInstance()
{
	if (!_ecs_instance) _ecs_instance = new ECSParser();
	return _ecs_instance;
}


ECSParser::ECSParser() {
	ComponentParser::setupDelegates();
}


std::unordered_map<std::string, pugi::xml_document*> _caches_doc_ecs;
void ECSParser::parse(artemis::World * world, const std::string & filename)
{
	pugi::xml_document* doc = nullptr;

	if (_caches_doc_ecs.find(filename) == _caches_doc_ecs.end()) {
		_caches_doc_ecs.insert(std::make_pair(filename, new pugi::xml_document()));
		doc = _caches_doc_ecs[filename];

		std::string fullPath = cocos2d::FileUtils::getInstance()->fullPathForFilename(filename).c_str();
		doc->load_string(cocos2d::FileUtils::getInstance()->getStringFromFile(filename).c_str());
	}
	else doc = _caches_doc_ecs[filename];
	auto entities = doc->child("entities");
	for (pugi::xml_node node = entities.first_child(); node; node = node.next_sibling()) {
		EntityParser::parseXmlnode(world, node);
	}
}

artemis::Entity * ECSParser::parseEntity(artemis::World * world, const std::string & filename)
{
	pugi::xml_document* doc = nullptr;

	if (_caches_doc_ecs.find(filename) == _caches_doc_ecs.end()) {
		_caches_doc_ecs.insert(std::make_pair(filename, new pugi::xml_document()));
		doc = _caches_doc_ecs[filename];

		std::string fullPath = cocos2d::FileUtils::getInstance()->fullPathForFilename(filename).c_str();
		doc->load_string(cocos2d::FileUtils::getInstance()->getStringFromFile(filename).c_str());
	}
	else doc = _caches_doc_ecs[filename];

	return EntityParser::parseXmlnode(world, doc->first_child());
}


