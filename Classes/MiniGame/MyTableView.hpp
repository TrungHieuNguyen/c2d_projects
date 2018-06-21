//
//  MyTableView.hpp
//  ChipGame-mobile
//
//  Created by TrungHieu on 6/21/18.
//

#ifndef MyTableView_hpp
#define MyTableView_hpp

#include <stdio.h>
#ifndef __MYTABLEVIEW_H__
#define __MYTABLEVIEW_H__
#include "cocos2d.h"
#include "cocos-ext.h"
#include <stdio.h> 
#include <sys/time.h> 
#include <time.h>


USING_NS_CC;
USING_NS_CC_EXT;

class MyTableView : public TableView
{
public:
    bool onTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    void onTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    void onTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    
    static MyTableView* create(TableViewDataSource* dataSource, CCSize size);
    static MyTableView* create(TableViewDataSource* dataSource, CCSize size, CCNode *container);
    
protected:
    CCPoint m_beginPoint;
    CCPoint m_lastPoint;
    struct timeval m_beginTime;
    struct timeval m_endTime;
};


#endif
#endif /* MyTableView_hpp */
