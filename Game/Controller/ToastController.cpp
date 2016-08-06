
#include "ToastController.hpp"
#include "../../UIParser/UIParser.hpp"
#include "../../UIParser/CustomUI/CustomUIData.h"
#include "../../UIParser/CustomUI/CustomUIRichText.h"
#include "../../UIParser/CustomUI/CustomUILayout.hpp"

USING_NS_CC;

static ToastController* _instance = nullptr;

ToastController* ToastController::getInstance()
{
    if (!_instance)
    {
        _instance = new ToastController();
        _instance->init();
    }
    return _instance;
}

bool ToastController::init()
{
	Controller::init();

	{
		auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
		mLayout = cocos2d::ui::Layout::create();
		mLayout->setAnchorPoint(cocos2d::Vec2(.5f,.5f));
		mLayout->setPosition(cocos2d::Vec2(visibleSize.width/2,100));
		mLayout->setLayoutType(cocos2d::ui::Layout::Type::RELATIVE);
		mLayout->setBackGroundImage("texture/border_white_32x32.png");
		mLayout->setBackGroundImageScale9Enabled(true);
		mLayout->setBackGroundImageCapInsets(cocos2d::Rect(10,10,12,12));
		mLayout->setBackGroundImageColor(cocos2d::Color3B::BLACK);
		mLayout->setBackGroundImageOpacity(200);

		mText = cocos2d::ui::Text::create("This is toast","fonts/SF-UI-Text-Light.otf",30);
		mText->setTextHorizontalAlignment(cocos2d::TextHAlignment::CENTER);
		mText->setTextVerticalAlignment(cocos2d::TextVAlignment::CENTER);

		auto center = cocos2d::ui::RelativeLayoutParameter::create();
		center->setAlign(cocos2d::ui::RelativeLayoutParameter::RelativeAlign::CENTER_IN_PARENT);
		mText->setLayoutParameter(center);
		mLayout->addChild(mText);
		


		auto size = mText->getTextAreaSize();
		mLayout->setContentSize(cocos2d::Size(size.width + 40, size.height + 20));
		setView(mLayout);

		mLayout->setCascadeOpacityEnabled(true);
		mLayout->setOpacity(0);
		mLayout->setVisible(false);
	}


  //  auto node = UIParser::parse("xml/toast.xml");
  //  setView(node);
  //  node->setLocalZOrder(9999);
    
    return true;
}

void ToastController::toast(const std::string& text, const float& time)
{

	mText->setString(text);	
	auto size = mText->getContentSize();
	mLayout->setContentSize(cocos2d::Size(size.width + 40, size.height + 20));

	_view->stopAllActions();
	_view->setCascadeOpacityEnabled(true);
	_view->setVisible(true);

	_view->runAction(cocos2d::Sequence::create(cocos2d::FadeIn::create(.2f),cocos2d::DelayTime::create(time), cocos2d::FadeOut::create(.2f), cocos2d::CallFunc::create([=]() {
		_view->setVisible(false);
	}), nullptr));



    /*auto parser = dynamic_cast<UIParser*>(dynamic_cast<CustomUIData*>(_view)->getCustomUIData().at(0));
    auto container = dynamic_cast<CustomUILayout*>(parser->getHasNodes()->at("container"));
    auto content = dynamic_cast<CustomRichText*>(parser->getHasNodes()->at("content"));
    
    _view->stopAllActions();
    container->stopAllActions();
    content->stopAllActions();
    
    content->getRichElement<CustomRichElementText*>(0)->_text = text;
    content->updateText();
    
    container->setOpacity(0);
    content->setOpacity(0);
    
    _view->setVisible(true);
    container->runAction(Sequence::create(FadeTo::create(0.25, atof(container->getCustomAttribute("target_opacity")->c_str())), DelayTime::create(time), FadeOut::create(0.25), NULL));
    content->runAction(Sequence::create(FadeIn::create(0.25),DelayTime::create(time), FadeOut::create(0.25), NULL));
    _view->runAction(Sequence::create(DelayTime::create(time + 0.6), Hide::create(), NULL));
    
    UIParser::refreshAllViewConstraint(2);*/
}
