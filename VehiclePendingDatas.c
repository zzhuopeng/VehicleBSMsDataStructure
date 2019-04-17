#include "VehiclePendingDatas.h"

/**************���ȼ�������ز���***************/

/**
@ brief  ��ʼ�� ���ȼ����У��ѣ�
@ param	 capacity ���ȼ����г�ʼ������
@ return PriorityQueue ���ȼ����� ����
*/
PriorityQueue PQInitialize(int capacity)
{
	PriorityQueue H;
	if(capacity < PQ_MIN_CAPACITY) {
		printf("PQInitialize: Priority Queue size is too small\n");
		return NULL;
	}
	if(capacity > PQ_MAX_CAPACITY) {
		printf("PQInitialize: Priority Queue size is too large\n");
		return NULL;
	}
	//PQ����ѿռ�
	H = calloc(1, sizeof(tHeapStruct));
	if(NULL == H) {
		printf("PQInitialize: calloc for H failed\n");
		return NULL;
	}
	//�������ѿռ�(�����0��Ԫ����sentinel��ǽڵ㣬������capacity��size)
	H->BSMs = calloc(capacity + 1, sizeof(tBSM));
	if(NULL == H->BSMs) {
		printf("PQInitialize: calloc for H->BSMs failed\n");
		return NULL;
	}
	H->Capacity = capacity;
	H->Size = 0;
//	H->BSMs[0] = {0};
	return H;
}

/**
@ brief  ���� ���ȼ����У��ѣ�
@ param	 PQhead ���ȼ����� ����
@ return 0��ʾʧ�ܣ�1��ʾ�ɹ�
*/
int PQDestroy(PriorityQueue PQhead)
{
	if(NULL == PQhead) {
		printf("PQDestroy: need to create Priority Queue first\n");
		return 0;
	}
	free(PQhead);
	free(PQhead->BSMs);
	return 1;
}

/**
@ brief  �ÿ� ���ȼ����У��ѣ�
@ param	 PQhead ���ȼ����� ����
@ return 0��ʾʧ�ܣ�1��ʾ�ɹ�
*/
int PQMakeEmpty(PriorityQueue PQhead)
{
	if(NULL == PQhead) {
		printf("PQMakeEmpty: need to create Priority Queue first\n");
		return 0;
	}
	PQhead->Size = 0;
	return 1;
}

/**
@ brief  ��ӣ����복��BSM��Ϣ
@ param	 PQhead ���ȼ����� ���ף�bsm ��ӵ�BSM��Ϣ
@ return 0��ʾʧ�ܣ�1��ʾ�ɹ�
*/
int PQInsertBSM(PriorityQueue PQhead, tBSM bsm)
{
	tBSM* biggerBSM = NULL;
	int biggerCapacity = 0;
	int i;
	//��ʱ���ڴ洢��ɾ����maxBSM
	tBSM* maxBSM = calloc(1, sizeof(tBSM));
	if(NULL == maxBSM) {
		printf("PQInsertBSM: maxBSM calloc() failed\n");
		return 0;
	}

	//�ﵽ�����������ɾ�������ݡ���չ�Ĵ�С=ԭ��С*��������
	if(IsPQFull(PQhead)) {

		biggerCapacity = (int)PQhead->Size*(1+EXPENDFACTOR);//ǿתΪint

		//���������������������ֻ��ͨ��ɾ�����ȼ���ͣ��ؼ�ֵ���BSM���ڳ��ռ�
		if(biggerCapacity > PQ_MAX_CAPACITY) {
			printf("PQInsertBSM: biggerCapacity is > PQ_MAX_CAPACITY, need to PQDeleteMaxBSM()\n");
			if(0 == PQDeleteMaxBSM(PQhead, maxBSM)) {
				printf("PQInsertBSM: PQDeleteMaxBSM() failed\n\n");
				return 0;
			}
		}
		//δ��������������������������
		if(biggerCapacity <= PQ_MAX_CAPACITY) {
			biggerBSM = realloc(PQhead->BSMs, (biggerCapacity+1)*sizeof(tBSM));//��1��Ϊ���ڱ��ڵ�
			if(NULL == biggerBSM) {  //����ʧ�ܣ�ֻ��ͨ��ɾ�����ȼ���ͣ��ؼ�ֵ���BSM���ڳ��ռ�
				printf("PQInsertBSM: biggerBSM realloc() failed, need to PQDeleteMaxBSM()\n");
				if(0 == PQDeleteMaxBSM(PQhead, maxBSM)) {
					printf("PQInsertBSM: PQDeleteMaxBSM() failed\n\n");
					return 0;
				}
			} else { //���ݳɹ�
				PQhead->BSMs = biggerBSM;
				PQhead->Capacity = biggerCapacity;
			}
		}
	}
	//�ǵ��ͷ��ڴ�
	free(maxBSM);
	//����BSM��Ϣ������������ˣ�
	for(i=++PQhead->Size; PQComputeKey(PQhead->BSMs[i/2])>PQComputeKey(bsm) && i<=1; i/=2) {
		PQhead->BSMs[i] = PQhead->BSMs[i/2];//�����ڵ������ƶ�
	}
	PQhead->BSMs[i] = bsm;
	return 1;
}

