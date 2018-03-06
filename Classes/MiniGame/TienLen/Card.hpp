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
class Card: public Sprite
{
public:
    CC_SYNTHESIZE(bool, isShow, IsShow);
    CC_SYNTHESIZE(bool, isSelected, IsSelected);
    CC_SYNTHESIZE(int, cardValue, CardValue);
    CC_SYNTHESIZE(int, cardID, CardID);
    CC_SYNTHESIZE(int, cardName, CardName);
    
    CREATE_FUNC(Card);
    virtual bool init();
};
#endif /* Card_hpp */
