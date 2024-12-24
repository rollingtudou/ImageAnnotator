#include "zoomableview.h"
#include <QScrollBar>

ZoomableView::ZoomableView(QGraphicsScene *scene, QWidget *parent)
    : QGraphicsView(scene, parent)
    , m_zoomFactor(1.0)
    , m_isPanning(false)
{
    setRenderHint(QPainter::Antialiasing);
    setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    setResizeAnchor(QGraphicsView::AnchorUnderMouse);
    setMouseTracking(true);
}

void ZoomableView::wheelEvent(QWheelEvent *event)
{
    const qreal delta = event->angleDelta().y();
    if (delta > 0)
        scaleView(1.1);
    else if (delta < 0)
        scaleView(0.9);
}

void ZoomableView::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::MiddleButton) {
        m_isPanning = true;
        m_lastMousePos = event->pos();
        setCursor(Qt::ClosedHandCursor);
        event->accept();
        return;
    }
    QGraphicsView::mousePressEvent(event);
}

void ZoomableView::mouseMoveEvent(QMouseEvent *event)
{
    if (m_isPanning) {
        horizontalScrollBar()->setValue(horizontalScrollBar()->value() - (event->pos().x() - m_lastMousePos.x()));
        verticalScrollBar()->setValue(verticalScrollBar()->value() - (event->pos().y() - m_lastMousePos.y()));
        m_lastMousePos = event->pos();
        event->accept();
        return;
    }
    QGraphicsView::mouseMoveEvent(event);
}

void ZoomableView::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::MiddleButton) {
        m_isPanning = false;
        setCursor(Qt::ArrowCursor);
        event->accept();
        return;
    }
    QGraphicsView::mouseReleaseEvent(event);
}

void ZoomableView::scaleView(qreal factor)
{
    qreal newZoom = m_zoomFactor * factor;
    if (newZoom < 0.1 || newZoom > 10.0)
        return;
        
    m_zoomFactor = newZoom;
    scale(factor, factor);
    emit zoomFactorChanged(m_zoomFactor);
}

void ZoomableView::setZoomFactor(qreal factor)
{
    if (factor < 0.1 || factor > 10.0)
        return;
        
    qreal scaleFactor = factor / m_zoomFactor;
    scaleView(scaleFactor);
}

void ZoomableView::resetZoom()
{
    setZoomFactor(1.0);
    resetTransform();
    centerOn(sceneRect().center());
}

// ... 其他方法的实现 