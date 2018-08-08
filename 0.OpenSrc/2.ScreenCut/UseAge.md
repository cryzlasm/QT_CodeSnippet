网上摘抄的代码, 看样子是在QT4下运行, 因为使用了 `QPixmap::grabWindow` 进行截屏
而个人在测试上个截屏代码时, QT5显示此函数弃用

``` C++
ScreenCutDialog dlg;
dlg.exec();
QPixmap px = dlg.getPixmap();
```