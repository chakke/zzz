#include "UIParser_LabelBMF_Delegate.hpp"
#include "CustomUI/CustomLabelBMF.hpp"
#include "UIParserUtils.hpp"
USING_NS_CC;

cocos2d::Node* UIParserLabelBMFDelegate::createNode(const pugi::xml_node& node)
{
	std::string str = "text";
	std::string bmf = "fonts/font-ingame.fnt";
	cocos2d::TextHAlignment hAlign = cocos2d::TextHAlignment::CENTER;
	cocos2d::TextVAlignment vAlign = cocos2d::TextVAlignment::CENTER;
	float maxLineWidth = 0;
	for (auto it = node.attributes_begin(); it != node.attributes_end(); it++)
	{
		if (strcmp(it->name(), "font") == 0)
		{
			bmf = it->value();
		}
		else if (strcmp(it->name(), "value") == 0)
		{
			str = it->value();
		}
		else if (strcmp(it->name(), "text-align") == 0)
		{
			if (strcmp(it->value(), "center") == 0) {
				hAlign = cocos2d::TextHAlignment::CENTER;
				vAlign = cocos2d::TextVAlignment::CENTER;
			}
			else if (strcmp(it->value(), "left") == 0) {
				hAlign = cocos2d::TextHAlignment::LEFT;
				vAlign = cocos2d::TextVAlignment::CENTER;
			}	
			else if (strcmp(it->value(), "right") == 0) {
				hAlign = cocos2d::TextHAlignment::RIGHT;
				vAlign = cocos2d::TextVAlignment::CENTER;
			}
			else if (strcmp(it->value(), "top") == 0) {
				hAlign = cocos2d::TextHAlignment::CENTER;
				vAlign = cocos2d::TextVAlignment::TOP;
			}
			else if (strcmp(it->value(), "bottom") == 0) {
				hAlign = cocos2d::TextHAlignment::CENTER;
				vAlign = cocos2d::TextVAlignment::BOTTOM;
			}
			else if (strcmp(it->value(), "top-left") == 0) {
				hAlign = cocos2d::TextHAlignment::LEFT;
				vAlign = cocos2d::TextVAlignment::TOP;
			}
			else if (strcmp(it->value(), "top-right") == 0) {
				hAlign = cocos2d::TextHAlignment::RIGHT;
				vAlign = cocos2d::TextVAlignment::TOP;
			}
			else if (strcmp(it->value(), "bottom-left") == 0) {
				hAlign = cocos2d::TextHAlignment::LEFT;
				vAlign = cocos2d::TextVAlignment::BOTTOM;
			}
			else if (strcmp(it->value(), "bottom-right") == 0) {
				hAlign = cocos2d::TextHAlignment::RIGHT;
				vAlign = cocos2d::TextVAlignment::BOTTOM;
			}
		}
		else if (strcmp(it->name(), "max-line-width") == 0)
		{
			maxLineWidth = atof(it->value());
		}
	}
	auto ret = CustomLabelBMF::create(bmf.c_str(), str.c_str(), hAlign,vAlign, maxLineWidth);
	return ret;
}

void UIParserLabelBMFDelegate::constraintWithParent(const pugi::xml_node& node, const pugi::xml_node& prev_node, cocos2d::Node* parent, cocos2d::Node* recent)
{

}