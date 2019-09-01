#pragma once

#include <QtWidgets/QWidget>
#include "ui_sqlback.h"

class sqlback : public QWidget
{
	Q_OBJECT

public:
	sqlback(QWidget *parent = Q_NULLPTR);

private:
	Ui::sqlbackClass ui;
private slots:
	void on_pushButton_clicked();
};
