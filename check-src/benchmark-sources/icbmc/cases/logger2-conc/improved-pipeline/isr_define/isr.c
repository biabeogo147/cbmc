/* Extracted ISR/task definitions for the improved interleaving pipeline. */

void *task_measure(void *args) {
  __CPROVER_atomic_begin();
TRANS_atomic_assume_task_measure();
TRANS_task_measure_enter_thread();
TRANS_atomic_assume_task_measure();
TRANS_atomic_assume_task_measure();
  __VERIFIER_assume(systemState==LOGGING);
TRANS_atomic_assume_task_measure();
TRANS_atomic_assume_task_measure();
TRANS_atomic_assume_task_measure();
  tickCounter++;
TRANS_atomic_assume_task_measure();
TRANS_atomic_assume_task_measure();
  // Lihao: lift if
TRANS_atomic_assume_task_measure();
  uint16_t tmp_tickCounter = tickCounter;
TRANS_atomic_assume_task_measure();
TRANS_atomic_assume_task_measure();
  if (tmp_tickCounter == period) {
  //if (tickCounter == period) {
TRANS_atomic_assume_task_measure();
TRANS_atomic_assume_task_measure();
    uint16_t value = read_sensor_value();
TRANS_atomic_assume_task_measure();
TRANS_atomic_assume_task_measure();
TRANS_atomic_assume_task_measure();
    uint8_t pos = numberOfRecords;
TRANS_atomic_assume_task_measure();
TRANS_atomic_assume_task_measure();
TRANS_atomic_assume_task_measure();
    uint32_t _startTime = startTime;
TRANS_atomic_assume_task_measure();
TRANS_atomic_assume_task_measure();
TRANS_atomic_assume_task_measure();
    uint32_t currentTime = _startTime + period*periodCounter+tickCounter;
TRANS_atomic_assume_task_measure();
TRANS_atomic_assume_task_measure();
TRANS_atomic_assume_task_measure();
    tickCounter = 0;
TRANS_atomic_assume_task_measure();
TRANS_atomic_assume_task_measure();
TRANS_atomic_assume_task_measure();
    periodCounter++;
TRANS_atomic_assume_task_measure();
TRANS_atomic_assume_task_measure();
TRANS_atomic_assume_task_measure();
    records[pos] =  process_value(currentTime,value);
TRANS_atomic_assume_task_measure();
TRANS_atomic_assume_task_measure();
TRANS_atomic_assume_task_measure();
    numberOfRecords++;
TRANS_atomic_assume_task_measure();
TRANS_atomic_assume_task_measure();
TRANS_atomic_assume_task_measure();
    //assert(startTime==_startTime);
    //assert(numberOfRecords==pos+1);
    __VERIFIER_assert(numberOfRecords==pos+1);
    //if (numberOfRecords!=pos+1) irq_err();
TRANS_atomic_assume_task_measure();
TRANS_atomic_assume_task_measure();
  }
TRANS_task_measure_leave_thread();
  __CPROVER_atomic_end();
}

void *task_ext_power(void *args) {
  __CPROVER_atomic_begin();
TRANS_atomic_assume_task_ext_power();
TRANS_task_ext_power_enter_thread();
TRANS_atomic_assume_task_ext_power();
TRANS_atomic_assume_task_ext_power();
  uint8_t power = get_power_status();
TRANS_atomic_assume_task_ext_power();
TRANS_atomic_assume_task_ext_power();
  // Lihao: lift if
TRANS_atomic_assume_task_ext_power();
  uint8_t tmp_systemState = systemState;
TRANS_atomic_assume_task_ext_power();
TRANS_atomic_assume_task_ext_power();
  if(power && tmp_systemState==SLEEP) {
  //if(power && systemState==SLEEP) {
TRANS_atomic_assume_task_ext_power();
TRANS_atomic_assume_task_ext_power();
    systemState = IDLE;
TRANS_atomic_assume_task_ext_power();
TRANS_atomic_assume_task_ext_power();
  }

TRANS_atomic_assume_task_ext_power();
   // Lihao: lift if
TRANS_atomic_assume_task_ext_power();
  tmp_systemState = systemState;
TRANS_atomic_assume_task_ext_power();
TRANS_atomic_assume_task_ext_power();
  if(!power && tmp_systemState==IDLE) {
  //if(!power && systemState==IDLE) {
TRANS_atomic_assume_task_ext_power();
TRANS_atomic_assume_task_ext_power();
    systemState = SLEEP;
TRANS_atomic_assume_task_ext_power();
TRANS_atomic_assume_task_ext_power();
  }
TRANS_task_ext_power_leave_thread();
  __CPROVER_atomic_end();
}

