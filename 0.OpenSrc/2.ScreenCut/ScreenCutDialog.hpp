#ifndef SCREENCUTDILAOG_HPP
#define SCREENCUTDIALOG_HPP
#include <QtCore/QRect>
#include <QtCore/QPoint>
#include <QtGui/QDialog>
#include <QtGui/QPixmap>
class QMouseEvent;
class QPaintEvent;
class ScreenCutDialog : public QDialog
{
    Q_OBJECT
public:
    ScreenCutDialog(QWidget *parent = 0, Qt::WindowFlags f = 0);
    virtual ~ScreenCutDialog();
    QPixmap getPixmap();
protected:
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void mouseReleaseEvent(QMouseEvent *event);
    virtual void mouseDoubleClickEvent(QMouseEvent *event);
    virtual void paintEvent(QPaintEvent *event);
private:
    bool _bDrag;
    QPoint _pos;
    QRect _rect;
    QImage _image;
    QImage _darkImage;
};
#endif