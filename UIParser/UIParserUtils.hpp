//
//  UIParserUtils.hpp
//  Busino
//
//  Created by Manh Tran on 1/16/16.
//
//

#ifndef UIParserUtils_hpp
#define UIParserUtils_hpp

#include "cocos2d.h"
#include "ui/UIImageView.h"

namespace ui_parser_utils
{
    cocos2d::Color3B convertColor(const std::string& s);
    
    bool isNumber(const std::string& s);
    
    void split(const std::string& input, const char& pivot, std::vector<std::string>& result);
};

#endif /* UIParserUtils_hpp */
