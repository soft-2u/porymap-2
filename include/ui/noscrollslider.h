#ifndef NOSCROLLSLIDER_H
#define NOSCROLLSLIDER_H

#include <QSlider>

class NoScrollSlider : public QSlider
{
    Q_OBJECT

public:
    explicit NoScrollSlider(QWidget *parent = nullptr);
    void wheelEvent(QWheelEvent *event) override;
    void setFocusedScrollingEnabled(bool enabled);

private:
    bool focusedScrollingEnabled = true;
};

#endif // NOSCROLLSLIDER_H
