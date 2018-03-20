#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#define BALL_W 72
#define BALL_SIZE 150
#define BALL_COL_MAX 12
#define BALL_ROW_MAX 15
#define GRID_COL_MAX 15
#define GRID_ROW_MAX 30
#include "cocos2d.h"
USING_NS_CC;
using namespace std;
class Ball : public Sprite
{
    public:
    int _index;
    int color_index;
};


class HelloWorld : public cocos2d::Layer
{
    std::vector<std::vector<int>> vBallGrid;
    std::vector<Sprite*> vBalls;
    Sprite* sprCanon;
    float _prevAngle;
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    virtual bool onTouchBegan(cocos2d::Touch*, cocos2d::Event*);
    virtual void onTouchEnded(cocos2d::Touch*, cocos2d::Event*);
    virtual void onTouchMoved(cocos2d::Touch*, cocos2d::Event*);
    virtual void onTouchCancelled(cocos2d::Touch*, cocos2d::Event*);
    Point tileCoordForPosition(Point);
    Point posOfGridCord(Point);
    int getTagNumber(Point p);
    void findMatchColor(Point p,int color);
    void addHUD();
    void resetGame();
    void startGame();
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
