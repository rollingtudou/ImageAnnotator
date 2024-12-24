#ifndef ANNOTATIONSCENE_H
#define ANNOTATIONSCENE_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include "annotationitem.h"
#include "annotationtools.h"
#include <QUndoStack>

class AnnotationScene : public QGraphicsScene
{
    Q_OBJECT

public:
    enum ToolType {
        Rectangle,
        Circle,
        Polygon,
        None
    };

    explicit AnnotationScene(QObject *parent = nullptr);
    void setToolType(ToolType type);
    void loadImage(const QString &path);
    void setUndoStack(QUndoStack *stack);
    void setDefaultStyle(const QPen &pen, const QBrush &brush);
    void setImageFileName(const QString &name);
    bool saveToJson(const QString &filename);
    bool saveToXml(const QString &filename) { return false; }
    QJsonObject annotationToJson(const AnnotationItem *item) const;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

private:
    ToolType currentTool;
    QGraphicsItem *currentItem;
    bool drawing;
    QPointF startPoint;
    QVector<QPointF> polygonPoints;
    QUndoStack *undoStack;
    QPointF lastPos;  // 用于跟踪移动
    QPen defaultPen;
    QBrush defaultBrush;
    QString imageFileName;
};

#endif // ANNOTATIONSCENE_H 