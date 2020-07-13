#include "mainscene.h"
#include "config.h"
#include <QIcon>
#include <QPainter>
#include <QMouseEvent>
#include <ctime>
#include<QDebug>
#include<QString>
#include<QLabel>
MainScene::MainScene(QWidget *parent,Start* fa,Data_Options* a)
    : QWidget(parent)
{
    player_option=*a;
    sco1.setText("分数");
    sco2.setNum(score);
    sco1.move(400,0);
    sco1.resize(100,50);
    sco2.move(450,0);
    sco2.resize(200,50);
    sco1.setParent(this);
    sco2.setParent(this);
    father=fa;
    //调用初始化场景函数
    initScene();
}

MainScene::~MainScene()
{

}

void MainScene::initScene()
{
    //初始化窗口大小
    setFixedSize(GAME_WIDTH,GAME_HEIGHT);

    //设置窗口标题
    setWindowTitle(GAME_TITLE);

    //设置窗口标题
    setWindowIcon(QIcon(GAME_ICON));

    //设置定时器间隔
    m_Timer.setInterval(GAME_RATE);

    //初始化数据
    m_hero.m_health=player_option.Hero_Blood;
    for(int i=0;i<ENEMY_NUM;i++)
    {
        m_enemys1[i].m_Speed=player_option.Enenmy_Speed;
        m_enemys2[i].m_Speed=player_option.Enenmy_Speed;
        m_enemys1[i].interval_Bullet=player_option.Enenmy_Bullet_Interval;
        m_enemys2[i].interval_Bullet=player_option.Enenmy_Bullet_Interval;
    }

    //调用启动游戏接口
    playGame();

    //敌机出场纪录变量 初始化
    m_recorder1 = 0;
    m_recorder2 = 0;

    //随机数种子
    srand((unsigned int)time(NULL));  //头文件  #include <ctime>
}

void MainScene::playGame()
{
    //启动背景音乐
    //QSound::play(SOUND_BACKGROUND);

    //玩游戏 启动定时器
    m_Timer.start();

    //监听定时器的信号
    connect(&m_Timer , &QTimer::timeout,[=](){
        //敌机出场
        enemyToScene1();
        enemyToScene2();

        //更新游戏中所有元素的坐标
        updatePosition();
        //游戏中的元素 绘制到屏幕中
        update(); //再调用paintEvent函数

        //碰撞检测
        collisionDetection();
    });
}

