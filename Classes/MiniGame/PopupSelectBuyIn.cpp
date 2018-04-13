//
//  PopupConfirm.cpp
//  CGV
//
//  Created by Tien Bao Nguyen on 9/6/16.
//
//

#include <climits>
#include "PopupSelectBuyIn.hpp"
#include "../Utility/Resources.h"
#include "../Screen/AbstractScreen.h"
//#include "../Utility/AppUtil.h"
#define W 710.00
#define H 552

PopupSelectBuyIn* PopupSelectBuyIn::instance = 0;
PopupSelectBuyIn * PopupSelectBuyIn::gI()
{
    
    if (instance == NULL){
        instance = PopupSelectBuyIn::create();
    }
    return instance;
}

// on "init" you need to initialize your instance
bool PopupSelectBuyIn::init()
{
    //////////////////////////////
    // 1. super init first
    bool pRet = false;
    isAutoDrawMoney = false;
    lMaxValue = 0;
    lMinValue = 0;
    lTableValue = 0;
    sliderUnit = 0;
    iSelectedValue = 0;
    tableID = -1;
    tablePass = "";
    isInvited = false;
    hasLogin = false;
    if (PopupAbstract::init())
    {
        instance = this;
        setAnchorPoint(Vec2::ANCHOR_MIDDLE);
        setIgnoreAnchorPointForPosition(false);
       
        mainNode = CSLoader::createNode(RES_POPUP_SELECT_BUYIN_LIENG);
        mainNode->setIgnoreAnchorPointForPosition(false);
        mainNode->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
        setContentSize(mainNode->getContentSize());
        mainNode->setScale(0);
        mainNode->setPosition(getContentSize()/2);
        addChild(mainNode);
        initBgDark();
        btnOk = static_cast<cocos2d::ui::Button*>(mainNode->getChildByName("btnOk"));
        btnOk->setPressedActionEnabled(true);
        btnOk->addClickEventListener([&](Ref* sender)
                                     {
                                         SoundManager::gI()->playSound(SOUND_BUTTON);
                                         log("Select BUY-IN: Money:%ld, AutoDraw:%d",iSelectedValue,isAutoDrawMoney);
                                         if(!hasLogin){
                                             PopupWaiting::gI()->show();
                                             CCGlobalService::gI()->setBuyIn(iSelectedValue, isAutoDrawMoney,tableID,tablePass,isInvited );
                                         }
                                         else
                                             CCGlobalService::gI()->getBuyIn(iSelectedValue, isAutoDrawMoney);
                                         
                                         PopupSelectBuyIn::close();
                                     });
        btnCancel = static_cast<cocos2d::ui::Button*>(mainNode->getChildByName("btnCancel"));
        btnCancel->setPressedActionEnabled(true);
        btnCancel->addClickEventListener([&](Ref* sender)
                                         {
                                             SoundManager::gI()->playSound(SOUND_BUTTON);
                                             PopupSelectBuyIn::close();
                                              if(hasLogin)
                                              {
                                            
                                                      CCGlobalService::gI()->sendMsgLeaveTable(tableID);
                                              }
                                         });


   
        txtSelectedValue = mainNode->getChildByName("imgContent")->getChildByName<Text*>("txtSelectedValue");
        txtMinValue = mainNode->getChildByName("imgContent")->getChildByName<Text*>("txtMIN");
        txtMaxValue = mainNode->getChildByName("imgContent")->getChildByName<Text*>("txtMAX");
        sliderBuyIn = ( cocos2d::ui::Slider * )mainNode->getChildByName("sliderBuyIn");
        sliderBuyIn->setMaxPercent(100);
        iSelectedValue = (sliderBuyIn->getPercent());
        txtSelectedValue->setString(getShortStringGoldDisplayK(iSelectedValue, true, true));
        sliderBuyIn->addEventListener([&](Ref* sender, Slider::EventType type) {
            auto slider = dynamic_cast<Slider*>(sender);
            if (type == Slider::EventType::ON_PERCENTAGE_CHANGED)
            {
                iSelectedValue = ((slider->getPercent() + lMinValue/lTableValue) * lTableValue);
                
                //lMaxValue/tableBet -lMinValue/tableBet
                txtSelectedValue->setString(getShortStringGoldDisplayK(iSelectedValue, true, true));
                //txtSelectedValue->setString(StringUtils::toString(sliderBuyIn->getPercent()));
            }
        });
        
        cocos2d::ui::CheckBox *checkbox = ( cocos2d::ui::CheckBox * )mainNode->getChildByName("imgContent")->getChildByName("cbTuDongNap");
        checkbox->setSelected(true);
        isAutoDrawMoney= true;
        checkbox->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type)
                                        {
                                            CheckBox* cb = (CheckBox*) sender;
                                            switch (type)
                                            {
                                                case ui::Widget::TouchEventType::BEGAN:
                                                    break;
                                                case ui::Widget::TouchEventType::ENDED:
                                                        log("Select BUY-IN: AutoDraw:%d",cb->isSelected());
                                                        isAutoDrawMoney = cb->isSelected();
                                                        log("Select BUY-IN: AutoDraw:%d",isAutoDrawMoney);
                                                    break;
                                                default:
                                                    break;
                                            }
                                        });
        
        
        auto spriteEffect = (Sprite*)mainNode->getChildByName("effectTopPopup");
        float pos1 = mainNode->getChildByName("imgBG")->getContentSize().width - spriteEffect->getContentSize().width;
        float pos2 = spriteEffect->getPositionX() - 30;
        auto action = Sequence::create(MoveTo::create(4, Vec2(pos1,spriteEffect->getPositionY())),MoveTo::create(4, Vec2(pos2,spriteEffect->getPositionY())), NULL);
        spriteEffect->runAction(RepeatForever::create(action));
        pRet = true;
        
        removeBgTouch();
    }
    return pRet;
}

