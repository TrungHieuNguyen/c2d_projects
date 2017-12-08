#ifndef __GAME2D_SCENE_H__
#define __GAME2D_SCENE_H__

#include "cocos2d.h"
#include "../cocos/editor-support/cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "GameDefine.h"
#include "AbstractScene.hpp"
USING_NS_CC;


enum class HeroState
{
    STAND,
    LEFT,
    RIGHT,
    UP,
    DOWN,
    HURT,
    ATTACH,
    SHOOT,
    JUMP,
    DIE
};

class Game2D : public AbstractScene
{
public:
    Animate * animateRun;
    Animate * animateAttach;
    Animate * animateDizzy;
    Sprite * sprHero;
    HeroState stateHero;
    static cocos2d::Scene* createScene();
    virtual bool init();
    void update(float dt);
    void onAttach(Ref* pSender, ui::Widget::TouchEventType eEventType);
    void onHurt(Ref* pSender, ui::Widget::TouchEventType eEventType);
    void onUp(Ref* pSender, ui::Widget::TouchEventType eEventType);
    void onDown(Ref* pSender, ui::Widget::TouchEventType eEventType);
    void onLeft(Ref* pSender, ui::Widget::TouchEventType eEventType);
    void onRight(Ref* pSender, ui::Widget::TouchEventType eEventType);
    
    void onA(Ref* pSender, ui::Widget::TouchEventType eEventType);
    void onB(Ref* pSender, ui::Widget::TouchEventType eEventType);
    void onC(Ref* pSender, ui::Widget::TouchEventType eEventType);
    void onD(Ref* pSender, ui::Widget::TouchEventType eEventType);
    Vector< SpriteFrame*> getAnimation(const char *format, int count);
    CREATE_FUNC(Game2D);
};

#endif
