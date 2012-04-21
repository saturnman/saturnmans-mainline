//
//  driver.c
//  testfeature
//
//  Created by 久亮 郭 on 12-4-21.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "limits.h"
#include "driver.h"
Table_ update(Table_ t,string key,int value){
    Table_ result = Table(key, value, t);
    return result;
}
int lookup(Table_ t,string key){
    assert(t);
    Table_ tmpTablePtr = t;
    while (tmpTablePtr!=NULL){
        if (strcmp(t->id,key)==0) {
            return t->value;
        }
        tmpTablePtr = tmpTablePtr->tail;
    }
    //assert(t);
    //printf("invalid key\n");
    //exit(1);
    return INT_MAX;
}