#ifndef _BSM_H_
#define _BSM_H_

/* ����ģ��BSM��Ϣ */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


//BSM��Ϣ
typedef struct BSM {
	int id; 			//id
	int vehicleID; 		//����ID
	double latitude;	//����γ��
	double longitude;	//��������
	long vehicleClass;	//����״̬�����ࣩ
} tBSM;

#endif
