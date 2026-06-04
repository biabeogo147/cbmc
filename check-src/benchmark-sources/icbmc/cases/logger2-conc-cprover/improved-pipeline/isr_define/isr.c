/* Extracted ISR/task definitions for the improved interleaving pipeline. */

void task_measure(void) {
  __CPROVER_atomic_begin();
__VERIFIER_atomic_TRANS_task_measure_enter_thread();

  __CPROVER_assume(systemState==LOGGING);
  tickCounter++;

  if (tickCounter == period) {
    uint16_t value = read_sensor_value();
    uint8_t pos = numberOfRecords;
    uint32_t _startTime = startTime;
    uint32_t currentTime = _startTime + period*periodCounter+tickCounter;
 
    tickCounter = 0;
    periodCounter++;
    
    records[pos] =  process_value(currentTime,value);
    numberOfRecords++;
    //assert(startTime==_startTime);
    assert(numberOfRecords==pos+1);
    //if (numberOfRecords!=pos+1) irq_err();
  }

__VERIFIER_atomic_TRANS_task_measure_leave_thread();
  __CPROVER_atomic_end();
}

void task_ext_power(void) {
  __CPROVER_atomic_begin();
__VERIFIER_atomic_TRANS_atomic_assume_task_ext_power();
__VERIFIER_atomic_TRANS_task_ext_power_enter_thread();
__VERIFIER_atomic_TRANS_atomic_assume_task_ext_power();
TRANS_atomic_assume_task_ext_power();
  uint8_t power = get_power_status();
TRANS_atomic_assume_task_ext_power();
__VERIFIER_atomic_TRANS_atomic_assume_task_ext_power();
  // Lihao: lift if
TRANS_atomic_assume_task_ext_power();
  uint8_t tmp_systemState = systemState;
TRANS_atomic_assume_task_ext_power();
__VERIFIER_atomic_TRANS_atomic_assume_task_ext_power();
  if(power && tmp_systemState==SLEEP) {
__VERIFIER_atomic_TRANS_atomic_assume_task_ext_power();
TRANS_atomic_assume_task_ext_power();
    systemState = IDLE;
TRANS_atomic_assume_task_ext_power();
__VERIFIER_atomic_TRANS_atomic_assume_task_ext_power();
  }

__VERIFIER_atomic_TRANS_atomic_assume_task_ext_power();
  // Lihao: lift if 
TRANS_atomic_assume_task_ext_power();
  tmp_systemState = systemState;
TRANS_atomic_assume_task_ext_power();
__VERIFIER_atomic_TRANS_atomic_assume_task_ext_power();
  if(!power && tmp_systemState==IDLE) {
__VERIFIER_atomic_TRANS_atomic_assume_task_ext_power();
TRANS_atomic_assume_task_ext_power();
    systemState = SLEEP;
TRANS_atomic_assume_task_ext_power();
__VERIFIER_atomic_TRANS_atomic_assume_task_ext_power();
  }
__VERIFIER_atomic_TRANS_task_ext_power_leave_thread();
  __CPROVER_atomic_end();
}

