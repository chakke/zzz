#include "AppDelegate.h"
#include "Data/AppConfiguration.hpp"
#include "Game/GameModel/Cache.hpp"
#include "UIParser/UIParser.hpp"
#include "Game/Controller/RootViewController.hpp"
#include "Game/Controller/ToastController.hpp"
USING_NS_CC;

static cocos2d::Size designResolutionSize = cocos2d::Size(480, 320);
static cocos2d::Size smallResolutionSize = cocos2d::Size(480, 320);
static cocos2d::Size mediumResolutionSize = cocos2d::Size(1024, 768);
static cocos2d::Size largeResolutionSize = cocos2d::Size(2048, 1536);

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

void AppDelegate::initGLContextAttrs()
{

    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};
    GLView::setGLContextAttrs(glContextAttrs);
}

static int register_all_packages()
{
    return 0;
}

bool AppDelegate::applicationDidFinishLaunching() {    
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
	if (!glview) {
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32) || (CC_TARGET_PLATFORM == CC_PLATFORM_MAC) || (CC_TARGET_PLATFORM == CC_PLATFORM_LINUX)
		glview = GLViewImpl::createWithRect("ArcadeDotaGame", Rect(0, 0, designResolutionSize.width, designResolutionSize.height));
#else
		glview = GLViewImpl::create("ArcadeDotaGame");
#endif
		director->setOpenGLView(glview);
		float scale = 0.4f;
		glview->setFrameSize(2208 * scale, 1242 * scale);
	}
	director->setAnimationInterval(1.0 / 60);
	director->setDisplayStats(true);
	glview->setDesignResolutionSize(1280, 800, ResolutionPolicy::FIXED_WIDTH);

	FileUtils::getInstance()->addSearchPath("res/");
	FileUtils::getInstance()->addSearchPath("layout-HD/");
	FileUtils::getInstance()->addSearchPath("res-HD/");
	
	app_configuration::setup();
	game_model::load_user_cache();


	/*auto scene = HelloWorld::createScene();
	director->runWithScene(scene);*/

	
	auto scene = Scene::create();
	auto controller = RootViewController::create();

	scene->addChild(controller->getView());
	controller->getView()->setPosition(scene->getContentSize() / 2);
	controller->onLinked();
	controller->retain();
	

	{
		auto toastController = ToastController::getInstance();
		scene->addChild(toastController->getView());
		toastController->getView()->setPosition(scene->getContentSize() / 2);
		toastController->onLinked();
		toastController->retain();
	}

	UIParser::refreshAllViewConstraint(2); 										   
	director->runWithScene(scene);
    register_all_packages();

    return true;
}

void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();
}

void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();
}
