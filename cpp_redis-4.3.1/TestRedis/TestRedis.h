#pragma once

#include <QtWidgets/QWidget>
#include "ui_TestRedis.h"

class TestRedis : public QWidget
{
    Q_OBJECT

public:
    TestRedis(QWidget *parent = Q_NULLPTR);
private:
    void test();
private:
    Ui::TestRedisClass ui;
};
