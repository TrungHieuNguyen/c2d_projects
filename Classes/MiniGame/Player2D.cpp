//
//  Player.cpp
//  ChipGame-mobile
//
//  Created by TrungHieu on 3/26/18.
//

#include "Player2D.hpp"
USING_NS_CC;

using namespace cocostudio::timeline;
using namespace cocos2d;
bool Player2D::init()
{
    if (Sprite::init())
    {
        lbStatus = nullptr;
        Size winSize = Director::sharedDirector()->getWinSize();
        loadComponents();
        return true;
    }
    
    return false;
}
void Player2D::loadComponents()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    lbStatus = Label::createWithTTF("00", "Marker Felt.ttf", 18);
    lbStatus->setColor(Color3B::WHITE);
    lbStatus->setIgnoreAnchorPointForPosition(false);
    lbStatus->setAnchorPoint(Point(0.5f, 0.5f));
    lbStatus->setPosition(Vec2(0, -50));
    addChild(lbStatus,10);
    
    
    sprPlayer= Sprite::createWithSpriteFrameName("hero_run_01.png");
    sprPlayer->setPosition(Vec2(0, 0));
    addChild(sprPlayer);
    //sprPlayer->stopAllActions();
    Vector< SpriteFrame*> frames = getAnimation("hero_stand_0%d.png",5);
    Animation* animation = Animation::createWithSpriteFrames(frames, 0.1f);
    animation->retain();
    //sprPlayer->runAction(Animate::create(animation));
    auto action1 = FadeIn::create(1.0f);
    auto action1Back = action1->reverse();
    
    auto action2 = FadeOut::create(1.0f);
    auto action2Back = action2->reverse();
    sprPlayer->runAction(Sequence::create(action1,action1Back,nullptr));
    sprPlayer->runAction(RepeatForever::create(Animate::create(animation)));
    
    

}

void Player2D::run()
{
    
}
void Player2D::jump()
{
    
}
void Player2D::shoot()
{
    
}
void Player2D::slash()
{
    
}
void Player2D::stand()
{
    setStatus(HeroState(7));
}
void Player2D::showStatus(HeroState stt)
{
    lbStatus->setString(StringUtils::toString(int(stt) ));
    
}
void Player2D::setStatus(HeroState stt)
{
    showStatus(stt);
    switch (stt) {
                case HeroState::RUN:
                {
                    sprPlayer->stopAllActions();
                    Vector< SpriteFrame*> frames = getAnimation("hero_run_0%d.png",6);
                    Animation* animation = Animation::createWithSpriteFrames(frames, 0.1f);
                    animation->retain();
                    sprPlayer->runAction(RepeatForever::create(Animate::create(animation)));
                }
                break;
                case HeroState::DIZZY:
                {
                    sprPlayer->stopAllActions();
                    Vector< SpriteFrame*> frames = getAnimation("hero_dizzy_0%d.png",5);
                    Animation* animation = Animation::createWithSpriteFrames(frames, 0.1f);
                    animation->retain();
                    sprPlayer->runAction(RepeatForever::create(Animate::create(animation)));
                }
                break;
                case  HeroState::THROUGH:
                {
                    sprPlayer->stopAllActions();
                    Vector< SpriteFrame*> frames = getAnimation("hero_through_0%d.png",3);
                    Animation* animation = Animation::createWithSpriteFrames(frames, 0.1f);
                    animation->retain();
                    sprPlayer->runAction(RepeatForever::create(Animate::create(animation)));
                }
                break;
                case HeroState::SHOOT:
                {
                    sprPlayer->stopAllActions();
                    Vector< SpriteFrame*> frames = getAnimation("hero_shooting_0%d.png",4);
                    Animation* animation = Animation::createWithSpriteFrames(frames, 0.1f);
                    animation->retain();
                    sprPlayer->runAction(RepeatForever::create(Animate::create(animation)));
                }
                break;
                case HeroState::FLY:
                {
                    sprPlayer->stopAllActions();
                    Vector< SpriteFrame*> frames = getAnimation("hero_flying_0%d.png",4);
                    Animation* animation = Animation::createWithSpriteFrames(frames, 0.1f);
                    animation->retain();
                    sprPlayer->runAction(RepeatForever::create(Animate::create(animation)));
                }
                break;
                case HeroState::JUMP:
                {
                    sprPlayer->stopAllActions();
                    Vector< SpriteFrame*> frames = getAnimation("hero_jump_0%d.png",4);
                    Animation* animation = Animation::createWithSpriteFrames(frames, 0.1f);
                    animation->retain();
                    sprPlayer->runAction(RepeatForever::create(Animate::create(animation)));
                }
                break;
                case HeroState::DIE:
                {
                    sprPlayer->stopAllActions();
                    Vector< SpriteFrame*> frames = getAnimation("hero_die_0%d.png",3);
                    Animation* animation = Animation::createWithSpriteFrames(frames, 0.1f);
                    animation->retain();
                    sprPlayer->runAction(Animate::create(animation));
                }
                break;
                case HeroState::STAND:
                    sprPlayer->stopAllActions();
                    Vector< SpriteFrame*> frames = getAnimation("hero_stand_0%d.png",5);
                    Animation* animation = Animation::createWithSpriteFrames(frames, 0.1f);
                    animation->retain();
                    //sprHero->runAction(Animate::create(animation));
                    sprPlayer->runAction(RepeatForever::create(Animate::create(animation)));
                break;

    }
}
Vector< SpriteFrame*> Player2D::getAnimation(const char *format, int count)
{
    auto spritecache = SpriteFrameCache::getInstance();
    Vector< SpriteFrame*> animFrames;
    char str[100];
    for(int i = 1; i <= count; i++)
    {
        sprintf(str, format, i);
        animFrames.pushBack(spritecache->getSpriteFrameByName(str));
    }
    return animFrames;
}
