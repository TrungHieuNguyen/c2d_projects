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

USING_NS_CC;

Scene* GameScene::createScene()
{
    return GameScene::create();
}

bool GameScene::init()
{
    if ( !Scene::init() )
    {
        return false;
    }
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    isStartedGame = false;
    _frameCounter = 0;
    _tileMap = TMXTiledMap::create("TiledMap/TileMap.tmx");
    _background = _tileMap->layerNamed("Background");
    _foreground = _tileMap->layerNamed("Foreground");
    _meta = _tileMap->layerNamed("Meta");
    _meta->setVisible(false);
    //this->addChild(_tileMap,Z_ODER_TILEMAP);
    TMXObjectGroup *objectGroup = _tileMap->getObjectGroup("Objects");
    
    if(objectGroup == NULL){
        CCLog("tile map has no objects object layer");
        return false;
    }
    // all tiles are aliased by default, let's set them anti-aliased
    for (const auto& child : _tileMap->getChildren())
    {
        static_cast<SpriteBatchNode*>(child)->getTexture()->setAntiAliasTexParameters();
    }
    ValueMap spawnPoint = objectGroup->getObject("SpawnPoint");
     float x  = spawnPoint["x"].asFloat();
     float y  = spawnPoint["y"].asFloat();

    _player = Sprite::create("Player.png");
    _player->setPosition(Vec2(x,y));
    this->addChild(_player,6);
    //this->setViewPointCenter(_player->getPosition());
    
    

    auto layerBG = CSLoader::createNode("GameScene.csb");
    layerBG->setAnchorPoint(Point(0.5f, 0.5f));
    layerBG->setPosition(layerBG->getContentSize()/2);
    addChild(layerBG);
    
    Button* btnA = (Button*) layerBG->getChildByName("btnA");
    btnA->addClickEventListener([&](Ref* sender){
        if(!isStartedGame)
            start();
        else
            stop();
    });

    Button* btnB = (Button*) layerBG->getChildByName("btnB");
    btnB->addClickEventListener([&](Ref* sender){
        PopupResult* p = PopupResult::gI();
        if (p->getParent() == NULL)
        {
            p->setPosition(Point(Director::getInstance()->getVisibleSize().width / 2, Director::getInstance()->getVisibleSize().height/2));
            addChild(p, Z_ODER_POPUP);
            p->fadeInBgDark();
            p->open();
        }
        
    });
    //LayerCard
    auto LayerCard = layerBG->getChildByName("LayerCard");
    
    
    lbScore = (Text*) layerBG->getChildByName("lbScore");
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
    
    auto slider = Slider::create();
    slider->loadBarTexture("res/loading/Slider_Back.png"); // what the slider looks like
    slider->loadSlidBallTextures("res/loading/SliderNode_Normal.png", "res/loading/SliderNode_Press.png", "res/loading/SliderNode_Disable.png");
    slider->loadProgressBarTexture("res/loading/Slider_PressBar.png");
    slider->setScale(2.0f);
    slider->setRotation(90);
    slider->setPosition(Vec2(30, slider->getContentSize().width +100) );
 
   
    slider->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type){
        https://kencoding.wordpress.com/category/cocos2d-x-developer/
        switch (type)
        {
            case ui::Widget::TouchEventType::BEGAN:
                break;
            case ui::Widget::TouchEventType::ENDED:
                break;
            default:
                break;
        }
    });
    
    this->addChild(slider);
    auto touchListener = EventListenerTouchOneByOne::create();
    
    touchListener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
    touchListener->onTouchCancelled = CC_CALLBACK_2(GameScene::onTouchCancelled, this);
    
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    layerHUD = CSLoader::createNode("HUDLayer.csb");
    layerHUD->setAnchorPoint(Point(0.5f, 0.5f));
    layerHUD->setPosition(Vec2(layerHUD->getContentSize().width/2,visibleSize.height -70));
    addChild(layerHUD, Z_ODER_HUD);
    
    sliderValue = 0;
    sliderUnit = 500;
    silderDatChuong = CSLoader::createNode(RES_SLIDER_DATCHUONG_CSB);
    silderDatChuong->setAnchorPoint(Point(0.5f, 0.5f));
    silderDatChuong->setPosition(Vec2(visibleSize.width + silderDatChuong->getContentSize().width/2, visibleSize.height/2 - 50 ));
    this->addChild(silderDatChuong,Z_ODER_HUD);
    auto btnChuong = silderDatChuong->getChildByName<Button*>("btnChuong");
    btnChuong->setPressedActionEnabled(true);
    
    

    btnChuong->addClickEventListener([&](Ref* sender)
    {
            auto visibleSize = Director::getInstance()->getVisibleSize();
            ActionInterval* move = MoveTo::create(0.5, Point(visibleSize.width + silderDatChuong->getContentSize().width/2 +50, visibleSize.height/2 - 50));
            ActionInterval* move_ease = EaseBackInOut::create((ActionInterval*) (move->clone()));
            silderDatChuong->runAction(move_ease);
    });
    cocos2d::ui::Slider *sliderSound = ( cocos2d::ui::Slider * )silderDatChuong->getChildByName( "Slider" );
    auto txtValue = silderDatChuong->getChildByName<Text*>("lbValueChuong");
    sliderSound->setMaxPercent(9);
    sliderValue = (sliderSound->getPercent() + 1) * sliderUnit;
    txtValue->setString(std::to_string(sliderValue));
    sliderSound->addEventListener([&,txtValue](Ref* sender, Slider::EventType type) {
        auto slider = dynamic_cast<Slider*>(sender);
        if (type == Slider::EventType::ON_PERCENTAGE_CHANGED)
        {
            log("MOVED: %d",slider->getPercent());
            sliderValue = (slider->getPercent() + 1)*sliderUnit;
            txtValue->setString(std::to_string(sliderValue));
        }
    });
    
    for(int i = 0; i<10 ; i++)
    {
        //std::string btnName = "btnValue0" + Utils::IntToString(i);
        std::string txtName = "lbValue0" + std::to_string(i);
        auto txtValue = silderDatChuong->getChildByName<Text*>(txtName);
        txtValue->setString(std::to_string((i+1)*sliderUnit));
    }
    
    silderDatChuong->stopAllActions();
    ActionInterval* move = MoveTo::create(0.5, Point(visibleSize.width - silderDatChuong->getContentSize().width/2 - 50, visibleSize.height/2 - 50));
    ActionInterval* move_ease = EaseBackInOut::create((ActionInterval*) (move->clone()));
    silderDatChuong->runAction(move_ease);

    std::string fileName = "Sprite3DTest/tortoise.c3b";
    auto sprite = Sprite3D::create(fileName);
    sprite->setScale(0.1f);
    auto s = Director::getInstance()->getWinSize();
    sprite->setPosition(Vec2(s.width * 4.f / 5.f, s.height / 2.f));
    addChild(sprite,Z_ODER_HUD);
    _sprite = sprite;
    auto animation = Animation3D::create(fileName);
    if (animation)
    {
        auto animate = Animate3D::create(animation, 0.f, 1.933f);
        _swim = RepeatForever::create(animate);
        sprite->runAction(_swim);
        
        _swim->retain();
        _hurt = Animate3D::create(animation, 1.933f, 2.8f);
        _hurt->retain();
        _state = State::SWIMMING;
    }
    
    _moveAction = MoveTo::create(4.f, Vec2(s.width / 5.f, s.height / 2.f));
    _moveAction->retain();
    auto seq = Sequence::create(_moveAction, CallFunc::create(CC_CALLBACK_0(GameScene::reachEndCallBack, this)), nullptr);
    seq->setTag(100);
    sprite->runAction(seq);
    _elapseTransTime = 0;
    return true;
}
void GameScene::update(float dt)
{
    log("update...%f", dt);
    Sprite* sprMoneyBar = layerHUD->getChildByName<Sprite*>("sprMoneyBar");
    Text* lbMoneyValue = sprMoneyBar->getChildByName<Text*>("lbMoney");
    lbMoneyValue->setString(std::to_string(_frameCounter));
    Sprite* sprCoinBar = layerHUD->getChildByName<Sprite*>("sprCoinBar");
    Text* lbCoinValue = sprCoinBar->getChildByName<Text*>("lbCoin");
    lbCoinValue->setString(std::to_string(dt));
    _frameCounter++;
    if (_frameCounter >= 100)
    {
        //unschedule(schedule_selector(LoadingScreen::loading));
        _frameCounter = 0;
    }

    _ldbGameClock->setPercent(_frameCounter);
    if (_state == State::HURT_TO_SWIMMING)
    {
        _elapseTransTime += dt;
        
        if (_elapseTransTime >= Animate3D::getTransitionTime())
        {
            _sprite->stopAction(_hurt);
            _state = State::SWIMMING;
        }
    }
    else if (_state == State::SWIMMING_TO_HURT)
    {
        _elapseTransTime += dt;
        if (_elapseTransTime >= Animate3D::getTransitionTime())
        {
            _sprite->stopAction(_swim);
            _state = State::HURT;
        }
    }

}
void GameScene::setViewPointCenter(Point position) {
    return;
    
    CCSize winSize = Director::sharedDirector()->getWinSize();
    
    int x = MAX(position.x, winSize.width/2);
    int y = MAX(position.y, winSize.height/2);
    x = MIN(x, (_tileMap->getMapSize().width * this->_tileMap->getTileSize().width) - winSize.width / 2);
    y = MIN(y, (_tileMap->getMapSize().height * _tileMap->getTileSize().height) - winSize.height/2);
    Point actualPosition = ccp(x, y);
    
    Point centerOfView = ccp(winSize.width/2, winSize.height/2);
    Point viewPoint = ccpSub(centerOfView, actualPosition);
    this->setPosition(viewPoint);
}


