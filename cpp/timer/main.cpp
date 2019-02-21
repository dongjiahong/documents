#include "CSimpletimer.h"
#include <stdlib.h>		//atoi
#include <unistd.h>		//pause,sleep
#include <iostream>

using namespace std;

// 事件/信号 处理函数，全局函数
void TimerProcess(int sig, siginfo_t * info, void *context) {
	time_t lt	=	time(NULL);
	cout << "TimerProcess received a signal:" << sig << "  at" << lt << endl;
}

int main(int argc, char *argv[]) {	// `./main 5` 每隔5秒执行一次
	//命令行参数判断
	if(argc < 2) {
		cout << "usage:TestSimpleTimer, argc:"<<argc << endl;
		return 0;
	}

	//创建一个简单定时器实例
	CSimpleTimer timer;
	//设置事件/信号 处理程序
	if (timer.SetTimerProc(TimerProcess) < 0) {
		cout << "error:SetTimerProc" << endl;
	}
	//启动定时器
	if(timer.Timer(atoi(argv[1])) < 0) {
		cout << "Error:Timer" << endl;
	}
	//for(;;) {			//跟下面的while(1) 一样
	while(1) {
		cout << "For ..." << endl;
		pause();	//等待信号，这里是等待时间的间隔信号，
	}

	return 0;
}
