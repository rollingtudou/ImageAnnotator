#include "styledialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QPainter>

StyleDialog::StyleDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("标注样式设置");

    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // 颜色选择
    QPushButton *colorButton = new QPushButton("选择颜色", this);
    connect(colorButton, &QPushButton::clicked, this, &StyleDialog::selectColor);
    mainLayout->addWidget(colorButton);

    // 线宽设置
    QHBoxLayout *lineWidthLayout = new QHBoxLayout;
    lineWidthLayout->addWidget(new QLabel("线宽:"));
    lineWidthSpin = new QSpinBox(this);
    lineWidthSpin->setRange(1, 10);
    lineWidthSpin->setValue(2);
    connect(lineWidthSpin, QOverload<int>::of(&QSpinBox::valueChanged),
            this, &StyleDialog::updatePreview);
    lineWidthLayout->addWidget(lineWidthSpin);
    mainLayout->addLayout(lineWidthLayout);

    // 透明度设置
    QHBoxLayout *opacityLayout = new QHBoxLayout;
    opacityLayout->addWidget(new QLabel("透明度:"));
    opacitySlider = new QSlider(Qt::Horizontal, this);
    opacitySlider->setRange(0, 100);
    opacitySlider->setValue(50);
    connect(opacitySlider, &QSlider::valueChanged,
            this, &StyleDialog::updatePreview);
    opacityLayout->addWidget(opacitySlider);
    mainLayout->addLayout(opacityLayout);

    // 预览区域
    previewFrame = new QFrame(this);
    previewFrame->setMinimumHeight(100);
    previewFrame->setFrameStyle(QFrame::Panel | QFrame::Sunken);
    previewFrame->setAutoFillBackground(true);
    
    // 添加绘制事件处理
    previewFrame->installEventFilter(this);
    
    mainLayout->addWidget(previewFrame);

    // 确定取消按钮
    QHBoxLayout *buttonLayout = new QHBoxLayout;
    QPushButton *okButton = new QPushButton("确定", this);
    QPushButton *cancelButton = new QPushButton("取消", this);
    connect(okButton, &QPushButton::clicked, this, &QDialog::accept);
    connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);
    mainLayout->addLayout(buttonLayout);

    // 初始化画笔和画刷
    m_pen = QPen(Qt::red, 2);
    m_brush = QBrush(QColor(255, 0, 0, 127));

    updatePreview();
}

void StyleDialog::selectColor()
{
    QColor color = QColorDialog::getColor(m_pen.color(), this, "选择标注颜色",
                                        QColorDialog::ShowAlphaChannel);
    if (color.isValid()) {
        m_pen.setColor(color);
        m_brush.setColor(QColor(color.red(), color.green(), color.blue(),
                              opacitySlider->value() * 255 / 100));
        updatePreview();
    }
}

void StyleDialog::updatePreview()
{
    m_pen.setWidth(lineWidthSpin->value());
    QColor brushColor = m_pen.color();
    brushColor.setAlpha(opacitySlider->value() * 255 / 100);
    m_brush.setColor(brushColor);

    previewFrame->update();
    emit styleChanged(m_pen, m_brush);
}

QPen StyleDialog::getPen() const
{
    return m_pen;
}

QBrush StyleDialog::getBrush() const
{
    return m_brush;
}

void StyleDialog::setPen(const QPen &pen)
{
    m_pen = pen;
    lineWidthSpin->setValue(pen.width());
    updatePreview();
}

void StyleDialog::setBrush(const QBrush &brush)
{
    m_brush = brush;
    opacitySlider->setValue(brush.color().alpha() * 100 / 255);
    updatePreview();
}

bool StyleDialog::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == previewFrame && event->type() == QEvent::Paint) {
        QPainter painter(previewFrame);
        painter.setPen(m_pen);
        painter.setBrush(m_brush);
        
        QRect rect = previewFrame->rect().adjusted(10, 10, -10, -10);
        painter.drawRect(rect);
        return true;
    }
    return QDialog::eventFilter(obj, event);
} 