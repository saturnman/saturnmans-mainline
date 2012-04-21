//
//  tree.c
//  testfeature
//
//  Created by 久亮 郭 on 12-4-21.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include <stdio.h>
#include "util.h"
#include "tree.h"
A_stm A_CompoundStm(A_stm stm1,A_stm stm2){
    A_stm a_stm = checked_malloc(sizeof(*a_stm));
    a_stm->kind = A_compoundStm;
    a_stm->u.compound.stm1 = stm1;
    a_stm->u.compound.stm2 = stm2;
    return a_stm;
}
A_stm A_AssignStm(string id,A_exp exp){
    A_stm a_stm = checked_malloc(sizeof(*a_stm));
    a_stm->kind = A_assignStm;
    a_stm->u.assign.id = id;
    a_stm->u.assign.exp = exp;
    return a_stm;
}
A_stm A_PrintStm(A_expList expList){
    A_stm a_stm = checked_malloc(sizeof(*a_stm));
    a_stm->kind = A_printStm;
    a_stm->u.print.exps = expList;
    return a_stm;
}
A_exp A_IdExp(string id){
    A_exp a_exp = checked_malloc(sizeof(*a_exp));
    a_exp->kind = A_idExp;
    a_exp->u.id = id;
    return a_exp;
}
A_exp A_NumExp(int num){
    A_exp a_exp = checked_malloc(sizeof(*a_exp));
    a_exp->kind = A_numExp;
    a_exp->u.num = num;
    return a_exp;
}
A_exp A_OpExp(A_exp left,A_binop op,A_exp right){
    A_exp a_exp = checked_malloc(sizeof(*a_exp));
    a_exp->kind = A_opExp;
    a_exp->u.op.left = left;
    a_exp->u.op.oper = op;
    a_exp->u.op.right = right;
    return a_exp;
}
A_exp A_EseqExp(A_stm stm,A_exp exp){
    A_exp a_exp = checked_malloc(sizeof(*a_exp));
    a_exp->kind = A_eseqExp;
    a_exp->u.eseq.stm = stm;
    a_exp->u.eseq.exp = exp;
    return a_exp;
}
A_expList A_PairExpList(A_exp head,A_expList tail){
    A_expList a_expList = checked_malloc(sizeof(*a_expList));
    a_expList->kind = A_pairExpList;
    a_expList->u.pair.head = head;
    a_expList->u.pair.tail = tail;
    return a_expList;
}
A_expList A_LastExpList(A_exp last){
    A_expList a_expList = checked_malloc(sizeof(*a_expList));
    a_expList->kind = A_lastExpList;
    a_expList->u.last = last;
    return a_expList;
}