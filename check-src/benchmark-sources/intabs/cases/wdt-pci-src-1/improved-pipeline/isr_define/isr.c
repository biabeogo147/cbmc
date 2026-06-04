/* Extracted ISR/task definitions for the improved interleaving pipeline. */

void *closer1(void *unused) {
    __CPROVER_atomic_begin();

    //while(cnt1 < LIMIT) {
        wdtpci_write_buf = 'V';
        expect_close = 42;
        count = 1;
        // function inline 
        if (count) { 
            if (!nowayout) { 
                /* note: just in case someone wrote the magic character
                 * five months ago... */ 
                //expect_close = 0; 
                /* markus: originally, the buffer would be looped-over here */
                if (wdtpci_write_buf != 'V') { 
                    expect_close = 0;
                } 
            } 
        } 

        // function inline wdtpci_release
        if (expect_close != 42) {
            assert(0);
        } else {
            /* printk(KERN_CRIT PFX "Unexpected close, not stopping timer!"); */
            wdtpci_stop();
        }
        expect_close = 0;
        //up(open_sem);
        //cnt1++;
    //}
    __CPROVER_atomic_end();
    return NULL;
}

void *closer2(void *unused) {
    __CPROVER_atomic_begin();

    //while(cnt2 < LIMIT) {
        wdtpci_write_buf = 'V';
        expect_close = 42;
        count = 1;
        // function inline 
        if (count) { 
            if (!nowayout) { 
                /* note: just in case someone wrote the magic character
                 * five months ago... */ 
                //expect_close = 0; 
                /* markus: originally, the buffer would be looped-over here */ \
                if (wdtpci_write_buf != 'V') { 
                    expect_close = 0;
                } 
            } 
        } 

        // function inline wdtpci_release
        if (expect_close != 42) {
            assert(0);
        } else {
            /* printk(KERN_CRIT PFX "Unexpected close, not stopping timer!"); */ \
                wdtpci_stop();
        }
        expect_close = 0;
        //up(open_sem);
        //cnt2++;
    //}
    __CPROVER_atomic_end();
    return NULL;
}

void *writer1(void *unused) {
    __CPROVER_atomic_begin();
    //while (cnt3 < LIMIT) {
        count = 0;
        expect_close = 0;
        // function inline 
        if (count) { 
            if (!nowayout) { 
                /* note: just in case someone wrote the magic character
                 * five months ago... */ 
                //expect_close = 0; 
                /* markus: originally, the buffer would be looped-over here */ \
                if (wdtpci_write_buf != 'V') { 
                    expect_close = 0;
                } 
            } 
        } 
        //cnt3++;
    //}
    __CPROVER_atomic_end();
    return NULL;
}

void *writer2(void *unused) {
    __CPROVER_atomic_begin();
    //while (cnt4 < LIMIT) {
        count = 0;
        expect_close = 0;
        // function inline 
        if (count) { 
            if (!nowayout) { 
                /* note: just in case someone wrote the magic character
                 * five months ago... */ 
                //expect_close = 0; 
                /* markus: originally, the buffer would be looped-over here */ \
                if (wdtpci_write_buf != 'V') { 
                    expect_close = 0;
                } 
            } 
        } 
        //cnt4++;
    //}
    __CPROVER_atomic_end();
    return NULL;
}
