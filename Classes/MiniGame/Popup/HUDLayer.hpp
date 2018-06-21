//
//  HUDLayer.hpp
//  ChipGame-mobile
//
//  Created by TrungHieu on 3/23/18.
//

#ifndef HUDLayer_hpp
#define HUDLayer_hpp

#include <stdio.h>
#include "cocos2d.h"

using namespace cocos2d;

class HudLayer : public cocos2d::CCLayer
{
private:
    CCLabelTTF *_label;
    
public:
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();
    
    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    
    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(HudLayer);
    
    void numCollectedChanged (int numCollected);
};

#endif /* HUDLayer_hpp */
