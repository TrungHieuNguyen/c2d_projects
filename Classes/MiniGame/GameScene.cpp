//
//  GameScene.cpp
//  ChipGame
//
//  Created by Nguyen Trung Hieu on 8/22/17.
//
//

#include "GameScene.hpp"
#include "GameDefine.h"
#include "ui/CocosGUI.h"
#include "../cocos/editor-support/cocostudio/CocoStudio.h"
#include "SimpleAudioEngine.h"
#include "PopupResult.hpp"

#include "MainScene.hpp"
USING_NS_CC;

Scene* GameScene::createScene()
{
    auto scene = Scene::create();
    auto layer = GameScene::create();
    scene->addChild(layer);
    return scene;
}

bool GameScene::init()
{
    if ( !AbstractScene::init() )
    {
        return false;
    }
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    isStartedGame = false;
    _frameCounter = 0;
   

    auto layerBG = CSLoader::createNode(SCENE_GAME_CSB);
    layerBG->setAnchorPoint(Point(0.5f, 0.5f));
    layerBG->setPosition(layerBG->getContentSize()/2);
    addChild(layerBG,-1);
    
    Button* btnA = (Button*) layerBG->getChildByName("btnA");
    btnA->setPressedActionEnabled(true);
    btnA->addClickEventListener([&](Ref* sender){
        if(!isStartedGame)
            start();
        else
            stop();
    });

    Button* btnB = (Button*) layerBG->getChildByName("btnB");
    btnB->setPressedActionEnabled(true);
    btnB->addClickEventListener([&](Ref* sender){
       Director::getInstance()->replaceScene(MainScene::createScene());
        
    });
    //LayerCard
    auto LayerCard = layerBG->getChildByName("LayerCard");
    
    
    lbScore = (Text*) layerBG->getChildByName("lbTitle");
    lbScore->setColor(Color3B::WHITE);
    lbScore->setIgnoreAnchorPointForPosition(false);
    lbScore->setAnchorPoint(Point(0, 0.5f));
 
    auto card01 = LayerCard->getChildByName("sprMC01");
    auto card02 = LayerCard->getChildByName("sprMC02");
    auto card03 = LayerCard->getChildByName("sprMC03");
    
    
    listenerTouchByOne = EventListenerTouchOneByOne::create();
    listenerTouchByOne->setSwallowTouches(true);
    
    listenerTouchByOne->onTouchBegan = [](Touch* touch, Event* event){
        auto target = static_cast<Sprite*>(event->getCurrentTarget());
        
        Vec2 locationInNode = target->convertToNodeSpace(touch->getLocation());
        Size s = target->getContentSize();
        Rect rect = Rect(0, 0, s.width, s.height);
        
        if (rect.containsPoint(locationInNode))
        {
            log("sprite began... x = %f, y = %f", locationInNode.x, locationInNode.y);
            target->setOpacity(180);
            return true;
        }
        return false;
    };
    
    listenerTouchByOne->onTouchMoved = [](Touch* touch, Event* event){
        auto target = static_cast<Sprite*>(event->getCurrentTarget());
        target->setPosition(target->getPosition() + touch->getDelta());
    };
    
    listenerTouchByOne->onTouchEnded = [=](Touch* touch, Event* event){
        auto target = static_cast<Sprite*>(event->getCurrentTarget());
        target->setOpacity(255);

    };
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listenerTouchByOne, card01);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listenerTouchByOne->clone(), card02);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listenerTouchByOne->clone(), card03);
    
    
    auto spBarBg = Sprite::create("res/loading/loading_bar2.png");
    spBarBg->setPosition(Vec2(visibleSize.width / 2, 20));
    addChild(spBarBg);
    
    _ldbGameClock = ui::LoadingBar::create("res/loading/loading_bar.png", 0);
    _ldbGameClock->setPosition(spBarBg->getPosition());
    addChild(_ldbGameClock);
    
