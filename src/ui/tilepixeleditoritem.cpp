#include "tilepixeleditoritem.h"

#include <QPainter>
#include <QtMath>

TilePixelEditorItem::TilePixelEditorItem(QObject *parent)
    : QObject(parent)
{
    setTileDisplayImage(QImage());
}

void TilePixelEditorItem::setTileDisplayImage(const QImage &displayImage) {
    const int displaySize = cellSize * pixelCount;
    QImage scaled(displaySize, displaySize, QImage::Format_RGBA8888);
    scaled.fill(Qt::transparent);
    QPainter painter(&scaled);
    if (!displayImage.isNull()) {
        painter.drawImage(QRect(0, 0, displaySize, displaySize),
                          displayImage.scaled(pixelCount, pixelCount, Qt::IgnoreAspectRatio, Qt::FastTransformation));
    }
    // Draw the pixel grid on top.
    painter.setPen(QColor(0, 0, 0, 60));
    for (int i = 0; i <= pixelCount; i++) {
        painter.drawLine(i * cellSize, 0, i * cellSize, displaySize);
        painter.drawLine(0, i * cellSize, displaySize, i * cellSize);
    }
    painter.end();
    setPixmap(QPixmap::fromImage(scaled));
}

void TilePixelEditorItem::clearTile() {
    setTileDisplayImage(QImage());
}

QPoint TilePixelEditorItem::pixelPosFromEvent(QGraphicsSceneMouseEvent *event) const {
    QPoint pos(qFloor(event->pos().x() / cellSize), qFloor(event->pos().y() / cellSize));
    if (pos.x() < 0 || pos.x() >= pixelCount || pos.y() < 0 || pos.y() >= pixelCount)
        return QPoint(-1, -1);
    return pos;
}

bool TilePixelEditorItem::isEyedropEvent(QGraphicsSceneMouseEvent *event) const {
    return (event->button() == Qt::RightButton) || (event->modifiers() & Qt::AltModifier);
}

void TilePixelEditorItem::mousePressEvent(QGraphicsSceneMouseEvent *event) {
    QPoint pos = pixelPosFromEvent(event);
    if (pos.x() < 0) {
        QGraphicsPixmapItem::mousePressEvent(event);
        return;
    }
    if (isEyedropEvent(event)) {
        emit eyedropPixel(pos);
        event->accept();
        return;
    }
    if (event->button() == Qt::LeftButton) {
        this->painting = true;
        this->lastPixelPos = pos;
        emit paintPixel(pos);
        event->accept();
        return;
    }
    QGraphicsPixmapItem::mousePressEvent(event);
}

void TilePixelEditorItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event) {
    if (!this->painting) {
        QGraphicsPixmapItem::mouseMoveEvent(event);
        return;
    }
    QPoint pos = pixelPosFromEvent(event);
    if (pos.x() >= 0 && pos != this->lastPixelPos) {
        this->lastPixelPos = pos;
        emit paintPixel(pos);
    }
    event->accept();
}

void TilePixelEditorItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event) {
    if (this->painting && event->button() == Qt::LeftButton) {
        this->painting = false;
        this->lastPixelPos = QPoint(-1, -1);
        emit strokeFinished();
        event->accept();
        return;
    }
    QGraphicsPixmapItem::mouseReleaseEvent(event);
}
