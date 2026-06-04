/* Extracted ISR/task definitions for the improved interleaving pipeline. */

void *ir_devnode_ldvwrapper(void){
  __CPROVER_atomic_begin();
  (& ir_devnode)(ldvarg1,ldvarg2);
  __CPROVER_atomic_end();
}

void *store_protocols_ldvwrapper(void){
  __CPROVER_atomic_begin();
  // Lihao

  (& store_protocols)(&dev_attr_protocols_group0,dev_attr_protocols_group1,ldvarg5,ldvarg4);
  __CPROVER_atomic_end();
}

void *show_protocols_ldvwrapper(void){
  __CPROVER_atomic_begin();
  // Lihao

  (& show_protocols)(&dev_attr_protocols_group0,dev_attr_protocols_group1,ldvarg3);
  __CPROVER_atomic_end();
}

void *rc_dev_uevent_ldvwrapper(void){
  __CPROVER_atomic_begin();
  (& rc_dev_uevent)(rc_dev_type_group0,ldvarg0);
  __CPROVER_atomic_end();
}

void *rc_dev_release_ldvwrapper(void){
  __CPROVER_atomic_begin();
  (& rc_dev_release)(rc_dev_type_group0);
  __CPROVER_atomic_end();
}
