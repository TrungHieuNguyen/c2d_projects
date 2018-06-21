//
//  PopupResult.hpp
//  ChipGame
//
//  Created by Nguyen Trung Hieu on 9/6/17.
//
//

#ifndef PopupResult_hpp
#define PopupResult_hpp

#include <stdio.h>
#include "Popup.hpp"
#include "GameDefine.h"
class PopupResult : public Popup
{
   
    static PopupResult* instance;
    Node * mainLayer;
    PopupResult();
    virtual ~PopupResult();
    CREATE_FUNC(PopupResult);
public:
    static PopupResult* gI();
    virtual bool init();
    void open();
    void close();
    void readData();
    void clickClose(Ref * sender);
};
#endif /* PopupResult_hpp */
