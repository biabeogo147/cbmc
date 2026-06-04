/* Extracted ISR/task definitions for the improved interleaving pipeline. */

void *ir_devnode_ldvwrapper(void *arg){
  __CPROVER_atomic_begin();
__VERIFIER_atomic_TRANS_ir_devnode_ldvwrapper_enter_thread();
 // Lihao: inline function
 //(& ir_devnode)(ldvarg1,ldvarg2);
  char const *tmp ;
  char *tmp___0 ;
// Lihao
  //test_bug=2;
  tmp = dev_name((struct device const *)ldvarg1);
  tmp___0 = kasprintf(208U, "rc/%s", tmp);
__VERIFIER_atomic_TRANS_ir_devnode_ldvwrapper_leave_thread();
  __CPROVER_atomic_end();
  return (tmp___0);
}

void *store_protocols_ldvwrapper(void *arg){
  __CPROVER_atomic_begin();
//void store_protocols_ldvwrapper(void){
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_TRANS_store_protocols_ldvwrapper_enter_thread();
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
 // Lihao: inline function
 //(& store_protocols)(&dev_attr_protocols_group0,dev_attr_protocols_group1,ldvarg5,ldvarg4);
__VERIFIER_atomic_begin();
TRANS_atomic_assume_store_protocols_ldvwrapper();
  struct rc_dev *dev ;
  struct rc_dev tmp_dev; // Lihao: lift if
  int tmp_rc_core_debug; // Lihao: lift if
  char tmp_tmp;          // Lihao: lift if
TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_store_protocols_ldvwrapper();
  struct device const *__mptr ;
TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_store_protocols_ldvwrapper();
  bool enable ;
TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_store_protocols_ldvwrapper();
  bool disable ;
TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_store_protocols_ldvwrapper();
  char const *tmp ;
TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_store_protocols_ldvwrapper();
  u64 type ;
TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_store_protocols_ldvwrapper();
  u64 mask ;
TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_store_protocols_ldvwrapper();
  int rc ;
TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_store_protocols_ldvwrapper();
  int i ;
TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_store_protocols_ldvwrapper();
  int count ;
TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_store_protocols_ldvwrapper();
  unsigned long flags ;
TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_store_protocols_ldvwrapper();
  ssize_t ret ;
TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_store_protocols_ldvwrapper();
  struct _ddebug descriptor ;
TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_store_protocols_ldvwrapper();
  long tmp___0 ;
TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_store_protocols_ldvwrapper();
  int tmp___1 ;
TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_store_protocols_ldvwrapper();
  struct _ddebug descriptor___0 ;
TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_store_protocols_ldvwrapper();
  long tmp___2 ;
TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_store_protocols_ldvwrapper();
  char *tmp___3 ;
TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_store_protocols_ldvwrapper();
  struct _ddebug descriptor___1 ;
TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_store_protocols_ldvwrapper();
  long tmp___4 ;
TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_store_protocols_ldvwrapper();
  struct _ddebug descriptor___2 ;
TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_store_protocols_ldvwrapper();
  long tmp___5 ;
TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_store_protocols_ldvwrapper();
  raw_spinlock_t *tmp___6 ;
TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_store_protocols_ldvwrapper();
  struct _ddebug descriptor___3 ;
TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_store_protocols_ldvwrapper();
  long tmp___7 ;
TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();

__VERIFIER_atomic_begin();
TRANS_atomic_assume_store_protocols_ldvwrapper();
  __mptr = (struct device const *)(&dev_attr_protocols_group0);
TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_store_protocols_ldvwrapper();
  dev = (struct rc_dev *)__mptr;
TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_store_protocols_ldvwrapper();
  count = 0;
TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
  if ((unsigned long )dev == (unsigned long )((struct rc_dev *)0)) {
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_TRANS_store_protocols_ldvwrapper_leave_thread();
    __CPROVER_atomic_end();
  return (-22L);
  } else {
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();

  }


  //Peter
  //ldv_mutex_lock_8(& dev->lock); // remove lock
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
 // Lihao: lift if
__VERIFIER_atomic_begin();
TRANS_atomic_assume_store_protocols_ldvwrapper();
  tmp_dev = *dev;
TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
  if ((unsigned int )tmp_dev.driver_type == 0U) {
  //if ((unsigned int )dev->driver_type == 0U) {
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_store_protocols_ldvwrapper();
    type = (u64 )dev->rc_map.rc_type;
TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
  } else {
  // Lihao: lift if
__VERIFIER_atomic_begin();
TRANS_atomic_assume_store_protocols_ldvwrapper();
  tmp_dev = *dev;
TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
  if ((unsigned long )tmp_dev.raw != (unsigned long )((struct ir_raw_event_ctrl *)0)) {
  //if ((unsigned long )dev->raw != (unsigned long )((struct ir_raw_event_ctrl *)0)) {
  __VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
  __VERIFIER_atomic_begin();
TRANS_atomic_assume_store_protocols_ldvwrapper();
      type = (dev->raw)->enabled_protocols;
TRANS_atomic_assume_store_protocols_ldvwrapper();
  __VERIFIER_atomic_end();
  __VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
  } else { 
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
     // Lihao
     //test_bug=1;
    //Peter
    // uncomment this line to introduce a bug in the device struct
__VERIFIER_atomic_begin();
TRANS_atomic_assume_store_protocols_ldvwrapper();
    struct ir_raw_event_ctrl r;
TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_store_protocols_ldvwrapper();
    dev->raw = &r; // this will violate the consistency check
TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();   
//dev->driver_type = RC_DRIVER_SCANCODE; // this will violate the consistency check
// Lihao: lift if 
__VERIFIER_atomic_begin();
TRANS_atomic_assume_store_protocols_ldvwrapper();
  tmp_rc_core_debug = rc_core_debug;
TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
    if (tmp_rc_core_debug > 0) {
    //if (rc_core_debug > 0) {
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_store_protocols_ldvwrapper();
      descriptor.modname = "rc_core";
TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_store_protocols_ldvwrapper();
      descriptor.function = "store_protocols";
TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_store_protocols_ldvwrapper();
      descriptor.filename = "/work/zakharov/bench-tests/cpa-1/work/current--X--drivers/media/rc/rc-core.ko--X--deg2_cpalinux-3.8-rc1--X--32_7a--X--cpachecker/linux-3.8-rc1/csd_deg_dscv/13/dscv_tempdir/dscv/ri/32_7a/drivers/media/rc/rc-main.c.prepared";
TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_store_protocols_ldvwrapper();
      descriptor.format = "%s: Protocol switching not supported\n";
TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_store_protocols_ldvwrapper();
      descriptor.lineno = 916U;
TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_store_protocols_ldvwrapper();
      descriptor.flags = 0U;
TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_store_protocols_ldvwrapper();
      tmp___0 = __builtin_expect((long )descriptor.flags & 1L, 0L);
TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
      if (tmp___0 != 0L) {
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_store_protocols_ldvwrapper();
        __dynamic_pr_debug(& descriptor, "%s: Protocol switching not supported\n",
                           "store_protocols");
TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
      } else {
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();

      }
    } else {
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();

    }
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_store_protocols_ldvwrapper();
    ret = -22L;
TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
//__VERIFIER_atomic_begin();
    goto out;
//__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
  }
 }
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
//__VERIFIER_atomic_begin();
  goto ldv_23470;
//__VERIFIER_atomic_end();
//__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
//__VERIFIER_atomic_begin();
  ldv_23469: ;
//__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
// Lihao: lift if
__VERIFIER_atomic_begin();
TRANS_atomic_assume_store_protocols_ldvwrapper();
  tmp_tmp = *tmp;
TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
  if ((int )((signed char )tmp_tmp) == 0) {
  //if ((int )((signed char )*tmp) == 0) {
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
//__VERIFIER_atomic_begin();
    goto ldv_23460;
//__VERIFIER_atomic_end();
//__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
  } else {
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();

  }
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
 // Lihao: lift if
__VERIFIER_atomic_begin();
TRANS_atomic_assume_store_protocols_ldvwrapper();
  tmp_tmp = *tmp;
TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
  if ((int )((signed char )tmp_tmp) == 43) {
  //if ((int )((signed char )*tmp) == 43) {
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_store_protocols_ldvwrapper();
    enable = 1;
TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_store_protocols_ldvwrapper();
    disable = 0;
TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_store_protocols_ldvwrapper();
    tmp = tmp + 1;
TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
  } else {
  // Lihao: lift if
__VERIFIER_atomic_begin();
TRANS_atomic_assume_store_protocols_ldvwrapper();
  tmp_tmp = *tmp;
TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
  if ((int )((signed char )tmp_tmp) == 45) {
  //if ((int )((signed char )*tmp) == 45) {
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_store_protocols_ldvwrapper();
    enable = 0;
TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_store_protocols_ldvwrapper();
    disable = 1;
TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_store_protocols_ldvwrapper();
    tmp = tmp + 1;
TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
  } else {
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_store_protocols_ldvwrapper();
    enable = 0;
TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_store_protocols_ldvwrapper();
    disable = 0;
TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
  }
 }
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_store_protocols_ldvwrapper();
  i = 0;
TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
//__VERIFIER_atomic_begin();
  goto ldv_23465;
//__VERIFIER_atomic_end();
//__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
  ldv_23464:
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_store_protocols_ldvwrapper();
  tmp___1 = strcasecmp(tmp, (char const *)proto_names[i].name);
TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
  if (tmp___1 == 0) {
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_store_protocols_ldvwrapper();
    mask = proto_names[i].type;
TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
//__VERIFIER_atomic_begin();
    goto ldv_23463;
//__VERIFIER_atomic_end();
//__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
  } else {
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();

  }
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_store_protocols_ldvwrapper();
  i = i + 1;
TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
//__VERIFIER_atomic_begin();
  ldv_23465: ;
//__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
  if ((unsigned int )i <= 11U) {
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
//__VERIFIER_atomic_begin();
    goto ldv_23464;
//__VERIFIER_atomic_end();
//__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
  } else {
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();

  }
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
//__VERIFIER_atomic_begin();
  ldv_23463: ;
//__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
  if (i == 12) {
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
// Lihao: lift if
 __VERIFIER_atomic_begin();
TRANS_atomic_assume_store_protocols_ldvwrapper();
  tmp_rc_core_debug = rc_core_debug;
TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
    if (tmp_rc_core_debug > 0) {
    //if (rc_core_debug > 0) {
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_store_protocols_ldvwrapper();
      descriptor___0.modname = "rc_core";
TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_store_protocols_ldvwrapper();
      descriptor___0.function = "store_protocols";
TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_store_protocols_ldvwrapper();
      descriptor___0.filename = "/work/zakharov/bench-tests/cpa-1/work/current--X--drivers/media/rc/rc-core.ko--X--deg2_cpalinux-3.8-rc1--X--32_7a--X--cpachecker/linux-3.8-rc1/csd_deg_dscv/13/dscv_tempdir/dscv/ri/32_7a/drivers/media/rc/rc-main.c.prepared";
TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_store_protocols_ldvwrapper();
      descriptor___0.format = "%s: Unknown protocol: \'%s\'\n";
TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_store_protocols_ldvwrapper();
      descriptor___0.lineno = 946U;
TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_store_protocols_ldvwrapper();
      descriptor___0.flags = 0U;
TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_store_protocols_ldvwrapper();
      tmp___2 = __builtin_expect((long )descriptor___0.flags & 1L, 0L);
TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
      if (tmp___2 != 0L) {
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_store_protocols_ldvwrapper();
        __dynamic_pr_debug(& descriptor___0, "%s: Unknown protocol: \'%s\'\n", "store_protocols",
                           tmp);
TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
      } else {
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();

      }
    } else {
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();

    }
    //__CPROVER_atomic_end();
  return (-22L); //Peter: unwanted bug fixed
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_store_protocols_ldvwrapper();
    ret = -22L;
TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
//__VERIFIER_atomic_begin();
    goto out;
//__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
  } else {
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();

  }
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_store_protocols_ldvwrapper();
  count = count + 1;
TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
  if ((int )enable) {
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_store_protocols_ldvwrapper();
    type = type | mask;
TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
  } else if ((int )disable) {
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_store_protocols_ldvwrapper();
    type = ~ mask & type;
TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
  } else {
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_store_protocols_ldvwrapper();
    type = mask;
TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
  }
  ldv_23470:
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_store_protocols_ldvwrapper();
  tmp___3 = strsep((char **)(& ldvarg5), " \n");
TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_store_protocols_ldvwrapper();
  tmp = (char const *)tmp___3;
TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
  if ((unsigned long )tmp != (unsigned long )((char const *)0)) {
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
//__VERIFIER_atomic_begin();
    goto ldv_23469;
//__VERIFIER_atomic_end();
//__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
  } else {
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
  }
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
//__VERIFIER_atomic_begin();
  ldv_23460: ;
//__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
  if (count == 0) {
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
// Lihao: lift if
__VERIFIER_atomic_begin();
TRANS_atomic_assume_store_protocols_ldvwrapper();
tmp_rc_core_debug = rc_core_debug;
TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
    if (tmp_rc_core_debug > 0) {
    //if (rc_core_debug > 0) {
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_store_protocols_ldvwrapper();
      descriptor___1.modname = "rc_core";
TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_store_protocols_ldvwrapper();
      descriptor___1.function = "store_protocols";
TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_store_protocols_ldvwrapper();
      descriptor___1.filename = "/work/zakharov/bench-tests/cpa-1/work/current--X--drivers/media/rc/rc-core.ko--X--deg2_cpalinux-3.8-rc1--X--32_7a--X--cpachecker/linux-3.8-rc1/csd_deg_dscv/13/dscv_tempdir/dscv/ri/32_7a/drivers/media/rc/rc-main.c.prepared";
TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_store_protocols_ldvwrapper();
      descriptor___1.format = "%s: Protocol not specified\n";
TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_store_protocols_ldvwrapper();
      descriptor___1.lineno = 961U;
TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_store_protocols_ldvwrapper();
      descriptor___1.flags = 0U;
TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_store_protocols_ldvwrapper();
      tmp___4 = __builtin_expect((long )descriptor___1.flags & 1L, 0L);
TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
      if (tmp___4 != 0L) {
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_store_protocols_ldvwrapper();
        __dynamic_pr_debug(& descriptor___1, "%s: Protocol not specified\n", "store_protocols");
TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
      } else {
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();

      }
    } else {
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();

    }
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_store_protocols_ldvwrapper();
    ret = -22L;
TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
//__VERIFIER_atomic_begin();
    goto out;
//__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
  } else {
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();

  }
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
// Lihao: lift if
__VERIFIER_atomic_begin();
TRANS_atomic_assume_store_protocols_ldvwrapper();
  tmp_dev = *dev;
TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
  if ((unsigned long )tmp_dev.change_protocol != (unsigned long )((int (*)(struct rc_dev * , u64 * ))0)) {
  //if ((unsigned long )dev->change_protocol != (unsigned long )((int (*)(struct rc_dev * , u64 * ))0)) {
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_store_protocols_ldvwrapper();
    rc = (*(dev->change_protocol))(dev, & type);
TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
    if (rc < 0) {
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
// Lihao: lift if 
__VERIFIER_atomic_begin();
TRANS_atomic_assume_store_protocols_ldvwrapper();
  tmp_rc_core_debug = rc_core_debug;
TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
      if (tmp_rc_core_debug > 0) {
      //if (rc_core_debug > 0) {
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_store_protocols_ldvwrapper();
        descriptor___2.modname = "rc_core";
TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_store_protocols_ldvwrapper();
        descriptor___2.function = "store_protocols";
TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_store_protocols_ldvwrapper();
        descriptor___2.filename = "/work/zakharov/bench-tests/cpa-1/work/current--X--drivers/media/rc/rc-core.ko--X--deg2_cpalinux-3.8-rc1--X--32_7a--X--cpachecker/linux-3.8-rc1/csd_deg_dscv/13/dscv_tempdir/dscv/ri/32_7a/drivers/media/rc/rc-main.c.prepared";
TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_store_protocols_ldvwrapper();
        descriptor___2.format = "%s: Error setting protocols to 0x%llx\n";
TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_store_protocols_ldvwrapper();
        descriptor___2.lineno = 970U;
TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_store_protocols_ldvwrapper();
        descriptor___2.flags = 0U;
TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_store_protocols_ldvwrapper();
        tmp___5 = __builtin_expect((long )descriptor___2.flags & 1L, 0L);
TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
        if (tmp___5 != 0L) {
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_store_protocols_ldvwrapper();
          __dynamic_pr_debug(& descriptor___2, "%s: Error setting protocols to 0x%llx\n",
                             "store_protocols", (long long )type);
TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
        } else {
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();

        }
      } else {
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();

      }
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_store_protocols_ldvwrapper();
      ret = -22L;
TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
//__VERIFIER_atomic_begin();
      goto out;
//__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
    } else {
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();

    }
  } else {
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();

  }
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
 // Lihao: lift if
__VERIFIER_atomic_begin();
TRANS_atomic_assume_store_protocols_ldvwrapper();
  tmp_dev = *dev;
TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
  if ((unsigned int )tmp_dev.driver_type == 0U) {
  //if ((unsigned int )dev->driver_type == 0U) {
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_store_protocols_ldvwrapper();
    tmp___6 = spinlock_check(& dev->rc_map.lock);
TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_store_protocols_ldvwrapper();
    flags = _raw_spin_lock_irqsave(tmp___6);
TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_store_protocols_ldvwrapper();
    dev->rc_map.rc_type = (enum rc_type )type;
TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_store_protocols_ldvwrapper();
    spin_unlock_irqrestore(& dev->rc_map.lock, flags);
TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
  } else {
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_store_protocols_ldvwrapper();
    (dev->raw)->enabled_protocols = type;
TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
  }
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
// Lihao: lift if
__VERIFIER_atomic_begin();
TRANS_atomic_assume_store_protocols_ldvwrapper();
  tmp_rc_core_debug = rc_core_debug;
TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
  if (tmp_rc_core_debug > 0) {
  //if (rc_core_debug > 0) {
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_store_protocols_ldvwrapper();
    descriptor___3.modname = "rc_core";
TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_store_protocols_ldvwrapper();
    descriptor___3.function = "store_protocols";
TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_store_protocols_ldvwrapper();
    descriptor___3.filename = "/work/zakharov/bench-tests/cpa-1/work/current--X--drivers/media/rc/rc-core.ko--X--deg2_cpalinux-3.8-rc1--X--32_7a--X--cpachecker/linux-3.8-rc1/csd_deg_dscv/13/dscv_tempdir/dscv/ri/32_7a/drivers/media/rc/rc-main.c.prepared";
TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_store_protocols_ldvwrapper();
    descriptor___3.format = "%s: Current protocol(s): 0x%llx\n";
TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_store_protocols_ldvwrapper();
    descriptor___3.lineno = 985U;
TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_store_protocols_ldvwrapper();
    descriptor___3.flags = 0U;
TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_store_protocols_ldvwrapper();
    tmp___7 = __builtin_expect((long )descriptor___3.flags & 1L, 0L);
TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
    if (tmp___7 != 0L) {
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_store_protocols_ldvwrapper();
      __dynamic_pr_debug(& descriptor___3, "%s: Current protocol(s): 0x%llx\n", "store_protocols",
                         (long long )type);
TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
    } else {
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();

    }
  } else {
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();

  }
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_store_protocols_ldvwrapper();
  ret = (ssize_t )ldvarg4;
TRANS_atomic_assume_store_protocols_ldvwrapper();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_store_protocols_ldvwrapper();
  out:
  // Peter
  // ldv_mutex_unlock_9(& dev->lock); //remove lock
__VERIFIER_atomic_TRANS_store_protocols_ldvwrapper_leave_thread();
  __CPROVER_atomic_end();
  return (ret);
//__VERIFIER_atomic_TRANS_store_protocols_ldvwrapper_leave_thread();
}

