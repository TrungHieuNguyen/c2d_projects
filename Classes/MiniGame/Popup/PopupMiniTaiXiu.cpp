
#include <climits>
#include "PopupMiniTaiXiu.hpp"


//#include "../Utility/AppUtil.h"
#define W 710.00
#define H 552

PopupMiniTaiXiu* PopupMiniTaiXiu::instance = 0;
PopupMiniTaiXiu * PopupMiniTaiXiu::gI()
{
    
    if (instance == NULL){
        instance = PopupMiniTaiXiu::create();
    }
    return instance;
}

// on "init" you need to initialize your instance
bool PopupMiniTaiXiu::init()
{
    //////////////////////////////
    // 1. super init first
    bool pRet = false;
    if (Popup::init())
    {
        instance = this;
        setAnchorPoint(Vec2::ANCHOR_MIDDLE);
        setIgnoreAnchorPointForPosition(false);
       
        mainNode = CSLoader::createNode("");
        mainNode->setIgnoreAnchorPointForPosition(false);
        mainNode->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
        setContentSize(mainNode->getContentSize());
        mainNode->setScale(0);
        mainNode->setPosition(getContentSize()/2);
        addChild(mainNode);
        
        txtTitle = mainNode->getChildByName<Text*>("txtTitle");
        btnLS = mainNode->getChildByName<Button*>("btnLichSu");
        btnLS->setPressedActionEnabled(true);
        btnLS->addClickEventListener([&](Ref* sender){
            if(btnTK)
                btnTK->setEnabled(true);
            if(btnTT)
                btnTT->setEnabled(true);
            if(btnLS)
                btnLS->setEnabled(false);
            if(btnHD)
                btnHD->setEnabled(true);
            if(txtTitle) txtTitle->setString("LỊCH SỬ");
            nodeLichSuPage->setVisible(true);
            nodeTKPage01->setVisible(false);
            nodeTKPage02->setVisible(false);
        });
        btnTK = mainNode->getChildByName<Button*>("btnThongKe");
        btnTK->setPressedActionEnabled(true);
        btnTK->addClickEventListener([&](Ref* sender)
        {
            if(btnTK)
                btnTK->setEnabled(false);
            if(btnTT)
                btnTT->setEnabled(true);
            if(btnLS)
                btnLS->setEnabled(true);
            if(btnHD)
                btnHD->setEnabled(true);
            if(txtTitle) txtTitle->setString("THỐNG KÊ");
            nodeLichSuPage->setVisible(false);
            nodeTKPage01->setVisible(true);
            nodeTKPage02->setVisible(false);
            
           
        });
        btnHD = mainNode->getChildByName<Button*>("btnHuongDan");
        btnHD->setPressedActionEnabled(true);
        btnHD->addClickEventListener([&](Ref* sender){
            if(btnTK)
                btnTK->setEnabled(true);
            if(btnTT)
                btnTT->setEnabled(true);
            if(btnLS)
                btnLS->setEnabled(true);
            if(btnHD)
                btnHD->setEnabled(false);
            if(txtTitle) txtTitle->setString("HƯỚNG DẪN");
            nodeLichSuPage->setVisible(false);
            nodeTKPage01->setVisible(false);
            nodeTKPage02->setVisible(false);
            
        });
        btnTT = mainNode->getChildByName<Button*>("btnThanhTich");
        btnTT->setPressedActionEnabled(true);
        btnTT->addClickEventListener([&](Ref* sender){
            if(btnTK)
                btnTK->setEnabled(true);
            if(btnTT)
                btnTT->setEnabled(false);
            if(btnLS)
                btnLS->setEnabled(true);
            if(btnHD)
                btnHD->setEnabled(true);
            if(txtTitle) txtTitle->setString("THÀNH TÍCH");
            nodeLichSuPage->setVisible(false);
            nodeTKPage01->setVisible(false);
            nodeTKPage02->setVisible(false);
        });
        auto btnClose = mainNode->getChildByName<Button*>("btnClose");
        btnClose->setPressedActionEnabled(true);
        btnClose->addClickEventListener([&](Ref* sender){
            this->close();
        });
        nodeTKPage01 = mainNode->getChildByName<Layout*>("pnlThongke01");
        nodeTKPage02 = mainNode->getChildByName<Layout*>("pnlThongke02");
        nodeTKPage02->setVisible(false);
        nodeLichSuPage = mainNode->getChildByName<Layout*>("pnlLichSu");
        nodeLichSuPage->setVisible(false);
        auto btnNext = nodeTKPage01->getChildByName<Button*>("btnNext");
        btnNext->setPressedActionEnabled(true);
        btnNext->addClickEventListener([&](Ref* sender){
            nodeTKPage01->setVisible(false);
            nodeTKPage02->setVisible(true);
            
        });
        auto btnBack = nodeTKPage02->getChildByName<Button*>("btnBack");
        btnBack->setPressedActionEnabled(true);
        btnBack->addClickEventListener([&](Ref* sender){
            nodeTKPage01->setVisible(true);
            nodeTKPage02->setVisible(false);
            
        });

        
        tableView = cocos2d::extension::TableView::create(this, Size(800, 420));
        tableView->setDirection(cocos2d::extension::ScrollView::Direction::VERTICAL);
        tableView->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
        tableView->setColor(Color3B::RED);
        tableView->setIgnoreAnchorPointForPosition(false);
        tableView->setPosition(nodeLichSuPage->getContentSize()/2);
        tableView->setDelegate(this);
        tableView->setVerticalFillOrder(cocos2d::extension::TableView::VerticalFillOrder::TOP_DOWN);;
        nodeLichSuPage->addChild(tableView, 10);
        tableView->reloadData();
        initBgDark();
        removeBgTouch();
        return true;
    }
    return pRet;
}

