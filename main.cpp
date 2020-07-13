
#include "mainscene.h"
#include <QApplication>
//注册二进制文件
#include <QResource>
#include "config.h"
#include<QDialog>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //注册外部二进制资源文件
    QResource::registerResource(GAME_RES_PATH);
    Start s;
    s.show();
    return a.exec();
}
