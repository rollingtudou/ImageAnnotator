#ifndef ANNOTATIONTOOLS_H
#define ANNOTATIONTOOLS_H

#include <QObject>
#include <QGraphicsSceneMouseEvent>
#include "annotationitem.h"

class AnnotationTool : public QObject
{
    Q_OBJECT

public:
    explicit AnnotationTool(QObject *parent = nullptr);
    virtual ~AnnotationTool() = default;

    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) = 0;
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event) = 0;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) = 0;

signals:
    void itemCreated(AnnotationItem *item);

protected:
    bool m_isDrawing;
    QPointF m_startPoint;
    AnnotationItem *m_currentItem;
};

class RectangleTool : public AnnotationTool
{
    Q_OBJECT

public:
    explicit RectangleTool(QObject *parent = nullptr);
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
};

class CircleTool : public AnnotationTool
{
    Q_OBJECT

public:
    explicit CircleTool(QObject *parent = nullptr);
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
};

class PolygonTool : public AnnotationTool
{
    Q_OBJECT

public:
    explicit PolygonTool(QObject *parent = nullptr);
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);

private:
    QVector<QPointF> m_points;
};

// 类似地实现 CircleTool 和 PolygonTool
// ...

#endif // ANNOTATIONTOOLS_H 