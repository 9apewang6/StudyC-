#include "TestWizard.h"

TestWizard::TestWizard(QWidget *parent)
    : QWizard(parent),m_fir(new firstpage),m_sec(new Secondpage),m_thi(new Thirdpage)
{
    setPage(TestWizard::Page_First, m_fir);
    setPage(TestWizard::Page_second, m_sec);
    setPage(TestWizard::Page_third, m_thi);

    //
    setWizardStyle(QWizard::ModernStyle);
    setWindowTitle("Qt wizard");

    QPixmap pix(QSize(500, 78));
    pix.fill(QColor(173, 173, 173));
    setPixmap(QWizard::BannerPixmap, pix);


    setTitleFormat(Qt::RichText);
    //设置子标题显示格式
    setSubTitleFormat(Qt::RichText);


    setButtonText(QWizard::NextButton, QStringLiteral("<下一步>"));
    setButtonText(QWizard::BackButton, QStringLiteral("<上一步"));

}
