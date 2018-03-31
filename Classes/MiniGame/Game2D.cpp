#include "Game2D.h"
#include "renderer/CCRenderer.h"
#include "2d/CCFontAtlasCache.h"

#include "AbstractScene.hpp"
#include "Player2D.hpp"
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
    stateHero = HeroState::LEFT;
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    DrawNode* drawNode = DrawNode::create();
    float x = visibleSize.width*2 - 100;
    float y = visibleSize.height;
    
    Vec2 vertices[] = { Vec2(5,5), Vec2(x-5,5), Vec2(x-5,y-5), Vec2(5,y-5) };
    drawNode->drawPoly(vertices, 4, true,  Color4F(CCRANDOM_0_1(), CCRANDOM_0_1(), CCRANDOM_0_1(), 1));

    this->addChild(drawNode);
    
    
    
    
    
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
    
    ui::Button* btnOK = (ui::Button*) rootNode->getChildByName("btnOK");
    btnOK->setPressedActionEnabled(true);
    btnOK->addTouchEventListener(CC_CALLBACK_2(Game2D::onA, this));
    
    
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
    cache->addSpriteFramesWithFile("res/plist/anim_hero_standing.plist");
    
    
    sprHero= Sprite::createWithSpriteFrameName("hero_run_01.png");
    //sprHero->setPosition(Vec2(visibleSize.width/2 + origin.x, 300));
    addChild(sprHero);
    //sprHero->stopAllActions();
    Vector< SpriteFrame*> frames = getAnimation("hero_stand_0%d.png",5);
    Animation* animation = Animation::createWithSpriteFrames(frames, 0.1f);
    animation->retain();
    //sprHero->runAction(Animate::create(animation));
    sprHero->runAction(RepeatForever::create(Animate::create(animation)));
    stateHero = HeroState::STAND;
//    SpriteBatchNode* spritebatch = SpriteBatchNode::create("res/plist/anim_hero_run.png");
//    spritebatch->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
//    addChild(spritebatch);
    
//    Sprite *sprite2 = Sprite::createWithSpriteFrameName("hero_run_01.png");
//    spritebatch->addChild(sprite2);
    auto btnAttach = ui::Button::create();
    btnAttach->setTouchEnabled(true);
    btnAttach->loadTextures("res/images/button/btn_red.png","res/image/button/btn_red2.png", "");
    btnAttach->setPosition(Vec2(btnAttach->getContentSize().width/2 ,700));
    btnAttach->setScale(0.5);
    btnAttach->addTouchEventListener(CC_CALLBACK_2(Game2D::onAttach, this));
    addChild(btnAttach);
    
    auto btnRun = ui::Button::create();
    btnRun->setTouchEnabled(true);
    btnRun->loadTextures("res/images/button/btn_red.png","res/image/button/btn_red2.png", "");
    btnRun->setPosition(Vec2(visibleSize.width - btnRun->getContentSize().width/2 ,700));
    btnRun->setScale(0.5);
    btnRun->addTouchEventListener(CC_CALLBACK_2(Game2D::onHurt, this));
    addChild(btnRun);
    
