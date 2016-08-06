//
//  Functions.hpp
//  TestApp
//
//  Created by Manh Tran on 12/9/15.
//
//

#ifndef Functions_hpp
#define Functions_hpp

#include "cocos2d.h"

namespace app_function
{
    void destroyTree(cocos2d::Node* tree);
    
    bool checkHit(cocos2d::Scene* scene, cocos2d::Node* node, const cocos2d::Vec2& location);
    
    bool is_email_valid(const std::string& email);
  
    void split(const std::string& input, const char& pivot, std::vector<std::string>& result);
    
    std::string & ltrim(std::string & str);
    std::string & rtrim(std::string & str);
    std::string & trim(std::string & str);

	int count(std::vector<int> datas, int value);
	float clamp(float value,float min,float max);
	int clampInt(int value, int min, int max);
	int random(int start,int end);
};

#endif /* Functions_hpp */
