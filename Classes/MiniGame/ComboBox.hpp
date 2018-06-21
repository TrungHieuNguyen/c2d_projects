//
//  ComboBox.hpp
//  ChipGame-mobile
//
//  Created by TrungHieu on 6/21/18.
//

#ifndef ComboBox_hpp
#define ComboBox_hpp

#include <stdio.h>
#ifndef __COMBOBOX_H__
#define __COMBOBOX_H__

#include "cocos2d.h"
#include "cocos-ext.h"
#include "MyTableView.hpp"
#include <vector>

USING_NS_CC;
USING_NS_CC_EXT;


typedef std::vector<std::string> ComboBoxDataList;

class ComboBoxTableViewLayer;

class ComboBox : public Layer
{
public:
    ComboBox();
    virtual ~ComboBox();
    bool init(const char* text, const char* bgImg, const char* btnImg, const char* hightLightBtnImg, const char* cellBackGround, int fontSize, float borderPix, const char* font);
    static ComboBox* create(const char* text, const char* bgImg, const char* btnImg, const char* hightLightBtnImg, const char* cellBackGround, int fontSize, float borderPix, const char* font="Marker Felt");
    
    bool onTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    void onTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    void onTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    void onTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
    
    void touchUpInside(Object* pSender, Event event);
    
    void setComboBoxDataList(const ComboBoxDataList& dataList) ;
    void setComboBoxDataFromContinuousInt(int start, int end, int step=1);
    void setComboBoxDataFromContinuousFloat(float start, float end, float step=1.0);
    void clearDataList();
    
    const char* getLabel();
    void setLabel(const char* label);
    
protected:
    void setContentSize(const CCSize& s);
    
protected:
    CCLabelTTF* m_label;
    ControlButton* m_button;
    Scale9Sprite* m_backGround;
    ComboBoxTableViewLayer* m_tableViewLayer;
    ComboBoxDataList m_dataList;
    
    const char* m_cellBackGround;
    const char* m_font;
    float m_borderPix;
    float m_fontSize;
    
    
};


class ComboBoxTableViewLayer : public Layer, public TableViewDataSource, public TableViewDelegate
{
public:
    ComboBoxTableViewLayer();
    ~ComboBoxTableViewLayer();
    
    virtual bool init(ComboBoxDataList* dataList, const char* cellBackGround, float borderPix, float fontSize, const char* font);
    
    static ComboBoxTableViewLayer* create(ComboBox* frame, ComboBoxDataList* dataList, const char* cellBackGround, float borderPix, float fontSize, const char* font);
    
    void reloadDataList();
    MyTableView* getTableView() { return m_tableView; }
    
    virtual void scrollViewDidScroll(ScrollView* view) {};
    virtual void scrollViewDidZoom(ScrollView* view) {}
    virtual void tableCellTouched(TableView* table, TableViewCell* cell);
    virtual CCSize cellSizeForTable(TableView *table);
    virtual TableViewCell* tableCellAtIndex(TableView *table, unsigned int idx);
    virtual ssize_t numberOfCellsInTableView(TableView *table);
    void setFrame(ComboBox* frame) { m_frame = frame;}
    
    bool onTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    void onTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    void onTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    void onTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
    
    
    
    void onEnter();
    void onExit();
    
    
protected:
    const char* m_cellBackGround;
    float m_borderPix;
    float m_fontSize;
    const char* m_font;
    CCRect m_backGroundRect;
    CCRect m_backGroundRectInsets;
    ComboBoxDataList* m_dataList;
    MyTableView* m_tableView;
    ComboBox* m_frame;
    
protected:
    virtual       cocos2d::extension::TableViewCell* tableCellAtIndex(cocos2d::extension::TableView *table, ssize_t idx);

    
};



#endif
#endif /* ComboBox_hpp */
