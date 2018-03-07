//
//  Card.hpp
//  ChipGame-mobile
//
//  Created by TrungHieu on 3/6/18.
//

#ifndef Card_hpp
#define Card_hpp
#include "cocos2d.h"
#include "../GameDefine.h"
#include <stdio.h>
USING_NS_CC;
#include <stdio.h>
using namespace cocos2d;
using namespace std;


enum CardType {
    CardTypeBich = 0,
    CardTypeChuon,
    CardTypeRo,
    CardTypeCo,
};

enum CardNumber {
    XI = 1,
    HAI,
    BA,
    BON,
    NAM,
    SAU,
    BAY,
    TAM,
    CHIN,
    MUOI,
    RI,
    DAM,
    GIA,
};

class Card: public Sprite
{
    Sprite* sprCard;
public:
    CC_SYNTHESIZE(bool, isShow, IsShow);
    CC_SYNTHESIZE(bool, isSelected, IsSelected);
    CC_SYNTHESIZE(int, cardValue, CardValue);
    CC_SYNTHESIZE(int, cardID, CardID);
    CC_SYNTHESIZE(int, cardName, CardName);
    CC_SYNTHESIZE(Point, startPoint, StartPoint);
    CC_SYNTHESIZE(Point, worldPoint, WorldPoint);
    CC_SYNTHESIZE(CardType, type, Type);
    CardNumber mNumber;
    Sprite *sprBack;
    Sprite *sprFace;
    CREATE_FUNC(Card);
    virtual bool init();
    void initContent();
    void set(CardType _type, CardNumber _number);
    void flip();
    void set52(int b);
};
#endif /* Card_hpp */
