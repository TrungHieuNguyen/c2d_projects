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
    CCTMXTiledMap *_tileMap;
    CCTMXLayer *_background;
    CCSprite *_player;
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
    void setViewPointCenter(CCPoint position);
    void registerWithTouchDispatcher();
    void setPlayerPosition(CCPoint position);
    bool ccTouchBegan(CCTouch *touch, CCEvent *event);
    void ccTouchEnded(CCTouch *touch, CCEvent *event);
    CREATE_FUNC(GameScene);
    void start();
    void stop();
    void pause();
};
#endif /* GameScene_hpp */
