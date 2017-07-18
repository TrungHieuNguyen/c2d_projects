#include "DBAnimation.h"

USING_NS_CC;

DBAnimation::DBAnimation()
{
    _isMoved = false;
    _prevArmatureScale = 1.f;
    _armatureScale = 1.f;
    _armatureIndex = 0;
    _animationIndex = 0;
    _armature = nullptr;
    _armatureDisplay = nullptr;
    
}
DBAnimation::~DBAnimation()
{
    
}

void DBAnimation::load(std::string data,std::string texture)
{
    _data = _factory.loadDragonBonesData(data);
    _factory.loadTextureAtlasData(texture);

}
void DBAnimation::run(std::string arma, std::string anim)
{
    load("DragonBoy/DragonBoy.json","DragonBoy/DragonBoy_texture_1.json");
    if (_data)
    {
        if (_armature)
        {
            _armature->dispose();
            this->removeChild(_armatureDisplay);
        }
        _armatureDisplay = _factory.buildArmatureDisplay(arma);
        _armature = _armatureDisplay->getArmature();
        
        const auto center = cocos2d::Director::getInstance()->getVisibleSize();
        _armatureDisplay->setPosition(center.width * 0.5f, center.height * 0.5f);
        this->addChild(_armatureDisplay);
        _armature->getAnimation().play(anim);
    } else
    {
        assert(false);
    }
    
}
