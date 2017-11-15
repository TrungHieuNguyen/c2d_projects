#ifndef __GAME2D_SCENE_H__
#define __GAME2D_SCENE_H__

#include "cocos2d.h"
#include "../cocos/editor-support/cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
class Game2D : public cocos2d::Layer
{
public:
    Animate * animateRun;
    Animate * animateAttach;
    Animate * animateDizzy;
    Sprite * sprHero;
    int stateHero;
    static cocos2d::Scene* createScene();
    virtual bool init();
    void onAttach(Ref* pSender, ui::Widget::TouchEventType eEventType);
    void onHurt(Ref* pSender, ui::Widget::TouchEventType eEventType);
    Vector< SpriteFrame*> getAnimation(const char *format, int count);
    CREATE_FUNC(Game2D);
};

#endif
