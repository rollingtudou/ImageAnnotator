#ifndef ZOOMABLEVIEW_H
#define ZOOMABLEVIEW_H

#include <QGraphicsView>
#include <QWheelEvent>
#include <QMouseEvent>

class ZoomableView : public QGraphicsView
{
    Q_OBJECT

public:
    explicit ZoomableView(QGraphicsScene *scene = nullptr, QWidget *parent = nullptr);
    void setZoomFactor(qreal factor);
    qreal zoomFactor() const { return m_zoomFactor; }
    void resetZoom();

signals:
    void zoomFactorChanged(qreal factor);

protected:
    void wheelEvent(QWheelEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;

private:
    void scaleView(qreal factor);
    qreal m_zoomFactor;
    QPoint m_lastMousePos;
    bool m_isPanning;
};

#endif // ZOOMABLEVIEW_H 