//    auto slider = Slider::create();
//    slider->loadBarTexture("res/loading/Slider_Back.png"); // what the slider looks like
//    slider->loadSlidBallTextures("res/loading/SliderNode_Normal.png", "res/loading/SliderNode_Press.png", "res/loading/SliderNode_Disable.png");
//    slider->loadProgressBarTexture("res/loading/Slider_PressBar.png");
//    slider->setScale(2.0f);
//    slider->setRotation(90);
//    slider->setPosition(Vec2(30, slider->getContentSize().width +100) );
// 
//   
//    slider->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type){
//        switch (type)
//        {
//            case ui::Widget::TouchEventType::BEGAN:
//                break;
//            case ui::Widget::TouchEventType::ENDED:
//                break;
//            default:
//                break;
//        }
//    });
//    
//    this->addChild(slider);
    auto touchListener = EventListenerTouchOneByOne::create();
    
    touchListener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
    touchListener->onTouchCancelled = CC_CALLBACK_2(GameScene::onTouchCancelled, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    AbstractScene::showHUD();
//    sliderValue = 0;
//    sliderUnit = 500;
//    silderDatChuong = CSLoader::createNode(RES_SLIDER_DATCHUONG_CSB);
//    silderDatChuong->setAnchorPoint(Point(0.5f, 0.5f));
//    silderDatChuong->setPosition(Vec2(visibleSize.width + silderDatChuong->getContentSize().width/2, visibleSize.height/2 - 50 ));
//    this->addChild(silderDatChuong,Z_ODER_HUD);
//    auto btnChuong = silderDatChuong->getChildByName<Button*>("btnChuong");
//    btnChuong->setPressedActionEnabled(true);
//
//
//
//    btnChuong->addClickEventListener([&](Ref* sender)
//    {
//            auto visibleSize = Director::getInstance()->getVisibleSize();
//            ActionInterval* move = MoveTo::create(0.5, Point(visibleSize.width + silderDatChuong->getContentSize().width/2 +50, visibleSize.height/2 - 50));
//            ActionInterval* move_ease = EaseBackInOut::create((ActionInterval*) (move->clone()));
//            silderDatChuong->runAction(move_ease);
//    });
//    cocos2d::ui::Slider *sliderSound = ( cocos2d::ui::Slider * )silderDatChuong->getChildByName( "Slider" );
//    auto txtValue = silderDatChuong->getChildByName<Text*>("lbValueChuong");
//    sliderSound->setMaxPercent(9);
//    sliderValue = (sliderSound->getPercent() + 1) * sliderUnit;
//    txtValue->setString(std::to_string(sliderValue));
//    sliderSound->addEventListener([&,txtValue](Ref* sender, Slider::EventType type) {
//        auto slider = dynamic_cast<Slider*>(sender);
//        if (type == Slider::EventType::ON_PERCENTAGE_CHANGED)
//        {
//            log("MOVED: %d",slider->getPercent());
//            sliderValue = (slider->getPercent() + 1)*sliderUnit;
//            txtValue->setString(std::to_string(sliderValue));
//        }
//    });
//
//    for(int i = 0; i<10 ; i++)
//    {
//        //std::string btnName = "btnValue0" + Utils::IntToString(i);
//        std::string txtName = "lbValue0" + std::to_string(i);
//        auto txtValue = silderDatChuong->getChildByName<Text*>(txtName);
//        txtValue->setString(std::to_string((i+1)*sliderUnit));
//    }
//
//    silderDatChuong->stopAllActions();
//    ActionInterval* slider_move = MoveTo::create(0.5, Point(visibleSize.width - silderDatChuong->getContentSize().width/2 - 50, visibleSize.height/2 - 50));
//    ActionInterval* slider_move_ease = EaseBackInOut::create((ActionInterval*) (slider_move->clone()));
//    silderDatChuong->runAction(slider_move_ease);
//
//

    _player = Sprite::create("Player.png");
    _player->setPosition(Vec2(10,800));
    this->addChild(_player,6);
    
    
    
    topImage = ProgressTimer::create(Sprite::create("loading/time.png"));
    topImage->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2));
    topImage->setRotation(180);
    topImage->setType(cocos2d::ProgressTimer::Type::RADIAL);
    topImage->setPercentage(0);
    addChild(topImage);
    
    AbstractScene::showGold(10000,false);
    AbstractScene::showResult(PlayerRank::RANK_NHAT,5);
    return true;
}
void GameScene::update(float dt)
{
    log("update...%f", dt);
    updateScore(_frameCounter);
    _frameCounter++;
    if (_frameCounter >= 100)
    {
        result();
    }
    _ldbGameClock->setPercent(_frameCounter);
    topImage->setPercentage(_frameCounter);


}



