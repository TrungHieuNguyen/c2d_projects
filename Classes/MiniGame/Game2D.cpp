#include "Game2D.h"
#include "AbstractScene.hpp"

USING_NS_CC;

using namespace cocostudio::timeline;

Scene* Game2D::createScene()
{
    auto scene = Scene::create();
    auto layer = Game2D::create();
    scene->addChild(layer);
    return scene;
}

bool Game2D::init()
{
   
    if ( !AbstractScene::init())
    {
        return false;
    }
    stateHero = 0;
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto rootNode = CSLoader::createNode(SCENE_GAME2D_CSB);
   
    addChild(rootNode,-1);
    
    ui::Button* btnUp = (ui::Button*) rootNode->getChildByName("btnUp");
    btnUp->setPressedActionEnabled(true);
    btnUp->addTouchEventListener(CC_CALLBACK_2(Game2D::onUp, this));
    
    ui::Button* btnDown = (ui::Button*) rootNode->getChildByName("btnDown");
    btnDown->setPressedActionEnabled(true);
    btnDown->addTouchEventListener(CC_CALLBACK_2(Game2D::onDown, this));
    
    ui::Button* btnLeft = (ui::Button*) rootNode->getChildByName("btnLeft");
    btnLeft->setPressedActionEnabled(true);
    btnLeft->addTouchEventListener(CC_CALLBACK_2(Game2D::onLeft, this));
    
    ui::Button* btnRight = (ui::Button*) rootNode->getChildByName("btnRight");
    btnRight->setPressedActionEnabled(true);
    btnRight->addTouchEventListener(CC_CALLBACK_2(Game2D::onRight, this));
    
    
    ui::Button* btnA = (ui::Button*) rootNode->getChildByName("btnA");
    btnA->setPressedActionEnabled(true);
    btnA->addTouchEventListener(CC_CALLBACK_2(Game2D::onA, this));
    
    ui::Button* btnB = (ui::Button*) rootNode->getChildByName("btnB");
    btnB->setPressedActionEnabled(true);
    btnB->addTouchEventListener(CC_CALLBACK_2(Game2D::onB, this));
    
    ui::Button* btnC = (ui::Button*) rootNode->getChildByName("btnC");
    btnC->setPressedActionEnabled(true);
    btnC->addTouchEventListener(CC_CALLBACK_2(Game2D::onC, this));
    
    ui::Button* btnD = (ui::Button*) rootNode->getChildByName("btnD");
    btnD->setPressedActionEnabled(true);
    btnD->addTouchEventListener(CC_CALLBACK_2(Game2D::onD, this));
    
    SpriteFrameCache* cache = SpriteFrameCache::getInstance();
    cache->addSpriteFramesWithFile("res/plist/anim_hero_run.plist");
    cache->addSpriteFramesWithFile("res/plist/anim_hero_dizzy.plist");
    cache->addSpriteFramesWithFile("res/plist/anim_hero_splash.plist");
    cache->addSpriteFramesWithFile("res/plist/anim_hero_jump.plist");
    cache->addSpriteFramesWithFile("res/plist/anim_hero_flying.plist");
    cache->addSpriteFramesWithFile("res/plist/anim_hero_die.plist");
    cache->addSpriteFramesWithFile("res/plist/anim_hero_shoot.plist");
    
    sprHero= Sprite::createWithSpriteFrameName("hero_run_01.png");
    sprHero->setPosition(Vec2(visibleSize.width/2 + origin.x, 200));
    addChild(sprHero);
    
    SpriteBatchNode* spritebatch = SpriteBatchNode::create("res/plist/anim_hero_run.png");
    spritebatch->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    addChild(spritebatch);
    
//    Sprite *sprite2 = Sprite::createWithSpriteFrameName("hero_run_01.png");
//    spritebatch->addChild(sprite2);
    auto btnAttach = ui::Button::create();
    btnAttach->setTouchEnabled(true);
    btnAttach->loadTextures("res/image/button/btn_red.png","res/image/button/btn_red2.png", "");
    btnAttach->setPosition(Vec2(btnAttach->getContentSize().width/2 ,700));
    btnAttach->setScale(0.5);
    btnAttach->addTouchEventListener(CC_CALLBACK_2(Game2D::onAttach, this));
    addChild(btnAttach);
    
    
    
    auto btnRun = ui::Button::create();
    btnRun->setTouchEnabled(true);
    btnRun->loadTextures("res/image/button/btn_red.png","res/image/button/btn_red2.png", "");
    btnRun->setPosition(Vec2(visibleSize.width - btnRun->getContentSize().width/2 ,700));
    btnRun->setScale(0.5);
    btnRun->addTouchEventListener(CC_CALLBACK_2(Game2D::onHurt, this));
    addChild(btnRun);
    
    Vector< SpriteFrame*> fizzyFrames = getAnimation("hero_dizzy_0%d.png",5);
    Animation* fizzyAnimation = Animation::createWithSpriteFrames(fizzyFrames, 0.1f);
    fizzyAnimation->retain();
    Sprite *fizzySprite = Sprite::createWithSpriteFrameName("hero_run_01.png");
    fizzySprite->setPosition(Vec2(visibleSize.width/2 + origin.x, 300));
    addChild(fizzySprite);
    fizzySprite->setScale(1.5f);
    fizzySprite->runAction(RepeatForever::create(Animate::create(fizzyAnimation)));
    
    Vector< SpriteFrame*> splashFrames = getAnimation("hero_through_0%d.png",4);
    Animation* splashAnimation = Animation::createWithSpriteFrames(splashFrames, 0.1f);
    splashAnimation->retain();
    Sprite *splashSprite = Sprite::createWithSpriteFrameName("hero_through_01.png");
    splashSprite->setPosition(Vec2(visibleSize.width/2 + origin.x, 500));
    addChild(splashSprite);
    splashSprite->setScale(1.5f);
    
    splashSprite->runAction(RepeatForever::create(Animate::create(splashAnimation)));
    
    
    Vector< SpriteFrame*> _walkFrames = getAnimation("hero_run_0%d.png",6);
    Animation* _walkAnimation = Animation::createWithSpriteFrames(_walkFrames, 0.1f);
    _walkAnimation->retain();
    sprHero->setScale(1.5f);
    
//    //sprite->runAction(RepeatForever::create(Animate::create(_walkAnimation)));
//    auto movement = MoveTo::create(15, Vec2(800,sprHero->getPosition().y));
//    auto resetPosition = MoveTo::create(0, Vec2(0,sprHero->getPosition().y));
//    auto sequence = Sequence::create(movement, resetPosition, NULL);
//    //sprite->runAction(RepeatForever::create(sequence));
//    animateRun = Animate::create(_walkAnimation);
//    animateAttach = Animate::create(splashAnimation);
//    animateDizzy = Animate::create(fizzyAnimation);
//    auto hero_sequence = Sequence::create(movement, animateAttach, animateDizzy,NULL);
//    sprHero->runAction(RepeatForever::create(hero_sequence));
     this->schedule(schedule_selector(Game2D::update));
     AbstractScene::showHUD();
    return true;
}
 Vector< SpriteFrame*> Game2D::getAnimation(const char *format, int count)
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
void Game2D::onAttach(Ref* pSender, ui::Widget::TouchEventType eEventType)
{
   
    switch (eEventType)
    {
        case ui::Widget::TouchEventType::BEGAN:
            if(sprHero!= nullptr)
            {
                if(stateHero==0)
                {
                    sprHero->stopAllActions();
                    Vector< SpriteFrame*> frames = getAnimation("hero_run_0%d.png",6);
                    Animation* animation = Animation::createWithSpriteFrames(frames, 0.1f);
                    animation->retain();
                    sprHero->runAction(RepeatForever::create(Animate::create(animation)));
                }
                else if(stateHero==1)
                {
                    sprHero->stopAllActions();
                    Vector< SpriteFrame*> frames = getAnimation("hero_dizzy_0%d.png",5);
                    Animation* animation = Animation::createWithSpriteFrames(frames, 0.1f);
                    animation->retain();
                    sprHero->runAction(RepeatForever::create(Animate::create(animation)));
                }
                else if(stateHero==2)
                {
                    sprHero->stopAllActions();
                    Vector< SpriteFrame*> frames = getAnimation("hero_through_0%d.png",3);
                    Animation* animation = Animation::createWithSpriteFrames(frames, 0.1f);
                    animation->retain();
                    sprHero->runAction(RepeatForever::create(Animate::create(animation)));
                }
                else if(stateHero==3)
                {
                    sprHero->stopAllActions();
                    Vector< SpriteFrame*> frames = getAnimation("hero_shooting_0%d.png",4);
                    Animation* animation = Animation::createWithSpriteFrames(frames, 0.1f);
                    animation->retain();
                    sprHero->runAction(RepeatForever::create(Animate::create(animation)));
                }
                else if(stateHero==4)
                {
                    sprHero->stopAllActions();
                    Vector< SpriteFrame*> frames = getAnimation("hero_flying_0%d.png",4);
                    Animation* animation = Animation::createWithSpriteFrames(frames, 0.1f);
                    animation->retain();
                    sprHero->runAction(RepeatForever::create(Animate::create(animation)));
                }
                else if(stateHero==5)
                {
                    sprHero->stopAllActions();
                    Vector< SpriteFrame*> frames = getAnimation("hero_jump_0%d.png",4);
                    Animation* animation = Animation::createWithSpriteFrames(frames, 0.1f);
                    animation->retain();
                    sprHero->runAction(RepeatForever::create(Animate::create(animation)));
                }
                else if(stateHero==6)
                {
                    sprHero->stopAllActions();
                    Vector< SpriteFrame*> frames = getAnimation("hero_die_0%d.png",3);
                    Animation* animation = Animation::createWithSpriteFrames(frames, 0.1f);
                    animation->retain();
                    sprHero->runAction(Animate::create(animation));
                }
                
            }
            stateHero++;
            if(stateHero > 6) stateHero = 0;
            break;
        case ui::Widget::TouchEventType::ENDED:
            break;
        default:
            break;
    }
  
    
}
void Game2D::onHurt(Ref* pSender, ui::Widget::TouchEventType eEventType)
{
    sprHero->stopAllActions();
    Vector< SpriteFrame*> frames = getAnimation("hero_dizzy_0%d.png",5);
    Animation* animation = Animation::createWithSpriteFrames(frames, 0.1f);
    animation->retain();
    sprHero->runAction(RepeatForever::create(Animate::create(animation)));
}
void Game2D::onUp(Ref* pSender, ui::Widget::TouchEventType eEventType){
    sprHero->stopAllActions();
    Vector< SpriteFrame*> frames = getAnimation("hero_flying_0%d.png",4);
    Animation* animation = Animation::createWithSpriteFrames(frames, 0.1f);
    animation->retain();
    sprHero->runAction(RepeatForever::create(Animate::create(animation)));
    
}
void Game2D::onDown(Ref* pSender, ui::Widget::TouchEventType eEventType){
    sprHero->stopAllActions();
    Vector< SpriteFrame*> frames = getAnimation("hero_jump_0%d.png",4);
    Animation* animation = Animation::createWithSpriteFrames(frames, 0.1f);
    animation->retain();
    sprHero->runAction(RepeatForever::create(Animate::create(animation)));
}
void Game2D::onLeft(Ref* pSender, ui::Widget::TouchEventType eEventType){
    sprHero->stopAllActions();
    Vector< SpriteFrame*> frames = getAnimation("hero_run_0%d.png",6);
    Animation* animation = Animation::createWithSpriteFrames(frames, 0.1f);
    sprHero->setFlippedX(true);
    animation->retain();
    sprHero->runAction(RepeatForever::create(Animate::create(animation)));
}
void Game2D::onRight(Ref* pSender, ui::Widget::TouchEventType eEventType){
    sprHero->stopAllActions();
    Vector< SpriteFrame*> frames = getAnimation("hero_run_0%d.png",6);
    Animation* animation = Animation::createWithSpriteFrames(frames, 0.1f);
    animation->retain();
    sprHero->setFlippedX(false);
    sprHero->runAction(RepeatForever::create(Animate::create(animation)));
}
void Game2D::onA(Ref* pSender, ui::Widget::TouchEventType eEventType){
    sprHero->stopAllActions();
    Vector< SpriteFrame*> frames = getAnimation("hero_shooting_0%d.png",4);
    Animation* animation = Animation::createWithSpriteFrames(frames, 0.1f);
    animation->retain();
    sprHero->runAction(RepeatForever::create(Animate::create(animation)));
}
void Game2D::onB(Ref* pSender, ui::Widget::TouchEventType eEventType){
    sprHero->stopAllActions();
    Vector< SpriteFrame*> frames = getAnimation("hero_die_0%d.png",3);
    Animation* animation = Animation::createWithSpriteFrames(frames, 0.1f);
    animation->retain();
    sprHero->runAction(Animate::create(animation));
}
void Game2D::onC(Ref* pSender, ui::Widget::TouchEventType eEventType){
    sprHero->stopAllActions();
    Vector< SpriteFrame*> frames = getAnimation("hero_through_0%d.png",3);
    Animation* animation = Animation::createWithSpriteFrames(frames, 0.1f);
    animation->retain();
    sprHero->runAction(RepeatForever::create(Animate::create(animation)));
}
void Game2D::onD(Ref* pSender, ui::Widget::TouchEventType eEventType){
    sprHero->stopAllActions();
    Vector< SpriteFrame*> frames = getAnimation("hero_dizzy_0%d.png",5);
    Animation* animation = Animation::createWithSpriteFrames(frames, 0.1f);
    animation->retain();
    sprHero->runAction(RepeatForever::create(Animate::create(animation)));
}
void Game2D::update(float dt)
{
    log("update...%f", dt);
}
