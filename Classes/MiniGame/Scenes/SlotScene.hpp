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
    int m_Velocity;
    int m_SpinCounter;
    int m_showResult;
    
    int arrResult[3][5] = {{ 1,1,1,1,1 },
                            { 2,2,2,2,2 },
                            { 3,3,3,3,3 }};
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    void initComponents();
    void spin(float dt);
    void showResult(int arr[3][5]);
    void spinCounter(float dt);
    bool isPlaying;
    bool stopSpinning;
    void resetArrayResult(int k);
    int getValueItem(int i, int j);
    // implement the "static create()" method manually
    CREATE_FUNC(SlotScene);
};
#endif /* SlotScene_hpp */
