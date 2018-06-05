//
//  MainScene.hpp
//  ChipGame
//
//  Created by Nguyen Trung Hieu on 8/18/17.
//
//

#ifndef SlotScene_hpp
#define SlotScene_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "ui/CocosGUI.h"
using namespace cocos2d;
using namespace ui;
#include "GameDefine.h"

class SlotScene : public AbstractScene
{
    Node* layerBG;
    Text* lbTitle;
    int m_Speed;
    int m_Direction;
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    void initComponents();
    void spin(float dt);
    void spinCounter(float dt);
    bool isPlaying;
    bool stopSpinning;
    // implement the "static create()" method manually
    CREATE_FUNC(SlotScene);
};
#endif /* SlotScene_hpp */
