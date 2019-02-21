#include <db_cxx.h>
#include "log.h"
#include <fstream>
#include "tools.h"
using namespace std;
using namespace superman;
void Log::printLogInfo(initializer_list<string> info) {
    string cache;
    for(const auto& ele : info) {
        cache += ele;
    }
    fstream wf;
    wf.open(log_file_.c_str(), ios::out);
    if (!wf.is_open()) {
        cout << "Log::printLogInfo --> 文件:" << log_file_ << "打开失败!" << endl;
        return;
    }
    const size_t str_size = cache.size();
    wf.write(cache.c_str(),str_size);
    if (wf.is_open()) {
        cout << "Log::printLogInfo --> 文件:" << log_file_ << "将关闭" << endl;
        wf.close();
    }
}

void Log::setLogFileName () {
    log_file_ += log_path_;
    log_file_ += mTime.GetLocalYMD();
    log_file_ += mTime.GetLocalTimeHour();
    log_file_ += mTime.GetLocalTimeMinute();
}
