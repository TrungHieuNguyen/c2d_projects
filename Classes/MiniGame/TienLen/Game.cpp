//
//  Game.cpp
//  ChipGame-mobile
//
//  Created by TrungHieu on 3/6/18.
//

#include "Game.hpp"
void Game::onEnter(){}
void Game::onStart(){}
void Game::onEnd(){}
void Game::deliverCard(){}
void Game::resetTable(){}
void Game::addPlayer()
{
    Player* player = Player::create();
    vPlayer.pushBack(player);
    addChild(player);
    
    
}
