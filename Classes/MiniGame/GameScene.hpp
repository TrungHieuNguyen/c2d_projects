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
enum class State
{
    SWIMMING,
    SWIMMING_TO_HURT,
    HURT,
    HURT_TO_SWIMMING,
};

class GameScene : public AbstractScene
{
    TMXTiledMap *_tileMap;
    TMXLayer *_background;
    TMXLayer *_foreground;
    TMXLayer *_meta;
    Sprite *_player;
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
    
    cocos2d::Camera * _camera;
    cocos2d::Vec3 _targetPos;
    unsigned int   _curState;
    cocos2d::Sprite3D * _plane;
    cocos2d::Sprite3D * _orc;
    State   _state;
    cocos2d::Sprite3D* _sprite;
    cocos2d::Action* _swim;
    cocos2d::Animate3D* _hurt;
    cocos2d::MoveTo*    _moveAction;
    ProgressTimer *topImage;
     float _elapseTransTime;
    
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    void update(float dt);
    void menuCloseCallback(cocos2d::Ref* pSender);
    void setViewPointCenter(Point position);
    //void registerWithTouchDispatcher();
    void setPlayerPosition(Point position);
    CREATE_FUNC(GameScene);
    void start();
    void stop();
    void pause();
    void result();
    virtual bool onTouchBegan(cocos2d::Touch*, cocos2d::Event*);
    virtual void onTouchEnded(cocos2d::Touch*, cocos2d::Event*);
    virtual void onTouchMoved(cocos2d::Touch*, cocos2d::Event*);
    virtual void onTouchCancelled(cocos2d::Touch*, cocos2d::Event*);
    Point tileCoordForPosition(Point position);
    void reachEndCallBack();    
    
    
};


#endif /* GameScene_hpp */
