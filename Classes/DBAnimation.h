#pragma once

#include "cocos2d.h"
#include "DragonBones/cocos2dx/CCDragonBonesHeaders.h"

class DBAnimation : public cocos2d::Node
{
public:
     DBAnimation();
    virtual ~DBAnimation();
    void load(std::string , std::string);
    void run(std::string, std::string);
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


