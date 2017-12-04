
#include "MainScene.hpp"
#include "ui/CocosGUI.h"
#include "../cocos/editor-support/cocostudio/CocoStudio.h"
#include "GameTiledMap.hpp"
#include "AbstractScene.hpp"
USING_NS_CC;

Scene* GameTiledMap::createScene()
{
    //return MainScene::create();
    auto scene = Scene::create();
    auto layer = GameTiledMap::create();
    scene->addChild(layer);
    return scene;
}

bool GameTiledMap::init()
{
    if ( !AbstractScene::init())
    {
        return false;
    }
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    initComponents();
     AbstractScene::showHUD();
    return true;
}

void GameTiledMap::initComponents()
{
    layerBG = CSLoader::createNode(SCENE_GAME_TILEDMAP_CSB);
    addChild(layerBG, -1);

    lbTitle = (Text*) layerBG->getChildByName("lbTitle");
    lbTitle->setIgnoreAnchorPointForPosition(false);
    lbTitle->setAnchorPoint(Point(0.5, 0.5f));
    
    Button* btnPlay = (Button*) layerBG->getChildByName("btnPlay");
    btnPlay->setPressedActionEnabled(true);
    btnPlay->addClickEventListener([&](Ref* sender){

        Director::getInstance()->replaceScene(MainScene::createScene());
    });
    
    _tileMap = TMXTiledMap::create("TiledMap/TileMap.tmx");
    _background = _tileMap->layerNamed("Background");
    _foreground = _tileMap->layerNamed("Foreground");
    _meta = _tileMap->layerNamed("Meta");
    _meta->setVisible(false);
    this->addChild(_tileMap,Z_ODER_TILEMAP);
    TMXObjectGroup *objectGroup = _tileMap->getObjectGroup("Objects");
    
    if(objectGroup == NULL){
        CCLog("tile map has no objects object layer");
        return;
    }
    // all tiles are aliased by default, let's set them anti-aliased
    for (const auto& child : _tileMap->getChildren())
    {
        static_cast<SpriteBatchNode*>(child)->getTexture()->setAntiAliasTexParameters();
    }
    ValueMap spawnPoint = objectGroup->getObject("SpawnPoint");
    float x  = spawnPoint["x"].asFloat();
    float y  = spawnPoint["y"].asFloat();
    

    //this->setViewPointCenter(_player->getPosition());
    
    

    
}
void GameTiledMap::setViewPointCenter(Point position) {
    return;
    
    CCSize winSize = Director::sharedDirector()->getWinSize();
    
    int x = MAX(position.x, winSize.width/2);
    int y = MAX(position.y, winSize.height/2);
    x = MIN(x, (_tileMap->getMapSize().width * this->_tileMap->getTileSize().width) - winSize.width / 2);
    y = MIN(y, (_tileMap->getMapSize().height * _tileMap->getTileSize().height) - winSize.height/2);
    Point actualPosition = ccp(x, y);
    Point centerOfView = ccp(winSize.width/2, winSize.height/2);
    Point viewPoint = ccpSub(centerOfView, actualPosition);
    this->setPosition(viewPoint);
}

void GameTiledMap::setPlayerPosition(CCPoint position)
{
    Point tileCoord = this->tileCoordForPosition(position);
    int tileGid = _meta->getTileGIDAt(tileCoord);
    if (tileGid) {
        ValueMap properties = _tileMap->getPropertiesForGID(tileGid).asValueMap();
        if (properties.size()) {
            String *collision = new String();
            *collision = properties["Collidable"].asString();
            if (collision && (collision->compare("True") == 0)) {
                return;
            }
            
            CCString *collectible = new CCString();
            *collectible = properties["Collectable"].asString();
            if (collectible && (collectible->compare("True") == 0)) {
                _meta->removeTileAt(tileCoord);
                _foreground->removeTileAt(tileCoord);
            }
        }
    }
    _player->setPosition(position);
}

CCPoint GameTiledMap::tileCoordForPosition(CCPoint position)
{
    int x = position.x / _tileMap->getTileSize().width;
    int y = ((_tileMap->getMapSize().height * _tileMap->getTileSize().height) - position.y) / _tileMap->getTileSize().height;
    return ccp(x, y);
}
void GameTiledMap::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
bool GameTiledMap::onTouchBegan(cocos2d::Touch*, cocos2d::Event*){}
void GameTiledMap::onTouchEnded(cocos2d::Touch*, cocos2d::Event*){}
void GameTiledMap::onTouchMoved(cocos2d::Touch*, cocos2d::Event*){}
void GameTiledMap::onTouchCancelled(cocos2d::Touch*, cocos2d::Event*){}
