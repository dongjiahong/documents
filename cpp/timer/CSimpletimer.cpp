#include "CSimpletimer.h"

CSimpleTimer::CSimpleTimer() {
	Initialize();
}

//该类使用sa_sigaction做处理函数，所以下面的函数指针类型跟sa_sigaction对应
CSimpleTimer::CSimpleTimer(void (*timerproc)(int, siginfo_t *, void *),const int interval) {
	Initialize();
	SetTimerProc(timerproc);
	Timer(interval);
}

void CSimpleTimer::Initialize() {
	//初始化msa_action成员变量
	msa_action.sa_flags		=	SA_SIGINFO;		//使用sa_sigaction信号处理程序(sa_sigaction函数的原型见CSimpleTimer.h中有介绍)
	//sigemptyset用来将参数信号集初始化并清空
	sigemptyset(&msa_action.sa_mask);			//出错时返回-1,此处未进行错误判断

	//由于此时还不知道sa_sigaction将会是什么值，所以初始化为null

	//sa_sigaction值通过SetTimerProc方法来设置 (sa_sigaction是函数指针)
	msa_action.sa_sigaction	=	NULL;

	//此时不知道使用者将使用的定时器时间间隔，所以初始化为0

	//mit_value值通过SetInterval方法来设置
	mit_value.it_interval.tv_sec	=	0;						//单位 秒
	mit_value.it_interval.tv_usec	=	0;						//单位 微妙
	mit_value.it_interval			=	mit_value.it_interval;	//重新装载定时器的值
}

//用于安装逻辑处理函数
int CSimpleTimer::SetTimerProc(void (*timerproc)(int, siginfo_t *, void *)) {
	msa_action.sa_sigaction		=	timerproc;					//timerproc是参数，是函数指针
	return sigaction(SIGALRM, &msa_action, NULL);
}

int CSimpleTimer::Timer(const int interval) {					//函数，参数为时间间隔
	mit_value.it_interval.tv_sec	=	interval;				//该程序只要秒级别的就行
	mit_value.it_interval.tv_usec	=	0;
	mit_value.it_value				=	mit_value.it_interval;

	return setitimer(ITIMER_REAL, &mit_value, NULL);			//setitimer函数见下面注解
}

CSimpleTimer::~CSimpleTimer() {
	Timer(0);
}


/*  关于该程序中使用的信号函数等做些讲解
	POSIX:XSI提供了三种用户间隔定时器
	1、ITIMER_REAL:		真实时间定时器，在定时器到期时产生 SIGALRM 信号;
	2、ITIMER_VIRTUAL： 虚拟时间定时器，即进程使用cpu时间，定时器到期时产生SIGVTALRM 信号
	3、ITIMER_PROF:		根据虚拟时间和进程的系统时间，定时器到期时产生SIGPROF 信号

	sigemptyset函数原型：int sigemptyset(sigset_t *set); 在头文件<signal.h>
			   函数说明: sigemptyset()用来将参数set信号集合初始化并清空
			   返回值:	 成功返回0,如果有错误返回-1

	setitimer函数是linux的api函数而不是c函数。
			函数原型：	int setitimer(int which, const struct itimerval *value, struct ittimerval *ovalue);
			函数说明：	which 为定时器类型，支持三种类型上面有介绍,该程序使用真实时间ITIMER_REAL。
						value 是itimerval的结构体，就是时间间隔
						ovalue可不做处理
*/
