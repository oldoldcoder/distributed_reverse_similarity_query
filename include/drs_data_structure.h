/**
* @author:heqi
* @time:2024/04/10
* @desc:分布式反向查询的数据结构定义文件
*/
#pragma once
#include "openssl/bn.h"
#include "stdio.h"
#include "stdlib.h"

/*------------------------常量定义--------------------*/
#define x
/*------------------------结构方法定义--------------------*/
// 数据拥有者单元
typedef struct {
    int id;
    BIGNUM * val;
}drs_data_owner_unit;

typedef struct {
    // 长度
    int n;
    // 一个数据
    drs_data_owner_unit ** units;
}drs_data_owner;

// 数据总的持有者
typedef struct {
    // 维度也是数据拥有者的量
    int d;
    // 数据拥有者的集合
    drs_data_owner ** owners;
}drs_data_set;

// 总的数据y
typedef struct {
    // y集合的数据的总量
    int n;
    // 维度数量
    int d;
    // val值的集合
    BIGNUM *** val;
}drs_y_set;

/*----------------------方法定义----------------------*/
// 初始化y

// 初始化x

// 读取文件数据到x的数据拥有者和y之中

// 释放数据




