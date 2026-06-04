/* Extracted ISR/task definitions for the improved interleaving pipeline. */

void closer1(void ) {
    __CPROVER_atomic_begin();

    //while(cnt1<LIMIT) {
        tco_write_buf = 'V';
        i8xx_tco_write(1);
        tco_expect_close = 42;
        //i8xx_tco_release();
        cnt1++;
    //}
    __CPROVER_atomic_end();
    return NULL;
}

void closer2(void) {
    __CPROVER_atomic_begin();
    //while(cnt2<LIMIT) {
        tco_write_buf = 'V';
        i8xx_tco_write(1);
        tco_expect_close = 42;
        i8xx_tco_release();
        cnt2++;
    //}
    __CPROVER_atomic_end();
    return NULL;
}

void writer1(void ) {
    __CPROVER_atomic_begin();
    //while(cnt3<LIMIT) {
        i8xx_tco_write(0);
        cnt3++;
    //}
    __CPROVER_atomic_end();
    return NULL;
}

void writer2(void ) {
    __CPROVER_atomic_begin();
    //while(cnt4<LIMIT) {
        i8xx_tco_write(0);
        cnt4++;
    //}
    __CPROVER_atomic_end();
    return NULL;
}
