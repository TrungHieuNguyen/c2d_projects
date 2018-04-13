//
//  PopupMail.hpp
//  CoCaNgua
//
//  Created by Tien Bao Nguyen on 9/23/16.
//
//

#ifndef PopupMail_hpp
#define PopupMail_hpp

#include <stdio.h>
#include "cocos2d.h"
#include "PopupAbstract.hpp"
using namespace ui;

class PopupMail : public PopupAbstract,
public cocos2d::extension::TableViewDataSource,
public cocos2d::extension::TableViewDelegate
{
    Node * mainLayer;
    ValueVector arrData;
    TableView * tableView;
    void clickBack(Ref * sender);
    Node * layerContent;
    Node * layerDetail;
    Text * lbDetail;
    Text * lbTitle;
public: //sss
    static PopupMail* gI();
    static PopupMail* instance;
    PopupMail();
    virtual ~PopupMail();
    CREATE_FUNC(PopupMail);
    virtual bool init();
    void readData(CCMessage * mess);
protected:
    virtual void							scrollViewDidScroll(cocos2d::extension::ScrollView* view);
    virtual void							scrollViewDidZoom(cocos2d::extension::ScrollView* view);
    virtual void							tableCellTouched(cocos2d::extension::TableView* table, cocos2d::extension::TableViewCell* cell);
    virtual									cocos2d::extension::TableViewCell* tableCellAtIndex(cocos2d::extension::TableView *table, ssize_t idx);
    virtual									ssize_t numberOfCellsInTableView(cocos2d::extension::TableView *table);
    virtual Size cellSizeForTable(TableView *table);
    
};

#endif /* PopupMail_hpp */
