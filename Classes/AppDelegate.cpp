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
        glview = GLViewImpl::createWithRect("DragonBonesCPP", Rect(0, 0, 1280, 720));
        director->setOpenGLView(glview);
    }

    director->getOpenGLView()->setDesignResolutionSize(1280, 720, ResolutionPolicy::SHOW_ALL);
    director->setDisplayStats(true);
    director->setAnimationInterval(1.f / 60.f);

    FileUtils::getInstance()->addSearchPath(".");
    FileUtils::getInstance()->addSearchPath("res");
    FileUtils::getInstance()->addSearchPath("fonts");
    auto scene = GameScene::createScene();

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
