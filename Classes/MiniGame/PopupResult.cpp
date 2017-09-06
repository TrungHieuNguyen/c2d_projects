//
//  PopupResult.cpp
//  ChipGame
//
//  Created by Nguyen Trung Hieu on 9/6/17.
//
//

#include "PopupResult.hpp"
#include "GameDefine.h"
#include "ui/CocosGUI.h"
#include "../cocos/editor-support/cocostudio/CocoStudio.h"


PopupResult* PopupResult::instance = 0;
PopupResult * PopupResult::gI()
{
    
    if (instance == NULL){
        instance = PopupResult::create();
    }
    return instance;
}

PopupResult::PopupResult()
{
    
}


PopupResult::~PopupResult()
{
    
    instance = nullptr;
}

bool PopupResult::init()
{
    bool pRet = false;
    if (Popup::init())
    {
        initBgDark();
        auto visibleSize = Director::getInstance()->getVisibleSize();
        Vec2 origin = Director::getInstance()->getVisibleOrigin();
        mainLayer = CSLoader::createNode(RES_SLIDER_RESULT_CSB);
        mainLayer->setAnchorPoint(Point(0.5f, 0.5f));
        mainLayer->setPosition(Vec2(visibleSize.width/2 , visibleSize.height/2));
        cocos2d::ui::Button *btnClose = (ui::Button*)mainLayer->getChildByName("btnClose");
        btnClose->addClickEventListener(CC_CALLBACK_1(PopupResult::clickClose, this));
        this->addChild(mainLayer,101);
        removeBgTouch();
        pRet = true;
    }
    return pRet;
}

void PopupResult::open()
{
    mainLayer->setScale(0);
    mainLayer->runAction(Sequence::create(ScaleTo::create(0.2, 1.1), ScaleTo::create(0.2, 1.0), NULL));
}
void PopupResult::close()
{
    CallFuncN * cal = CallFuncN::create([&](Ref *target){
//        if  (layerBG != nullptr && layerBG->getParent() != nullptr)
//        {
//            layerBG->removeFromParent();
//            layerBG = nullptr;
//        }
        Popup::close();
    });
    
    mainLayer->runAction(Sequence::create(CallFuncN::create([&](Ref* sender){
        this->fadeOutBgDark();
    }), ScaleTo::create(0.1, 1.1), ScaleTo::create(0.1, 0),cal ,NULL));
}
void PopupResult::clickClose(Ref * sender)
{
    close();
}