void MainScene::updatePosition()
{
    //更新地图坐标
    m_map.mapPosition();
    //发射子弹
    if(m_hero.m_health>0)
    {
        m_hero.m_recorder++;
        m_hero.shoot();
    }
    for(int i=0;i<ENEMY_NUM;i++){
    if(m_enemys1[i].m_Free == false){
    m_enemys1[i].shoot();}
    if(m_enemys2[i].m_Free == false){
    m_enemys2[i].shoot();
    }
    }

    //计算子弹坐标
    for(int i = 0 ;i < BULLET_NUM;i++)
    {
        //如果子弹状态为非空闲，计算发射位置
        if(m_hero.m_bullets[i].m_Free == false)
        {
            m_hero.m_bullets[i].updatePosition();
        }

    }
    for(int i = 0 ;i < ENEMY_NUM;i++)
    {  for(int j=0;j<BULLET_NUM;j++){
        //如果子弹状态为非空闲，计算发射位置
        if(m_enemys1[i].m_bullets[j].m_Free == false)
        {
            m_enemys1[i].m_bullets[j].updatePosition();
        }
}
    }
        for(int i = 0 ;i < ENEMY_NUM;i++)
        {  for(int j=0;j<BULLET_NUM;j++){
            //如果子弹状态为非空闲，计算发射位置
            if(m_enemys2[i].m_bullets[j].m_Free == false)
            {
                m_enemys2[i].m_bullets[j].updatePosition();
            }
}
        }

    //敌机坐标计算
    for(int i = 0 ; i< ENEMY_NUM;i++)
    {
        //非空闲敌机 更新坐标
       if(m_enemys1[i].m_Free == false)
       {
          m_enemys1[i].updatePosition();
       }
    }
    for(int i = 0 ; i< ENEMY_NUM;i++)
    {
        //非空闲敌机 更新坐标
       if(m_enemys2[i].m_Free == false)
       {
          m_enemys2[i].updatePosition();
       }
    }
    //计算爆炸播放的图片
    for(int i = 0 ; i < BOMB_NUM;i++)
    {
        if(m_bombs[i].m_Free == false)
        {
           m_bombs[i].updateInfo();
        }
    }

    //测试子弹
//    temp_Bullet.m_Free = false;
//    temp_Bullet.updatePosition();
}
void MainScene::paintEvent(QPaintEvent *)
{
    //利用画家画图图片
    QPainter painter(this);

    //绘制地图
    painter.drawPixmap(0,m_map.m_map1_posY,m_map.m_map1);
    painter.drawPixmap(0,m_map.m_map2_posY,m_map.m_map2);

    //绘制飞机
    if(m_hero.m_health>0)
    {
        painter.drawPixmap(m_hero.m_X,m_hero.m_Y,m_hero.m_Plane);
    }
    //绘制子弹
    for(int i = 0 ;i < BULLET_NUM;i++)
    {
        //如果子弹状态为非空闲 ，绘制图片
        if(m_hero.m_bullets[i].m_Free == false)
        {
            if(!m_hero.type)
                painter.drawPixmap(m_hero.m_bullets[i].m_X,m_hero.m_bullets[i].m_Y,m_hero.m_bullets[i].m_Bullet);
            else painter.drawPixmap(m_hero.m_bullets[i].m_X,m_hero.m_bullets[i].m_Y,m_hero.m_bullets[i].m_Bullet2);
        }

    }
    for(int i = 0 ;i < ENEMY_NUM;i++)
    {
        //如果子弹状态为非空闲 ，绘制图片
        for(int j=0;j<BULLET_NUM;j++)
        if(m_enemys1[i].m_bullets[j].m_Free == false)
        {
            painter.drawPixmap(m_enemys1[i].m_bullets[j].m_X,m_enemys1[i].m_bullets[j].m_Y,m_enemys1[i].m_bullets[j].m_Bullet);
        }

    }
    for(int i = 0 ;i < ENEMY_NUM;i++)
    {
        //如果子弹状态为非空闲 ，绘制图片
        for(int j=0;j<BULLET_NUM;j++)
        if(m_enemys2[i].m_bullets[j].m_Free == false)
        {
            painter.drawPixmap(m_enemys2[i].m_bullets[j].m_X,m_enemys2[i].m_bullets[j].m_Y,m_enemys2[i].m_bullets[j].m_Bullet);
        }

    }

    //绘制敌机
    for(int i = 0 ; i< ENEMY_NUM;i++)
    {
        if(m_enemys1[i].m_Free == false)
        {
            painter.drawPixmap(m_enemys1[i].m_X,m_enemys1[i].m_Y,m_enemys1[i].m_enemy);
        }
    }
    for(int i = 0 ; i< ENEMY_NUM;i++)
    {
        if(m_enemys2[i].m_Free == false)
        {
            painter.drawPixmap(m_enemys2[i].m_X,m_enemys2[i].m_Y,m_enemys2[i].m_enemy);
        }
    }


    //绘制爆炸图片
    for(int i = 0 ; i < BOMB_NUM;i++)
    {
        if(m_bombs[i].m_Free == false)
        {
           painter.drawPixmap(m_bombs[i].m_X,m_bombs[i].m_Y,m_bombs[i].m_pixArr[m_bombs[i].m_index]);
        }
    }

    //测试子弹
    //painter.drawPixmap(temp_Bullet.m_X,temp_Bullet.m_Y,temp_Bullet.m_Bullet);

    //显示血量
    for(int i=0;i<m_hero.m_health;i++)
    {
        painter.drawRect(15*i,0,15,15);
        painter.fillRect(15*i,0,15,15,Qt::red);
    }

    //显示分数
    sco2.setNum(score);

    //失败界面
    if(gobacktime)
    {
        QFont font;
        font.setPixelSize(50);
        font.setStyle(QFont::StyleItalic);
        painter.setFont(font);
        painter.drawText(110,350,"You lose!");
    }

    //绘制边框  检查碰撞范围
       /* for(int i=0;i<ENEMY_NUM;i++)
        {
            if(!m_enemys1[i].m_Free)
            {
                painter.drawRect(m_enemys1[i].m_Rect);
                for(int j=0;j<BULLET_NUM;j++)
                {
                    if(!m_enemys1[i].m_bullets[j].m_Free)
                    {
                        painter.drawRect(m_enemys1[i].m_bullets[j].m_Rect);
                    }
                }
            }
            if(!m_enemys2[i].m_Free)
            {
                painter.drawRect(m_enemys2[i].m_Rect);
                for(int j=0;j<BULLET_NUM;j++)
                {
                    if(!m_enemys2[i].m_bullets[j].m_Free)
                    {
                        painter.drawRect(m_enemys2[i].m_bullets[j].m_Rect);
                    }
                }
            }
        }
        painter.drawRect(m_hero.m_Rect);
        for(int i=0;i<BULLET_NUM;i++)
        {
            if(!m_hero.m_bullets[i].m_Free)
                painter.drawRect(m_hero.m_bullets[i].m_Rect);
        }*/
}

