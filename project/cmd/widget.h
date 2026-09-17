
#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QToolButton;
class QLineEdit;
class QLabel;
class QPushButton;
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void selectFile();
    void doPreview();
    void doOK();
    void doCancel();

private:
    QToolButton *toolButton_file;
    QLineEdit   *lineEdit_path;
    QLabel      *label_preview;

    QPushButton *btnPreview;
    QPushButton *btnOK;
    QPushButton *btnCancel;

    QString selectedFilePath;
};

#endif // WIDGET_H
