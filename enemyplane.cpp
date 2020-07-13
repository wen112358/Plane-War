#include "enemyplane.h"
#include "config.h"
#include <ctime>

EnemyPlane1::EnemyPlane1()
{

    //敌机资源加载

    m_enemy.load(ENEMY_PATH1);


    //敌机位置
    m_X = 0;
    m_Y = 0;


    //敌机状态
    m_Free = true;

    //敌机速度
    m_Speed = 1;

    //敌机矩形
    m_Rect.setWidth(m_enemy.width());
    m_Rect.setHeight(m_enemy.height());
    m_Rect.moveTo(m_X,m_Y);
}

void EnemyPlane1::updatePosition()
{
    //空闲状态，不计算坐标
    if(m_Free)
    {
        return;
    }

    m_Y += m_Speed;
    m_Rect.moveTo(m_X,m_Y);

    if(m_Y >= GAME_HEIGHT)
    {
        m_Free = true;
    }}
void EnemyPlane1::shoot()
{

    //累加事件间隔记录的变量
    m_recorder++;


    //如果记录数字 未达到发射间隔，直接return
    if(m_recorder < BULLET_INTERVAL1*interval_Bullet)
    {
        return;
    }

    m_recorder = 0;

    //发射子弹
    for(int i = 0 ; i < BULLET_NUM;i++)
    {
        //如果是空闲状态的子弹，发射子弹
        if(m_bullets[i].m_Free)
        {
            m_bullets[i].m_Free = false;
            m_bullets[i].m_X = m_X+m_Rect.width()*0.5 - 10;
            m_bullets[i].m_Y = m_Y +25 ;
            break;
        }

    }
}
EnemyPlane2::EnemyPlane2()
{

    //敌机资源加载

    m_enemy.load(ENEMY_PATH2);


    //敌机位置
    m_X = 0;
    m_Y = 0;

    //敌机状态
    m_Free = true;

    //敌机速度
    m_Speed = 1;

    //敌机矩形
    m_Rect.setWidth(m_enemy.width());
    m_Rect.setHeight(m_enemy.height());
    m_Rect.moveTo(m_X,m_Y);
}

void EnemyPlane2::updatePosition()
{
    //空闲状态，不计算坐标
    if(m_Free)
    {
        return;
    }

    m_Y += m_Speed;
    m_Rect.moveTo(m_X,m_Y);

    if(m_Y >= GAME_HEIGHT)
    {
        m_Free = true;
    }}
void EnemyPlane2::shoot()
{

    //累加事件间隔记录的变量
    m_recorder++;


    //如果记录数字 未达到发射间隔，直接return
    if(m_recorder < BULLET_INTERVAL1*interval_Bullet)
    {
        return;
    }

    m_recorder = 0;

    //发射子弹
    for(int i = 0 ; i < BULLET_NUM;i++)
    {
        //如果是空闲状态的子弹，发射子弹
        if(m_bullets[i].m_Free)
        {
            m_bullets[i].m_Free = false;
            m_bullets[i].m_X = m_X+m_Rect.width()-100;
            m_bullets[i].m_Y = m_Y + 25 ;
            break;
        }

    }
    for(int i = 0 ; i < BULLET_NUM;i++)
    {
        //如果是空闲状态的子弹，发射子弹
        if(m_bullets[i].m_Free)
        {
            m_bullets[i].m_Free = false;
            m_bullets[i].m_X = m_X+m_Rect.width()-20;
            m_bullets[i].m_Y = m_Y + 25 ;
            break;
        }

    }
}


