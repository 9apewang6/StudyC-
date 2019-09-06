#pragma once
#include "boming_base_ptr.h"
#include <QString>
struct bmImageR
{

	unsigned char* data;
	int width;
	int height;
	int channel;
	int nDataSize;
	int format;
	bmImageR()
	{
		data = nullptr;
		width = 0;
		height = 0;
		channel = 0;
		nDataSize = 0;
		format = 0;
	}
};
class image_informations
{
public:
	image_informations()
	{
		 data = nullptr; image = make_shared<bmImageR>(); image->data = NULL; 
		filepath = "";
	}
	~image_informations()
	{
		if (nullptr != image->data)
		{
			delete[] image->data; image->data = NULL;
		}
	}
	void create_image_buff(long size)
	{
		size_ = size;
		data = new unsigned char[size];
		image->data = data;
	}

public:
	QString index;
	shared_ptr<bmImageR> image;
	QString time;
	QString filepath;
	QString image_name;
	QString area_alarm_image_name;
	QString user_name;
	long size_;
	unsigned char* data;
};
PTR_DEF(image_informations)