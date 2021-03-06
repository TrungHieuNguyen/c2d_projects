//
//  MainScene.hpp
//  ChipGame
//
//  Created by Nguyen Trung Hieu on 8/18/17.
//
//

#ifndef MainScene_hpp
#define MainScene_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "AbstractScene.hpp"
using namespace cocos2d;
using namespace ui;

class MainScene : public AbstractScene
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
    CREATE_FUNC(MainScene);
};
#endif /* MainScene_hpp */
