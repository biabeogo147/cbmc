/* Extracted ISR/task definitions for the improved interleaving pipeline. */

static void VirtualizeTimerC_0_updateFromTimer_runTask( void ) 
{
  __CPROVER_atomic_begin();
  // Lihao
  AlarmToTimerC_0_fired_runTask();

  uint32_t now = VirtualizeTimerC_0_TimerFrom_getNow();
  int32_t min_remaining = (1UL << 31) - 1;
  bool min_remaining_isset = FALSE;
  uint8_t num;
  VirtualizeTimerC_0_TimerFrom_stop();
  for(num = 0; num < VirtualizeTimerC_0_NUM_TIMERS; num++)
  {
    VirtualizeTimerC_0_Timer_t *timer = &VirtualizeTimerC_0_m_timers[num];
    if(timer->isrunning)
    {
      //test = 1; // Lihao
      uint32_t elapsed = now - timer->t0;
      int32_t remaining = timer->dt - elapsed;
      if(remaining < min_remaining)
      {
        min_remaining = remaining;
        min_remaining_isset = TRUE;
        //test = 0; // Lihao
      }
    }
    timer->isrunning = TRUE; //Peter: this will cause the bug
  }

  // Lihao: unwind loop VirtualizeTimerC_0_NUM_TIMERS+1 times to reach here
  //assert(0); 

  if(min_remaining_isset)
  {
    if(min_remaining <= 0)
    {
      VirtualizeTimerC_0_fireTimers(now);
    }
    else 
    {
      VirtualizeTimerC_0_TimerFrom_startOneShotAt(now, min_remaining);
    }
  }
  __CPROVER_atomic_end();
}

static void AlarmToTimerC_0_fired_runTask( void ) 
{
  __CPROVER_atomic_begin();
  //test = 1; // Lihao
  if(AlarmToTimerC_0_m_oneshot == FALSE)
  {
    AlarmToTimerC_0_start(AlarmToTimerC_0_Alarm_getAlarm(), AlarmToTimerC_0_m_dt, FALSE);
    //assert(test == 1); // Lihao
  }
  AlarmToTimerC_0_Timer_fired();
  __CPROVER_atomic_end();
}
