
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
    m_Speed = 1;
    m_Direction = 1;
    stopSpinning = true;
    m_Velocity = 1;
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
    m_Velocity = 1;
    arrResult[3][5] = {{1}};
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
    //m_Speed = 20;
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
            m_Speed = 20;
            schedule(schedule_selector(SlotScene::spin), 0.02);
            schedule(schedule_selector(SlotScene::spinCounter), 0.5);
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
void SlotScene::spinCounter(float dt)
{
    log("spinCounter...");
    if(m_Speed >= 100)
    {
        m_Direction = -1;
    }
    if(abs(m_Speed) > 50)
    {
        m_Velocity = 30;
    }
    else
    {
         m_Velocity = 10;
    }
    m_Speed += m_Direction*m_Velocity;
    if(m_Speed<= 0 && m_Direction < 0)
    {
        isPlaying = false;
        m_Direction = 1;
        m_Speed = 20;
    }
    Text* txtCoinSize = (Text*) layerBG->getChildByName("txtCoinSize");
    txtCoinSize->setString(StringUtils::toString(m_Speed));
}
void SlotScene::spin(float dt)
{
    log("spin...");
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
                Sprite* item = Layer->getChildByName<Sprite*>(name);
                if(item)
                {
                    
                    item->setPositionY(item->getPositionY() - m_Speed);
                    int deltaY  = item->getPositionY() - pEnd.y;
                    if(deltaY<=0)
                    {
                        int rand = RandomHelper::random_int(0,11);
                        string path = StringUtils::format("images/items/item%02d.png",rand);
                        item->setTexture(path);
                        item->setPositionY(pStart.y + deltaY);
                    }
                    
                }
            }
        }
    }
    else
    {
        stopSpinning = true;
        showResult(arrResult);
        unschedule(schedule_selector(SlotScene::spinCounter));
        unschedule(schedule_selector(SlotScene::spin));
    }
    
}
void SlotScene::showResult(int arr[3][5])
{
    resetArrayResult(0);
    for(int k =1; k<6; k++)
    {
        string namePanel = StringUtils::format("panel0%d",k);
        auto Layer = layerBG->getChildByName(namePanel);
        Point pStart = Layer->getChildByName("itemStart")->getPosition();
        Point pEnd = Layer->getChildByName("itemEnd")->getPosition();
        for(int i =0; i<= 3; i++)
        {
            
            string name = StringUtils::format("item0%d",i);
            Sprite* item = Layer->getChildByName<Sprite*>(name);
            if(item)
            {
                string path = StringUtils::format("images/items/item%02d.png",arrResult[i][k-1]);
                item->setTexture(path);
            }
        }
    }
}
void SlotScene::resetArrayResult(int k)
{
    for(int i =0; i<= 3; i++)
    for(int j =0; j<= 5; j++)
    {
        if(k==-1)
             arrResult[i][j] = RandomHelper::random_int(0,11);
        else
            arrResult[i][j] = k;
    }
}
void SlotScene::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
    
}
