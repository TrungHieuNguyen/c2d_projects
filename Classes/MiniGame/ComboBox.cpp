//
//  ComboBox.cpp
//  ChipGame-mobile
//
//  Created by TrungHieu on 6/21/18.
//

#include "ComboBox.hpp"

ComboBox::ComboBox()
:m_label(NULL), m_button(NULL), m_backGround(NULL), m_tableViewLayer(NULL)
{
}

ComboBox::~ComboBox()
{
    if (m_label) {
        m_label->release();
    }
    if (m_button) {
        m_button->release();
    }
    if (m_backGround) {
        m_backGround->release();
    }
    
    if (m_tableViewLayer) {
        m_tableViewLayer->release();
    }
}

ComboBox* ComboBox::create(const char* text, const char* bgImg, const char* btnImg, const char* hightLightBtnImg, const char* cellBackGround, int fontSize, float border, const char* font )
{
    ComboBox* comboBox = new ComboBox();
    if (comboBox && comboBox->init(text, bgImg, btnImg, hightLightBtnImg, cellBackGround, fontSize, border, font)) {
        comboBox->autorelease();
        return comboBox;
    } else {
        delete comboBox;
        return NULL;
    }
}

const char* ComboBox::getLabel()
{
    return m_label->getString().c_str();
}

void ComboBox::setLabel(const char* label)
{
    m_label->setString(label);
}

bool ComboBox::init(const char* text, const char* bgImg, const char* btnImg, const char* hightLightBtnImg, const char* cellBackGround, int fontSize, float borderPix,  const char* font)
{
    m_cellBackGround = cellBackGround;
    m_borderPix = borderPix;
    m_fontSize = (float)fontSize;
    m_font = font;
    
    if (!CCLayer::init()) {
        return false;
    }
    
    // 支持AnchorPoint定位, 默认情况下Layer不支持
    ignoreAnchorPointForPosition(false);
    
    // 支持触屏
    setTouchEnabled(true);
    
    // 创建Label
    CCSize size;
    m_label = CCLabelTTF::create(text, font, fontSize);
    if (!m_label) return false;
    m_label->setPosition(ccp(m_label->getContentSize().width/2, m_label->getContentSize().height/2));
    m_label->retain();
    addChild(m_label, 1);
    size = m_label->getContentSize();
    
    // 创建按钮
    float space = 3;
    
    /// 由于按钮图片可能是大图片，需要收缩，所以采用三个参数的create，需要先获取图片大小
    Sprite* tsp = Sprite::create(btnImg);
    Size s = tsp->getContentSize();
    Rect imgRect = CCRectMake(0,0, s.width, s.height);
    Rect imgRectInsets = CCRectMake(borderPix, borderPix, s.width-2*borderPix, s.height-2*borderPix);
    tsp->release();
    
    Scale9Sprite *backgroundButton = Scale9Sprite::create(btnImg, imgRect, imgRectInsets);
    Scale9Sprite *backgroundHighlightedButton = Scale9Sprite::create(hightLightBtnImg, imgRect, imgRectInsets);
    m_button = ControlButton::create(backgroundButton);
    m_button->setZoomOnTouchDown(false);
    //m_button->setBackgroundSpriteForState(backgroundHighlightedButton, ControlStateHighlighted);
    m_button->setPreferredSize(CCSizeMake(size.height, size.height));
    m_button->setPosition(m_label->getContentSize().width + m_button->getContentSize().width/2 + space, m_button->getContentSize().height/2);
    //m_button->addTargetWithActionForControlEvents(this, cccontrol_selector(ComboBox::touchUpInside), ControlEventTouchUpInside);
    m_button->retain();
    addChild(m_button, 1);
    
    size.width += m_button->getContentSize().width + space;
    if (m_button->getContentSize().height > size.height) {
        size.height = m_button->getContentSize().height;
    }
    
    // 创建背景, 背景图片正常都是拉伸，用一个参数的create够了，如果背景还搞大图片，那就不能怪我了。。。
    m_backGround = Scale9Sprite::create(bgImg);
    m_backGround->setPreferredSize(size);
    m_backGround->setPosition(ccp(m_backGround->getContentSize().width/2, m_backGround->getContentSize().height/2));
    m_backGround->retain();
    addChild(m_backGround, 0);
    
    this->setContentSize(size);
    
//    m_tableViewLayer = ComboBoxTableViewLayer::create(&m_dataList, cellBackGround, borderPix, (float)fontSize, font);
//    m_tableViewLayer->retain();
}

