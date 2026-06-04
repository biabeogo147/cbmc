/* Extracted ISR/task definitions for the improved interleaving pipeline. */

static void VirtualizeTimerC_0_updateFromTimer_runTask(void) {
  __CPROVER_atomic_begin();
__VERIFIER_atomic_TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
__VERIFIER_atomic_TRANS_VirtualizeTimerC_0_updateFromTimer_runTask_enter_thread();
__VERIFIER_atomic_TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
  //inline
  //VirtualizeTimerC_0_TimerFrom_getNow();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
  TransformCounterC_0_to_size_type rv = 0;
  bool tmp_bool; // Lihao: lift if
TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
  
  /* IRQ INSTR 17 */
  //  if ((_R2 & 0x0008) != 0x0000) { _R2 &= 0xfff7; sig_TIMERB0_VECTOR(); _R2 |= 0x0008; }
__VERIFIER_atomic_begin();
TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
  __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
    TransformCounterC_0_upper_count_type high = TransformCounterC_0_m_upper;
TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
    TransformCounterC_0_from_size_type low = TransformCounterC_0_CounterFrom_get();
TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
    // Lihao: lift if 
__VERIFIER_atomic_begin();
TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
    tmp_bool = TransformCounterC_0_CounterFrom_isOverflowPending();
TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
    //if(TransformCounterC_0_CounterFrom_isOverflowPending()) {
    if(tmp_bool) {
__VERIFIER_atomic_TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
      high++;
TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
      low = TransformCounterC_0_CounterFrom_get();
TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
    }

__VERIFIER_atomic_TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
    TransformCounterC_0_to_size_type high_to = high;
TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
    TransformCounterC_0_to_size_type low_to = low >> TransformCounterC_0_LOW_SHIFT_RIGHT;
TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
    rv = (high_to << TransformCounterC_0_HIGH_SHIFT_LEFT) | low_to;
TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
  __nesc_atomic_end(__nesc_atomic);
TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
  // end of inline: VirtualizeTimerC_0_TimerFrom_getNow();

__VERIFIER_atomic_begin();
TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
  uint32_t now = rv;   
TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
  int32_t min_remaining = (1UL << 31) - 1;
TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
  bool min_remaining_isset = FALSE;
TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
  uint8_t num;
TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
  VirtualizeTimerC_0_TimerFrom_stop();
TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
// Lihao: lift if
__VERIFIER_atomic_begin();
TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
  uint32_t tmp_VirtualizeTimerC_0_NUM_TIMERS = VirtualizeTimerC_0_NUM_TIMERS; 
TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
  for(num = 0; num < tmp_VirtualizeTimerC_0_NUM_TIMERS; num++) {
  //for(num = 0; num < VirtualizeTimerC_0_NUM_TIMERS; num++) {
__VERIFIER_atomic_TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
    VirtualizeTimerC_0_Timer_t *timer = &VirtualizeTimerC_0_m_timers[num];
TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
  bool isrunning = timer->isrunning;
TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
    if(isrunning) {
__VERIFIER_atomic_TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
      //test = 1; // Lihao
__VERIFIER_atomic_begin();
TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
      uint32_t elapsed = now - timer->t0;
TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
      int32_t remaining = timer->dt - elapsed;
TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
      if(remaining < min_remaining) {
__VERIFIER_atomic_TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
        min_remaining = remaining;
TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
        min_remaining_isset = TRUE;
TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
        //test = 0; // Lihao
      }
    }
__VERIFIER_atomic_TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
    timer->isrunning = TRUE; //Peter: this will cause the bug
TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
__VERIFIER_atomic_end();
  }

  // Lihao: unwind loop VirtualizeTimerC_0_NUM_TIMERS times to reach here
  //assert(0); 

__VERIFIER_atomic_TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
  if(min_remaining_isset) {
__VERIFIER_atomic_TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
    if(min_remaining <= 0) {
__VERIFIER_atomic_TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
      // inline
      //VirtualizeTimerC_0_fireTimers(now);
__VERIFIER_atomic_begin();
TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
      uint8_t num;
TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
// Lihao: lift if
__VERIFIER_atomic_begin();
TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
  tmp_VirtualizeTimerC_0_NUM_TIMERS = VirtualizeTimerC_0_NUM_TIMERS; 
TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
      for(num = 0; num < tmp_VirtualizeTimerC_0_NUM_TIMERS; num++) {
      //for(num = 0; num < VirtualizeTimerC_0_NUM_TIMERS; num++) {
__VERIFIER_atomic_TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
        VirtualizeTimerC_0_Timer_t *timer = &VirtualizeTimerC_0_m_timers[num];
TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
        bool isrunning = timer->isrunning;
TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
        if(isrunning) {
__VERIFIER_atomic_TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
          uint32_t elapsed = now - timer->t0;
TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
          //test = 0; assert(test == 0); // Lihao
          // Lihao: lift if
__VERIFIER_atomic_begin();
TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
          VirtualizeTimerC_0_Timer_t tmp_timer = *timer;
TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
          if(elapsed >= tmp_timer.dt) {
          //if(elapsed >= timer->dt) {
__VERIFIER_atomic_TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
 __VERIFIER_atomic_begin();
TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
          tmp_timer = *timer;
TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
            if(tmp_timer.isoneshot) {
            //if(timer->isoneshot) {
__VERIFIER_atomic_TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
              timer->isrunning = FALSE;
TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
              //assert(timer->isrunning == FALSE); //Peter
              //if(timer->isrunning =! FALSE) irq_err(); 
              //test = 0; assert(test == 0); // Lihao
            } else {
__VERIFIER_atomic_TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
              timer->t0 += timer->dt;
TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
            }
__VERIFIER_atomic_TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
            VirtualizeTimerC_0_Timer_fired(num);
TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
              break;
          }
        }
      }
__VERIFIER_atomic_TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
      VirtualizeTimerC_0_updateFromTimer_postTask();
TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
      // end of inline: VirtualizeTimerC_0_fireTimers(now);
    } else {
__VERIFIER_atomic_TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
      //VirtualizeTimerC_0_TimerFrom_startOneShotAt(now, min_remaining);
      // inline
__VERIFIER_atomic_begin();
TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
      AlarmToTimerC_0_m_dt = min_remaining;
TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
      AlarmToTimerC_0_m_oneshot = TRUE;
TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
      // inline
      // AlarmToTimerC_0_Alarm_startAt(now, min_remaining);
      /* IRQ INSTR 19 */
      //  if ((_R2 & 0x0008) != 0x0000) { _R2 &= 0xfff7; sig_TIMERB0_VECTOR(); _R2 |= 0x0008; }
      
__VERIFIER_atomic_begin();
TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
      __nesc_atomic_t __nesc_atomic = __nesc_atomic_start(); 
TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
        TransformAlarmC_0_m_t0 = now;
TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
        TransformAlarmC_0_m_dt = min_remaining;
TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
      
        // inline
        //TransformAlarmC_0_set_alarm();
        // inline: TransformAlarmC_0_Counter_get()
__VERIFIER_atomic_begin();
TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
        TransformCounterC_0_to_size_type rv = 0;
TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
        /* IRQ INSTR 17 */
        //  if ((_R2 & 0x0008) != 0x0000) { _R2 &= 0xfff7; sig_TIMERB0_VECTOR(); _R2 |= 0x0008; }
__VERIFIER_atomic_begin();
TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
        __nesc_atomic_t __nesc_atomic2 = __nesc_atomic_start();
TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
        TransformCounterC_0_upper_count_type high = TransformCounterC_0_m_upper;
TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
        TransformCounterC_0_from_size_type low = TransformCounterC_0_CounterFrom_get();
TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
        // Lihao: lift if
__VERIFIER_atomic_begin();
TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
        tmp_bool = TransformCounterC_0_CounterFrom_isOverflowPending();
TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
        if(tmp_bool) {
        //if(TransformCounterC_0_CounterFrom_isOverflowPending()) {
__VERIFIER_atomic_TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
          high++;
TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
          low = TransformCounterC_0_CounterFrom_get();
TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
        }
__VERIFIER_atomic_TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
        TransformCounterC_0_to_size_type high_to = high;
TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
        TransformCounterC_0_to_size_type low_to = low >> TransformCounterC_0_LOW_SHIFT_RIGHT;
TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
        rv = (high_to << TransformCounterC_0_HIGH_SHIFT_LEFT) | low_to;
TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
        __nesc_atomic_end(__nesc_atomic2);
TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
        // end of inline: TransformAlarmC_0_Counter_get()
        
__VERIFIER_atomic_begin();
TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
        TransformAlarmC_0_to_size_type now = rv; //TransformAlarmC_0_Counter_get();
TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
        TransformAlarmC_0_to_size_type expires;
TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
        TransformAlarmC_0_to_size_type remaining;
TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
        /* IRQ INSTR 12 */
        //  if ((_R2 & 0x0008) != 0x0000) { _R2 &= 0xfff7; sig_TIMERB0_VECTOR(); _R2 |= 0x0008; }
__VERIFIER_atomic_begin();
TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
        expires = TransformAlarmC_0_m_t0 + TransformAlarmC_0_m_dt;
TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
        remaining = ( TransformAlarmC_0_to_size_type )(expires - now);
TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
        /* IRQ INSTR 15 */
        //  if ((_R2 & 0x0008) != 0x0000) { _R2 &= 0xfff7; sig_TIMERB0_VECTOR(); _R2 |= 0x0008; }
        // Lihao: lift if
__VERIFIER_atomic_begin();
TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
        TransformAlarmC_0_to_size_type tmp_TransformAlarmC_0_m_t0 = TransformAlarmC_0_m_t0;   
TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
        if(tmp_TransformAlarmC_0_m_t0 <= now) {
__VERIFIER_atomic_TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
        /* IRQ INSTR 13 */
        //  if ((_R2 & 0x0008) != 0x0000) { _R2 &= 0xfff7; sig_TIMERB0_VECTOR(); _R2 |= 0x0008; }
        // Lihao: lift if
__VERIFIER_atomic_begin();
TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
          tmp_TransformAlarmC_0_m_t0 = TransformAlarmC_0_m_t0;   
TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
          if((expires >= tmp_TransformAlarmC_0_m_t0) && (expires <= now)) {
__VERIFIER_atomic_TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
            remaining = 0;
TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
          }
__VERIFIER_atomic_TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
        } else {
__VERIFIER_atomic_TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
        /* IRQ INSTR 14 */
        //  if ((_R2 & 0x0008) != 0x0000) { _R2 &= 0xfff7; sig_TIMERB0_VECTOR(); _R2 |= 0x0008; }
        //  Lihao: lift if
__VERIFIER_atomic_begin();
TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
          tmp_TransformAlarmC_0_m_t0 = TransformAlarmC_0_m_t0;   
TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
          if((expires >= tmp_TransformAlarmC_0_m_t0) || (expires <= now)) {
__VERIFIER_atomic_TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
            remaining = 0;
TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
          }
        }

__VERIFIER_atomic_TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
        // Lihao: lift if
__VERIFIER_atomic_begin();
TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
        TransformAlarmC_0_to_size_type tmp_TransformAlarmC_0_MAX_DELAY = TransformAlarmC_0_MAX_DELAY;
TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
        if(remaining > tmp_TransformAlarmC_0_MAX_DELAY) {
__VERIFIER_atomic_TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
          TransformAlarmC_0_m_t0 = now + TransformAlarmC_0_MAX_DELAY;
TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
          TransformAlarmC_0_m_dt = remaining - TransformAlarmC_0_MAX_DELAY;
TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
          remaining = TransformAlarmC_0_MAX_DELAY;
TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
        } else {
__VERIFIER_atomic_TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
        /* IRQ INSTR 16 */
        //  if ((_R2 & 0x0008) != 0x0000) { _R2 &= 0xfff7; sig_TIMERB0_VECTOR(); _R2 |= 0x0008; }
__VERIFIER_atomic_begin();
TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
          TransformAlarmC_0_m_t0 += TransformAlarmC_0_m_dt;
TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
          TransformAlarmC_0_m_dt = 0;
TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
        }

        // inline
        // TransformAlarmC_0_AlarmFrom_startAt(( TransformAlarmC_0_from_size_type )(now) << 5, ( TransformAlarmC_0_from_size_type )(remaining) << 5);
__VERIFIER_atomic_TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
        uint16_t t0 = ( TransformAlarmC_0_from_size_type )(now) << 5;
TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
        uint16_t dt =  ( TransformAlarmC_0_from_size_type )(remaining) << 5;
TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
        //uint16_t now = Msp430AlarmC_0_Msp430Timer_get();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
        now = Msp430AlarmC_0_Msp430Timer_get();
TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
        uint16_t elapsed = now - t0;
TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
        if(elapsed >= dt) {
__VERIFIER_atomic_TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
          Msp430AlarmC_0_Msp430Compare_setEventFromNow(2);
TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
        } else {
__VERIFIER_atomic_TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
          uint16_t remaining = dt - elapsed;
TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
          if(remaining <= 2) {
__VERIFIER_atomic_TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
            Msp430AlarmC_0_Msp430Compare_setEventFromNow(2);
TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
          } else {
__VERIFIER_atomic_TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
            Msp430AlarmC_0_Msp430Compare_setEvent(now + remaining);
TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
          }
        }
__VERIFIER_atomic_TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
        Msp430AlarmC_0_Msp430TimerControl_clearPendingInterrupt();
TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
        Msp430AlarmC_0_Msp430TimerControl_enableEvents();
TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
        // end of inline:  TransformAlarmC_0_AlarmFrom_startAt

        // end of inline: TransformAlarmC_0_set_alarm();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
      __nesc_atomic_end(__nesc_atomic); 
TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_VirtualizeTimerC_0_updateFromTimer_runTask();
      // end of inline: AlarmToTimerC_0_Alarm_startAt(now, min_remaining);
      // end of inline: VirtualizeTimerC_0_TimerFrom_startOneShotAt(now, min_remaining);
    }
  }
__VERIFIER_atomic_TRANS_VirtualizeTimerC_0_updateFromTimer_runTask_leave_thread();
  __CPROVER_atomic_end();
}

