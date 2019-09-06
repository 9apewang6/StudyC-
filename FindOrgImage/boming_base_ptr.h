/*	File name: boming_base_ptr.h
 *
 *	list thread safe implementation
 *
 *	CCopyright (C) boming
 *	
 *	Created @  ylshan 2018-3-23
 */
 
#pragma once
#include<memory>
#include<iostream>

using namespace std;
//struct声明
#define PTR_DEF_I(interf) struct interf; \
	typedef shared_ptr<interf> interf##_ptr; \
	typedef weak_ptr<interf> interf##_weak_ptr; \
	typedef auto_ptr<interf> interf##_auto_ptr; \
	typedef unique_ptr<interf> interf##_unique_ptr; 
	
//struct声明
#define PTR_DEF(cls) class cls; \
	typedef shared_ptr<cls> cls##_ptr; \
	typedef weak_ptr<cls> cls##_weak_ptr; \
	typedef auto_ptr<cls> cls##_auto_ptr; \
	typedef unique_ptr<cls> cls##_unique_ptr; 
	
	
	// 用法如下：
	//interf_ptr td;
	//td = make_shared<interf>();