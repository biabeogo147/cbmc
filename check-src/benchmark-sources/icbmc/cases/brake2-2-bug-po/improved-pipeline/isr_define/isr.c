/* Extracted ISR/task definitions for the improved interleaving pipeline. */

void task_compute(void)
{
  __CPROVER_atomic_begin();
  // Lihao
  //__CPROVER_ASYNC_1:
  //task_FR_Wheel();

//#if 0
  B_brake_acc_nodiv_ctrl_T brake_acc_nodiv_ctrl_B_local;

  /* Start for RateTransition: '<Root>/RT' */
  brake_acc_nodiv_ctrl_B_local.RT_h = brake_acc_nodiv_ctrl_P.RT_X0;

  /* Start for RateTransition: '<Root>/RT4' */
  brake_acc_nodiv_ctrl_B_local.RT4 = brake_acc_nodiv_ctrl_P.RT4_X0;

  /* Start for RateTransition: '<Root>/RT1' */
  brake_acc_nodiv_ctrl_B_local.RT1 = brake_acc_nodiv_ctrl_P.RT1_X0;

  /* Start for RateTransition: '<Root>/RT2' */
  brake_acc_nodiv_ctrl_B_local.RT2 = brake_acc_nodiv_ctrl_P.RT2_X0;

  /* Start for RateTransition: '<Root>/RT3' */
  brake_acc_nodiv_ctrl_B_local.RT3 = brake_acc_nodiv_ctrl_P.RT3_X0;
//#endif

  //B_brake_acc_nodiv_ctrl_T brake_acc_nodiv_ctrl_B_local = brake_acc_nodiv_ctrl_B;
  //test = 0;

  //  brake_acc_nodiv_ctrl_step2(); //the following code is from this function
  real_T vkmh;
  real_T Distribution_idx;
  real_T Distribution_idx_0;
  real_T Distribution_idx_1;

  /* S-Function (fcncallgen): '<Root>/20ms' incorporates:
   *  SubSystem: '<Root>/Global Brake Controller'
   */
  /* Gain: '<S6>/Distribution' */
  Distribution_idx = brake_acc_nodiv_ctrl_P.Distribution_Gain[1] *
    brake_acc_nodiv_ctrl_B_local.RT14;
  Distribution_idx_0 = brake_acc_nodiv_ctrl_P.Distribution_Gain[2] *
    brake_acc_nodiv_ctrl_B_local.RT14;
  Distribution_idx_1 = brake_acc_nodiv_ctrl_P.Distribution_Gain[3] *
    brake_acc_nodiv_ctrl_B_local.RT14;

  /* S-Function (fcncallgen): '<Root>/20ms1' incorporates:
   *  SubSystem: '<Root>/Veh_Speed_Estimator'
   */
  /* Gain: '<S25>/v (km//h)' incorporates:
   *  Gain: '<S25>/average_rpm'
   *  Gain: '<S25>/w (grad//s)'
   *  Sum: '<S25>/Add'
   */

  vkmh = (((RT9 + RT10) + RT11) + RT12) *
    brake_acc_nodiv_ctrl_P.average_rpm_Gain * brake_acc_nodiv_ctrl_P.wgrads_Gain
    * brake_acc_nodiv_ctrl_P.vkmh_Gain;

  // Lihao
  {
    real_T tmp = (((RT9 + RT10) + RT11) + RT12) *
    brake_acc_nodiv_ctrl_P.average_rpm_Gain * brake_acc_nodiv_ctrl_P.wgrads_Gain
    * brake_acc_nodiv_ctrl_P.vkmh_Gain;

    assert(fabs(vkmh-tmp)<=0.001);
    //assert(test == 0);
  }


  /* S-Function (fcncallgen): '<Root>/20ms' incorporates:
   *  SubSystem: '<Root>/Global Brake Controller'
   */
  /* Update for RateTransition: '<Root>/RT' incorporates:
   *  Gain: '<S6>/Distribution'
   */
  RT_Buffer0 = brake_acc_nodiv_ctrl_P.Distribution_Gain
    [0] * brake_acc_nodiv_ctrl_B_local.RT14;

  /* Update for RateTransition: '<Root>/RT4' */
  RT4_Buffer0 = vkmh;

  /* Update for RateTransition: '<Root>/RT1' */
  RT1_Buffer0 = Distribution_idx;

  /* Update for RateTransition: '<Root>/RT2' */
  RT2_Buffer0 = Distribution_idx_0;

  /* Update for RateTransition: '<Root>/RT3' */
  RT3_Buffer0 = Distribution_idx_1;
  __CPROVER_atomic_end();
}

