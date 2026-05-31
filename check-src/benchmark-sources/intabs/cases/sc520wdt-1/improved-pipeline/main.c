/* Generated foreground harness for improved interleaving benchmarks. */
extern char fops_write_buf;
extern char wdt_expect_close;
extern long jiffies;

int main(void)
{
  int sink = 0;
  sink += (int)fops_write_buf;
  fops_write_buf = fops_write_buf;
  sink += (int)wdt_expect_close;
  wdt_expect_close = wdt_expect_close;
  sink += (int)jiffies;
  jiffies = jiffies;
  return sink == 1234567;
}
