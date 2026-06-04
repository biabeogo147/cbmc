/* Extracted ISR/task definitions for the improved interleaving pipeline. */

void *writer1(void *unused) {
  __CPROVER_atomic_begin();
  sc1200wdt_write(0);
  __CPROVER_atomic_end();
  return NULL;
}

void *writer2(void *unused) {
  __CPROVER_atomic_begin();
  sc1200wdt_write(0);
  __CPROVER_atomic_end();
  return NULL;
}

void *writer3(void *unused) {
  __CPROVER_atomic_begin();
  sc1200wdt_write(0);
  __CPROVER_atomic_end();
  return NULL;
}

void *writer4(void *unused) {
  __CPROVER_atomic_begin();
  sc1200wdt_write(0);
  __CPROVER_atomic_end();
  return NULL;
}

void *writer5(void *unused) {
  __CPROVER_atomic_begin();
  sc1200wdt_write(0);
  __CPROVER_atomic_end();
  return NULL;
}

void *writer6(void *unused) {
  __CPROVER_atomic_begin();
  sc1200wdt_write(0);
  __CPROVER_atomic_end();
  return NULL;
}

void *writer7(void *unused) {
  __CPROVER_atomic_begin();
  sc1200wdt_write(0);
  __CPROVER_atomic_end();
  return NULL;
}

void *writer8(void *unused) {
  __CPROVER_atomic_begin();
  sc1200wdt_write(0);
  __CPROVER_atomic_end();
  return NULL;
}

void *writer9(void *unused) {
  __CPROVER_atomic_begin();
  sc1200wdt_write(0);
  __CPROVER_atomic_end();
  return NULL;
}

void *writer10(void *unused) {
  __CPROVER_atomic_begin();
  sc1200wdt_write(0);
  __CPROVER_atomic_end();
  return NULL;
}

void *writer11(void *unused) {
  __CPROVER_atomic_begin();
  sc1200wdt_write(0);
  __CPROVER_atomic_end();
  return NULL;
}

void *writer12(void *unused) {
  __CPROVER_atomic_begin();
  sc1200wdt_write(0);
  __CPROVER_atomic_end();
  return NULL;
}

void *writer13(void *unused) {
  __CPROVER_atomic_begin();
  sc1200wdt_write(0);
  __CPROVER_atomic_end();
  return NULL;
}

void *writer14(void *unused) {
  __CPROVER_atomic_begin();
  sc1200wdt_write(0);
  __CPROVER_atomic_end();
  return NULL;
}

void *writer15(void *unused) {
  __CPROVER_atomic_begin();
  sc1200wdt_write(0);
  __CPROVER_atomic_end();
  return NULL;
}

void *writer16(void *unused) {
  __CPROVER_atomic_begin();
  sc1200wdt_write(0);
  __CPROVER_atomic_end();
  return NULL;
}

void *writer17(void *unused) {
  __CPROVER_atomic_begin();
  sc1200wdt_write(0);
  __CPROVER_atomic_end();
  return NULL;
}

void *writer18(void *unused) {
  __CPROVER_atomic_begin();
  sc1200wdt_write(0);
  __CPROVER_atomic_end();
  return NULL;
}

void *writer19(void *unused) {
  __CPROVER_atomic_begin();
  sc1200wdt_write(0);
  __CPROVER_atomic_end();
  return NULL;
}

void *writer20(void *unused) {
  __CPROVER_atomic_begin();
  sc1200wdt_write(0);
  __CPROVER_atomic_end();
  return NULL;
}

void *writer21(void *unused) {
  __CPROVER_atomic_begin();
  sc1200wdt_write(0);
  __CPROVER_atomic_end();
  return NULL;
}

void *writer22(void *unused) {
  __CPROVER_atomic_begin();
  sc1200wdt_write(0);
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
