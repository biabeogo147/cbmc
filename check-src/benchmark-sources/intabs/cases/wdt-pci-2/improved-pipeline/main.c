/* Generated foreground harness for improved interleaving benchmarks. */
extern char wdtpci_write_buf;
extern int expect_close;
extern int count;
extern int cnt1;
extern int cnt3;
extern int cnt5;
extern int cnt6;

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
  sink += (int)cnt3;
  cnt3 = cnt3;
  sink += (int)cnt5;
  cnt5 = cnt5;
  sink += (int)cnt6;
  cnt6 = cnt6;
  return sink == 1234567;
}
