#include "fifo.h"
 
/**
* @brief ����fifo
* @param ItemAmount��fifo��Ԫ����.ע�ⲻ���ֽ���
* @param ItemSize: Ԫ�ش�С.��λ: �ֽ�
* @return fifoָ��
*/
 
FIFO * FIFOCreate(int ItemAmount, int ItemSize)
{
    FIFO *fifo = (FIFO *)malloc(sizeof(FIFO));
    fifo->ItemAmount = ItemAmount;
    fifo->ItemSize = ItemSize;
    fifo->front = 0;
    fifo->rear = 0;
    fifo->IsFull = FALSE;
    fifo->base = (void *)malloc(ItemAmount * ItemSize);
    return fifo;
}
 
/**
* @brief ɾ��fifo
* @param FIFOIndex: fifoָ��
*/
 
void FIFODelete(FIFO * FIFOIndex)
{
    FIFO *fifo = (FIFO *)FIFOIndex;
    free(fifo->base);
    fifo->base = NULL;
    free(fifo);
    fifo = NULL;
}
 
/**
* @brief fifo����Ƿ����д��
* @param FIFOIndex: fifoָ��
* @retval FALSE:������д��.TURE:����д��
*/
 
int FIFOWriteAvailable(FIFO * FIFOIndex)
{	
    FIFO *fifo = (FIFO *)FIFOIndex;
    return !fifo->IsFull;
}
 
/**
* @brief fifoд��
* @param FIFOIndex: fifoָ��
* @param frame:д��Ԫ��ָ��
* @return FALSE:ʧ��.TURE:�ɹ�
*/
 
int FIFOWrite(FIFO * FIFOIndex, void *data)
{
    FIFO *fifo = (FIFO *)FIFOIndex;
    if (fifo->IsFull)
	{
		return FALSE;
	}

    memcpy((char *)(fifo->base) + fifo->front * fifo->ItemSize, data, fifo->ItemSize);
    fifo->front++;

    if (fifo->front >= fifo->ItemAmount)
	{
        fifo->front = 0;
	}
    if (fifo->front == fifo->rear)
	{
        fifo->IsFull = TURE;
	}
	
	return TURE;
}
 
/**
* @brief fifo����д��
* @param FIFOIndex: fifoָ��
* @param data: д��Ԫ��ָ��
* @param num��д���Ԫ����Ŀ
* @return FALSE:ʧ��.TURE:�ɹ�
*/
int FIFOBatchWrite(FIFO * FIFOIndex, void *data, int num)
{
    FIFO *fifo = (FIFO *)FIFOIndex;
    if (FIFOWritableAmount(fifo) < num)
    {
        return FALSE;
    }
 	
 	if (fifo->ItemAmount-fifo->front > num)
    {
        memcpy((char *)(fifo->base) + fifo->front * fifo->ItemSize, data, fifo->ItemSize * num);
    }
    else
    {
    	memcpy((char *)(fifo->base) + fifo->front * fifo->ItemSize, (char *)data, fifo->ItemSize * (fifo->ItemAmount-fifo->front));
    	memcpy((char *)(fifo->base) , (char *)data+ (fifo->ItemSize * (fifo->ItemAmount-fifo->front)),fifo->ItemSize * ( num+fifo->front-fifo->ItemAmount));
	}
    
    fifo->front = (fifo->front+num)%fifo->ItemAmount;

    if (fifo->front == fifo->rear)
    {
        fifo->IsFull = TURE;
    }
 
    return TURE;
}
 
/**
* @brief fifo����Ƿ���Զ�ȡ
* @param FIFOIndex: fifoָ��
* @return FALSE:�����Զ�ȡ.TURE:���Զ�ȡ
*/
int FIFOReadAvailable(FIFO * FIFOIndex)
{
    FIFO *fifo = (FIFO *)FIFOIndex;
    if (fifo->front == fifo->rear && !fifo->IsFull)
	{
		return FALSE;
	}
	return TURE;
}
 
