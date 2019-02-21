#include <sys/inotify.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
//#include <sys/types.h>

/*		inotify的简单使用步骤
	1、使用inotify_init()创建inotify实例
	2、使用inotify_add_watch()添加要监控的路径
	3、使用read()能确定inotify实例存在，其返回值我们能确定是那种变化发生
	4、inotigy_rm_watch()能删除监控
*/

#define EVENT_BUFSIZE 4096

int main(int argc, char *argv[]) {
	int len = 0,i=0;
	int fd, dir_wd;
	char buf[EVENT_BUFSIZE], *cur = buf, *end;

	//创建inotify实例
	fd = inotify_init();
	if (fd < 0) {
		std::cout<< "inotify_init error!!" << std::endl;
	}

	//添加要监控的路径和监控的类型
	dir_wd = inotify_add_watch(fd, "./lib/log", IN_DELETE|IN_MODIFY);

	//读取一个或者多个事件信息的缓存
	len = read(fd, buf, EVENT_BUF_LEN);
	if (len < 0) {
		std::cout << "read error!!" std::endl;
	}

	while (i < len) {
		struct inotify_event *event = (struct inotify_event *) &buf[i];
		if (event->len) {
			if (event->mask & IN_MODIFY) {
				std::cout << "file is modifing!" << std::endl;
			} else if{event->mask & IN_DELETE} {
				std::cout << "file is deleted!" << std::endl;
			}
		}
		i += sizeof(struct inotify_event) + event->len;
	}

	//删除监控
	inotify_rm_watch(fd, dir_wd);
	//关闭监控实例
	close(fd);
}