//    Vector< SpriteFrame*> fizzyFrames = getAnimation("hero_dizzy_0%d.png",5);
//    Animation* fizzyAnimation = Animation::createWithSpriteFrames(fizzyFrames, 0.1f);
//    fizzyAnimation->retain();
//    Sprite *fizzySprite = Sprite::createWithSpriteFrameName("hero_run_01.png");
//    fizzySprite->setPosition(Vec2(visibleSize.width/2 + origin.x, 300));
//    addChild(fizzySprite);
//    fizzySprite->setScale(1.5f);
//    fizzySprite->runAction(RepeatForever::create(Animate::create(fizzyAnimation)));
//
//    Vector< SpriteFrame*> splashFrames = getAnimation("hero_through_0%d.png",4);
//    Animation* splashAnimation = Animation::createWithSpriteFrames(splashFrames, 0.1f);
//    splashAnimation->retain();
//    Sprite *splashSprite = Sprite::createWithSpriteFrameName("hero_through_01.png");
//    splashSprite->setPosition(Vec2(visibleSize.width/2 + origin.x, 500));
//    addChild(splashSprite);
//    splashSprite->setScale(1.5f);
//
//    splashSprite->runAction(RepeatForever::create(Animate::create(splashAnimation)));
//
    
    Vector< SpriteFrame*> _walkFrames = getAnimation("hero_run_0%d.png",6);
    Animation* _walkAnimation = Animation::createWithSpriteFrames(_walkFrames, 0.1f);
    _walkAnimation->retain();
    sprHero->setScale(2.0f);
     this->schedule(schedule_selector(Game2D::update));
     AbstractScene::showHUD();
    
    sprPlayer = Player2D::create();
    sprPlayer->setScale(2.0f);
    
    sprPlayer->setPosition(Vec2(200, visibleSize.height/2 + 100));
    addChild(sprPlayer);
    
    
    _grossini = Sprite::create("images/grossini.png");
    //_grossini->retain();
    _grossini->setPosition(Vec2(visibleSize.width - 100 + origin.x, 100));
    
    _tamara = Sprite::create("images/grossinis_sister1.png");
    //_tamara->retain();
    _tamara->setPosition(Vec2(visibleSize.width/2 - 100 + origin.x, 300));
    
    _kathia = Sprite::create("images/grossinis_sister2.png");
    //_kathia->retain();
    _kathia->setPosition(Vec2(100 + origin.x, 500));
    
    addChild(_grossini, 1);
    addChild(_tamara, 2);
    addChild(_kathia, 3);
    
    auto actionTo = JumpTo::create(2, Vec2(300,300), 50, 4);
    auto actionBy = JumpBy::create(2, Vec2(-300,0), 50, 4);
    auto actionUp = JumpBy::create(2, Vec2(0,0), 80, 4);
    auto actionByBack = actionBy->reverse();
    
    //_tamara->runAction( RepeatForever::create(actionTo));
    _grossini->runAction(RepeatForever::create( Sequence::create(actionBy, actionByBack, nullptr)));
    //_kathia->runAction( RepeatForever::create(actionUp));
    
    
    auto move = MoveBy::create(3, Vec2(visibleSize.width-130, 0));
    
    auto move_ease_inout1 = EaseElasticInOut::create(move->clone(), 0.3f);
    auto move_ease_inout_back1 = move_ease_inout1->reverse();
    
    auto move_ease_inout2 = EaseElasticInOut::create(move->clone(), 0.45f);
    auto move_ease_inout_back2 = move_ease_inout2->reverse();
    
    auto move_ease_inout3 = EaseElasticInOut::create(move->clone(), 0.6f);
    auto move_ease_inout_back3 = move_ease_inout3->reverse();
    
    auto delay = DelayTime::create(0.25f);
    
    auto seq1 = Sequence::create(move_ease_inout1, delay, move_ease_inout_back1, delay->clone(), nullptr);
    auto seq2 = Sequence::create(move_ease_inout2, delay->clone(), move_ease_inout_back2, delay->clone(), nullptr);
    auto seq3 = Sequence::create(move_ease_inout3, delay->clone(), move_ease_inout_back3, delay->clone(), nullptr);
    
    //_grossini->runAction( RepeatForever::create(seq1));
    //_tamara->runAction( RepeatForever::create(seq2));
   _kathia->runAction( RepeatForever::create(seq3));
    // sprite 1
//    ccBezierConfig bezier;
//    bezier.controlPoint_1 = Vec2(0, visibleSize.height/2);
//    bezier.controlPoint_2 = Vec2(300, -visibleSize.height/2);
//    bezier.endPosition = Vec2(300,100);
    
//    auto bezierForward = BezierBy::create(3, bezier);
//    auto bezierBack = bezierForward->reverse();
//    auto rep = RepeatForever::create(Sequence::create( bezierForward, bezierBack, nullptr));
//    _tamara->runAction( rep);
    auto s = Director::getInstance()->getWinSize();
    
    auto array = PointArray::create(20);
    
    array->addControlPoint(Vec2(0, 0));
    array->addControlPoint(Vec2(s.width/2-30,0));
    array->addControlPoint(Vec2(s.width/2-30,s.height-80));
    array->addControlPoint(Vec2(0, s.height-80));
    array->addControlPoint(Vec2(0, 0));
    auto *action2 = CardinalSplineBy::create(3, array, 1);
    auto reverse2 = action2->reverse();
    
    auto seq5 = Sequence::create(action2, reverse2, nullptr);
    
    _tamara->setPosition(s.width/2,50);
    
    _tamara->runAction(RepeatForever::create(seq5));
    
