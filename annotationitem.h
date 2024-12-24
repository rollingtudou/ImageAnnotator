#ifndef ANNOTATIONITEM_H
#define ANNOTATIONITEM_H

#include <QGraphicsItem>
#include <QPen>
#include <QBrush>
#include <QPainter>

class AnnotationItem : public QGraphicsItem
{
public:
    enum { Type = UserType + 1 };
    enum AnnotationType {
        RectType,
        CircleType,
        PolygonType
    };

    AnnotationItem(AnnotationType type, QGraphicsItem *parent = nullptr);
    
    int type() const override { return Type; }
    AnnotationType annotationType() const { return m_type; }
    
    QString label() const { return m_label; }
    void setLabel(const QString &label) { m_label = label; update(); }
    
    QString category() const { return m_category; }
    void setCategory(const QString &category) { m_category = category; }
    
    QPolygonF points() const { return m_points; }
    void setPoints(const QPolygonF &points);
    
    QPen pen() const { return m_pen; }
    void setPen(const QPen &pen) { m_pen = pen; update(); }
    
    QBrush brush() const { return m_brush; }
    void setBrush(const QBrush &brush) { m_brush = brush; update(); }

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

private:
    AnnotationType m_type;
    QString m_label;
    QString m_category;
    QPolygonF m_points;
    QPen m_pen;
    QBrush m_brush;
};

#endif // ANNOTATIONITEM_H 