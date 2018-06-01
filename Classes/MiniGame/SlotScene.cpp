
#include "MainScene.hpp"
#include "ui/CocosGUI.h"
#include "../cocos/editor-support/cocostudio/CocoStudio.h"
#include "SlotScene.hpp"

USING_NS_CC;

Scene* SlotScene::createScene()
{
    auto scene = Scene::create();
    auto layer = SlotScene::create();
    scene->addChild(layer);
    return scene;
}

bool SlotScene::init()
{
    if ( !AbstractScene::init() )
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    initComponents();

    
    return true;
}

void SlotScene::initComponents()
{
    layerBG = CSLoader::createNode(SCENE_SLOT_CSB);
    addChild(layerBG, -1);

//    lbTitle = (Text*) layerBG->getChildByName("lbTitle");
//    lbTitle->setIgnoreAnchorPointForPosition(false);
//    lbTitle->setAnchorPoint(Point(0.5, 0.5f));
//    
//    Button* btnPlay = (Button*) layerBG->getChildByName("btnPlay");
//    btnPlay->setPressedActionEnabled(true);
//    btnPlay->addClickEventListener([&](Ref* sender){
//        Director::getInstance()->replaceScene(SlotScene::createScene());
//    });
    AbstractScene::showHUD();
    
    auto LayerCard01 = layerBG->getChildByName("panel01");
    auto card01 = LayerCard01->getChildByName("item01");
    auto card02 = LayerCard01->getChildByName("item02");
    auto card03 = LayerCard01->getChildByName("item03");
}
void SlotScene::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
    
}
