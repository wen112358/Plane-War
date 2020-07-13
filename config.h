#ifndef CONFIG_H
#define CONFIG_H

class Data_Options
{
public:
    int Hero_Blood=5;
    int Enenmy_Interval=10;
    int Enenmy_Speed=1;
    int Enenmy_Bullet_Interval=2;
};


/**********  游戏配置数据 **********/
#define GAME_WIDTH  512  //宽度
#define GAME_HEIGHT 768  //高度
#define GAME_TITLE "飞机大战 v1.0" //标题
#define GAME_RES_PATH "./plane.rcc" //二进制资源路径
#define GAME_ICON ":/res/app.ico"  //图标路径
#define GAME_RATE  10  //单位毫秒
#define START_PATH ":/res/start.jpg"
#define OPTION_PATH ":/res/img_bg_level_3.jpg"
/**********  地图配置数据 **********/
#define MAP_PATH  ":/res/img_bg_level_2.jpg" //地图图片路径
#define MAP_SCROLL_SPEED 2  //地图滚动速度
#define MOVE_SPEED 5
/**********  飞机配置数据 **********/
#define HERO_PATH ":/res/hero2.png"
/**********  子弹配置数据 **********/
#define BULLET_PATH ":/res/bullet_11.png"   //子弹图片路径
#define BULLET2_PATH ":/res/bullet_10.png"
#define ENEMY_BULLET_PATH ":/res/bullet_3.png" //敌机子弹图片路径
#define BULLET_SPEED 5  //子弹移动速度
#define BULLET_NUM 100   //弹匣中子弹总数
#define BULLET_INTERVAL 20 //发射子弹时间间隔
#define BULLET_INTERVAL1 100 //敌人发射子弹时间间隔
/**********  敌机配置数据 **********/
#define ENEMY_PATH1  ":/res/img-plane_4.png"  //敌机资源图片
#define ENEMY_PATH2  ":/res/img-plane_5.png"  //敌机资源图片
//#define ENEMY_SPEED 1  //敌机移动速度
#define ENEMY_NUM   20  //敌机总数量
//#define ENEMY_INTERVAL1  100 //敌机1出场时间间隔
//#define ENEMY_INTERVAL2  400  //敌机2出场时间间隔
#define ENEMY_BLOOD1  3  //敌机1血量
#define ENEMY_BLOOD2  5  //敌机2血量
/**********  爆炸配置数据 **********/
#define BOMB_PATH  ":/res/bomb-%1.png"   //爆炸资源图片
#define BOMB_NUM  20     //爆炸数量
#define BOMB_MAX  7      //爆炸图片最大索引
#define BOMB_INTERVAL 20   //爆炸切图时间间隔

#define SOUND_BACKGROUND ":/res/bg.wav" //背景音乐
#define SOUND_BOMB ":/res/bomb.wav" //爆炸音效

#endif // CONFIG_H
