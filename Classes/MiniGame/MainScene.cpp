

#include "ui/CocosGUI.h"
//#include "cocos-ext.h"
#include "../cocos/editor-support/cocostudio/CocoStudio.h"
#include <string>

#include "MainScene.hpp"
#include "GameScene.hpp"
#include "Game3D.hpp"
#include "GameTiledMap.hpp"
#include "AboutScene.hpp"
#include "SlotScene.hpp"
#include "Game2D.h"
USING_NS_CC;

Scene* MainScene::createScene()
{
    
    //return MainScene::create();
    auto scene = Scene::create();
    auto layer = MainScene::create();
    scene->addChild(layer);
    return scene;
}

bool MainScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    

    initComponents();

    
    return true;
}

void MainScene::initComponents()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    ValueMap map = FileUtils::getInstance()->getValueMapFromFile("config.plist");
    string homeURL = map["HOME_URL"].asString();
    log("HOME_URL...%s", homeURL.c_str());
    layerBG = CSLoader::createNode(SCENE_MAIN_CSB);
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
        Director::getInstance()->replaceScene(Game2D::createScene());
    });
    
    Button* btnTiledMap = (Button*) layerBG->getChildByName("btnTiledMap");
    btnTiledMap->setPressedActionEnabled(true);
    btnTiledMap->addClickEventListener([&](Ref* sender){
        Director::getInstance()->replaceScene(GameTiledMap::createScene());
    });
    
    Button* btn3D = (Button*) layerBG->getChildByName("btn3D");
    btn3D->setPressedActionEnabled(true);
    btn3D->addClickEventListener([&](Ref* sender){
        Director::getInstance()->replaceScene(Game3D::createScene());
    });
    
    Button* btnAbout = (Button*) layerBG->getChildByName("btnAbout");
    btnAbout->setPressedActionEnabled(true);
    btnAbout->addClickEventListener([&](Ref* sender){
        Director::getInstance()->replaceScene(AboutScene::createScene());
    });

    Button* btnSlotScene = (Button*) layerBG->getChildByName("btnSlot");
    btnSlotScene->setPressedActionEnabled(true);
    btnSlotScene->addClickEventListener([&](Ref* sender){
        Director::getInstance()->replaceScene(SlotScene::createScene());
    });
    
    Menu* menu = Menu::create();
    for (int i = 0; i < 9; i++)
    {
        auto closeItem = MenuItemImage::create(  "res/images/button/btn_red.png", "res/images/button/btn_red2.png",CC_CALLBACK_1(MainScene::menuCloseCallback, this));
        closeItem->setAnchorPoint(Point(0.5, 0.5));
        //closeItem->setAnchorPoint(Point(0,0));
        closeItem->setPosition(Vec2(0,i*closeItem->getContentSize().height/2));
        menu->addChild(closeItem);
    }
    menu->alignItemsVertically();
    
//    Size scroll_size = Director::getInstance()->getWinSize();
//    Size container_size = Size(scroll_size.width * 2, scroll_size.height);
//    Layer* container = Layer::create();
//    container->setContentSize(container_size);
    cocos2d::ui::ScrollView* scrollView = cocos2d::ui::ScrollView::create();
    scrollView->setContentSize(Size(visibleSize.width, 450)); // What user see
    scrollView->setInnerContainerSize(Size(visibleSize.width, 830));
    scrollView->setAnchorPoint(Vec2(0.5,0.5));
    scrollView->setDirection(ScrollView::Direction::VERTICAL);
    //scrollView->setBounceEnabled(true);
    scrollView->addChild(menu);
    scrollView->setPosition(Point (visibleSize.width-200,visibleSize.height/2));
   // scrollView->setContentSize(Size(menu->getContentSize().width, menu->getContentSize().height));
    scrollView->unscheduleAllSelectors();
    //this->addChild(scrollView, 2);
    
}
void MainScene::menuCloseCallback(Ref* pSender)
{
   // Director::getInstance()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
   // exit(0);
#endif
    
    
    
}
