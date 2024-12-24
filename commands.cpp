#include "commands.h"

AddItemCommand::AddItemCommand(QGraphicsScene *scene, AnnotationItem *item, QUndoCommand *parent)
    : QUndoCommand(parent)
    , scene(scene)
    , item(item)
{
    setText("添加标注");
}

void AddItemCommand::undo()
{
    scene->removeItem(item);
}

void AddItemCommand::redo()
{
    scene->addItem(item);
}

RemoveItemCommand::RemoveItemCommand(QGraphicsScene *scene, AnnotationItem *item, QUndoCommand *parent)
    : QUndoCommand(parent)
    , scene(scene)
    , item(item)
{
    setText("删除标注");
}

void RemoveItemCommand::undo()
{
    scene->addItem(item);
}

void RemoveItemCommand::redo()
{
    scene->removeItem(item);
}

MoveItemCommand::MoveItemCommand(AnnotationItem *item, const QPointF &oldPos, 
                               const QPointF &newPos, QUndoCommand *parent)
    : QUndoCommand(parent)
    , item(item)
    , oldPos(oldPos)
    , newPos(newPos)
{
    setText("移动标注");
}

void MoveItemCommand::undo()
{
    item->setPos(oldPos);
}

void MoveItemCommand::redo()
{
    item->setPos(newPos);
}

bool MoveItemCommand::mergeWith(const QUndoCommand *command)
{
    const MoveItemCommand *moveCommand = static_cast<const MoveItemCommand*>(command);
    if (item != moveCommand->item)
        return false;

    newPos = moveCommand->newPos;
    return true;
} 