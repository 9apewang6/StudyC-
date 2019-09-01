/*	File name: plc_com_protocol.h
*
*	plc comm implementation
*
*	CCopyright (C) bomming
*
*	Created @  ylshan 2019-6-13
*/

#ifndef PLC_COM_PROTOCOL_H
#define PLC_COM_PROTOCOL_H

#include "..\QCableTest\modbus_comm_def.h"
#include <QObject>
#include <QDebug>
#include <QThread>
#include <thread>
#include <mutex>
#include "modbus.h"

using namespace std;

using namespace bm_modbus_comm;

class plc_comm_protocol:public QObject
{
	Q_OBJECT
public:
	plc_comm_protocol(modbus_comm_param param);
	~plc_comm_protocol();

public:
	int on_connect();
	void dis_connect();

	void start();
	void stop();

	void ribbon_width_alarm_off();
	void ribbon_width_alarm_on();

	void trigger_reset_off();
	void trigger_reset_on();
	int trigger_reset();
	int trigger_coder();

	//���
	void trigger_marking();

	// ��ȡ������ť״̬
	bool get_status_switch();

	void light_control(bm_plc_value_status status);// ����/�ر� plc���ƹ�Դ  //��Ч
	void light_soud(bm_light_soud_status status, bm_plc_value_status value= bm_plc_value_status::on);
	// ���÷�����ģʽ
	void buzzer_mode(bm_buzzer_ring_mode ring_mode_);
	// ���ö̼��������ʱ��
	void short_buzzing_time(int times_);
	// ���ó����������ʱ��
	void long_buzzing_time(int times_);
	// ���ö̼�����������ʱ��
	void short_buzzing_interval(bm_buzzer_short_ring_interval intervals_);
	// ������
	void trigger_cnt();
	// ���
	double getCableMil();
	// �ٶ�
	double cable_speed();

	// ������
	void clearCableMil();
	// ���������
	void setCableLength(double length);
	// �������������� �������
	void setCamTriggerInterval(double Interval);
	// ��������
	void trigger_switch(bm_plc_value_status status);
private:
	void set_value(int addr, int value);
	void set_light_values(int addr, int value_normal, int value_green, int value_red);
	void onData(uint16_t*);

	void transfor(plc_register_info& data);

private:
	void task();
private:
	std::thread trd_task_;
	bool _exit = false;

private:
	modbus_comm_param param_;
	modbus_t* mb_ = nullptr;
	plc_register_info data_;
	mutex mutex_;

private:
	bool switch_btn_status_ = false;
	double mCableMil = 0.0;
	double cable_speed_ = 0.0;
	int codeer_count_;
	int conn_status;
	int trigger_flag_;
	unsigned short  read_tag_event_cnt_;//�� ͨ���������ʶ��;
	unsigned short write_tag_event_cnt_;
	short   tag_data_len_;// ���ݳ���
	unsigned char dev_addr_;//�豸��ַ�����Ա�ʶ�����ڴ����߻��������ϵ�Զ�̷���˵ĵ�ַ

signals:
	void update_info(plc_register_info);
};

#endif