void MainScene::mouseMoveEvent(QMouseEvent * event)
{
    int x =  event->x() -m_hero.m_Rect.width() * 0.5;
    int y =  event->y() -m_hero.m_Rect.height() *0.5;

    //边界检测

    if(x <= 0 )
    {
        x = 0;
    }
    if(x >= GAME_WIDTH - m_hero.m_Rect.width())
    {
        x = GAME_WIDTH - m_hero.m_Rect.width();
    }
    if(y <= 0)
    {
        y = 0;
    }
    if(y >= GAME_HEIGHT - m_hero.m_Rect.height())
    {
        y = GAME_HEIGHT - m_hero.m_Rect.height();
    }

    m_hero.setPosition(x,y);
}
void MainScene::keyPressEvent(QKeyEvent *event)
{
    if(event->key()==87)
        m_hero.m_Y-=MOVE_SPEED;
    if(event->key()==65)
        m_hero.m_X-=MOVE_SPEED;
    if(event->key()==83)
        m_hero.m_Y+=MOVE_SPEED;
    if(event->key()==68)
        m_hero.m_X+=MOVE_SPEED;
    if(event->key()==74)
        m_hero.shoot();
}
void MainScene::enemyToScene1()
{
    //累加出场间隔
    m_recorder1++;
    if(m_recorder1 < 10*player_option.Enenmy_Interval)
    {
        return;
    }

    score+=5;
    m_recorder1 = 0;
    q=ENEMY_BLOOD1;
    for(int i = 0 ; i< ENEMY_NUM;i++)
    {
        if(m_enemys1[i].m_Free)
        {
            //敌机空闲状态改为false
            m_enemys1[i].m_Free = false;
            //设置坐标
            m_enemys1[i].m_X = rand() % (GAME_WIDTH - m_enemys1[i].m_Rect.width());
            m_enemys1[i].m_Y = -m_enemys1[i].m_Rect.height();
            break;
        }
    }
}
void MainScene::enemyToScene2()
{
    //累加出场间隔
    m_recorder2++;
    if(m_recorder2 < 40*player_option.Enenmy_Interval)
    {
        return;
    }

    score+=10;
    p=ENEMY_BLOOD2;
    m_recorder2 = 0;

    for(int i = 0 ; i< ENEMY_NUM;i++)
    {
        if(m_enemys2[i].m_Free)
        {
            //敌机空闲状态改为false
            m_enemys2[i].m_Free = false;
            //设置坐标
            m_enemys2[i].m_X = rand() % (GAME_WIDTH - m_enemys2[i].m_Rect.width());
            m_enemys2[i].m_Y = -m_enemys2[i].m_Rect.height();
            break;
        }
    }
}

