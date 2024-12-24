#include "labeleditor.h"
#include "ui_labeleditor.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>

LabelEditor::LabelEditor(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LabelEditor)
{
    ui->setupUi(this);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // 标签输入
    QHBoxLayout *labelLayout = new QHBoxLayout;
    labelLayout->addWidget(new QLabel("标签名称:"));
    labelEdit = new QLineEdit(this);
    labelLayout->addWidget(labelEdit);
    mainLayout->addLayout(labelLayout);

    // 类别选择
    QHBoxLayout *categoryLayout = new QHBoxLayout;
    categoryLayout->addWidget(new QLabel("类别:"));
    categoryCombo = new QComboBox(this);
    categoryCombo->addItems({"人物", "动物", "植物", "车辆", "建筑", "其他"});
    categoryLayout->addWidget(categoryCombo);
    mainLayout->addLayout(categoryLayout);

    // 按钮
    QHBoxLayout *buttonLayout = new QHBoxLayout;
    QPushButton *okButton = new QPushButton("确定", this);
    QPushButton *cancelButton = new QPushButton("取消", this);
    connect(okButton, &QPushButton::clicked, this, &QDialog::accept);
    connect(cancelButton, &QPushButton::clicked, this, &QDialog::reject);
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);
    mainLayout->addLayout(buttonLayout);
}

LabelEditor::~LabelEditor()
{
    delete ui;
}

QString LabelEditor::getLabel() const
{
    return labelEdit->text();
}

QString LabelEditor::getCategory() const
{
    return categoryCombo->currentText();
}

void LabelEditor::setLabel(const QString &label)
{
    labelEdit->setText(label);
}

void LabelEditor::setCategory(const QString &category)
{
    int index = categoryCombo->findText(category);
    if (index >= 0) {
        categoryCombo->setCurrentIndex(index);
    }
} 