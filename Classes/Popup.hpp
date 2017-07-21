//
//  Popup.hpp
//  ChipGame
//
//  Created by Nguyen Trung Hieu on 7/14/17.
//
//

#ifndef Popup_hpp
#define Popup_hpp
#include <stdio.h>
#include "cocos2d.h"
#include "cocos-ext.h"
#include "ui/CocosGUI.h"
#include <stdio.h>
#define  Z_POPUP_PRIORITY 100
using namespace::cocos2d;
using namespace::extension;
#define COLOR_TITTLE Color3B(35, 195, 233)

class Popup: public LayerColor
{
  
    Label * lbTitle;
     static Vector<Popup*> *listPopups;
    Size size;
    Size sTable;
    Sprite * spBgFull;
    LayerColor * layerBG;
    
    CREATE_FUNC(Popup);
    Popup();
    
    virtual ~Popup();
    virtual void initComponent();
    virtual void onTouchClose(Ref* pSender, cocos2d::ui::Widget::TouchEventType type);
    virtual void close();
    virtual void effectShow(Node* mainNode) final;
    virtual void effectHide();
    void effectColse();
    
    bool init();
    bool initWithColor(Color4B color);
    void initTitle(const char * title, Point p);
    void removeBgTouch();
    void removeTouch();
    void setBackground();
    void initBgDark();
    void fadeOutBgDark();
    void fadeInBgDark();
    
    static void closeAllPopup();
    static Popup* getActivePopup();
   
};
#endif /* Popup_hpp */