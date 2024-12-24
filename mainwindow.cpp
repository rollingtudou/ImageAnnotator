#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QToolBar>
#include <QAction>
#include <QFileDialog>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , styleDialog(nullptr)
    , undoView(nullptr)
{
    ui->setupUi(this);

    // 设置窗口基本属性
    setWindowTitle("图像标注工具");
    resize(1200, 800);

    // 创建场景和视图
    scene = new AnnotationScene(this);
    view = new ZoomableView(scene);
    setCentralWidget(view);

    // 创建撤销栈
    undoStack = new QUndoStack(this);
    scene->setUndoStack(undoStack);

    // 创建工具栏
    createToolBars();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createToolBars()
{
    // 文件工具栏
    QToolBar *fileToolBar = addToolBar("文件");
    
    QAction *openAct = fileToolBar->addAction("打开图像");
    openAct->setShortcut(QKeySequence::Open);
    connect(openAct, &QAction::triggered, this, &MainWindow::openImage);

    QAction *saveAct = fileToolBar->addAction("保存标注");
    saveAct->setShortcut(QKeySequence::Save);
    connect(saveAct, &QAction::triggered, this, &MainWindow::saveAnnotations);

    // 标注工具栏
    QToolBar *annotationToolBar = addToolBar("标注工具");
    
    QAction *rectAct = annotationToolBar->addAction("矩形工具");
    connect(rectAct, &QAction::triggered, this, &MainWindow::setRectangleTool);

    QAction *circleAct = annotationToolBar->addAction("圆形工具");
    connect(circleAct, &QAction::triggered, this, &MainWindow::setCircleTool);

    QAction *polygonAct = annotationToolBar->addAction("多边形工具");
    connect(polygonAct, &QAction::triggered, this, &MainWindow::setPolygonTool);

    // AI工具栏
    QToolBar *aiToolBar = addToolBar("AI工具");
    
    QAction *segmentAct = aiToolBar->addAction("自动分割");
    connect(segmentAct, &QAction::triggered, this, &MainWindow::runAutoSegmentation);

    // 添加编辑工具栏
    QToolBar *editToolBar = addToolBar("编辑");
    
    QAction *undoAct = undoStack->createUndoAction(this, "撤销");
    undoAct->setShortcut(QKeySequence::Undo);
    editToolBar->addAction(undoAct);

    QAction *redoAct = undoStack->createRedoAction(this, "重做");
    redoAct->setShortcut(QKeySequence::Redo);
    editToolBar->addAction(redoAct);

    // 添加撤销历史视图
    QAction *showUndoViewAct = editToolBar->addAction("显示历史");
    connect(showUndoViewAct, &QAction::triggered, this, &MainWindow::createUndoView);

    // 添加视图控制工具栏
    QToolBar *viewToolBar = addToolBar("视图控制");
    
    QAction *zoomInAct = viewToolBar->addAction("放大");
    zoomInAct->setShortcut(QKeySequence::ZoomIn);
    connect(zoomInAct, &QAction::triggered, this, [this]() {
        view->setZoomFactor(view->zoomFactor() * 1.2);
    });

    QAction *zoomOutAct = viewToolBar->addAction("缩小");
    zoomOutAct->setShortcut(QKeySequence::ZoomOut);
    connect(zoomOutAct, &QAction::triggered, this, [this]() {
        view->setZoomFactor(view->zoomFactor() / 1.2);
    });

    QAction *resetZoomAct = viewToolBar->addAction("重置缩放");
    resetZoomAct->setShortcut(QKeySequence("Ctrl+0"));
    connect(resetZoomAct, &QAction::triggered, this, [this]() {
        view->resetZoom();
    });

    // 添加缩放比例显示
    QLabel *zoomLabel = new QLabel(this);
    viewToolBar->addWidget(zoomLabel);
    connect(view, &ZoomableView::zoomFactorChanged, this, [zoomLabel](qreal factor) {
        zoomLabel->setText(QString::number(factor * 100, 'f', 0) + "%");
    });

    // 添加样式工具栏
    QToolBar *styleToolBar = addToolBar("样式设置");
    
    QAction *styleAct = styleToolBar->addAction("设置样式");
    connect(styleAct, &QAction::triggered, this, &MainWindow::showStyleDialog);
}

void MainWindow::openImage()
{
    QString fileName = QFileDialog::getOpenFileName(this,
        "打开图像", "", "图像文件 (*.png *.jpg *.bmp)");
    
    if (!fileName.isEmpty()) {
        currentImagePath = fileName;
        scene->loadImage(fileName);
        scene->setImageFileName(fileName);  // 现在可以调用这个方法了
        view->fitInView(scene->sceneRect(), Qt::KeepAspectRatio);
    }
}

void MainWindow::setRectangleTool()
{
    scene->setToolType(AnnotationScene::Rectangle);
}

void MainWindow::setCircleTool()
{
    scene->setToolType(AnnotationScene::Circle);
}

void MainWindow::setPolygonTool()
{
    scene->setToolType(AnnotationScene::Polygon);
}

void MainWindow::runAutoSegmentation()
{
    if (currentImagePath.isEmpty()) {
        QMessageBox::warning(this, "警告", "请先打开一张图片");
        return;
    }
    QMessageBox::information(this, "提示", "自动分割功能尚未实现");
}

void MainWindow::createUndoView()
{
    if (!undoView) {
        undoView = new QDockWidget(tr("操作历史"), this);
        undoView->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
        QUndoView *view = new QUndoView(undoStack, undoView);
        undoView->setWidget(view);
        addDockWidget(Qt::RightDockWidgetArea, undoView);
    }
    undoView->show();
}

void MainWindow::saveAnnotations()
{
    if (currentImagePath.isEmpty()) {
        QMessageBox::warning(this, "警告", "请先打开一张图片");
        return;
    }

    QString fileName = QFileDialog::getSaveFileName(this,
        "保存标注", "", "JSON文件 (*.json);;XML文件 (*.xml)");
    
    if (fileName.isEmpty())
        return;
        
    bool success = false;
    if (fileName.endsWith(".json")) {
        success = scene->saveToJson(fileName);
    } else if (fileName.endsWith(".xml")) {
        success = scene->saveToXml(fileName);
    }
    
    if (success) {
        QMessageBox::information(this, "成功", "标注数据保存成功！");
    } else {
        QMessageBox::critical(this, "错误", "保存标注数据失败！");
    }
}

void MainWindow::showStyleDialog()
{
    if (!styleDialog) {
        styleDialog = new StyleDialog(this);
        connect(styleDialog, &StyleDialog::styleChanged,
                this, &MainWindow::applyStyle);
    }
    
    styleDialog->setPen(currentPen);
    styleDialog->setBrush(currentBrush);
    
    if (styleDialog->exec() == QDialog::Accepted) {
        currentPen = styleDialog->getPen();
        currentBrush = styleDialog->getBrush();
        scene->setDefaultStyle(currentPen, currentBrush);
    }
}

void MainWindow::applyStyle(const QPen &pen, const QBrush &brush)
{
    // 更新当前选中项的样式
    foreach (QGraphicsItem *item, scene->selectedItems()) {
        if (item->type() == AnnotationItem::Type) {
            AnnotationItem *annItem = static_cast<AnnotationItem*>(item);
            annItem->setPen(pen);
            annItem->setBrush(brush);
        }
    }
} 