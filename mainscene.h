#ifndef MAINSCENE_H
#define MAINSCENE_H

#include <QWidget>
#include <QTimer>
#include "map.h"
#include "heroplane.h"
#include "bullet.h"
#include "enemyplane.h"
#include "bomb.h"
#include <QSound>
#include<QPushButton>
#include<QLabel>
#include<QSpinBox>
class Start :public QWidget
{
    Q_OBJECT
public:
    Start();
    Data_Options of_start;
public slots:
    void play();
    void set();
    void end();
    void paintEvent(QPaintEvent*ev);
private:
    QPushButton start;
    QPushButton options;
    QPushButton back;
    QPixmap start_pixmap;
};

class MainScene : public QWidget
{
    Q_OBJECT

public:
    MainScene(QWidget *parent = 0,Start* fa=0,Data_Options* a=0);
    ~MainScene();
    //返回父窗口
    void goback();
    //初始化场景
    void initScene();

    //启动游戏  用于启动定时器对象
    void playGame();
    //更新坐标
    void updatePosition();
    //绘图事件
    void paintEvent(QPaintEvent *event);

    //重写鼠标移动事件
    void mouseMoveEvent(QMouseEvent *);
    //重写键盘敲击事件
    void keyPressEvent(QKeyEvent *event);
    //敌机出场
    void enemyToScene1();
    void enemyToScene2();
    //碰撞检测
    void collisionDetection();

    //地图对象
    Map m_map;

    //创建飞机对象
    HeroPlane m_hero;


    //定时器对象
    QTimer m_Timer;


    //敌机数组

    EnemyPlane1 m_enemys1[ENEMY_NUM];
    EnemyPlane2 m_enemys2[ENEMY_NUM];

    //敌机出场间隔记录
    int m_recorder1;
    int m_recorder2;
    //爆炸数组
    int q=ENEMY_BLOOD1;
    int p=ENEMY_BLOOD2;
    Bomb m_bombs[BOMB_NUM];

    int gobacktime=0;
    int score=0;
    QLabel sco1,sco2;
    Start* father;
    Data_Options player_option;
    //测试子弹
    //Bullet temp_Bullet;

};

class OptionScene:public QWidget
{
    Q_OBJECT
public:
    OptionScene(Start* pa);
    QSpinBox choice_blood,choice_speed,choice_interval,choice_bullet_interval;
    QLabel a,b,c,d;
    QPushButton back;
    void goback();
    void paintEvent(QPaintEvent *event);
private:
    Start* fa;
    QPixmap option_pixmap;
};

#endif // MAINSCENE_H
