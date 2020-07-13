#ifndef ENEMYPLANE_H
#define ENEMYPLANE_H
#include "enemybullet.h"


#include <QPixmap>

class EnemyPlane1
{
public:
    EnemyPlane1();

    void shoot();

    //更新坐标
    void updatePosition();
public:
    //敌机资源对象
    QPixmap m_enemy;
    int x;

    //位置
    int m_X;
    int m_Y;

    //敌机的矩形边框（碰撞检测）
    QRect m_Rect;

    //状态
    bool m_Free;

    //速度
    int m_Speed;
    //弹匣
    enemyBullet m_bullets[BULLET_NUM];

    //发射间隔记录
    int m_recorder;
    int interval_Bullet=2;
};
class EnemyPlane2
{
public:
    EnemyPlane2();

    void shoot();

    //更新坐标
    void updatePosition();
public:
    //敌机资源对象
    QPixmap m_enemy;
    int x;

    //位置
    int m_X;
    int m_Y;

    //敌机的矩形边框（碰撞检测）
    QRect m_Rect;

    //状态
    bool m_Free;

    //速度
    int m_Speed;
    //弹匣
    enemyBullet m_bullets[BULLET_NUM];

    //发射间隔记录
    int m_recorder;
    int interval_Bullet=2;

};


#endif // ENEMYPLANE_H
