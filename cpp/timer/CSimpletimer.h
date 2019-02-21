#pragma once

#include <sys/time.h>
#include <signal.h>
#include <iostream>

class CSimpleTimer {
public:
	CSimpleTimer();
	CSimpleTimer(void(*timerproc)(int, siginfo_t *, void *),const int interval);
	int SetTimerProc(void (*timerproc)(int, siginfo_t *, void *));
	int Timer(const int interval);
	~CSimpleTimer();
protected:
	struct sigaction msa_action;	//用于设置时间处理函数 (该结构体，下面有介绍)
	itimerval mit_value;			//用于设置定时器的时间间隔 (该结构体，下面有介绍)
	void Initialize();				//初始化成员变量，设置默认值
};


/*  关于该程序中使用的信号函数等做些讲解
	sigaction 函数在<signal.h>中
	sigaction 结构体如下：
	struct sigaction {
		void (*sa_handler) (int);		//SIG_DFL, SIG_IGN或者指向函数的指针
		sigset_t sa_mask;				//处理程序要阻塞的信号
		int sa_flags;					//标志和选项
		void(*sa_sigaction)(int, siginfo_t*, void *);		//信号处理程序
	};

	关于上面的sa_handler和sa_sigaction的函数原型如下
	void sa_handler(int signo);										//signo是被捕获的信号
	void sa_sigaction(int signo, siginfo_t * info, void context);	//info是siginfo_t结构体变量
	struct siginfo_t {
		int si_signo;				//信号码
		int si_code;				//引发信号的原因
		union sigval {
			int sival_int;
			void * sival_prt;
		} si_value;
	};

	itimerval 结构体包含两个成员，具体如下：
	struct itimerval {
		struct timeval it_value;			//到下一次到期为止剩下的时间
		struct timeval it_interval;			//重新装载定时器的值
	};
	timeval也是一个结构体，如下：
	struct timeval {
		time_t tv_sec;						//秒
		time_t tv_usec;						//微妙
	};
*/