static void AlarmToTimerC_0_fired_runTask(void) {
  __CPROVER_atomic_begin();
__VERIFIER_atomic_TRANS_AlarmToTimerC_0_fired_runTask_enter_thread();
  //test = 1; // Lihao
  if(AlarmToTimerC_0_m_oneshot == FALSE) {
    // inline
    //AlarmToTimerC_0_start(AlarmToTimerC_0_Alarm_getAlarm(), AlarmToTimerC_0_m_dt, FALSE);
    // inline: TransformAlarmC_0_Alarm_getAlarm()
    /* IRQ INSTR 5 */
    //  if ((_R2 & 0x0008) != 0x0000) { _R2 &= 0xfff7; sig_TIMERB0_VECTOR(); _R2 |= 0x0008; }
    __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
    /* IRQ INSTR 4 */
    //  if ((_R2 & 0x0008) != 0x0000) { _R2 &= 0xfff7; sig_TIMERB0_VECTOR(); _R2 |= 0x0008; }
    TransformAlarmC_0_to_size_type __nesc_temp = TransformAlarmC_0_m_t0 + TransformAlarmC_0_m_dt;
    __nesc_atomic_end(__nesc_atomic);
    // end of inline: TransformAlarmC_0_Alarm_getAlarm()

    // inline: AlarmToTimerC_0_start(__nesc_temp, AlarmToTimerC_0_m_dt, FALSE);
    //AlarmToTimerC_0_m_dt = AlarmToTimerC_0_m_dt;
    AlarmToTimerC_0_m_oneshot = FALSE;
    // inline
    // AlarmToTimerC_0_Alarm_startAt(__nesc_temp, AlarmToTimerC_0_m_dt);
    /* IRQ INSTR 19 */
    //  if ((_R2 & 0x0008) != 0x0000) { _R2 &= 0xfff7; sig_TIMERB0_VECTOR(); _R2 |= 0x0008; }
    
    __nesc_atomic_t __nesc_atomic2 = __nesc_atomic_start(); 
      TransformAlarmC_0_m_t0 = __nesc_temp;
      TransformAlarmC_0_m_dt = AlarmToTimerC_0_m_dt;
    
      // inline
      //TransformAlarmC_0_set_alarm();
      // inline: TransformAlarmC_0_Counter_get()
      TransformCounterC_0_to_size_type rv = 0;
      /* IRQ INSTR 17 */
      //  if ((_R2 & 0x0008) != 0x0000) { _R2 &= 0xfff7; sig_TIMERB0_VECTOR(); _R2 |= 0x0008; }
      __nesc_atomic_t __nesc_atomic3 = __nesc_atomic_start();
      TransformCounterC_0_upper_count_type high = TransformCounterC_0_m_upper;
      TransformCounterC_0_from_size_type low = TransformCounterC_0_CounterFrom_get();
      if(TransformCounterC_0_CounterFrom_isOverflowPending()) {
        high++;
        low = TransformCounterC_0_CounterFrom_get();
      }
      TransformCounterC_0_to_size_type high_to = high;
      TransformCounterC_0_to_size_type low_to = low >> TransformCounterC_0_LOW_SHIFT_RIGHT;
      rv = (high_to << TransformCounterC_0_HIGH_SHIFT_LEFT) | low_to;
      __nesc_atomic_end(__nesc_atomic3);
      // end of inline: TransformAlarmC_0_Counter_get()
      
      TransformAlarmC_0_to_size_type now = rv; //TransformAlarmC_0_Counter_get();
      TransformAlarmC_0_to_size_type expires;
      TransformAlarmC_0_to_size_type remaining;
      /* IRQ INSTR 12 */
      //  if ((_R2 & 0x0008) != 0x0000) { _R2 &= 0xfff7; sig_TIMERB0_VECTOR(); _R2 |= 0x0008; }
      expires = TransformAlarmC_0_m_t0 + TransformAlarmC_0_m_dt;
      remaining = ( TransformAlarmC_0_to_size_type )(expires - now);
      /* IRQ INSTR 15 */
      //  if ((_R2 & 0x0008) != 0x0000) { _R2 &= 0xfff7; sig_TIMERB0_VECTOR(); _R2 |= 0x0008; }
      if(TransformAlarmC_0_m_t0 <= now) {
      /* IRQ INSTR 13 */
      //  if ((_R2 & 0x0008) != 0x0000) { _R2 &= 0xfff7; sig_TIMERB0_VECTOR(); _R2 |= 0x0008; }
        if((expires >= TransformAlarmC_0_m_t0) && (expires <= now)) {
          remaining = 0;
        }
      } else {
      /* IRQ INSTR 14 */
      //  if ((_R2 & 0x0008) != 0x0000) { _R2 &= 0xfff7; sig_TIMERB0_VECTOR(); _R2 |= 0x0008; }
        if((expires >= TransformAlarmC_0_m_t0) || (expires <= now)) {
          remaining = 0;
        }
      }

      if(remaining > TransformAlarmC_0_MAX_DELAY) {
        TransformAlarmC_0_m_t0 = now + TransformAlarmC_0_MAX_DELAY;
        TransformAlarmC_0_m_dt = remaining - TransformAlarmC_0_MAX_DELAY;
        remaining = TransformAlarmC_0_MAX_DELAY;
      } else {
      /* IRQ INSTR 16 */
      //  if ((_R2 & 0x0008) != 0x0000) { _R2 &= 0xfff7; sig_TIMERB0_VECTOR(); _R2 |= 0x0008; }
        TransformAlarmC_0_m_t0 += TransformAlarmC_0_m_dt;
        TransformAlarmC_0_m_dt = 0;
      }

      // inline
      // TransformAlarmC_0_AlarmFrom_startAt(( TransformAlarmC_0_from_size_type )(now) << 5, ( TransformAlarmC_0_from_size_type )(remaining) << 5);
      uint16_t t0 = ( TransformAlarmC_0_from_size_type )(now) << 5;
      uint16_t dt =  ( TransformAlarmC_0_from_size_type )(remaining) << 5;
      //uint16_t now = Msp430AlarmC_0_Msp430Timer_get();
      now = Msp430AlarmC_0_Msp430Timer_get();
      uint16_t elapsed = now - t0;
      if(elapsed >= dt) {
        Msp430AlarmC_0_Msp430Compare_setEventFromNow(2);
      } else {
        uint16_t remaining = dt - elapsed;
        if(remaining <= 2) {
          Msp430AlarmC_0_Msp430Compare_setEventFromNow(2);
        } else {
          Msp430AlarmC_0_Msp430Compare_setEvent(now + remaining);
        }
      }
      Msp430AlarmC_0_Msp430TimerControl_clearPendingInterrupt();
      Msp430AlarmC_0_Msp430TimerControl_enableEvents();
      // end of inline:  TransformAlarmC_0_AlarmFrom_startAt

      // end of inline: TransformAlarmC_0_set_alarm();
    __nesc_atomic_end(__nesc_atomic2); 
    // end of inline: AlarmToTimerC_0_Alarm_startAt(__nesc_temp, AlarmToTimerC_0_m_dt);
 
    // end of inline: AlarmToTimerC_0_start(__nesc_temp, AlarmToTimerC_0_m_dt, FALSE);
    // end of inline: AlarmToTimerC_0_start(AlarmToTimerC_0_Alarm_getAlarm(), AlarmToTimerC_0_m_dt, FALSE);
    //assert(test == 1); // Lihao
  }
  // inline
  //AlarmToTimerC_0_Timer_fired(); --> VirtualizeTimerC_0_fireTimers(VirtualizeTimerC_0_TimerFrom_getNow()); 
  // inline: VirtualizeTimerC_0_TimerFrom_getNow()
  TransformCounterC_0_to_size_type now = 0;
    /* IRQ INSTR 17 */
    //  if ((_R2 & 0x0008) != 0x0000) { _R2 &= 0xfff7; sig_TIMERB0_VECTOR(); _R2 |= 0x0008; }
  __nesc_atomic_t __nesc_atomic = __nesc_atomic_start();
    TransformCounterC_0_upper_count_type high = TransformCounterC_0_m_upper;
    TransformCounterC_0_from_size_type low = TransformCounterC_0_CounterFrom_get();

    if(TransformCounterC_0_CounterFrom_isOverflowPending()) {
      high++;
      low = TransformCounterC_0_CounterFrom_get();
    }

    TransformCounterC_0_to_size_type high_to = high;
    TransformCounterC_0_to_size_type low_to = low >> TransformCounterC_0_LOW_SHIFT_RIGHT;
    now = (high_to << TransformCounterC_0_HIGH_SHIFT_LEFT) | low_to;
  __nesc_atomic_end(__nesc_atomic);
  // end of inline: VirtualizeTimerC_0_TimerFrom_getNow()
  
  // inline: VirtualizeTimerC_0_fireTimers(now);
  uint8_t num;
  for(num = 0; num < VirtualizeTimerC_0_NUM_TIMERS; num++) {
    VirtualizeTimerC_0_Timer_t *timer = &VirtualizeTimerC_0_m_timers[num];
    bool isrunning = timer->isrunning;

    if(isrunning) {
      uint32_t elapsed = now - timer->t0;
      //test = 0; assert(test == 0); // Lihao
      if(elapsed >= timer->dt) {
        if(timer->isoneshot) {
          timer->isrunning = FALSE;
          //assert(timer->isrunning == FALSE); //Peter
          __VERIFIER_assert(timer->isrunning == FALSE); //Peter
          //if(timer->isrunning =! FALSE) irq_err(); 
          //test = 0; assert(test == 0); // Lihao
        } else {
          timer->t0 += timer->dt;
        }
        VirtualizeTimerC_0_Timer_fired(num);
          break;
      }
    }
  }

  VirtualizeTimerC_0_updateFromTimer_postTask();
  // end of inline: VirtualizeTimerC_0_fireTimers(now);
  // end of inline: AlarmToTimerC_0_Timer_fired();
__VERIFIER_atomic_TRANS_AlarmToTimerC_0_fired_runTask_leave_thread();
  __CPROVER_atomic_end();
}
