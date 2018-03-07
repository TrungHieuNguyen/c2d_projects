//
//  CardList.hpp
//  ChipGame-mobile
//
//  Created by TrungHieu on 3/6/18.
//

#ifndef CardList_hpp
#define CardList_hpp

#include <stdio.h>
#include <stdio.h>
#include <iostream>
#include "cocos2d.h"

using namespace std;
using namespace cocos2d;
#include "Card.hpp"
class CardList: public LayerColor
{
public:
    CC_SYNTHESIZE(Vector<Card*>, vCard, VCard);
    CC_SYNTHESIZE(Vector<Card*>, vFireCard, vFireCard);
    CREATE_FUNC(CardList);
    virtual ~CardList();
    CardList();
    virtual bool init();
};
#endif /* CardList_hpp */
