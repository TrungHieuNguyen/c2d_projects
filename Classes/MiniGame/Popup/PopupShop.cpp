//
//  PopupResult.cpp
//  ChipGame
//
//  Created by Nguyen Trung Hieu on 9/6/17.
//
//

#include "PopupShop.hpp"
#include "GameDefine.h"
#include "ui/CocosGUI.h"
#include "../cocos/editor-support/cocostudio/CocoStudio.h"

#define W 1000
#define H 600

#define WTAB 800
#define HTAB 400

#define WCELL 270
#define HCELL 350

PopupShop* PopupShop::instance = 0;
PopupShop * PopupShop::gI()
{
    
    if (instance == NULL){
        instance = PopupShop::create();
    }
    return instance;
}

PopupShop::PopupShop()
{
    
}


PopupShop::~PopupShop()
{
    
    instance = nullptr;
}

bool PopupShop::init()
{
    bool pRet = false;
    if (Popup::init())
    {
        initBgDark();
        auto visibleSize = Director::getInstance()->getVisibleSize();
        Vec2 origin = Director::getInstance()->getVisibleOrigin();
        mainLayer = CSLoader::createNode(RES_SLIDER_RESULT_CSB);
        mainLayer->setAnchorPoint(Point(0.5f, 0.5f));
        mainLayer->setPosition(Vec2(visibleSize.width/2 , visibleSize.height/2));
        
        auto layerContent = mainLayer->getChildByName("pnlProducts");
        tableView = TableView::create(this, Size(WTAB, HTAB));
        tableView->setDirection(cocos2d::extension::ScrollView::Direction::HORIZONTAL);
        tableView->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
        tableView->setColor(Color3B::RED);
        tableView->setIgnoreAnchorPointForPosition(false);
        tableView->setPosition(layerContent->getContentSize()/2);
        tableView->setDelegate(this);
        tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);;
        layerContent->addChild(tableView, 10);
        tableView->reloadData();
        
        cocos2d::ui::Button *btnClose = (ui::Button*)mainLayer->getChildByName("btnClose");
        btnClose->addClickEventListener(CC_CALLBACK_1(PopupShop::clickClose, this));
        this->addChild(mainLayer,101);
        removeBgTouch();
        pRet = true;
    }
    return pRet;
}

void PopupShop::open()
{
    mainLayer->setScale(0);
    mainLayer->runAction(Sequence::create(ScaleTo::create(0.2, 1.1), ScaleTo::create(0.2, 1.0), NULL));
    for (int i = 0; i < 6; i++)
    {
        ValueMap value;
        value["id"] = "om.nyc.csclient.cashpack";
        value["cash"] = "0.99USD";
        value["tier"] = arc4random()%2;
        arrData.push_back((cocos2d::Value)value);
    }
    vector<IAPItem> mailList;
//    if (result.empty()) return;
//    cocos2d::Value value = JSONUtils::gI()->valueFromString(result);
//    ValueMap map = (!value.isNull()) ? value.asValueMap() : ValueMapNull;
//    ValueVector& frameArray = map["data"].asValueVector();
//
//    arrData.clear();
//    for (auto& item : frameArray)
//    {
//        arrData.push_back((cocos2d::Value)item);
//    }
    if(arrData.size()<=0)
    {
        auto emptySprite = Sprite::create("studio/popup/icon_kohang.png");
        emptySprite->setAnchorPoint(Vec2::ZERO);
        emptySprite->setPosition(mainLayer->getContentSize().width/2 - emptySprite->getContentSize().width/2, mainLayer->getContentSize().height/2 - emptySprite->getContentSize().height/2);
        mainLayer->addChild(emptySprite,1,"ICON_EMPTY_ITEM");
    }
    else
    {
        Sprite* emptySprite = (Sprite*) mainLayer->getChildByName("ICON_EMPTY_ITEM");
        if(emptySprite!=nullptr)
        {
            emptySprite->setVisible(false);
        }
        
    }
    tableView->reloadData();
}
void PopupShop::close()
{
    CallFuncN * cal = CallFuncN::create([&](Ref *target){
//        if  (layerBG != nullptr && layerBG->getParent() != nullptr)
//        {
//            layerBG->removeFromParent();
//            layerBG = nullptr;
//        }
        Popup::close();
    });
    
    mainLayer->runAction(Sequence::create(CallFuncN::create([&](Ref* sender){
        this->fadeOutBgDark();
    }), ScaleTo::create(0.1, 1.1), ScaleTo::create(0.1, 0),cal ,NULL));
}
void PopupShop::clickClose(Ref * sender)
{
    close();
}

