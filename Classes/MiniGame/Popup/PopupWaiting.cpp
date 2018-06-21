#include "PopupWaiting.h"
//#include "../Utility/AppUtil.h"

#define TIME_DISMISS 10

using namespace cocos2d;

PopupWaiting* PopupWaiting::instance = NULL;

PopupWaiting* PopupWaiting::gI() {
    if (NULL == instance) {
        instance = PopupWaiting::create();
    }
    
    return instance;
}

PopupWaiting::PopupWaiting() {
}


PopupWaiting::~PopupWaiting() {
    instance = NULL;
}

bool PopupWaiting::init()
{
    if (!LayerColor::initWithColor(Color4B(0, 0, 0, 120)))
    {
        return false;
    }

    instance = this;
    size = Director::getInstance()->getVisibleSize();
    
    isShow = false;
    this->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
    setIgnoreAnchorPointForPosition(false);
    this->setPosition(Vec2::ZERO);
    cocos2d::Node::setContentSize(size);
    
    return true;
}

void PopupWaiting::open() {
    if (isShow) return;
    setContentSize(size);
    removeTouch();
    
    Node* nodeLoading = Node::create();
    nodeLoading->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    nodeLoading->setPosition(Vec2(size.width / 2, size.height / 2));
    addChild(nodeLoading,1);
    //AppUtil::setScale(nodeLoading, ScaleType::ScaleTypeComponent);
    
    auto spriteBich = Sprite::create("res/loading/loadingBich.png");
    spriteBich->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    spriteBich->setPosition(Vec2(- spriteBich->getContentSize().width * 1, 0));
    nodeLoading->addChild(spriteBich,1);
    
    auto spriteCo = Sprite::create("res/loading/loadingCo.png");
    spriteCo->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    spriteCo->setPosition(Vec2(0, spriteCo->getContentSize().height * 1));
    nodeLoading->addChild(spriteCo,1);
    
    auto spriteChuong = Sprite::create("res/loading/loadingChuong.png");
    spriteChuong->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    spriteChuong->setPosition(Vec2(spriteBich->getContentSize().width * 1, 0));
    nodeLoading->addChild(spriteChuong,1);
    
    auto spriteRo = Sprite::create("res/loading/loadingRo.png");
    spriteRo->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    spriteRo->setPosition(Vec2(0, - spriteCo->getContentSize().height * 1));
    nodeLoading->addChild(spriteRo,1);
    
    nodeLoading->runAction(RepeatForever::create(RotateBy::create(0.35, 180)));
    spriteBich->runAction(RepeatForever::create(RotateBy::create(0.35, -180)));
    spriteCo->runAction(RepeatForever::create(RotateBy::create(0.35, -180)));
    spriteChuong->runAction(RepeatForever::create(RotateBy::create(0.35, -180)));
    spriteRo->runAction(RepeatForever::create(RotateBy::create(0.35, -180)));
    
//    auto sprite = Sprite::create();
//    sprite->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
//    sprite->setPosition(Vec2(size.width / 2, size.height / 2));
//    addChild(sprite,1);
//    AppUtil::setScale(sprite, ScaleType::ScaleTypeComponent);
//    
//    Vector<SpriteFrame*> animFrames(15);
//    char str[100] = { 0 };
//    for (int i = 1; i < 13; i++)
//    {
//        sprintf(str, "res/loading/loading%d.png", i);
//        auto frame = SpriteFrame::create(str, Rect(0, 0, sprite->getContentSize().width, sprite->getContentSize().height));
//        animFrames.pushBack(frame);
//    }
//    
//    auto animation = Animation::createWithSpriteFrames(animFrames, 0.1f);
//    animation->setLoops(-1);
//    auto animate = Animate::create(animation);
//    sprite->runAction(animate);
    
    Node* root = Director::getInstance()->getRunningScene();
    if (root != nullptr)
        root->addChild(this, INT_MAX);
    isShow = true;
    
    DelayTime * delay = DelayTime::create(TIME_DISMISS);
    CallFuncN * cal = CallFuncN::create(CC_CALLBACK_0(PopupWaiting::dismiss, this));
    stopAllActions();
    runAction(Sequence::create(delay, cal, NULL));

}

void PopupWaiting::open(Node * node)
{
    open(node, node->getContentSize());
}
void PopupWaiting::open(Node * node, Size _nodeSize)
{
    if (isShow) return;
    setContentSize(_nodeSize);
    setAnchorPoint(Vec2::ANCHOR_MIDDLE_TOP);
    removeTouch();
    
    auto sprite = Sprite::create("res/loading/loading1.png");
    float scaleValue = node->getContentSize().width / 9 / sprite->getContentSize().width;
    sprite->setScale(scaleValue);
    
    float x = node->getContentSize().width / 2;
    float y = node->getContentSize().height;
    this->setPosition(x, y);
    
    sprite->setPosition(Vec2(_nodeSize.width/2, _nodeSize.height/2));
    addChild(sprite, INT_MAX);
    
    Vector<SpriteFrame*> animFrames(15);
    char str[100] = { 0 };
    for (int i = 1; i < 13; i++)
    {
        sprintf(str, "res/loading_popup/loading%d.png", i);
        auto frame = SpriteFrame::create(str, Rect(0, 0, sprite->getContentSize().width, sprite->getContentSize().height));
        animFrames.pushBack(frame);
    }
    
    auto animation = Animation::createWithSpriteFrames(animFrames, 0.1f);
    animation->setLoops(-1);
    auto animate = Animate::create(animation);
    sprite->runAction(animate);
    
    node->addChild(this, INT_MAX);
    isShow = true;
    
    DelayTime * delay = DelayTime::create(TIME_DISMISS);
    CallFuncN * cal = CallFuncN::create(CC_CALLBACK_0(PopupWaiting::dismiss, this));
    stopAllActions();
    runAction(Sequence::create(delay, cal, NULL));
}

void PopupWaiting::removeTouch()
{
    MenuItemSprite * item = MenuItemSprite::create(LayerColor::create(Color4B(0, 0, 0, 0)), LayerColor::create());
    item->setContentSize(getContentSize()*2);
    item->setPosition(size.width/2, size.height/2);
    auto menu = Menu::create(item, nullptr);
    menu->setPosition(Vec2::ZERO);
    menu->setContentSize(getContentSize());
    addChild(menu, -1);
}

void PopupWaiting::dismiss()
{
    stopAllActions();
    if (isShow && instance != nullptr && instance->getParent() != nullptr)
        removeFromParent();
}
