//
//  MainScene.hpp
//  ChipGame
//
//  Created by Nguyen Trung Hieu on 8/18/17.
//
//

#ifndef GameTiledMap_hpp
#define GameTiledMap_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "GameDefine.h"
#include "AbstractScene.hpp"
using namespace cocos2d;
using namespace ui;

class GameTiledMap : public AbstractScene
{
    Node* layerBG;
    Text* lbTitle;
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    void initComponents();
    // implement the "static create()" method manually
    CREATE_FUNC(GameTiledMap);
};
#endif /* MainScene_hpp */