void *task_communicate(void *args) {
  __CPROVER_atomic_begin();
//void task_communicate(void) {
TRANS_atomic_assume_task_communicate();
TRANS_task_communicate_enter_thread();
TRANS_atomic_assume_task_communicate();
TRANS_atomic_assume_task_communicate();
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
  uint8_t tmp_systemState; // Lihao: lift if
  uint8_t tmp_numberOfRecords; // Lihao: lift if
  __VERIFIER_assume(systemState!=SLEEP);
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
TRANS_atomic_assume_task_communicate();
TRANS_atomic_assume_task_communicate();
  // Lihao: inline
  //uint8_t len = receive_cmd(msgBuffer);
TRANS_atomic_assume_task_communicate();
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
  msgBuffer[0] = nondet_uint8();
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
TRANS_atomic_assume_task_communicate();
TRANS_atomic_assume_task_communicate();
TRANS_atomic_assume_task_communicate();
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
  msgBuffer[1] = nondet_uint8();
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
TRANS_atomic_assume_task_communicate();
TRANS_atomic_assume_task_communicate();
TRANS_atomic_assume_task_communicate();
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
  msgBuffer[2] = nondet_uint8();
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
TRANS_atomic_assume_task_communicate();
TRANS_atomic_assume_task_communicate();
TRANS_atomic_assume_task_communicate();
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
  msgBuffer[3] = nondet_uint8();
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
TRANS_atomic_assume_task_communicate();
TRANS_atomic_assume_task_communicate();
TRANS_atomic_assume_task_communicate();
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
  msgBuffer[4] = nondet_uint8();
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
TRANS_atomic_assume_task_communicate();
TRANS_atomic_assume_task_communicate();
TRANS_atomic_assume_task_communicate();
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
  msgBuffer[5] = nondet_uint8();
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
TRANS_atomic_assume_task_communicate();
TRANS_atomic_assume_task_communicate();
TRANS_atomic_assume_task_communicate();
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
  msgBuffer[6] = nondet_uint8();
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
TRANS_atomic_assume_task_communicate();
TRANS_atomic_assume_task_communicate();
TRANS_atomic_assume_task_communicate();
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
  uint8_t cmd = msgBuffer[0];
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
TRANS_atomic_assume_task_communicate();
TRANS_atomic_assume_task_communicate();
TRANS_atomic_assume_task_communicate();
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
  uint8_t decodingStatus = CMD_DEC_ERROR;
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
TRANS_atomic_assume_task_communicate();
TRANS_atomic_assume_task_communicate();
  if(cmd==CMD_STOP || cmd==CMD_READ_STATE || cmd==CMD_READ_DATA ||
     cmd==CMD_RESTART) {
TRANS_atomic_assume_task_communicate();
TRANS_atomic_assume_task_communicate();
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
    decodingStatus = CMD_DEC_OK;
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
TRANS_atomic_assume_task_communicate();
TRANS_atomic_assume_task_communicate();
  }
TRANS_atomic_assume_task_communicate();
  if (decodingStatus != CMD_DEC_OK) {
TRANS_atomic_assume_task_communicate();
TRANS_atomic_assume_task_communicate();
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
    msgBuffer[0] = RSP_ERROR;
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
TRANS_atomic_assume_task_communicate();
TRANS_atomic_assume_task_communicate();
TRANS_atomic_assume_task_communicate();
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
    send_response(msgBuffer,1);
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
TRANS_atomic_assume_task_communicate();
TRANS_atomic_assume_task_communicate();
  } else {
TRANS_atomic_assume_task_communicate();
TRANS_atomic_assume_task_communicate();
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
    uint8_t rspStatus = RSP_SUCCESS;
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
TRANS_atomic_assume_task_communicate();
TRANS_atomic_assume_task_communicate();
    switch(cmd) {
      case CMD_STOP:
TRANS_atomic_assume_task_communicate();
// Lihao: lift if
TRANS_atomic_assume_task_communicate();
  tmp_systemState = systemState;
TRANS_atomic_assume_task_communicate();
TRANS_atomic_assume_task_communicate();
        if (tmp_systemState != LOGGING) {
TRANS_atomic_assume_task_communicate();
TRANS_atomic_assume_task_communicate();
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
          rspStatus = RSP_ERROR;
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
TRANS_atomic_assume_task_communicate();
TRANS_atomic_assume_task_communicate();
        } else {
TRANS_atomic_assume_task_communicate();
TRANS_atomic_assume_task_communicate();
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
          systemState = IDLE;
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
TRANS_atomic_assume_task_communicate();
TRANS_atomic_assume_task_communicate();
        }
TRANS_atomic_assume_task_communicate();
TRANS_atomic_assume_task_communicate();
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
        msgBuffer[0] = rspStatus;
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
TRANS_atomic_assume_task_communicate();
TRANS_atomic_assume_task_communicate();
// Lihao: lift if
TRANS_atomic_assume_task_communicate();
  tmp_systemState = systemState;
TRANS_atomic_assume_task_communicate();
TRANS_atomic_assume_task_communicate();
        if(tmp_systemState==SLEEP) {
TRANS_atomic_assume_task_communicate();
goto task_communicate_exit;
        }
TRANS_atomic_assume_task_communicate();
TRANS_atomic_assume_task_communicate();
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
        send_response(msgBuffer,1);
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
TRANS_atomic_assume_task_communicate();
TRANS_atomic_assume_task_communicate();
        break;
      case CMD_READ_STATE:
TRANS_atomic_assume_task_communicate();
TRANS_atomic_assume_task_communicate();
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
        msgBuffer[0] = rspStatus;
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
TRANS_atomic_assume_task_communicate();
TRANS_atomic_assume_task_communicate();
TRANS_atomic_assume_task_communicate();
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
        msgBuffer[1] = systemState;
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
TRANS_atomic_assume_task_communicate();
TRANS_atomic_assume_task_communicate();
TRANS_atomic_assume_task_communicate();
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
        msgBuffer[2] = numberOfRecords;
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
TRANS_atomic_assume_task_communicate();
TRANS_atomic_assume_task_communicate();
	// Lihao: inline
        //put_uint32(msgBuffer,3,startTime);
TRANS_atomic_assume_task_communicate();
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
   	msgBuffer[3] = (uint8_t)(startTime>>24);
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
TRANS_atomic_assume_task_communicate();
TRANS_atomic_assume_task_communicate();
TRANS_atomic_assume_task_communicate();
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
  	msgBuffer[4] = (uint8_t)(startTime>>16);
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
TRANS_atomic_assume_task_communicate();
TRANS_atomic_assume_task_communicate();
TRANS_atomic_assume_task_communicate();
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
  	msgBuffer[5] = (uint8_t)(startTime>>8);
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
TRANS_atomic_assume_task_communicate();
TRANS_atomic_assume_task_communicate();
TRANS_atomic_assume_task_communicate();
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
  	msgBuffer[6] = (uint8_t)startTime;
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
TRANS_atomic_assume_task_communicate();
TRANS_atomic_assume_task_communicate();
// Lihao: lift if
TRANS_atomic_assume_task_communicate();
  tmp_systemState = systemState;
TRANS_atomic_assume_task_communicate();
TRANS_atomic_assume_task_communicate();
        if(tmp_systemState==SLEEP) {
TRANS_atomic_assume_task_communicate();
goto task_communicate_exit;
        }
TRANS_atomic_assume_task_communicate();
TRANS_atomic_assume_task_communicate();
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
        send_response(msgBuffer,7);
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
TRANS_atomic_assume_task_communicate();
TRANS_atomic_assume_task_communicate();
	break;
      case CMD_READ_DATA: {
TRANS_atomic_assume_task_communicate();
TRANS_atomic_assume_task_communicate();
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
        uint8_t pos = msgBuffer[1];
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
TRANS_atomic_assume_task_communicate();
TRANS_atomic_assume_task_communicate();
   // Lihao: lift if
TRANS_atomic_assume_task_communicate();
        tmp_numberOfRecords = numberOfRecords;
TRANS_atomic_assume_task_communicate();
TRANS_atomic_assume_task_communicate();
        if(pos>=tmp_numberOfRecords) {
TRANS_atomic_assume_task_communicate();
TRANS_atomic_assume_task_communicate();
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
          msgBuffer[0] = RSP_ERROR;
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
TRANS_atomic_assume_task_communicate();
TRANS_atomic_assume_task_communicate();
// Lihao: lift if
TRANS_atomic_assume_task_communicate();
  tmp_systemState = systemState;
TRANS_atomic_assume_task_communicate();
TRANS_atomic_assume_task_communicate();
          if(tmp_systemState==SLEEP) {
TRANS_atomic_assume_task_communicate();
goto task_communicate_exit;
          }
TRANS_atomic_assume_task_communicate();
TRANS_atomic_assume_task_communicate();
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
          send_response(msgBuffer,1);
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
TRANS_atomic_assume_task_communicate();
TRANS_atomic_assume_task_communicate();
  	} else {
TRANS_atomic_assume_task_communicate();
TRANS_atomic_assume_task_communicate();
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
          msgBuffer[0] = RSP_SUCCESS;
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
TRANS_atomic_assume_task_communicate();
TRANS_atomic_assume_task_communicate();
	  // Lihao: inline
          //put_uint16(msgBuffer,1,records[pos]);
TRANS_atomic_assume_task_communicate();
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
          msgBuffer[1] = (uint8_t)(records[pos]>>8);
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
TRANS_atomic_assume_task_communicate();
TRANS_atomic_assume_task_communicate();
TRANS_atomic_assume_task_communicate();
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
          msgBuffer[2] = (uint8_t)records[pos];
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
TRANS_atomic_assume_task_communicate();
TRANS_atomic_assume_task_communicate();
// Lihao: lift if
TRANS_atomic_assume_task_communicate();
  tmp_systemState = systemState;
TRANS_atomic_assume_task_communicate();
TRANS_atomic_assume_task_communicate();
          if(tmp_systemState==SLEEP) {
TRANS_atomic_assume_task_communicate();
goto task_communicate_exit;
          }
TRANS_atomic_assume_task_communicate();
TRANS_atomic_assume_task_communicate();
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
          send_response(msgBuffer,3);
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
TRANS_atomic_assume_task_communicate();
TRANS_atomic_assume_task_communicate();
	}
	break;
      }
      case CMD_RESTART: {
TRANS_atomic_assume_task_communicate();
TRANS_atomic_assume_task_communicate();
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
        uint32_t _startTime = get_uint32(msgBuffer,1);
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
TRANS_atomic_assume_task_communicate();
TRANS_atomic_assume_task_communicate();
TRANS_atomic_assume_task_communicate();
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
        uint16_t _period = get_uint16(msgBuffer,5);
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
TRANS_atomic_assume_task_communicate();
TRANS_atomic_assume_task_communicate();
	// Lihao: inline
        //restart(_startTime,_period);
    // Lihao: lift if
TRANS_atomic_assume_task_communicate();
        tmp_numberOfRecords = numberOfRecords;
TRANS_atomic_assume_task_communicate();
TRANS_atomic_assume_task_communicate();
        if (tmp_numberOfRecords+1 >= MAX_RECORDS) {
TRANS_atomic_assume_task_communicate();
TRANS_atomic_assume_task_communicate();
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
          systemState = IDLE;
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
TRANS_atomic_assume_task_communicate();
TRANS_atomic_assume_task_communicate();
        }
TRANS_atomic_assume_task_communicate();
TRANS_atomic_assume_task_communicate();
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
  	periodCounter = 0;
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
TRANS_atomic_assume_task_communicate();
TRANS_atomic_assume_task_communicate();
TRANS_atomic_assume_task_communicate();
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
  	tickCounter = 0;
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
TRANS_atomic_assume_task_communicate();
TRANS_atomic_assume_task_communicate();
TRANS_atomic_assume_task_communicate();
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
  	numberOfRecords = 0;
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
TRANS_atomic_assume_task_communicate();
TRANS_atomic_assume_task_communicate();
TRANS_atomic_assume_task_communicate();
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
  	startTime = _startTime;
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
TRANS_atomic_assume_task_communicate();
TRANS_atomic_assume_task_communicate();
TRANS_atomic_assume_task_communicate();
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
  	period = _period;
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
TRANS_atomic_assume_task_communicate();
TRANS_atomic_assume_task_communicate();
TRANS_atomic_assume_task_communicate();
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
  	systemState = LOGGING;
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
TRANS_atomic_assume_task_communicate();
TRANS_atomic_assume_task_communicate();
TRANS_atomic_assume_task_communicate();
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
        msgBuffer[0] = rspStatus;
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
TRANS_atomic_assume_task_communicate();
TRANS_atomic_assume_task_communicate();
  // Lihao: lift if
TRANS_atomic_assume_task_communicate();
  tmp_systemState = systemState;
TRANS_atomic_assume_task_communicate();
TRANS_atomic_assume_task_communicate();
        if(tmp_systemState==SLEEP) {
TRANS_atomic_assume_task_communicate();
goto task_communicate_exit;
        }
TRANS_atomic_assume_task_communicate();
TRANS_atomic_assume_task_communicate();
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
        send_response(msgBuffer,1);
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
TRANS_atomic_assume_task_communicate();
TRANS_atomic_assume_task_communicate();
        break;
      }
      default:
TRANS_atomic_assume_task_communicate();
        break;
    }
  }
task_communicate_exit:
TRANS_task_communicate_leave_thread();
  __CPROVER_atomic_end();
  return NULL;
}

