
#include "MainScene.hpp"
#include "ui/CocosGUI.h"
#include "../cocos/editor-support/cocostudio/CocoStudio.h"
#include "GameScene.hpp"

USING_NS_CC;

Scene* MainScene::createScene()
{
    return MainScene::create();
}

bool MainScene::init()
{
    if ( !Scene::init() )
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
        initComponents();

    
    return true;
}

void MainScene::initComponents()
{
    layerBG = CSLoader::createNode("MainScene.csb");
    addChild(layerBG, -1);

    lbTitle = (Text*) layerBG->getChildByName("lbTitle");
    lbTitle->setIgnoreAnchorPointForPosition(false);
    lbTitle->setAnchorPoint(Point(0.5, 0.5f));
    
    Button* btnPlay = (Button*) layerBG->getChildByName("btnPlay");
    btnPlay->setPressedActionEnabled(true);
    btnPlay->addClickEventListener([&](Ref* sender){

        Director::getInstance()->replaceScene(GameScene::createScene());

        
    });
    
    Button* btn2D = (Button*) layerBG->getChildByName("btn2D");
    btn2D->setPressedActionEnabled(true);
    btn2D->addClickEventListener([&](Ref* sender){
        Director::getInstance()->replaceScene(GameScene::createScene());
    });
    
    Button* btnTiledMap = (Button*) layerBG->getChildByName("btnTiledMap");
    btnTiledMap->setPressedActionEnabled(true);
    btnTiledMap->addClickEventListener([&](Ref* sender){
        Director::getInstance()->replaceScene(GameScene::createScene());
    });
    
    Button* btn3D = (Button*) layerBG->getChildByName("btn3D");
    btn3D->setPressedActionEnabled(true);
    btn3D->addClickEventListener([&](Ref* sender){
        Director::getInstance()->replaceScene(GameScene::createScene());
    });
    
    Button* btnAbout = (Button*) layerBG->getChildByName("btnAbout");
    btnAbout->setPressedActionEnabled(true);
    btnAbout->addClickEventListener([&](Ref* sender){
        Director::getInstance()->replaceScene(GameScene::createScene());
    });

    
}
void MainScene::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
    
    
    
}
