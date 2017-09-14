#include "AppDelegate.h"
#include "DragonBonesTest/CoreElement.h"
#include "MiniGame/MainScene.hpp"
#include "MiniGame/GameScene.hpp"


USING_NS_CC;

AppDelegate::AppDelegate() 
{
}

AppDelegate::~AppDelegate() 
{
}

void AppDelegate::initGLContextAttrs()
{
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching() {
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
               glview = GLViewImpl::create("Game Sample");
#if  (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
		//glview->setFrameSize(m_SceenSize.x *FRAME_SCALE_FACTOR, m_SceenSize.y * FRAME_SCALE_FACTOR);
		glview->setFrameSize(1280, 720);
#else
		glview->setFrameSize(1280, 720);
#endif
		
        director->setOpenGLView(glview);
    }

    director->getOpenGLView()->setDesignResolutionSize(1280, 720, ResolutionPolicy::SHOW_ALL);
    director->setDisplayStats(true);
    director->setAnimationInterval(1.f / 60.f);

    FileUtils::getInstance()->addSearchPath(".");
    FileUtils::getInstance()->addSearchPath("res");
    FileUtils::getInstance()->addSearchPath("fonts");
    //auto scene = GameScene::createScene();
    auto scene = MainScene::createScene();
    director->runWithScene(scene);
    return true;
}


void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
