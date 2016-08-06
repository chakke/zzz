
#include "Controller.hpp"

static int __ID = 0;

Controller::Controller() : _view(nullptr), _userData(nullptr), _parent(nullptr)
{
    _id = __ID;
    __ID++;
}

Controller::~Controller()
{
    CC_SAFE_RELEASE_NULL(_view);
    CC_SAFE_RELEASE_NULL(_userData);
    CC_SAFE_RELEASE_NULL(_parent);

    while (_subController.size() > 0)
    {
        _subController.back()->onRemove();
        _subController.popBack();
    }
    unscheduleUpdate();
}

bool Controller::init()
{
    return true;
}

void Controller::scheduleUpdate()
{
    cocos2d::Director::getInstance()->getScheduler()->scheduleUpdate(this, 0, false);
}

void Controller::unscheduleUpdate()
{
    cocos2d::Director::getInstance()->getScheduler()->unscheduleUpdate(this);
}

void Controller::update(float delta)
{
    
}

void Controller::setView(cocos2d::Node* view)
{
    CC_SAFE_RELEASE_NULL(_view);
    _view = view;
    CC_SAFE_RETAIN(_view);
}

cocos2d::Node* Controller::getView()
{
    return _view;
}

void Controller::addSubController(Controller* controller)
{
    if(!_subController.contains(controller))
    {
        controller->onLinked();
        _subController.pushBack(controller);
        controller->_parent = this;
        CC_SAFE_RETAIN(controller->_parent);
    }
}

void Controller::removeSubController(Controller* controller, bool recursive)
{
    if(_subController.contains(controller))
    {
        if (recursive)
        {
            while (controller->_subController.size() > 0)
            {
                controller->removeSubController(controller->_subController.back(), recursive);
            }
        }
        
        controller->onRemove();
        CC_SAFE_RELEASE_NULL(controller->_parent);
        _subController.eraseObject(controller);
    }
}

void Controller::removeSelf(bool recursive)
{
    if (_parent)
    {
        _parent->removeSubController(this, recursive);
    }
}

void Controller::setUserData(cocos2d::Ref* data)
{
    CC_SAFE_RELEASE_NULL(_userData);
    _userData = data;
    CC_SAFE_RETAIN(_userData);
}

void Controller::listen(Observer* sender, cocos2d::Ref* ref)
{

}

void Controller::onLinked()
{
    
}

void Controller::onRemove()
{
    
}