void MainScene::collisionDetection()
{
    //遍历所有非空闲的敌机
    for(int i = 0 ;i < ENEMY_NUM;i++)
    {
        if(m_enemys1[i].m_Free)
        {
            //空闲飞机 跳转下一次循环
            continue;
        }

        //遍历所有 非空闲的子弹
        for(int j = 0 ; j < BULLET_NUM;j++)
        {
            if(m_hero.m_bullets[j].m_Free)
            {
                //空闲子弹 跳转下一次循环
                continue;
            }
            //如果子弹和子弹边框相交，发生碰撞，同时变为空闲


            //如果子弹矩形框和敌机矩形框相交，发生碰撞，同时变为空闲状态即可
            if(m_enemys1[i].m_Rect.intersects(m_hero.m_bullets[j].m_Rect))
           { q--;q-=m_hero.type; m_hero.m_bullets[j].m_Free = true;}


                //播放音效

              if(q<=0){
                QSound::play(SOUND_BOMB);
                m_enemys1[i].m_Free = true;
                q=ENEMY_BLOOD1;

                //加分
                score+=25;
                //调用爆炸特效
                //播放爆炸效果
              for(int k = 0 ; k < BOMB_NUM;k++)
              {
                  if(m_bombs[k].m_Free)
                  {
                      //爆炸状态设置为非空闲
                      m_bombs[k].m_Free = false;
                      //更新坐标
                      m_bombs[k].m_X = m_enemys1[i].m_X;
                      m_bombs[k].m_Y = m_enemys1[i].m_Y;
                      break;
                  }
              }

            }
        }
    }


    for(int i = 0 ;i < ENEMY_NUM;i++)
    {
        if(m_enemys2[i].m_Free)
        {
            //空闲飞机 跳转下一次循环
            continue;
        }

        //遍历所有 非空闲的子弹
        for(int j = 0 ; j < BULLET_NUM;j++)
        {
            if(m_hero.m_bullets[j].m_Free)
            {
                //空闲子弹 跳转下一次循环
                continue;
            }

            //如果子弹矩形框和敌机矩形框相交，发生碰撞，同时变为空闲状态即可
            if(m_enemys2[i].m_Rect.intersects(m_hero.m_bullets[j].m_Rect))
           { p--;p-=m_hero.type; m_hero.m_bullets[j].m_Free = true;}


                //播放音效

             if(p<=0){
                //QSound::play(SOUND_BOMB);
                m_enemys2[i].m_Free = true;
                p=ENEMY_BLOOD2;

                //加分
                score+=40;
                //子弹增强
                m_hero.type=1;
                //调用爆炸特效
                //播放爆炸效果
              for(int k = 0 ; k < BOMB_NUM;k++)
              {
                  if(m_bombs[k].m_Free)
                  {
                      //爆炸状态设置为非空闲
                      m_bombs[k].m_Free = false;
                      //更新坐标
                      m_bombs[k].m_X = m_enemys2[i].m_X;
                      m_bombs[k].m_Y = m_enemys2[i].m_Y;
                      break;
                  }
              }

            }
        }
    }

    for(int i=0;i<BULLET_NUM;i++)
    {
        if(!m_hero.m_bullets[i].m_Free)
        {
            for(int j=0;j<ENEMY_NUM;j++)
            {
                if(!m_enemys1[j].m_Free)
                {
                    for(int k=0;k<BULLET_NUM;k++)
                    {
                        if(!m_enemys1[j].m_bullets[k].m_Free)
                        {
                            if(m_enemys1[j].m_bullets[k].m_Rect.intersects(m_hero.m_bullets[i].m_Rect))
                            {
                                m_enemys1[j].m_bullets[k].m_Free=true;
                                m_hero.m_bullets[i].m_Free=true;
                            }
                        }
                    }
                }
                if(!m_enemys2[j].m_Free)
                {
                    for(int k=0;k<BULLET_NUM;k++)
                    {
                        if(!m_enemys2[j].m_bullets[k].m_Free)
                        {
                            if(m_enemys2[j].m_bullets[k].m_Rect.intersects(m_hero.m_bullets[i].m_Rect))
                            {
                                m_enemys2[j].m_bullets[k].m_Free=true;
                                m_hero.m_bullets[i].m_Free=true;
                            }
                        }
                    }
                }
            }
        }
    }

    if(m_hero.m_health>0)
    {for(int i=0;i<ENEMY_NUM;i++)
    {
        if(!m_enemys1[i].m_Free)
        {
            for(int j=0;j<BULLET_NUM;j++)
            {
                if(!m_enemys1[i].m_bullets[j].m_Free)
                {
                    if(m_enemys1[i].m_bullets[j].m_Rect.intersects(m_hero.m_Rect))
                    {
                            //敌机子弹变为空闲
                            m_enemys1[i].m_bullets[j].m_Free=true;
                            m_hero.m_health--;
                            //播放爆炸音效 显示爆炸画面
                            for(int k = 0 ; k < BOMB_NUM;k++)
                            {
                                if(m_bombs[k].m_Free)
                                {
                                    //爆炸状态设置为非空闲
                                    m_bombs[k].m_Free = false;
                                    //更新坐标
                                    m_bombs[k].m_X = m_enemys1[i].m_bullets[j].m_X;
                                    m_bombs[k].m_Y = m_enemys1[i].m_bullets[j].m_Y;
                                    break;
                                }
                            }
                            if(m_hero.m_health==0)
                            {
                                gobacktime=200;
                            }
                    }
                }
            }
        }
        if(!m_enemys2[i].m_Free)
        {
            for(int j=0;j<BULLET_NUM;j++)
            {
                if(!m_enemys2[i].m_bullets[j].m_Free)
                {
                    if(m_enemys2[i].m_bullets[j].m_Rect.intersects(m_hero.m_Rect))
                    {
                            //敌机子弹变为空闲
                            m_enemys2[i].m_bullets[j].m_Free=true;
                            m_hero.m_health--;
                            //爆炸音效 显示爆炸画面
                            for(int k = 0 ; k < BOMB_NUM;k++)
                            {
                                if(m_bombs[k].m_Free)
                                {
                                    //爆炸状态设置为非空闲
                                    m_bombs[k].m_Free = false;
                                    //更新坐标
                                    m_bombs[k].m_X = m_enemys2[i].m_bullets[j].m_X;
                                    m_bombs[k].m_Y = m_enemys2[i].m_bullets[j].m_Y;
                                    break;
                                }
                            }
                            if(m_hero.m_health==0)
                            {
                                gobacktime=200;
                            }
                    }
                }
            }
        }
    }}

    if(gobacktime)
    {
        gobacktime--;
        if(!gobacktime)
        {

            goback();
        }
    }
}
void MainScene::goback()
{
    father->show();
    this->hide();
    this->~MainScene();
}
Start::Start()
{
    start_pixmap.load(START_PATH);
    update();
    QSound::play(SOUND_BACKGROUND);
    int x=70;
    start.setStyleSheet("background-color:yellow;border:2px groove gray;border-radius:10px;padding:2px 4px;");
    options.setStyleSheet("background-color:yellow;border:2px groove gray;border-radius:10px;padding:2px 4px;");
    back.setStyleSheet("background-color:yellow;border:2px groove gray;border-radius:10px;padding:2px 4px;");
    this->resize(300,400);
    start.setParent(this);
    options.setParent(this);
    back.setParent(this);
    start.setText("开始游戏");
    start.move(80,40+x);
    start.resize(140,60);
    options.setText("选项");
    options.move(80,120+x);
    options.resize(140,60);
    back.setText("关闭");
    back.move(80,200+x);
    back.resize(140,60);
    connect(&this->start,&QPushButton::clicked,this,&Start::play);
    connect(&this->options,&QPushButton::clicked,this,&Start::set);
    connect(&this->back,&QPushButton::clicked,this,&Start::end);
}
void Start::paintEvent(QPaintEvent* ev)
{
    QPainter p(this);
    p.drawPixmap(-40,-10,start_pixmap);
}
void Start::play()
{
    MainScene* son=new MainScene(0,this,&of_start);
    this->hide();
    son->show();
}
void Start::set()
{
    OptionScene *opt=new OptionScene(this);
    this->hide();
    opt->show();
}
void Start::end()
{
    close();
}
OptionScene::OptionScene(Start* pa)
{
    option_pixmap.load(OPTION_PATH);
    update();
    this->resize(300,400);
    fa=pa;
    a.setParent(this);
    b.setParent(this);
    c.setParent(this);
    d.setParent(this);
    QPalette pe;
    pe.setColor(QPalette::WindowText,Qt::red);
    a.setPalette(pe);
    b.setPalette(pe);
    c.setPalette(pe);
    d.setPalette(pe);
    a.setText("主角血量");
    b.setText("敌机速度");
    c.setText("敌机出现间隔");
    d.setText("敌机射击间隔");
    a.move(120,110);
    b.move(120,150);
    c.move(80,190);
    d.move(80,230);
    back.setParent(this);
    choice_blood.setParent(this);
    choice_speed.setParent(this);
    choice_interval.setParent(this);
    choice_bullet_interval.setParent(this);
    choice_blood.setRange(1,10);
    choice_blood.setValue(fa->of_start.Hero_Blood);
    choice_blood.resize(50,30);
    choice_blood.move(200,100);
    choice_speed.setRange(1,5);
    choice_speed.setValue(fa->of_start.Enenmy_Speed);
    choice_speed.resize(50,30);
    choice_speed.move(200,140);
    choice_interval.setRange(5,20);
    choice_interval.setValue(fa->of_start.Enenmy_Interval);
    choice_interval.resize(50,30);
    choice_interval.move(200,180);
    choice_bullet_interval.setRange(1,3);
    choice_bullet_interval.setValue(fa->of_start.Enenmy_Bullet_Interval);
    choice_bullet_interval.resize(50,30);
    choice_bullet_interval.move(200,220);
    back.setText("返回");
    back.move(110,260);
    connect(&this->back,&QPushButton::clicked,this,&OptionScene::goback);
}

void OptionScene::goback()
{
    fa->of_start.Hero_Blood=choice_blood.value();
    fa->of_start.Enenmy_Speed=choice_speed.value();
    fa->of_start.Enenmy_Interval=choice_interval.value();
    fa->of_start.Enenmy_Bullet_Interval=choice_bullet_interval.value();
    fa->show();
    this->~OptionScene();
}
void OptionScene::paintEvent(QPaintEvent *event)
{
    QPainter p(this);
    p.drawPixmap(0,-100,option_pixmap);
}
