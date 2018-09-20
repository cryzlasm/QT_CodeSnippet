#include <QtGui/QPainter>
#include <QtGui/QMouseEvent>
#include <QtGui/QPaintEvent>
#include <QtGui/QApplication>
#include <QtGui/QDesktopWidget>
#include "ScreenCutDialog.hpp"
ScreenCutDialog::ScreenCutDialog(QWidget *parent, Qt::WindowFlags f)
    : QDialog(parent, f), _bDrag(false)
{
    setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint
            | Qt::WindowStaysOnTopHint);
    setWindowState(Qt::WindowFullScreen);
    setCursor(Qt::CrossCursor);
    QDesktopWidget *desk = QApplication::desktop();
    setGeometry(desk->availableGeometry());
    _image = QPixmap::grabWindow(desk->winId()).toImage();
    _darkImage = _image;
    int bytesPerLine = _darkImage.width() * _darkImage.depth() / 8;
    int h = _darkImage.height();
    for (int i = 0; i < h; i++)
    {
        unsigned char *lineBuf = _darkImage.scanLine(i);
        for (int x = 0; x < bytesPerLine; x++)
        {
            lineBuf[x] /= 2;
        }
    }
}
ScreenCutDialog::~ScreenCutDialog()
{
}
void ScreenCutDialog::mousePressEvent(QMouseEvent *event)
{
    _bDrag = true;
    _pos = event->pos();
    _rect = QRect(_pos.x(), _pos.y(), 0, 0);
    QDialog::mousePressEvent(event);
}
void ScreenCutDialog::mouseMoveEvent(QMouseEvent *event)
{
    if (_bDrag = true)
    {
        QPoint pos = event->pos();
        if (pos.x() > _pos.x())
        {
            if (pos.y() > _pos.y())
            {
                _rect = QRect(_pos, pos);
            }
            else
            {
                _rect = QRect(QPoint(_pos.x(), pos.y()),
                            QPoint(pos.x(), _pos.y()));
            }
        }
        else
        {
            if (pos.y() > _pos.y())
            {
                _rect = QRect(QPoint(pos.x(), _pos.y()),
                            QPoint(_pos.x(), pos.y()));
            }
            else
            {
                _rect = QRect(pos, _pos);
            }
        }
        update();
    }
    QDialog::mouseMoveEvent(event);
}
void ScreenCutDialog::mouseReleaseEvent(QMouseEvent *event)
{
    _bDrag = false;
    QDialog::mouseReleaseEvent(event);
    accept();
}