void *task_communicate2(void *args) {
  __CPROVER_atomic_begin();
//void task_communicate2(void) {
TRANS_atomic_assume_task_communicate2();
TRANS_task_communicate2_enter_thread();
TRANS_atomic_assume_task_communicate2();
TRANS_atomic_assume_task_communicate2();
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
  uint8_t tmp_systemState; // Lihao: lift if
  uint8_t tmp_numberOfRecords; // Lihao: lift if
  __VERIFIER_assume(systemState!=SLEEP);
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
TRANS_atomic_assume_task_communicate2();
TRANS_atomic_assume_task_communicate2();
  // Lihao: inline
  //uint8_t len = receive_cmd(msgBuffer);
TRANS_atomic_assume_task_communicate2();
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
  msgBuffer[0] = nondet_uint8();
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
TRANS_atomic_assume_task_communicate2();
TRANS_atomic_assume_task_communicate2();
TRANS_atomic_assume_task_communicate2();
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
  msgBuffer[1] = nondet_uint8();
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
TRANS_atomic_assume_task_communicate2();
TRANS_atomic_assume_task_communicate2();
TRANS_atomic_assume_task_communicate2();
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
  msgBuffer[2] = nondet_uint8();
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
TRANS_atomic_assume_task_communicate2();
TRANS_atomic_assume_task_communicate2();
TRANS_atomic_assume_task_communicate2();
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
  msgBuffer[3] = nondet_uint8();
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
TRANS_atomic_assume_task_communicate2();
TRANS_atomic_assume_task_communicate2();
TRANS_atomic_assume_task_communicate2();
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
  msgBuffer[4] = nondet_uint8();
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
TRANS_atomic_assume_task_communicate2();
TRANS_atomic_assume_task_communicate2();
TRANS_atomic_assume_task_communicate2();
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
  msgBuffer[5] = nondet_uint8();
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
TRANS_atomic_assume_task_communicate2();
TRANS_atomic_assume_task_communicate2();
TRANS_atomic_assume_task_communicate2();
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
  msgBuffer[6] = nondet_uint8();
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
TRANS_atomic_assume_task_communicate2();
TRANS_atomic_assume_task_communicate2();
TRANS_atomic_assume_task_communicate2();
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
  uint8_t cmd = msgBuffer[0];
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
TRANS_atomic_assume_task_communicate2();
TRANS_atomic_assume_task_communicate2();
TRANS_atomic_assume_task_communicate2();
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
  uint8_t decodingStatus = CMD_DEC_ERROR;
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
TRANS_atomic_assume_task_communicate2();
TRANS_atomic_assume_task_communicate2();
  if(cmd==CMD_STOP || cmd==CMD_READ_STATE || cmd==CMD_READ_DATA ||
     cmd==CMD_RESTART) {
TRANS_atomic_assume_task_communicate2();
TRANS_atomic_assume_task_communicate2();
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
    decodingStatus = CMD_DEC_OK;
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
TRANS_atomic_assume_task_communicate2();
TRANS_atomic_assume_task_communicate2();
  }
TRANS_atomic_assume_task_communicate2();
  if (decodingStatus != CMD_DEC_OK) {
TRANS_atomic_assume_task_communicate2();
TRANS_atomic_assume_task_communicate2();
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
    msgBuffer[0] = RSP_ERROR;
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
TRANS_atomic_assume_task_communicate2();
TRANS_atomic_assume_task_communicate2();
TRANS_atomic_assume_task_communicate2();
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
    send_response(msgBuffer,1);
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
TRANS_atomic_assume_task_communicate2();
TRANS_atomic_assume_task_communicate2();
  } else {
TRANS_atomic_assume_task_communicate2();
TRANS_atomic_assume_task_communicate2();
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
    uint8_t rspStatus = RSP_SUCCESS;
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
TRANS_atomic_assume_task_communicate2();
TRANS_atomic_assume_task_communicate2();
    switch(cmd) {
      case CMD_STOP:
TRANS_atomic_assume_task_communicate2();
// Lihao: lift if
TRANS_atomic_assume_task_communicate2();
  tmp_systemState = systemState;
TRANS_atomic_assume_task_communicate2();
TRANS_atomic_assume_task_communicate2();
        if (tmp_systemState != LOGGING) {
TRANS_atomic_assume_task_communicate2();
TRANS_atomic_assume_task_communicate2();
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
          rspStatus = RSP_ERROR;
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
TRANS_atomic_assume_task_communicate2();
TRANS_atomic_assume_task_communicate2();
        } else {
TRANS_atomic_assume_task_communicate2();
TRANS_atomic_assume_task_communicate2();
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
          systemState = IDLE;
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
TRANS_atomic_assume_task_communicate2();
TRANS_atomic_assume_task_communicate2();
        }
TRANS_atomic_assume_task_communicate2();
TRANS_atomic_assume_task_communicate2();
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
        msgBuffer[0] = rspStatus;
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
TRANS_atomic_assume_task_communicate2();
TRANS_atomic_assume_task_communicate2();
// Lihao: lift if
TRANS_atomic_assume_task_communicate2();
  tmp_systemState = systemState;
TRANS_atomic_assume_task_communicate2();
TRANS_atomic_assume_task_communicate2();
        if(tmp_systemState==SLEEP) {
TRANS_atomic_assume_task_communicate2();
goto task_communicate2_exit;
        }
TRANS_atomic_assume_task_communicate2();
TRANS_atomic_assume_task_communicate2();
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
        send_response(msgBuffer,1);
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
TRANS_atomic_assume_task_communicate2();
TRANS_atomic_assume_task_communicate2();
        break;
      case CMD_READ_STATE:
TRANS_atomic_assume_task_communicate2();
TRANS_atomic_assume_task_communicate2();
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
        msgBuffer[0] = rspStatus;
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
TRANS_atomic_assume_task_communicate2();
TRANS_atomic_assume_task_communicate2();
TRANS_atomic_assume_task_communicate2();
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
        msgBuffer[1] = systemState;
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
TRANS_atomic_assume_task_communicate2();
TRANS_atomic_assume_task_communicate2();
TRANS_atomic_assume_task_communicate2();
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
        msgBuffer[2] = numberOfRecords;
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
TRANS_atomic_assume_task_communicate2();
TRANS_atomic_assume_task_communicate2();
	// Lihao: inline
        //put_uint32(msgBuffer,3,startTime);
TRANS_atomic_assume_task_communicate2();
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
   	msgBuffer[3] = (uint8_t)(startTime>>24);
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
TRANS_atomic_assume_task_communicate2();
TRANS_atomic_assume_task_communicate2();
TRANS_atomic_assume_task_communicate2();
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
  	msgBuffer[4] = (uint8_t)(startTime>>16);
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
TRANS_atomic_assume_task_communicate2();
TRANS_atomic_assume_task_communicate2();
TRANS_atomic_assume_task_communicate2();
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
  	msgBuffer[5] = (uint8_t)(startTime>>8);
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
TRANS_atomic_assume_task_communicate2();
TRANS_atomic_assume_task_communicate2();
TRANS_atomic_assume_task_communicate2();
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
  	msgBuffer[6] = (uint8_t)startTime;
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
TRANS_atomic_assume_task_communicate2();
TRANS_atomic_assume_task_communicate2();
// Lihao: lift if
TRANS_atomic_assume_task_communicate2();
  tmp_systemState = systemState;
TRANS_atomic_assume_task_communicate2();
TRANS_atomic_assume_task_communicate2();
        if(tmp_systemState==SLEEP) {
TRANS_atomic_assume_task_communicate2();
goto task_communicate2_exit;
        }
TRANS_atomic_assume_task_communicate2();
TRANS_atomic_assume_task_communicate2();
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
        send_response(msgBuffer,7);
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
TRANS_atomic_assume_task_communicate2();
TRANS_atomic_assume_task_communicate2();
	break;
      case CMD_READ_DATA: {
TRANS_atomic_assume_task_communicate2();
TRANS_atomic_assume_task_communicate2();
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
        uint8_t pos = msgBuffer[1];
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
TRANS_atomic_assume_task_communicate2();
TRANS_atomic_assume_task_communicate2();
   // Lihao: lift if
TRANS_atomic_assume_task_communicate2();
        tmp_numberOfRecords = numberOfRecords;
TRANS_atomic_assume_task_communicate2();
TRANS_atomic_assume_task_communicate2();
        if(pos>=tmp_numberOfRecords) {
TRANS_atomic_assume_task_communicate2();
TRANS_atomic_assume_task_communicate2();
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
          msgBuffer[0] = RSP_ERROR;
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
TRANS_atomic_assume_task_communicate2();
TRANS_atomic_assume_task_communicate2();
// Lihao: lift if
TRANS_atomic_assume_task_communicate2();
  tmp_systemState = systemState;
TRANS_atomic_assume_task_communicate2();
TRANS_atomic_assume_task_communicate2();
          if(tmp_systemState==SLEEP) {
TRANS_atomic_assume_task_communicate2();
goto task_communicate2_exit;
          }
TRANS_atomic_assume_task_communicate2();
TRANS_atomic_assume_task_communicate2();
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
          send_response(msgBuffer,1);
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
TRANS_atomic_assume_task_communicate2();
TRANS_atomic_assume_task_communicate2();
  	} else {
TRANS_atomic_assume_task_communicate2();
TRANS_atomic_assume_task_communicate2();
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
          msgBuffer[0] = RSP_SUCCESS;
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
TRANS_atomic_assume_task_communicate2();
TRANS_atomic_assume_task_communicate2();
	  // Lihao: inline
          //put_uint16(msgBuffer,1,records[pos]);
TRANS_atomic_assume_task_communicate2();
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
          msgBuffer[1] = (uint8_t)(records[pos]>>8);
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
TRANS_atomic_assume_task_communicate2();
TRANS_atomic_assume_task_communicate2();
TRANS_atomic_assume_task_communicate2();
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
          msgBuffer[2] = (uint8_t)records[pos];
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
TRANS_atomic_assume_task_communicate2();
TRANS_atomic_assume_task_communicate2();
// Lihao: lift if
TRANS_atomic_assume_task_communicate2();
  tmp_systemState = systemState;
TRANS_atomic_assume_task_communicate2();
TRANS_atomic_assume_task_communicate2();
          if(tmp_systemState==SLEEP) {
TRANS_atomic_assume_task_communicate2();
goto task_communicate2_exit;
          }
TRANS_atomic_assume_task_communicate2();
TRANS_atomic_assume_task_communicate2();
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
          send_response(msgBuffer,3);
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
TRANS_atomic_assume_task_communicate2();
TRANS_atomic_assume_task_communicate2();
	}
	break;
      }
      case CMD_RESTART: {
TRANS_atomic_assume_task_communicate2();
TRANS_atomic_assume_task_communicate2();
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
        uint32_t _startTime = get_uint32(msgBuffer,1);
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
TRANS_atomic_assume_task_communicate2();
TRANS_atomic_assume_task_communicate2();
TRANS_atomic_assume_task_communicate2();
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
        uint16_t _period = get_uint16(msgBuffer,5);
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
TRANS_atomic_assume_task_communicate2();
TRANS_atomic_assume_task_communicate2();
	// Lihao: inline
        //restart(_startTime,_period);
    // Lihao: lift if
TRANS_atomic_assume_task_communicate2();
        tmp_numberOfRecords = numberOfRecords;
TRANS_atomic_assume_task_communicate2();
TRANS_atomic_assume_task_communicate2();
        if (tmp_numberOfRecords+1 >= MAX_RECORDS) {
TRANS_atomic_assume_task_communicate2();
TRANS_atomic_assume_task_communicate2();
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
          systemState = IDLE;
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
TRANS_atomic_assume_task_communicate2();
TRANS_atomic_assume_task_communicate2();
        }
TRANS_atomic_assume_task_communicate2();
TRANS_atomic_assume_task_communicate2();
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
  	periodCounter = 0;
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
TRANS_atomic_assume_task_communicate2();
TRANS_atomic_assume_task_communicate2();
TRANS_atomic_assume_task_communicate2();
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
  	tickCounter = 0;
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
TRANS_atomic_assume_task_communicate2();
TRANS_atomic_assume_task_communicate2();
TRANS_atomic_assume_task_communicate2();
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
  	numberOfRecords = 0;
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
TRANS_atomic_assume_task_communicate2();
TRANS_atomic_assume_task_communicate2();
TRANS_atomic_assume_task_communicate2();
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
  	startTime = _startTime;
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
TRANS_atomic_assume_task_communicate2();
TRANS_atomic_assume_task_communicate2();
TRANS_atomic_assume_task_communicate2();
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
  	period = _period;
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
TRANS_atomic_assume_task_communicate2();
TRANS_atomic_assume_task_communicate2();
TRANS_atomic_assume_task_communicate2();
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
  	systemState = LOGGING;
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
TRANS_atomic_assume_task_communicate2();
TRANS_atomic_assume_task_communicate2();
TRANS_atomic_assume_task_communicate2();
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
        msgBuffer[0] = rspStatus;
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
TRANS_atomic_assume_task_communicate2();
TRANS_atomic_assume_task_communicate2();
  // Lihao: lift if
TRANS_atomic_assume_task_communicate2();
  tmp_systemState = systemState;
TRANS_atomic_assume_task_communicate2();
TRANS_atomic_assume_task_communicate2();
        if(tmp_systemState==SLEEP) {
TRANS_atomic_assume_task_communicate2();
goto task_communicate2_exit;
        }
TRANS_atomic_assume_task_communicate2();
TRANS_atomic_assume_task_communicate2();
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
        send_response(msgBuffer,1);
//__CPROVER_assume(__TRANS_thread_running[0]==0 && 1);
TRANS_atomic_assume_task_communicate2();
TRANS_atomic_assume_task_communicate2();
        break;
      }
      default:
TRANS_atomic_assume_task_communicate2();
        break;
    }
  }
task_communicate2_exit:
TRANS_task_communicate2_leave_thread();
  __CPROVER_atomic_end();
  return NULL;
}
