#ifndef LABELEDITOR_H
#define LABELEDITOR_H

#include <QDialog>
#include <QLineEdit>
#include <QComboBox>

namespace Ui {
class LabelEditor;
}

class LabelEditor : public QDialog
{
    Q_OBJECT

public:
    explicit LabelEditor(QWidget *parent = nullptr);
    ~LabelEditor();

    QString getLabel() const;
    QString getCategory() const;
    void setLabel(const QString &label);
    void setCategory(const QString &category);

private:
    Ui::LabelEditor *ui;
    QLineEdit *labelEdit;
    QComboBox *categoryCombo;
};

#endif // LABELEDITOR_H 