/* Extracted ISR/task definitions for the improved interleaving pipeline. */

void *writer1(void *unused) {
    __CPROVER_atomic_begin();
    if (!dev_open) { 
        assert(0);
    }
    /* See if we got the magic character 'V' and reload the timer */
    if(len) {
        if (!nowayout) {
            /* note: just in case someone wrote the magic character
             * five months ago... */ 
            expect_close = 0;
            /* markus: originally, the buffer would be looped-over here */
            if (fops_write_buf == 'V') {
                expect_close = 42;
            } 
        } 
    }
    // sc1200wdt_write_data(WDTO, timeout);
    if (sc1200wdt_lock_init != true) {
        assert(0);
    }
    spin_lock(sc1200wdt_lock);
    //outb_p(index, pmir_port);
    pmir_port = WDTO;
    //outb(data, pmdr_port);
    pmdr_port = timeout;
    if (sc1200wdt_lock_init != true) {
        assert(0);
    }
    spin_unlock(sc1200wdt_lock);
    __CPROVER_atomic_end();
    return NULL;
}

void *closer(void *unused) {
  __CPROVER_atomic_begin();
  fops_write_buf = 'V';
  sc1200wdt_write(1);
  sc1200wdt_release();
  __CPROVER_atomic_end();
  return NULL;
}
