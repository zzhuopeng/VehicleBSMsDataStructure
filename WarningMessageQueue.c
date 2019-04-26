#include "WarningMessageQueue.h"

/**静态函数声明**/
//③重复的BSM消息，会在PriorityQueue里面去除


/****优先级队列相关操作（最大堆）****/

/**
@ brief  初始化 优先级队列（堆）
@ param	 capacity 优先级队列初始化容量
@ return WarningPriorityQueue 优先级队列
*/
WarningPriorityQueue WarningPQInitialize(int capacity)
{
    WarningPriorityQueue W;
    if(capacity < WarningPQ_MIN_CAPACITY) {
        printf("WarningPQInitialize: Priority Queue size is too small\n");
        return NULL;
    }
    if(capacity > WarningPQ_MAX_CAPACITY) {
        printf("WarningPQInitialize: Priority Queue size is too large\n");
        return NULL;
    }

    //分配内存
    W = calloc(1, sizeof(tMaxHeapStruct));
    if(NULL == W) {
        printf("WarningPQInitialize: calloc for W failed\n");
        return NULL;
    }
    W->WarningMessages = calloc(capacity+1, sizeof(tWarningMessage));
    if(NULL == W->WarningMessages) {
        printf("WarningPQInitialize: calloc for W->WarningMessages failed\n");
        return NULL;
    }
    W->Capacity = capacity;
    W->Size = 0;
    return W;
}


/**
@ brief  销毁 优先级队列（堆）
@ param	 WPQ 优先级队列
@ return 0表示失败，1表示成功
*/
int WarningPQDestroy(WarningPriorityQueue WPQ)
{
    free(WPQ->WarningMessages);
    free(WPQ);
    return 1;
}


/**
@ brief  清空 优先级队列（堆）
@ param	 WPQ 优先级队列
@ return 0表示失败，1表示成功
*/
int WarningPQMakeEmpty(WarningPriorityQueue WPQ)
{
    if(NULL == WPQ) {
        printf("WarningPQMakeEmpty: WPQ need to be initialized\n");
        return 0;
    }
    WPQ->Size = 0;
    return 1;
}


/**
@ brief  入队：插入车辆BSM消息
@ param	 WPQ 优先级队列；WM 入队的预警消息
@ return 0表示失败，1表示成功
*/
int WarningPQInsert(WarningPriorityQueue WPQ, tWarningMessage WM)
{
    int biggerCapacity;         //扩展后容量
    tWarningMessage* biggerWM;  //扩展后数组
    tWarningMessage* minWM;     //临时预警消息指针
    int i;

    if(NULL == WPQ) {
        printf("WarningPQInsertBSM: WPQ need to be initialized\n");
        return 0;
    }
    //满了就动态扩容
    if(IsWarningPQFull(WPQ)) {
        //初始化临时变量minWM
        minWM = calloc(1, sizeof(tWarningMessage));
        if(NULL == minWM) {
            printf("WarningPQInsertBSM: WPQ need to be initialized\n");
            return 0;
        }

        //扩展的大小=原大小*扩容因子
        biggerCapacity = (int) WPQ->Capacity*(1+WarningPQ_EXPENDFACTOR);
        //可以扩容
        if(biggerCapacity <= WarningPQ_MAX_CAPACITY) {
            biggerWM = realloc(WPQ->WarningMessages, (biggerCapacity+1)*sizeof(tWarningMessage));
            if(NULL == biggerWM) {
                printf("WarningPQInsertBSM: realloc() for biggerWM failed\n");
                //扩容失败的话，只能删除优先级最低预警消息
                if(0 == WarningPQDeleteMin(WPQ, minWM)) {
                    printf("WarningPQInsertBSM: WarningPQDeleteMin() failed\n");
                    return 0;
                }
            }
            //扩容成功
            WPQ->WarningMessages = biggerWM;
            WPQ->Capacity = biggerCapacity;
        }
        //不能扩容，直接删除优先级最低预警消息
        if(biggerCapacity > WarningPQ_MAX_CAPACITY) {
            printf("WarningPQInsert: biggerCapacity is > WarningPQ_MAX_CAPACITY, need to PQDeleteMin()\n");
            if(0 == WarningPQDeleteMin(WPQ, minWM)) {
                printf("WarningPQInsertBSM: WarningPQDeleteMin() failed\n");
                return 0;
            }
        }
        //释放临时变量minWM内存
        free(minWM);
    }

    //插入预警消息（上滤）
    for(i=++WPQ->Size; i/2>=1&&WarningPQComputeKey(WPQ->WarningMessages[i/2])<WarningPQComputeKey(WM); i/=2) {
        //父节点向下移动
        WPQ->WarningMessages[i] = WPQ->WarningMessages[i/2];
    }
    WPQ->WarningMessages[i] = WM;
    return 1;
}


/**
@ brief  计算预警消息的优先级（key越小，优先级越高）
@ param	 WPQ 优先级队列
@ return 0表示失败，1表示成功
*/
int WarningPQComputeKey(tWarningMessage WM)
{
    //这里暂时用相加的方式计算权值
    //实际上可能某些优先级低而Level高的场景会比优先级高而Level低的场景更危险
    return WM.Scene+WM.Level;
}

