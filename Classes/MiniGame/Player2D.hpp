//
//  Player.hpp
//  ChipGame-mobile
//
//  Created by TrungHieu on 3/26/18.
//

#ifndef Player2D_hpp
#define Player2D_hpp
#include "cocos2d.h"
#include "GameDefine.h"
#include <stdio.h>
#include "../cocos/editor-support/cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
using namespace::cocos2d;
using namespace std;
class Player2D : public Sprite
{
    Sprite* sprPlayer;
    Label* lbStatus;
public:
    virtual bool init();
    void loadComponents();
    CREATE_FUNC(Player2D);
    Vector< SpriteFrame*> getAnimation(const char *format, int count);
    void run();
    void jump();
    void shoot();
    void slash();
    void stand();
    void setStatus(HeroState stt);
    void showStatus(HeroState stt);
};
#endif /* Player2D_hpp */
