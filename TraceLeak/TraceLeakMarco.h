/*
步骤：
1. 将TraceLeakMarco.h、TraceLeak.h、TraceLeak.cpp引入工程中。
2. 在需要检测的内存泄露的文件中#include "TraceLeakMarco.h"

注意：
检测针对全局的new和delete、new[]和delete[]，无法检测自定义的。

API：
void print();//打印未释放的内存信息
void output(const char* filename);//将未释放的内存信息输出到文件中

*/
#ifndef _TRACE_LEAK_MARCO_H_
#define _TRACE_LEAK_MARCO_H_

#include "TraceLeak.h"
#define new new(__FILE__, __LINE__)

#endif