/**
* @brief fifoֻ��ȡ��ɾ������ 
* @param FIFOIndex: fifoָ��
* @param data: ��ȡ������
* @param depath: ��ȡ������� 
* @return FALSE: ʧ��.TURE: �ɹ�
*/
int FIFOPeek(FIFO * FIFOIndex, void *data,int depth)
{
    FIFO *fifo = (FIFO *)FIFOIndex;
    if (fifo->front == fifo->rear && !fifo->IsFull)
	{
		return FALSE;
	}
	
	if(depth>FIFOReadableAmount(fifo)-1)
	{
		return FALSE;
	}
    
    memcpy(data, (char *)(fifo->base) + ((fifo->rear+depth)%fifo->ItemAmount) * fifo->ItemSize, fifo->ItemSize);
	return TURE;
}

/**
* @brief fifo��ȡ
* @param FIFOIndex: fifoָ��
* @param data: ��ȡ������
* @return FALSE: ʧ��.TURE: �ɹ�
*/
int FIFORead(FIFO * FIFOIndex, void *data)
{
    FIFO *fifo = (FIFO *)FIFOIndex;
    if (fifo->front == fifo->rear && !fifo->IsFull)
	{
		return FALSE;
	}
    
    memcpy(data, (char *)(fifo->base) + fifo->rear * fifo->ItemSize, fifo->ItemSize);
    fifo->rear++;
    if (fifo->rear >= fifo->ItemAmount)
	{
        fifo->rear = 0;
	}
    fifo->IsFull = FALSE;
	return TURE;
}
 
/**
* @brief fifo������ȡ
* @param FIFOIndex: fifoָ��
* @param data: ��ȡ������
* @param num����ȡ��Ԫ����
* @return FALSE: ʧ��.TURE: �ɹ�
*/
int FIFOBatchRead(FIFO * FIFOIndex, void *data, int num)
{
        FIFO *fifo = (FIFO *)FIFOIndex;
    if (FIFOReadableAmount(fifo) < num)
    {
        return FALSE;
    }
 
 	if (fifo->ItemAmount-fifo->rear > num)
    {
    	memcpy(data, (char *)(fifo->base) + fifo->rear * fifo->ItemSize, fifo->ItemSize * num);
    }
    else
    {
    	memcpy((char *)data, (char *)(fifo->base) + fifo->rear * fifo->ItemSize,  fifo->ItemSize * (fifo->ItemAmount-fifo->rear));
    	memcpy((char *)data+ (fifo->ItemSize * (fifo->ItemAmount-fifo->rear)),fifo->base,  fifo->ItemSize * ( num+fifo->rear-fifo->ItemAmount));
	}
    fifo->rear = (num+fifo->rear)%fifo->ItemAmount;

    fifo->IsFull = FALSE;
    return TURE;
}
 
/**
* @brief fifo�ɶ���Ԫ����,����ʹ�õ����� 
* @param FIFOIndex: fifoָ��
* @return Ԫ����
*/
int FIFOReadableAmount(FIFO * FIFOIndex)
{
    FIFO *fifo = (FIFO *)FIFOIndex;
    if (fifo->IsFull)
    {
        return fifo->ItemAmount;
    }
    else
    {
        return (fifo->ItemAmount + fifo->front - fifo->rear) % fifo->ItemAmount;
    }
}
 
/**
* @brief fifo��д��Ԫ����,��δʹ������ 
* @param FIFOIndex: fifoָ��
* @return Ԫ����
*/
int FIFOWritableAmount(FIFO * FIFOIndex)
{
    FIFO *fifo = (FIFO *)FIFOIndex;
    if (fifo->IsFull)
    {
        return 0;
    }
    else
    {
        if (fifo->front == fifo->rear)
        {
            return fifo->ItemAmount;
        }
        else
        {
            return (fifo->ItemAmount + fifo->rear - fifo->front) % fifo->ItemAmount;
        }
    }
}