#pragma mark - handle touches

void GameScene::start()
{
    isStartedGame = true;
    _frameCounter = 0;
    _elapseTransTime = 0;

    this->schedule(schedule_selector(GameScene::update));
    silderDatChuong->stopAllActions();
    auto visibleSize = Director::getInstance()->getVisibleSize();
    ActionInterval* move = MoveTo::create(0.5, Point(visibleSize.width - silderDatChuong->getContentSize().width/2 -50, visibleSize.height/2 - 50));
    ActionInterval* move_ease = EaseBackInOut::create((ActionInterval*) (move->clone()));
    silderDatChuong->runAction(move_ease);
}
void GameScene::stop()
{
    isStartedGame = false;
    this->unschedule(schedule_selector(GameScene::update));
    //_eventDispatcher->removeAllEventListeners();
}
void GameScene::pause()
{
    
}
void GameScene::setPlayerPosition(CCPoint position)
{
    Point tileCoord = this->tileCoordForPosition(position);
    int tileGid = _meta->getTileGIDAt(tileCoord);
    if (tileGid) {
        ValueMap properties = _tileMap->getPropertiesForGID(tileGid).asValueMap();
        if (properties.size()) {
            String *collision = new String();
            *collision = properties["Collidable"].asString();
            if (collision && (collision->compare("True") == 0)) {
                return;
            }
            
            CCString *collectible = new CCString();
            *collectible = properties["Collectable"].asString();
            if (collectible && (collectible->compare("True") == 0)) {
                _meta->removeTileAt(tileCoord);
                _foreground->removeTileAt(tileCoord);
            }
        }
    }
    _player->setPosition(position);
}

