#include "VehiclePendingDatas.h"

/**静态函数声明**/
static int PQDeduplication(PriorityQueue PQhead, tBSM bsm);


/**************优先级队列相关操作***************/

/**
@ brief  初始化 优先级队列（堆）
@ param	 capacity 优先级队列初始化容量
@ return PriorityQueue 优先级队列 队首
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
    //PQ分配堆空间
    H = calloc(1, sizeof(tHeapStruct));
    if(NULL == H) {
        printf("PQInitialize: calloc for H failed\n");
        return NULL;
    }
    //数组分配堆空间(数组第0个元素是sentinel标记节点，不算入capacity和size)
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
@ brief  销毁 优先级队列（堆）
@ param	 PQhead 优先级队列 队首
@ return 0表示失败，1表示成功
*/
int PQDestroy(PriorityQueue PQhead)
{
    free(PQhead);
    free(PQhead->BSMs);
    return 1;
}

/**
@ brief  置空 优先级队列（堆）
@ param	 PQhead 优先级队列 队首
@ return 0表示失败，1表示成功
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
@ brief  入队：插入车辆BSM消息
@ param	 PQhead 优先级队列 队首；bsm 入队的BSM消息
@ return 0表示失败，1表示成功
*/
int PQInsertBSM(PriorityQueue PQhead, tBSM bsm)
{
    tBSM* biggerBSM = NULL; //用于扩容的临时BSM数组
    tBSM* maxBSM = NULL;    //临时用于存储被删除的maxBSM
    int biggerCapacity = 0;
    int i;

    if(NULL == PQhead) {
        printf("PQInsertBSM: need to create Priority Queue first\n");
        return 0;
    }
    //去除VehicleID重复的BSM
    if(0 != PQDeduplication(PQhead, bsm)) {
        printf("PQInsertBSM: PQDeduplication() failed\n");
    }

    //达到容量，则进行删除或扩容。扩展的大小=原大小*扩容因子
    if(IsPQFull(PQhead)) {
        //临时用于存储被删除的maxBSM
        maxBSM = calloc(1, sizeof(tBSM));
        if(NULL == maxBSM) {
            printf("PQInsertBSM: maxBSM calloc() failed\n");
            return 0;
        }

        biggerCapacity = (int)PQhead->Size*(1+PQ_EXPENDFACTOR);//强转为int

        //若超过最大允许容量，则只能通过删除优先级最低（关键值最大）BSM，腾出空间
        if(biggerCapacity > PQ_MAX_CAPACITY) {
            printf("PQInsertBSM: biggerCapacity is > PQ_MAX_CAPACITY, need to PQDeleteMaxBSM()\n");
            if(0 == PQDeleteMaxBSM(PQhead, maxBSM)) {
                printf("PQInsertBSM: PQDeleteMaxBSM() failed\n\n");
                return 0;
            }
        }
        //未超过最大允许容量，则进行扩容
        if(biggerCapacity <= PQ_MAX_CAPACITY) {
            biggerBSM = realloc(PQhead->BSMs, (biggerCapacity+1)*sizeof(tBSM));//加1是为了哨兵节点
            if(NULL == biggerBSM) {  //分配失败，只能通过删除优先级最低（关键值最大）BSM，腾出空间
                printf("PQInsertBSM: biggerBSM realloc() failed, need to PQDeleteMaxBSM()\n");
                if(0 == PQDeleteMaxBSM(PQhead, maxBSM)) {
                    printf("PQInsertBSM: PQDeleteMaxBSM() failed\n\n");
                    return 0;
                }
            } else { //扩容成功
                PQhead->BSMs = biggerBSM;
                PQhead->Capacity = biggerCapacity;
            }
        }

        //记得释放内存
        free(maxBSM);
    }

    //插入BSM消息到数组最后（上滤）
    for(i=++PQhead->Size; PQComputeKey(PQhead->BSMs[i/2])>PQComputeKey(bsm) && i<=1; i/=2) {
        PQhead->BSMs[i] = PQhead->BSMs[i/2];//将父节点向下移动
    }
    PQhead->BSMs[i] = bsm;
    return 1;
}