void task_RR_Wheel(void)
{
  __CPROVER_atomic_begin();
  
  // Lihao
  //__CPROVER_ASYNC_1:
  //task_compute();
  //test = 1;
 
//#if 0
  B_brake_acc_nodiv_ctrl_T brake_acc_nodiv_ctrl_B_local;

  /* Start for RateTransition: '<Root>/RT' */
  brake_acc_nodiv_ctrl_B_local.RT_h = brake_acc_nodiv_ctrl_P.RT_X0;

  /* Start for RateTransition: '<Root>/RT4' */
  brake_acc_nodiv_ctrl_B_local.RT4 = brake_acc_nodiv_ctrl_P.RT4_X0;

  /* Start for RateTransition: '<Root>/RT1' */
  brake_acc_nodiv_ctrl_B_local.RT1 = brake_acc_nodiv_ctrl_P.RT1_X0;

  /* Start for RateTransition: '<Root>/RT2' */
  brake_acc_nodiv_ctrl_B_local.RT2 = brake_acc_nodiv_ctrl_P.RT2_X0;

  /* Start for RateTransition: '<Root>/RT3' */
  brake_acc_nodiv_ctrl_B_local.RT3 = brake_acc_nodiv_ctrl_P.RT3_X0;
//#endif

  //B_brake_acc_nodiv_ctrl_T brake_acc_nodiv_ctrl_B_local = brake_acc_nodiv_ctrl_B;

  //brake_acc_nodiv_ctrl_step1 // the following code is from this function

  /* local block i/o variables */
  real_T rtb_to_int;

  /* RateTransition: '<Root>/RT' */
  brake_acc_nodiv_ctrl_B_local.RT_h = RT_Buffer0;

  /* RateTransition: '<Root>/RT4' */
  brake_acc_nodiv_ctrl_B_local.RT4 = RT4_Buffer0;

  /* Rounding: '<S15>/to_int' incorporates:
   *  Inport: '<Root>/In_RRRotation'
   */
  rtb_to_int = rt_roundd_snf(brake_acc_nodiv_ctrl_U.In_RRRotation);

  /* S-Function (fcncallgen): '<Root>/10ms_1' incorporates:
   *  SubSystem: '<Root>/ABS_RR_Wheel'
   */
  brake_acc_nodiv_ct_ABS_RR_Wheel(brake_acc_nodiv_ctrl_B_local.RT4,
    brake_acc_nodiv_ctrl_B_local.RT_h, rtb_to_int,
    &brake_acc_nodiv_ctrl_B_local.ABS_RR_Wheel, //(P_ABS_RR_Wheel_brake_acc_nodi_T *)
    brake_acc_nodiv_ctrl_P.ABS_RR_Wheel);

  /* Outport: '<Root>/Out_TQ_RRBrake' */
  //brake_acc_nodiv_ctrl_Y.Out_TQ_RRBrake =
  //  brake_acc_nodiv_ctrl_B_local.ABS_RR_Wheel.Threshold_10kmh;

  /* RateTransition: '<Root>/RT1' */
  brake_acc_nodiv_ctrl_B_local.RT1 = RT1_Buffer0;

  /* End of RateTransition: '<Root>/RT1' */

  /* RateTransition: '<Root>/RT9' incorporates:
     *  Gain: '<S5>/Gain1'
     *  Rounding: '<S16>/round_to_int'
     *  Saturate: '<S7>/Pedal_map'
   */
  RT9 = rtb_to_int;

  __CPROVER_atomic_end();
}

