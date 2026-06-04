/* Extracted ISR/task definitions for the improved interleaving pipeline. */

void *closer1(void *unused) {
    __CPROVER_atomic_begin();
    //while(cnt1< LIMIT) {
        tco_write_buf = 'V';
        i8xx_tco_write(1);
        tco_expect_close = 42;
        i8xx_tco_release();
        //cnt1++;
    //}
    __CPROVER_atomic_end();
    return NULL;
}

void *closer2(void *unused) {
    __CPROVER_atomic_begin();
    //while(cnt2<LIMIT) {
        tco_write_buf = 'V';
        i8xx_tco_write(1);
        tco_expect_close = 42;
        i8xx_tco_release();
        //cnt2++;
    //}
    __CPROVER_atomic_end();
    return NULL;
}

void *closer3(void *unused) {
    __CPROVER_atomic_begin();
    //while(cnt3<LIMIT) {
        tco_write_buf = 'V';
        i8xx_tco_write(1);
        tco_expect_close = 42;
        i8xx_tco_release();
        //cnt3++;
    //}
    __CPROVER_atomic_end();
    return NULL;
}

void *writer1(void *unused) {
    __CPROVER_atomic_begin();
    //while(cnt4<LIMIT) {
        i8xx_tco_write(0);
        //cnt4++;
    //}
    __CPROVER_atomic_end();
    return NULL;
}

void *writer2(void *unused) {
    __CPROVER_atomic_begin();
    //while(cnt5<LIMIT) {
        i8xx_tco_write(0);
        //cnt5++;
    //}
    __CPROVER_atomic_end();
    return NULL;
}

void *writer3(void *unused) {
    __CPROVER_atomic_begin();
    //while(cnt6<LIMIT) {
        i8xx_tco_write(0);
        //cnt6++;
    //}
    __CPROVER_atomic_end();
    return NULL;
}

void *writer5(void *unused) {
  __CPROVER_atomic_begin();
  i8xx_tco_write(0);
  __CPROVER_atomic_end();
  return NULL;
}

void *writer6(void *unused) {
  __CPROVER_atomic_begin();
  i8xx_tco_write(0);
  __CPROVER_atomic_end();
  return NULL;
}

void *writer7(void *unused) {
  __CPROVER_atomic_begin();
  i8xx_tco_write(0);
  __CPROVER_atomic_end();
  return NULL;
}

void *writer8(void *unused) {
  __CPROVER_atomic_begin();
  i8xx_tco_write(0);
  __CPROVER_atomic_end();
  return NULL;
}

void *writer9(void *unused) {
  __CPROVER_atomic_begin();
  i8xx_tco_write(0);
  __CPROVER_atomic_end();
  return NULL;
}

void *writer10(void *unused) {
  __CPROVER_atomic_begin();
  i8xx_tco_write(0);
  __CPROVER_atomic_end();
  return NULL;
}

void *writer11(void *unused) {
  __CPROVER_atomic_begin();
  i8xx_tco_write(0);
  __CPROVER_atomic_end();
  return NULL;
}

void *writer12(void *unused) {
  __CPROVER_atomic_begin();
  i8xx_tco_write(0);
  __CPROVER_atomic_end();
  return NULL;
}

void *writer13(void *unused) {
  __CPROVER_atomic_begin();
  i8xx_tco_write(0);
  __CPROVER_atomic_end();
  return NULL;
}

void *writer14(void *unused) {
  __CPROVER_atomic_begin();
  i8xx_tco_write(0);
  __CPROVER_atomic_end();
  return NULL;
}

void *writer15(void *unused) {
  __CPROVER_atomic_begin();
  i8xx_tco_write(0);
  __CPROVER_atomic_end();
  return NULL;
}

void *writer16(void *unused) {
  __CPROVER_atomic_begin();
  i8xx_tco_write(0);
  __CPROVER_atomic_end();
  return NULL;
}

void *writer17(void *unused) {
  __CPROVER_atomic_begin();
  i8xx_tco_write(0);
  __CPROVER_atomic_end();
  return NULL;
}

void *writer18(void *unused) {
  __CPROVER_atomic_begin();
  i8xx_tco_write(0);
  __CPROVER_atomic_end();
  return NULL;
}

void *writer19(void *unused) {
  __CPROVER_atomic_begin();
  i8xx_tco_write(0);
  __CPROVER_atomic_end();
  return NULL;
}

void *writer20(void *unused) {
  __CPROVER_atomic_begin();
  i8xx_tco_write(0);
  __CPROVER_atomic_end();
  return NULL;
}

void *writer21(void *unused) {
  __CPROVER_atomic_begin();
  i8xx_tco_write(0);
  __CPROVER_atomic_end();
  return NULL;
}
