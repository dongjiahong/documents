#!/bin/bash

# 补log
# bp_click--->     click_val_2015_10_13_17_00.log.gz
# bp_pv------>     pv_val_2015_10_13_17_00.log.gz
# charge_log->     settle_online_201510131700_rec.txt
# pv_charge_log->  cpm_settle_online_201510131700_rec.txt.gz
# stat_log--->     stat_val_2015_10_13_17_00.log.gz
# 一次只能补一个文件夹,即补一个小时的
HOUR=$1

PATH_TIME="2015/10/13/${HOUR}/"
NAME_TIME="2015_10_13_${HOUR}"
NAME_TIME_CHARGE="20151013${HOUR}"

###########---------文件名----------##############
CLICK_NAME="click_val_${NAME_TIME}_"
PV_NAME="pv_val_${NAME_TIME}_"
CHARGE_NAME="settle_online_${NAME_TIME_CHARGE}"
PV_CHARGE_NAME="cpm_settle_online_${NAME_TIME_CHARGE}"
STAT_NAME="stat_val_${NAME_TIME}_"

############--------------路径------------#########
PATH_CLICK="../bp_click/${PATH_TIME}"
PATH_PV="../bp_pv/${PATH_TIME}"
PATH_CHARGE="../charge_log/${PATH_TIME}"
PATH_PV_CHARGE="../pv_charge_log/${PATH_TIME}"
PATH_STAT="../stat_log/${PATH_TIME}"

#########-----------判断文件夹是否存在------########
for dir in ${PATH_CLICK} ${PATH_PV} ${PATH_CHARGE} ${PATH_PV_CHARGE} ${PATH_STAT}
do
	if [ ! -d "${dir}" ]
	then
		echo "${dir} is not exist"
		mkdir ${dir}
		echo "mkdir ${dir}"
	fi
done

######-----判断文件是否存在,不存补充空文件-----###

for i in $(seq 0 59)
do
	if [ $i -le 9 ]
	then
		i=0${i}
	fi
	CLICK_FILE_NAME=${CLICK_NAME}${i}.log.gz
	PV_FILE_NAME=${PV_NAME}${i}.log.gz
	CHARGE_FILE_NAME=${CHARGE_NAME}${i}_rec.txt
	PV_CHARGE_FILE_NAME=${PV_CHARGE_NAME}${i}_rec.txt.gz
	STAT_FILE_NAME=${STAT_NAME}${i}.log.gz

	if [ ! -f "${PATH_CLICK}${CLICK_FILE_NAME}" ]
	then
		cp ./NULL_LOG/click_val.log.gz ${PATH_CLICK}${CLICK_FILE_NAME}
	fi

	if [ ! -f "${PATH_PV}${PV_FILE_NAME}" ]
	then
		cp ./NULL_LOG/pv_val.log.gz ${PATH_PV}${PV_FILE_NAME}
	fi

	if [ ! -f "${PATH_CHARGE}${CHARGE_FILE_NAME}" ]
	then
		cp ./NULL_LOG/settle_online.txt ${PATH_CHARGE}${CHARGE_FILE_NAME}
	fi

	if [ ! -f "${PATH_PV_CHARGE}${PV_CHARGE_FILE_NAME}" ]
	then
		cp ./NULL_LOG/cpm_settle_online.txt.gz ${PATH_PV_CHARGE}${PV_CHARGE_FILE_NAME}
	fi

	if [ ! -f "${PATH_STAT}${STAT_FILE_NAME}" ]
	then
		cp ./NULL_LOG/stat_val.log.gz ${PATH_STAT}${STAT_FILE_NAME}
	fi

done


