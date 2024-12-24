#ifndef COMMANDS_H
#define COMMANDS_H

#include <QUndoCommand>
#include <QGraphicsScene>
#include <QPointF>
#include "annotationitem.h"

class AddItemCommand : public QUndoCommand
{
public:
    AddItemCommand(QGraphicsScene *scene, AnnotationItem *item, QUndoCommand *parent = nullptr);
    void undo() override;
    void redo() override;

private:
    QGraphicsScene *scene;
    AnnotationItem *item;
};

class RemoveItemCommand : public QUndoCommand
{
public:
    RemoveItemCommand(QGraphicsScene *scene, AnnotationItem *item, QUndoCommand *parent = nullptr);
    void undo() override;
    void redo() override;

private:
    QGraphicsScene *scene;
    AnnotationItem *item;
};

class MoveItemCommand : public QUndoCommand
{
public:
    MoveItemCommand(AnnotationItem *item, const QPointF &oldPos, const QPointF &newPos,
                   QUndoCommand *parent = nullptr);
    void undo() override;
    void redo() override;
    bool mergeWith(const QUndoCommand *command) override;
    int id() const override { return 1; }

private:
    AnnotationItem *item;
    QPointF oldPos;
    QPointF newPos;
};

#endif // COMMANDS_H