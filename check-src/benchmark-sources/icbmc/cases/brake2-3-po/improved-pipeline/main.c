/* 
 * Copyright 2012 The MathWorks, Inc.
 *
 * File: rt_main.c
 *
 * Abstract:
 *
 *   A real-time main that runs generated Simulink Coder code under most 
 *   operating systems.  Based on the definition of MULTITASKING, a single-task 
 *   or multitask step function is employed.
 *
 *   This file is a useful starting point for creating a custom main when 
 *   targeting a custom floating point processor or integer micro-controller.
 *
 *   Alternatively for ERT targets, you can generate a sample ert_main.c file 
 *   with the generated code by selecting the "Generate an example main program"
 *   option.  In this case, ert_main.c is precisely customized to the
 *   model requirements.  
 *
 * Required Defines:
 *
 *   MODEL - Model name
 *   NUMST - Number of sample times
 *
 */

#include <stdio.h>
#include <assert.h>

#include "brake_acc_nodiv_ctrl.c"
#include "brake_acc_nodiv_ctrl_data.c"
#include "rtGetNaN.c"
#include "rtGetInf.c"
#include "rt_nonfinite.c"
#include "cbmc-math.c"
//#include "brake_acc_nodiv_ctrl.h"

// Lihao
//int test;

#define MODEL brake_acc_nodiv_ctrl
#define NUMST 4

/*==================*
 * Required defines *
 *==================*/

#ifndef MODEL
# error Must specify a model name.  Define MODEL=name.
#else
/* create generic macros that work with any model */
# define EXPAND_CONCAT(name1,name2) name1 ## name2
# define CONCAT(name1,name2) EXPAND_CONCAT(name1,name2)
# define MODEL_INITIALIZE CONCAT(MODEL,_initialize)
# define MODEL_STEP       CONCAT(MODEL,_step)
# define MODEL_TERMINATE  CONCAT(MODEL,_terminate)
# define RT_MDL           CONCAT(MODEL,_M)
#endif

#if defined(TID01EQ) && TID01EQ == 1
#define FIRST_TID 1
#else 
#define FIRST_TID 0
#endif

/*====================*
 * External functions *
 *====================*/

extern void MODEL_INITIALIZE(void);
extern void MODEL_TERMINATE(void);

#if 0
extern void MODEL_STEP(int_T tid);  /* multirate step function */


/*===================*
 * Visible functions *
 *===================*/

/* Function: rtOneStep ========================================================
 *
 * Abstract:
 *   Perform one step of the model.  This function is modeled such that
 *   it could be called from an interrupt service routine (ISR) with minor
 *   modifications.
 *
 *   Note that error checking is only necessary when this routine is
 *   attached to an interrupt.
 *
 *   Also, you may wish to unroll any or all of for and while loops to
 *   improve the real-time performance of this function.
 */
static void rt_OneStep(void)
{
    int_T i;

    /*******************************************
     * Step the model for the base sample time *
     *******************************************/
    MODEL_STEP(0);

    /*********************************************************
     * Step the model for any other sample times (subrates) *
     *********************************************************/
    for (i = FIRST_TID+1; i < NUMST; i++) {

      /******************************************
       * Step the model for sample time "i" *
       ******************************************/
      MODEL_STEP(i);
    }

} /* end rtOneStep */
#endif


/* Function: rt_InitModel ====================================================
 * 
 * Abstract: 
 *   Initialized the model and the overrun flags
 *
 */
void rt_InitModel(void)
{
    MODEL_INITIALIZE();
}

/* Function: rt_TermModel ====================================================
 * 
 * Abstract:
 *   Terminates the model and prints the error status
 *
 */
int_T rt_TermModel(void)
{
    MODEL_TERMINATE();
    return(0);
}

// Lihao
#if 0
void printState() {
  printf("state = {\n");
  printf("  RT2_Buffer0 = %f\n",brake_acc_nodiv_ctrl_DW.RT2_Buffer0);
  printf("  RT4_Buffer0 = %f\n",brake_acc_nodiv_ctrl_DW.RT4_Buffer0);
  printf("  RT1_Buffer0 = %f\n",brake_acc_nodiv_ctrl_DW.RT1_Buffer0);
  printf("  RT3_Buffer0 = %f\n",brake_acc_nodiv_ctrl_DW.RT3_Buffer0);
  printf("}\n");
}

void printOutputs() {
  printf("outputs = {\n");
  printf("  Out_TQ_RRBrake = %f\n",brake_acc_nodiv_ctrl_Y.Out_TQ_RRBrake);
  printf("  Out_TQ_RLBrake = %f\n",brake_acc_nodiv_ctrl_Y.Out_TQ_RLBrake);
  printf("  Out_TQ_FRBrake = %f\n",brake_acc_nodiv_ctrl_Y.Out_TQ_FRBrake);
  printf("  Out_TQ_FLBrake = %f\n",brake_acc_nodiv_ctrl_Y.Out_TQ_FLBrake);
  printf("}\n");
}

void printInputs() {
  printf("inputs = {\n");
  printf("  In_BrakePedal = %f\n",brake_acc_nodiv_ctrl_U.In_BrakePedal);
  printf("  In_RRRotation = %f\n",brake_acc_nodiv_ctrl_U.In_RRRotation);
  printf("  In_RLRotation = %f\n",brake_acc_nodiv_ctrl_U.In_RLRotation);
  printf("  In_FRRotation = %f\n",brake_acc_nodiv_ctrl_U.In_FRRotation);
  printf("  In_FLRotation = %f\n",brake_acc_nodiv_ctrl_U.In_FLRotation);
  printf("}\n");
}
#endif

void havocInputs(ExtU_brake_acc_nodiv_ctrl_T *_inputs) {
  ExtU_brake_acc_nodiv_ctrl_T inputs; 

#ifdef CBMC
  __CPROVER_assume(0<=inputs.In_BrakePedal && inputs.In_BrakePedal<=100 &&
              -10000<=inputs.In_RRRotation && inputs.In_RRRotation <= 10000 &&
              -10000<=inputs.In_RLRotation && inputs.In_RLRotation <= 10000 &&
              -10000<=inputs.In_FRRotation && inputs.In_FRRotation <= 10000 &&
              -10000<=inputs.In_FLRotation && inputs.In_FLRotation <= 10000);
#endif

  *_inputs = inputs;
}

/* Split in separate tasks
   Lihao
*/

//Lihao
const int __CPROVER_thread_priorities[] = {5, 5, 5, 5, 22};
const char* __CPROVER_threads[] = {"c::task_RR_Wheel", "c::task_FR_Wheel",
  "c::task_FL_Wheel", "c::task_RL_Wheel", "c::task_compute"};

void task_RR_Wheel(void);
void task_RL_Wheel(void);
void task_FR_Wheel(void);
void task_FL_Wheel(void);




#include "isr_define/isr.c"



/* Function: main =============================================================
 *
 * Abstract:
 *   Execute model on a generic target such as a workstation.
 */
int_T main(int_T argc, const char *argv[])
{
  rt_InitModel();

#if 0
  while (1) 
  {
#endif

    havocInputs(&brake_acc_nodiv_ctrl_U);

    //Lihao
    //__CPROVER_ASYNC_1:
    //task_RL_Wheel();
    //__CPROVER_ASYNC_1:
    //task_compute();


#if 0
    printInputs();

    rt_OneStep();

    printState();
    printOutputs();
  }
#endif

  const int_T result = rt_TermModel();
  return result;
}

/* [EOF] rt_main.c */
