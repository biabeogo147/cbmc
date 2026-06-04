/* Extracted ISR/task definitions for the improved interleaving pipeline. */

void *closer(void *unused) {
  __CPROVER_atomic_begin();
  wdtpci_write_buf = 'V';
  wdtpci_write(1);
  wdtpci_release();
  __CPROVER_atomic_end();
  return NULL;
}

void *writer1(void *unused) {
  __CPROVER_atomic_begin();
  wdtpci_write(0);
  __CPROVER_atomic_end();
  return NULL;
}

void *writer2(void *unused) {
  __CPROVER_atomic_begin();
  wdtpci_write(0);
  __CPROVER_atomic_end();
  return NULL;
}

void *writer3(void *unused) {
  __CPROVER_atomic_begin();
  wdtpci_write(0);
  __CPROVER_atomic_end();
  return NULL;
}

void *writer4(void *unused) {
  __CPROVER_atomic_begin();
  wdtpci_write(0);
  __CPROVER_atomic_end();
  return NULL;
}

void *writer5(void *unused) {
  __CPROVER_atomic_begin();
  wdtpci_write(0);
  __CPROVER_atomic_end();
  return NULL;
}

void *writer6(void *unused) {
  __CPROVER_atomic_begin();
  wdtpci_write(0);
  __CPROVER_atomic_end();
  return NULL;
}

void *writer7(void *unused) {
  __CPROVER_atomic_begin();
  wdtpci_write(0);
  __CPROVER_atomic_end();
  return NULL;
}

void *writer8(void *unused) {
  __CPROVER_atomic_begin();
  wdtpci_write(0);
  __CPROVER_atomic_end();
  return NULL;
}

void *writer9(void *unused) {
  __CPROVER_atomic_begin();
  wdtpci_write(0);
  __CPROVER_atomic_end();
  return NULL;
}

void *writer10(void *unused) {
  __CPROVER_atomic_begin();
  wdtpci_write(0);
  __CPROVER_atomic_end();
  return NULL;
}

void *writer11(void *unused) {
  __CPROVER_atomic_begin();
  wdtpci_write(0);
  __CPROVER_atomic_end();
  return NULL;
}

void *writer12(void *unused) {
  __CPROVER_atomic_begin();
  wdtpci_write(0);
  __CPROVER_atomic_end();
  return NULL;
}

void *writer13(void *unused) {
  __CPROVER_atomic_begin();
  wdtpci_write(0);
  __CPROVER_atomic_end();
  return NULL;
}

void *writer14(void *unused) {
  __CPROVER_atomic_begin();
  wdtpci_write(0);
  __CPROVER_atomic_end();
  return NULL;
}

void *writer15(void *unused) {
  __CPROVER_atomic_begin();
  wdtpci_write(0);
  __CPROVER_atomic_end();
  return NULL;
}

void *writer16(void *unused) {
  __CPROVER_atomic_begin();
  wdtpci_write(0);
  __CPROVER_atomic_end();
  return NULL;
}

void *writer17(void *unused) {
  __CPROVER_atomic_begin();
  wdtpci_write(0);
  __CPROVER_atomic_end();
  return NULL;
}

void *writer18(void *unused) {
  __CPROVER_atomic_begin();
  wdtpci_write(0);
  __CPROVER_atomic_end();
  return NULL;
}

void *writer19(void *unused) {
  __CPROVER_atomic_begin();
  wdtpci_write(0);
  __CPROVER_atomic_end();
  return NULL;
}

void *writer20(void *unused) {
  __CPROVER_atomic_begin();
  wdtpci_write(0);
  __CPROVER_atomic_end();
  return NULL;
}

void *writer21(void *unused) {
  __CPROVER_atomic_begin();
  wdtpci_write(0);
  __CPROVER_atomic_end();
  return NULL;
}

void *writer22(void *unused) {
  __CPROVER_atomic_begin();
  wdtpci_write(0);
  __CPROVER_atomic_end();
  return NULL;
}

void *writer23(void *unused) {
  __CPROVER_atomic_begin();
  wdtpci_write(0);
  __CPROVER_atomic_end();
  return NULL;
}

void *writer24(void *unused) {
  __CPROVER_atomic_begin();
  wdtpci_write(0);
  __CPROVER_atomic_end();
  return NULL;
}

void *writer25(void *unused) {
  __CPROVER_atomic_begin();
  wdtpci_write(0);
  __CPROVER_atomic_end();
  return NULL;
}

void *writer26(void *unused) {
  __CPROVER_atomic_begin();
  wdtpci_write(0);
  __CPROVER_atomic_end();
  return NULL;
}

void *writer27(void *unused) {
  __CPROVER_atomic_begin();
  wdtpci_write(0);
  __CPROVER_atomic_end();
  return NULL;
}

void *writer28(void *unused) {
  __CPROVER_atomic_begin();
  wdtpci_write(0);
  __CPROVER_atomic_end();
  return NULL;
}

void *writer29(void *unused) {
  __CPROVER_atomic_begin();
  wdtpci_write(0);
  __CPROVER_atomic_end();
  return NULL;
}
