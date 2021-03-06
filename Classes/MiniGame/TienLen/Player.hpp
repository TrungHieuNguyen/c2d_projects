//
//  Player.hpp
//  ChipGame-mobile
//
//  Created by TrungHieu on 3/6/18.
//

#ifndef Player_hpp
#define Player_hpp
#include "cocos2d.h"
#include "../GameDefine.h"
#include <stdio.h>
#include "Player.hpp"
#include "CardList.hpp"
USING_NS_CC;
using namespace::cocos2d;

class CardList;
class Player : public LayerColor
{
    PlayerType mType;
    Sprite * sprAvatar;
    Vec2 mPosition;
   
    public:
    CardList* Cards;
    Player();
    virtual ~Player();
    bool init();
    CREATE_FUNC(Player);
    void initContent();
    void initPlayerType(PlayerType _type);
    void setPosPlayer(int _pos);
};
#endif /* Player_hpp */
