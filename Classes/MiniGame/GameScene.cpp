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
        if(!isStartedGame)
            start();
        else
            stop();
        
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
    this->schedule(schedule_selector(GameScene::update));
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
        this->setPlayerPosition(playerPos);
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
