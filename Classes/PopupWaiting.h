

#ifndef __PopupWaiting__
#define __PopupWaiting__

#include <stdio.h>
#include "cocos2d.h"
#include "cocos-ext.h"

using namespace std;
using namespace cocos2d;

class PopupWaiting : public LayerColor {
protected:
    bool isShow;
    Size size;
public:
    static PopupWaiting* curPopup;
    PopupWaiting();
    virtual ~PopupWaiting();
    CREATE_FUNC(PopupWaiting);
    virtual bool init();
    void show();
	void showEmpty();
    void show(Node * node);
    void show(Node * node, Size _nodeSize);
    void dismiss();
    
    static PopupWaiting* instance ;
    static PopupWaiting* gI();
    void removeTouch();
};
#endif /* defined(__PopupWaiting__) */
