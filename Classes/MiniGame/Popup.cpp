//
//  Popup.cpp
//  ChipGame
//
//  Created by Nguyen Trung Hieu on 7/14/17.
//
//

#include "Popup.hpp"
Vector<Popup*> *Popup::listPopups = new Vector<Popup*>();

Popup::Popup()
{
    spBgFull = nullptr;
    layerBG = nullptr;

}
Popup::~Popup(){}
void Popup::initComponent()
{
}
void Popup::onTouchClose(Ref* pSender, cocos2d::ui::Widget::TouchEventType type)
{
    cocos2d::ui::Button* selectedBtn = (cocos2d::ui::Button*)pSender;
    switch (type)
    {
        case cocos2d::ui::Widget::TouchEventType::BEGAN:
            selectedBtn->setColor(Color3B(170, 170, 170));
            break;
        case cocos2d::ui::Widget::TouchEventType::ENDED:
            selectedBtn->setColor(Color3B(255, 255, 255));
            close();
            break;
        case cocos2d::ui::Widget::TouchEventType::CANCELED:
            selectedBtn->setColor(Color3B(255, 255, 255));
            break;
        default:
            break;
    }
}
void Popup::close()
{
    removeFromParentAndCleanup(true);
    listPopups->eraseObject(this, true);
}

bool Popup::init()
{
    return initWithColor(Color4B(100, 100, 100, 0));
}
bool Popup::initWithColor(Color4B color)
{
    bool pRet = false;
    if (LayerColor::initWithColor(color));
    {
        listPopups->pushBack(this);
        setAnchorPoint(Vec2::ANCHOR_MIDDLE);
        setIgnoreAnchorPointForPosition(false);
        initComponent();
        pRet = true;
    }
    return pRet;
}
void Popup::initTitle(const char * title, Point p)
{
    lbTitle = Label::createWithTTF(title, "", 60);
    lbTitle->setColor(Color3B::BLACK);
    lbTitle->setIgnoreAnchorPointForPosition(false);
    lbTitle->setAnchorPoint(Point(0.5f, 0.5f));
    lbTitle->setPosition(p);
    addChild(lbTitle);
    
}
void Popup::setBackground()
{
    Size size = getContentSize();
    auto visibleSize = Director::getInstance()->getVisibleSize();
    spBgFull = Sprite::create("platform/hallBg.png");
    spBgFull->setPosition(Vec2(size.width / 2, 720 / 2));
    float _xScale = visibleSize.width / spBgFull->getContentSize().width;
    float _yScale = visibleSize.height / spBgFull->getContentSize().height;
    spBgFull->setScaleX(_xScale);
    spBgFull->setScaleY(_yScale);
    spBgFull->setName("BackGround");
    this->addChild(spBgFull, -1);
}
void Popup::initBgDark()
{
    Size size =  Director::getInstance()->getOpenGLView()->getVisibleSize();
    LayerColor * layerBg = LayerColor::create(Color4B(0,0,0, 150));
    layerBg->setIgnoreAnchorPointForPosition(false);
    layerBg->setOpacity(0);
    layerBg->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    layerBg->setTag(1001);
    addChild(layerBg, -1);
    layerBg->setPosition(getContentSize()/2);
    layerBg->setContentSize(size/2);
}
void Popup::fadeOutBgDark()
{
    if(this->getChildByTag(1001))
    {
        this->getChildByTag<LayerColor*>(1001)->runAction(Sequence::create(FadeTo::create(0.15, 0), CallFuncN::create([&](Ref* sender){
            this->removeChildByTag(1001);
        }), NULL));
    }
}
void Popup::fadeInBgDark()
{
    this->getChildByTag<LayerColor*>(1001)->runAction(FadeTo::create(0.4, 160));
}
void Popup::removeBgTouch()
{
    
    MenuItemSprite * item = MenuItemSprite::create(LayerColor::create(Color4B(0, 0, 0, 0)), LayerColor::create());
    
    Size _size = Director::getInstance()->getVisibleSize();
    _size.width = _size.width*1.5f;
    _size.height = _size.height*1.5f;
    item->setContentSize(Size(_size));
    item->setPosition(_size.width/2, _size.height/2);
    auto menu = Menu::create(item, nullptr);
    menu->setIgnoreAnchorPointForPosition(false);
    menu->setAnchorPoint(Vec2(0.5f, 0.5f));
    menu->setPosition(getContentSize().width/2, getContentSize().height/2);
    menu->setContentSize(Size(_size));
    addChild(menu, -1);
}

void Popup::removeTouch()
{
    
    MenuItemSprite * item = MenuItemSprite::create(LayerColor::create(Color4B(0, 0, 0, 200)), LayerColor::create());
    item->setAnchorPoint(Vec2(0.5f, 0.5f));
    item->setIgnoreAnchorPointForPosition(false);
    item->setContentSize(getContentSize());
    item->setPosition(getContentSize().width/2, getContentSize().height/2);
    auto menuTouch = Menu::create(item, nullptr);
    menuTouch->setIgnoreAnchorPointForPosition(false);
    menuTouch->setAnchorPoint(Vec2(0.5f, 0.5f));
    menuTouch->setContentSize(Size(getContentSize()));
    menuTouch->setPosition(getContentSize().width/2, getContentSize().height/2);
    addChild(menuTouch, -1);
}
Popup* Popup::getActivePopup()
{
    if (listPopups->size() <= 0)
    {
        return nullptr;
    }
    return listPopups->at(listPopups->size() - 1);
}
void Popup::effectShow(Node* mainNode)
{
    float _scaleX = getScaleX();
    float _scaleY = getScaleY();
    mainNode->setScaleX(_scaleX*0.8f);
    mainNode->setScaleY(_scaleY*0.8f);
    ScaleTo * scaleTo = ScaleTo::create(0.3f, _scaleX, _scaleY);
    EaseBackOut *out = EaseBackOut::create(scaleTo);
    mainNode->stopAllActions();
    mainNode->runAction(out);
}
void Popup::effectHide()
{
}
void Popup::effectColse()
{
    Size size = Director::getInstance()->getVisibleSize();
    MoveTo * moveTo = MoveTo::create(0.2f, Vec2(size.width + getBoundingBox().size.width/2, size.height/2));
    CallFuncN * cal = CallFuncN::create([&](Ref *target){
        if  (layerBG != nullptr && layerBG->getParent() != nullptr)
            layerBG->removeFromParent();
        this->removeFromParent();
    });
    Sequence * se = Sequence::create(moveTo, cal, NULL);
    runAction(se);
}
