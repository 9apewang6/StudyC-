#include <QFile>
#include <QJsonArray>
#include <QJsonValue>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonParseError>

#include "DebugMotion.h"


DebugMotion::DebugMotion(QWidget* parent):QWidget(parent),_isInit(false),len_(0),addr_(0),val_(0), m_CurId(0)
{
   

}


DebugMotion::~DebugMotion()
{
    if (plcmanager)plcmanager->deInitialize();
    qDeleteAll(horizont_);
    horizont_.clear();
    qDeleteAll(m_pointBtn);
    m_pointBtn.clear();
    delete pbtnLayout;
    pbtnLayout = nullptr;

    delete vblayout;
    vblayout = nullptr;
  
    cfgs_.clear();
    views_.reset();
}

void DebugMotion::loadConfig(const std::string& path)
{
    horizont_.clear();
    cfgs_.clear();
    views_.reset();

    cfgFile = QString::fromStdString(path);
    QFile js(cfgFile);
    js.open(QIODevice::ReadWrite);
    QString contex;
    if (js.isOpen())
    {
        contex = js.readAll();
    }
    else
    {
        _isInit = false;
        return;
    }

    QJsonParseError parseJsonErr;
    QJsonDocument document = QJsonDocument::fromJson(contex.toUtf8(), &parseJsonErr);

    if (!(parseJsonErr.error == QJsonParseError::NoError))
    {
        return;
    }
    QJsonObject jsonobj = document.object();
    if (jsonobj.contains(QStringLiteral("MOTION")))
    {
        QJsonValue jsonValueslist = jsonobj.value(QStringLiteral("MOTION"));
        if (jsonValueslist.isArray())
        {
            QJsonArray array = jsonValueslist.toArray();
            for (int i = 0; i < array.size(); i++) {
                AxisConfig a_cfg;
                QJsonValue iconarray = array.at(i);
                QJsonObject icon = iconarray.toObject();
                a_cfg.lable_ = icon["label"].toString().toLocal8Bit();
                a_cfg.left_ = icon["Left"].toString().toStdString();
                a_cfg.right_ = icon["Right"].toString().toStdString();
                a_cfg.speed_ = icon["Speed"].toString().toStdString();
                a_cfg.startmove_ = icon["Start"].toString().toStdString();
                a_cfg.position_ = icon["Position"].toString().toStdString();
                a_cfg.goback_ = icon["GoBack"].toString().toStdString();

                cfgs_.push_back(a_cfg);
            }
        }
    }

    if (jsonobj.contains("EnsurePoint"))
    {
        QJsonValue jsonValueslist = jsonobj.value(QStringLiteral("EnsurePoint"));
        if (jsonValueslist.isArray())
        {
            QJsonArray array = jsonValueslist.toArray();
            for (int i = 0; i < array.size(); i++) {
              
                QJsonValue iconarray = array.at(i);
                QJsonObject icon = iconarray.toObject();
               
                m_points.push_back(icon["addr"].toString().toStdString());
                m_pointSured.push_back(false);
                
            }
        }
    }

    product_addr = jsonobj.value("ProductId").toString().toStdString();


    if (jsonobj.contains("MotionJson"))
    {
        QJsonValue p_serpath = jsonobj.value(QStringLiteral("MotionJson"));

        motionFile = p_serpath.toString();
        if (!motionFile.isEmpty())
        {       
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }
    if (jsonobj.contains("MotionLabel"))
    {
        motionLabel = jsonobj.value(QStringLiteral("MotionLabel")).toString().toStdString();
    }
    if (jsonobj.contains("qssfile"))
    {
        qssFile = jsonobj.value(QStringLiteral("qssfile")).toString();
    }
    js.close();


    initMotionHandle();

    initView();
}

void DebugMotion::setCurrentProductId(const int index)
{
    m_CurId = index;
    if (m_plcdevice)
    {
        parseAddr(product_addr, addr_, type_);
        m_plcdevice->writeInt(type_, addr_, m_CurId);
    }
}

void DebugMotion::reset()
{
 
}

void DebugMotion::initMotionHandle()
{
    plcmanager = PlcDeviceManager::instance();
    if (plcmanager)
    {
        plcmanager->loadConfig(motionFile.toStdString());

        plcmanager->Initialize();
        if (!motionLabel.empty())
        {
            m_plcdevice = plcmanager->getDeviceByLabel(motionLabel);
           
        }
        if (!m_plcdevice)
        {
            std::vector<std::string> labels;
            plcmanager->enumDevice(labels);
            if (labels.size() > 0)m_plcdevice = plcmanager->getDeviceByLabel(labels[0]);
        }
        if (m_plcdevice)
        {
            m_plcdevice->open();
        }
    }
   
}

void DebugMotion::initView()
{

    vblayout = new QVBoxLayout;
    pbtnLayout = new QHBoxLayout;
    int addr;
    int val;
    for (int i = 0; i < cfgs_.size(); i++)
    {
        QHBoxLayout* hori = new QHBoxLayout;


        QLabel* axislabel = new QLabel;
        axislabel->setText(QString::fromLocal8Bit(cfgs_[i].lable_.data()));
        axislabel->setAlignment(Qt::AlignRight);
        views_.m_axis.push_back(axislabel);       
        hori->addWidget(axislabel);


        QPushButton* t_left = new QPushButton;
        t_left->setText(QStringLiteral("向左"));
        connect(t_left,&QPushButton::pressed,this,&DebugMotion::GoLeft);
        connect(t_left, &QPushButton::released, this, &DebugMotion::StopLeft);
        views_.m_left.push_back(t_left);
        hori->addWidget(t_left);

        QPushButton* t_right = new QPushButton;
        t_right->setText(QStringLiteral("向右"));
        connect(t_right, &QPushButton::pressed, this, &DebugMotion::GoRight);
        connect(t_right, &QPushButton::released, this, &DebugMotion::StopRight);
        views_.m_right.push_back(t_right);
        hori->addWidget(t_right);

        QLabel* t_speedlabel = new QLabel;
        t_speedlabel->setText(QStringLiteral("速度"));
        t_speedlabel->setAlignment(Qt::AlignRight);
        views_.m_speedlabel.push_back(t_speedlabel);
        hori->addWidget(t_speedlabel);

        QSpinBox* t_spin = new QSpinBox;
        t_spin->setMinimum(1);
        t_spin->setMaximum(100000);
        if (m_plcdevice)
        {
           // m_plcdevice->readInt(RegisterType::DPART,)
            val_ = 0;
            parseAddr(cfgs_[i].speed_,addr_,type_);
            m_plcdevice->readInt(type_, addr_, val_);
            t_spin->setValue(val_);
        }


        // 先读 
        connect(t_spin, (void(QSpinBox::*)(int))(&QSpinBox::valueChanged), this, &DebugMotion::SpeedChange);
        views_.m_speed.push_back(t_spin);
        hori->addWidget(t_spin);

        QPushButton* t_start = new QPushButton;
        t_start->setText(QStringLiteral("开始运动"));
        connect(t_start,&QPushButton::clicked,this,&DebugMotion::MoveTo);
        views_.m_start.push_back(t_start);
        hori->addWidget(t_start);

        QLabel* t_positionlabel = new QLabel;
        t_positionlabel->setText(QStringLiteral("绝对位置"));
        t_positionlabel->setAlignment(Qt::AlignRight);
        views_.m_positionLabel.push_back(t_positionlabel);
        hori->addWidget(t_positionlabel);

        QSpinBox* t_pos = new QSpinBox;
        t_pos->setMinimum(1);
        t_pos->setMaximum(100000);
        // 先读 
        if (m_plcdevice)
        {
            // m_plcdevice->readInt(RegisterType::DPART,)
            val_ = 0;
            parseAddr(cfgs_[i].position_, addr_, type_);
            m_plcdevice->readInt(type_, addr_, val_);
            t_pos->setValue(val_);
        }
        connect(t_pos, (void(QSpinBox::*)(int))(&QSpinBox::valueChanged), this, &DebugMotion::PositionChange);
        views_.m_position.push_back(t_pos);
        hori->addWidget(t_pos);

        QPushButton* t_back = new QPushButton;
        t_back->setText(QStringLiteral("回零运动"));
        connect(t_back, &QPushButton::clicked, this, &DebugMotion::BackTo);
        views_.m_goback.push_back(t_back);
        hori->addWidget(t_back);

        
        vblayout->addLayout(hori);
    }


    for (int j = 0; j < m_points.size(); j++)
    {
        QPushButton* p_btn = new QPushButton;
        p_btn->setText(QStringLiteral("确定点%1").arg(QString::number(j)));
        m_pointBtn.push_back(p_btn);
        connect(p_btn,&QPushButton::clicked,this,&DebugMotion::EnsurePoint);
        pbtnLayout->addWidget(p_btn, 30);
    }
    vblayout->addLayout(pbtnLayout);

    this->setLayout(vblayout);
    ui.setupUi(this);
}




void DebugMotion::leftmove(int addr, bool tostart)
{
    if (m_plcdevice)
    {
        m_plcdevice->writeInt(RegisterType::MPART, addr, tostart);
    }
}

void DebugMotion::rightmove(int addr, bool tostart)
{
    if (m_plcdevice)
    {
        m_plcdevice->writeInt(RegisterType::MPART, addr, tostart);
    }
}

void DebugMotion::startmoving(int addr, bool tostart)
{
    if (m_plcdevice)
    {
        m_plcdevice->writeInt(RegisterType::MPART, addr, tostart);
    }
}

void DebugMotion::goback(int addr, bool tostart)
{
    if (m_plcdevice)
    {
        m_plcdevice->writeInt(RegisterType::MPART, addr, tostart);
    }
}

void DebugMotion::setSpeed(int addr, int value)
{
    if (m_plcdevice)
    {
        m_plcdevice->writeInt(RegisterType::DPART, addr, value);
    }
}

void DebugMotion::setPosition(int addr, int value)
{
    if (m_plcdevice)
    {
        m_plcdevice->writeInt(RegisterType::DPART, addr, value);
    }
}

void DebugMotion::PointOk(int addr, bool isOk /*= true */)
{
    if (m_plcdevice)
    {
        m_plcdevice->writeInt(RegisterType::MPART,addr_,isOk);
    }
}

void DebugMotion::GoLeft()
{
    QPushButton* signal = qobject_cast<QPushButton*>(sender());
    int rowcount = 0;
    for (rowcount; rowcount < views_.m_left.size(); rowcount++)
    {
        if (signal == views_.m_left[rowcount])
        {
            break;
        }
    }
    if (rowcount < 0 || rowcount >= views_.m_left.size())return;

    parseAddr(cfgs_[rowcount].left_, addr_, type_);
    leftmove(addr_);

}

void DebugMotion::StopLeft()
{
    QPushButton* signal = qobject_cast<QPushButton*>(sender());
    int rowcount = 0;
    for (rowcount; rowcount < views_.m_left.size(); rowcount++)
    {
        if (signal == views_.m_left[rowcount])
        {
            break;
        }
    }
    if (rowcount < 0 || rowcount >= views_.m_left.size())return;

    parseAddr(cfgs_[rowcount].left_, addr_, type_);
    leftmove(addr_, false);
}

void DebugMotion::GoRight()
{
    QPushButton* signal = qobject_cast<QPushButton*>(sender());
    int rowcount = 0;
    for (rowcount; rowcount < views_.m_right.size(); rowcount++)
    {
        if (signal == views_.m_right[rowcount])
        {
            break;
        }
    }
    if (rowcount < 0 || rowcount >= views_.m_right.size())return;

    parseAddr(cfgs_[rowcount].right_, addr_, type_);
    rightmove(addr_);
}

void DebugMotion::StopRight()
{
    QPushButton* signal = qobject_cast<QPushButton*>(sender());
    int rowcount = 0;
    for (rowcount; rowcount < views_.m_right.size(); rowcount++)
    {
        if (signal == views_.m_right[rowcount])
        {
            break;
        }
    }
    if (rowcount < 0 || rowcount >= views_.m_right.size())return;

    parseAddr(cfgs_[rowcount].right_, addr_, type_);
    rightmove(addr_,false);
}

void DebugMotion::MoveTo()
{
    QPushButton* signal = qobject_cast<QPushButton*>(sender());
    int rowcount = 0;
    for (rowcount; rowcount < views_.m_start.size(); rowcount++)
    {
        if (signal == views_.m_start[rowcount])
        {
            break;
        }
    }
    if (rowcount < 0 || rowcount >= views_.m_start.size())return;

    parseAddr(cfgs_[rowcount].startmove_, addr_, type_);
    startmoving(addr_);
}

void DebugMotion::BackTo()
{
    QPushButton* signal = qobject_cast<QPushButton*>(sender());
    int rowcount = 0;
    for (rowcount; rowcount < views_.m_goback.size(); rowcount++)
    {
        if (signal == views_.m_goback[rowcount])
        {
            break;
        }
    }
    if (rowcount < 0 || rowcount >= views_.m_goback.size())return;

    parseAddr(cfgs_[rowcount].goback_, addr_, type_);
    goback(addr_);

}

void DebugMotion::SpeedChange()
{
    QSpinBox* signal = qobject_cast<QSpinBox*>(sender());
    int rowcount = 0;
    for (rowcount; rowcount < views_.m_speed.size(); rowcount++)
    {
        if (signal == views_.m_speed[rowcount])
        {
            break;
        }
    }
    if (rowcount < 0 || rowcount >= views_.m_speed.size())return;

    parseAddr(cfgs_[rowcount].speed_, addr_, type_);
    setSpeed(addr_,signal->value());
}

void DebugMotion::PositionChange()
{
    QSpinBox* signal = qobject_cast<QSpinBox*>(sender());
    int rowcount = 0;
    for (rowcount; rowcount < views_.m_position.size(); rowcount++)
    {
        if (signal == views_.m_position[rowcount])
        {
            break;
        }
    }
    if (rowcount < 0 || rowcount >= views_.m_position.size())return;

    parseAddr(cfgs_[rowcount].position_, addr_, type_);
    setPosition(addr_, signal->value());
}


void DebugMotion::EnsurePoint()
{
    QPushButton* signal = qobject_cast<QPushButton*>(sender());
    int rowcount = 0;
    for (rowcount; rowcount < m_pointBtn.size(); rowcount++)
    {
        if (signal == m_pointBtn[rowcount])
        {
            break;
        }
    }
    if (rowcount < 0 || rowcount >= views_.m_goback.size())return;
    if (m_pointSured[rowcount])
    {
        parseAddr(m_points[rowcount], addr_, type_);

        PointOk(addr_,false);
        m_pointSured[rowcount] = false;
        signal->setText(QStringLiteral("重置点%1").arg(QString::number(rowcount)));
    }
    else
    {
        parseAddr(m_points[rowcount], addr_, type_);

        PointOk(addr_);
        m_pointSured[rowcount] = true;
        signal->setText(QStringLiteral("确认点%1").arg(QString::number(rowcount)));
    }
  
    
}

void DebugMotion::parseAddr(const std::string& intro, int& addr, RegisterType& t)
{
    len_ = intro.size();
    if (len_ == 0)return;
    int dpos = intro.find_first_of('D');
    if (dpos >= 0 && dpos<len_)
    {
        t = RegisterType::DPART;
        addr = std::stoi(intro.substr(dpos+1,len_-1));
        return;
    }
    int mpos = intro.find_first_of('M');
    if (mpos >= 0 && mpos<len_)
    {
        t = RegisterType::MPART;
        addr = std::stoi(intro.substr(mpos+1,len_-1));
        return;
    }
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DebugMotion w;
    w.loadConfig("G:/DebuggingPlc.json");
    w.show();
    return a.exec();
}


extern "C" DEBUGMOTION_EXPORT QWidget* createDebugMotionWidget()
{
    DebugMotion* motion = new DebugMotion();
   return (QWidget*)(motion);
}