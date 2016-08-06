
#include "CustomLabelBMF.hpp"


CustomLabelBMF * CustomLabelBMF::create(const std::string & bmfontPath, const std::string & text, const cocos2d::TextHAlignment & hAlignment, const cocos2d::TextVAlignment & vAlignment, int maxLineWidth, const cocos2d::Vec2 & imageOffset)
{
	auto label = CustomLabelBMF::create();
	label->setAlignment(hAlignment);
	if (!label->setBMFontFilePath(bmfontPath, imageOffset)) {
		CCLOG("Invalid font path : %s",bmfontPath);
		return nullptr;
	}
	label->setString(text);
	label->setMaxLineWidth(maxLineWidth);
	return label;
}

void CustomLabelBMF::attach_node(cocos2d::Node* node)
{
    addChild(node);
}