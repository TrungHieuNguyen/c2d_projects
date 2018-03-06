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
        isSelected = false;
        pRet = true;
    }
    return pRet;
}