/**
@ brief  ����BSM��Ϣ�����ȼ���keyԽС�����ȼ�Խ�ߣ�
@ param	 PQhead ���ȼ����� ����
@ return 0��ʾʧ�ܣ�1��ʾ�ɹ�
*/
double PQComputeKey(tBSM bsm)
{
	//HV��BSM��Ϣ������ģ��������ȼ�
	tBSM HV_BSM;
	HV_BSM.id = 0;
	HV_BSM.latitude =  0.0;
	HV_BSM.longitude = 0.0;
	HV_BSM.vehicleClass = 10000;
	HV_BSM.vehicleID = 0;

	//�����׼���ٳ���״̬��״̬��ԽС�����ȼ�Խ�ߣ�����״̬�����
	//			��RV����HV�ľ��루RV����HVԽ�������ȼ�Խ�ߣ�

	//ŷʽ���룬��Ҫƽ�����������ϴ��ݲ��ã�
//	return pow((bsm.latitude-HV_BSM->latitude), 2)
//	       + pow((bsm.longitude-HV_BSM->longitude), 2)
//	       + bsm.vehicleClass;
	//�����پ���
	return (bsm.latitude-HV_BSM.latitude)
	       + (bsm.longitude-HV_BSM.longitude)
	       + bsm.vehicleClass;
}

/**
@ brief  ���ӣ�ɾ�����ȼ���ߣ��ؼ�����С��BSM��Ϣ
@ param	 PQhead ���ȼ����� ����, topBSM ���ȼ���ߵ�BSM��Ϣָ��
@ return 0��ʾʧ�ܣ�1��ʾ�ɹ�
*/
int PQDeleteMinBSM(PriorityQueue PQhead, tBSM* topBSM)
{
	int i, Child;
	tBSM LastBSM;

	if(IsPQEmpty(PQhead)) {
		printf("PQDeleteMinBSM: PQhead is empty\n");
		return 0;
	}
	//�ȼ�¼����
	*topBSM = PQhead->BSMs[1];
	LastBSM = PQhead->BSMs[PQhead->Size];
	//������һ���ڵ㣨����ֱ����insertʱ���ǣ���
	memset(PQhead->BSMs+PQhead->Size, 0, sizeof(tBSM));
	PQhead->Size--;
	//�������һ���ڵ㣬���ɸ��ڵ㣩����
	for(i=1; i*2<=PQhead->Size; i=Child) {
		//�Ƚ������ӽڵ�Ĵ�С,��С���ӽڵ�
		Child = i*2;
		if(Child!=PQhead->Size &&
		   PQComputeKey(PQhead->BSMs[Child]) > PQComputeKey(PQhead->BSMs[Child+1])) {
			Child++;
		}
		//����
		if(PQComputeKey(LastBSM) > PQComputeKey(PQhead->BSMs[Child])) {
			PQhead->BSMs[i] = PQhead->BSMs[Child];
		} else {
			break;//��������forѭ��
		}
	}
	//���ýڵ�ŵ�����λ��
	PQhead->BSMs[i] = LastBSM;
	return 1;
}

/**
@ brief  ��ѯ�����ȼ���ߣ��ؼ�����С��BSM��Ϣ
@ param	 PQhead ���ȼ����� ����, topBSM ���ȼ���ߵ�BSM��Ϣָ��
@ return 0��ʾʧ�ܣ�1��ʾ�ɹ�
*/
int PQQueryMinBSM(PriorityQueue PQhead, tBSM* topBSM)
{
	if(IsPQEmpty(PQhead)) {
		printf("PQQueryMinBSM: PQhead is empty\n");
		return 0;
	}
	*topBSM = PQhead->BSMs[1];
	return 1;
}

