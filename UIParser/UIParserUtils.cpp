//
//  UIParserUtils.cpp
//  Busino
//
//  Created by Manh Tran on 1/16/16.
//
//

#include "UIParserUtils.hpp"

USING_NS_CC;

namespace ui_parser_utils
{

    bool isNumber(const std::string& s)
    {
        if (s.empty())
        {
            return false;
        }
        for (int i = 0; i < s.length(); i++)
        {
            if (i == 0 && s[i] == '-')
            {
                continue;
            }
            if (!isdigit(s[i]) && s[i] != '.')
            {
                return false;
            }
        }
        
        return true;
    }
    
    Color3B convertColor(const std::string& s)
    {
        if (s.find("#") != -1) {
            int index = s.find("#");
            std::string colorHex = std::string(s, index + 1, s.length() - (index+1));
            if (colorHex.size() >= 6) {
                char* pEnd;
                int r = strtol(std::string(colorHex,0,2).c_str(), &pEnd, 16);
                int g = strtol(std::string(colorHex,2,2).c_str(), &pEnd, 16);
                int b = strtol(std::string(colorHex,4,2).c_str(), &pEnd, 16);
                return Color3B(r,g,b);
            }
        }
        else if (s.compare("black") == 0 || s.compare("BLACK") == 0) {
            return Color3B::BLACK;
        }
        else if (s.compare("blue") == 0 || s.compare("BLUE") == 0) {
            return Color3B::BLUE;
        }
        else if (s.compare("white") == 0 || s.compare("WHITE") == 0) {
            return Color3B::WHITE;
        }
        else if (s.compare("yellow") == 0 || s.compare("YELLOW") == 0) {
            return Color3B::YELLOW;
        }
        else if (s.compare("red") == 0 || s.compare("RED") == 0) {
            return Color3B::RED;
        }
        else if (s.compare("green") == 0 || s.compare("GREEN") == 0) {
            return Color3B::GREEN;
        }
        else if (s.compare("magenta") == 0 || s.compare("MAGENTA") == 0) {
            return Color3B::MAGENTA;
        }
        else if (s.compare("orange") == 0 || s.compare("ORANGE") == 0) {
            return Color3B::ORANGE;
        }
        else if (s.compare("gray") == 0 || s.compare("GRAY") == 0) {
            return Color3B::GRAY;
        }
        
        return Color3B::BLACK;
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

};