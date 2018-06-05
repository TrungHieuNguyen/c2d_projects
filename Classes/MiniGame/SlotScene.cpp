
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
    m_Speed = 0;
    m_Direction = 1;
    stopSpinning = true;
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    initComponents();

    
    return true;
}

void SlotScene::initComponents()
{
    layerBG = CSLoader::createNode(SCENE_SLOT_CSB);
    addChild(layerBG, -1);
    isPlaying = false;
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
    m_Speed = 20;
    auto LayerCard01 = layerBG->getChildByName("panel01");
    auto card01 = LayerCard01->getChildByName("item01");
    auto card02 = LayerCard01->getChildByName("item02");
    auto card03 = LayerCard01->getChildByName("item03");
    
    Button* btnSpin = (Button*) layerBG->getChildByName("btnSpin");
    btnSpin->setPressedActionEnabled(true);
    btnSpin->addClickEventListener([&](Ref* sender){
        if(isPlaying)
        {
//            stopSpinning = true;
//            unschedule(schedule_selector(SlotScene::spin));
        }
        else
        {
            stopSpinning = false;
            schedule(schedule_selector(SlotScene::spin), 0.02);
        }
         isPlaying = !isPlaying;
    });
    
    Button* btnUp = (Button*) layerBG->getChildByName("btnUp");
    btnUp->setPressedActionEnabled(true);
    btnUp->addClickEventListener([&](Ref* sender){
         m_Speed += 20;
    });
    
    Button* btnDown = (Button*) layerBG->getChildByName("btnDown");
    btnDown->setPressedActionEnabled(true);
    btnDown->addClickEventListener([&](Ref* sender){
        m_Speed -= 20;
    });
    
}
void SlotScene::spin(float dt)
{
    if(isPlaying)
    {
        for(int k =1; k<6; k++)
        {
            string namePanel = StringUtils::format("panel0%d",k);
            auto Layer = layerBG->getChildByName(namePanel);
            Point pStart = Layer->getChildByName("itemStart")->getPosition();
            Point pEnd = Layer->getChildByName("itemEnd")->getPosition();
            for(int i =0; i<= 3; i++)
            {
                string name = StringUtils::format("item0%d",i);
                auto item = Layer->getChildByName(name);
                if(item)
                {
                    item->setPositionY(item->getPositionY() - m_Speed);
                    int deltaY  = item->getPositionY() - pEnd.y;
                    if(deltaY<=0)
                    {
                        item->setPositionY(pStart.y + deltaY);
                    }
                    
                }
            }
        }
    }
    else
    {
        stopSpinning = true;
        unschedule(schedule_selector(SlotScene::spin));
//        for(int k =1; k<6; k++)
//        {
//            string namePanel = StringUtils::format("panel0%d",k);
//            auto Layer = layerBG->getChildByName(namePanel);
//            Point pStart = Layer->getChildByName("itemStart")->getPosition();
//            Point pEnd = Layer->getChildByName("itemEnd")->getPosition();
//            int deltaY  = 0;
//            int botItem = -1;
//            for(int i =0; i<= 3; i++)
//            {
//
//                string name = StringUtils::format("item0%d",i);
//                auto item = Layer->getChildByName(name);
//                if(item)
//                {
//                    int dtY  = item->getPositionY() - pEnd.y;
//                    if(dtY<=deltaY)
//                    {
//                        item->setPositionY(pStart.y + deltaY);
//                        deltaY = dtY;
//                        botItem = i;
//                    }
//                }
//            }
//
//            for(int i =0; i<= 3; i++)
//            {
//                string name = StringUtils::format("item0%d",i);
//                auto item = Layer->getChildByName(name);
//                if(item)
//                {
//                    item->runAction(MoveTo::create(0.3,Vec2(item->getPosition().x, item->getPosition().y + deltaY)));
//                }
//            }
//        }
    }
    
}
void SlotScene::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
    
}
