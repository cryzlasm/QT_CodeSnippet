#ifndef MARQUEELABEL_HPP
#define MARQUEELABEL_HPP
#include <QtGui/QLabel>
class QPropertyAnimation;
class QResizeEvent;
class MarqueeLabel : public QLabel
{
    Q_OBJECT
public:
    MarqueeLabel(QWidget * parent = 0, Qt::WindowFlags f = 0);
    MarqueeLabel(const QString &text, QWidget *parent = 0,
            Qt::WindowFlags f = 0);
    virtual ~MarqueeLabel();
public slots:
    void setText(const QString &text);
protected:
    virtual void resizeEvent(QResizeEvent *event);
    virtual void leaveEvent(QEvent *event);
    virtual void enterEvent(QEvent *event);
private slots:
    void openLink(const QString &url);
private:
    QPropertyAnimation *_animation;
};
#endif