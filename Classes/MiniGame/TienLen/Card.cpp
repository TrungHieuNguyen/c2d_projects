//
//  Card.cpp
//  ChipGame-mobile
//
//  Created by TrungHieu on 3/6/18.
//

#include "Card.hpp"
bool Card::init()
{
    bool pRet = false;
    if (Sprite::init())
    {
        initContent();
        isSelected = false;
        pRet = true;
    }
    return pRet;
}
void Card::initContent()
{
    //setIgnoreAnchorPointForPosition(false);
    setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    sprFace = Sprite::create("res/images/card/bich1.png");
    setContentSize(sprFace->getContentSize());
    sprFace->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    sprFace->setPosition(Vec2(getContentSize().width/2,getContentSize().height/2));
    sprFace->setVisible(false);
    sprFace->setScale(0.5);
    addChild(sprFace);
    
    sprBack = Sprite::create("res/images/card/cardback.png");
    setContentSize(sprBack->getContentSize());
    sprBack->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    sprBack->setPosition(Vec2(getContentSize().width/2,getContentSize().height/2));
    //sprCard->setPosition(Vec2(0,0));
    sprBack->setScale(0.5);
    sprBack->setVisible(true);
    addChild(sprBack);
    
    return;
}
void Card::flip()
{
    sprBack->setVisible(false);
    sprFace->setVisible(true);
}
void  Card::set(CardType _type, CardNumber _number)
{
    type = _type;
    mNumber = _number;
    const char * strImageNameType;
    switch (_type) {
        case CardTypeBich:
            strImageNameType = "bich";
            break;
        case CardTypeChuon:
            strImageNameType = "chuon";
            break;
        case CardTypeRo:
            strImageNameType = "ro";
            break;
        case CardTypeCo:
            strImageNameType = "co";
            break;
        default:
            break;
    }
    char str[30];
    sprintf(str, "res/images/card/%s%d.png", strImageNameType , (int)_number);
    sprFace->setTexture(TextureCache::getInstance()->addImage(str));
}
void Card::set52(int b)
{
    cardValue = b;
    int temp = 0;
    int _number = ((b  % 13) + 3);
    if (_number > 13) {
        _number = _number - 13;
    }
    CardType _type;
    cardValue = b;
    temp = (int) b / 13;
    switch (temp) {
        case 0:
            _type = CardTypeBich;
            break;
        case 1:
            _type = CardTypeChuon;
            break;
        case 2:
            _type = CardTypeRo;
            break;
        case 3:
            _type = CardTypeCo;
            break;
    }
    mNumber =  (CardNumber)_number;
    //cardName = (CardNameTL)((b % 13) * 4 + b/13);
    type = _type;
    set(type, mNumber);
}
