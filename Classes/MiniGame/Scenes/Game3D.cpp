
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
    sprite_orc->setPosition( Vec2(1000, 100) );
    
    auto sp = Sprite3D::create("Sprite3DTest/axe.c3b");
    sprite_orc->getAttachNode("Bip001 R Hand")->addChild(sp);
    
    auto animation_orc = Animation3D::create("Sprite3DTest/orc.c3b");
    if (animation_orc)
    {
        auto animate = Animate3D::create(animation_orc);
        sprite_orc->runAction(RepeatForever::create(animate));
    }
    
    auto sn = ShaderNode::shaderNodeWithVertex("", "Shaders/shadertoy_Glow.fsh");
    sn->setPosition(Vec2(100, 20));
    sn->setContentSize(Size(visibleSize.width/4,visibleSize.height/4));
    addChild(sn);
    
    
    AbstractScene::showHUD();
    
    
    
    //auto s = Director::getInstance()->getWinSize();
    
    auto sprite3 = Sprite3D::create("Sprite3DTest/box_VertexCol.c3t");
    sprite3->setPosition(Vec2(0, 0));
    sprite3->setScale(1.0f);
    sprite3->setCameraMask(2);
    auto mat = Sprite3DMaterial::createWithFilename("Sprite3DTest/VertexColor.material");
    sprite3->setMaterial(mat);
    sprite3->runAction(RepeatForever::create(RotateBy::create(1.0f, Vec3(10.0f, 50.0f, 10.0f))));
    
    this->addChild(sprite3);
    
    //setup camera
    auto camera = Camera::createPerspective(40, s.width / s.height, 0.01f, 1000.f);
    camera->setCameraFlag(CameraFlag::USER1);
    camera->setPosition3D(Vec3(0.0f, 0.0f, 10.f));
    camera->lookAt(Vec3(0.f, 0.f, 0.f));
    addChild(camera);
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    _backToForegroundListener = EventListenerCustom::create(EVENT_COME_TO_FOREGROUND,
                                                            [=](EventCustom*)
                                                            {
                                                                auto mat = Sprite3DMaterial::createWithFilename("Sprite3DTest/VertexColor.material");
                                                                sprite->setMaterial(mat);
                                                            }
                                                            );
    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(_backToForegroundListener, 1);
#endif
    
//    
////==================
//    auto _camera = Camera::createPerspective(60, visibleSize.width/visibleSize.height, 0.1f, 200);
//    _camera->setCameraFlag(CameraFlag::USER1);
//    // create a teapot
//    auto teapot = Sprite3D::create("Sprite3DTest/teapot.c3b");
//    auto matTeaPot = Sprite3DMaterial::createWithFilename("Sprite3DTest/BasicToon.material");
//    _glState = matTeaPot->getTechniqueByIndex(0)->getPassByIndex(0)->getGLProgramState();
//    teapot->setMaterial(matTeaPot);
//    
//    teapot->setPosition3D(Vec3(0,-5,-20));
//    teapot->setRotation3D(Vec3(-90,180,0));
//    auto rotate_action = RotateBy::create(1.5,Vec3(0,30,0));
//    teapot->runAction(RepeatForever::create(rotate_action));
//    addChild(teapot);
//    addChild(_camera);
//    setCameraMask(2);
//#if (CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID || CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
//    _backToForegroundListener = EventListenerCustom::create(EVENT_COME_TO_FOREGROUND,
//                                                            [=](EventCustom*)
//                                                            {
//                                                                auto mat = Sprite3DMaterial::createWithFilename("Sprite3DTest/BasicToon.material");
//                                                                _glState = matTeaPot->getTechniqueByIndex(0)->getPassByIndex(0)->getGLProgramState();
//                                                                teapot->setMaterial(matTeaPot);
//                                                            }
//                                                            );
//    Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(_backToForegroundListener, -1);
//#endif
//    
 //=========
    Sprite3DNormalMappingTest();
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
void Game3D::Sprite3DNormalMappingTest()
{
    auto s = Director::getInstance()->getWinSize();
    
    {
        auto sprite = Sprite3D::create("Sprite3DTest/sphere.c3b");
        sprite->setPosition(Vec2(-30, 0));
        sprite->setRotation3D(Vec3(90.0f, 0.0f, 0.0f));
        sprite->setScale(2.0);
        sprite->setCameraMask(2);
        sprite->setTexture("Sprite3DTest/brickwork-texture.jpg");
        addChild(sprite);
    }
    
    int maxAttributes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &maxAttributes);
    CCASSERT(maxAttributes > 8, "attributes supported must be greater than 8");
    if (maxAttributes > 8)
    {
        auto sprite = Sprite3D::create("Sprite3DTest/sphere_bumped.c3b");
        sprite->setPosition(Vec2(30, 0));
        sprite->setRotation3D(Vec3(90.0f, 0.0f, 0.0f));
        sprite->setScale(20.0);
        sprite->setCameraMask(2);
        sprite->setTexture("Sprite3DTest/brickwork-texture.jpg");
        addChild(sprite);
    }
    
    float radius = 100.0;
    
    PointLight* light = PointLight::create(Vec3(0.0, 0.0, 0.0), Color3B(255, 255, 255), 1000);
    light->runAction(RepeatForever::create(Sequence::create(CallFuncN::create([radius](Node *node){
        static float angle = 0.0;
        static bool reverseDir = false;
        node->setPosition3D(Vec3(radius * cos(angle), 0.0f, radius * sin(angle)));
        if (reverseDir){
            angle -= 0.01f;
            if (angle < 0.0)
                reverseDir = false;
        }
        else{
            angle += 0.01f;
            if (3.14159 < angle)
                reverseDir = true;
        }
    }), nullptr)));
    //setup camera
    auto camera = Camera::createPerspective(60.0, s.width / s.height, 1.0f, 1000.f);
    camera->setCameraFlag(CameraFlag::USER1);
    camera->setPosition3D(Vec3(0.f, 0.f, 100.f));
    camera->lookAt(Vec3(0.f, 0.f, 0.f));
    addChild(camera);
    
    addChild(light);
}