void ComboBox::setComboBoxDataList(const ComboBoxDataList& dataList)
{
    m_dataList = dataList;
}

void ComboBox::setComboBoxDataFromContinuousInt(int start, int end, int step)
{
    char buf[50];
    for (int i=start; i <= end; i+=step)
    {
        sprintf(buf, "%d", i);
        m_dataList.push_back(buf);
    }
}
void ComboBox::setComboBoxDataFromContinuousFloat(float start, float end, float step)
{
    char buf[50];
    for (float i=start; i <= end; i+=step)
    {
        sprintf(buf, "%f", i);
        m_dataList.push_back(buf);
    }
}

void ComboBox::clearDataList()
{
    m_dataList.clear();
}

void ComboBox::setContentSize(const CCSize& s)
{
    CCLayer::setContentSize(s);
}


bool ComboBox::onTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    CCPoint p = m_button->getPosition();
    p.x+=1;
    p.y+=1;
    pTouch->setTouchInfo(pTouch->getID(), p.x, p.y);
    m_button->ccTouchBegan(pTouch, pEvent);
    return true;    // 屏蔽该消息不往下传递
}

void ComboBox::onTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
    CCPoint p = m_button->getPosition();
    p.x+=1;
    p.y+=1;
    pTouch->setTouchInfo(pTouch->getID(), p.x, p.y);
    m_button->ccTouchMoved(pTouch, pEvent);
}

void ComboBox::onTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    CCPoint p = m_button->getPosition();
    p.x+=1;
    p.y+=1;
    pTouch->setTouchInfo(pTouch->getID(), p.x, p.y);
    m_button->ccTouchEnded(pTouch, pEvent);
}

void ComboBox::onTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{
    CCPoint p = m_button->getPosition();
    p.x+=1;
    p.y+=1;
    pTouch->setTouchInfo(pTouch->getID(), p.x, p.y);
    m_button->ccTouchEnded(pTouch, pEvent);
}

void ComboBox::touchUpInside(Object* pSender,Event event)
{
    CCLog("touchUpInside");
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    float fontSize = (float)m_fontSize/2;
    if (fontSize < 20) {
        fontSize = 20;
    }
    ComboBoxTableViewLayer* layer = ComboBoxTableViewLayer::create(this, &m_dataList, m_cellBackGround, m_borderPix, fontSize, m_font);
    layer->setAnchorPoint(ccp(0.5,0.5));
    layer->setPosition(ccp(winSize.width/2, winSize.height/2));
    CCScene* curScene = CCDirector::sharedDirector()->getRunningScene();
    int cnt = curScene->getChildrenCount();
    CCLog("cnt=%d", cnt);
    curScene->addChild(layer, cnt+15);
}




ComboBoxTableViewLayer::ComboBoxTableViewLayer()
:m_tableView(NULL)
{
}

ComboBoxTableViewLayer::~ComboBoxTableViewLayer()
{
    CC_SAFE_RELEASE(m_tableView);
}

ComboBoxTableViewLayer* ComboBoxTableViewLayer::create(ComboBox* frame, ComboBoxDataList* dataList, const char* cellBackGround, float borderPix, float fontSize, const char* font)
{
    ComboBoxTableViewLayer* layer = new ComboBoxTableViewLayer();
    if (layer && layer->init(dataList, cellBackGround, borderPix, fontSize, font)) {
        layer->setFrame(frame);
        layer->autorelease();
        return layer;
    }else {
        CC_SAFE_DELETE(layer);
        return NULL;
    }
}

