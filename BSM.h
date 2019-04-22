#ifndef _BSM_H_
#define _BSM_H_

/* 用于模拟BSM消息 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


//BSM消息
typedef struct BSM {
	int id; 			//id
	int vehicleID; 		//车辆ID
	double latitude;	//车辆纬度
	double longitude;	//车辆经度
	long vehicleClass;	//车辆状态（分类）
} tBSM;

#endif
