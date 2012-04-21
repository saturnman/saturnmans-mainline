//
//  driver.h
//  testfeature
//
//  Created by 久亮 郭 on 12-4-21.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#ifndef testfeature_driver_h
#define testfeature_driver_h
#include "tree.h"
#include "util.h"
Table_ interpStm(A_stm stmt,Table_ t);
Table_ update(Table_ t,string key,int value);
int lookup(Table_ t,string key);
void printExpList(A_expList el,Table_ t);
void printExp(A_exp e,Table_ t);
#endif
