//
//  main.cpp
//  testfeature
//
//  Created by Guo Jiuliang on 12-4-21.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include "stdio.h"
#include "tree.h"
#include "util.h"
#include "prog1.h"
#include "driver.h"
int main (int argc, const char * argv[])
{

    // insert code here...
    //int x = (1,2,3);
    //printf("%d\n",x);
    interpStm(prog1(),NULL);
    return 0;
}

