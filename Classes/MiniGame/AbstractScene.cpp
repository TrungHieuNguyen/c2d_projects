//
//  AbstractScene.cpp
//  ChipGame-mobile
//
//  Created by TrungHieu on 11/30/17.
//

#include "AbstractScene.hpp"
#include "MainScene.hpp"
void AbstractScene::clickBtnBack(Ref* sender)
{
    
}
bool AbstractScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    visibleSize = Director::getInstance()->getVisibleSize();
    return true;
}
 void AbstractScene:: updateScore(int score)
{
        Sprite* sprMoneyBar = layerHUD->getChildByName<Sprite*>("sprMoneyBar");
        Text* lbMoneyValue = sprMoneyBar->getChildByName<Text*>("lbMoney");
        lbMoneyValue->setString(std::to_string(score));
        Sprite* sprCoinBar = layerHUD->getChildByName<Sprite*>("sprCoinBar");
        Text* lbCoinValue = sprCoinBar->getChildByName<Text*>("lbCoin");
        lbCoinValue->setString(std::to_string(score));
}
void AbstractScene::hideHUD()
{
    layerHUD->stopAllActions();
    ActionInterval* hud_move = MoveTo::create(0.7, Point(layerHUD->getContentSize().width/2, visibleSize.height -70));
    ActionInterval* hud_move_ease = EaseBackInOut::create((ActionInterval*) (hud_move->clone()));
    layerHUD->runAction(hud_move_ease);
}
void AbstractScene::showHUD()
{
    layerHUD = CSLoader::createNode(SCENE_GAME_HUD_CSB);
    layerHUD->setAnchorPoint(Point(0.5f, 0.5f));
    layerHUD->setPosition(Vec2(layerHUD->getContentSize().width/2,visibleSize.height + 70));
    layerHUD->stopAllActions();
    ActionInterval* hud_move = MoveTo::create(0.7, Point(layerHUD->getContentSize().width/2, visibleSize.height -70));
    ActionInterval* hud_move_ease = EaseBackInOut::create((ActionInterval*) (hud_move->clone()));
    
    Button* btnBack = (Button*) layerHUD->getChildByName("btnBack");
    btnBack->setPressedActionEnabled(true);
    btnBack->addClickEventListener([&](Ref* sender){
        
        Director::getInstance()->replaceScene(MainScene::createScene());
        
        
    });
    layerHUD->runAction(hud_move_ease);
    addChild(layerHUD, Z_ODER_HUD);
}
void AbstractScene::showGold(long long _gold, bool isWin)
{
    log("showGold %lld", _gold);
    
    const char* fontRes = FONT_BITMAP_LOSE_EFF;
    std::string strGold = StringUtils::toString(_gold);
    if(_gold > 0 )
    {
        fontRes = FONT_BITMAP_WIN_EFF;
    }
    
    auto _lbGold = Label::createWithBMFont(fontRes,  strGold);
    _lbGold->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    _lbGold->setPosition(150, 100);
    addChild(_lbGold,1000);
    _lbGold->runAction(Sequence::create(FadeIn::create(0.3f),Spawn::create( MoveBy::create(3, Vec2(0,150)),FadeOut::create(1.5f),NULL),RemoveSelf::create(), NULL));
    
}
void AbstractScene::showResult(PlayerRank stt, int delay)
{
    const char* res = "images/texts/hoa.png";
    log("setResultPLayer %d",stt);
    
    if (stt == HIDE){
    }
    else if(stt ==RANK_NHAT)
    {

       res = "images/texts/nhat.png";
    }
    auto label = Sprite::create(res);
    addChild(label, 100);
    label->setPosition(90,100);
    label->runAction(Sequence::create(Spawn::create(ScaleTo::create(0.1f, 1.3f) ,FadeIn::create(0.3f), NULL),DelayTime::create(delay),RemoveSelf::create(), NULL));
}
void AbstractScene::showTextGame(string text)
{
    auto labelAction = Label::createWithBMFont( FONT_BITMAP_WIN_EFF,text);
    labelAction->setHorizontalAlignment(TextHAlignment::CENTER);
    labelAction->setAnchorPoint(Point(0.5f, 0.5f));
    labelAction->setPosition(visibleSize/2);
    addChild(labelAction,1000);
    labelAction->setOpacity(0);
    labelAction->runAction(Sequence::create(Spawn::create(ScaleTo::create(0.1f, 2.0f) ,FadeIn::create(0.3f), NULL),DelayTime::create(1),RemoveSelf::create(), NULL));
    
}
void AbstractScene::goMainScreen()
{
    Director::getInstance()->replaceScene(MainScene::createScene());
}