void PopupSelectBuyIn::initType(long _min, long _max,long tableBet,int _id, string _pass,
                                bool _invited, bool _login)
{
    lMaxValue  = _max*tableBet;
    lMinValue = _min*tableBet;
    txtMaxValue->setString(getShortStringGoldDisplayK(lMaxValue,true,true));
    txtMinValue->setString(getShortStringGoldDisplayK(lMinValue,true,true));
    tableID = _id;
    tablePass = _pass;
    isInvited = _invited;
    sliderUnit = lMinValue;
    lTableValue = tableBet;
    //sliderUnit =tableBet;
    hasLogin = _login;
    if(sliderBuyIn!=nullptr){
        int maxPecent = lMaxValue/tableBet -lMinValue/tableBet;
        sliderBuyIn->setMaxPercent(maxPecent);
        sliderBuyIn->setPercent(maxPecent/2);
        //iSelectedValue = ((sliderBuyIn->getPercent() + lMinValue/sliderUnit) * sliderUnit);
         iSelectedValue = ((sliderBuyIn->getPercent() + lMinValue/lTableValue) * lTableValue);
        txtSelectedValue->setString(getShortStringGoldDisplayK(iSelectedValue, true, true));
        //txtSelectedValue->setString(StringUtils::toString(sliderBuyIn->getPercent()));
    }
}

void PopupSelectBuyIn::close()
{
    CallFuncN * cal = CallFuncN::create([&](Ref *target){
        if  (layerBG != nullptr && layerBG->getParent() != nullptr)
        {
            layerBG->removeFromParent();
            layerBG = nullptr;
        }
        PopupAbstract::close();
    });
    
    mainNode->runAction(Sequence::create(CallFuncN::create([&](Ref* sender){
        this->fadeOutBgDark();
    }), ScaleTo::create(0.1, 1.1), ScaleTo::create(0.1, 0),cal ,NULL));
}

void PopupSelectBuyIn::removePopup(){
    if(instance != nullptr){
        instance->close();
    }
}

PopupSelectBuyIn::~PopupSelectBuyIn()
{
    instance = nullptr;
}

string PopupSelectBuyIn::getStringMinValue()
{
    string strBet = txtMinValue->getString();
    strBet.erase (std::remove(strBet.begin(), strBet.end(), '.'), strBet.end());
    return strBet;
}

string PopupSelectBuyIn::getStringMaxValue()
{
    return txtMaxValue->getString();
}

void PopupSelectBuyIn::open()
{
    mainNode->runAction(Sequence::create(ScaleTo::create(0.2, 1.1), ScaleTo::create(0.2, 1.0), NULL));
//    ActionInterval* move = MoveTo::create(0.5, Point(getContentSize().width/2, getContentSize().height/2));
//    ActionInterval* move_ease = EaseBackInOut::create(
//                                                      (ActionInterval*) (move->clone()));
//    mainNode->runAction(move_ease);
}

void PopupSelectBuyIn::setPositionType(TypeEase type)
{
    switch (type) {
        case TypeEase::TOP:
        {
            mainNode->setPosition(getContentSize().width/2, - getContentSize().height * 2);
        }
            break;
        case TypeEase::DOWN:
        {
            mainNode->setPosition(getContentSize().width/2, getContentSize().height * 2);
        }
            break;
        case TypeEase::RIGHT:
        {
            mainNode->setPosition(getContentSize().width * 2.5, getContentSize().height/2);
        }
            break;
        case TypeEase::LEFT:
        {
            mainNode->setPosition(-getContentSize().width * 2.5, getContentSize().height/2);
        }
            break;
        default:
            break;
    }
}
