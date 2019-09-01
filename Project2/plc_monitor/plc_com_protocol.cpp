/*	File name: plc_com_protocol.h
*
*	plc comm implementation
*
*	CCopyright (C) bomming
*
*	Created @  ylshan 2019-6-13
*/
#include <iostream>
#include "plc_com_protocol.h"
#include "..\QCableTest\log.h"
#include "..\QCableTest\publicDefine.h"
using namespace std;

plc_comm_protocol::plc_comm_protocol(modbus_comm_param param)
{
	qRegisterMetaType<plc_register_info>("plc_register_info");

	param_ = param;
	conn_status = bm_plc_conn_status::disconnect;
	read_tag_event_cnt_ = 0;
	write_tag_event_cnt_ = 0;
	codeer_count_ = 0;
}

plc_comm_protocol::~plc_comm_protocol()
{
	_exit = true;
	if (trd_task_.joinable())
	{
		trd_task_.join();
	}

	if (nullptr != mb_)
	{
		modbus_close(mb_);
		modbus_free(mb_);
		mb_ = nullptr;
	}
}
//////////////////////////////////////////////////////////////////////////////////外部接口////////////////////////////////////////////////////////////////////////////////////////
int plc_comm_protocol::on_connect()
{
	int ret;
	if (nullptr != mb_)
	{
		modbus_close(mb_);
		modbus_free(mb_);
		mb_ = nullptr;
	}
	if (param_.run.conn_type == bm_modbus_comm::serial)
	{
		mb_ = modbus_new_rtu(param_.serial_port.port, param_.serial_port.baud_rate, toupper(param_.serial_port.parity), param_.serial_port.data_bits, param_.serial_port.stop_bits);   //相同的端口只能同时打开一个
	}
	else
	{
		mb_ = modbus_new_tcp(param_.tcp.ip, param_.tcp.port);
	}
	if (nullptr == mb_)
	{
		printf("mb null \r\n");
		return -1;
	}

	ret = modbus_set_slave(mb_, param_.run.server_addr);  //设置modbus从机地址
	if (0 != ret)
	{
		printf("ret %d, %s\r\n", ret, modbus_strerror(errno));
		return ret;
	}

	ret = modbus_connect(mb_);
	if (0 != ret)
	{
		printf("ret %d, %s\r\n", ret, modbus_strerror(errno));
		return ret;
	}
	//ret = modbus_set_debug(mb_, TRUE);
	struct timeval t;
	t.tv_sec = param_.run.time_out / 1000;
	t.tv_usec = (param_.run.time_out % 1000) * 1000;   //设置modbus超时时间为1000毫秒
	ret = modbus_set_response_timeout(mb_, t.tv_sec, t.tv_usec);
	if (0 != ret)
	{
		printf("ret %d, %s\r\n", ret, modbus_strerror(errno));
		return ret;
	}
	modbus_set_error_recovery(mb_, (modbus_error_recovery_mode)(MODBUS_ERROR_RECOVERY_LINK | MODBUS_ERROR_RECOVERY_PROTOCOL));

	trd_task_ = std::thread([=]() {task(); });
	return ret;
}

void plc_comm_protocol::task()
{
	std::this_thread::sleep_for(std::chrono::milliseconds(300));
	while (!_exit)
	{
		uint16_t data[40] = { 0x00 };
		mutex_.lock();
		int ret = modbus_read_registers(mb_, 0, 40, data);
		mutex_.unlock();
		if (ret == 40)onData(data);
//		onData(data);//test
//		printf("modbus_read_registers ret %d \r\n", ret);
		std::this_thread::sleep_for(std::chrono::milliseconds(20));
	}
}

void inline reverse(int& value)
{
	unsigned char a[4] = { 0 }, b[4] = { 0 };
	memcpy_s(a, 4, &value, 4);

	b[0] = a[1];
	b[1] = a[0];
	b[2] = a[3];
	b[3] = a[2];

	value = b[0] * 256 * 256 * 256 + b[1] * 256 * 256 + b[2] * 256 + b[3];
}

