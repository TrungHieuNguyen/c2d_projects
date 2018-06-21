//
//  AbstractScene.hpp
//  ChipGame-mobile
//
//  Created by TrungHieu on 11/30/17.
//

#ifndef AbstractScene_hpp
#define AbstractScene_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "../cocos/editor-support/cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "GameDefine.h"
USING_NS_CC;
using namespace std;
enum PlayerRank
{
    RANK_NHAT,
    RANK_NHI,
    RANK_BA,
    RANK_BET,
    RANK_THANG,
    RANK_HOA,
    RANK_THUA,
    HIDE,
};

class AbstractScene : public cocos2d::Layer
{
    Node * _layerMain;
    Node* layerHUD;
    public:
    Size visibleSize;
    bool init();
    virtual void goMainScreen();
    virtual void clickBtnBack(Ref* sender);
    void hideHUD();
    void showHUD();
    void updateScore(int);
    void showGold(long long _gold, bool isWin);
    void showResult(PlayerRank stt, int delay);
    void showTextGame(string);
};
#endif /* AbstractScene_hpp */
