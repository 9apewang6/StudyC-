#ifndef _VPMODELWIDGET_H_
#define _VPMODELWIDGET_H_
#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
class vpmodelwidget : public QWidget
{
    Q_OBJECT

public:
    vpmodelwidget(QWidget *parent);
    ~vpmodelwidget();

    void setText(QString name, QString path);
    QString path();


private:
    QLabel* mNameLabel;
    QLabel* mPathLabel;
    QVBoxLayout* mLayout;
};

#endif //_VPMODELWIDGET_H_