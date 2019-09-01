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

	//打标
	void trigger_marking();

	// 获取紧急按钮状态
	bool get_status_switch();

	void light_control(bm_plc_value_status status);// 开启/关闭 plc控制光源  //无效
	void light_soud(bm_light_soud_status status, bm_plc_value_status value= bm_plc_value_status::on);
	// 设置蜂鸣器模式
	void buzzer_mode(bm_buzzer_ring_mode ring_mode_);
	// 设置短间隔蜂鸣器时间
	void short_buzzing_time(int times_);
	// 设置长间隔蜂鸣器时间
	void long_buzzing_time(int times_);
	// 设置短间隔蜂鸣器间隔时间
	void short_buzzing_interval(bm_buzzer_short_ring_interval intervals_);
	// 触发数
	void trigger_cnt();
	// 里程
	double getCableMil();
	// 速度
	double cable_speed();

	// 清除里程
	void clearCableMil();
	// 设置里程数
	void setCableLength(double length);
	// 设置相机触发间隔 辅助相机
	void setCamTriggerInterval(double Interval);
	// 触发开关
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
	unsigned short  read_tag_event_cnt_;//读 通信事务处理标识符;
	unsigned short write_tag_event_cnt_;
	short   tag_data_len_;// 数据长度
	unsigned char dev_addr_;//设备地址，用以标识连接在串行线或者网络上的远程服务端的地址

signals:
	void update_info(plc_register_info);
};

#endif