#pragma mark - handle touches

void GameScene::start()
{
    isStartedGame = true;
    _frameCounter = 0;
    _elapseTransTime = 0;

    this->schedule(schedule_selector(GameScene::update));
//    //silderDatChuong->stopAllActions();
//    auto visibleSize = Director::getInstance()->getVisibleSize();
//    ActionInterval* move = MoveTo::create(0.5, Point(visibleSize.width - silderDatChuong->getContentSize().width/2 -50, visibleSize.height/2 - 50));
//    ActionInterval* move_ease = EaseBackInOut::create((ActionInterval*) (move->clone()));
//    //silderDatChuong->runAction(move_ease);
    

}
void GameScene::stop()
{
    isStartedGame = false;
    this->unschedule(schedule_selector(GameScene::update));
    
//    auto visibleSize = Director::getInstance()->getVisibleSize();
//    ActionInterval* move = MoveTo::create(0.5, Point(visibleSize.width + silderDatChuong->getContentSize().width/2 +50, visibleSize.height/2 - 50));
//    ActionInterval* move_ease = EaseBackInOut::create((ActionInterval*) (move->clone()));
//    silderDatChuong->runAction(move_ease);
    
//    layerHUD->stopAllActions();
//    ActionInterval* hud_move = MoveTo::create(0.7, Point(layerHUD->getContentSize().width/2, visibleSize.height + 70));
//    ActionInterval* hud_move_ease = EaseBackInOut::create((ActionInterval*) (hud_move->clone()));
//    layerHUD->runAction(hud_move_ease);
    
    
    
    //_eventDispatcher->removeAllEventListeners();
}
void GameScene::pause()
{
    
}

void GameScene::result()
{
    //unschedule(schedule_selector(LoadingScreen::loading));
    _frameCounter = 0;
    stop();
    
    AbstractScene::showGold(10000,false);
    AbstractScene::showResult(PlayerRank::RANK_NHAT,5);
    
    PopupResult* p = PopupResult::gI();
    if (p->getParent() == NULL)
    {
        p->setPosition(Point(Director::getInstance()->getVisibleSize().width / 2, Director::getInstance()->getVisibleSize().height/2));
        addChild(p, Z_ODER_POPUP);
        p->fadeInBgDark();
        p->open();
    }
}




bool GameScene::onTouchBegan(Touch* touch, Event* event)
{
    //labelTouchInfo->setPosition(touch->getLocation());
    //labelTouchInfo->setString("You Touched Here");
    return true;
}

void GameScene::onTouchEnded(Touch* touch, Event* event)
{
    cocos2d::log("touch ended");
    CCPoint touchLocation = touch->getLocationInView();
    touchLocation = CCDirector::sharedDirector()->convertToGL(touchLocation);
    touchLocation = this->convertToNodeSpace(touchLocation);
    
    Point playerPos = _player->getPosition();
    Point diff = ccpSub(touchLocation, playerPos);
//
//    if ( abs(diff.x) > abs(diff.y) ) {
//        if (diff.x > 0) {
//            playerPos.x += _tileMap->getTileSize().width;
//        } else {
//            playerPos.x -= _tileMap->getTileSize().width;
//        }
//    } else {
//        if (diff.y > 0) {
//            playerPos.y += _tileMap->getTileSize().height;
//        } else {
//            playerPos.y -= _tileMap->getTileSize().height;
//        }
//    }
    
//    // safety check on the bounds of the map
//    if (playerPos.x <= (_tileMap->getMapSize().width * _tileMap->getTileSize().width) &&
//        playerPos.y <= (_tileMap->getMapSize().height * _tileMap->getTileSize().height) &&
//        playerPos.y >= 0 &&
//        playerPos.x >= 0 )
//    {
//        //this->setPlayerPosition(playerPos);
//    }
//    
//    this->setViewPointCenter(_player->getPosition());

}

void GameScene::onTouchMoved(Touch* touch, Event* event)
{
    cocos2d::log("touch moved");
}

void GameScene::onTouchCancelled(Touch* touch, Event* event)
{
    cocos2d::log("touch cancelled");
}
void GameScene::updateSliderBar(int value)
{
}





