#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"


using namespace std;
using namespace cocostudio::timeline;

static std::vector<Point> neighbor = {Point(-1,1),Point(0,1),Point(1,1),Point(-1,0),Point(1,0),Point(-1,-1),Point(0,-1),Point(1,-1)};
static int s_matchedBallCounter = 0;
static std::vector<int> s_matchedBallTagList;
static std::vector<std::vector<int>> s_vBallSearchlist;


Scene* HelloWorld::createScene()
{
    auto scene = Scene::create();
    auto layer = HelloWorld::create();
    scene->addChild(layer);

    return scene;
}

bool HelloWorld::init()
{
  
    if ( !Layer::init() )
    {
        return false;
    }
    vBallGrid = std::vector<vector<int>>(GRID_ROW_MAX , std::vector<int> (BALL_COL_MAX,0));
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(true);
    touchListener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
    touchListener->onTouchCancelled = CC_CALLBACK_2(HelloWorld::onTouchCancelled, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    auto rootNode = CSLoader::createNode("SceneGame.csb");
    addChild(rootNode,-1);
    sprCanon = (Sprite*) rootNode->getChildByName("sprCanon");
//    TMXTiledMap* _tileMap = TMXTiledMap::create("res/untitled.tmx");
//    addChild(_tileMap,-1);
//    
//   
//    
//    auto stencil = DrawNode::create();
//    stencil->drawSolidCircle(visibleSize/2, 50.0f, 0.0f, 32.0f, Color4F::GREEN);
//    //addChild(stencil);
//    auto clipper = ClippingNode::create();
//    clipper->setStencil(stencil);
//    auto sprite = Sprite::create("res/image/ground_pt.png");
//    sprite->setPosition(Vec2( visibleSize.width/2 , 10));
//    clipper->addChild(sprite);
//    clipper->setInverted(true);
//    clipper->setAlphaThreshold(1000.5f);
//    //clipper->setTag(100);
//    addChild(clipper,-1);
//    
//     auto mask = Sprite::create("res/image/mask_star.png");
//     auto object = Sprite::create("res/image/ground_pt.png");
    
//    CCMask* masked = CCMask::create(mask , object);
//    masked->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2));
//    this->addChild(masked);
    
    return true;
}
bool HelloWorld::onTouchBegan(Touch* touch, Event* event)
{
    Point pt = touch->getLocation();
     log("[onTouchBegan] [%f,%f]",pt.x,pt.y);
    Point pOfGrid = tileCoordForPosition(pt);
    auto diff =  touch->getLocation() - sprCanon->getPosition();
    _prevAngle = CC_RADIANS_TO_DEGREES(atan2(diff.x, diff.y));
    auto angle = CC_RADIANS_TO_DEGREES(atan2(diff.x, diff.y));
    sprCanon->setRotation(angle);
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    Point p = tileCoordForPosition(Point(pt.x,pt.y ));
    log("=> GridPos [%f,%f]",p.x,p.y);
    CCParticleSystemQuad * smokeParticle = CCParticleSystemQuad::create("res/particle/particle_yellow_circle_click.plist");
    smokeParticle->setPosition(posOfGridCord(p));
    smokeParticle->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
    this->addChild(smokeParticle);
    smokeParticle->setAutoRemoveOnFinish(true);
    int color = vBallGrid[p.y][p.x];
   
    if(color <= 0)
    {
        
        color = cocos2d::random(1, 4);
        string path = StringUtils::format("res/image/ball0%d.png", color);
        Sprite* ball = (Sprite*)this->getChildByTag(p.x +100 + p.y*BALL_COL_MAX);
        if(ball!= nullptr)
        {
            ball->setVisible(true);
            ball->setTexture(path);
        }
        else
        {
            Sprite* ball = Sprite::create(path);
            ball->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
            ball->setPosition(posOfGridCord(p));
            ball->setTag(p.x +100 + p.y*BALL_COL_MAX);
            auto label = Label::createWithSystemFont(StringUtils::toString(ball->getTag()) , "Arial", 24);
            ball->addChild(label);
            label->setPosition(25, 25);
            addChild(ball);
            
        }
        log("Add ball [%f,%f]",p.x,p.y);
        int x = p.x;
        int y = p.y;
        vBallGrid[y][x] = color;
      
    }

        s_vBallSearchlist.clear();
        s_matchedBallTagList.clear();
        std::copy(vBallGrid.begin(), vBallGrid.end(),std::back_inserter(s_vBallSearchlist));
       
        findMatchColor(p,color);
        log("The number of matched ball %d",s_matchedBallTagList.size());
        
    return true;
}
void HelloWorld::onTouchMoved(Touch* touch, Event* event)
{
    auto diff = touch->getLocation() - sprCanon->getPosition();
    auto angle = CC_RADIANS_TO_DEGREES(atan2(diff.x, diff.y));
    sprCanon->setRotation(angle);
}

void HelloWorld::onTouchEnded(Touch* touch, Event* event)
{
    Point pt = touch->getLocation();
    CCPoint touchLocation = touch->getLocationInView();
    touchLocation = CCDirector::sharedDirector()->convertToGL(touchLocation);
    touchLocation = this->convertToNodeSpace(touchLocation);
    
    if(s_matchedBallTagList.size() >= 3)
    {
        for(int tag:s_matchedBallTagList)
        {
            Sprite* ball = (Sprite*)this->getChildByTag(tag);
            ball->setVisible(false);
            Point p = tileCoordForPosition(ball->getPosition());
            int x = p.x;
            int y = p.y;
            vBallGrid[y][x] = 0;
        }
    }
    s_matchedBallTagList.clear();
}


void HelloWorld::onTouchCancelled(Touch* touch, Event* event)
{
    cocos2d::log("touch cancelled");
}

Point HelloWorld::tileCoordForPosition(Point position)
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    int x = (position.x + BALL_W/2)/ BALL_W;
    //int y = (visibleSize.height - position.y + BALL_W/2) / BALL_W;
    int y = (1250 - position.y + BALL_W/2) / BALL_W;
    return Point(x, y);
}