TableViewCell* PopupShop::tableCellAtIndex(cocos2d::extension::TableView *table, ssize_t idx)
{
    auto index = StringUtils::format("%ld", static_cast<long>(idx));
    TableViewCell *cell = table->dequeueCell();
    ValueMap value = arrData.at(idx).asValueMap();
    string time = value["time"].asString();
    string cash = "0.0";
    string coin = "1.0";
    string formatedTime = value["formattedTime"].asString();
    string sku = value["id"].asString();
    
    if (!cell)
    {
        cell = new TableViewCell();
        cell->autorelease();
        
        Label * lbCoin = Label::createWithTTF("", FONT_AVENIR_REGULAR, 40);
        lbCoin->setColor(Color3B::YELLOW);
        lbCoin->setDimensions(WCELL - 50, 0);
        lbCoin->setHorizontalAlignment(cocos2d::TextHAlignment::CENTER);
        lbCoin->setIgnoreAnchorPointForPosition(false);
        lbCoin->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
        lbCoin->setTag(9990);
        //lbCoin->setName("AAA");
        cell->addChild(lbCoin);
        lbCoin->setPosition(WCELL/2, HCELL-50);
        
        auto star = Sprite::create("res/images/popup/frame_light.png");
        star->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
        star->setPosition(Vec2(WCELL/2, HCELL/2));
        cell->addChild(star, 0);
        auto icon = Sprite::create("res/images/popup/coin.png");
        icon->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
        icon->setPosition(Vec2(WCELL/2, HCELL/2));
        icon->setTag(9992);
        cell->addChild(icon, 0);
        
        auto btnItem = Button::create("res/images/popup/frame_money.png", "studio/popup/frame_money.png", "studio/popup/frame_money.png");
        btnItem->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
        btnItem->setPosition(Vec2(WCELL/2 , 50));
        btnItem->setPressedActionEnabled(true);
        btnItem->setTag(9991);
        cell->addChild(btnItem,0);
        
        Label * lbCash = Label::createWithTTF("", FONT_AVENIR_REGULAR, 42);
        lbCash->setColor(Color3B::YELLOW);
        lbCash->setDimensions(WCELL - 50, 0);
        lbCash->setHorizontalAlignment(cocos2d::TextHAlignment::CENTER);
        lbCash->setIgnoreAnchorPointForPosition(false);
        lbCash->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
        lbCash->setTag(9993);
        cell->addChild(lbCash);
        lbCash->setPosition(WCELL/2, 50);
        
        auto bg = Sprite::create("res/images/popup/frame_pur.png");
        bg->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
        bg->setTag(9995);
        bg->setPosition(Vec2(0, 0));
        bg->setAnchorPoint(Vec2::ANCHOR_BOTTOM_LEFT);
        cell->addChild(bg,-1);
        
    }
    
    Label * lbCoinValue = (Label*)cell->getChildByTag(9990);
    Button* btnItem = (Button*) cell->getChildByTag(9991);
    Label * lbCashValue = (Label*)cell->getChildByTag(9993);
    //Sprite* sprIcon = (Sprite*) cell->getChildByTag(9992);
    //    string icon_path = "studio/popup/coin" + index + ".png";
    //    if(sprIcon!= nullptr){
    //        sprIcon->setTexture(icon_path);
    //        sprIcon->setTextureRect(Rect(Point::ZERO, sprIcon->getTexture()->getContentSize()));
    //    }
    
    string font = FONT_AVENIR_REGULAR;
    if (lbCoinValue != nullptr){
        lbCoinValue->setString(coin);
        TTFConfig config = lbCoinValue->getTTFConfig();
        config.fontFilePath = font;
        lbCoinValue->setTTFConfig(config);
    }
    if (lbCashValue != nullptr)
    {
        lbCashValue->setString(cash);
        TTFConfig config = lbCashValue->getTTFConfig();
        config.fontFilePath = font;
        lbCashValue->setTTFConfig(config);
    }
    if (btnItem != nullptr)
    {
        btnItem->addClickEventListener([&, this, sku](Ref* sender){
            log("Buy item %s", sku.c_str());
         
            
        });
    }
    return cell;
}
void PopupShop::scrollViewDidScroll(cocos2d::extension::ScrollView* view){}
void PopupShop::scrollViewDidZoom(cocos2d::extension::ScrollView* view){}
void PopupShop::tableCellTouched(cocos2d::extension::TableView* table, cocos2d::extension::TableViewCell* cell){}

ssize_t PopupShop::numberOfCellsInTableView(cocos2d::extension::TableView *table){
    return arrData.size();
    
}
Size PopupShop::cellSizeForTable(TableView *table)
{
     return Size(WCELL+30, HCELL);
}
IAPItem::IAPItem()
{
    index = -1;
    gold = "";
    id = "";
}

IAPItem::~IAPItem()
{
    
}

ItemCell::ItemCell(Size size)
{
}

ItemCell::~ItemCell()
{
}


void ItemCell::setdata(IAPItem item, int i)
{
    index->setString(StringUtils::toString( item.getIndex()));
    id->setString(item.getID());
    gold->setString(item.getGold());
}