void task_communicate(void) {
  __CPROVER_atomic_begin();
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate();
__VERIFIER_atomic_TRANS_task_communicate_enter_thread();
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate();
TRANS_atomic_assume_task_communicate();
  uint8_t tmp_systemState; // Lihao: lift if 
  uint8_t tmp_numberOfRecords; // Lihao: lift if
  __CPROVER_assume(systemState!=SLEEP);
TRANS_atomic_assume_task_communicate();
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate();
  // Lihao: inline 
  //uint8_t len = receive_cmd(msgBuffer);
TRANS_atomic_assume_task_communicate();
  msgBuffer[0] = nondet_uint8();
TRANS_atomic_assume_task_communicate();
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate();
TRANS_atomic_assume_task_communicate();
  msgBuffer[1] = nondet_uint8();
TRANS_atomic_assume_task_communicate();
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate();
TRANS_atomic_assume_task_communicate();
  msgBuffer[2] = nondet_uint8();
TRANS_atomic_assume_task_communicate();
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate();
TRANS_atomic_assume_task_communicate();
  msgBuffer[3] = nondet_uint8();
TRANS_atomic_assume_task_communicate();
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate();
TRANS_atomic_assume_task_communicate();
  msgBuffer[4] = nondet_uint8();
TRANS_atomic_assume_task_communicate();
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate();
TRANS_atomic_assume_task_communicate();
  msgBuffer[5] = nondet_uint8();
TRANS_atomic_assume_task_communicate();
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate();
TRANS_atomic_assume_task_communicate();
  msgBuffer[6] = nondet_uint8();
TRANS_atomic_assume_task_communicate();
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate();
TRANS_atomic_assume_task_communicate();
  uint8_t cmd = msgBuffer[0];
TRANS_atomic_assume_task_communicate();
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate();
TRANS_atomic_assume_task_communicate();
  uint8_t decodingStatus = CMD_DEC_ERROR;
TRANS_atomic_assume_task_communicate();
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate();
  if(cmd==CMD_STOP || cmd==CMD_READ_STATE || cmd==CMD_READ_DATA ||
     cmd==CMD_RESTART) {
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate();
TRANS_atomic_assume_task_communicate();
    decodingStatus = CMD_DEC_OK;
TRANS_atomic_assume_task_communicate();
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate();
  }
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate();
  if (decodingStatus != CMD_DEC_OK) {
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate();
TRANS_atomic_assume_task_communicate();
    msgBuffer[0] = RSP_ERROR;
TRANS_atomic_assume_task_communicate();
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate();
TRANS_atomic_assume_task_communicate();
    send_response(msgBuffer,1);
TRANS_atomic_assume_task_communicate();
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate();
  } else {
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate();
TRANS_atomic_assume_task_communicate();
    uint8_t rspStatus = RSP_SUCCESS;
TRANS_atomic_assume_task_communicate();
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate();
    switch(cmd) {
      case CMD_STOP:   
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate();
// Lihao: lift if
TRANS_atomic_assume_task_communicate();
  tmp_systemState = systemState;
TRANS_atomic_assume_task_communicate();
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate();
        if (tmp_systemState != LOGGING) {
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate();
TRANS_atomic_assume_task_communicate();
          rspStatus = RSP_ERROR;
TRANS_atomic_assume_task_communicate();
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate();
        } else {
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate();
TRANS_atomic_assume_task_communicate();
          systemState = IDLE;
TRANS_atomic_assume_task_communicate();
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate();
        }
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate();
TRANS_atomic_assume_task_communicate();
        msgBuffer[0] = rspStatus;
TRANS_atomic_assume_task_communicate();
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate();
// Lihao: lift if
TRANS_atomic_assume_task_communicate();
  tmp_systemState = systemState;
TRANS_atomic_assume_task_communicate();
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate();
        if(tmp_systemState==SLEEP) {
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate();
__VERIFIER_atomic_TRANS_task_communicate_leave_thread();
          __CPROVER_atomic_end();
  return;
        }
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate();
TRANS_atomic_assume_task_communicate();
        send_response(msgBuffer,1);
TRANS_atomic_assume_task_communicate();
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate();
        break;
      case CMD_READ_STATE:
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate();
TRANS_atomic_assume_task_communicate();
        msgBuffer[0] = rspStatus;
TRANS_atomic_assume_task_communicate();
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate();
TRANS_atomic_assume_task_communicate();
        msgBuffer[1] = systemState;
TRANS_atomic_assume_task_communicate();
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate();
TRANS_atomic_assume_task_communicate();
        msgBuffer[2] = numberOfRecords;
TRANS_atomic_assume_task_communicate();
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate();
	// Lihao: inline
        //put_uint32(msgBuffer,3,startTime);
TRANS_atomic_assume_task_communicate();
   	msgBuffer[3] = (uint8_t)(startTime>>24);
TRANS_atomic_assume_task_communicate();
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate();
TRANS_atomic_assume_task_communicate();
  	msgBuffer[4] = (uint8_t)(startTime>>16);
TRANS_atomic_assume_task_communicate();
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate();
TRANS_atomic_assume_task_communicate();
  	msgBuffer[5] = (uint8_t)(startTime>>8);
TRANS_atomic_assume_task_communicate();
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate();
TRANS_atomic_assume_task_communicate();
  	msgBuffer[6] = (uint8_t)startTime;
TRANS_atomic_assume_task_communicate();
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate();
// Lihao: lift if
TRANS_atomic_assume_task_communicate();
  tmp_systemState = systemState;
TRANS_atomic_assume_task_communicate();
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate();
        if(tmp_systemState==SLEEP) {
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate();
__VERIFIER_atomic_TRANS_task_communicate_leave_thread();
          __CPROVER_atomic_end();
  return;
        }
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate();
TRANS_atomic_assume_task_communicate();
        send_response(msgBuffer,7);
TRANS_atomic_assume_task_communicate();
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate();
	break;
      case CMD_READ_DATA: {
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate();
TRANS_atomic_assume_task_communicate();
        uint8_t pos = msgBuffer[1];
TRANS_atomic_assume_task_communicate();
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate();
   // Lihao: lift if
TRANS_atomic_assume_task_communicate();
        tmp_numberOfRecords = numberOfRecords;
TRANS_atomic_assume_task_communicate();
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate();
        if(pos>=tmp_numberOfRecords) {
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate();
TRANS_atomic_assume_task_communicate();
          msgBuffer[0] = RSP_ERROR;
TRANS_atomic_assume_task_communicate();
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate();
// Lihao: lift if
TRANS_atomic_assume_task_communicate();
  tmp_systemState = systemState;
TRANS_atomic_assume_task_communicate();
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate();
          if(tmp_systemState==SLEEP) {
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate();
__VERIFIER_atomic_TRANS_task_communicate_leave_thread();
            __CPROVER_atomic_end();
  return;
          }
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate();
TRANS_atomic_assume_task_communicate();
          send_response(msgBuffer,1);
TRANS_atomic_assume_task_communicate();
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate();
  	} else {
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate();
TRANS_atomic_assume_task_communicate();
          msgBuffer[0] = RSP_SUCCESS;
TRANS_atomic_assume_task_communicate();
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate();
	  // Lihao: inline
          //put_uint16(msgBuffer,1,records[pos]);
TRANS_atomic_assume_task_communicate();
          msgBuffer[1] = (uint8_t)(records[pos]>>8);
TRANS_atomic_assume_task_communicate();
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate();
TRANS_atomic_assume_task_communicate();
          msgBuffer[2] = (uint8_t)records[pos];
TRANS_atomic_assume_task_communicate();
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate();
// Lihao: lift if
TRANS_atomic_assume_task_communicate();
  tmp_systemState = systemState;
TRANS_atomic_assume_task_communicate();
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate();
          if(tmp_systemState==SLEEP) {
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate();
__VERIFIER_atomic_TRANS_task_communicate_leave_thread();
            __CPROVER_atomic_end();
  return;
          }
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate();
TRANS_atomic_assume_task_communicate();
          send_response(msgBuffer,3);
TRANS_atomic_assume_task_communicate();
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate();
	}
	break;
      }
      case CMD_RESTART: {
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate();
TRANS_atomic_assume_task_communicate();
        uint32_t _startTime = get_uint32(msgBuffer,1);
TRANS_atomic_assume_task_communicate();
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate();
TRANS_atomic_assume_task_communicate();
        uint16_t _period = get_uint16(msgBuffer,5);
TRANS_atomic_assume_task_communicate();
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate();
	// Lihao: inline
        //restart(_startTime,_period);
    // Lihao: lift if
TRANS_atomic_assume_task_communicate();
        tmp_numberOfRecords = numberOfRecords;
TRANS_atomic_assume_task_communicate();
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate();
        if (tmp_numberOfRecords+1 >= MAX_RECORDS) {
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate();
TRANS_atomic_assume_task_communicate();
          systemState = IDLE;
TRANS_atomic_assume_task_communicate();
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate();
        }
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate();
TRANS_atomic_assume_task_communicate();
  	periodCounter = 0;
TRANS_atomic_assume_task_communicate();
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate();
TRANS_atomic_assume_task_communicate();
  	tickCounter = 0;
TRANS_atomic_assume_task_communicate();
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate();
TRANS_atomic_assume_task_communicate();
  	numberOfRecords = 0;
TRANS_atomic_assume_task_communicate();
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate();
TRANS_atomic_assume_task_communicate();
  	startTime = _startTime;
TRANS_atomic_assume_task_communicate();
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate();
TRANS_atomic_assume_task_communicate();
  	period = _period;
TRANS_atomic_assume_task_communicate();
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate();
TRANS_atomic_assume_task_communicate();
  	systemState = LOGGING;
TRANS_atomic_assume_task_communicate();
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate();
TRANS_atomic_assume_task_communicate();
        msgBuffer[0] = rspStatus;
TRANS_atomic_assume_task_communicate();
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate();
  // Lihao: lift if
TRANS_atomic_assume_task_communicate();
  tmp_systemState = systemState;
TRANS_atomic_assume_task_communicate();
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate();
        if(tmp_systemState==SLEEP) {
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate();
__VERIFIER_atomic_TRANS_task_communicate_leave_thread();
          __CPROVER_atomic_end();
  return;
        }
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate();
TRANS_atomic_assume_task_communicate();
        send_response(msgBuffer,1);
TRANS_atomic_assume_task_communicate();
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate();
        break;
      }
      default: 
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate();
        break;
    }
__VERIFIER_atomic_TRANS_task_communicate_leave_thread();
  }
__VERIFIER_atomic_TRANS_task_communicate_leave_thread();
  __CPROVER_atomic_end();
}