CCPoint GameScene::tileCoordForPosition(CCPoint position)
{
    int x = position.x / _tileMap->getTileSize().width;
    int y = ((_tileMap->getMapSize().height * _tileMap->getTileSize().height) - position.y) / _tileMap->getTileSize().height;
    return ccp(x, y);
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
    
    if ( abs(diff.x) > abs(diff.y) ) {
        if (diff.x > 0) {
            playerPos.x += _tileMap->getTileSize().width;
        } else {
            playerPos.x -= _tileMap->getTileSize().width;
        }
    } else {
        if (diff.y > 0) {
            playerPos.y += _tileMap->getTileSize().height;
        } else {
            playerPos.y -= _tileMap->getTileSize().height;
        }
    }
    
    // safety check on the bounds of the map
    if (playerPos.x <= (_tileMap->getMapSize().width * _tileMap->getTileSize().width) &&
        playerPos.y <= (_tileMap->getMapSize().height * _tileMap->getTileSize().height) &&
        playerPos.y >= 0 &&
        playerPos.x >= 0 )
    {
        //this->setPlayerPosition(playerPos);
    }
    
    this->setViewPointCenter(_player->getPosition());

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
//    for(int i = 1; i<=5 ; i++)
//    {
//        std::string btnName = "btnValue0" + Utils::IntToString(i);
//        std::string txtName = "lbValue0" + Utils::IntToString(i);
//        auto txtValue = silderDatChuong->getChildByName<Text*>(txtName);
//        auto btnValue = silderDatChuong->getChildByName<Button*>(btnName);
//        auto sprEffect = btnValue->getChildByName<Sprite*>("sprEffectSelected");
//        if(i==value)
//        {
//            sprEffect->setRotation(0);
//            sprEffect->runAction(RotateTo::create(0.5, 180));
//            txtValue->setOpacity(255);
//            btnValue->setOpacity(255);
//            txtValue->setTextColor(Color4B::YELLOW);
//        }
//        else
//        {
//            txtValue->setOpacity(75);
//            txtValue->setTextColor(Color4B::WHITE);
//            btnValue->setOpacity(75);
//        }
//        
//    }
}
void GameScene::reachEndCallBack()
{
    auto s = Director::getInstance()->getWinSize();
    _sprite->stopActionByTag(100);
    auto inverse = MoveTo::create(4.f, Vec2(s.width - _sprite->getPositionX(), s.height / 2.f));
    inverse->retain();
    _moveAction->release();
    _moveAction = inverse;
    auto rot = RotateBy::create(1.f, Vec3(0.f, 180.f, 0.f));
    auto seq = Sequence::create(rot, _moveAction, CallFunc::create(CC_CALLBACK_0(GameScene::reachEndCallBack, this)), nullptr);
    seq->setTag(100);
    _sprite->runAction(seq);
}