bool ComboBoxTableViewLayer::init(ComboBoxDataList* dataList, const char* cellBackGround, float borderPix, float fontSize, const char* font)
{
    m_dataList = dataList;
    m_cellBackGround = cellBackGround;
    m_borderPix = borderPix;
    m_fontSize = fontSize;
    m_font = font;
    
    CCLog("ComboBoxTableViewLayer, cellBackGround=%s, borderPix=%f, fontSize=%f, font=%s", m_cellBackGround, m_borderPix, m_fontSize, m_font);
    
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    /// 支持锚点
    ignoreAnchorPointForPosition(false);
    
    // 先保存图片的大小
    CCSprite* tps = CCSprite::create(cellBackGround);
    CCSize s = tps->getContentSize();
    m_backGroundRect = CCRectMake(0,0, s.width, s.height);
    m_backGroundRectInsets = CCRectMake(m_borderPix, m_borderPix, s.width-2*m_borderPix, s.height-2*m_borderPix);
    tps->release();
    
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    CCSize contentSize = CCSizeMake(winSize.width*0.9, winSize.height*0.9);
    
    m_tableView = MyTableView::create(this, contentSize);
    m_tableView->setDirection(TableView::Direction::VERTICAL);
    m_tableView->setDelegate(this);
    m_tableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
    m_tableView->reloadData();
    m_tableView->retain();
    this->addChild(m_tableView);
    
    setContentSize(contentSize);
    
    CCSize sx = getContentSize();
    CCLog("cctt.w,h:%f,%f", sx.width, sx.height);
    
    return true;
}


void ComboBoxTableViewLayer::tableCellTouched(TableView* table, TableViewCell* cell)
{
    CCLog("cell touched at index: %i", cell->getIdx());
    const char* name = ((LabelTTF*)(cell->getChildByTag(123)))->getString().c_str();
    m_frame->setLabel(name);
    this->removeFromParentAndCleanup(true);
}

CCSize ComboBoxTableViewLayer::cellSizeForTable(TableView *table)
{
    CCSize contentSize = getContentSize();
    return CCSizeMake(contentSize.width, m_fontSize+15);
}

TableViewCell* ComboBoxTableViewLayer::tableCellAtIndex(TableView *table, unsigned int idx)
{
    std::string str = (*m_dataList)[idx];
    TableViewCell *cell = table->dequeueCell();
    
    if (!cell) {
        CCLog("add str:%s", str.c_str());
        CCSize s = cellSizeForTable(NULL);
        cell = new TableViewCell();
        cell->autorelease();
        Scale9Sprite* backGround = Scale9Sprite::create(m_cellBackGround, m_backGroundRect, m_backGroundRectInsets);
        backGround->setContentSize(s);
        backGround->setPosition(CCPointZero);
        backGround->setAnchorPoint(CCPointZero);
        cell->addChild(backGround, 0);
        CCLabelTTF *label = CCLabelTTF::create(str.c_str(), m_font, m_fontSize);
        label->setPosition(Point::ZERO);
        label->setAnchorPoint(Point::ZERO);
        label->setTag(123);
        cell->addChild(label, 1);
    }
    else
    {
        LabelTTF *label = (CCLabelTTF*)cell->getChildByTag(123);
        label->setString(str.c_str());
    }
    
    return cell;
}

ssize_t ComboBoxTableViewLayer::numberOfCellsInTableView(TableView *table)
{
    return m_dataList->size();
}

void ComboBoxTableViewLayer::reloadDataList()
{
    m_tableView->reloadData();
}

bool ComboBoxTableViewLayer::onTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    m_tableView->ccTouchBegan(pTouch, pEvent);
    return true;
}

void ComboBoxTableViewLayer::onTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
    m_tableView->ccTouchMoved(pTouch, pEvent);
}

void ComboBoxTableViewLayer::onTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    m_tableView->ccTouchEnded(pTouch, pEvent);
}

void ComboBoxTableViewLayer::onTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{
    m_tableView->ccTouchEnded(pTouch, pEvent);
}


void ComboBoxTableViewLayer::onEnter()
{
    CCLayer::onEnter();
    //Director::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, -129, true);
}

void ComboBoxTableViewLayer::onExit()
{
    CCLayer::onExit();
    //Director::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}
cocos2d::extension::TableViewCell* ComboBoxTableViewLayer::tableCellAtIndex(cocos2d::extension::TableView *table, ssize_t idx){}