/**
@ brief  查询数组中是否有该VehicleID的BSM（用于去重）（静态方法）
@ param	 PQhead 优先级队列 队首，bsm 需要去重的BSM
@ return 0表示失败，1表示成功
*/
static int PQDeduplication(PriorityQueue PQhead, tBSM bsm)
{
    int index, i, Child;
    if(NULL == PQhead) {
        printf("PQDeduplication: need to create Priority Queue first\n");
        return 0;
    }

    //先查询看看有没有VehicleID相同的BSM
    index = 1;
    while(index<=PQhead->Size && PQhead->BSMs[index].vehicleID != bsm.vehicleID) {
        index++;
    }
    //说明没找到相同的，也即去重成功
    if(index > PQhead->Size) {
        return 1;
    } else { //说明有相同VehicleID的BSM消息
        if(PQComputeKey(PQhead->BSMs[index]) > PQComputeKey(bsm)) { //比原来的小，上滤
            //从原来index位置，上滤
            for(i=index; PQComputeKey(PQhead->BSMs[i/2])>PQComputeKey(bsm) && i<=1; i/=2) {
                PQhead->BSMs[i] = PQhead->BSMs[i/2];//将父节点向下移动
            }
            //将该节点放到合适位置
            PQhead->BSMs[i] = bsm;
        }
        if(PQComputeKey(PQhead->BSMs[index]) < PQComputeKey(bsm)) { //比原来的大，下滤
            //从原来index位置,下滤
            for(i=index; i*2<=PQhead->Size; i=Child) {
                //比较左右子节点的大小,找小的子节点
                Child = i*2;
                if(Child!=PQhead->Size &&
                        PQComputeKey(PQhead->BSMs[Child]) > PQComputeKey(PQhead->BSMs[Child+1])) {
                    Child++;
                }
                //下滤
                if(PQComputeKey(bsm) > PQComputeKey(PQhead->BSMs[Child])) {
                    PQhead->BSMs[i] = PQhead->BSMs[Child];
                } else {
                    break;//否则跳出for循环
                }
            }
            //将该节点放到合适位置
            PQhead->BSMs[i] = bsm;
        }
        if(PQComputeKey(PQhead->BSMs[index]) == PQComputeKey(bsm)) { //相等则直接替换
            PQhead->BSMs[index] = bsm;
        }
        return 1;
    }
}

/**
@ brief  计算BSM消息的优先级（key越小，优先级越高）
@ param	 PQhead 优先级队列 队首
@ return 0表示失败，1表示成功
*/
double PQComputeKey(tBSM bsm)
{
    //HV的BSM消息，用于模拟计算优先级
    tBSM HV_BSM;
    HV_BSM.id = 0;
    HV_BSM.latitude =  0.0;
    HV_BSM.longitude = 0.0;
    HV_BSM.vehicleClass = 10000;
    HV_BSM.vehicleID = 0;

    //排序标准：①车辆状态（状态码越小，优先级越高；正常状态码最大）
    //			②RV距离HV的距离（RV距离HV越近，优先级越高）

    //欧式距离，需要平方，计算量较大（暂不用）
//	return pow((bsm.latitude-HV_BSM->latitude), 2)
//	       + pow((bsm.longitude-HV_BSM->longitude), 2)
//	       + bsm.vehicleClass;
    //曼哈顿距离
    return (bsm.latitude-HV_BSM.latitude)
           + (bsm.longitude-HV_BSM.longitude)
           + bsm.vehicleClass;
}

/**
@ brief  出队：删除优先级最高（关键字最小）BSM消息
@ param	 PQhead 优先级队列 队首, topBSM 优先级最高的BSM消息指针
@ return 0表示失败，1表示成功
*/
int PQDeleteMinBSM(PriorityQueue PQhead, tBSM* topBSM)
{
    int i, Child;
    tBSM LastBSM;

    if(NULL == PQhead) {
        printf("PQDeleteMinBSM: need to create Priority Queue first\n");
        return 0;
    }
    if(IsPQEmpty(PQhead)) {
        printf("PQDeleteMinBSM: PQhead is empty\n");
        return 0;
    }
    if(NULL == topBSM) {
        printf("PQDeleteMinBSM: topBSM must be initialized before use\n");
        return 0;
    }
    //先记录下来
    *topBSM = PQhead->BSMs[1];
    LastBSM = PQhead->BSMs[PQhead->Size];
    //清除最后一个节点（或者直接在insert时覆盖？）
    memset(PQhead->BSMs+PQhead->Size, 0, sizeof(tBSM));
    PQhead->Size--;
    //（将最后一个节点，当成根节点）下滤
    for(i=1; i*2<=PQhead->Size; i=Child) {
        //比较左右子节点的大小,找小的子节点
        Child = i*2;
        if(Child!=PQhead->Size &&
                PQComputeKey(PQhead->BSMs[Child]) > PQComputeKey(PQhead->BSMs[Child+1])) {
            Child++;
        }
        //下滤
        if(PQComputeKey(LastBSM) > PQComputeKey(PQhead->BSMs[Child])) {
            PQhead->BSMs[i] = PQhead->BSMs[Child];
        } else {
            break;//否则跳出for循环
        }
    }
    //将该节点放到合适位置
    PQhead->BSMs[i] = LastBSM;
    return 1;
}

/**
@ brief  查询：优先级最高（关键字最小）BSM消息
@ param	 PQhead 优先级队列 队首, topBSM 优先级最高的BSM消息指针
@ return 0表示失败，1表示成功
*/
int PQQueryMinBSM(PriorityQueue PQhead, tBSM* topBSM)
{
    if(NULL == PQhead) {
        printf("PQQueryMinBSM: need to create Priority Queue first\n");
        return 0;
    }
    if(IsPQEmpty(PQhead)) {
        printf("PQQueryMinBSM: PQhead is empty\n");
        return 0;
    }
    if(NULL == topBSM) {
        printf("PQQueryMinBSM: topBSM must be initialized before use\n");
        return 0;
    }
    *topBSM = PQhead->BSMs[1];
    return 1;
}

