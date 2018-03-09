//
//  CardList.cpp
//  ChipGame-mobile
//
//  Created by TrungHieu on 3/6/18.
//
#include "CardList.hpp"
#include "Player.hpp"
CardList::~CardList(){}
CardList::CardList(){}
bool CardList::init()
{
    bool pRet = false;
    if (LayerColor::initWithColor(Color4B(100, 100, 200, 200)))
    {
        this->setContentSize(Size(WIDTH_CARD*13, HEIGHT_CARD));
        setTouchEnabled(true);
        vCard.clear();
        vFireCard.clear();
        pRet = true;
    }
    return pRet;
}
void CardList::initCards(int number)
{
    vCard.clear();
    vFireCard.clear();
    auto visibleSize = Director::getInstance()->getVisibleSize();
    this->setContentSize(Size(WIDTH_CARD*number, HEIGHT_CARD));
    for (int i = 0; i < number; i++)
    {
        Card *card = Card::create();
        card->set(CardTypeBich, XI);
        card->setPosition(i*30, 0);
        vCard.pushBack(card);
        addCard(card);
    }
}
void CardList::setPlayer(Player* player)
{
    mPlayer = player;
}

void CardList::addCard(Card *c)
{
    vCard.pushBack(c);
    //int PosY = vCard.size()*100;
    switch (getTypePlayer())
    {
        
        case PlayerLeft:
        {
             c->setPosition(0,250 - vCard.size()*40);
            break;
        }
        case PlayerRight:
        {
            c->setPosition(0,250 -vCard.size()*40);
            break;
        }
        case PlayerBottom:
        {
            c->setPosition(vCard.size()*30, 0);
            break;
        }
        case PlayerTop:
        {
            c->setPosition(vCard.size()*30, 0);
            break;
        }
        default:
             c->setPosition(vCard.size()*30, 0);
            break;
    }
   
    addChild(c);
}
