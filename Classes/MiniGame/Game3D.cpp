
#include "MainScene.hpp"
#include "ui/CocosGUI.h"
#include "../cocos/editor-support/cocostudio/CocoStudio.h"
#include "Game3D.hpp"
#include "ShaderNode.hpp"
USING_NS_CC;

Scene* Game3D::createScene()
{
    //return Game3D::create();
    auto scene = Scene::create();
    auto layer = Game3D::create();
    scene->addChild(layer);
    return scene;
    
}

bool Game3D::init()
{
    if ( !AbstractScene::init() )
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    initComponents();
    this->schedule(schedule_selector(Game3D::update));
    return true;
}

void Game3D::initComponents()
{
    std::string fileName = "Sprite3DTest/tortoise.c3b";
    auto sprite = Sprite3D::create(fileName);
    sprite->setScale(0.3f);
    auto s = Director::getInstance()->getWinSize();
    sprite->setPosition(Vec2(visibleSize.width /2, visibleSize.height / 2));
    addChild(sprite,Z_ODER_HUD);
    _sprite = sprite;
    auto animation = Animation3D::create(fileName);
    if (animation)
    {
        auto animate = Animate3D::create(animation, 0.f, 1.933f);
        _swim = RepeatForever::create(animate);
        sprite->runAction(_swim);
        
        _swim->retain();
        _hurt = Animate3D::create(animation, 1.933f, 2.8f);
        _hurt->retain();
        _state = State::SWIMMING;
    }
    
    _moveAction = MoveTo::create(4.f, Vec2(s.width / 5.f, s.height / 2.f));
    _moveAction->retain();
    auto seq = Sequence::create(_moveAction, CallFunc::create(CC_CALLBACK_0(Game3D::reachEndCallBack, this)), nullptr);
    seq->setTag(100);
    sprite->runAction(seq);
    _elapseTransTime = 0;
    
    
    
    
    auto sprite_orc = Sprite3D::create("Sprite3DTest/orc.c3b");
    sprite_orc->setScale(10);
    sprite_orc->setRotation3D(Vec3(0,180,0));
    addChild(sprite_orc);
    sprite_orc->setPosition( Vec2(visibleSize.width /2, visibleSize.height / 2) );
    
    auto sp = Sprite3D::create("Sprite3DTest/axe.c3b");
    sprite_orc->getAttachNode("Bip001 R Hand")->addChild(sp);
    
    auto animation_orc = Animation3D::create("Sprite3DTest/orc.c3b");
    if (animation_orc)
    {
        auto animate = Animate3D::create(animation_orc);
        sprite_orc->runAction(RepeatForever::create(animate));
    }
    
    auto sn = ShaderNode::shaderNodeWithVertex("", "Shaders/shadertoy_Glow.fsh");
    sn->setPosition(Vec2(visibleSize.width/4, visibleSize.height/4));
    sn->setContentSize(Size(visibleSize.width/4,visibleSize.height/4));
    addChild(sn);
    
    
    AbstractScene::showHUD();
    
}
void Game3D::update(float dt)
{
    log("update...%f", dt);
    if (_state == State::HURT_TO_SWIMMING)
    {
        _elapseTransTime += dt;
        
        if (_elapseTransTime >= Animate3D::getTransitionTime())
        {
            _sprite->stopAction(_hurt);
            _state = State::SWIMMING;
        }
    }
    else if (_state == State::SWIMMING_TO_HURT)
    {
        _elapseTransTime += dt;
        if (_elapseTransTime >= Animate3D::getTransitionTime())
        {
            _sprite->stopAction(_swim);
            _state = State::HURT;
        }
    }
    
}
void Game3D::reachEndCallBack()
{
    auto s = Director::getInstance()->getWinSize();
    _sprite->stopActionByTag(100);
    auto inverse = MoveTo::create(4.f, Vec2(s.width - _sprite->getPositionX(), s.height / 2.f));
    inverse->retain();
    _moveAction->release();
    _moveAction = inverse;
    auto rot = RotateBy::create(1.f, Vec3(0.f, 180.f, 0.f));
    auto seq = Sequence::create(rot, _moveAction, CallFunc::create(CC_CALLBACK_0(Game3D::reachEndCallBack, this)), nullptr);
    seq->setTag(100);
    _sprite->runAction(seq);
}
void Game3D::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
    

    
}
