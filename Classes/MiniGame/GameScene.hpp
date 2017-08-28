//
//  GameScene.hpp
//  ChipGame
//
//  Created by Nguyen Trung Hieu on 8/22/17.
//
//

#ifndef GameScene_hpp
#define GameScene_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "ui/CocosGUI.h"
using namespace cocos2d;
using namespace ui;

class GameScene : public cocos2d::Scene
{
    TMXTiledMap *_tileMap;
    TMXLayer *_background;
    TMXLayer *_foreground;
    TMXLayer *_meta;
    Sprite *_player;
    EventListenerTouchOneByOne* listenerTouchByOne;
    Text* lbScore;
    bool isStartedGame;
    long _frameCounter;
    LoadingBar* _ldbGameClock;

public:
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    void update(float dt);
    void menuCloseCallback(cocos2d::Ref* pSender);
    void setViewPointCenter(Point position);
    void registerWithTouchDispatcher();
    void setPlayerPosition(Point position);
    CREATE_FUNC(GameScene);
    void start();
    void stop();
    void pause();
    virtual bool onTouchBegan(cocos2d::Touch*, cocos2d::Event*);
    virtual void onTouchEnded(cocos2d::Touch*, cocos2d::Event*);
    virtual void onTouchMoved(cocos2d::Touch*, cocos2d::Event*);
    virtual void onTouchCancelled(cocos2d::Touch*, cocos2d::Event*);
    Point tileCoordForPosition(Point position);
};
#endif /* GameScene_hpp */
