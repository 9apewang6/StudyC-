#ifndef _AXISCFG_H_
#define _AXISCFG_H_
#include <QPushButton>
#include <QLabel>
#include <QSpinBox>
#include <QList>
#include <string>
struct AxisConfig
{
    std::string lable_;
    std::string left_;
    std::string right_;
    std::string speed_;
    std::string startmove_;
    std::string position_;
    std::string goback_;
    AxisConfig()
    {
        lable_ = "";
        left_ = "";
        right_ = "";
        speed_ = ""; 
        startmove_ = "";
        position_ = "";
        goback_ = "";
    }
};


struct Components
{
    QList<QLabel*> m_axis;
    QList<QPushButton*> m_left;
    QList<QPushButton*> m_right;

    QList<QLabel*> m_speedlabel;
    QList<QSpinBox*> m_speed;
    QList<QPushButton*> m_start;
    QList<QLabel*> m_positionLabel;
    QList<QSpinBox*> m_position;
    QList<QPushButton*> m_goback;
    Components()
    {
        m_axis.clear();
        m_left.clear();
        m_right.clear();
        m_speedlabel.clear();
        m_speed.clear();
        m_start.clear();
        m_positionLabel.clear();
        m_position.clear();
        m_goback.clear();
    }
    void reset()
    {
        qDeleteAll(m_axis);
        m_axis.clear();

        qDeleteAll(m_left);
        m_left.clear();

        qDeleteAll(m_right);
        m_right.clear();

        qDeleteAll(m_speedlabel);
        m_speedlabel.clear();

        qDeleteAll(m_speed);
        m_speed.clear();

        qDeleteAll(m_start);
        m_start.clear();


        qDeleteAll(m_positionLabel);
        m_positionLabel.clear();

        qDeleteAll(m_position);
        m_position.clear();

        qDeleteAll(m_goback);
        m_goback.clear();

  }
};

#endif //_AXISCFG_H_