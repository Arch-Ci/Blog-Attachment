#ifndef _FIFO_H_
#define _FIFO_H_
 
#include "stdlib.h"
#include "stdint.h"
#include "string.h" 

 
#define FALSE 0
#define TURE 1 
 
 /**
* @brief fifo�ṹ
*/
 
typedef struct
{
	//FIFOͷ�ڵ�λ�� 
    int front;
	//FIFOβ���λ��     
    int rear;
    //FIFO״̬ 
    int IsFull;
    //FIFO�����ַ 
  	void *base;
    // fifo�д洢��Ԫ����,�����ֽڴ�С
    int ItemAmount;
    // Ԫ�ش�С.��λ: �ֽ�
    int ItemSize;
} FIFO;
 
 
/**
* @brief ����fifo
* @param ItemAmount��fifo��Ԫ����.ע�ⲻ���ֽ���
* @param ItemSize: Ԫ�ش�С.��λ: �ֽ�
* @return fifoָ��
*/
FIFO * FIFOCreate(int ItemAmount, int ItemSize);
 
/**
* @brief ɾ��fifo
* @param FIFOIndex: fifoָ��
*/
void FIFODelete(FIFO * FIFOIndex);
 
/**
* @brief fifo����Ƿ����д��
* @param FIFOIndex: fifoָ��
* @retval FALSE:������д��.TURE:����д��
*/
int FIFOWriteAvailable(FIFO * FIFOIndex);
 
/**
* @brief fifoд��
* @param FIFOIndex: fifoָ��
* @param frame:д��Ԫ��ָ��
* @return FALSE:ʧ��.TURE:�ɹ�
*/
int FIFOWrite(FIFO * FIFOIndex, void *data);
 
/**
* @brief fifo����д��
* @param FIFOIndex: fifoָ��
* @param data: д��Ԫ��ָ��
* @param @param num��д���Ԫ����Ŀ
* @return FALSE:ʧ��.TURE:�ɹ�
*/
int FIFOBatchWrite(FIFO * FIFOIndex, void *data, int num);
 
/**
* @brief fifo����Ƿ���Զ�ȡ
* @param FIFOIndex: fifoָ��
* @return FALSE:�����Զ�ȡ.TURE:���Զ�ȡ
*/
int FIFOReadAvailable(FIFO * FIFOIndex);
 
/**
* @brief fifo��ȡ
* @param FIFOIndex: fifoָ��
* @param data: ��ȡ������
* @return FALSE: ʧ��.TURE: �ɹ�
*/
int FIFORead(FIFO * FIFOIndex, void *data);
 
/**
* @brief fifoֻ��ȡ��ɾ������ 
* @param FIFOIndex: fifoָ��
* @param data: ��ȡ������
* @param depath: ��ȡ������� 
* @return FALSE: ʧ��.TURE: �ɹ�
*/
int FIFOPeek(FIFO * FIFOIndex, void *data,int depth); 
 
/**
* @brief fifo������ȡ
* @param FIFOIndex: fifoָ��
* @param data: ��ȡ������
* @param num����ȡ��Ԫ����
* @return FALSE: ʧ��.TURE: �ɹ�
*/
int FIFOBatchRead(FIFO * FIFOIndex, void *data, int num);
 
/**
* @brief fifo�ɶ���Ԫ����
* @param FIFOIndex: fifoָ��
* @return Ԫ����
*/
int FIFOReadableAmount(FIFO * FIFOIndex);
 
/**
* @brief fifo��д��Ԫ����
* @param FIFOIndex: fifoָ��
* @return Ԫ����
*/
int FIFOWritableAmount(FIFO * FIFOIndex);
 
#endif

