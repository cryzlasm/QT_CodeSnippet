# 屏幕截图
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
---

## Tips:
要想在Qt中实现屏幕或窗口截图功能 ，通常有两种方法：
1. 使用 QPixmap 类  
2. 使用 QScreen类

然而虽然俩两种方法用到的类不相同，但是调用到的类成员函数的函数名称和参数却是相同的
都是 `grabWindow()` 这个函数.   
所不同的是，`QPixmap`中的`grabWindow()`函数是静态成员`QScreen`中的`grabWindow()`成员是非静态成员  
下面展示两种截屏的方法:  
### `QPixmap`方法
``` C++
//截屏并保存为 123.jpg
QPixmap::grabWindow(QApplication::desktop()->winId()).save("123","jpg");
// 注意! **这种方法在Qt5中已经过时, 应该使用QScreen方法代替**
```

> 要注意的是 `QApplication::desktop()->winId()`，    
> **返回的是要截屏的窗口的ID, 设为0 表示当前桌面 ，截屏时就会截全屏**  


### `QScreen`方法:
``` C++
//功能同样是截屏 ， 注：QScreen的构造函数是私有的
QScreen *screen = QGuiApplication::primaryScreen();
screen->grabWindow(0).save("123","jpg");
```