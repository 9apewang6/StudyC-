#include "plc_monitor.h"

plc_monitor::plc_monitor(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	ui.comboBox_buzzer_mode->addItem("long", 0);
	ui.comboBox_buzzer_mode->addItem("short", 1);

	ui.comboBox_short_buzzing_interval->addItem("short_ring_one", 0);
	ui.comboBox_short_buzzing_interval->addItem("short_ring_two", 1);
	ui.comboBox_short_buzzing_interval->addItem("short_ring_third", 2);

	model_data_ = new QStandardItemModel(ui.tableView);

	model_data_->setColumnCount(2);

	modbus_comm_param param;
	param.run.conn_type = bm_modbus_comm::bm_modbus_conn_type::tcp;
	param.run.server_addr = 1;
	sprintf_s(param.tcp.ip, "192.168.0.1");
//	sprintf_s(param.tcp.ip, "127.0.0.1");
	param.tcp.port = 502;
//	param.run.time_out = 3000;

	plc_comm_protocol_ = new plc_comm_protocol(param);
	plc_comm_protocol_->on_connect();

	plc_comm_protocol_->start();

	connect(plc_comm_protocol_, &plc_comm_protocol::update_info, this, &plc_monitor::update_info);
}

void plc_monitor::update_info(plc_register_info setting)
{
	model_data_->clear();
	model_data_->setHeaderData(0, Qt::Vertical, QStringLiteral("字段"));
	model_data_->setHeaderData(1, Qt::Vertical, QStringLiteral("值"));
	model_data_->setItem(0, 0, new QStandardItem(QStringLiteral("输出里程")));
	model_data_->setItem(0, 1, new QStandardItem(QString::number(setting.o_cable_register)));

	model_data_->setItem(1, 0, new QStandardItem(QStringLiteral("输入里程")));
	model_data_->setItem(1, 1, new QStandardItem(QString::number(setting.l_cable_register)));

	model_data_->setItem(2, 0, new QStandardItem(QStringLiteral("未使用")));
	model_data_->setItem(2, 1, new QStandardItem(QString::number(setting.start_register)));

	model_data_->setItem(3, 0, new QStandardItem(QStringLiteral("绿色灯")));
	model_data_->setItem(3, 1, new QStandardItem(QString::number(setting.green_lamp_register)));

	model_data_->setItem(4, 0, new QStandardItem(QStringLiteral("红色灯")));
	model_data_->setItem(4, 1, new QStandardItem(QString::number(setting.red_lamp_register)));

	model_data_->setItem(5, 0, new QStandardItem(QStringLiteral("黄色灯")));
	model_data_->setItem(5, 1, new QStandardItem(QString::number(setting.yellow_lamp_register)));

	model_data_->setItem(6, 0, new QStandardItem(QStringLiteral("重置灯状态")));
	model_data_->setItem(6, 1, new QStandardItem(QString::number(setting.clear_lamp_register)));

	model_data_->setItem(7, 0, new QStandardItem(QStringLiteral("初始化里程")));
	model_data_->setItem(7, 1, new QStandardItem(QString::number(setting.initial_length)));

	model_data_->setItem(8, 0, new QStandardItem(QStringLiteral("编码器触发数")));
	model_data_->setItem(8, 1, new QStandardItem(QString::number(setting.tigger_codeer_register)));

	model_data_->setItem(9, 0, new QStandardItem(QStringLiteral("告警灯控制")));
	model_data_->setItem(9, 1, new QStandardItem(QString::number(setting.light_control_register)));

	model_data_->setItem(10, 0, new QStandardItem(QStringLiteral("帧触发控制")));
	model_data_->setItem(10, 1, new QStandardItem(QString::number(setting.tigger_control_register)));

	model_data_->setItem(11, 0, new QStandardItem(QStringLiteral("触发器开关")));
	model_data_->setItem(11, 1, new QStandardItem(QString::number(setting.switch_register)));

	model_data_->setItem(12, 0, new QStandardItem(QStringLiteral("速度")));
	model_data_->setItem(12, 1, new QStandardItem(QString::number(setting.speed_register)));

	model_data_->setItem(13, 0, new QStandardItem(QStringLiteral("急停开关")));
	model_data_->setItem(13, 1, new QStandardItem(QString::number(setting.switch_btn_register)));

	model_data_->setItem(14, 0, new QStandardItem(QStringLiteral("辅助相机触发间隔")));
	model_data_->setItem(14, 1, new QStandardItem(QString::number(setting.tigger_interval_register)));

	model_data_->setItem(15, 0, new QStandardItem(QStringLiteral("打标机")));
	model_data_->setItem(15, 1, new QStandardItem(QString::number(setting.trigger_Marking_register)));

	model_data_->setItem(16, 0, new QStandardItem(QStringLiteral("短间隔蜂鸣器")));
	model_data_->setItem(16, 1, new QStandardItem(QString::number(setting.short_buzzing_trigger_choice)));

	model_data_->setItem(17, 0, new QStandardItem(QStringLiteral("长间隔蜂鸣器")));
	model_data_->setItem(17, 1, new QStandardItem(QString::number(setting.long_buzzing_trigger_choice)));

	model_data_->setItem(18, 0, new QStandardItem(QStringLiteral("蜂鸣器选项")));
	model_data_->setItem(18, 1, new QStandardItem(QString::number(setting.buzzing_trigger_choice)));

	model_data_->setItem(19, 0, new QStandardItem(QStringLiteral("短蜂鸣器间隔")));
	model_data_->setItem(19, 1, new QStandardItem(QString::number(setting.short_buzzing_time_choice)));

	model_data_->setItem(20, 0, new QStandardItem(QStringLiteral("分卷")));
	model_data_->setItem(20, 1, new QStandardItem(QString::number(setting.subSection)));

	model_data_->setItem(21, 0, new QStandardItem(QStringLiteral("电缸位置")));
	model_data_->setItem(21, 1, new QStandardItem(QString::number(setting.cylinderPosition)));

	model_data_->setItem(22, 0, new QStandardItem(QStringLiteral("光源状态")));
	model_data_->setItem(22, 1, new QStandardItem(QString::number(setting.lightSource)));

	model_data_->setItem(23, 0, new QStandardItem(QStringLiteral("电缸运动")));
	model_data_->setItem(23, 1, new QStandardItem(QString::number(setting.moveRegister)));

	model_data_->setItem(24, 0, new QStandardItem(QStringLiteral("目标位置")));
	model_data_->setItem(24, 1, new QStandardItem(QString::number(setting.aim)));

	model_data_->setItem(25, 0, new QStandardItem(QStringLiteral("运动状态")));
	model_data_->setItem(25, 1, new QStandardItem(QString::number(setting.status)));

	ui.tableView->setModel(model_data_);
}
void plc_monitor::on_control_register_on_clicked()
{
	plc_comm_protocol_->trigger_reset_on();
}
void plc_monitor::on_control_register_off_clicked()
{
	plc_comm_protocol_->trigger_reset_off();
}
void plc_monitor::on_trigger_coder_clicked()
{
	plc_comm_protocol_->trigger_coder();
}
void plc_monitor::on_trigger_marking_clicked()
{
	plc_comm_protocol_->trigger_marking();
}
void plc_monitor::on_clearCableMil_clicked()
{
	plc_comm_protocol_->clearCableMil();
}
void plc_monitor::on_trigger_switch_on_clicked()
{
	plc_comm_protocol_->trigger_switch(bm_plc_value_status::on);
}
void plc_monitor::on_trigger_switch_off_clicked()
{
	plc_comm_protocol_->trigger_switch(bm_plc_value_status::off);
}
void plc_monitor::on_setCableLength_clicked()
{
	plc_comm_protocol_->setCableLength(ui.CableLength->text().toInt());
}
void plc_monitor::on_setCamTriggerInterval_clicked()
{
	plc_comm_protocol_->setCamTriggerInterval(ui.CamTriggerInterval->text().toInt());
}

