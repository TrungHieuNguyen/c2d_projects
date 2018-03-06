//
//  CardList.cpp
//  ChipGame-mobile
//
//  Created by TrungHieu on 3/6/18.
//
#include <stdio.h>
#include <iostream>
#include "cocos2d.h"
#include "CardList.hpp"
using namespace std;
using namespace cocos2d;
#include "Card.hpp"
class CardList: public LayerColor
{
public:
    CC_SYNTHESIZE(Vector<Card*>, vCard, VCard);
    CC_SYNTHESIZE(Vector<Card*>, vFireCard, vFireCard);
};