/**
@ brief  ���ӣ�ɾ�����ȼ���ͣ��ؼ������BSM��Ϣ {��������ʵ��}
@ param	 PQhead ���ȼ����� ����, bottomBSM ���ȼ���͵�BSM��Ϣָ��
@ return 0��ʾʧ�ܣ�1��ʾ�ɹ�
*/
int PQDeleteMaxBSM(PriorityQueue PQhead, tBSM* bottomBSM)
{
	int i, MaxIndex;
	tBSM MaxBSM, LastBSM;

	if(IsPQEmpty(PQhead)) {
		printf("PQDeleteMaxBSM: PQhead is empty\n");
		return 0;
	}
	//�ҵ����ȼ���͵�BSM,����¼�±�MaxIndex
	i = (int)PQhead->Size/2+1;
	MaxIndex = i;
	MaxBSM = PQhead->BSMs[i];
	for(i=i+1; i<=PQhead->Size; i++) {
		if(PQComputeKey(PQhead->BSMs[i]) > PQComputeKey(MaxBSM)) {
			MaxBSM = PQhead->BSMs[i];
			MaxIndex = i;
		}
	}
	*bottomBSM = MaxBSM;
	//�ȼ�¼���һ���ڵ㣬�������MaxBSMɾ����Ŀ�ȱ
	LastBSM = PQhead->BSMs[PQhead->Size];
	//������һ���ڵ㣨����ֱ����insertʱ���ǣ���
	memset(PQhead->BSMs+PQhead->Size, 0, sizeof(tBSM));
	PQhead->Size--;
	//(�����һ���ڵ�LastBSM����ԭ��MaxBSMλ��)����
	for(i=MaxIndex; PQComputeKey(PQhead->BSMs[i/2])>PQComputeKey(LastBSM) && i<=1; i/=2) {
		PQhead->BSMs[i] = PQhead->BSMs[i/2];//�����ڵ������ƶ�
	}
	//���ýڵ�ŵ�����λ��
	PQhead->BSMs[i] = LastBSM;

	return 1;
}

/**
@ brief  ��ѯ�����ȼ���ͣ��ؼ������BSM��Ϣ {��������ʵ��}
@ param	 PQhead ���ȼ����� ����, bottomBSM ���ȼ���͵�BSM��Ϣָ��
@ return 0��ʾʧ�ܣ�1��ʾ�ɹ�
*/
int PQQueryMaxBSM(PriorityQueue PQhead, tBSM* bottomBSM)
{
	int i;
	tBSM MaxBSM;

	if(IsPQEmpty(PQhead)) {
		printf("PQQueryMaxBSM: PQhead is empty\n");
		return 0;
	}

	i = (int)PQhead->Size/2+1;
	MaxBSM = PQhead->BSMs[i];
	//���ֵһ������Ҷ�ϣ�Ҷ�ӽڵ㷶ΧΪ(n/2+1~n),�±��1��ʼ
	for(i=i+1; i<=PQhead->Size; i++) {
		if(PQComputeKey(PQhead->BSMs[i]) > PQComputeKey(MaxBSM)) {
			MaxBSM = PQhead->BSMs[i];
		}
	}
	*bottomBSM = MaxBSM;
	return 1;
}

/**
@ brief  ����HV��BSM��Ϣ����Ҫ�����ȼ����н���������
		Ϊ�˱���PQhead��Ӧ�ѿռ��Ƶ�����١��ؽ�������ֻ�ı�BSMs��Ӧ��������ݣ�ʵ��������
@ param	 PQhead ���ȼ����� ����
@ return 0��ʾʧ�ܣ�1��ʾ�ɹ�
*/
int PQReSort(PriorityQueue PQhead)
{
	int i, size;
	if(IsPQEmpty(PQhead)) {
		printf("PQReSort: PQhead is empty\n");
		return 0;
	}
	//������飨���������գ�
	size = PQhead->Size;
	if(0 == PQMakeEmpty(PQhead)) {
		printf("PQReSort: PQMakeEmpty() failded\n");
		return 0;
	}
	//��ԭ������Ԫ�أ�ֱ�Ӵ��·Ž���պ��PQhead(��1��n��һ��һ�����)
	//�����Ͳ���������BSMs����ȫ������������Ȼ��һ��������
	for(i=1; i<=size; i++) {
		PQInsertBSM(PQhead, PQhead->BSMs[i]);
	}
	return 1;
}

/**
@ brief  �ж����ȼ������Ƿ�Ϊ��
@ param	 PQhead ���ȼ����� ����
@ return 0��ʾΪ�գ�1��ʾ�ǿ�
*/
int IsPQEmpty(PriorityQueue PQhead)
{
	return 0 == PQhead->Size;
}

/**
@ brief  �ж����ȼ������Ƿ�����
@ param	 PQhead ���ȼ����� ����
@ return 0��ʾΪ�գ�1��ʾ�ǿ�
*/
int IsPQFull(PriorityQueue PQhead)
{
	return PQhead->Capacity == PQhead->Size;
}
