//
//  MainScene.hpp
//  ChipGame
//
//  Created by Nguyen Trung Hieu on 8/18/17.
//
//

#ifndef Game3D_hpp
#define Game3D_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "GameDefine.h"

using namespace cocos2d;
using namespace ui;

enum class State
{
    SWIMMING,
    SWIMMING_TO_HURT,
    HURT,
    HURT_TO_SWIMMING,
};

class Game3D : public AbstractScene
{
    Node* layerBG;
    Text* lbTitle;
    
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
    float _elapseTransTime;
protected:
    cocos2d::GLProgramState * _glState;
public:
    static cocos2d::Scene* createScene();
    void update(float dt);
    virtual bool init();
    void reachEndCallBack();
    void menuCloseCallback(cocos2d::Ref* pSender);
    void initComponents();
    void Sprite3DNormalMappingTest();
    CREATE_FUNC(Game3D);
};
#endif /* Game3D_hpp */
