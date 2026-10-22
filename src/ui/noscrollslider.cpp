#include "noscrollslider.h"
#include <QWheelEvent>

NoScrollSlider::NoScrollSlider(QWidget *parent)
    : QSlider(parent)
{
    // Don't let scrolling hijack focus.
    setFocusPolicy(Qt::StrongFocus);
}

void NoScrollSlider::wheelEvent(QWheelEvent *event)
{
    // By default NoScrollSliders will allow scrolling to modify its contents only when it explicitly has focus.
    // If focusedScrollingEnabled is false it won't allow scrolling even with focus.
    // Ignoring (rather than accepting) the event lets an ancestor QScrollArea still scroll.
    if (this->focusedScrollingEnabled && hasFocus()) {
        QSlider::wheelEvent(event);
    } else {
        event->ignore();
    }
}

void NoScrollSlider::setFocusedScrollingEnabled(bool enabled)
{
    this->focusedScrollingEnabled = enabled;
}
