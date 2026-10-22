#ifndef NOSCROLLSPINBOX_H
#define NOSCROLLSPINBOX_H

#include <QSpinBox>

class NoScrollSpinBox : public QSpinBox
{
    Q_OBJECT

public:
    explicit NoScrollSpinBox(QWidget *parent = nullptr);
    void wheelEvent(QWheelEvent *event) override;
    void focusOutEvent(QFocusEvent *event) override;

    void setLineEditEnabled(bool enabled);
    void setFocusedScrollingEnabled(bool enabled);

    unsigned getActionId();

private:
    bool focusedScrollingEnabled = true;
};

#endif // NOSCROLLSPINBOX_H
