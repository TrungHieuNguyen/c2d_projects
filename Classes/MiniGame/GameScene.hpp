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
#include "GameDefine.h"
#include "AbstractScene.hpp"
#include "TienLen/Player.hpp"
#include "TienLen/Card.hpp"
class GameScene : public AbstractScene
{


    EventListenerTouchOneByOne* listenerTouchByOne;
    Text* lbScore;
    Node* layerHUD;
    bool isStartedGame;
    long _frameCounter;
    LoadingBar* _ldbGameClock;
    int   sliderUnit;
    long sliderValue;
    Node* silderDatChuong;
    void updateSliderBar(int value);
    ProgressTimer *topImage;
    float _elapseTransTime;
    Sprite* _player;
    Vector<Player*> vPlayer;
    Vector<Card*> vCard52;
    
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    void update(float dt);
    void menuCloseCallback(cocos2d::Ref* pSender);
    void setViewPointCenter(Point position);
    //void registerWithTouchDispatcher();

    CREATE_FUNC(GameScene);
    void start();
    void stop();
    void pause();
    void result();
    virtual bool onTouchBegan(cocos2d::Touch*, cocos2d::Event*);
    virtual void onTouchEnded(cocos2d::Touch*, cocos2d::Event*);
    virtual void onTouchMoved(cocos2d::Touch*, cocos2d::Event*);
    virtual void onTouchCancelled(cocos2d::Touch*, cocos2d::Event*);
    void dealCards();
 
    
    
};


#endif /* GameScene_hpp */
