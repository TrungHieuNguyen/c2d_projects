
#include "MainScene.hpp"
#include "ui/CocosGUI.h"
#include "../cocos/editor-support/cocostudio/CocoStudio.h"
#include "GameTiledMap.hpp"
#include "AbstractScene.hpp"
USING_NS_CC;

Scene* GameTiledMap::createScene()
{
    //return MainScene::create();
    auto scene = Scene::create();
    auto layer = GameTiledMap::create();
    scene->addChild(layer);
    return scene;
}

bool GameTiledMap::init()
{
    if ( !AbstractScene::init())
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    initComponents();
     AbstractScene::showHUD();
    return true;
}

void GameTiledMap::initComponents()
{
    layerBG = CSLoader::createNode(SCENE_GAME_TILEDMAP_CSB);
    addChild(layerBG, -1);

    lbTitle = (Text*) layerBG->getChildByName("lbTitle");
    lbTitle->setIgnoreAnchorPointForPosition(false);
    lbTitle->setAnchorPoint(Point(0.5, 0.5f));
    
    Button* btnPlay = (Button*) layerBG->getChildByName("btnPlay");
    btnPlay->setPressedActionEnabled(true);
    btnPlay->addClickEventListener([&](Ref* sender){

        Director::getInstance()->replaceScene(MainScene::createScene());
    });
    
  

    
}
void GameTiledMap::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
    
    
    
}
