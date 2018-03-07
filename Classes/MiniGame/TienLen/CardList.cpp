//
//  CardList.cpp
//  ChipGame-mobile
//
//  Created by TrungHieu on 3/6/18.
//
#include "CardList.hpp"
bool CardList::init()
{
    bool pRet = false;
    if (LayerColor::initWithColor(Color4B(100, 100, 200, 0)))
    {
        this->setContentSize(Size(WIDTH_CARD*13, HEIGHT_CARD));
        setTouchEnabled(true);
        pRet = true;
    }
    return pRet;
}
