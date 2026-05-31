/* Generated foreground harness for improved interleaving benchmarks. */
extern char wdtpci_write_buf;
extern int expect_close;
extern int count;
extern int cnt1;
extern int cnt2;
extern int cnt3;
extern int cnt4;

int main(void)
{
  int sink = 0;
  sink += (int)wdtpci_write_buf;
  wdtpci_write_buf = wdtpci_write_buf;
  sink += (int)expect_close;
  expect_close = expect_close;
  sink += (int)count;
  count = count;
  sink += (int)cnt1;
  cnt1 = cnt1;
  sink += (int)cnt2;
  cnt2 = cnt2;
  sink += (int)cnt3;
  cnt3 = cnt3;
  sink += (int)cnt4;
  cnt4 = cnt4;
  return sink == 1234567;
}