/**
@ brief  出队：删除优先级最低（关键字最大）BSM消息 {遍历数组实现}
@ param	 PQhead 优先级队列 队首, bottomBSM 优先级最低的BSM消息指针
@ return 0表示失败，1表示成功
*/
int PQDeleteMaxBSM(PriorityQueue PQhead, tBSM* bottomBSM)
{
    int i, MaxIndex;
    tBSM MaxBSM, LastBSM;

    if(NULL == PQhead) {
        printf("PQDeleteMaxBSM: need to create Priority Queue first\n");
        return 0;
    }
    if(IsPQEmpty(PQhead)) {
        printf("PQDeleteMaxBSM: PQhead is empty\n");
        return 0;
    }
    if(NULL == bottomBSM) {
        printf("PQDeleteMaxBSM: bottomBSM must be initialized before use\n");
        return 0;
    }
    //找到优先级最低的BSM,并记录下标MaxIndex
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
    //先记录最后一个节点，用于填充MaxBSM删除后的空缺
    LastBSM = PQhead->BSMs[PQhead->Size];
    //清除最后一个节点（或者直接在insert时覆盖？）
    memset(PQhead->BSMs+PQhead->Size, 0, sizeof(tBSM));
    PQhead->Size--;
    //(将最后一个节点LastBSM，从原来MaxBSM位置)上滤
    for(i=MaxIndex; PQComputeKey(PQhead->BSMs[i/2])>PQComputeKey(LastBSM) && i<=1; i/=2) {
        PQhead->BSMs[i] = PQhead->BSMs[i/2];//将父节点向下移动
    }
    //将该节点放到合适位置
    PQhead->BSMs[i] = LastBSM;

    return 1;
}

/**
@ brief  查询：优先级最低（关键字最大）BSM消息 {遍历数组实现}
@ param	 PQhead 优先级队列 队首, bottomBSM 优先级最低的BSM消息指针
@ return 0表示失败，1表示成功
*/
int PQQueryMaxBSM(PriorityQueue PQhead, tBSM* bottomBSM)
{
    int i;
    tBSM MaxBSM;

    if(NULL == PQhead) {
        printf("PQQueryMaxBSM: need to create Priority Queue first\n");
        return 0;
    }
    if(IsPQEmpty(PQhead)) {
        printf("PQQueryMaxBSM: PQhead is empty\n");
        return 0;
    }
    if(NULL == bottomBSM) {
        printf("PQQueryMaxBSM: bottomBSM must be initialized before use\n");
        return 0;
    }
    i = (int)PQhead->Size/2+1;
    MaxBSM = PQhead->BSMs[i];
    //最大值一定在树叶上，叶子节点范围为(n/2+1~n),下标从1开始
    for(i=i+1; i<=PQhead->Size; i++) {
        if(PQComputeKey(PQhead->BSMs[i]) > PQComputeKey(MaxBSM)) {
            MaxBSM = PQhead->BSMs[i];
        }
    }
    *bottomBSM = MaxBSM;
    return 1;
}

/**
@ brief  更新HV的BSM消息后，需要对优先级队列进行重排序
		为了避免PQhead对应堆空间的频繁销毁、重建，考虑只改变BSMs对应数组的内容，实现重排序
@ param	 PQhead 优先级队列 队首
@ return 0表示失败，1表示成功
*/
int PQReSort(PriorityQueue PQhead)
{
    int i, size;
    if(NULL == PQhead) {
        printf("PQReSort: need to create Priority Queue first\n");
        return 0;
    }
    if(IsPQEmpty(PQhead)) {
        printf("PQReSort: PQhead is empty\n");
        return 0;
    }
    //清空数组（不是真的清空）
    size = PQhead->Size;
    if(0 == PQMakeEmpty(PQhead)) {
        printf("PQReSort: PQMakeEmpty() failded\n");
        return 0;
    }
    //将原数组中元素，直接从新放进清空后的PQhead(从1到n，一个一个填充)
    //这样就不用整个将BSMs数组全部复制下来，然后一个个插入
    for(i=1; i<=size; i++) {
        PQInsertBSM(PQhead, PQhead->BSMs[i]);
    }
    return 1;
}


/**
@ brief  判断优先级队列是否为空
@ param	 PQhead 优先级队列 队首
@ return 0表示为空，1表示非空
*/
int IsPQEmpty(PriorityQueue PQhead)
{
    return 0 == PQhead->Size;
}

/**
@ brief  判断优先级队列是否已满
@ param	 PQhead 优先级队列 队首
@ return 0表示为未满，1表示已满
*/
int IsPQFull(PriorityQueue PQhead)
{
    return PQhead->Capacity == PQhead->Size;
}
