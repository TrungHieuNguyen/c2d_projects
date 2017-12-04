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

    
};
#endif /* AbstractScene_hpp */
