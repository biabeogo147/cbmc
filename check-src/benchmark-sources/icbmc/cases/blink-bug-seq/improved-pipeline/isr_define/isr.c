/* Extracted ISR/task definitions for the improved interleaving pipeline. */

static void VirtualizeTimerC_0_updateFromTimer_runTask( void ) 
{
  __CPROVER_atomic_begin();
disable_irq(0);
disable_irq(1);

  uint32_t now = VirtualizeTimerC_0_TimerFrom_getNow();
schedule_irq();
  int32_t min_remaining = (1UL << 31) - 1; // W-W dependency
schedule_irq();
  bool min_remaining_isset = FALSE; // W-W dependency
schedule_irq();
  uint8_t num;
  VirtualizeTimerC_0_TimerFrom_stop();
schedule_irq();
  for(num = 0; num < VirtualizeTimerC_0_NUM_TIMERS; num++) // W-W dependency
  {
schedule_irq();
    VirtualizeTimerC_0_Timer_t *timer = &VirtualizeTimerC_0_m_timers[num]; // W-W dependency
schedule_irq();
    if(timer->isrunning) // R-W dependency
    {
      //test = 1; // Lihao
schedule_irq();
      uint32_t elapsed = now - timer->t0; // W-W dependency
schedule_irq();
      int32_t remaining = timer->dt - elapsed; // W-W dependency
schedule_irq();
      if(remaining < min_remaining) // R-W dependency
      {
schedule_irq();
        min_remaining = remaining; // W-W dependency
schedule_irq();
        min_remaining_isset = TRUE; // W-W dependency
schedule_irq();
        //test = 0; // Lihao
      }
    }
schedule_irq();
    timer->isrunning = TRUE; //Peter: this will cause the bug // W-W dependency
schedule_irq();
  }

  // Lihao: unwind loop VirtualizeTimerC_0_NUM_TIMERS+1 times to reach here
  //assert(0); 

schedule_irq();
  if(min_remaining_isset) // R-W dependency
  {
schedule_irq();
    if(min_remaining <= 0) // R-W dependency
    {
schedule_irq();
      VirtualizeTimerC_0_fireTimers(now); // R-W dependency
    }
    else 
    {
      VirtualizeTimerC_0_TimerFrom_startOneShotAt(now, min_remaining);
    }
  }

enable_irq(0);
enable_irq(1);
  __CPROVER_atomic_end();
}

static void AlarmToTimerC_0_fired_runTask( void ) 
{
  __CPROVER_atomic_begin();
disable_irq(0);
enable_irq(1);

  //test = 1; // Lihao
schedule_irq();
  if(AlarmToTimerC_0_m_oneshot == FALSE) // R-W dependency
  {
    AlarmToTimerC_0_start(AlarmToTimerC_0_Alarm_getAlarm(), AlarmToTimerC_0_m_dt, FALSE);
    //assert(test == 1); // Lihao
  }
  AlarmToTimerC_0_Timer_fired();

enable_irq(0);
  __CPROVER_atomic_end();
}
