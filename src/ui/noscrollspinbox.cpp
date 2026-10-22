#include "noscrollspinbox.h"
#include <QWheelEvent>
#include <QLineEdit>

unsigned actionId = 0xffff;

NoScrollSpinBox::NoScrollSpinBox(QWidget *parent)
    : QSpinBox(parent)
{
    // Don't let scrolling hijack focus.
    setFocusPolicy(Qt::StrongFocus);
}

void NoScrollSpinBox::wheelEvent(QWheelEvent *event)
{
    // Only allow scrolling to modify contents when it explicitly has focus,
    // and only if focused scrolling hasn't been disabled for this spin box.
    // Ignoring (rather than accepting) the event lets an ancestor QScrollArea still scroll.
    if (this->focusedScrollingEnabled && hasFocus()) {
        QSpinBox::wheelEvent(event);
    } else {
        event->ignore();
    }
}

void NoScrollSpinBox::setFocusedScrollingEnabled(bool enabled)
{
    this->focusedScrollingEnabled = enabled;
}

void NoScrollSpinBox::focusOutEvent(QFocusEvent *event) {
    actionId++;
    QSpinBox::focusOutEvent(event);
}

void NoScrollSpinBox::setLineEditEnabled(bool enabled) {
    this->lineEdit()->setReadOnly(!enabled);
}

unsigned NoScrollSpinBox::getActionId() {
    return actionId;
}
