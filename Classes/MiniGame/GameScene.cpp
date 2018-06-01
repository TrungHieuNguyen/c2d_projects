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
#include "PopupShop.hpp"

#include "MainScene.hpp"
#include "Card.hpp"
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
    btnB->addClickEventListener([&,btnB](Ref* sender){
        dealCards();
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
    _player = Sprite::create("res/images/card/cardback.png");
    _player->setPosition(Vec2(10,500));
    if(_player)
        _player->runAction(
                           RepeatForever::create(
                                                 Sequence::create(
                                                                  MoveBy::create(0.05f, Vec2(20,2)),
                                                                  MoveBy::create(0.05f, Vec2(-20,-2)),
                                                                  nullptr)));
    this->addChild(_player,6);
    
    
    Sprite* sprDish = layerBG->getChildByName<Sprite*>("sprDish");
    if(sprDish)
        sprDish->runAction(
                      RepeatForever::create(
                                            Sequence::create(
                                                             MoveBy::create(0.05f, Vec2(20,2)),
                                                             DelayTime::create(0.05),
                                                             MoveBy::create(0.05f, Vec2(-20,-2)),
                                                             nullptr)));
    
    topImage = ProgressTimer::create(Sprite::create("res/loading/icon_sample.png"));
    topImage->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2));
    topImage->setRotation(180);
    topImage->setType(cocos2d::ProgressTimer::Type::RADIAL);
    topImage->setPercentage(0);
    addChild(topImage);
    
    for(int i=0; i< 4;i++)
    {
        Player* player = Player::create();
        player->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
        vPlayer.pushBack(player);
        player->initPlayerType((PlayerType) i);
        player->Cards->setTypePlayer((PlayerType)i);
        //player->setPosition(Vec2(0,0));
        addChild(player,10);
    }
    int offsetX = 0;
    int offsetY = 0;
    vCard52.clear();
    for(int j=0; j< 52;j++)
    {

        if(j%13==0)
        {
            offsetY++;
            offsetX = 0;
        }
        Card* card = Card::create();
        card->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
        //card->setPosition(Vec2(400+offsetX*50,600 - offsetY*100));
        card->set52(j);
        card->flip();
        vCard52.pushBack(card);
        //this->addChild(card,10);
        offsetX++;
    }
    //player->setPosition(100,100);
    ///AbstractScene::showGold(10000,false);
    //AbstractScene::showResult(PlayerRank::RANK_NHAT,5);
    
    
    auto array = PointArray::create(20);
    
    array->addControlPoint(Vec2(0, 0));
    array->addControlPoint(Vec2(100,100));
    array->addControlPoint(Vec2(200,200));
    array->addControlPoint(Vec2(300, 150));
    array->addControlPoint(Vec2(400, 230));
    array->addControlPoint(Vec2(500, 90));
    array->addControlPoint(Vec2(600, 60));
    array->addControlPoint(Vec2(700, 110));
    
    auto drawNode1 = DrawNode::create();
    drawNode1->setPosition(Vec2(50,50));
    drawNode1->drawCatmullRom(array, 50, Color4F(1.0, 0.0, 1.0, 1.0));
    this->addChild(drawNode1);
    
    auto drawNode2 = DrawNode::create();
    drawNode2->setPosition(Vec2(100,100));
    drawNode2->setLineWidth(10);
    drawNode2->drawCardinalSpline(array, 1, 100, Color4F::GREEN);
    this->addChild(drawNode2);

    
    for(int i = 0; i< array->count(); i++)
    {
        auto drawDot = DrawNode::create();
        drawDot->setPosition(Vec2(100,100));
        //drawDot->drawDot(array[i], 1, Color4F::GREEN);
        this->addChild(drawDot);
    }
    
    auto drawPoly = DrawNode::create();
    drawPoly->setLineWidth(4);
    addChild(drawPoly, 10);
    // open random color poly
    Vec2 vertices[] = { Vec2(0,0), Vec2(50,50), Vec2(100,50), Vec2(100,100), Vec2(50,100) };
    drawPoly->drawPoly( vertices, 5, false, Color4F(CCRANDOM_0_1(), CCRANDOM_0_1(), CCRANDOM_0_1(), 1));
    
    
//    string path = "res/screen/XD/AnimDice/skeleton";
//    anim = spine::SkeletonAnimation::createWithJsonFile(path + ".json", path + ".atlas", 1);
//    anim->setAnimation(0, "idle", false);
//    anim->setScale(1.0);
//    anim->setVisible(true);
//    anim->setPosition(convertToWorldSpace(screenCenter->convertToWorldSpace(screenCenter->getChildByName("nodeXN")->getPosition())));
//    this->addChild(anim, 10);
    
    
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
    AbstractScene::showTextGame("You Win!!!");
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


void GameScene::dealCards()
{
    for(int i=0; i<vCard52.size();i++){
        Card* card = (Card*) vCard52.at(i);
        Player *player = (Player*) vPlayer.at(i % vPlayer.size());
        player->Cards->addCard(card);
    }

}


