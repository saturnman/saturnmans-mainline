//
//  prog1.c
//  testfeature
//
//  Created by 久亮 郭 on 12-4-21.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include <stdio.h>
#include "prog1.h"
A_stm prog1(void)
{
    //return A_AssignStm("a", A_OpExp(A_NumExp(5),A_plus, A_NumExp(3)));
    
    return     A_CompoundStm(A_AssignStm("a", A_OpExp(A_NumExp(5),A_plus, A_NumExp(3))),
                             A_CompoundStm(A_AssignStm("b", 
                                                       A_EseqExp(A_PrintStm(A_PairExpList(A_IdExp("a"),
                                                                                          A_LastExpList(A_OpExp(A_IdExp("a"), A_minus, A_NumExp(1))))),
                                                                 A_OpExp(A_NumExp(10), A_times, A_IdExp("a")))),
                                           A_PrintStm(A_LastExpList(A_IdExp("b")))));

}