void *show_protocols_ldvwrapper(void *arg){
  __CPROVER_atomic_begin();
//void show_protocols_ldvwrapper(void){
__VERIFIER_atomic_TRANS_atomic_assume_show_protocols_ldvwrapper();
__VERIFIER_atomic_TRANS_show_protocols_ldvwrapper_enter_thread();
__VERIFIER_atomic_TRANS_atomic_assume_show_protocols_ldvwrapper();
 // Lihao: inline
 //(& show_protocols)(&dev_attr_protocols_group0,dev_attr_protocols_group1,ldvarg3);
__VERIFIER_atomic_begin();
TRANS_atomic_assume_show_protocols_ldvwrapper();
  struct rc_dev *dev ;
  struct rc_dev tmp_dev; // Lihao: lift if
  int tmp_rc_core_debug;     // Lihao: lift if
TRANS_atomic_assume_show_protocols_ldvwrapper();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_show_protocols_ldvwrapper();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_show_protocols_ldvwrapper();
  struct device const *__mptr ;
TRANS_atomic_assume_show_protocols_ldvwrapper();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_show_protocols_ldvwrapper();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_show_protocols_ldvwrapper();
  u64 allowed ;
TRANS_atomic_assume_show_protocols_ldvwrapper();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_show_protocols_ldvwrapper();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_show_protocols_ldvwrapper();
  u64 enabled ;
TRANS_atomic_assume_show_protocols_ldvwrapper();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_show_protocols_ldvwrapper();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_show_protocols_ldvwrapper();
  char *tmp ;
TRANS_atomic_assume_show_protocols_ldvwrapper();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_show_protocols_ldvwrapper();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_show_protocols_ldvwrapper();
  int i ;
TRANS_atomic_assume_show_protocols_ldvwrapper();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_show_protocols_ldvwrapper();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_show_protocols_ldvwrapper();
  struct _ddebug descriptor ;
TRANS_atomic_assume_show_protocols_ldvwrapper();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_show_protocols_ldvwrapper();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_show_protocols_ldvwrapper();
  long tmp___0 ;
TRANS_atomic_assume_show_protocols_ldvwrapper();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_show_protocols_ldvwrapper();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_show_protocols_ldvwrapper();
  int tmp___1 ;
TRANS_atomic_assume_show_protocols_ldvwrapper();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_show_protocols_ldvwrapper();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_show_protocols_ldvwrapper();
  int tmp___2 ;
TRANS_atomic_assume_show_protocols_ldvwrapper();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_show_protocols_ldvwrapper();

__VERIFIER_atomic_begin();
TRANS_atomic_assume_show_protocols_ldvwrapper();
  __mptr = (struct device const *)(&dev_attr_protocols_group0);
TRANS_atomic_assume_show_protocols_ldvwrapper();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_show_protocols_ldvwrapper();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_show_protocols_ldvwrapper();
  dev = (struct rc_dev *)__mptr;
TRANS_atomic_assume_show_protocols_ldvwrapper();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_show_protocols_ldvwrapper();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_show_protocols_ldvwrapper();
  tmp = ldvarg3;
TRANS_atomic_assume_show_protocols_ldvwrapper();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_show_protocols_ldvwrapper();
  if ((unsigned long )dev == (unsigned long )((struct rc_dev *)0)) {
__VERIFIER_atomic_TRANS_atomic_assume_show_protocols_ldvwrapper();
__VERIFIER_atomic_TRANS_show_protocols_ldvwrapper_leave_thread();
    __CPROVER_atomic_end();
  return (-22L);
  } else {
__VERIFIER_atomic_TRANS_atomic_assume_show_protocols_ldvwrapper();

  }

  // Peter
  //  ldv_mutex_lock_6(& dev->lock); // remove lock
__VERIFIER_atomic_TRANS_atomic_assume_show_protocols_ldvwrapper();
// Lihao: lift if
__VERIFIER_atomic_begin();
TRANS_atomic_assume_show_protocols_ldvwrapper();
  tmp_dev = *dev;
TRANS_atomic_assume_show_protocols_ldvwrapper();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_show_protocols_ldvwrapper();
  if ((unsigned int )tmp_dev.driver_type == 0U) {
  //if ((unsigned int )dev->driver_type == 0U) {
__VERIFIER_atomic_TRANS_atomic_assume_show_protocols_ldvwrapper();

__VERIFIER_atomic_begin();
TRANS_atomic_assume_show_protocols_ldvwrapper();
    enabled = (u64 )dev->rc_map.rc_type;
TRANS_atomic_assume_show_protocols_ldvwrapper();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_show_protocols_ldvwrapper();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_show_protocols_ldvwrapper();
    allowed = dev->allowed_protos;
TRANS_atomic_assume_show_protocols_ldvwrapper();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_show_protocols_ldvwrapper();

   

  } else {
 // Lihao: lift if
__VERIFIER_atomic_begin();
TRANS_atomic_assume_show_protocols_ldvwrapper();
  tmp_dev = *dev;
TRANS_atomic_assume_show_protocols_ldvwrapper();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_show_protocols_ldvwrapper();
  if ((unsigned long )tmp_dev.raw != (unsigned long )((struct ir_raw_event_ctrl *)0)) {
  //if ((unsigned long )dev->raw != (unsigned long )((struct ir_raw_event_ctrl *)0)) {
__VERIFIER_atomic_TRANS_atomic_assume_show_protocols_ldvwrapper();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_show_protocols_ldvwrapper();
    enabled = (dev->raw)->enabled_protocols;
TRANS_atomic_assume_show_protocols_ldvwrapper();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_show_protocols_ldvwrapper();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_show_protocols_ldvwrapper();
    allowed = ir_raw_get_allowed_protocols();
TRANS_atomic_assume_show_protocols_ldvwrapper();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_show_protocols_ldvwrapper();
  } else {
__VERIFIER_atomic_TRANS_atomic_assume_show_protocols_ldvwrapper();

   //Lihao
   //if(test_bug==0) assert(test_bug==0);
   //Peter
   // uncomment this line to introduce a bug in the device struct
__VERIFIER_atomic_begin();
TRANS_atomic_assume_show_protocols_ldvwrapper();
   //assert((unsigned int )dev->driver_type != 0U && (unsigned long )dev->raw == (unsigned long )((struct ir_raw_event_ctrl *)0)); //consistency check
   __VERIFIER_assert((unsigned int )dev->driver_type != 0U && (unsigned long )dev->raw == (unsigned long )((struct ir_raw_event_ctrl *)0)); //consistency check
   //if(!((unsigned int )dev->driver_type != 0U && (unsigned long )dev->raw == (unsigned long )((struct ir_raw_event_ctrl *)0))) irq_err(); //consistency check
TRANS_atomic_assume_show_protocols_ldvwrapper();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_show_protocols_ldvwrapper();
__VERIFIER_atomic_TRANS_show_protocols_ldvwrapper_leave_thread();
    __CPROVER_atomic_end();
  return (-19L);
  }
 }
__VERIFIER_atomic_TRANS_atomic_assume_show_protocols_ldvwrapper();
// Lihao: lift if
__VERIFIER_atomic_begin();
TRANS_atomic_assume_show_protocols_ldvwrapper();
  tmp_rc_core_debug = rc_core_debug;
TRANS_atomic_assume_show_protocols_ldvwrapper();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_show_protocols_ldvwrapper();
  if (tmp_rc_core_debug > 0) {
  //if (rc_core_debug > 0) {
__VERIFIER_atomic_TRANS_atomic_assume_show_protocols_ldvwrapper();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_show_protocols_ldvwrapper();
    descriptor.modname = "rc_core";
TRANS_atomic_assume_show_protocols_ldvwrapper();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_show_protocols_ldvwrapper();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_show_protocols_ldvwrapper();
    descriptor.function = "show_protocols";
TRANS_atomic_assume_show_protocols_ldvwrapper();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_show_protocols_ldvwrapper();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_show_protocols_ldvwrapper();
    descriptor.filename = "/work/zakharov/bench-tests/cpa-1/work/current--X--drivers/media/rc/rc-core.ko--X--deg2_cpalinux-3.8-rc1--X--32_7a--X--cpachecker/linux-3.8-rc1/csd_deg_dscv/13/dscv_tempdir/dscv/ri/32_7a/drivers/media/rc/rc-main.c.prepared";
TRANS_atomic_assume_show_protocols_ldvwrapper();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_show_protocols_ldvwrapper();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_show_protocols_ldvwrapper();
    descriptor.format = "%s: allowed - 0x%llx, enabled - 0x%llx\n";
TRANS_atomic_assume_show_protocols_ldvwrapper();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_show_protocols_ldvwrapper();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_show_protocols_ldvwrapper();
    descriptor.lineno = 851U;
TRANS_atomic_assume_show_protocols_ldvwrapper();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_show_protocols_ldvwrapper();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_show_protocols_ldvwrapper();
    descriptor.flags = 0U;
TRANS_atomic_assume_show_protocols_ldvwrapper();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_show_protocols_ldvwrapper();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_show_protocols_ldvwrapper();
    tmp___0 = __builtin_expect((long )descriptor.flags & 1L, 0L);
TRANS_atomic_assume_show_protocols_ldvwrapper();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_show_protocols_ldvwrapper();
    if (tmp___0 != 0L) {
__VERIFIER_atomic_TRANS_atomic_assume_show_protocols_ldvwrapper();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_show_protocols_ldvwrapper();
      __dynamic_pr_debug(& descriptor, "%s: allowed - 0x%llx, enabled - 0x%llx\n",
                         "show_protocols", (long long )allowed, (long long )enabled);
TRANS_atomic_assume_show_protocols_ldvwrapper();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_show_protocols_ldvwrapper();
    } else {
__VERIFIER_atomic_TRANS_atomic_assume_show_protocols_ldvwrapper();

    }
  } else {
__VERIFIER_atomic_TRANS_atomic_assume_show_protocols_ldvwrapper();

  }
__VERIFIER_atomic_TRANS_atomic_assume_show_protocols_ldvwrapper();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_show_protocols_ldvwrapper();
  i = 0;
TRANS_atomic_assume_show_protocols_ldvwrapper();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_show_protocols_ldvwrapper();
//__VERIFIER_atomic_begin();
  goto ldv_23436;
//__VERIFIER_atomic_end();
//__VERIFIER_atomic_TRANS_atomic_assume_show_protocols_ldvwrapper();
//__VERIFIER_atomic_begin();
  ldv_23435: ;
//__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_show_protocols_ldvwrapper();
// Lihao: lift if
__VERIFIER_atomic_begin();
TRANS_atomic_assume_show_protocols_ldvwrapper();
  u64 tmp_type = proto_names[i].type;
TRANS_atomic_assume_show_protocols_ldvwrapper();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_show_protocols_ldvwrapper();
  if (((allowed & enabled) & tmp_type) != 0ULL) {
  //if (((allowed & enabled) & proto_names[i].type) != 0ULL) {
__VERIFIER_atomic_TRANS_atomic_assume_show_protocols_ldvwrapper();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_show_protocols_ldvwrapper();
    tmp___1 = sprintf(tmp, "[%s] ", proto_names[i].name);
TRANS_atomic_assume_show_protocols_ldvwrapper();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_show_protocols_ldvwrapper();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_show_protocols_ldvwrapper();
    tmp = tmp + (unsigned long )tmp___1;
TRANS_atomic_assume_show_protocols_ldvwrapper();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_show_protocols_ldvwrapper();
  } else  {
// Lihao: lift if
__VERIFIER_atomic_begin();
TRANS_atomic_assume_show_protocols_ldvwrapper();
  tmp_type = proto_names[i].type;
TRANS_atomic_assume_show_protocols_ldvwrapper();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_show_protocols_ldvwrapper();
  if ((tmp_type & allowed) != 0ULL) {
  //if ((proto_names[i].type & allowed) != 0ULL) {
__VERIFIER_atomic_TRANS_atomic_assume_show_protocols_ldvwrapper();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_show_protocols_ldvwrapper();
    tmp___2 = sprintf(tmp, "%s ", proto_names[i].name);
TRANS_atomic_assume_show_protocols_ldvwrapper();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_show_protocols_ldvwrapper();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_show_protocols_ldvwrapper();
    tmp = tmp + (unsigned long )tmp___2;
TRANS_atomic_assume_show_protocols_ldvwrapper();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_show_protocols_ldvwrapper();
  } else {
__VERIFIER_atomic_TRANS_atomic_assume_show_protocols_ldvwrapper();

  }
 }
__VERIFIER_atomic_TRANS_atomic_assume_show_protocols_ldvwrapper();
 // Lihao: lift if
__VERIFIER_atomic_begin();
TRANS_atomic_assume_show_protocols_ldvwrapper();
  tmp_type = proto_names[i].type;
TRANS_atomic_assume_show_protocols_ldvwrapper();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_show_protocols_ldvwrapper();
  if ((tmp_type & allowed) != 0ULL) {
  //if ((proto_names[i].type & allowed) != 0ULL) {
__VERIFIER_atomic_TRANS_atomic_assume_show_protocols_ldvwrapper();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_show_protocols_ldvwrapper();
    allowed = ~ proto_names[i].type & allowed;
TRANS_atomic_assume_show_protocols_ldvwrapper();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_show_protocols_ldvwrapper();
  } else {
__VERIFIER_atomic_TRANS_atomic_assume_show_protocols_ldvwrapper();

  }
__VERIFIER_atomic_TRANS_atomic_assume_show_protocols_ldvwrapper();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_show_protocols_ldvwrapper();
  i = i + 1;
TRANS_atomic_assume_show_protocols_ldvwrapper();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_show_protocols_ldvwrapper();
//__VERIFIER_atomic_begin();
  ldv_23436: ;
//__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_show_protocols_ldvwrapper();
  if ((unsigned int )i <= 11U) {
__VERIFIER_atomic_TRANS_atomic_assume_show_protocols_ldvwrapper();
//__VERIFIER_atomic_begin();
    goto ldv_23435;
//__VERIFIER_atomic_end();
//__VERIFIER_atomic_TRANS_atomic_assume_show_protocols_ldvwrapper();
  } else {
__VERIFIER_atomic_TRANS_atomic_assume_show_protocols_ldvwrapper();

  }
__VERIFIER_atomic_TRANS_atomic_assume_show_protocols_ldvwrapper();
  if ((unsigned long )tmp != (unsigned long )ldvarg3) {
__VERIFIER_atomic_TRANS_atomic_assume_show_protocols_ldvwrapper();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_show_protocols_ldvwrapper();
    tmp = tmp - 1;
TRANS_atomic_assume_show_protocols_ldvwrapper();
__VERIFIER_atomic_end();
__VERIFIER_atomic_TRANS_atomic_assume_show_protocols_ldvwrapper();
  } else {
__VERIFIER_atomic_TRANS_atomic_assume_show_protocols_ldvwrapper();

  }
__VERIFIER_atomic_TRANS_atomic_assume_show_protocols_ldvwrapper();
__VERIFIER_atomic_begin();
TRANS_atomic_assume_show_protocols_ldvwrapper();
  *tmp = 10;
TRANS_atomic_assume_show_protocols_ldvwrapper();
__VERIFIER_atomic_end();
  // Peter
  //ldv_mutex_unlock_7(& dev->lock); // remove lock
__VERIFIER_atomic_TRANS_show_protocols_ldvwrapper_leave_thread();
  __CPROVER_atomic_end();
  return ((long )(tmp + 1UL) - (long )ldvarg3);
//__VERIFIER_atomic_TRANS_show_protocols_ldvwrapper_leave_thread();
}