/**
@ brief  出队：删除优先级最高（关键字最大）预警消息
@ param	 WPQ 优先级队列, topWM 优先级最高的预警消息指针
@ return 0表示失败，1表示成功
*/
int WarningPQDeleteMax(WarningPriorityQueue WPQ, tWarningMessage* topWM)
{
    tWarningMessage LastWM;
    int child, i;

    if(NULL == WPQ) {
        printf("WarningPQDeleteMax: WPQ need to be initialized\n");
        return 0;
    }
    if(IsPQEmpty(WPQ)) {
        printf("WarningPQDeleteMax: WPQ is empty\n");
        return 0;
    }
    if(NULL == topWM) {
        printf("WarningPQDeleteMax: topWM need to be initialized\n");
        return 0;
    }
    //记录根节点的值
    *topWM = WPQ->WarningMessages[1];

    //记录最后节点
    LastWM = WPQ->WarningMessages[WPQ->Size];
    WPQ->Size--;
    //将最后一个节点从根节点开始下滤
    for(i=1; i<=WPQ->Size; i=child) {
        child = i*2;
        //比较子节点大小，找大的子节点
        if(child!=WPQ->Size && WarningPQComputeKey(WPQ->WarningMessages[child]) < WarningPQComputeKey(WPQ->WarningMessages[child+1])) {
            child++;
        }
        //下滤
        if(WarningPQComputeKey(child) > WarningPQComputeKey(LastWM)) {
            //子节点上移
            WPQ->WarningMessages[i] = WPQ->WarningMessages[child];
        } else {
            break;
        }
    }
    //将该节点放到合适位置
    WPQ->WarningMessages[i] = LastWM;
    return 1;
}


/**
@ brief  查询：优先级最高（关键字最大）预警消息
@ param	 WPQ 优先级队列, topBSM 优先级最高的预警消息指针
@ return 0表示失败，1表示成功
*/
int WarningPQQueryMax(WarningPriorityQueue WPQ, tWarningMessage* topWM)
{
    if(NULL == WPQ) {
        printf("WarningPQQueryMax: WPQ need to be initialized\n");
        return 0;
    }
    if(IsPQEmpty(WPQ)) {
        printf("WarningPQQueryMax: WPQ is empty\n");
        return 0;
    }
    if(NULL == topWM) {
        printf("WarningPQQueryMax: topWM need to be initialized\n");
        return 0;
    }
    *topWM = WPQ->WarningMessages[1];
    return 1;
}


/**
@ brief  出队：删除优先级最低（关键字最小）预警消息 {遍历数组实现}
@ param	 WPQ 优先级队列 队首, bottomWM 优先级最低的预警消息指针
@ return 0表示失败，1表示成功
*/
int WarningPQDeleteMin(WarningPriorityQueue WPQ, tWarningMessage* bottomWM)
{
    int i, minIndex;
    tWarningMessage* minWM;

    if(NULL == WPQ) {
        printf("WarningPQDeleteMin: WPQ need to be initialized\n");
        return 0;
    }
    if(IsPQEmpty(WPQ)) {
        printf("WarningPQDeleteMin: WPQ is empty\n");
        return 0;
    }
    if(NULL == bottomWM) {
        printf("WarningPQDeleteMin: bottomWM need to be initialized\n");
        return 0;
    }
    //优先级最低节点在叶子上，叶子范围为(n/2)+1至n，index从1开始
    minWM = WPQ->WarningMessages+WPQ->Size;
    minIndex = WPQ->Size;
    for(i=WPQ->Size-1; i>=(int)(WPQ->Size/2)+1; i--) {
        if(WarningPQComputeKey(WPQ->WarningMessages[i]) < WarningPQComputeKey(*minWM)) {
            minWM = WPQ->WarningMessages+i;
            minIndex = i;
        }
    }
    //找到优先级最低的节点
    *bottomWM = *minWM;

    //通过最后一个节点填充，应该删除的优先级最小节点（上滤）
    for(i=minIndex; i/2<=1 &&
        WarningPQComputeKey(WPQ->WarningMessages[i/2])<WarningPQComputeKey(WPQ->WarningMessages[WPQ->Size]); i/=2) {
        WPQ->WarningMessages[i] = WPQ->WarningMessages[i/2];
    }
    WPQ->WarningMessages[i] = WPQ->WarningMessages[WPQ->Size];
    WPQ->Size--;
    return 1;
}


/**
@ brief  判断优先级队列是否为空
@ param	 WPQ 优先级队列
@ return 0表示为空，1表示非空
*/
int IsWarningPQEmpty(WarningPriorityQueue WPQ)
{
    return 0 == WPQ->Size;
}


/**
@ brief  判断优先级队列是否已满
@ param	 WPQ 优先级队列
@ return 0表示为未满，1表示已满
*/
int IsWarningPQFull(WarningPriorityQueue WPQ)
{
    return WPQ->Capacity == WPQ->Size;
}


