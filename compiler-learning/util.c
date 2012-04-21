//
//  util.c
//  testfeature
//
//  Created by 久亮 郭 on 12-4-21.
//  Copyright (c) 2012年 __MyCompanyName__. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "limits.h"
#include "util.h"
#include "tree.h"
#include "driver.h"
void* checked_malloc(int size){
    void *ptr = malloc((unsigned long)size);
    assert(ptr);
    return ptr;
}
Table_ Table(string id,int value,struct table* tail){
    Table_ t = malloc(sizeof(*t));
    t->id=id;
    t->value = value;
    t->tail = tail;
    return t;
}
struct IntAndTable
interpExp(A_exp e,Table_ t){
    struct IntAndTable result;
    result.t = t;
    switch (e->kind) {
        case A_idExp:
            if(lookup(t, e->u.id)==INT_MAX){
                printf("ERROR: uninitialized identifier %s\n",t->id);
                exit(1);
                //result.t = update(t,e->u.id,0);
            }
            result.t = t;
            result.i = lookup(t,e->u.id);
            break;
        case A_opExp:
        {
            struct IntAndTable tmp_left = interpExp(e->u.op.left,t);
            struct IntAndTable tmp_right = interpExp(e->u.op.right, tmp_left.t);
            switch (e->u.op.oper) {
                case A_plus:
                    result.i = tmp_left.i + tmp_right.i;
                    break;
                case A_minus:
                    result.i = tmp_left.i - tmp_right.i;
                    break;
                case A_times:
                    result.i = tmp_left.i * tmp_right.i;
                    break;
                case A_div:
                    result.i = tmp_left.i / tmp_right.i;
                    break;
                default:
                    break;
            }
            result.t = t;
            break;
        }
        case A_numExp:
            result.i = e->u.num;
            result.t = t;
            break;
        case A_eseqExp:
        {
            Table_ stmResult = interpStm(e->u.eseq.stm, t);
            result  = interpExp(e->u.eseq.exp, stmResult);
            break;
        }
        default:
            break;
    }
    return result;
}
Table_ interpStm(A_stm stmt,Table_ t){
    Table_ result = t ;
    switch (stmt->kind) {
        case A_compoundStm:
        {
            result = interpStm(stmt->u.compound.stm1, result);
            result = interpStm(stmt->u.compound.stm2, result);
            break;
        }
        case A_assignStm:
        {
            struct IntAndTable expResult = interpExp(stmt->u.assign.exp, t);
            result = update(expResult.t,stmt->u.assign.id,expResult.i);
            break;
        }
        case A_printStm:
            printExpList(stmt->u.print.exps,t);
            printf("\n");
            break;
        default:
            break;
    }
    return result;
}
void printExpList(A_expList el,Table_ t){
    switch (el->kind) {
        case A_pairExpList:
            printExp(el->u.pair.head, t);
            printExpList(el->u.pair.tail,t);
            break;
        case A_lastExpList:
            printExp(el->u.last,t);
            break;
        default:
            break;
    }
}
void printExp(A_exp e,Table_ t){
    switch (e->kind) {
        case A_idExp:
            printf("%d ",lookup(t,e->u.id));
            break;
        case A_numExp:
            printf("%d ",e->u.num);
            break;
        case A_opExp:
            printf("%d",interpExp(e,t).i);
            break;
        case A_eseqExp:
        {
            Table_ stmtResult = interpStm(e->u.eseq.stm, t);
            struct IntAndTable expResult = interpExp(e->u.eseq.exp, stmtResult);
            printf("%d ",expResult.i);
            break;
        }
        default:
            break;
    }
}