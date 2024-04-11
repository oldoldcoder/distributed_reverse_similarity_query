/**
* @author:heqi
* @time:2024/04/10
* @desc:分布式反向查询的操作定义文件
*/
#pragma once

#pragma once
#include "openssl/bn.h"
#include "stdio.h"
#include "stdlib.h"
#include "drs_data_structure.h"
/*------------------------常量定义---------------------*/
#define path x
/*------------------------结构方法定义------------------*/
// 按照id我们每个数据x维护一个堆
typedef struct {

};
// 查询请求的格式
typedef struct{

};
// 查询结果的格式
typedef struct {

};

/*------------------------方法定义---------------------*/
// 预处理计算y集合

// 初始化大顶堆

// 对于每个x遍历y中的数据，进行堆的构建

// 计算流程

// 一次查询请求

// 释放内存