void task_FL_Wheel(void)
{
  __CPROVER_atomic_begin();
  
  // Lihao
  //__CPROVER_ASYNC_1:
  //task_compute();

//#if 0
  B_brake_acc_nodiv_ctrl_T brake_acc_nodiv_ctrl_B_local;

  /* Start for RateTransition: '<Root>/RT' */
  brake_acc_nodiv_ctrl_B_local.RT_h = brake_acc_nodiv_ctrl_P.RT_X0;

  /* Start for RateTransition: '<Root>/RT4' */
  brake_acc_nodiv_ctrl_B_local.RT4 = brake_acc_nodiv_ctrl_P.RT4_X0;

  /* Start for RateTransition: '<Root>/RT1' */
  brake_acc_nodiv_ctrl_B_local.RT1 = brake_acc_nodiv_ctrl_P.RT1_X0;

  /* Start for RateTransition: '<Root>/RT2' */
  brake_acc_nodiv_ctrl_B_local.RT2 = brake_acc_nodiv_ctrl_P.RT2_X0;

  /* Start for RateTransition: '<Root>/RT3' */
  brake_acc_nodiv_ctrl_B_local.RT3 = brake_acc_nodiv_ctrl_P.RT3_X0;
//#endif

  //B_brake_acc_nodiv_ctrl_T brake_acc_nodiv_ctrl_B_local = brake_acc_nodiv_ctrl_B;

  //brake_acc_nodiv_ctrl_step1 // the following code is from this function

  real_T rtb_to_int1;
  real_T tmp;

  /* Rounding: '<S9>/to_int1' incorporates:
   *  Inport: '<Root>/In_FLRotation'
   */
  rtb_to_int1 = rt_roundd_snf(brake_acc_nodiv_ctrl_U.In_FLRotation);

  /* RateTransition: '<Root>/RT' */
  brake_acc_nodiv_ctrl_B_local.RT_h = RT_Buffer0;

  /* RateTransition: '<Root>/RT4' */
  brake_acc_nodiv_ctrl_B_local.RT4 = RT4_Buffer0;

  /* S-Function (fcncallgen): '<Root>/10ms_4' incorporates:
   *  SubSystem: '<Root>/ABS_FL_Wheel'
   */
  brake_acc_nodiv_ct_ABS_RR_Wheel(brake_acc_nodiv_ctrl_B_local.RT4,
    brake_acc_nodiv_ctrl_B_local.RT3, rtb_to_int1,
    &brake_acc_nodiv_ctrl_B_local.ABS_FL_Wheel, //(P_ABS_RR_Wheel_brake_acc_nodi_T *)
    brake_acc_nodiv_ctrl_P.ABS_FL_Wheel);

  /* Outport: '<Root>/Out_TQ_FLBrake' */
  //brake_acc_nodiv_ctrl_Y.Out_TQ_FLBrake =
  //  brake_acc_nodiv_ctrl_B_local.ABS_FL_Wheel.Threshold_10kmh;

  /* Saturate: '<S7>/Pedal_map' incorporates:
   *  Inport: '<Root>/In_BrakePedal'
   */
  if (brake_acc_nodiv_ctrl_U.In_BrakePedal >=
      brake_acc_nodiv_ctrl_P.Pedal_map_UpperSat) {
    tmp = brake_acc_nodiv_ctrl_P.Pedal_map_UpperSat;
  } else if (brake_acc_nodiv_ctrl_U.In_BrakePedal <=
	     brake_acc_nodiv_ctrl_P.Pedal_map_LowerSat) {
    tmp = brake_acc_nodiv_ctrl_P.Pedal_map_LowerSat;
  } else {
    tmp = brake_acc_nodiv_ctrl_U.In_BrakePedal;
  }

  /* S-Function (fcncallgen): '<Root>/10ms' incorporates:
   *  SubSystem: '<Root>/Brake_Torq_Calculation'
   */
  RT14 = brake_acc_nodiv_ctrl_P.Gain1_Gain *
    rt_roundd_snf(tmp);

  /* RateTransition: '<Root>/RT12' */
  RT12 = rtb_to_int1;
  __CPROVER_atomic_end();
}

