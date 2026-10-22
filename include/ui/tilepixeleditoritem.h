#ifndef TILEPIXELEDITORITEM_H
#define TILEPIXELEDITORITEM_H

#include <QGraphicsPixmapItem>
#include <QGraphicsSceneMouseEvent>

// A zoomed 8x8 pixel grid for a single tile.
// Painting is reported to the owner via signals; this item only displays the tile
// and translates mouse events into pixel coordinates. Right-clicks and Alt+clicks
// are reported separately so the owner can use them for an eyedropper tool.
class TilePixelEditorItem : public QObject, public QGraphicsPixmapItem {
    Q_OBJECT
public:
    explicit TilePixelEditorItem(QObject *parent = nullptr);

    // Size of one pixel of the tile on-screen.
    static constexpr int cellSize = 24;
    static constexpr int pixelCount = 8;

    // 'displayImage' is the tile rendered at its natural 8x8 size; it is scaled up for display.
    void setTileDisplayImage(const QImage &displayImage);
    void clearTile();

signals:
    // Emitted for left-button presses/dragging (paint) and eyedropper presses.
    void paintPixel(const QPoint &pixelPos);
    void eyedropPixel(const QPoint &pixelPos);
    // Emitted once when a paint stroke (press .. release) finishes.
    void strokeFinished();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

private:
    QPoint pixelPosFromEvent(QGraphicsSceneMouseEvent *event) const;
    bool isEyedropEvent(QGraphicsSceneMouseEvent *event) const;

    bool painting = false;
    QPoint lastPixelPos = QPoint(-1, -1);
};

#endif // TILEPIXELEDITORITEM_H
