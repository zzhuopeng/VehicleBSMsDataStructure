#ifndef _VehiclePendingDatas_H_
#define _VehiclePendingDatas_H_

/**
 * ˵������������������VPDs(Vehicle Pending Datas)�洢�ṹ��
 		������������������ͨ��BSM�洢������֮������ͨ��PriorityQueue�洢��
 		������򣺳���״̬+����֮�����
 * ע�⣺��PriorityQueue�У���������Ϣ���ܱ���̫�࣬
 		����ÿ�θ���HV��BSM�󣬶���Ҫ�ķѽ϶�ʱ��������
 		 ��PriorityQueue�������������ܾ�����������������Ҫ����PQDeleteMaxBSM()�� �ȽϺ�ʱ
 	��չ�� 
	 	 ���ظ���BSM��Ϣ����Ҫ��PriorityQueue����ȥ�� 
 */

#include <math.h>
#include "VehicleHistoryDatas.h"

/****�궨��****/
#define PQ_MIN_CAPACITY 	8	//HV��Χ������������Ϣ������������С��������
#define PQ_MAX_CAPACITY 	64	//HV��Χ������������Ϣ�������������������
#define PQ_EXPENDFACTOR		0.5 //�������ӣ���չ�Ĵ�С=ԭ��С*��������


/****�ṹ�嶨��****/
typedef struct HeapStruct* PriorityQueue;

//�ѽṹ�壨�������飩
typedef struct HeapStruct {
	int Capacity; 	//������(�Զ���)
	int Size; 		//��ǰ�Ѵ�С
	tBSM* BSMs;		//BSM����
} tHeapStruct;


/****���ȼ�������ز�������С�ѣ�****/
PriorityQueue PQInitialize(int capacity);					//��ʼ�� ���ȼ����У��ѣ�
int PQDestroy(PriorityQueue PQhead);						//���� ���ȼ����У��ѣ�
int PQMakeEmpty(PriorityQueue PQhead);						//��� ���ȼ����У��ѣ�
int PQInsertBSM(PriorityQueue PQhead, tBSM bsm);			//��ӣ����복��BSM��Ϣ

double PQComputeKey(tBSM bsm);								//����BSM��Ϣ�����ȼ���keyԽС�����ȼ�Խ�ߣ�
int PQDeleteMinBSM(PriorityQueue PQhead, tBSM* topBSM); 	//���ӣ�ɾ�����ȼ���ߣ��ؼ�����С��BSM��Ϣ
int PQQueryMinBSM(PriorityQueue PQhead, tBSM* topBSM);		//��ѯ�����ȼ���ߣ��ؼ�����С��BSM��Ϣ
//��������ʵ�֣��ҹؼ������
int PQDeleteMaxBSM(PriorityQueue PQhead, tBSM* bottomBSM); 	//���ӣ�ɾ�����ȼ���ͣ��ؼ������BSM��Ϣ
int PQQueryMaxBSM(PriorityQueue PQhead, tBSM* bottomBSM);	//��ѯ�����ȼ���ͣ��ؼ������BSM��Ϣ
//��������С�ѣ�
int PQReSort(PriorityQueue PQhead);							//����HV��BSM��Ϣ����Ҫ�����ȼ����н���������
int IsPQEmpty(PriorityQueue PQhead); 						//�ж����ȼ������Ƿ�Ϊ��
int IsPQFull(PriorityQueue PQhead);							//�ж����ȼ������Ƿ�����


#endif