Point HelloWorld::posOfGridCord(Point position)
{
    return Point(position.x*BALL_W,1250-position.y*BALL_W);
}

void HelloWorld::findMatchColor(Point p,int color)
{
    log("[findMatchColor] color:%d, p:%f:%f",color,p.x,p.y);
    if(p.x < 0 ||  p.x >= BALL_COL_MAX ) return;
    if(p.y < 0 ||  p.y >= GRID_ROW_MAX ) return;
    if (s_vBallSearchlist[p.y][p.x] == 0 || s_vBallSearchlist[p.y][p.x] == 10 ) return;
    if (s_vBallSearchlist[p.y][p.x] == color )
    {
        s_vBallSearchlist[p.y][p.x] = 0;
        s_matchedBallTagList.push_back(getTagNumber(p));
        Sprite* b = (Sprite*) getChildByTag(getTagNumber(p));
        log("[findMatchColor] tag num:%d",getTagNumber(p));
        if(b!= nullptr){
            //b->setVisible(false);
            //b->setTexture("res/image/ball50x50_selected.png");
           
//            Sprite* ball_mask = Sprite::create("res/image/ball50x50_selected.png");
//            ball_mask->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
//            ball_mask->setPosition(b->getPosition());
//            b->addChild(ball_mask,1, "HIGHLIGHT");
        }
        for(Point pp: neighbor)
        {
            findMatchColor(p - pp, color);
        }
    }
    
   
    return;
}

int HelloWorld::getTagNumber(Point p)
{
    return p.x + p.y*BALL_COL_MAX +100;
}

void HelloWorld::resetGame()
{
    
}
void HelloWorld::startGame()
{
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    int x = origin.x;
    int y = 1250;
   
    //std::vector<std::vector<int>> fog(10, std::vector<int>(15));
    for(int i = 0; i< BALL_ROW_MAX; i++ )
    {
        std::vector<int> rowOfBall;
        //x = origin.x - (i%2)*25;
        for(int j = 0; j < BALL_COL_MAX; j++)
        {
            int random_v = cocos2d::random(1, 4);
            string path = StringUtils::format("res/image/ball0%d.png", random_v);
            //Ball* ball = new Ball();
            Sprite* ball = Sprite::create(path);
            ball->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
            ball->setPosition(Vec2(x + j*50,y - i*50));
            auto rotation = RotateBy::create(1.0f, 90.0f);
            //ball->runAction(RepeatForever::create(rotation));
            ball->setTag(j+ (i*BALL_COL_MAX) + 100);
            auto label = Label::createWithSystemFont(StringUtils::toString(ball->getTag()) , "Arial", 24);
            ball->addChild(label);
            label->setPosition(25, 25);
            addChild(ball);
            rowOfBall.push_back(random_v);
            vBallGrid[i][j] = random_v;
        }
        //vBallGrid.push_back(rowOfBall);
    }
}
