//
//  ObserverPattern.cpp
//  HoverUp
//
//  Created by Manh Tran on 3/11/15.
//
//

#include "ObserverPattern.h"

Observer::~Observer()
{
    _obs.clear();
    _strongList.clear();
}

void Observer::addDestination(Observable * ob, bool strong)
{
    for (Observable* o : _obs)
    {
        if (ob == o)
        {
            return;
        }
    }
    
    _obs.push_back(ob);

    auto ref = dynamic_cast<cocos2d::Ref*>(ob);
    if (ref && strong)
    {
        _strongList.pushBack(ref);
    }
}

void Observer::removeDestination(Observable* ob)
{
    tryRemoveStrong(ob);
    
    for (int i = 0; i < _obs.size(); i++)
    {
        if (_obs[i] == ob)
        {
            _obs.erase(_obs.begin() + i);
            return;
        }
    }
}

void Observer::tryRemoveStrong(Observable* ob)
{
    auto ref = dynamic_cast<cocos2d::Ref*>(ob);
    if (ref)
    {
        _strongList.eraseObject(ref);
    }
}

void Observer::sendData(cocos2d::Ref * data, bool release)
{
    for (int i = 0; i < _obs.size(); i++)
    {
        auto ob = _obs[i];
        
        auto ref = dynamic_cast<cocos2d::Ref*>(ob);
        if (ref)
        {
            if ((ref->getReferenceCount() > 1 && _strongList.contains(ref)) || (ref->getReferenceCount() == 1 && !_strongList.contains(ref)))
            {
                ob->listen(this, data);
            }
        }
        else if(ob)
        {
            ob->listen(this, data);
        }
        
    }
    if(release) data->release();
}