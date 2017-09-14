
#include "MainScene.hpp"
#include "ui/CocosGUI.h"
#include "../cocos/editor-support/cocostudio/CocoStudio.h"
#include "Game3D.hpp"

USING_NS_CC;

Scene* Game3D::createScene()
{
    return Game3D::create();
}

bool Game3D::init()
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

void Game3D::initComponents()
{
    layerBG = CSLoader::createNode(SCENE_GAME3D_CSB);
    addChild(layerBG, -1);

    lbTitle = (Text*) layerBG->getChildByName("lbTitle");
    lbTitle->setIgnoreAnchorPointForPosition(false);
    lbTitle->setAnchorPoint(Point(0.5, 0.5f));
    
    Button* btnPlay = (Button*) layerBG->getChildByName("btnPlay");
    btnPlay->setPressedActionEnabled(true);
    btnPlay->addClickEventListener([&](Ref* sender){

        Director::getInstance()->replaceScene(MainScene::createScene());

        
    });
    
    Button* btn2D = (Button*) layerBG->getChildByName("btn2D");
    btn2D->setPressedActionEnabled(true);
    btn2D->addClickEventListener([&](Ref* sender){
        Director::getInstance()->replaceScene(MainScene::createScene());
    });
    
    Button* btnTiledMap = (Button*) layerBG->getChildByName("btnTiledMap");
    btnTiledMap->setPressedActionEnabled(true);
    btnTiledMap->addClickEventListener([&](Ref* sender){
        Director::getInstance()->replaceScene(MainScene::createScene());
    });
    
    Button* btn3D = (Button*) layerBG->getChildByName("btn3D");
    btn3D->setPressedActionEnabled(true);
    btn3D->addClickEventListener([&](Ref* sender){
        Director::getInstance()->replaceScene(MainScene::createScene());
    });
    
    Button* btnAbout = (Button*) layerBG->getChildByName("btnAbout");
    btnAbout->setPressedActionEnabled(true);
    btnAbout->addClickEventListener([&](Ref* sender){
        Director::getInstance()->replaceScene(MainScene::createScene());
    });

    
}
void Game3D::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
    
    
    
}