void plc_comm_protocol::transfor(plc_register_info& data)
{
	int a[26] = {0};
	memcpy_s(a, sizeof(plc_register_info), &data, 4*26);

	for (int i=0; i<26; ++i)
	{
		reverse(a[i]);
	}

	memcpy_s(&data, 4 * 26, a, sizeof(plc_register_info));
}

void plc_comm_protocol::onData(uint16_t* data)
{
	memcpy_s(&data_, sizeof(plc_register_info), data, sizeof(uint16_t)*40);
	transfor(data_);

	emit update_info(data_);
}

void plc_comm_protocol::dis_connect()
{
	if (nullptr != mb_)
	{
		modbus_close(mb_);
		modbus_free(mb_);
		mb_ = nullptr;
	}
}

void plc_comm_protocol::setCamTriggerInterval(double Interval)
{
	set_value(I_tigger_interval_register, Interval);
}

void plc_comm_protocol::setCableLength(double length)
{
	set_value(l_initial_length, 1);
	set_value(l_l_cable_register, length * 1000);
	set_value(l_initial_length, 0);
}
void plc_comm_protocol::start()
{
	set_value(l_green_lamp_register, bm_plc_value_status::on);//默认绿灯亮
}

void plc_comm_protocol::stop()
{
	set_value(l_green_lamp_register, bm_plc_value_status::off);
	set_value(l_red_lamp_register, bm_plc_value_status::off);
	set_value(l_yellow_lamp_register, bm_plc_value_status::off);
}
void plc_comm_protocol::ribbon_width_alarm_off()
{
	set_value(o_ribbon_width_alarm, bm_plc_value_status::off);
}
void plc_comm_protocol::ribbon_width_alarm_on()
{
	set_value(o_ribbon_width_alarm, bm_plc_value_status::on);
	// 开启一次性定时器 进行延时关闭 ribbon_width_alarm_off
}
void plc_comm_protocol::trigger_reset_on()
{
	set_value(o_tigger_control_register, bm_plc_value_status::on);
}

void plc_comm_protocol::trigger_reset_off()
{
	set_value(o_tigger_control_register, bm_plc_value_status::off);
}

void plc_comm_protocol::trigger_switch(bm_plc_value_status status)
{
	set_value(o_switch_register, status);
}

int plc_comm_protocol::trigger_reset()
{
	set_value(o_tigger_control_register, bm_plc_value_status::off);
	QThread::msleep(30);
	set_value(o_tigger_control_register, bm_plc_value_status::on);

	trigger_flag_ = data_.tigger_codeer_register / 1000;
	return trigger_flag_;
}

int plc_comm_protocol::trigger_coder()
{
	uint16_t data[2];
	mutex_.lock();
	int ret = modbus_read_registers(mb_, o_tigger_codeer_register, 2, data);
	mutex_.unlock();
	printf("trigger_coder ret %d \r\n", ret);
	codeer_count_ = (data[0] * 256 * 256 + data[1]);
	set_value(o_tigger_codeer_register, 0);
	return codeer_count_;
}

void plc_comm_protocol::trigger_marking()
{
	set_value(l_trigger_Marking_register, bm_plc_value_status::on);
}

void plc_comm_protocol::light_control(bm_plc_value_status status)
{
	set_value(o_light_control_register, status);
}

void plc_comm_protocol::light_soud(bm_light_soud_status soud_status, bm_plc_value_status value)
{
	int light_normal_switch= bm_plc_value_status::off;
	int light_warnning_switch = bm_plc_value_status::off;
	int light_critical_switch = bm_plc_value_status::off;

	switch (soud_status)
	{
	case normal:
		light_normal_switch = value;
		light_warnning_switch = bm_plc_value_status::off;
		light_critical_switch = bm_plc_value_status::off;
		break;
	case warning:
		light_normal_switch = bm_plc_value_status::off;
		light_warnning_switch = value;
		light_critical_switch = bm_plc_value_status::off;
		break;
	case critical:
		light_normal_switch = bm_plc_value_status::off;
		light_warnning_switch = bm_plc_value_status::off;
		light_critical_switch = value;
		break;
	default:
		break;
	}
	param_.run.light_normal = l_green_lamp_register;//设地址
	param_.run.light_warnning = l_yellow_lamp_register;
	param_.run.light_critical = l_red_lamp_register;
	set_light_values(param_.run.light_normal, light_normal_switch, light_warnning_switch, light_critical_switch);
}

