//
//  PopupConfirm.hpp
//  CGV
//
//  Created by Tien Bao Nguyen on 9/6/16.
//
//

#ifndef PopupSelectBuyIn_hpp
#define PopupSelectBuyIn_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "cocos2d.h"
#include "cocos-ext.h"
#include "ui/CocosGUI.h"
#include "editor-support/cocostudio/ActionTimeline/CSLoader.h"
#include "Popup.hpp"

using namespace std;
using namespace cocos2d;
using namespace::ui;

class PopupSelectBuyIn : public Popup
{
    Node * mainNode;
    Node * spTextfield;
    long betGoldTable;
public:
   
    
    Button * btnOk;
    Button * btnCancel;
    Text * txtMinValue;
    Text * txtMaxValue;
    Text * txtSelectedValue;
    Slider *sliderBuyIn;
    long  lMinValue;
    long  lMaxValue;
    long  lTableValue;
    long sliderUnit;
    long iSelectedValue;
    bool isAutoDrawMoney;
    int tableID;
    string tablePass;
    bool isInvited;
    bool hasLogin;

    static PopupSelectBuyIn* gI();
    static PopupSelectBuyIn* instance;
    virtual bool init();
    virtual ~PopupSelectBuyIn();
    CREATE_FUNC(PopupSelectBuyIn);
    void initType(long,long,long,int tableID, string pass,
                  bool isInvited,bool login);
    void close();
    static void removePopup();
    string getStringMinValue();
    string getStringMaxValue();
    void open();
   // void setPositionType(TypeEase type);
    
};

#endif /* PopupSelectBuyIn_hpp */
