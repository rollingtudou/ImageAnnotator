#include "annotationitem.h"
#include <QPainter>
#include <QStyleOptionGraphicsItem>
#include <QGraphicsSceneMouseEvent>

AnnotationItem::AnnotationItem(AnnotationType type, QGraphicsItem *parent)
    : QGraphicsItem(parent)
    , m_type(type)
{
    setFlags(QGraphicsItem::ItemIsSelectable | 
             QGraphicsItem::ItemIsMovable | 
             QGraphicsItem::ItemSendsGeometryChanges);
    
    // 设置默认样式
    m_pen = QPen(Qt::red, 2);
    m_brush = QBrush(QColor(255, 0, 0, 50));
}

void AnnotationItem::setPoints(const QPolygonF &points)
{
    prepareGeometryChange();
    m_points = points;
    update();
}

QRectF AnnotationItem::boundingRect() const
{
    return m_points.boundingRect();
}

void AnnotationItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);

    painter->setPen(m_pen);
    painter->setBrush(m_brush);

    // 绘制标注形状
    switch (m_type) {
        case RectType:
            painter->drawRect(m_points.boundingRect());
            break;
        case CircleType:
            painter->drawEllipse(m_points.boundingRect());
            break;
        case PolygonType:
            painter->drawPolygon(m_points);
            break;
    }

    // 如果被选中，绘制选中效果
    if (option->state & QStyle::State_Selected) {
        painter->setPen(QPen(Qt::blue, 1, Qt::DashLine));
        painter->setBrush(Qt::NoBrush);
        painter->drawRect(boundingRect());
    }

    // 绘制标签
    if (!m_label.isEmpty()) {
        QRectF textRect = boundingRect();
        textRect.setHeight(20);
        painter->setPen(Qt::black);
        painter->setBrush(QColor(255, 255, 255, 200));
        painter->drawRect(textRect);
        painter->drawText(textRect, Qt::AlignCenter, m_label);
    }
}

void AnnotationItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        setCursor(Qt::ClosedHandCursor);
    }
    QGraphicsItem::mousePressEvent(event);
}

void AnnotationItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mouseMoveEvent(event);
}

void AnnotationItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        setCursor(Qt::ArrowCursor);
    }
    QGraphicsItem::mouseReleaseEvent(event);
} 