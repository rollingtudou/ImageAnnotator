#include "annotationscene.h"
#include "commands.h"
#include <QGraphicsPixmapItem>
#include <QDebug>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

AnnotationScene::AnnotationScene(QObject *parent)
    : QGraphicsScene(parent)
    , currentTool(None)
    , currentItem(nullptr)
    , drawing(false)
{
    // 设置默认样式
    defaultPen = QPen(Qt::red, 2);
    defaultBrush = QBrush(QColor(255, 0, 0, 50));
}

void AnnotationScene::setToolType(ToolType type)
{
    currentTool = type;
}

void AnnotationScene::loadImage(const QString &path)
{
    clear();
    QPixmap pixmap(path);
    if (!pixmap.isNull()) {
        addPixmap(pixmap);
        setSceneRect(pixmap.rect());
    }
}

void AnnotationScene::setUndoStack(QUndoStack *stack)
{
    undoStack = stack;
}

void AnnotationScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        lastPos = event->scenePos();
        startPoint = event->scenePos();
        drawing = true;
        
        switch (currentTool) {
            case Rectangle:
                currentItem = addRect(QRectF(startPoint, startPoint));
                break;
            case Circle:
                currentItem = addEllipse(QRectF(startPoint, startPoint));
                break;
            case Polygon:
                if (polygonPoints.isEmpty()) {
                    polygonPoints.append(startPoint);
                    currentItem = addPolygon(QPolygonF(polygonPoints));
                } else {
                    polygonPoints.append(startPoint);
                    static_cast<QGraphicsPolygonItem*>(currentItem)->setPolygon(QPolygonF(polygonPoints));
                }
                break;
            default:
                break;
        }
        if (currentItem) {
            undoStack->push(new AddItemCommand(this, static_cast<AnnotationItem*>(currentItem)));
        }
    }
    QGraphicsScene::mousePressEvent(event);
}

void AnnotationScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (drawing && currentItem) {
        QPointF currentPos = event->scenePos();
        
        switch (currentTool) {
            case Rectangle:
            case Circle: {
                QRectF rect = QRectF(startPoint, currentPos).normalized();
                if (currentTool == Rectangle) {
                    static_cast<QGraphicsRectItem*>(currentItem)->setRect(rect);
                } else {
                    static_cast<QGraphicsEllipseItem*>(currentItem)->setRect(rect);
                }
                break;
            }
            case Polygon: {
                // 更新多边形预览线
                QVector<QPointF> tempPoints = polygonPoints;
                tempPoints.append(currentPos);
                static_cast<QGraphicsPolygonItem*>(currentItem)->setPolygon(QPolygonF(tempPoints));
                break;
            }
            default:
                break;
        }
    }
    QGraphicsScene::mouseMoveEvent(event);
}

void AnnotationScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::LeftButton && drawing) {
        if (currentTool != Polygon) {
            drawing = false;
            currentItem = nullptr;
        }
        // 多边形工具需要双击完成绘制
        else if (event->flags() & Qt::MouseEventCreatedDoubleClick) {
            drawing = false;
            currentItem = nullptr;
            polygonPoints.clear();
        }
    }
    if (event->button() == Qt::LeftButton) {
        QGraphicsItem *item = itemAt(event->scenePos(), QTransform());
        if (item && item->type() == AnnotationItem::Type) {
            QPointF newPos = item->pos();
            if (newPos != lastPos) {
                undoStack->push(new MoveItemCommand(
                    static_cast<AnnotationItem*>(item), lastPos, newPos));
            }
        }
    }
    QGraphicsScene::mouseReleaseEvent(event);
}

void AnnotationScene::setImageFileName(const QString &name)
{
    imageFileName = name;
}

bool AnnotationScene::saveToJson(const QString &filename)
{
    QJsonObject root;
    
    // 添加基本信息
    root["version"] = "1.0";
    root["imageFile"] = imageFileName;
    root["imageWidth"] = sceneRect().width();
    root["imageHeight"] = sceneRect().height();
    
    // 创建标注数组
    QJsonArray annotations;
    
    // 遍历所有标注项
    foreach (QGraphicsItem *item, items()) {
        if (item->type() == AnnotationItem::Type) {
            AnnotationItem *annItem = static_cast<AnnotationItem*>(item);
            annotations.append(annotationToJson(annItem));
        }
    }
    
    root["annotations"] = annotations;
    
    // 写入文件
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly)) {
        return false;
    }
    
    QJsonDocument doc(root);
    file.write(doc.toJson(QJsonDocument::Indented));
    return true;
}

QJsonObject AnnotationScene::annotationToJson(const AnnotationItem *item) const
{
    QJsonObject annotation;
    
    // 添加基本属性
    annotation["id"] = QString::number(reinterpret_cast<qulonglong>(item));
    annotation["label"] = item->label();
    annotation["category"] = item->category();
    
    // 添加类型信息
    switch (item->annotationType()) {
        case AnnotationItem::RectType:
            annotation["type"] = "rectangle";
            break;
        case AnnotationItem::CircleType:
            annotation["type"] = "circle";
            break;
        case AnnotationItem::PolygonType:
            annotation["type"] = "polygon";
            break;
    }
    
    // 添加坐标信息
    QJsonArray points;
    for (const QPointF &point : item->points()) {
        QJsonObject pointObj;
        pointObj["x"] = point.x();
        pointObj["y"] = point.y();
        points.append(pointObj);
    }
    annotation["points"] = points;
    
    // 添加样式信息
    QJsonObject style;
    style["color"] = item->pen().color().name();
    style["lineWidth"] = item->pen().width();
    style["opacity"] = item->brush().color().alphaF();
    annotation["style"] = style;
    
    return annotation;
} 