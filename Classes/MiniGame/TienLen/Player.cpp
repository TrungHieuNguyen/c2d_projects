//
//  Player.cpp
//  ChipGame-mobile
//
//  Created by TrungHieu on 3/6/18.
//

#include "Player.hpp"
#include "CardList.hpp"

Player::Player(){}
Player::~Player(){}

bool Player::init()
{
    bool pRet = false;
    if (LayerColor::initWithColor(Color4B(0, 0, 100, 100)));
    {
        initContent();
        return true;
    }
    return pRet;
}
void Player::initContent()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    //setIgnoreAnchorPointForPosition(false);
    //setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    sprAvatar = Sprite::create("res/images/Icon-76.png");
    setContentSize(sprAvatar->getContentSize());
    sprAvatar->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    //sprAvatar->setPosition(Vec2(getContentSize().width/2,getContentSize().height/2));
    sprAvatar->setPosition(Vec2(0,0));
    sprAvatar->setScale(0.6);
    addChild(sprAvatar);
    Cards = CardList::create();
 //   Cards->initCards(3);
//    //Cards->setParent(this);
    addChild(Cards);
    
    return;
}
void Player::initPlayerType(PlayerType _type)
{
    Size size =  Director::getInstance()->getOpenGLView()->getVisibleSize();
    mType = _type;
    
    switch (_type)
    {
        case PlayerLeft:
        {
            mPosition = Vec2(100, size.height/2);
            break;
        }
        case PlayerRight:
        {
            mPosition = Vec2(size.width - 100, size.height/2);
            break;
        }
        case PlayerBottom:
        {
            mPosition = Vec2(size.width/2, 100);
            break;
        }
        case PlayerTop:
        {
            mPosition = Vec2(size.width/2, size.height - 100);
            break;
        }
        default:
            break;
    }
    
    setPosition(convertToWorldSpace(mPosition));
}