//    _tamara->runAction(RepeatForever::create(Sequence::create(
//                                                              MoveBy::create(0.05f, Vec2(10,0)),
//                                                              MoveBy::create(0.05f, Vec2(-10,0)),
//                                                              nullptr)));
    
    auto drawNode2 = DrawNode::create();
    drawNode2->setPosition(Vec2(s.width/2,50));
    drawNode2->drawCardinalSpline(array, 1, 100, Color4F(0.0, 0.0, 1.0, 1.0));
    this->addChild(drawNode2);
    
    auto label =  Label::createWithTTF("xchip.ios.com", "fonts/arial.ttf", 24);
    label->enableOutline(Color4B::ORANGE,1);
    label->setPosition(s.width/2, s.height/2 -30);
    addChild(label);
    
    auto label1 = Label::createWithBMFont("fonts/futura-48.fnt", "cocos2d-x sample");
    // Demo for reloadFontAtlasFNT function, after it been called, all UI widget
    //  use the special font must reset font, because the old one is invalid.
    FontAtlasCache::reloadFontAtlasFNT("fonts/futura-48.fnt");
    label1->setBMFontFilePath("fonts/futura-48.fnt");
    addChild(label1);
    label1->setPosition(Vec2(s.width / 2, s.height * 0.4f));
    
    auto label2 = Label::createWithBMFont("fonts/konqa32.fnt", "NYC STUDIO");
    addChild(label2);
    label2->setPosition(Vec2(s.width/2, s.height/2));
    //label2->enableOutline(Color4B::ORANGE,1);
    
    cocos2d::ui::Scale9Sprite* sprBg = cocos2d::ui::Scale9Sprite::create("images/bullet01.png");
    //sprBg->setScale(0);
    sprBg->setContentSize(Size(500, 100));
    sprBg->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
    sprBg->setPosition(Vec2(200, s.height/5));
    this->addChild(sprBg);
    
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
   
