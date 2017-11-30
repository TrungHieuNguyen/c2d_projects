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
void AbstractScene::goMainScreen()
{
    Director::getInstance()->replaceScene(MainScene::createScene());
}
