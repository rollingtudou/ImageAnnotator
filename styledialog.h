#ifndef STYLEDIALOG_H
#define STYLEDIALOG_H

#include <QDialog>
#include <QColorDialog>
#include <QSpinBox>
#include <QSlider>
#include <QPen>
#include <QBrush>

class StyleDialog : public QDialog
{
    Q_OBJECT

public:
    explicit StyleDialog(QWidget *parent = nullptr);

    QPen getPen() const;
    QBrush getBrush() const;
    void setPen(const QPen &pen);
    void setBrush(const QBrush &brush);

signals:
    void styleChanged(const QPen &pen, const QBrush &brush);

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;

private slots:
    void updatePreview();
    void selectColor();

private:
    QColorDialog *colorDialog;
    QSpinBox *lineWidthSpin;
    QSlider *opacitySlider;
    QFrame *previewFrame;
    
    QPen m_pen;
    QBrush m_brush;
};

#endif // STYLEDIALOG_H 