#pragma once

#include "cocos2d.h"
#include "DragonBones/cocos2dx/CCDragonBonesHeaders.h"

class Dealer : public cocos2d::LayerColor
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    CREATE_FUNC(Dealer);

private:
    bool _isMoved;
    float _prevArmatureScale;
    float _armatureScale;
    cocos2d::Vec2 _startPoint;

    unsigned _armatureIndex;
    unsigned _animationIndex;
    dragonBones::DragonBonesData* _dataDealerAnim;
    dragonBones::Armature* _armature;
    dragonBones::CCArmatureDisplay* _armatureDisplay;
    dragonBones::CCFactory _factory;

    void _changeArmature();
    void _changeAnimation();

    bool _touchBeganHandler(const cocos2d::Touch* touch, cocos2d::Event* event);
    void _touchEndedHandler(const cocos2d::Touch* touch, cocos2d::Event* event);
    void _touchMovedHandler(const cocos2d::Touch* touch, cocos2d::Event* event);
};


