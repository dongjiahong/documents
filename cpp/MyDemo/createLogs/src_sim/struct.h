#pragma once
#include <iostream>
using namespace std;

//这里是配置的各种结构体
// " adgroup|begin|end|num|flag "
typedef struct controlConfig{
    string platform;
    long adgroup;
    string beginTime;
    string endTime;
    int logNum;
    string logType;
} CCFIG;

//这里是数据库的链接格式
typedef struct db_info_machine{
    string db_name;
    string db_host;
    string db_user;
    string db_paswd;
}DBINFO;

//这里是广告的信息log格式
typedef struct adinfo{
    long adgroup_id;
    long member_id;
    long campaign_id;
    int max_price;
    int trans_type;
}ADINFO;
//这里是各种log的格式
typedef struct reqBd{

}REQBD;

//曝光日志log格式
enum pvlog{
    server_name,//服务器    AdEngineX0@10.3.21.120
    platform,   //平台      MZ
    bid,        //bid       auction-server-1.2-sandbox-1-t12-1393483649-0-666
    tid,        //tid       tvnoV0ZDcpn0
    jebeid,     //jebeid    a27f5382-82e5-4c06-a201-7179d7d09764
    id,         //id        2
    groupid,    //groupid   10001336480005
    ip,         //ip        12,23.110.23
    referer,    //refer     http://testweb.x.cn.miaozhen.com?MZADX&u=www.baidu.com 
    price,      //竞价      0.0123
    stage,      //stage     4
    gender,     //性别      1
    age,        //年龄      27
    school,     //学校      0
    major,      //专业      0
    grade,      //学历      0
    home_area,  //家庭地址  0086000000000000
    current_area,//当前地址 0086000000000000
    ip_area,    //ip地址    0086110000000000
    work_place, //工作地点  
    zone_id,    //区域地址  800000000000
    trans_type, //          20
    member_id,  //memberid  100000050532
    campaign_id,//campaign  10000133648
    bid_unit_id,//uint_id   10000133648000500004
    display_type,//展示类型 0
    member_category,//类别  2
    member_industry,//行业  105
    max_price,  //广告主价格0.150000
    tag_id,     //广告位    901234123545
    dateTime    //时间      2014-02-27 14:47:29
};
