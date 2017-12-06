//
//  PopupResult.hpp
//  ChipGame
//
//  Created by Nguyen Trung Hieu on 9/6/17.
//
//

#ifndef PopupIap_hpp
#define PopupIap_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "Popup.hpp"
#include "GameDefine.h"
using namespace::cocos2d;
using namespace::extension;
using namespace::ui;
using namespace std;

class IAPItem : public Ref
{
public:
    IAPItem();
    virtual ~IAPItem();
private:
    CC_SYNTHESIZE(int, index, Index);
    CC_SYNTHESIZE(std::string, id, ID);
    CC_SYNTHESIZE(std::string, gold, Gold);
    
};

class ItemCell : public Node
{
    cocos2d::ui::Scale9Sprite*              sprBg;
    Text*                                    index;
    Text*                                    id;
    Text*                                    gold;
    
public:
    string                                    uid;
    ItemCell(Size size);
    virtual ~ItemCell();
    void     setdata(IAPItem ref, int id);
};


class PopupShop : public Popup,
public cocos2d::extension::TableViewDataSource,
public cocos2d::extension::TableViewDelegate
{
   
    static PopupShop* instance;
    Node * mainLayer;
    ValueVector arrData;
    TableView * tableView;
    
    PopupShop();
    virtual ~PopupShop();
    CREATE_FUNC(PopupShop);
public:
    static PopupShop* gI();
    virtual bool init();
    void open();
    void close();
    void readData();
    void clickClose(Ref * sender);
    
protected:
    virtual void scrollViewDidScroll(cocos2d::extension::ScrollView* view);
    virtual void scrollViewDidZoom(cocos2d::extension::ScrollView* view);
    virtual void tableCellTouched(cocos2d::extension::TableView* table, cocos2d::extension::TableViewCell* cell);
    virtual      cocos2d::extension::TableViewCell* tableCellAtIndex(cocos2d::extension::TableView *table, ssize_t idx);
    virtual      ssize_t numberOfCellsInTableView(cocos2d::extension::TableView *table);
    virtual Size cellSizeForTable(TableView *table);
};
#endif /* PopupIap_hpp */
