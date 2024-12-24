#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDockWidget>
#include "annotationscene.h"
#include "zoomableview.h"
#include "styledialog.h"
#include <QUndoStack>
#include <QUndoView>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void openImage();
    void saveAnnotations();
    void setRectangleTool();
    void setCircleTool();
    void setPolygonTool();
    void showStyleDialog();
    void applyStyle(const QPen &pen, const QBrush &brush);
    void createUndoView();

private:
    void createToolBars();

    Ui::MainWindow *ui;
    AnnotationScene *scene;
    ZoomableView *view;
    StyleDialog *styleDialog;
    QUndoStack *undoStack;
    QDockWidget *undoView;
    QString currentImagePath;
    QPen currentPen;
    QBrush currentBrush;
};

#endif // MAINWINDOW_H 