//
//  MyTableView.cpp
//  ChipGame-mobile
//
//  Created by TrungHieu on 6/21/18.
//

#include "MyTableView.hpp"
#include <stdlib.h>


MyTableView* MyTableView::create(TableViewDataSource* dataSource, Size size)
{
    return MyTableView::create(dataSource, size, nullptr);
}

MyTableView* MyTableView::create(TableViewDataSource* dataSource, CCSize size, CCNode *container)
{
    MyTableView *table = new MyTableView();
    table->initWithViewSize(size, container);
    table->autorelease();
    table->setDataSource(dataSource);
    table->_updateCellPositions();
    table->_updateContentSize();
    
    return table;
}

bool MyTableView::onTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    m_beginPoint = pTouch->getLocation();
    ::gettimeofday(&m_beginTime, NULL);
    CCLog("touch begin");
    return TableView::ccTouchBegan(pTouch, pEvent);
    
}

void MyTableView::onTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
    m_lastPoint = pTouch->getLocation();
    TableView::ccTouchMoved(pTouch, pEvent);
}

void MyTableView::onTouchEnded(Touch *pTouch, CCEvent *pEvent)
{
    CCLog("touch end");
    ::gettimeofday(&m_endTime, NULL);
    
    if (!this->isVisible()) {
        return;
    }
    
    /// 判断是否有移动
    bool isTouchMove = true;
    float moveRange = 10; // 移动范围小于10个像素
    CCLog("bt:%d,%d", m_beginTime.tv_sec, m_beginTime.tv_usec);
    CCLog("et:%d,%d", m_endTime.tv_sec, m_endTime.tv_usec);
    long timediff = m_endTime.tv_sec - m_beginTime.tv_sec;
    timediff = timediff* 1000 + (m_endTime.tv_usec - m_beginTime.tv_usec)/1000;
    CCLog("timediff:%ld", timediff);
    // 触屏时间少于150ms
    if (timediff < 150) {
        float dx = m_beginPoint.x - m_lastPoint.x;
        float dy = m_beginPoint.y - m_lastPoint.y;
        CCLog("bp:%f,%f", m_beginPoint.x, m_beginPoint.y);
        CCLog("ep:%f,%f, %f, %f", m_lastPoint.x, m_lastPoint.y, dx, dy);
        if ((-moveRange < dx &&  dx < moveRange) && (-moveRange < dy && dy < moveRange)) {
            isTouchMove = false;
        }
    //
    //    if (pTouch->count() == 1 && !isTouchMove) {
    //        CCLog("TableView::ccTouchEnded not move");
    //        unsigned int        index;
    //        TableViewCell   *cell;
    //        Point           point;
    //
    //        point = this->getContainer()->convertTouchToNodeSpace(pTouch);
    //        if (m_eVordering == kTableViewFillTopDown) {
    //            CCSize cellSize = m_pDataSource->cellSizeForTable(this);
    //            point.y -= cellSize.height;
    //        }
    //        index = this->_indexFromOffset(point);
    //        cell  = this->_cellWithIndex(index);
    //
    //        if (cell) {
    //            m_pTableViewDelegate->tableCellTouched(this, cell);
    //        }
    //    }
    ScrollView::onTouchEnded(pTouch, pEvent);
    }
}
