//
//  Functions.cpp
//  TestApp
//
//  Created by Manh Tran on 12/9/15.
//
//

#include "Functions.hpp"
#include "ui/UIWidget.h"
#include <regex>

namespace app_function
{
    void destroyTree(cocos2d::Node* tree)
    {
        if ( ! tree)
        {
            return;
        }	
        tree->stopAllActions();
		tree->unscheduleAllCallbacks();
		tree->removeAllChildrenWithCleanup(true);
    }
    
    bool checkHit(cocos2d::Scene* scene, cocos2d::Node* node, const cocos2d::Vec2& location)
    {
        auto widget = dynamic_cast<cocos2d::ui::Widget*>(node);
        if (widget && widget->isTouchEnabled())
        {
            for (int i = 0; i < scene->getCameras().size(); i++)
            {
                cocos2d::Camera* camera = scene->getCameras().at(i);
                if ((unsigned short)camera->getCameraFlag() == widget->getCameraMask())
                {
                    bool test = widget->hitTest(location, camera, nullptr);
                    
                    if(test) return true;
                }
            }
        }
        
        for(ssize_t i = 0; i < node->getChildrenCount(); i++)
        {
            bool test = checkHit(scene, node->getChildren().at(i), location);
            if (test) return true;
        }
        
        return false;
    }
    
    bool is_email_valid(const std::string& email)
    {
        bool valid = std::regex_match(email, std::regex("\^[a-zA-Z0-9][a-zA-Z0-9\_.]+@[a-zA-Z0-9_]+.[a-zA-Z0-9_.]+\$") );
        
        return valid;
    }
    
    void split(const std::string& input, const char& pivot, std::vector<std::string>& result)
    {
        std::stringstream stream(input);
        std::string item;
        while (std::getline(stream, item, pivot))
        {
            if( ! item.empty()) result.push_back(item);
        }
    }
    
    std::string & ltrim(std::string & str)
    {
        auto it2 =  std::find_if( str.begin() , str.end() , [](char ch){ return !std::isspace<char>(ch , std::locale::classic() ) ; } );
        str.erase( str.begin() , it2);
        return str;
    }
    
    std::string & rtrim(std::string & str)
    {
        auto it1 =  std::find_if( str.rbegin() , str.rend() , [](char ch){ return !std::isspace<char>(ch , std::locale::classic() ) ; } );
        str.erase( it1.base() , str.end() );
        return str;   
    }
    
    std::string & trim(std::string & str)
    {
        return ltrim(rtrim(str));
    }
	int count(std::vector<int> datas, int value) {
		int count = 0;
		for (auto v : datas) {
			if (v == value) count++;
		}
		return count;
	}
	int random(int start, int end) {
		return start + (rand() % (int)(end - start + 1));		
	}
	float clamp(float value, float min, float max) {
		if (value < min) return min;
		if (value > max) return max;
		return value;
	}
	int clampInt(int value, int min, int max) {
		if (value < min) return min;
		if (value > max) return max;
		return value;
	}
}