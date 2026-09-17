
#include "widget.h"
#include <QToolButton>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QMessageBox>
#include <QPixmap>
#include <QFileInfo>
#include <QStyle>
#include<QPixmap>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    this->setWindowTitle("运行");
    toolButton_file = new QToolButton(this);
    toolButton_file->setText("选择文件");
    toolButton_file->setIcon(style()->standardIcon(QStyle::SP_DirOpenIcon));

    lineEdit_path = new QLineEdit(this);
    lineEdit_path->setReadOnly(true);

    label_preview = new QLabel("预览区域", this);
    label_preview->setAlignment(Qt::AlignCenter);
    label_preview->setMinimumSize(300, 200);
    label_preview->setStyleSheet("border: 1px solid gray;");

    btnPreview = new QPushButton("预览", this);
    btnOK      = new QPushButton("确定", this);
    btnCancel  = new QPushButton("取消", this);

    QHBoxLayout *topLayout = new QHBoxLayout;
    topLayout->addWidget(toolButton_file);
    topLayout->addWidget(lineEdit_path);

    QHBoxLayout *btnLayout = new QHBoxLayout;
    btnLayout->addWidget(btnPreview);
    btnLayout->addWidget(btnOK);
    btnLayout->addWidget(btnCancel);

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(topLayout);
    mainLayout->addWidget(label_preview);
    mainLayout->addLayout(btnLayout);

    connect(toolButton_file, &QToolButton::clicked, this, &Widget::selectFile);
    connect(btnPreview, &QPushButton::clicked, this, &Widget::doPreview);
    connect(btnOK, &QPushButton::clicked, this, &Widget::doOK);
    connect(btnCancel, &QPushButton::clicked, this, &Widget::doCancel);
}

Widget::~Widget() {}

void Widget::selectFile()
{
    QString file = QFileDialog::getOpenFileName(this);
    if (!file.isEmpty()) {
        selectedFilePath = file;
        lineEdit_path->setText(file);
    }
}

void Widget::doPreview()
{
    if (selectedFilePath.isEmpty()) {
        QMessageBox::warning(this, "提示", "请先选择文件");
        return;
    }

    QFileInfo info(selectedFilePath);
    if (info.suffix().toLower() == "png" ||
        info.suffix().toLower() == "jpg" ||
        info.suffix().toLower() == "bmp") {
        label_preview->setPixmap(
            QPixmap(selectedFilePath).scaled(
                label_preview->size(),
                Qt::KeepAspectRatio,
                Qt::SmoothTransformation
            )
        );
    } else {
        label_preview->setText(selectedFilePath);
    }
}

void Widget::doOK()
{
    QMessageBox::information(this, "确定", selectedFilePath);
    close();
}

void Widget::doCancel()
{
    close();
}
