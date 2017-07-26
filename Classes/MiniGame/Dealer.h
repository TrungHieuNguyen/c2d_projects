#pragma once

#include "cocos2d.h"
#include "../DragonBones/cocos2dx/CCDragonBonesHeaders.h"

class Dealer : public cocos2d::Node
{
public:
    Dealer();
    void load(std::string , std::string);
    void show(std::string, std::string);
private:
    bool _isMoved;
    float _prevArmatureScale;
    float _armatureScale;
    cocos2d::Vec2 _startPoint;

    unsigned _armatureIndex;
    unsigned _animationIndex;
    dragonBones::DragonBonesData* _data;
    dragonBones::Armature* _armature;
    dragonBones::CCArmatureDisplay* _armatureDisplay;
    dragonBones::CCFactory _factory;

};