void task_communicate2(void) {
  __CPROVER_atomic_begin();
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate2();
__VERIFIER_atomic_TRANS_task_communicate2_enter_thread();
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate2();
TRANS_atomic_assume_task_communicate2();
  uint8_t tmp_systemState; // Lihao: lift if 
  uint8_t tmp_numberOfRecords; // Lihao: lift if
  __CPROVER_assume(systemState!=SLEEP);
TRANS_atomic_assume_task_communicate2();
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate2();
  // Lihao: inline 
  //uint8_t len = receive_cmd(msgBuffer);
TRANS_atomic_assume_task_communicate2();
  msgBuffer[0] = nondet_uint8();
TRANS_atomic_assume_task_communicate2();
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate2();
TRANS_atomic_assume_task_communicate2();
  msgBuffer[1] = nondet_uint8();
TRANS_atomic_assume_task_communicate2();
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate2();
TRANS_atomic_assume_task_communicate2();
  msgBuffer[2] = nondet_uint8();
TRANS_atomic_assume_task_communicate2();
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate2();
TRANS_atomic_assume_task_communicate2();
  msgBuffer[3] = nondet_uint8();
TRANS_atomic_assume_task_communicate2();
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate2();
TRANS_atomic_assume_task_communicate2();
  msgBuffer[4] = nondet_uint8();
TRANS_atomic_assume_task_communicate2();
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate2();
TRANS_atomic_assume_task_communicate2();
  msgBuffer[5] = nondet_uint8();
TRANS_atomic_assume_task_communicate2();
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate2();
TRANS_atomic_assume_task_communicate2();
  msgBuffer[6] = nondet_uint8();
TRANS_atomic_assume_task_communicate2();
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate2();
TRANS_atomic_assume_task_communicate2();
  uint8_t cmd = msgBuffer[0];
TRANS_atomic_assume_task_communicate2();
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate2();
TRANS_atomic_assume_task_communicate2();
  uint8_t decodingStatus = CMD_DEC_ERROR;
TRANS_atomic_assume_task_communicate2();
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate2();
  if(cmd==CMD_STOP || cmd==CMD_READ_STATE || cmd==CMD_READ_DATA ||
     cmd==CMD_RESTART) {
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate2();
TRANS_atomic_assume_task_communicate2();
    decodingStatus = CMD_DEC_OK;
TRANS_atomic_assume_task_communicate2();
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate2();
  }
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate2();
  if (decodingStatus != CMD_DEC_OK) {
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate2();
TRANS_atomic_assume_task_communicate2();
    msgBuffer[0] = RSP_ERROR;
TRANS_atomic_assume_task_communicate2();
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate2();
TRANS_atomic_assume_task_communicate2();
    send_response(msgBuffer,1);
TRANS_atomic_assume_task_communicate2();
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate2();
  } else {
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate2();
TRANS_atomic_assume_task_communicate2();
    uint8_t rspStatus = RSP_SUCCESS;
TRANS_atomic_assume_task_communicate2();
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate2();
    switch(cmd) {
      case CMD_STOP:   
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate2();
// Lihao: lift if
TRANS_atomic_assume_task_communicate2();
  tmp_systemState = systemState;
TRANS_atomic_assume_task_communicate2();
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate2();
        if (tmp_systemState != LOGGING) {
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate2();
TRANS_atomic_assume_task_communicate2();
          rspStatus = RSP_ERROR;
TRANS_atomic_assume_task_communicate2();
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate2();
        } else {
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate2();
TRANS_atomic_assume_task_communicate2();
          systemState = IDLE;
TRANS_atomic_assume_task_communicate2();
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate2();
        }
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate2();
TRANS_atomic_assume_task_communicate2();
        msgBuffer[0] = rspStatus;
TRANS_atomic_assume_task_communicate2();
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate2();
// Lihao: lift if
TRANS_atomic_assume_task_communicate2();
  tmp_systemState = systemState;
TRANS_atomic_assume_task_communicate2();
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate2();
        if(tmp_systemState==SLEEP) {
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate2();
__VERIFIER_atomic_TRANS_task_communicate2_leave_thread();
          __CPROVER_atomic_end();
  return ;
        }
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate2();
TRANS_atomic_assume_task_communicate2();
        send_response(msgBuffer,1);
TRANS_atomic_assume_task_communicate2();
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate2();
        break;
      case CMD_READ_STATE:
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate2();
TRANS_atomic_assume_task_communicate2();
        msgBuffer[0] = rspStatus;
TRANS_atomic_assume_task_communicate2();
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate2();
TRANS_atomic_assume_task_communicate2();
        msgBuffer[1] = systemState;
TRANS_atomic_assume_task_communicate2();
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate2();
TRANS_atomic_assume_task_communicate2();
        msgBuffer[2] = numberOfRecords;
TRANS_atomic_assume_task_communicate2();
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate2();
	// Lihao: inline
        //put_uint32(msgBuffer,3,startTime);
TRANS_atomic_assume_task_communicate2();
   	msgBuffer[3] = (uint8_t)(startTime>>24);
TRANS_atomic_assume_task_communicate2();
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate2();
TRANS_atomic_assume_task_communicate2();
  	msgBuffer[4] = (uint8_t)(startTime>>16);
TRANS_atomic_assume_task_communicate2();
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate2();
TRANS_atomic_assume_task_communicate2();
  	msgBuffer[5] = (uint8_t)(startTime>>8);
TRANS_atomic_assume_task_communicate2();
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate2();
TRANS_atomic_assume_task_communicate2();
  	msgBuffer[6] = (uint8_t)startTime;
TRANS_atomic_assume_task_communicate2();
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate2();
// Lihao: lift if
TRANS_atomic_assume_task_communicate2();
  tmp_systemState = systemState;
TRANS_atomic_assume_task_communicate2();
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate2();
        if(tmp_systemState==SLEEP) {
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate2();
__VERIFIER_atomic_TRANS_task_communicate2_leave_thread();
          __CPROVER_atomic_end();
  return ;
        }
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate2();
TRANS_atomic_assume_task_communicate2();
        send_response(msgBuffer,7);
TRANS_atomic_assume_task_communicate2();
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate2();
	break;
      case CMD_READ_DATA: {
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate2();
TRANS_atomic_assume_task_communicate2();
        uint8_t pos = msgBuffer[1];
TRANS_atomic_assume_task_communicate2();
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate2();
   // Lihao: lift if
TRANS_atomic_assume_task_communicate2();
        tmp_numberOfRecords = numberOfRecords;
TRANS_atomic_assume_task_communicate2();
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate2();
        if(pos>=tmp_numberOfRecords) {
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate2();
TRANS_atomic_assume_task_communicate2();
          msgBuffer[0] = RSP_ERROR;
TRANS_atomic_assume_task_communicate2();
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate2();
// Lihao: lift if
TRANS_atomic_assume_task_communicate2();
  tmp_systemState = systemState;
TRANS_atomic_assume_task_communicate2();
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate2();
          if(tmp_systemState==SLEEP) {
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate2();
__VERIFIER_atomic_TRANS_task_communicate2_leave_thread();
            __CPROVER_atomic_end();
  return ;
          }
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate2();
TRANS_atomic_assume_task_communicate2();
          send_response(msgBuffer,1);
TRANS_atomic_assume_task_communicate2();
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate2();
  	} else {
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate2();
TRANS_atomic_assume_task_communicate2();
          msgBuffer[0] = RSP_SUCCESS;
TRANS_atomic_assume_task_communicate2();
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate2();
	  // Lihao: inline
          //put_uint16(msgBuffer,1,records[pos]);
TRANS_atomic_assume_task_communicate2();
          msgBuffer[1] = (uint8_t)(records[pos]>>8);
TRANS_atomic_assume_task_communicate2();
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate2();
TRANS_atomic_assume_task_communicate2();
          msgBuffer[2] = (uint8_t)records[pos];
TRANS_atomic_assume_task_communicate2();
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate2();
// Lihao: lift if
TRANS_atomic_assume_task_communicate2();
  tmp_systemState = systemState;
TRANS_atomic_assume_task_communicate2();
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate2();
          if(tmp_systemState==SLEEP) {
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate2();
__VERIFIER_atomic_TRANS_task_communicate2_leave_thread();
            __CPROVER_atomic_end();
  return ;
          }
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate2();
TRANS_atomic_assume_task_communicate2();
          send_response(msgBuffer,3);
TRANS_atomic_assume_task_communicate2();
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate2();
	}
	break;
      }
      case CMD_RESTART: {
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate2();
TRANS_atomic_assume_task_communicate2();
        uint32_t _startTime = get_uint32(msgBuffer,1);
TRANS_atomic_assume_task_communicate2();
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate2();
TRANS_atomic_assume_task_communicate2();
        uint16_t _period = get_uint16(msgBuffer,5);
TRANS_atomic_assume_task_communicate2();
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate2();
	// Lihao: inline
        //restart(_startTime,_period);
    // Lihao: lift if
TRANS_atomic_assume_task_communicate2();
        tmp_numberOfRecords = numberOfRecords;
TRANS_atomic_assume_task_communicate2();
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate2();
        if (tmp_numberOfRecords+1 >= MAX_RECORDS) {
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate2();
TRANS_atomic_assume_task_communicate2();
          systemState = IDLE;
TRANS_atomic_assume_task_communicate2();
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate2();
        }
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate2();
TRANS_atomic_assume_task_communicate2();
  	periodCounter = 0;
TRANS_atomic_assume_task_communicate2();
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate2();
TRANS_atomic_assume_task_communicate2();
  	tickCounter = 0;
TRANS_atomic_assume_task_communicate2();
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate2();
TRANS_atomic_assume_task_communicate2();
  	numberOfRecords = 0;
TRANS_atomic_assume_task_communicate2();
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate2();
TRANS_atomic_assume_task_communicate2();
  	startTime = _startTime;
TRANS_atomic_assume_task_communicate2();
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate2();
TRANS_atomic_assume_task_communicate2();
  	period = _period;
TRANS_atomic_assume_task_communicate2();
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate2();
TRANS_atomic_assume_task_communicate2();
  	systemState = LOGGING;
TRANS_atomic_assume_task_communicate2();
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate2();
TRANS_atomic_assume_task_communicate2();
        msgBuffer[0] = rspStatus;
TRANS_atomic_assume_task_communicate2();
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate2();
  // Lihao: lift if
TRANS_atomic_assume_task_communicate2();
  tmp_systemState = systemState;
TRANS_atomic_assume_task_communicate2();
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate2();
        if(tmp_systemState==SLEEP) {
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate2();
__VERIFIER_atomic_TRANS_task_communicate2_leave_thread();
          __CPROVER_atomic_end();
  return ;
        }
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate2();
TRANS_atomic_assume_task_communicate2();
        send_response(msgBuffer,1);
TRANS_atomic_assume_task_communicate2();
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate2();
        break;
      }
      default: 
__VERIFIER_atomic_TRANS_atomic_assume_task_communicate2();
        break;
    }
__VERIFIER_atomic_TRANS_task_communicate2_leave_thread();
  }
__VERIFIER_atomic_TRANS_task_communicate2_leave_thread();
  __CPROVER_atomic_end();
}