void plc_monitor::on_light_control_on_clicked()
{
	plc_comm_protocol_->light_control(bm_plc_value_status::on);
}
void plc_monitor::on_light_control_off_clicked()
{
	plc_comm_protocol_->light_control(bm_plc_value_status::off);
}
void plc_monitor::on_buzzer_mode_clicked()
{
	if(0==ui.comboBox_buzzer_mode->currentIndex())
		plc_comm_protocol_->buzzer_mode(bm_buzzer_ring_mode::long_buzzing);
	else plc_comm_protocol_->buzzer_mode(bm_buzzer_ring_mode::short_buzzing);
}
void plc_monitor::on_ocr_mil_clicked()
{
	plc_comm_protocol_->light_soud(bm_light_soud_status::critical, bm_plc_value_status::interval_2);
}
void plc_monitor::on_ocr_others_clicked()
{
	plc_comm_protocol_->light_soud(bm_light_soud_status::critical, bm_plc_value_status::interval_3);
}
void plc_monitor::on_surface_ln_clicked()
{
	plc_comm_protocol_->light_soud(bm_light_soud_status::critical);
}
void plc_monitor::on_surface_dia_clicked()
{
	plc_comm_protocol_->light_soud(bm_light_soud_status::critical);
}
void plc_monitor::on_surface_sur_clicked()
{
	plc_comm_protocol_->light_soud(bm_light_soud_status::critical);
}
void plc_monitor::on_short_buzzing_time_clicked()
{
	plc_comm_protocol_->short_buzzing_time(ui.tbshort_buzzing_time->text().toInt());
}
void plc_monitor::on_long_buzzing_time_clicked()
{
	plc_comm_protocol_->long_buzzing_time(ui.tblong_buzzing_time->text().toInt());
}
void plc_monitor::on_short_buzzing_interval_clicked()
{
		if (0 == ui.comboBox_buzzer_mode->currentIndex())plc_comm_protocol_->short_buzzing_interval(short_ring_one);
		else if (1== ui.comboBox_buzzer_mode->currentIndex())plc_comm_protocol_->short_buzzing_interval(short_ring_two);
		else if (2 == ui.comboBox_buzzer_mode->currentIndex())plc_comm_protocol_->short_buzzing_interval(short_ring_third);
}
