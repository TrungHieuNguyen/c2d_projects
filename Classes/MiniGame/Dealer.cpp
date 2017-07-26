#include "Dealer.h"

USING_NS_CC;


Dealer::Dealer()
{
    _isMoved = false;
    _prevArmatureScale = 1.f;
    _armatureScale = 1.f;

    _armatureIndex = 0;
    _animationIndex = 0;
    _armature = nullptr;
    _armatureDisplay = nullptr;
   
    return ;
}

void Dealer::load(std::string data,std::string texture)
{
    _data = _factory.loadDragonBonesData(data);
    _factory.loadTextureAtlasData(texture);

}
void Dealer::show(std::string arma, std::string anim)
{
    log("show dealer...");
    load("Dealer/PokerKing_ske.json","Dealer/PokerKing_tex.json");
    // Remove prev Armature.
    if (_armature)
    {
        _armature->dispose();
        this->removeChild(_armatureDisplay);
        
        // b.
        // dragonBones::WorldClock::clock.remove(_armature);
    }
    
    
    // a. Build Armature Display. (buildArmatureDisplay will advanceTime animation by Armature Display)
    _armatureDisplay = _factory.buildArmatureDisplay(arma);
    _armature = _armatureDisplay->getArmature();
    
    const auto center = cocos2d::Director::getInstance()->getVisibleSize();
    _armatureDisplay->setPosition(center.width * 0.5f, center.height * 0.5f);
    _armatureDisplay->setScale(0.5f);
    this->addChild(_armatureDisplay);
    _armature->getAnimation().play(anim);
    _animationIndex = 0;
    
}
