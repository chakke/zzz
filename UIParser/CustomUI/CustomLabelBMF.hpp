
#ifndef CustomLabelBMF_hpp
#define CustomLabelBMF_hpp

#include "ui/UIImageView.h"
#include "CustomUIData.h"
#include "CustomUIInterface.hpp"

class CustomLabelBMF : public cocos2d::Label, public CustomUIData, public CustomUIInterface
{
public:
	static CustomLabelBMF* create(const std::string& bmfontPath, const std::string& text,
		const cocos2d::TextHAlignment& hAlignment = cocos2d::TextHAlignment::CENTER, const cocos2d::TextVAlignment& vAlignment = cocos2d::TextVAlignment::CENTER, int maxLineWidth = 0,
		const cocos2d::Vec2& imageOffset = cocos2d::Vec2::ZERO);
	CREATE_FUNC(CustomLabelBMF);
	virtual void attach_node(cocos2d::Node* node);
};

#endif /* CustomLabelBMF_hpp */
