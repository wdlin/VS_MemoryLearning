/*
���裺
1. ��TraceLeakMarco.h��TraceLeak.h��TraceLeak.cpp���빤���С�
2. ����Ҫ�����ڴ�й¶���ļ���#include "TraceLeakMarco.h"

ע�⣺
������ȫ�ֵ�new��delete��new[]��delete[]���޷�����Զ���ġ�

API��
void print();//��ӡδ�ͷŵ��ڴ���Ϣ
void output(const char* filename);//��δ�ͷŵ��ڴ���Ϣ������ļ���

*/
#ifndef _TRACE_LEAK_MARCO_H_
#define _TRACE_LEAK_MARCO_H_

#include "TraceLeak.h"
#define new new(__FILE__, __LINE__)

#endif