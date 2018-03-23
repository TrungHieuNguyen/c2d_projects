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
    TMXTiledMap *_tileMap;
    TMXLayer *_background;
    TMXLayer *_foreground;
    TMXLayer *_meta;
    Sprite *_player;
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    void setViewPointCenter(Point position);
    Point tileCoordForPosition(Point position);
    void setPlayerPosition(Point position);
    void menuCloseCallback(cocos2d::Ref* pSender);
    void initComponents();
    // implement the "static create()" method manually
    CREATE_FUNC(GameTiledMap);
    void registerTouchDispatcher();
    virtual bool onTouchBegan(cocos2d::Touch*, cocos2d::Event*);
    virtual void onTouchEnded(cocos2d::Touch*, cocos2d::Event*);
    virtual void onTouchMoved(cocos2d::Touch*, cocos2d::Event*);
    virtual void onTouchCancelled(cocos2d::Touch*, cocos2d::Event*);
};
#endif /* MainScene_hpp */
