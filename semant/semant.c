#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "semant.h"

#define TODO()\
  do{\
  printf ("TODO: add your code at file: \"%s\", line: %d\n", __FILE__, __LINE__);\
}while(0)

//////////////////////////////////////
// the symbol table
List_t table = 0;

// lookup an "id" in the symbol table.
// return "type" on success; and -1 for failure
Type_t Table_lookup (char *id)
{
  List_t p = table;
  while (p){
    Dec_t d = (Dec_t)p->data;
    if (strcmp(d->id, id)==0)
      return d->type;
    p = p->next;
  }
  return -1;
}

void Table_insert (Dec_t dec)
{
  
  if (Table_lookup (dec->id) != -1){
    fprintf (stderr, "Error: the variable "
	     "\"%s\" has been declared!\n", dec->id);
    exit (0);
  }
  table = List_new (dec, table);
  return;
}

//////////////////////////////////////////
// dec
void check_dec(Dec_t d)
{
  Table_insert (d);
}

void check_decs(List_t decs)
{
  while (decs){
    Dec_t d = (Dec_t)decs->data;
    check_dec(d);
    decs = decs->next;
  }
  return;
}

////////////////////////////////////////
// exp

// Your job:
Type_t check_exp (Exp_t exp)
{
  // TODO();
  // add by blurt
  switch (exp->kind) {
    case EXP_INT: {
      Exp_Int p = (Exp_Int)exp;
      return TYPE_INT;
    }
    case EXP_TRUE: {
      return TYPE_BOOL;
    }
    case EXP_FALSE: {
      return TYPE_BOOL;
    }
    case EXP_ID: {
      Exp_Id p = (Exp_Id)exp;
      return Table_lookup(p->id);
    }
    case EXP_ADD: {
      Exp_Add p = (Exp_Add)exp;
      Type_t left = check_exp(p->left);
      Type_t right = check_exp(p->right);
      if (left != TYPE_INT || right != TYPE_INT) {
        fprintf(stderr, "Error:expression check error.");
        Exp_print(exp);
        exit(0);
      }
      return left;
    }
    case EXP_SUB: {
      Exp_Sub p = (Exp_Sub)exp;
      Type_t left = check_exp(p->left);
      Type_t right = check_exp(p->right);
      if (left != TYPE_INT || right != TYPE_INT) {
        fprintf(stderr, "Error:expression check error.");
        Exp_print(exp);
        exit(0);
      }
      return left;
    }
    case EXP_TIMES: {
      Exp_Times p = (Exp_Times)exp;
      Type_t left = check_exp(p->left);
      Type_t right = check_exp(p->right);
      if (left != TYPE_INT || right != TYPE_INT) {
        fprintf(stderr, "Error:expression check error.");
        Exp_print(exp);
        exit(0);
      }
      return left;
    }
    case EXP_DIVIDE: {
      Exp_Divide p = (Exp_Divide)exp;
      Type_t left = check_exp(p->left);
      Type_t right = check_exp(p->right);
      if (left != TYPE_INT || right != TYPE_INT) {
        fprintf(stderr, "Error:expression check error.");
        Exp_print(exp);
        exit(0);
      }
      return left;
    }
    case EXP_AND: {
      Exp_And p = (Exp_And)exp;
      Type_t left = check_exp(p->left);
      Type_t right = check_exp(p->right);
      if (left != TYPE_BOOL || right != TYPE_BOOL) {
        fprintf(stderr, "Error:expression check error.");
        Exp_print(exp);
        exit(0);
      }
      return left;
    }
    case EXP_OR: {
      Exp_Or p = (Exp_Or)exp;
      Type_t left = check_exp(p->left);
      Type_t right = check_exp(p->right);
      if (left != TYPE_BOOL || right != TYPE_BOOL) {
        fprintf(stderr, "Error:expression check error.");
        Exp_print(exp);
        exit(0);
      }
      return left;
    }
  }
}

////////////////////////////////////////
// stm

// Your job:
void check_stm (Stm_t stm)
{
  // TODO();
  // add by blurt
  switch (stm->kind) {
    case STM_ASSIGN: {
      Stm_Assign p = (Stm_Assign)(stm);
      Type_t t = Table_lookup(p->id);
      if (t == -1) {
        fprintf(stderr, "Error: the variable %s hasn't been declared.\n", p->id);
        exit(0);
      }
      if (t != check_exp(p->exp)) {
        fprintf(stderr, "Error: the right doesn't match the left type.\n");
        printf("%s:%d\n", p->id, t);
        Stm_print(stm);
        exit(0);
      }
      break;
    }
    case STM_PRINTI: {
      Stm_Printi p = (Stm_Printi)(stm);
      if (TYPE_INT != check_exp(p->exp)) {
        fprintf(stderr, "Error: the type of the expression doesn't match the function.\n");
        Stm_print(stm);
        exit(0);
      }
      break;
    }
    case STM_PRINTB: {
      Stm_Printb p = (Stm_Printb)(stm);
      if (TYPE_BOOL != check_exp(p->exp)) {
        fprintf(stderr, "Error: the type of the expression doesn't match the function.\n");
        Stm_print(stm);
        exit(0);
      }
      break;
    }
    default: {
      fprintf(stderr, "Unkown expression\n");
      exit(0);
    }
  }
}

void check_stms(List_t stms)
{
  while (stms){
    Stm_t s = (Stm_t)stms->data;
    check_stm(s);
    stms = stms->next;
  }
  return;
  TODO();
}


void Semant_check(Prog_t prog)
{
  // create table
  check_decs(prog->decs);
  // check stm
  check_stms(prog->stms);
  return;
}