void task_FR_Wheel(void)
{
  __CPROVER_atomic_begin();
  
  // Lihao
  //__CPROVER_ASYNC_1:
  //task_compute();
  
//#if 0 
  B_brake_acc_nodiv_ctrl_T brake_acc_nodiv_ctrl_B_local;

  /* Start for RateTransition: '<Root>/RT' */
  brake_acc_nodiv_ctrl_B_local.RT_h = brake_acc_nodiv_ctrl_P.RT_X0;

  /* Start for RateTransition: '<Root>/RT4' */
  brake_acc_nodiv_ctrl_B_local.RT4 = brake_acc_nodiv_ctrl_P.RT4_X0;

  /* Start for RateTransition: '<Root>/RT1' */
  brake_acc_nodiv_ctrl_B_local.RT1 = brake_acc_nodiv_ctrl_P.RT1_X0;

  /* Start for RateTransition: '<Root>/RT2' */
  brake_acc_nodiv_ctrl_B_local.RT2 = brake_acc_nodiv_ctrl_P.RT2_X0;

  /* Start for RateTransition: '<Root>/RT3' */
  brake_acc_nodiv_ctrl_B_local.RT3 = brake_acc_nodiv_ctrl_P.RT3_X0;
//#endif

  //B_brake_acc_nodiv_ctrl_T brake_acc_nodiv_ctrl_B_local = brake_acc_nodiv_ctrl_B;

  //brake_acc_nodiv_ctrl_step1 // the following code is from this function

  real_T rtb_to_int_k;

  /* RateTransition: '<Root>/RT4' */
  brake_acc_nodiv_ctrl_B_local.RT4 = RT4_Buffer0;

  /* Rounding: '<S11>/to_int' incorporates:
   *  Inport: '<Root>/In_FRRotation'
   */
  rtb_to_int_k = rt_roundd_snf(brake_acc_nodiv_ctrl_U.In_FRRotation);

  /* S-Function (fcncallgen): '<Root>/10ms_3' incorporates:
   *  SubSystem: '<Root>/ABS_FR_Wheel'
   */
  brake_acc_nodiv_ct_ABS_RR_Wheel(brake_acc_nodiv_ctrl_B_local.RT4,
    brake_acc_nodiv_ctrl_B_local.RT2, rtb_to_int_k,
    &brake_acc_nodiv_ctrl_B_local.ABS_FR_Wheel, //(P_ABS_RR_Wheel_brake_acc_nodi_T *)
    brake_acc_nodiv_ctrl_P.ABS_FR_Wheel);

  /* Outport: '<Root>/Out_TQ_FRBrake' */
  //brake_acc_nodiv_ctrl_Y.Out_TQ_FRBrake =
  //  brake_acc_nodiv_ctrl_B_local.ABS_FR_Wheel.Threshold_10kmh;

  /* RateTransition: '<Root>/RT3' */
  brake_acc_nodiv_ctrl_B_local.RT3 = RT3_Buffer0;

  /* End of RateTransition: '<Root>/RT3' */

  /* RateTransition: '<Root>/RT11' */
  RT11 = rtb_to_int_k;
  __CPROVER_atomic_end();
}

void task_RL_Wheel(void)
{
  __CPROVER_atomic_begin();
  
  // Lihao
  //__CPROVER_ASYNC_1:
  //task_compute();
 
//#if 0
  B_brake_acc_nodiv_ctrl_T brake_acc_nodiv_ctrl_B_local;

  /* Start for RateTransition: '<Root>/RT' */
  brake_acc_nodiv_ctrl_B_local.RT_h = brake_acc_nodiv_ctrl_P.RT_X0;

  /* Start for RateTransition: '<Root>/RT4' */
  brake_acc_nodiv_ctrl_B_local.RT4 = brake_acc_nodiv_ctrl_P.RT4_X0;

  /* Start for RateTransition: '<Root>/RT1' */
  brake_acc_nodiv_ctrl_B_local.RT1 = brake_acc_nodiv_ctrl_P.RT1_X0;

  /* Start for RateTransition: '<Root>/RT2' */
  brake_acc_nodiv_ctrl_B_local.RT2 = brake_acc_nodiv_ctrl_P.RT2_X0;

  /* Start for RateTransition: '<Root>/RT3' */
  brake_acc_nodiv_ctrl_B_local.RT3 = brake_acc_nodiv_ctrl_P.RT3_X0;
//#endif

  //B_brake_acc_nodiv_ctrl_T brake_acc_nodiv_ctrl_B_local = brake_acc_nodiv_ctrl_B;

  //brake_acc_nodiv_ctrl_step1 // the following code is from this function

  real_T rtb_to_int_g;

  /* RateTransition: '<Root>/RT4' */
  brake_acc_nodiv_ctrl_B_local.RT4 = RT4_Buffer0;

  /* S-Function (fcncallgen): '<Root>/10ms_2' incorporates:
   *  SubSystem: '<Root>/ABS_RL_Wheel'
   */
  brake_acc_nodiv_ct_ABS_RR_Wheel(brake_acc_nodiv_ctrl_B_local.RT4,
    brake_acc_nodiv_ctrl_B_local.RT1, rtb_to_int_g,
    &brake_acc_nodiv_ctrl_B_local.ABS_RL_Wheel, //(P_ABS_RR_Wheel_brake_acc_nodi_T *)
    brake_acc_nodiv_ctrl_P.ABS_RL_Wheel);

  /* Outport: '<Root>/Out_TQ_RLBrake' */
  //brake_acc_nodiv_ctrl_Y.Out_TQ_RLBrake =
  //  brake_acc_nodiv_ctrl_B_local.ABS_RL_Wheel.Threshold_10kmh;

  /* RateTransition: '<Root>/RT2' */
  brake_acc_nodiv_ctrl_B_local.RT2 = RT2_Buffer0;

  /* End of RateTransition: '<Root>/RT2' */

  /* RateTransition: '<Root>/RT10' */
  RT10 = rtb_to_int_g;
  __CPROVER_atomic_end();
}
