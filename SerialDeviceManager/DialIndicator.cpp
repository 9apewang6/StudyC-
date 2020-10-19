#include "DialIndicator.h"

DialIndicator::DialIndicator()
{

}

DialIndicator::~DialIndicator()
{

}

void DialIndicator::open()
{
    m_Scmm.Open(diacfg);
}

void DialIndicator::close()
{
    m_Scmm.Close();
}

float DialIndicator::readValue()
{
    QString data;
    m_Scmm.getMsg(data);

    return parseMsg(data);
}

void DialIndicator::setCfg(SerialCommInfo info)
{
    diacfg = info;
}

void DialIndicator::sendMsg(const QString& msg)
{
    m_Scmm.SendData(msg);
}

float DialIndicator::parseMsg(const QString& msg)
{
    QStringList ls = msg.split(Seperator);
    int len = msg.size();
    QString ans;
    if(ls.size()>1) ans= ls[ls.size() - 1];
    else ans = msg;
    if (ans.contains(DataSeperator1) || ans.contains(DataSeperator2))
    {
      if(ans.size()>1)  ans = ans.right(ans.size() - 1);
    }
    return ans.toFloat();
}