void PopupMiniTaiXiu::initType(long _min, long _max,long tableBet,int _id, string _pass,
                                bool _invited, bool _login)
{

}

void PopupMiniTaiXiu::close()
{
    CallFuncN * cal = CallFuncN::create([&](Ref *target){
        if  (layerBG != nullptr && layerBG->getParent() != nullptr)
        {
            layerBG->removeFromParent();
            layerBG = nullptr;
        }
        Popup::close();
    });
    
    mainNode->runAction(Sequence::create(CallFuncN::create([&](Ref* sender){
        this->fadeOutBgDark();
    }), ScaleTo::create(0.1, 1.1), ScaleTo::create(0.1, 0),cal ,NULL));
}

void PopupMiniTaiXiu::removePopup(){
    if(instance != nullptr){
        instance->close();
    }
}

PopupMiniTaiXiu::~PopupMiniTaiXiu()
{
    instance = nullptr;
}


void PopupMiniTaiXiu::open()
{
    mainNode->runAction(Sequence::create(ScaleTo::create(0.2, 1.1), ScaleTo::create(0.2, 1.0), NULL));
//    ActionInterval* move = MoveTo::create(0.5, Point(getContentSize().width/2, getContentSize().height/2));
//    ActionInterval* move_ease = EaseBackInOut::create(
//                                                      (ActionInterval*) (move->clone()));
//    mainNode->runAction(move_ease);
}

//void PopupMiniTaiXiu::setPositionType(TypeEase type)
//{
//    switch (type) {
//        case TypeEase::TOP:
//        {
//            mainNode->setPosition(getContentSize().width/2, - getContentSize().height * 2);
//        }
//            break;
//        case TypeEase::DOWN:
//        {
//            mainNode->setPosition(getContentSize().width/2, getContentSize().height * 2);
//        }
//            break;
//        case TypeEase::RIGHT:
//        {
//            mainNode->setPosition(getContentSize().width * 2.5, getContentSize().height/2);
//        }
//            break;
//        case TypeEase::LEFT:
//        {
//            mainNode->setPosition(-getContentSize().width * 2.5, getContentSize().height/2);
//        }
//            break;
//        default:
//            break;
//    }
//}
Size PopupMiniTaiXiu::cellSizeForTable(cocos2d::extension::TableView *table)
{
    return Size(800, 100);
}


void PopupMiniTaiXiu::scrollViewDidScroll(cocos2d::extension::ScrollView* view){
    
}

void PopupMiniTaiXiu::scrollViewDidZoom(cocos2d::extension::ScrollView* view){
    
}

void PopupMiniTaiXiu::tableCellTouched(cocos2d::extension::TableView* table, cocos2d::extension::TableViewCell* cell)
{
//    layerContent->setVisible(false);
//    layerDetail->setVisible(true);
//    idFocus = cell->getIdx();
//    ValueMap value = arrData.at(idFocus).asValueMap();
//    string id = value["id"].asString();
//    string title = value["title"].asString();
//    string content = value["content"].asString();
//    string date = value["time"].asString();
//    string sender = value["sender"].asString();
//    string is_read = value["view"].asString();
//    lbTitle->setString(title);
//    lbDetail->setString(content);
//    lbDetailDate->setString(date);
//    lbDetailSender->setString(sender);
//    if(id.length() > 0)
//    {
//        //PopupWaiting::gI()->show();
//
//
//    }
}

ssize_t PopupMiniTaiXiu::numberOfCellsInTableView(cocos2d::extension::TableView *table)
{
    return arrData.size();
}
cocos2d::extension::TableViewCell* PopupMiniTaiXiu::tableCellAtIndex(cocos2d::extension::TableView *table, ssize_t idx)
{
    auto index = StringUtils::format("%ld", static_cast<long>(idx));
    cocos2d::extension::TableViewCell *cell = table->dequeueCell();
    ValueMap value = arrData.at(idx).asValueMap();
    string sender = value["sender"].asString();
    string title = value["title"].asString();
    string time = value["time"].asString();
    bool isRead = value["view"].asBool();
    int mail_id = value["id"].asInt();
    if (!cell)
    {
        cell = new cocos2d::extension::TableViewCell();
        cell->autorelease();
        auto font_size = 27;
        Label * lbTitle = Label::createWithTTF("", FONT_AVENIR_REGULAR, 24);
        lbTitle->setColor(Color3B::YELLOW);
        lbTitle->setDimensions(100, 0);
        lbTitle->setHorizontalAlignment(cocos2d::TextHAlignment::LEFT);
        lbTitle->setIgnoreAnchorPointForPosition(false);
        lbTitle->setAnchorPoint(Point(0, 0.5f));
        lbTitle->setTag(9990);
        cell->addChild(lbTitle);
        lbTitle->setPosition(200, 30);
        
    }
    Label * lbSender = (Label*)cell->getChildByTag(9990);
    Label * lbContent = (Label*)cell->getChildByTag(9991);
    Label * lbTime = (Label*)cell->getChildByTag(9993);
    
    string font = FONT_AVENIR_REGULAR;
    string icon_path =  "studio/popup/mail.png";
    string bg_path =  "studio/popup/box_mail.png"; //box_mail.png
    int bg_z_oder = -1;
    if (isRead){
        icon_path = "studio/popup/mail_open.png";
        bg_path =  "studio/popup/box_hide.png";
        bg_z_oder = 1;
    }
    
    Sprite *icon = (Sprite*)cell->getChildByTag(9994);
    
    if (icon != nullptr)
    {
        icon->setTexture(icon_path);
        icon->setTextureRect(Rect(Point::ZERO, icon->getTexture()->getContentSize()));
    }
    

    return cell;
}
