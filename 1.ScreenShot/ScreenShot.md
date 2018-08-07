屏幕截图:
``` C++
#include <QPixmap>
#include <QString>
#include <QDebug>
#include <QApplication>
#include <QDesktopWidget>
#include <QTextCodec>
#include <QDir>
#include <QScreen>
#include <QDateTime>
#include <QWindow>

void Widget::on_pushButton_pressed()
{
    qDebug() << "Widget::on_pushButton_pressed()" << "\r\n";
    qDebug() << "CurWorkPath: " << QDir::currentPath();

    QDesktopWidget& deskTop = *QApplication::desktop();    //  获取桌面
    QWindow * pobjWindow = deskTop.windowHandle();         // 获取桌面工具类
    QScreen* pobjScreen = pobjWindow->screen();            // 获取屏幕对象
    
    // 屏幕对象抓取屏幕Wnd,  QT5 之后 不支持QPixMap::grabWindow()
    // 且 grabWindow() 不为静态函数
    QPixmap pixMap = pobjScreen->grabWindow(QApplication::desktop()->winId());  
    
    
    QString strPicPath = "./%1_screenShot.jpg"; 
    qDebug() << "\r\nQDateTime::currentDateTimeUtc().toString(): " << QDateTime::currentDateTimeUtc().toString();
    strPicPath = strPicPath.arg(QDateTime::currentDateTime().toString("yyyy.MM.dd-hh.mm.ss"));  // 格式化时间字符串
    qDebug() << "\r\nSavePicPath: " << strPicPath;  
    
    pixMap.save(strPicPath, "JPG");                                     // 输出 屏幕截图
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));   // 设置UTF-8支持

}
```