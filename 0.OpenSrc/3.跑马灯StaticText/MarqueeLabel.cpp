#include <QtGui>
#include <QtCore/QUrl>
#include <QtConcurrentRun>
#include <QtGui/QResizeEvent>
#include <QtGui/QDesktopServices>
#include <QtCore/QPropertyAnimation>
#include "MarqueeLabel.hpp"
MarqueeLabel::MarqueeLabel(QWidget * parent, Qt::WindowFlags f)
    : QLabel(parent, f)
{
    setOpenExternalLinks(false);
    _animation = new QPropertyAnimation(this, "geometry", this);
    connect(this, SIGNAL(linkActivated(const QString &)),
            this, SLOT(openLink(const QString &)));
}
MarqueeLabel::MarqueeLabel(const QString &text, QWidget *parent,
        Qt::WindowFlags f )
    : QLabel(text, parent, f)
{
    setOpenExternalLinks(false);
    _animation = new QPropertyAnimation(this, "geometry", this);
    connect(this, SIGNAL(linkActivated(const QString &)),
            this, SLOT(openLink(const QString &)));
}
MarqueeLabel::~MarqueeLabel()
{
}
void MarqueeLabel::leaveEvent(QEvent *event)
{
    _animation->resume();
    QLabel::leaveEvent(event);
}
void MarqueeLabel::enterEvent(QEvent *event)
{
    _animation->pause();
    QLabel::enterEvent(event);
}
void MarqueeLabel::resizeEvent(QResizeEvent *event)
{
    QLabel::resizeEvent(event);
    disconnect(_animation, SIGNAL(finished()), _animation, SLOT(start()));
    _animation->stop();
    int iWidth = sizeHint().width();
    int iParentWidth = parentWidget() ? parentWidget()->width() : 600;
    int iHeight = event->size().height();
    connect(_animation, SIGNAL(finished()), _animation, SLOT(start()));
    _animation->setDuration(10000);
    _animation->setStartValue(QRect(iParentWidth, 0, iWidth, iHeight));
    _animation->setEndValue(QRect(-iWidth, 0, iWidth, iHeight));
    _animation->start();
}
void MarqueeLabel::openLink(const QString &url)
{
    QtConcurrent::run(QDesktopServices::openUrl, QUrl(url));
}
void MarqueeLabel::setText(const QString &text)
{
    disconnect(_animation, SIGNAL(finished()), _animation, SLOT(start()));
    _animation->stop();
    QLabel::setText(text);
    int iWidth = sizeHint().width();
    int iParentWidth = parentWidget() ? parentWidget()->width() : 600;
    int iHeight = height();
    connect(_animation, SIGNAL(finished()), _animation, SLOT(start()));
    _animation->setDuration(10000);
    _animation->setStartValue(QRect(iParentWidth, 0, iWidth, iHeight));
    _animation->setEndValue(QRect(-iWidth, 0, iWidth, iHeight));
    _animation->start();
}
