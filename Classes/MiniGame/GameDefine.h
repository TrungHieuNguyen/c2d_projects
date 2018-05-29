//
//  GameDefine.h
//  ChipGame
//
//  Created by Nguyen Trung Hieu on 8/24/17.
//
//

#ifndef GameDefine_h
#define GameDefine_h






///////////////////////////////////////////////////
#define Z_ODER_TILEMAP 1
#define Z_ODER_HUD 2
#define Z_ODER_POPUP 3

#define WIDTH_CARD 70
#define HEIGHT_CARD 100

///////////////////////////////////////////////////
//         CSB DEFINED
///////////////////////////////////////////////////
#define SCENE_MAIN_CSB          "MainScene.csb"
#define SCENE_GAME_CSB        "GameScene.csb"
#define SCENE_GAME2D_CSB        "Game2D.csb"
#define SCENE_GAME3D_CSB        "Game3D.csb"
#define SCENE_GAME_TILEDMAP_CSB "GameTiledMap.csb"
#define SCENE_ABOUT_CSB         "AboutScene.csb"
#define SCENE_SLOT_CSB         "ScreenSlot.csb"
#define SCENE_GAME_HUD_CSB      "HUDLayer.csb"

#define RES_SLIDER_DATCHUONG_CSB    "SilderDatChuong10.csb"
#define RES_SLIDER_RESULT_CSB       "WinLoseResult.csb"

#define BM_FONT_WORD "fonts/font_word.fnt"
#define FONT_AVENIR_REGULAR "fonts/AvenirNextCondensed-Regular.ttf"
#define FONT_BUTTON "fonts/AvenirNextCondensed-Regular.ttf"
#define FONT_AVENIR_BOLD "fonts/AvenirNextCondensed-Bold.ttf"
#define FONT_AVENIR_MEDIUM "fonts/AvenirNextCondensed-Medium.ttf"
#define FONT_BITMAP_WIN_EFF "fonts/font_win_eff.fnt"
#define FONT_BITMAP_LOSE_EFF "fonts/font_lost_eff.fnt"


enum PlayerType
{
    PlayerNoThing   =   -1,
    PlayerBottom    =   0,
    PlayerLeft      =   1,
    PlayerTop       =   2,
    PlayerRight     =   3,
};



enum class HeroState
{
    STAND,
    LEFT,
    RIGHT,
    UP,
    DOWN,
    HURT,
    ATTACH,
    SHOOT,
    JUMP,
    DIE,
    DIZZY,
    THROUGH,
    RUN,
    FLY,
    END,
};


#endif /* GameDefine_h */