//    switch (eEventType)
//    {
//        case ui::Widget::TouchEventType::BEGAN:
//            if(sprHero!= nullptr)
//            {
//                if(stateHero==0)
//                {
//                    sprHero->stopAllActions();
//                    Vector< SpriteFrame*> frames = getAnimation("hero_run_0%d.png",6);
//                    Animation* animation = Animation::createWithSpriteFrames(frames, 0.1f);
//                    animation->retain();
//                    sprHero->runAction(RepeatForever::create(Animate::create(animation)));
//                }
//                else if(stateHero==1)
//                {
//                    sprHero->stopAllActions();
//                    Vector< SpriteFrame*> frames = getAnimation("hero_dizzy_0%d.png",5);
//                    Animation* animation = Animation::createWithSpriteFrames(frames, 0.1f);
//                    animation->retain();
//                    sprHero->runAction(RepeatForever::create(Animate::create(animation)));
//                }
//                else if(stateHero==2)
//                {
//                    sprHero->stopAllActions();
//                    Vector< SpriteFrame*> frames = getAnimation("hero_through_0%d.png",3);
//                    Animation* animation = Animation::createWithSpriteFrames(frames, 0.1f);
//                    animation->retain();
//                    sprHero->runAction(RepeatForever::create(Animate::create(animation)));
//                }
//                else if(stateHero==3)
//                {
//                    sprHero->stopAllActions();
//                    Vector< SpriteFrame*> frames = getAnimation("hero_shooting_0%d.png",4);
//                    Animation* animation = Animation::createWithSpriteFrames(frames, 0.1f);
//                    animation->retain();
//                    sprHero->runAction(RepeatForever::create(Animate::create(animation)));
//                }
//                else if(stateHero==4)
//                {
//                    sprHero->stopAllActions();
//                    Vector< SpriteFrame*> frames = getAnimation("hero_flying_0%d.png",4);
//                    Animation* animation = Animation::createWithSpriteFrames(frames, 0.1f);
//                    animation->retain();
//                    sprHero->runAction(RepeatForever::create(Animate::create(animation)));
//                }
//                else if(stateHero==5)
//                {
//                    sprHero->stopAllActions();
//                    Vector< SpriteFrame*> frames = getAnimation("hero_jump_0%d.png",4);
//                    Animation* animation = Animation::createWithSpriteFrames(frames, 0.1f);
//                    animation->retain();
//                    sprHero->runAction(RepeatForever::create(Animate::create(animation)));
//                }
//                else if(stateHero==6)
//                {
//                    sprHero->stopAllActions();
//                    Vector< SpriteFrame*> frames = getAnimation("hero_die_0%d.png",3);
//                    Animation* animation = Animation::createWithSpriteFrames(frames, 0.1f);
//                    animation->retain();
//                    sprHero->runAction(Animate::create(animation));
//                }
//
//            }
//            stateHero++;
//            if(stateHero > 6) stateHero = 0;
//            break;
//        case ui::Widget::TouchEventType::ENDED:
//            break;
//        default:
//            break;
//    }
  
    
}
void Game2D::onHurt(Ref* pSender, ui::Widget::TouchEventType eEventType)
{
    if( stateHero != HeroState::HURT)
    {
        sprHero->stopAllActions();
        Vector< SpriteFrame*> frames = getAnimation("hero_dizzy_0%d.png",5);
        Animation* animation = Animation::createWithSpriteFrames(frames, 0.15f);
        animation->retain();
        sprHero->runAction(RepeatForever::create(Animate::create(animation)));
        stateHero = HeroState::HURT;
    }
}
void Game2D::onUp(Ref* pSender, ui::Widget::TouchEventType eEventType){
  
    sprPlayer->setPositionY(sprPlayer->getPositionY()+10);
            
}
void Game2D::onDown(Ref* pSender, ui::Widget::TouchEventType eEventType)
{
    sprPlayer->setPositionY(sprPlayer->getPositionY()-10);
    
}
void Game2D::onLeft(Ref* pSender, ui::Widget::TouchEventType eEventType)
{
    if(!sprPlayer->isFlippedX())
        sprPlayer->setFlippedX(true);
    sprPlayer->setStatus(HeroState::SHOOT);
    sprPlayer->setPositionX(sprPlayer->getPositionX()-10);
}
void Game2D::onRight(Ref* pSender, ui::Widget::TouchEventType eEventType)
{
    if(sprPlayer->isFlippedX())
        sprPlayer->setFlippedX(false);
    sprPlayer->setStatus(HeroState::SHOOT);
    sprPlayer->setPositionX(sprPlayer->getPositionX()+10);
}
void Game2D::onA(Ref* pSender, ui::Widget::TouchEventType eEventType)
{
    switch (eEventType)
    {
        case ui::Widget::TouchEventType::BEGAN:
            if( stateHero != HeroState::SHOOT)
            {
                sprHero->stopAllActions();
                Vector< SpriteFrame*> frames = getAnimation("hero_shooting_0%d.png",4);
                Animation* animation = Animation::createWithSpriteFrames(frames, 0.1f);
                animation->retain();
                sprHero->runAction(RepeatForever::create(Animate::create(animation)));
                 stateHero = HeroState::SHOOT;
            }
            break;
        case ui::Widget::TouchEventType::ENDED:
            if( stateHero != HeroState::STAND)
            {
                sprHero->stopAllActions();
                Vector< SpriteFrame*> frames = getAnimation("hero_stand_0%d.png",5);
                Animation* animation = Animation::createWithSpriteFrames(frames, 0.1f);
                animation->retain();
                //sprHero->runAction(Animate::create(animation));
                sprHero->runAction(RepeatForever::create(Animate::create(animation)));
                stateHero = HeroState::STAND;
            }
            break;
    }
    
}
void Game2D::onB(Ref* pSender, ui::Widget::TouchEventType eEventType)
{
    switch (eEventType)
    {
        case ui::Widget::TouchEventType::BEGAN:
            playerStatus++;
            if(playerStatus > (int)HeroState::END) playerStatus = 0;
            log("status...%d", playerStatus);
            sprPlayer->setStatus(HeroState (playerStatus));
            break;
    }
//        if( stateHero != HeroState::STAND)
//        {
//            sprHero->stopAllActions();
//            Vector< SpriteFrame*> frames = getAnimation("hero_stand_0%d.png",5);
//            Animation* animation = Animation::createWithSpriteFrames(frames, 0.1f);
//            animation->retain();
//            //sprHero->runAction(Animate::create(animation));
//             sprHero->runAction(RepeatForever::create(Animate::create(animation)));
//             stateHero = HeroState::STAND;
//        }
//    if( stateHero != HeroState::DIE)
//    {
//        sprHero->stopAllActions();
//        Vector< SpriteFrame*> frames = getAnimation("hero_die_0%d.png",3);
//        Animation* animation = Animation::createWithSpriteFrames(frames, 0.1f);
//        animation->retain();
//        sprHero->runAction(Animate::create(animation));
//         stateHero = HeroState::DIE;
//    }
}
void Game2D::onC(Ref* pSender, ui::Widget::TouchEventType eEventType){
    if( stateHero != HeroState::ATTACH)
    {
        sprHero->stopAllActions();
        Vector< SpriteFrame*> frames = getAnimation("hero_through_0%d.png",3);
        Animation* animation = Animation::createWithSpriteFrames(frames, 0.1f);
        animation->retain();
        sprHero->runAction(RepeatForever::create(Animate::create(animation)));
         stateHero = HeroState::ATTACH;
    }
}
void Game2D::onD(Ref* pSender, ui::Widget::TouchEventType eEventType){
    if( stateHero != HeroState::HURT)
    {
        sprHero->stopAllActions();
        Vector< SpriteFrame*> frames = getAnimation("hero_dizzy_0%d.png",5);
        Animation* animation = Animation::createWithSpriteFrames(frames, 0.1f);
        animation->retain();
        sprHero->runAction(RepeatForever::create(Animate::create(animation)));
         stateHero = HeroState::HURT;
    }
}
void Game2D::update(float dt)
{
    //log("update...%f", dt);
}
