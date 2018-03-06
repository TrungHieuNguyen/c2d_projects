//
//  Game.hpp
//  ChipGame-mobile
//
//  Created by TrungHieu on 3/6/18.
//

#ifndef Game_hpp
#define Game_hpp

#include <stdio.h>
#include "Player.hpp"
class Game: public Layer
{
    int mNumberPlayer;
    Vector<Player*> vPlayer;
public:
     bool init();
    void onEnter();
    void onStart();
    void onPause();
    void onEnd();
    void onExit();
    void deliverCard();
    void resetTable();
    void addPlayer();
};
#endif /* Game_hpp */
