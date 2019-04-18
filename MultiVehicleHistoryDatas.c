#include "MultiVehicleHistoryDatas.h"

/**
@ brief  ��ʼ��HashMap
@ param	 size HashMapͰ�����С 
@ return ��ʼ�����HashMap
*/
HashMap HashMapInitialize(int size)
{
	HashMap H;
	int i;
	
	if(size < HASHMAP_BUCKET_MIN_CAPACITY) {
		printf("HashMapInitialize: HashMap size is too small\n");
		return NULL;
	}
	if(size > HASHMAP_BUCKET_MAX_CAPACITY) {
		printf("HashMapInitialize: HashMap size is too large\n");
		return NULL;
	}
	//HashMap����ռ�
	H = calloc(1, sizeof(tHashMapStruct));
	if(NULL == H) {
		printf("HashMapInitialize: calloc for H failed\n");
		return NULL;
	}
	H->MapSize = NextPrime(size);
	//�������ռ�
	H->bucket = calloc(H->MapSize, sizeof(EntryList));
	if(NULL == H->bucket) {
		printf("HashMapInitialize: calloc for H->bucket failed\n");
		return NULL;
	}
	//�������ռ�
	for(i=0; i<H->MapSize; i++) {
		H->bucket[i] = calloc(1, sizeof(tListNode));
		if(NULL == H->bucket[i]) {
			printf("HashMapInitialize: calloc for H->bucket[i] failed\n");
			return NULL;
		}
		H->bucket[i]->Next = NULL;
	}
	return H;
}

/**
@ brief  ��ȡ>N>10����С������static������ 
@ param	 N �����½� 
@ return �������� 
*/
static int NextPrime(int N)
{
    int i;

    if( N % 2 == 0 )
        N++;
    for( ; ; N += 2 )
    {
        for( i = 3; i * i <= N; i += 2 )
            if( N % i == 0 )
                goto ContOuter;
        return N;
    	ContOuter: ;
    }
}

/**
@ brief  ����HashMap
@ param	 H ��Ҫ���ٵ�HashMap 
@ return 0��ʾΪ�գ�1��ʾ�ǿ�
*/
int HashMapDestroy(HashMap H)
{
	int i;
	
	if(NULL == H) {
		printf("HashMapDestroy: need to create HashMap first\n");
		return 0;
	}
	for(i=0; i<H->MapSize; i++) {
		EntryList E = H->bucket[i];
		ListNode* tmp;
		
		while(NULL != E) {
			tmp = E->Next;
			//�ǵð�Stack�Ŀռ�ҲҪ�ͷ���
			DestroyStack(E->singleVHDs);
			free(E);
			E = tmp;
		}
	}

    free(H->bucket);
    free(H);
    return 1; 
}


/**
@ brief  ��ѯKey(vehiceID)��Ӧ��ListNode(Stack)
@ param	 vehicleID ����ID��H HashMap��ʷ���ݣ�pListNode��ѯ��� 
@ return 0��ʾΪ�գ�1��ʾ�ǿ�
*/
int HashMapFind(int vehicleID, HashMap H, tListNode* pListNode)
{
	EntryList E;
	tListNode* ListHead;
	
	if(NULL == H) {
		printf("HashMapFind: need to create HashMap first\n");
		return 0;
	}
	//�ҵ���Ӧ��List
	E = H->bucket[Hash(vehicleID, H->MapSize)];
	//ȡ��List���׽ڵ� 
	ListHead = E->Next;
	//�Ҷ�vehicleID��Ӧ��ListNode(Stack) 
	while(NULL != ListHead->Next && ListHead->singleVHDs->bsm->vehicleID) {
		ListHead = ListHead->Next;
	}
	//���ظ�ֵ 
	pListNode = ListHead;
	return 1; 
}


/**
@ brief  ������ʷBSM��Ϣ 
@ param	 bsm Ҫ�����bsm��Ϣ��H HashMap��ʷ����
@ return 0��ʾΪ�գ�1��ʾ�ǿ�
*/
int Insert(tBSM bsm, HashMap H)
{
	EntryList E;
	tListNode* tmp; 
	 
	if(NULL == H) {
		printf("Insert: need to create HashMap first\n");
		return 0;
	}
	E = H->bucket[Hash(bsm->vehicleID, H->MapSize)];
	if(NULL == E) { //������Ϊ�գ�ֱ�Ӳ��� 
		tmp = calloc(1, sizeof(tListNode));
		if(NULL == tmp) {
			printf("Insert: calloc for tListNode* tmp failed\n");
			return 0;
		}
		//�½�һ��Stack��������bsm���� 
		tmp->singleVHDs = CreateStack();
		tmp-> --------------------------------------------------------
		tmp->Next = NULL;
	}else{
		
	}
}

/**
@ brief  HashMap��̬����
@ param	 H ��Ҫ���ݵ�HashMap
@ return ���ݺ��HashMap 
*/
HashMap HashMapReHash(HashMap H)
{
	
}

/**
@ brief  Hash��������Keyת��ΪIndex��static������ 
@ param	 key ����HashMapSize HashMap��bucket�����С 
@ return key��Ӧ�������±� 
*/
static Index Hash(int key, int HashMapSize)
{
    return Key % HashMapSize;
}