void plc_comm_protocol::buzzer_mode(bm_buzzer_ring_mode ring_mode_)
{
	set_value(l_buzzing_trigger_choice, ring_mode_);
}

void plc_comm_protocol::short_buzzing_time(int times_)
{
	set_value(l_short_buzzing_time_choice, times_);
}

void plc_comm_protocol::long_buzzing_time(int times_)
{
	if (times_ >= 1800)
	{
		times_ = 1800;
	}
	set_value(l_long_buzzing_trigger_choice, times_);
}

void plc_comm_protocol::short_buzzing_interval(bm_buzzer_short_ring_interval intervals_)
{
	set_value(l_short_buzzing_trigger_choice, intervals_);
}

void plc_comm_protocol::trigger_cnt()
{
	mCableMil = data_.o_cable_register / 1000;
	cable_speed_ = data_.speed_register/1000.0;
}

double plc_comm_protocol::cable_speed()
{
	return cable_speed_;
}

bool plc_comm_protocol::get_status_switch()
{
	switch_btn_status_ = data_.switch_btn_register;

	if(switch_btn_status_)set_value(I_switch_btn_register, 0);
	return switch_btn_status_;
}

double plc_comm_protocol::getCableMil()
{
	if (mCableMil >= 0.0)
	{
		return mCableMil;
	}
	else
	{
		return 0.0;
	}
}

void plc_comm_protocol::clearCableMil()
{
	set_value(l_clear_lamp_register, 1);
	QThread::sleep(1);
	set_value(l_clear_lamp_register, 0);
}
//////////////////////////////////////////////////////////////////////////////////内部接口////////////////////////////////////////////////////////////////////////////////////////
void inline registers_pase(uint16_t* dest, int value)
{
	unsigned char a[4] = { 0 };
	a[1] = value / 256 / 256 / 256;
	a[0] = value / 256 / 256;
	a[3] = value / 256;
	a[2] = value % 256;

	memcpy_s(dest, 4, &a, 4);
}
/*
数据含义
00 01此次通信事务处理标识符，一般每次通信之后将被要求加1以区别不同的通信数据报文
00 00表示协议标识符，00 00为modbus协议
00 11数据长度，用来指示接下来数据的长度，单位字节
01设备地址，用以标识连接在串行线或者网络上的远程服务端的地址。以上七个字节也被称为modbus报文头
10功能码，此时代码10为写入寄存器数据
00 00起始地址
00 04写寄存器数量
0A写入数据的字节个数
----写入的数据
*/
/*写入数据请求 MD(200)
00 01 00 00 00 0b 00 10 00 02 00 02 04 05 06 07 08
00 01 00 00 00 0b 00 10 00 04 00 02 04 05 06 07 08
00 01 00 00 00 0b 00 10 00 06 00 02 04 05 06 07 08
00 01 00 00 00 0b 00 10 00 08 00 02 04 05 06 07 08
00 01 00 00 00 0b 00 10 00 0a 00 02 04 05 06 07 08
00 01 00 00 00 0b 00 10 00 0c 00 02 04 05 06 07 08
00 01 00 00 00 0b 00 10 00 0e 00 02 04 05 06 07 08
*/
void plc_comm_protocol::set_value(int startAddr, int value)
{
	mutex_.lock();

	uint16_t data[2] = {0x00};
	registers_pase(data, value);

	int ret = modbus_write_registers(mb_, startAddr, 2, data);
	printf("set_value ret %d  \r\n", ret);
	mutex_.unlock();
}

void plc_comm_protocol::set_light_values(int startAddr, int value_normal, int value_green, int value_red)
{
	mutex_.lock();
	uint16_t data[6];
	registers_pase(data, value_normal);
	registers_pase(&data[2], value_green);
	registers_pase(&data[4], value_red);
	int ret = modbus_write_registers(mb_, startAddr, 6, data);
	mutex_.unlock();
	printf("set_value ret %d  \r\n", ret);
}
