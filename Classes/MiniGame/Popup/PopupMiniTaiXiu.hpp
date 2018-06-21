
#ifndef PopupMiniTaiXiu_hpp
#define PopupMiniTaiXiu_hpp

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

class PopupMiniTaiXiu : public Popup,
public cocos2d::extension::TableViewDataSource,
public cocos2d::extension::TableViewDelegate
{
    Node * mainNode;
    Layout * nodeTKPage01;
    Layout * nodeTKPage02;
    Layout * nodeLichSuPage;
    cocos2d::extension::TableView* tableView;
    Node * spTextfield;
    long betGoldTable;
    ValueVector arrData;
    
protected:
    virtual void  scrollViewDidScroll(cocos2d::extension::ScrollView* view);
    virtual void  scrollViewDidZoom(cocos2d::extension::ScrollView* view);
    virtual void  tableCellTouched(cocos2d::extension::TableView* table, cocos2d::extension::TableViewCell* cell);
    virtual       cocos2d::extension::TableViewCell* tableCellAtIndex(cocos2d::extension::TableView *table, ssize_t idx);
    virtual       ssize_t numberOfCellsInTableView(cocos2d::extension::TableView *table);
    virtual Size  cellSizeForTable(cocos2d::extension::TableView *table);
    
public:
   
    
    Button * btnOk;
    Button * btnCancel;
    
    Button * btnHD;
    Button * btnTT;
    Button * btnLS;
    Button * btnTK;

    Text * txtTitle;
    Text * txtMaxValue;
    Text * txtSelectedValue;


    static PopupMiniTaiXiu* gI();
    static PopupMiniTaiXiu* instance;
    virtual bool init();
    virtual ~PopupMiniTaiXiu();
    CREATE_FUNC(PopupMiniTaiXiu);
    void initType(long,long,long,int tableID, string pass,
                  bool isInvited,bool login);
    void close();
    static void removePopup();
    void open();
    //void setPositionType(TypeEase type);
    
};

#endif /* PopupMiniTaiXiu_hpp */
