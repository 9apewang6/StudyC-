#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_plc_monitor.h"
#include <QStandardItemModel>
#include "plc_com_protocol.h"
#include <mutex>

class plc_monitor : public QMainWindow
{
	Q_OBJECT

public:
	plc_monitor(QWidget *parent = Q_NULLPTR);

private slots:
	void update_info(plc_register_info data);
	void on_control_register_on_clicked();
	void on_control_register_off_clicked();
	void on_trigger_coder_clicked();
	void on_trigger_marking_clicked();
	void on_clearCableMil_clicked();
	void on_trigger_switch_on_clicked();
	void on_trigger_switch_off_clicked();
	void on_setCableLength_clicked();
	void on_setCamTriggerInterval_clicked();
	void on_light_control_on_clicked();
	void on_light_control_off_clicked();
	void on_buzzer_mode_clicked();

	void on_ocr_mil_clicked();
	void on_ocr_others_clicked();
	void on_surface_ln_clicked();
	void on_surface_dia_clicked();
	void on_surface_sur_clicked();
	void on_short_buzzing_time_clicked();
	void on_long_buzzing_time_clicked();
	void on_short_buzzing_interval_clicked();

private:
	Ui::plc_monitorClass ui;
	QStandardItemModel* model_data_;
	plc_comm_protocol* plc_comm_protocol_;
};
