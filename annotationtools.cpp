#include "annotationtools.h"
#include <QGraphicsSceneMouseEvent>

AnnotationTool::AnnotationTool(QObject *parent)
    : QObject(parent)
    , m_isDrawing(false)
    , m_currentItem(nullptr)
{
}

RectangleTool::RectangleTool(QObject *parent)
    : AnnotationTool(parent)
{
}

void RectangleTool::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        m_isDrawing = true;
        m_startPoint = event->scenePos();
        
        m_currentItem = new AnnotationItem(AnnotationItem::RectType);
        QPolygonF points;
        points << m_startPoint << m_startPoint;
        m_currentItem->setPoints(points);
        
        emit itemCreated(m_currentItem);
    }
}

void RectangleTool::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (m_isDrawing && m_currentItem) {
        QPolygonF points;
        QRectF rect = QRectF(m_startPoint, event->scenePos()).normalized();
        points << rect.topLeft() << rect.topRight() 
              << rect.bottomRight() << rect.bottomLeft();
        m_currentItem->setPoints(points);
    }
}

void RectangleTool::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        m_isDrawing = false;
        m_currentItem = nullptr;
    }
}

CircleTool::CircleTool(QObject *parent)
    : AnnotationTool(parent)
{
}

void CircleTool::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        m_isDrawing = true;
        m_startPoint = event->scenePos();
        
        m_currentItem = new AnnotationItem(AnnotationItem::CircleType);
        QPolygonF points;
        points << m_startPoint << m_startPoint;
        m_currentItem->setPoints(points);
        
        emit itemCreated(m_currentItem);
    }
}

void CircleTool::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (m_isDrawing && m_currentItem) {
        QPolygonF points;
        QRectF rect = QRectF(m_startPoint, event->scenePos()).normalized();
        points << rect.topLeft() << rect.topRight() 
              << rect.bottomRight() << rect.bottomLeft();
        m_currentItem->setPoints(points);
    }
}

void CircleTool::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        m_isDrawing = false;
        m_currentItem = nullptr;
    }
}

PolygonTool::PolygonTool(QObject *parent)
    : AnnotationTool(parent)
{
}

void PolygonTool::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        if (!m_isDrawing) {
            m_isDrawing = true;
            m_points.clear();
            m_startPoint = event->scenePos();
            m_points << m_startPoint;
            
            m_currentItem = new AnnotationItem(AnnotationItem::PolygonType);
            m_currentItem->setPoints(QPolygonF(m_points));
            
            emit itemCreated(m_currentItem);
        } else {
            m_points << event->scenePos();
            m_currentItem->setPoints(QPolygonF(m_points));
        }
    }
}

void PolygonTool::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (m_isDrawing && m_currentItem) {
        QVector<QPointF> tempPoints = m_points;
        tempPoints << event->scenePos();
        m_currentItem->setPoints(QPolygonF(tempPoints));
    }
}

void PolygonTool::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    // 多边形工具不在这里结束绘制
    Q_UNUSED(event);
}

void PolygonTool::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && m_isDrawing) {
        m_isDrawing = false;
        m_currentItem = nullptr;
        m_points.clear();
    }
} 