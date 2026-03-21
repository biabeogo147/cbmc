
typedef long unsigned int size_t;
typedef __builtin_va_list __gnuc_va_list;
typedef unsigned char __u_char;
typedef unsigned short int __u_short;
typedef unsigned int __u_int;
typedef unsigned long int __u_long;
typedef signed char __int8_t;
typedef unsigned char __uint8_t;
typedef signed short int __int16_t;
typedef unsigned short int __uint16_t;
typedef signed int __int32_t;
typedef unsigned int __uint32_t;
typedef signed long int __int64_t;
typedef unsigned long int __uint64_t;
typedef __int8_t __int_least8_t;
typedef __uint8_t __uint_least8_t;
typedef __int16_t __int_least16_t;
typedef __uint16_t __uint_least16_t;
typedef __int32_t __int_least32_t;
typedef __uint32_t __uint_least32_t;
typedef __int64_t __int_least64_t;
typedef __uint64_t __uint_least64_t;
typedef long int __quad_t;
typedef unsigned long int __u_quad_t;
typedef long int __intmax_t;
typedef unsigned long int __uintmax_t;
typedef unsigned long int __dev_t;
typedef unsigned int __uid_t;
typedef unsigned int __gid_t;
typedef unsigned long int __ino_t;
typedef unsigned long int __ino64_t;
typedef unsigned int __mode_t;
typedef unsigned long int __nlink_t;
typedef long int __off_t;
typedef long int __off64_t;
typedef int __pid_t;
typedef struct { int __val[2]; } __fsid_t;
typedef long int __clock_t;
typedef unsigned long int __rlim_t;
typedef unsigned long int __rlim64_t;
typedef unsigned int __id_t;
typedef long int __time_t;
typedef unsigned int __useconds_t;
typedef long int __suseconds_t;
typedef long int __suseconds64_t;
typedef int __daddr_t;
typedef int __key_t;
typedef int __clockid_t;
typedef void * __timer_t;
typedef long int __blksize_t;
typedef long int __blkcnt_t;
typedef long int __blkcnt64_t;
typedef unsigned long int __fsblkcnt_t;
typedef unsigned long int __fsblkcnt64_t;
typedef unsigned long int __fsfilcnt_t;
typedef unsigned long int __fsfilcnt64_t;
typedef long int __fsword_t;
typedef long int __ssize_t;
typedef long int __syscall_slong_t;
typedef unsigned long int __syscall_ulong_t;
typedef __off64_t __loff_t;
typedef char *__caddr_t;
typedef long int __intptr_t;
typedef unsigned int __socklen_t;
typedef int __sig_atomic_t;
typedef struct
{
  int __count;
  union
  {
    unsigned int __wch;
    char __wchb[4];
  } __value;
} __mbstate_t;
typedef struct _G_fpos_t
{
  __off_t __pos;
  __mbstate_t __state;
} __fpos_t;
typedef struct _G_fpos64_t
{
  __off64_t __pos;
  __mbstate_t __state;
} __fpos64_t;
struct _IO_FILE;
typedef struct _IO_FILE __FILE;
struct _IO_FILE;
typedef struct _IO_FILE FILE;
struct _IO_FILE;
struct _IO_marker;
struct _IO_codecvt;
struct _IO_wide_data;
typedef void _IO_lock_t;
struct _IO_FILE
{
  int _flags;
  char *_IO_read_ptr;
  char *_IO_read_end;
  char *_IO_read_base;
  char *_IO_write_base;
  char *_IO_write_ptr;
  char *_IO_write_end;
  char *_IO_buf_base;
  char *_IO_buf_end;
  char *_IO_save_base;
  char *_IO_backup_base;
  char *_IO_save_end;
  struct _IO_marker *_markers;
  struct _IO_FILE *_chain;
  int _fileno;
  int _flags2:24;
  char _short_backupbuf[1];
  __off_t _old_offset;
  unsigned short _cur_column;
  signed char _vtable_offset;
  char _shortbuf[1];
  _IO_lock_t *_lock;
  __off64_t _offset;
  struct _IO_codecvt *_codecvt;
  struct _IO_wide_data *_wide_data;
  struct _IO_FILE *_freeres_list;
  void *_freeres_buf;
  struct _IO_FILE **_prevchain;
  int _mode;
  char _unused2[15 * sizeof (int) - 5 * sizeof (void *)];
};
typedef __ssize_t cookie_read_function_t (void *__cookie, char *__buf,
                                          size_t __nbytes);
typedef __ssize_t cookie_write_function_t (void *__cookie, const char *__buf,
                                           size_t __nbytes);
typedef int cookie_seek_function_t (void *__cookie, __off64_t *__pos, int __w);
typedef int cookie_close_function_t (void *__cookie);
typedef struct _IO_cookie_io_functions_t
{
  cookie_read_function_t *read;
  cookie_write_function_t *write;
  cookie_seek_function_t *seek;
  cookie_close_function_t *close;
} cookie_io_functions_t;
typedef __gnuc_va_list va_list;
typedef __off_t off_t;
typedef __ssize_t ssize_t;
typedef __fpos_t fpos_t;
extern FILE *stdin;
extern FILE *stdout;
extern FILE *stderr;
extern int remove (const char *__filename) __attribute__ ((__nothrow__ , __leaf__));
extern int rename (const char *__old, const char *__new) __attribute__ ((__nothrow__ , __leaf__));
extern int renameat (int __oldfd, const char *__old, int __newfd,
       const char *__new) __attribute__ ((__nothrow__ , __leaf__));
extern int fclose (FILE *__stream) __attribute__ ((__nonnull__ (1)));
extern FILE *tmpfile (void)
  __attribute__ ((__malloc__)) __attribute__ ((__malloc__ (fclose, 1))) ;
extern char *tmpnam (char[20]) __attribute__ ((__nothrow__ , __leaf__)) ;
extern char *tmpnam_r (char __s[20]) __attribute__ ((__nothrow__ , __leaf__)) ;
extern char *tempnam (const char *__dir, const char *__pfx)
   __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__malloc__)) __attribute__ ((__malloc__ (__builtin_free, 1)));
extern int fflush (FILE *__stream);
extern int fflush_unlocked (FILE *__stream);
extern FILE *fopen (const char *__restrict __filename,
      const char *__restrict __modes)
  __attribute__ ((__malloc__)) __attribute__ ((__malloc__ (fclose, 1))) ;
extern FILE *freopen (const char *__restrict __filename,
        const char *__restrict __modes,
        FILE *__restrict __stream) __attribute__ ((__nonnull__ (3)));
extern FILE *fdopen (int __fd, const char *__modes) __attribute__ ((__nothrow__ , __leaf__))
  __attribute__ ((__malloc__)) __attribute__ ((__malloc__ (fclose, 1))) ;
extern FILE *fopencookie (void *__restrict __magic_cookie,
     const char *__restrict __modes,
     cookie_io_functions_t __io_funcs) __attribute__ ((__nothrow__ , __leaf__))
  __attribute__ ((__malloc__)) __attribute__ ((__malloc__ (fclose, 1))) ;
extern FILE *fmemopen (void *__s, size_t __len, const char *__modes)
  __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__malloc__)) __attribute__ ((__malloc__ (fclose, 1))) ;
extern FILE *open_memstream (char **__bufloc, size_t *__sizeloc) __attribute__ ((__nothrow__ , __leaf__))
  __attribute__ ((__malloc__)) __attribute__ ((__malloc__ (fclose, 1))) ;
extern void setbuf (FILE *__restrict __stream, char *__restrict __buf) __attribute__ ((__nothrow__ , __leaf__))
  __attribute__ ((__nonnull__ (1)));
extern int setvbuf (FILE *__restrict __stream, char *__restrict __buf,
      int __modes, size_t __n) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern void setbuffer (FILE *__restrict __stream, char *__restrict __buf,
         size_t __size) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern void setlinebuf (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern int fprintf (FILE *__restrict __stream,
      const char *__restrict __format, ...) __attribute__ ((__nonnull__ (1)));
extern int printf (const char *__restrict __format, ...);
extern int sprintf (char *__restrict __s,
      const char *__restrict __format, ...) __attribute__ ((__nothrow__));
extern int vfprintf (FILE *__restrict __s, const char *__restrict __format,
       __gnuc_va_list __arg) __attribute__ ((__nonnull__ (1)));
extern int vprintf (const char *__restrict __format, __gnuc_va_list __arg);
extern int vsprintf (char *__restrict __s, const char *__restrict __format,
       __gnuc_va_list __arg) __attribute__ ((__nothrow__));
extern int snprintf (char *__restrict __s, size_t __maxlen,
       const char *__restrict __format, ...)
     __attribute__ ((__nothrow__)) __attribute__ ((__format__ (__printf__, 3, 4)));
extern int vsnprintf (char *__restrict __s, size_t __maxlen,
        const char *__restrict __format, __gnuc_va_list __arg)
     __attribute__ ((__nothrow__)) __attribute__ ((__format__ (__printf__, 3, 0)));
extern int vasprintf (char **__restrict __ptr, const char *__restrict __f,
        __gnuc_va_list __arg)
     __attribute__ ((__nothrow__)) __attribute__ ((__format__ (__printf__, 2, 0))) ;
extern int __asprintf (char **__restrict __ptr,
         const char *__restrict __fmt, ...)
     __attribute__ ((__nothrow__)) __attribute__ ((__format__ (__printf__, 2, 3))) ;
extern int asprintf (char **__restrict __ptr,
       const char *__restrict __fmt, ...)
     __attribute__ ((__nothrow__)) __attribute__ ((__format__ (__printf__, 2, 3))) ;
extern int vdprintf (int __fd, const char *__restrict __fmt,
       __gnuc_va_list __arg)
     __attribute__ ((__format__ (__printf__, 2, 0)));
extern int dprintf (int __fd, const char *__restrict __fmt, ...)
     __attribute__ ((__format__ (__printf__, 2, 3)));
extern int fscanf (FILE *__restrict __stream,
     const char *__restrict __format, ...) __attribute__ ((__nonnull__ (1)));
extern int scanf (const char *__restrict __format, ...) ;
extern int sscanf (const char *__restrict __s,
     const char *__restrict __format, ...) __attribute__ ((__nothrow__ , __leaf__));
extern int fscanf (FILE *__restrict __stream, const char *__restrict __format, ...) __asm__ ("" "__isoc99_fscanf") __attribute__ ((__nonnull__ (1)));
extern int scanf (const char *__restrict __format, ...) __asm__ ("" "__isoc99_scanf") ;
extern int sscanf (const char *__restrict __s, const char *__restrict __format, ...) __asm__ ("" "__isoc99_sscanf") __attribute__ ((__nothrow__ , __leaf__));
extern int vfscanf (FILE *__restrict __s, const char *__restrict __format,
      __gnuc_va_list __arg)
     __attribute__ ((__format__ (__scanf__, 2, 0))) __attribute__ ((__nonnull__ (1)));
extern int vscanf (const char *__restrict __format, __gnuc_va_list __arg)
     __attribute__ ((__format__ (__scanf__, 1, 0))) ;
extern int vsscanf (const char *__restrict __s,
      const char *__restrict __format, __gnuc_va_list __arg)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__format__ (__scanf__, 2, 0)));
extern int vfscanf (FILE *__restrict __s, const char *__restrict __format, __gnuc_va_list __arg) __asm__ ("" "__isoc99_vfscanf")
     __attribute__ ((__format__ (__scanf__, 2, 0))) __attribute__ ((__nonnull__ (1)));
extern int vscanf (const char *__restrict __format, __gnuc_va_list __arg) __asm__ ("" "__isoc99_vscanf")
     __attribute__ ((__format__ (__scanf__, 1, 0))) ;
extern int vsscanf (const char *__restrict __s, const char *__restrict __format, __gnuc_va_list __arg) __asm__ ("" "__isoc99_vsscanf") __attribute__ ((__nothrow__ , __leaf__))
     __attribute__ ((__format__ (__scanf__, 2, 0)));
extern int fgetc (FILE *__stream) __attribute__ ((__nonnull__ (1)));
extern int getc (FILE *__stream) __attribute__ ((__nonnull__ (1)));
extern int getchar (void);
extern int getc_unlocked (FILE *__stream) __attribute__ ((__nonnull__ (1)));
extern int getchar_unlocked (void);
extern int fgetc_unlocked (FILE *__stream) __attribute__ ((__nonnull__ (1)));
extern int fputc (int __c, FILE *__stream) __attribute__ ((__nonnull__ (2)));
extern int putc (int __c, FILE *__stream) __attribute__ ((__nonnull__ (2)));
extern int putchar (int __c);
extern int fputc_unlocked (int __c, FILE *__stream) __attribute__ ((__nonnull__ (2)));
extern int putc_unlocked (int __c, FILE *__stream) __attribute__ ((__nonnull__ (2)));
extern int putchar_unlocked (int __c);
extern int getw (FILE *__stream) __attribute__ ((__nonnull__ (1)));
extern int putw (int __w, FILE *__stream) __attribute__ ((__nonnull__ (2)));
extern char *fgets (char *__restrict __s, int __n, FILE *__restrict __stream)
     __attribute__ ((__access__ (__write_only__, 1, 2))) __attribute__ ((__nonnull__ (3)));
extern __ssize_t __getdelim (char **__restrict __lineptr,
                             size_t *__restrict __n, int __delimiter,
                             FILE *__restrict __stream) __attribute__ ((__nonnull__ (4)));
extern __ssize_t getdelim (char **__restrict __lineptr,
                           size_t *__restrict __n, int __delimiter,
                           FILE *__restrict __stream) __attribute__ ((__nonnull__ (4)));
extern __ssize_t getline (char **__restrict __lineptr,
                          size_t *__restrict __n,
                          FILE *__restrict __stream) __attribute__ ((__nonnull__ (3)));
extern int fputs (const char *__restrict __s, FILE *__restrict __stream)
  __attribute__ ((__nonnull__ (2)));
extern int puts (const char *__s);
extern int ungetc (int __c, FILE *__stream) __attribute__ ((__nonnull__ (2)));
extern size_t fread (void *__restrict __ptr, size_t __size,
       size_t __n, FILE *__restrict __stream)
  __attribute__ ((__nonnull__ (4)));
extern size_t fwrite (const void *__restrict __ptr, size_t __size,
        size_t __n, FILE *__restrict __s) __attribute__ ((__nonnull__ (4)));
extern size_t fread_unlocked (void *__restrict __ptr, size_t __size,
         size_t __n, FILE *__restrict __stream)
  __attribute__ ((__nonnull__ (4)));
extern size_t fwrite_unlocked (const void *__restrict __ptr, size_t __size,
          size_t __n, FILE *__restrict __stream)
  __attribute__ ((__nonnull__ (4)));
extern int fseek (FILE *__stream, long int __off, int __whence)
  __attribute__ ((__nonnull__ (1)));
extern long int ftell (FILE *__stream) __attribute__ ((__nonnull__ (1)));
extern void rewind (FILE *__stream) __attribute__ ((__nonnull__ (1)));
extern int fseeko (FILE *__stream, __off_t __off, int __whence)
  __attribute__ ((__nonnull__ (1)));
extern __off_t ftello (FILE *__stream) __attribute__ ((__nonnull__ (1)));
extern int fgetpos (FILE *__restrict __stream, fpos_t *__restrict __pos)
  __attribute__ ((__nonnull__ (1)));
extern int fsetpos (FILE *__stream, const fpos_t *__pos) __attribute__ ((__nonnull__ (1)));
extern void clearerr (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern int feof (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern int ferror (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern void clearerr_unlocked (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern int feof_unlocked (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern int ferror_unlocked (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern void perror (const char *__s) __attribute__ ((__cold__));
extern int fileno (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern int fileno_unlocked (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern int pclose (FILE *__stream) __attribute__ ((__nonnull__ (1)));
extern FILE *popen (const char *__command, const char *__modes)
  __attribute__ ((__malloc__)) __attribute__ ((__malloc__ (pclose, 1))) ;
extern char *ctermid (char *__s) __attribute__ ((__nothrow__ , __leaf__))
  __attribute__ ((__access__ (__write_only__, 1)));
extern void flockfile (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern int ftrylockfile (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern void funlockfile (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern int __uflow (FILE *);
extern int __overflow (FILE *, int);

char* stdimpl_strcpy(char *s1, const char *s2);
char* stdimpl_strcat(char *dst, const char *src);
char* stdimpl_strncat(char *dst, const char *src,unsigned int count);
int stdimpl_strlen(const char *str);
int stdimpl_strcmp(const char *s1, const char *s2);
char* stdimpl_itoa(int v,char *string,int r);
void addFailure(const char *msg, long line, const char *file);
void assertImplementationInt(int expected,int actual, long line, const char *file);
void assertImplementationCStr(const char *expected,const char *actual, long line, const char *file);
void assertImplementationInt(int expected,int actual, long line, const char *file)
{
 char buffer[32];
 char numbuf[12];
 stdimpl_strcpy(buffer, "exp ");
 { stdimpl_itoa(expected, numbuf, 10);
  stdimpl_strncat(buffer, numbuf, 11); }
 stdimpl_strcat(buffer, " was ");
 { stdimpl_itoa(actual, numbuf, 10);
  stdimpl_strncat(buffer, numbuf, 11); }
 addFailure(buffer, line, file);
}
void assertImplementationCStr(const char *expected,const char *actual, long line, const char *file)
{
 char buffer[64];
 int el;
 int al;
 if (expected) {
  el = stdimpl_strlen(expected);
 } else {
  el = 4;
  expected = "null";
 }
 if (actual) {
  al = stdimpl_strlen(actual);
 } else {
  al = 4;
  actual = "null";
 }
 if (el > ((64 -11-1)/2)) {
  if (al > ((64 -11-1)/2)) {
   al = ((64 -11-1)/2);
   el = ((64 -11-1)/2);
  } else {
   int w = ((64 -11-1)/2) + (((64 -11-1)/2) - al);
   if (el > w) {
    el = w;
   }
  }
 } else {
  int w = ((64 -11-1)/2) + (((64 -11-1)/2) - el);
  if (al > w) {
   al = w;
  }
 }
 stdimpl_strcpy(buffer, "exp \"");
 stdimpl_strncat(buffer, expected, el);
 stdimpl_strcat(buffer, "\" was \"");
 stdimpl_strncat(buffer, actual, al);
 stdimpl_strcat(buffer, "\"");
 addFailure(buffer, line, file);
}
typedef struct __TestResult TestResult;
typedef struct __TestResult* TestResultRef;
typedef struct __TestImplement TestImplement;
typedef struct __TestImplement* TestImplementRef;
typedef char*(*TestNameFunction)(void*);
typedef void(*TestRunFunction)(void*,TestResult*);
typedef int(*TestCountTestCasesFunction)(void*);
struct __TestImplement {
 TestNameFunction name;
 TestRunFunction run;
 TestCountTestCasesFunction countTestCases;
};
typedef struct __Test Test;
typedef struct __Test* TestRef;
struct __Test {
 TestImplement* isa;
};
typedef struct __RepeatedTest RepeatedTest;
typedef struct __RepeatedTest* RepeatedTestRef;
struct __RepeatedTest {
 TestImplement* isa;
 Test* test;
 int timesRepeat;
};
extern const TestImplement RepeatedTestImplement;
char* RepeatedTest_name(RepeatedTest* self)
{
 return ((Test*)self->test)->isa->name(self->test);
}
void RepeatedTest_run(RepeatedTest* self,TestResult* result)
{
 int i;
 Test* test = self->test;
 for (i=0; i<self->timesRepeat; i++) {
  ((Test*)test)->isa->run(test,result);
 }
}
int RepeatedTest_countTestCases(RepeatedTest* self)
{
 return ((Test*)self->test)->isa->countTestCases(self->test) * self->timesRepeat;
}
const TestImplement RepeatedTestImplement = {
 (TestNameFunction) RepeatedTest_name,
 (TestRunFunction) RepeatedTest_run,
 (TestCountTestCasesFunction)RepeatedTest_countTestCases,
};
char* stdimpl_strcpy(char *dst, const char *src)
{
 char *start = dst;
 char c;
 do {
  c = *src;
  *dst = c;
  src++;
  dst++;
 } while (c);
 return start;
}
char* stdimpl_strcat(char *dst, const char *src)
{
 char *start = dst;
 char c;
 do {
  c = *dst;
  dst++;
 } while (c);
 dst--;
 do {
  c = *src;
  *dst = c;
  src++;
  dst++;
 } while (c);
 return start;
}
char* stdimpl_strncat(char *dst, const char *src,unsigned int count)
{
 char *start = dst;
 char c;
 do {
  c = *dst;
  dst++;
 } while (c);
 dst--;
 if (count) {
  do {
   c = *src;
   *dst = c;
   src++;
   dst++;
   count--;
  } while (c && count);
  *dst = '\0';
 }
 return start;
}
int stdimpl_strlen(const char *str)
{
    const char *estr = str;
 char c;
 do {
  c = *estr;
  estr++;
 } while (c);
    return ((int)(estr - str - 1));
}
int stdimpl_strcmp(const char *s1, const char *s2)
{
 char c1,c2;
 do {
  c1 = *s1++;
  c2 = *s2++;
 } while ((c1) && (c2) && (c1==c2));
 return c1 - c2;
}
static char* _xtoa(unsigned long v,char *string, int r, int is_neg)
{
 char *start = string;
 char buf[33],*p;
 p = buf;
 do {
  *p++ = "0123456789abcdef"[(v % r) & 0xf];
 } while (v /= r);
 if (is_neg) {
  *p++ = '-';
 }
 do {
  *string++ = *--p;
 } while (buf != p);
 *string = '\0';
 return start;
}
char* stdimpl_itoa(int v,char *string,int r)
{
    if ((r == 10) && (v < 0)) {
  return _xtoa((unsigned long)(-v), string, r, 1);
 }
 return _xtoa((unsigned long)(v), string, r, 0);
}
typedef struct __TestCase TestCase;
typedef struct __TestCase* TestCaseRef;
struct __TestCase {
 TestImplement* isa;
 char *name;
 void(*setUp)(void);
 void(*tearDown)(void);
 void(*runTest)(void);
};
extern const TestImplement TestCaseImplement;
typedef struct __TestFixture TestFixture;
typedef struct __TestFixture* TestFixtureRef;
struct __TestFixture {
 char *name;
 void(*test)(void);
};
typedef struct __TestCaller TestCaller;
typedef struct __TestCaller* TestCallerRef;
struct __TestCaller {
 TestImplement* isa;
 char *name;
 void(*setUp)(void);
 void(*tearDown)(void);
 int numberOfFixtuers;
 TestFixture *fixtuers;
};
extern const TestImplement TestCallerImplement;
char* TestCaller_name(TestCaller* self)
{
 return self->name;
}
void TestCaller_run(TestCaller* self,TestResult* result)
{
 TestCase cs = { (TestImplement*)&TestCaseImplement, 0, 0, 0, 0, };
 int i;
 cs.setUp= self->setUp;
 cs.tearDown = self->tearDown;
 for (i=0; i<self->numberOfFixtuers; i++) {
  cs.name = self->fixtuers[i].name;
  cs.runTest = self->fixtuers[i].test;
  ((Test*)&cs)->isa->run(&cs,result);
 }
}
int TestCaller_countTestCases(TestCaller* self)
{
 return self->numberOfFixtuers;
}
const TestImplement TestCallerImplement = {
 (TestNameFunction) TestCaller_name,
 (TestRunFunction) TestCaller_run,
 (TestCountTestCasesFunction)TestCaller_countTestCases,
};
typedef struct __TestListner TestListner;
typedef struct __TestListner* TestListnerRef;
struct __TestResult {
 unsigned short runCount;
 unsigned short failureCount;
 TestListner* listener;
};
void TestResult_init(TestResult* self,TestListner* listner);
void TestResult_startTest(TestResult* self,Test* test);
void TestResult_endTest(TestResult* self,Test* test);
void TestResult_addFailure(TestResult* self,Test* test,const char* msg,int line,const char* file);
static TestResult* embunit_testcase_result_;
static TestCase* self_;
char* TestCase_name(TestCase* self)
{
 return self->name;
}
void TestCase_run(TestCase* self,TestResult* result)
{
 TestResult_startTest(result, (Test*)self);
 if (self->setUp) {
  self->setUp();
 }
 if (self->runTest) {
  TestResult* wr =embunit_testcase_result_;
  TestCase* ws = self_;
  embunit_testcase_result_ = result;
  self_ = self;
  self->runTest();
  embunit_testcase_result_ = wr;
  self_ = ws;
 }
 if (self->tearDown) {
  self->tearDown();
 }
 TestResult_endTest(result, (Test*)self);
}
int TestCase_countTestCases(TestCase* self)
{
 return 1;
}
const TestImplement TestCaseImplement = {
 (TestNameFunction) TestCase_name,
 (TestRunFunction) TestCase_run,
 (TestCountTestCasesFunction)TestCase_countTestCases,
};
void addFailure(const char *msg, long line, const char *file)
{
 TestResult_addFailure(embunit_testcase_result_, (Test*)self_, (char*)msg, line, (char*)file);
}
typedef struct __TestListnerImplement TestListnerImplement;
typedef struct __TestListnerImplement* TestListnerImplementRef;
typedef void(*TestListnerStartTestCallBack)(void*,void*);
typedef void(*TestListnerEndTestCallBack)(void*,void*);
typedef void(*TestListnerAddFailureCallBack)(void*,void*,const char*,int,const char*);
struct __TestListnerImplement {
 TestListnerStartTestCallBack startTest;
 TestListnerEndTestCallBack endTest;
 TestListnerAddFailureCallBack addFailure;
};
struct __TestListner {
 TestListnerImplement* isa;
};
void TestResult_init(TestResult* self,TestListner* listner)
{
 self->runCount = 0;
 self->failureCount = 0;
 self->listener = listner;
}
void TestResult_startTest(TestResult* self,Test* test)
{
 self->runCount++;
 if (self->listener) {
  ((TestListner*)self->listener)->isa->startTest(self->listener,test);
 }
}
void TestResult_endTest(TestResult* self,Test* test)
{
 if (self->listener) {
  ((TestListner*)self->listener)->isa->endTest(self->listener,test);
 }
}
void TestResult_addFailure(TestResult* self,Test* test,const char* msg,int line,const char* file)
{
 self->failureCount++;
 if (self->listener) {
  ((TestListner*)self->listener)->isa->addFailure(self->listener,test,msg,line,file);
 }
}
void TestRunner_start(void);
void TestRunner_runTest(Test* test);
void TestRunner_end(void);
static TestResult result_;
static Test* root_;
static void TestRunner_startTest(TestListner* self,Test* test)
{
 printf(".");
}
static void TestRunner_endTest(TestListner* self,Test* test)
{
}
static void TestRunner_addFailure(TestListner* self,Test* test,char* msg,int line,char* file)
{
 printf("\n");
 printf("%s",((Test*)root_)->isa->name(root_));
 printf(".");
 printf("%s",((Test*)test)->isa->name(test));
 {
  char buf[16];
  printf(" (");
  printf("%s",file);
  printf(" ");
  stdimpl_itoa(line, buf, 10);
  printf("%s",buf);
  printf(") ");
 }
 printf("%s",msg);
 printf("\n");
}
static const TestListnerImplement TestRunnerImplement = {
 (TestListnerStartTestCallBack) TestRunner_startTest,
 (TestListnerEndTestCallBack) TestRunner_endTest,
 (TestListnerAddFailureCallBack) TestRunner_addFailure,
};
static const TestListner testrunner_ = {
 (TestListnerImplement*)&TestRunnerImplement,
};
void TestRunner_start(void)
{
 TestResult_init(&result_, (TestListner*)&testrunner_);
}
void TestRunner_runTest(Test* test)
{
 root_ = test;
 ((Test*)test)->isa->run(test,&result_);
}
void TestRunner_end(void)
{
 char buf[16];
 if (result_.failureCount) {
  printf("\nrun ");
  stdimpl_itoa(result_.runCount, buf, 10);
  printf("%s",buf);
  printf(" failures ");
  stdimpl_itoa(result_.failureCount, buf, 10);
  printf("%s",buf);
  printf("\n");
 } else {
  printf("\nOK (");
  stdimpl_itoa(result_.runCount, buf, 10);
  printf("%s",buf);
  if(result_.runCount==1){
   printf(" test)\n");
  }
  else{
   printf(" tests)\n");
  }
 }
}
typedef struct __TestSuite TestSuite;
typedef struct __TestSuite* TestSuiteRef;
struct __TestSuite {
 TestImplement* isa;
 char *name;
 int numberOfTests;
 Test** tests;
};
extern const TestImplement TestSuiteImplement;
char* TestSuite_name(TestSuite* self)
{
 return self->name;
}
void TestSuite_run(TestSuite* self,TestResult* result)
{
 int i;
 Test* test;
 if (self->tests) {
  for (i=0; i<self->numberOfTests; i++) {
   test = self->tests[i];
   ((Test*)test)->isa->run(test,result);
  }
 }
}
int TestSuite_countTestCases(TestSuite* self)
{
 int count = 0;
 int i;
 Test* test;
 if (self->tests) {
  for (i=0; i<self->numberOfTests; i++) {
   test = self->tests[i];
   count += ((Test*)test)->isa->countTestCases(test);
  }
 }
 return count;
}
const TestImplement TestSuiteImplement = {
 (TestNameFunction) TestSuite_name,
 (TestRunFunction) TestSuite_run,
 (TestCountTestCasesFunction)TestSuite_countTestCases,
};
void assertImplementationInt(int expected,int actual, long line, const char *file);
unsigned char test_number = 0;
typedef __int8_t int8_t;
typedef __int16_t int16_t;
typedef __int32_t int32_t;
typedef __int64_t int64_t;
typedef __uint8_t uint8_t;
typedef __uint16_t uint16_t;
typedef __uint32_t uint32_t;
typedef __uint64_t uint64_t;
typedef __int_least8_t int_least8_t;
typedef __int_least16_t int_least16_t;
typedef __int_least32_t int_least32_t;
typedef __int_least64_t int_least64_t;
typedef __uint_least8_t uint_least8_t;
typedef __uint_least16_t uint_least16_t;
typedef __uint_least32_t uint_least32_t;
typedef __uint_least64_t uint_least64_t;
typedef signed char int_fast8_t;
typedef long int int_fast16_t;
typedef long int int_fast32_t;
typedef long int int_fast64_t;
typedef unsigned char uint_fast8_t;
typedef unsigned long int uint_fast16_t;
typedef unsigned long int uint_fast32_t;
typedef unsigned long int uint_fast64_t;
typedef long int intptr_t;
typedef unsigned long int uintptr_t;
typedef __intmax_t intmax_t;
typedef __uintmax_t uintmax_t;
typedef uint8_t uint8;
typedef int8_t sint8;
typedef uint16_t uint16;
typedef int16_t sint16;
typedef uint32_t uint32;
typedef int32_t sint32;
typedef uint8 tpl_heap_key;
typedef uint8 tpl_rank_count;
typedef sint8 tpl_proc_id;
typedef uint8 tpl_appmode_mask;
typedef uint8 tpl_priority;
typedef uint8 tpl_activate_counter;
typedef uint8 tpl_event_mask;
typedef uint8 tpl_alarm_id;
typedef uint8 tpl_resource_id;
typedef uint8 tpl_counter_id;
typedef uint8 tpl_schedtable_id;
typedef uint8 tpl_app_id;
typedef uint8 tpl_generic_id;
typedef uint32 tpl_tick;
typedef uint8 * tpl_buffer;
typedef uint32 tpl_time;

typedef long int __jmp_buf[8];
typedef struct
{
  unsigned long int __val[(1024 / (8 * sizeof (unsigned long int)))];
} __sigset_t;
struct __jmp_buf_tag
  {
    __jmp_buf __jmpbuf;
    int __mask_was_saved;
    __sigset_t __saved_mask;
  };
typedef struct __jmp_buf_tag jmp_buf[1];
extern int setjmp (jmp_buf __env) __attribute__ ((__nothrow__));
extern int __sigsetjmp (struct __jmp_buf_tag __env[1], int __savemask) __attribute__ ((__nothrow__));
extern int _setjmp (struct __jmp_buf_tag __env[1]) __attribute__ ((__nothrow__));
extern void longjmp (struct __jmp_buf_tag __env[1], int __val)
     __attribute__ ((__nothrow__)) __attribute__ ((__noreturn__));
extern void _longjmp (struct __jmp_buf_tag __env[1], int __val)
     __attribute__ ((__nothrow__)) __attribute__ ((__noreturn__));
typedef struct __jmp_buf_tag sigjmp_buf[1];
extern void siglongjmp (sigjmp_buf __env, int __val)
     __attribute__ ((__nothrow__)) __attribute__ ((__noreturn__));


typedef __sig_atomic_t sig_atomic_t;
typedef __sigset_t sigset_t;
typedef __pid_t pid_t;
typedef __uid_t uid_t;
typedef __time_t time_t;
struct timespec
{
  __time_t tv_sec;
  __syscall_slong_t tv_nsec;
};
union sigval
{
  int sival_int;
  void *sival_ptr;
};
typedef union sigval __sigval_t;
typedef struct
  {
    int si_signo;
    int si_errno;
    int si_code;
    int __pad0;
    union
      {
 int _pad[((128 / sizeof (int)) - 4)];
 struct
   {
     __pid_t si_pid;
     __uid_t si_uid;
   } _kill;
 struct
   {
     int si_tid;
     int si_overrun;
     __sigval_t si_sigval;
   } _timer;
 struct
   {
     __pid_t si_pid;
     __uid_t si_uid;
     __sigval_t si_sigval;
   } _rt;
 struct
   {
     __pid_t si_pid;
     __uid_t si_uid;
     int si_status;
     __clock_t si_utime;
     __clock_t si_stime;
   } _sigchld;
 struct
   {
     void *si_addr;

     short int si_addr_lsb;
     union
       {
  struct
    {
      void *_lower;
      void *_upper;
    } _addr_bnd;
  __uint32_t _pkey;
       } _bounds;
   } _sigfault;
 struct
   {
     long int si_band;
     int si_fd;
   } _sigpoll;
 struct
   {
     void *_call_addr;
     int _syscall;
     unsigned int _arch;
   } _sigsys;
      } _sifields;
  } siginfo_t ;
enum
{
  SI_ASYNCNL = -60,
  SI_DETHREAD = -7,
  SI_TKILL,
  SI_SIGIO,
  SI_ASYNCIO,
  SI_MESGQ,
  SI_TIMER,
  SI_QUEUE,
  SI_USER,
  SI_KERNEL = 0x80
};
enum
{
  ILL_ILLOPC = 1,
  ILL_ILLOPN,
  ILL_ILLADR,
  ILL_ILLTRP,
  ILL_PRVOPC,
  ILL_PRVREG,
  ILL_COPROC,
  ILL_BADSTK,
  ILL_BADIADDR
};
enum
{
  FPE_INTDIV = 1,
  FPE_INTOVF,
  FPE_FLTDIV,
  FPE_FLTOVF,
  FPE_FLTUND,
  FPE_FLTRES,
  FPE_FLTINV,
  FPE_FLTSUB,
  FPE_FLTUNK = 14,
  FPE_CONDTRAP
};
enum
{
  SEGV_MAPERR = 1,
  SEGV_ACCERR,
  SEGV_BNDERR,
  SEGV_PKUERR,
  SEGV_ACCADI,
  SEGV_ADIDERR,
  SEGV_ADIPERR,
  SEGV_MTEAERR,
  SEGV_MTESERR,
  SEGV_CPERR
};
enum
{
  BUS_ADRALN = 1,
  BUS_ADRERR,
  BUS_OBJERR,
  BUS_MCEERR_AR,
  BUS_MCEERR_AO
};
enum
{
  CLD_EXITED = 1,
  CLD_KILLED,
  CLD_DUMPED,
  CLD_TRAPPED,
  CLD_STOPPED,
  CLD_CONTINUED
};
enum
{
  POLL_IN = 1,
  POLL_OUT,
  POLL_MSG,
  POLL_ERR,
  POLL_PRI,
  POLL_HUP
};
typedef __sigval_t sigval_t;
typedef union pthread_attr_t pthread_attr_t;
typedef struct sigevent
  {
    __sigval_t sigev_value;
    int sigev_signo;
    int sigev_notify;
    union
      {
 int _pad[((64 / sizeof (int)) - 4)];
 __pid_t _tid;
 struct
   {
     void (*_function) (__sigval_t);
     pthread_attr_t *_attribute;
   } _sigev_thread;
      } _sigev_un;
  } sigevent_t;
enum
{
  SIGEV_SIGNAL = 0,
  SIGEV_NONE,
  SIGEV_THREAD,
  SIGEV_THREAD_ID = 4
};
typedef void (*__sighandler_t) (int);
extern __sighandler_t __sysv_signal (int __sig, __sighandler_t __handler)
     __attribute__ ((__nothrow__ , __leaf__));
extern __sighandler_t signal (int __sig, __sighandler_t __handler)
     __attribute__ ((__nothrow__ , __leaf__));
extern int kill (__pid_t __pid, int __sig) __attribute__ ((__nothrow__ , __leaf__));
extern int killpg (__pid_t __pgrp, int __sig) __attribute__ ((__nothrow__ , __leaf__));
extern int raise (int __sig) __attribute__ ((__nothrow__ , __leaf__));
extern __sighandler_t ssignal (int __sig, __sighandler_t __handler)
     __attribute__ ((__nothrow__ , __leaf__));
extern int gsignal (int __sig) __attribute__ ((__nothrow__ , __leaf__));
extern void psignal (int __sig, const char *__s);
extern void psiginfo (const siginfo_t *__pinfo, const char *__s);
extern int sigblock (int __mask) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__deprecated__));
extern int sigsetmask (int __mask) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__deprecated__));
extern int siggetmask (void) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__deprecated__));
typedef __sighandler_t sig_t;
extern int sigemptyset (sigset_t *__set) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern int sigfillset (sigset_t *__set) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern int sigaddset (sigset_t *__set, int __signo) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern int sigdelset (sigset_t *__set, int __signo) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern int sigismember (const sigset_t *__set, int __signo)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
struct sigaction
  {
    union
      {
 __sighandler_t sa_handler;
 void (*sa_sigaction) (int, siginfo_t *, void *);
      }
    __sigaction_handler;
    __sigset_t sa_mask;
    int sa_flags;
    void (*sa_restorer) (void);
  };
extern int sigprocmask (int __how, const sigset_t *__restrict __set,
   sigset_t *__restrict __oset) __attribute__ ((__nothrow__ , __leaf__));
extern int sigsuspend (const sigset_t *__set) __attribute__ ((__nonnull__ (1)));
extern int sigaction (int __sig, const struct sigaction *__restrict __act,
        struct sigaction *__restrict __oact) __attribute__ ((__nothrow__ , __leaf__));
extern int sigpending (sigset_t *__set) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern int sigwait (const sigset_t *__restrict __set, int *__restrict __sig)
     __attribute__ ((__nonnull__ (1, 2)));
extern int sigwaitinfo (const sigset_t *__restrict __set,
   siginfo_t *__restrict __info) __attribute__ ((__nonnull__ (1)));
extern int sigtimedwait (const sigset_t *__restrict __set,
    siginfo_t *__restrict __info,
    const struct timespec *__restrict __timeout)
     __attribute__ ((__nonnull__ (1)));
extern int sigqueue (__pid_t __pid, int __sig, const union sigval __val)
     __attribute__ ((__nothrow__ , __leaf__));
struct _fpx_sw_bytes
{
  __uint32_t magic1;
  __uint32_t extended_size;
  __uint64_t xstate_bv;
  __uint32_t xstate_size;
  __uint32_t __glibc_reserved1[7];
};
struct _fpreg
{
  unsigned short significand[4];
  unsigned short exponent;
};
struct _fpxreg
{
  unsigned short significand[4];
  unsigned short exponent;
  unsigned short __glibc_reserved1[3];
};
struct _xmmreg
{
  __uint32_t element[4];
};
struct _fpstate
{
  __uint16_t cwd;
  __uint16_t swd;
  __uint16_t ftw;
  __uint16_t fop;
  __uint64_t rip;
  __uint64_t rdp;
  __uint32_t mxcsr;
  __uint32_t mxcr_mask;
  struct _fpxreg _st[8];
  struct _xmmreg _xmm[16];
  __uint32_t __glibc_reserved1[24];
};
struct sigcontext
{
  __uint64_t r8;
  __uint64_t r9;
  __uint64_t r10;
  __uint64_t r11;
  __uint64_t r12;
  __uint64_t r13;
  __uint64_t r14;
  __uint64_t r15;
  __uint64_t rdi;
  __uint64_t rsi;
  __uint64_t rbp;
  __uint64_t rbx;
  __uint64_t rdx;
  __uint64_t rax;
  __uint64_t rcx;
  __uint64_t rsp;
  __uint64_t rip;
  __uint64_t eflags;
  unsigned short cs;
  unsigned short gs;
  unsigned short fs;
  unsigned short __pad0;
  __uint64_t err;
  __uint64_t trapno;
  __uint64_t oldmask;
  __uint64_t cr2;
  __extension__ union
    {
      struct _fpstate * fpstate;
      __uint64_t __fpstate_word;
    };
  __uint64_t __reserved1 [8];
};
struct _xsave_hdr
{
  __uint64_t xstate_bv;
  __uint64_t __glibc_reserved1[2];
  __uint64_t __glibc_reserved2[5];
};
struct _ymmh_state
{
  __uint32_t ymmh_space[64];
};
struct _xstate
{
  struct _fpstate fpstate;
  struct _xsave_hdr xstate_hdr;
  struct _ymmh_state ymmh;
};
extern int sigreturn (struct sigcontext *__scp) __attribute__ ((__nothrow__ , __leaf__));
typedef struct
  {
    void *ss_sp;
    int ss_flags;
    size_t ss_size;
  } stack_t;
__extension__ typedef long long int greg_t;
typedef greg_t gregset_t[23];
struct _libc_fpxreg
{
  unsigned short int significand[4];
  unsigned short int exponent;
  unsigned short int __glibc_reserved1[3];
};
struct _libc_xmmreg
{
  __uint32_t element[4];
};
struct _libc_fpstate
{
  __uint16_t cwd;
  __uint16_t swd;
  __uint16_t ftw;
  __uint16_t fop;
  __uint64_t rip;
  __uint64_t rdp;
  __uint32_t mxcsr;
  __uint32_t mxcr_mask;
  struct _libc_fpxreg _st[8];
  struct _libc_xmmreg _xmm[16];
  __uint32_t __glibc_reserved1[24];
};
typedef struct _libc_fpstate *fpregset_t;
typedef struct
  {
    gregset_t gregs;
    fpregset_t fpregs;
    __extension__ unsigned long long __reserved1 [8];
} mcontext_t;
typedef struct ucontext_t
  {
    unsigned long int uc_flags;
    struct ucontext_t *uc_link;
    stack_t uc_stack;
    mcontext_t uc_mcontext;
    sigset_t uc_sigmask;
    struct _libc_fpstate __fpregs_mem;
    __extension__ unsigned long long int __ssp[4];
  } ucontext_t;
extern int siginterrupt (int __sig, int __interrupt) __attribute__ ((__nothrow__ , __leaf__))
  __attribute__ ((__deprecated__ ("Use sigaction with SA_RESTART instead")));
enum
{
  SS_ONSTACK = 1,
  SS_DISABLE
};
extern int sigaltstack (const stack_t *__restrict __ss,
   stack_t *__restrict __oss) __attribute__ ((__nothrow__ , __leaf__));
struct sigstack
  {
    void *ss_sp;
    int ss_onstack;
  };
extern int sigstack (struct sigstack *__ss, struct sigstack *__oss)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__deprecated__));
typedef union
{
  __extension__ unsigned long long int __value64;
  struct
  {
    unsigned int __low;
    unsigned int __high;
  } __value32;
} __atomic_wide_counter;
typedef struct __pthread_internal_list
{
  struct __pthread_internal_list *__prev;
  struct __pthread_internal_list *__next;
} __pthread_list_t;
typedef struct __pthread_internal_slist
{
  struct __pthread_internal_slist *__next;
} __pthread_slist_t;
struct __pthread_mutex_s
{
  int __lock;
  unsigned int __count;
  int __owner;
  unsigned int __nusers;
  int __kind;
  short __spins;
  short __elision;
  __pthread_list_t __list;
};
struct __pthread_rwlock_arch_t
{
  unsigned int __readers;
  unsigned int __writers;
  unsigned int __wrphase_futex;
  unsigned int __writers_futex;
  unsigned int __pad3;
  unsigned int __pad4;
  int __cur_writer;
  int __shared;
  signed char __rwelision;
  unsigned char __pad1[7];
  unsigned long int __pad2;
  unsigned int __flags;
};
struct __pthread_cond_s
{
  __atomic_wide_counter __wseq;
  __atomic_wide_counter __g1_start;
  unsigned int __g_size[2] ;
  unsigned int __g1_orig_size;
  unsigned int __wrefs;
  unsigned int __g_signals[2];
  unsigned int __unused_initialized_1;
  unsigned int __unused_initialized_2;
};
typedef unsigned int __tss_t;
typedef unsigned long int __thrd_t;
typedef struct
{
  int __data ;
} __once_flag;
typedef unsigned long int pthread_t;
typedef union
{
  char __size[4];
  int __align;
} pthread_mutexattr_t;
typedef union
{
  char __size[4];
  int __align;
} pthread_condattr_t;
typedef unsigned int pthread_key_t;
typedef int pthread_once_t;
union pthread_attr_t
{
  char __size[56];
  long int __align;
};
typedef union
{
  struct __pthread_mutex_s __data;
  char __size[40];
  long int __align;
} pthread_mutex_t;
typedef union
{
  struct __pthread_cond_s __data;
  char __size[48];
  __extension__ long long int __align;
} pthread_cond_t;
typedef union
{
  struct __pthread_rwlock_arch_t __data;
  char __size[56];
  long int __align;
} pthread_rwlock_t;
typedef union
{
  char __size[8];
  long int __align;
} pthread_rwlockattr_t;
typedef volatile int pthread_spinlock_t;
typedef union
{
  char __size[32];
  long int __align;
} pthread_barrier_t;
typedef union
{
  char __size[4];
  int __align;
} pthread_barrierattr_t;
extern int pthread_sigmask (int __how,
       const __sigset_t *__restrict __newmask,
       __sigset_t *__restrict __oldmask)__attribute__ ((__nothrow__ , __leaf__));
extern int pthread_kill (pthread_t __threadid, int __signo) __attribute__ ((__nothrow__ , __leaf__));
extern int __libc_current_sigrtmin (void) __attribute__ ((__nothrow__ , __leaf__));
extern int __libc_current_sigrtmax (void) __attribute__ ((__nothrow__ , __leaf__));


typedef __gid_t gid_t;
typedef __useconds_t useconds_t;
typedef __socklen_t socklen_t;
extern int access (const char *__name, int __type) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern int faccessat (int __fd, const char *__file, int __type, int __flag)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2))) ;
extern __off_t lseek (int __fd, __off_t __offset, int __whence) __attribute__ ((__nothrow__ , __leaf__));
extern int close (int __fd);
extern void closefrom (int __lowfd) __attribute__ ((__nothrow__ , __leaf__));
extern ssize_t read (int __fd, void *__buf, size_t __nbytes)
    __attribute__ ((__access__ (__write_only__, 2, 3)));
extern ssize_t write (int __fd, const void *__buf, size_t __n)
    __attribute__ ((__access__ (__read_only__, 2, 3)));
extern ssize_t pread (int __fd, void *__buf, size_t __nbytes,
        __off_t __offset)
    __attribute__ ((__access__ (__write_only__, 2, 3)));
extern ssize_t pwrite (int __fd, const void *__buf, size_t __n,
         __off_t __offset)
    __attribute__ ((__access__ (__read_only__, 2, 3)));
extern int pipe (int __pipedes[2]) __attribute__ ((__nothrow__ , __leaf__)) ;
extern unsigned int alarm (unsigned int __seconds) __attribute__ ((__nothrow__ , __leaf__));
extern unsigned int sleep (unsigned int __seconds);
extern __useconds_t ualarm (__useconds_t __value, __useconds_t __interval)
     __attribute__ ((__nothrow__ , __leaf__));
extern int usleep (__useconds_t __useconds);
extern int pause (void);
extern int chown (const char *__file, __uid_t __owner, __gid_t __group)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) ;
extern int fchown (int __fd, __uid_t __owner, __gid_t __group) __attribute__ ((__nothrow__ , __leaf__)) ;
extern int lchown (const char *__file, __uid_t __owner, __gid_t __group)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) ;
extern int fchownat (int __fd, const char *__file, __uid_t __owner,
       __gid_t __group, int __flag)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2))) ;
extern int chdir (const char *__path) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) ;
extern int fchdir (int __fd) __attribute__ ((__nothrow__ , __leaf__)) ;
extern char *getcwd (char *__buf, size_t __size) __attribute__ ((__nothrow__ , __leaf__)) ;
extern char *getwd (char *__buf)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) __attribute__ ((__deprecated__))
    __attribute__ ((__access__ (__write_only__, 1)));
extern int dup (int __fd) __attribute__ ((__nothrow__ , __leaf__)) ;
extern int dup2 (int __fd, int __fd2) __attribute__ ((__nothrow__ , __leaf__));
extern char **__environ;
extern int execve (const char *__path, char *const __argv[],
     char *const __envp[]) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern int fexecve (int __fd, char *const __argv[], char *const __envp[])
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2)));
extern int execv (const char *__path, char *const __argv[])
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern int execle (const char *__path, const char *__arg, ...)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern int execl (const char *__path, const char *__arg, ...)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern int execvp (const char *__file, char *const __argv[])
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern int execlp (const char *__file, const char *__arg, ...)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern int nice (int __inc) __attribute__ ((__nothrow__ , __leaf__)) ;
extern void _exit (int __status) __attribute__ ((__noreturn__));
enum
  {
    _PC_LINK_MAX,
    _PC_MAX_CANON,
    _PC_MAX_INPUT,
    _PC_NAME_MAX,
    _PC_PATH_MAX,
    _PC_PIPE_BUF,
    _PC_CHOWN_RESTRICTED,
    _PC_NO_TRUNC,
    _PC_VDISABLE,
    _PC_SYNC_IO,
    _PC_ASYNC_IO,
    _PC_PRIO_IO,
    _PC_SOCK_MAXBUF,
    _PC_FILESIZEBITS,
    _PC_REC_INCR_XFER_SIZE,
    _PC_REC_MAX_XFER_SIZE,
    _PC_REC_MIN_XFER_SIZE,
    _PC_REC_XFER_ALIGN,
    _PC_ALLOC_SIZE_MIN,
    _PC_SYMLINK_MAX,
    _PC_2_SYMLINKS
  };
enum
  {
    _SC_ARG_MAX,
    _SC_CHILD_MAX,
    _SC_CLK_TCK,
    _SC_NGROUPS_MAX,
    _SC_OPEN_MAX,
    _SC_STREAM_MAX,
    _SC_TZNAME_MAX,
    _SC_JOB_CONTROL,
    _SC_SAVED_IDS,
    _SC_REALTIME_SIGNALS,
    _SC_PRIORITY_SCHEDULING,
    _SC_TIMERS,
    _SC_ASYNCHRONOUS_IO,
    _SC_PRIORITIZED_IO,
    _SC_SYNCHRONIZED_IO,
    _SC_FSYNC,
    _SC_MAPPED_FILES,
    _SC_MEMLOCK,
    _SC_MEMLOCK_RANGE,
    _SC_MEMORY_PROTECTION,
    _SC_MESSAGE_PASSING,
    _SC_SEMAPHORES,
    _SC_SHARED_MEMORY_OBJECTS,
    _SC_AIO_LISTIO_MAX,
    _SC_AIO_MAX,
    _SC_AIO_PRIO_DELTA_MAX,
    _SC_DELAYTIMER_MAX,
    _SC_MQ_OPEN_MAX,
    _SC_MQ_PRIO_MAX,
    _SC_VERSION,
    _SC_PAGESIZE,
    _SC_RTSIG_MAX,
    _SC_SEM_NSEMS_MAX,
    _SC_SEM_VALUE_MAX,
    _SC_SIGQUEUE_MAX,
    _SC_TIMER_MAX,
    _SC_BC_BASE_MAX,
    _SC_BC_DIM_MAX,
    _SC_BC_SCALE_MAX,
    _SC_BC_STRING_MAX,
    _SC_COLL_WEIGHTS_MAX,
    _SC_EQUIV_CLASS_MAX,
    _SC_EXPR_NEST_MAX,
    _SC_LINE_MAX,
    _SC_RE_DUP_MAX,
    _SC_CHARCLASS_NAME_MAX,
    _SC_2_VERSION,
    _SC_2_C_BIND,
    _SC_2_C_DEV,
    _SC_2_FORT_DEV,
    _SC_2_FORT_RUN,
    _SC_2_SW_DEV,
    _SC_2_LOCALEDEF,
    _SC_PII,
    _SC_PII_XTI,
    _SC_PII_SOCKET,
    _SC_PII_INTERNET,
    _SC_PII_OSI,
    _SC_POLL,
    _SC_SELECT,
    _SC_UIO_MAXIOV,
    _SC_IOV_MAX = _SC_UIO_MAXIOV,
    _SC_PII_INTERNET_STREAM,
    _SC_PII_INTERNET_DGRAM,
    _SC_PII_OSI_COTS,
    _SC_PII_OSI_CLTS,
    _SC_PII_OSI_M,
    _SC_T_IOV_MAX,
    _SC_THREADS,
    _SC_THREAD_SAFE_FUNCTIONS,
    _SC_GETGR_R_SIZE_MAX,
    _SC_GETPW_R_SIZE_MAX,
    _SC_LOGIN_NAME_MAX,
    _SC_TTY_NAME_MAX,
    _SC_THREAD_DESTRUCTOR_ITERATIONS,
    _SC_THREAD_KEYS_MAX,
    _SC_THREAD_STACK_MIN,
    _SC_THREAD_THREADS_MAX,
    _SC_THREAD_ATTR_STACKADDR,
    _SC_THREAD_ATTR_STACKSIZE,
    _SC_THREAD_PRIORITY_SCHEDULING,
    _SC_THREAD_PRIO_INHERIT,
    _SC_THREAD_PRIO_PROTECT,
    _SC_THREAD_PROCESS_SHARED,
    _SC_NPROCESSORS_CONF,
    _SC_NPROCESSORS_ONLN,
    _SC_PHYS_PAGES,
    _SC_AVPHYS_PAGES,
    _SC_ATEXIT_MAX,
    _SC_PASS_MAX,
    _SC_XOPEN_VERSION,
    _SC_XOPEN_XCU_VERSION,
    _SC_XOPEN_UNIX,
    _SC_XOPEN_CRYPT,
    _SC_XOPEN_ENH_I18N,
    _SC_XOPEN_SHM,
    _SC_2_CHAR_TERM,
    _SC_2_C_VERSION,
    _SC_2_UPE,
    _SC_XOPEN_XPG2,
    _SC_XOPEN_XPG3,
    _SC_XOPEN_XPG4,
    _SC_CHAR_BIT,
    _SC_CHAR_MAX,
    _SC_CHAR_MIN,
    _SC_INT_MAX,
    _SC_INT_MIN,
    _SC_LONG_BIT,
    _SC_WORD_BIT,
    _SC_MB_LEN_MAX,
    _SC_NZERO,
    _SC_SSIZE_MAX,
    _SC_SCHAR_MAX,
    _SC_SCHAR_MIN,
    _SC_SHRT_MAX,
    _SC_SHRT_MIN,
    _SC_UCHAR_MAX,
    _SC_UINT_MAX,
    _SC_ULONG_MAX,
    _SC_USHRT_MAX,
    _SC_NL_ARGMAX,
    _SC_NL_LANGMAX,
    _SC_NL_MSGMAX,
    _SC_NL_NMAX,
    _SC_NL_SETMAX,
    _SC_NL_TEXTMAX,
    _SC_XBS5_ILP32_OFF32,
    _SC_XBS5_ILP32_OFFBIG,
    _SC_XBS5_LP64_OFF64,
    _SC_XBS5_LPBIG_OFFBIG,
    _SC_XOPEN_LEGACY,
    _SC_XOPEN_REALTIME,
    _SC_XOPEN_REALTIME_THREADS,
    _SC_ADVISORY_INFO,
    _SC_BARRIERS,
    _SC_BASE,
    _SC_C_LANG_SUPPORT,
    _SC_C_LANG_SUPPORT_R,
    _SC_CLOCK_SELECTION,
    _SC_CPUTIME,
    _SC_THREAD_CPUTIME,
    _SC_DEVICE_IO,
    _SC_DEVICE_SPECIFIC,
    _SC_DEVICE_SPECIFIC_R,
    _SC_FD_MGMT,
    _SC_FIFO,
    _SC_PIPE,
    _SC_FILE_ATTRIBUTES,
    _SC_FILE_LOCKING,
    _SC_FILE_SYSTEM,
    _SC_MONOTONIC_CLOCK,
    _SC_MULTI_PROCESS,
    _SC_SINGLE_PROCESS,
    _SC_NETWORKING,
    _SC_READER_WRITER_LOCKS,
    _SC_SPIN_LOCKS,
    _SC_REGEXP,
    _SC_REGEX_VERSION,
    _SC_SHELL,
    _SC_SIGNALS,
    _SC_SPAWN,
    _SC_SPORADIC_SERVER,
    _SC_THREAD_SPORADIC_SERVER,
    _SC_SYSTEM_DATABASE,
    _SC_SYSTEM_DATABASE_R,
    _SC_TIMEOUTS,
    _SC_TYPED_MEMORY_OBJECTS,
    _SC_USER_GROUPS,
    _SC_USER_GROUPS_R,
    _SC_2_PBS,
    _SC_2_PBS_ACCOUNTING,
    _SC_2_PBS_LOCATE,
    _SC_2_PBS_MESSAGE,
    _SC_2_PBS_TRACK,
    _SC_SYMLOOP_MAX,
    _SC_STREAMS,
    _SC_2_PBS_CHECKPOINT,
    _SC_V6_ILP32_OFF32,
    _SC_V6_ILP32_OFFBIG,
    _SC_V6_LP64_OFF64,
    _SC_V6_LPBIG_OFFBIG,
    _SC_HOST_NAME_MAX,
    _SC_TRACE,
    _SC_TRACE_EVENT_FILTER,
    _SC_TRACE_INHERIT,
    _SC_TRACE_LOG,
    _SC_LEVEL1_ICACHE_SIZE,
    _SC_LEVEL1_ICACHE_ASSOC,
    _SC_LEVEL1_ICACHE_LINESIZE,
    _SC_LEVEL1_DCACHE_SIZE,
    _SC_LEVEL1_DCACHE_ASSOC,
    _SC_LEVEL1_DCACHE_LINESIZE,
    _SC_LEVEL2_CACHE_SIZE,
    _SC_LEVEL2_CACHE_ASSOC,
    _SC_LEVEL2_CACHE_LINESIZE,
    _SC_LEVEL3_CACHE_SIZE,
    _SC_LEVEL3_CACHE_ASSOC,
    _SC_LEVEL3_CACHE_LINESIZE,
    _SC_LEVEL4_CACHE_SIZE,
    _SC_LEVEL4_CACHE_ASSOC,
    _SC_LEVEL4_CACHE_LINESIZE,
    _SC_IPV6 = _SC_LEVEL1_ICACHE_SIZE + 50,
    _SC_RAW_SOCKETS,
    _SC_V7_ILP32_OFF32,
    _SC_V7_ILP32_OFFBIG,
    _SC_V7_LP64_OFF64,
    _SC_V7_LPBIG_OFFBIG,
    _SC_SS_REPL_MAX,
    _SC_TRACE_EVENT_NAME_MAX,
    _SC_TRACE_NAME_MAX,
    _SC_TRACE_SYS_MAX,
    _SC_TRACE_USER_EVENT_MAX,
    _SC_XOPEN_STREAMS,
    _SC_THREAD_ROBUST_PRIO_INHERIT,
    _SC_THREAD_ROBUST_PRIO_PROTECT,
    _SC_MINSIGSTKSZ,
    _SC_SIGSTKSZ
  };
enum
  {
    _CS_PATH,
    _CS_V6_WIDTH_RESTRICTED_ENVS,
    _CS_GNU_LIBC_VERSION,
    _CS_GNU_LIBPTHREAD_VERSION,
    _CS_V5_WIDTH_RESTRICTED_ENVS,
    _CS_V7_WIDTH_RESTRICTED_ENVS,
    _CS_LFS_CFLAGS = 1000,
    _CS_LFS_LDFLAGS,
    _CS_LFS_LIBS,
    _CS_LFS_LINTFLAGS,
    _CS_LFS64_CFLAGS,
    _CS_LFS64_LDFLAGS,
    _CS_LFS64_LIBS,
    _CS_LFS64_LINTFLAGS,
    _CS_XBS5_ILP32_OFF32_CFLAGS = 1100,
    _CS_XBS5_ILP32_OFF32_LDFLAGS,
    _CS_XBS5_ILP32_OFF32_LIBS,
    _CS_XBS5_ILP32_OFF32_LINTFLAGS,
    _CS_XBS5_ILP32_OFFBIG_CFLAGS,
    _CS_XBS5_ILP32_OFFBIG_LDFLAGS,
    _CS_XBS5_ILP32_OFFBIG_LIBS,
    _CS_XBS5_ILP32_OFFBIG_LINTFLAGS,
    _CS_XBS5_LP64_OFF64_CFLAGS,
    _CS_XBS5_LP64_OFF64_LDFLAGS,
    _CS_XBS5_LP64_OFF64_LIBS,
    _CS_XBS5_LP64_OFF64_LINTFLAGS,
    _CS_XBS5_LPBIG_OFFBIG_CFLAGS,
    _CS_XBS5_LPBIG_OFFBIG_LDFLAGS,
    _CS_XBS5_LPBIG_OFFBIG_LIBS,
    _CS_XBS5_LPBIG_OFFBIG_LINTFLAGS,
    _CS_POSIX_V6_ILP32_OFF32_CFLAGS,
    _CS_POSIX_V6_ILP32_OFF32_LDFLAGS,
    _CS_POSIX_V6_ILP32_OFF32_LIBS,
    _CS_POSIX_V6_ILP32_OFF32_LINTFLAGS,
    _CS_POSIX_V6_ILP32_OFFBIG_CFLAGS,
    _CS_POSIX_V6_ILP32_OFFBIG_LDFLAGS,
    _CS_POSIX_V6_ILP32_OFFBIG_LIBS,
    _CS_POSIX_V6_ILP32_OFFBIG_LINTFLAGS,
    _CS_POSIX_V6_LP64_OFF64_CFLAGS,
    _CS_POSIX_V6_LP64_OFF64_LDFLAGS,
    _CS_POSIX_V6_LP64_OFF64_LIBS,
    _CS_POSIX_V6_LP64_OFF64_LINTFLAGS,
    _CS_POSIX_V6_LPBIG_OFFBIG_CFLAGS,
    _CS_POSIX_V6_LPBIG_OFFBIG_LDFLAGS,
    _CS_POSIX_V6_LPBIG_OFFBIG_LIBS,
    _CS_POSIX_V6_LPBIG_OFFBIG_LINTFLAGS,
    _CS_POSIX_V7_ILP32_OFF32_CFLAGS,
    _CS_POSIX_V7_ILP32_OFF32_LDFLAGS,
    _CS_POSIX_V7_ILP32_OFF32_LIBS,
    _CS_POSIX_V7_ILP32_OFF32_LINTFLAGS,
    _CS_POSIX_V7_ILP32_OFFBIG_CFLAGS,
    _CS_POSIX_V7_ILP32_OFFBIG_LDFLAGS,
    _CS_POSIX_V7_ILP32_OFFBIG_LIBS,
    _CS_POSIX_V7_ILP32_OFFBIG_LINTFLAGS,
    _CS_POSIX_V7_LP64_OFF64_CFLAGS,
    _CS_POSIX_V7_LP64_OFF64_LDFLAGS,
    _CS_POSIX_V7_LP64_OFF64_LIBS,
    _CS_POSIX_V7_LP64_OFF64_LINTFLAGS,
    _CS_POSIX_V7_LPBIG_OFFBIG_CFLAGS,
    _CS_POSIX_V7_LPBIG_OFFBIG_LDFLAGS,
    _CS_POSIX_V7_LPBIG_OFFBIG_LIBS,
    _CS_POSIX_V7_LPBIG_OFFBIG_LINTFLAGS,
    _CS_V6_ENV,
    _CS_V7_ENV
  };
extern long int pathconf (const char *__path, int __name)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern long int fpathconf (int __fd, int __name) __attribute__ ((__nothrow__ , __leaf__));
extern long int sysconf (int __name) __attribute__ ((__nothrow__ , __leaf__));
extern size_t confstr (int __name, char *__buf, size_t __len) __attribute__ ((__nothrow__ , __leaf__))
    __attribute__ ((__access__ (__write_only__, 2, 3)));
extern __pid_t getpid (void) __attribute__ ((__nothrow__ , __leaf__));
extern __pid_t getppid (void) __attribute__ ((__nothrow__ , __leaf__));
extern __pid_t getpgrp (void) __attribute__ ((__nothrow__ , __leaf__));
extern __pid_t __getpgid (__pid_t __pid) __attribute__ ((__nothrow__ , __leaf__));
extern __pid_t getpgid (__pid_t __pid) __attribute__ ((__nothrow__ , __leaf__));
extern int setpgid (__pid_t __pid, __pid_t __pgid) __attribute__ ((__nothrow__ , __leaf__));
extern int setpgrp (void) __attribute__ ((__nothrow__ , __leaf__));
extern __pid_t setsid (void) __attribute__ ((__nothrow__ , __leaf__));
extern __pid_t getsid (__pid_t __pid) __attribute__ ((__nothrow__ , __leaf__));
extern __uid_t getuid (void) __attribute__ ((__nothrow__ , __leaf__));
extern __uid_t geteuid (void) __attribute__ ((__nothrow__ , __leaf__));
extern __gid_t getgid (void) __attribute__ ((__nothrow__ , __leaf__));
extern __gid_t getegid (void) __attribute__ ((__nothrow__ , __leaf__));
extern int getgroups (int __size, __gid_t __list[]) __attribute__ ((__nothrow__ , __leaf__))
    __attribute__ ((__access__ (__write_only__, 2, 1)));
extern int setuid (__uid_t __uid) __attribute__ ((__nothrow__ , __leaf__)) ;
extern int setreuid (__uid_t __ruid, __uid_t __euid) __attribute__ ((__nothrow__ , __leaf__)) ;
extern int seteuid (__uid_t __uid) __attribute__ ((__nothrow__ , __leaf__)) ;
extern int setgid (__gid_t __gid) __attribute__ ((__nothrow__ , __leaf__)) ;
extern int setregid (__gid_t __rgid, __gid_t __egid) __attribute__ ((__nothrow__ , __leaf__)) ;
extern int setegid (__gid_t __gid) __attribute__ ((__nothrow__ , __leaf__)) ;
extern __pid_t fork (void) __attribute__ ((__nothrow__));
extern __pid_t vfork (void) __attribute__ ((__nothrow__ , __leaf__));
extern char *ttyname (int __fd) __attribute__ ((__nothrow__ , __leaf__));
extern int ttyname_r (int __fd, char *__buf, size_t __buflen)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2)))
     __attribute__ ((__access__ (__write_only__, 2, 3)));
extern int isatty (int __fd) __attribute__ ((__nothrow__ , __leaf__));
extern int ttyslot (void) __attribute__ ((__nothrow__ , __leaf__));
extern int link (const char *__from, const char *__to)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2))) ;
extern int linkat (int __fromfd, const char *__from, int __tofd,
     const char *__to, int __flags)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2, 4))) ;
extern int symlink (const char *__from, const char *__to)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2))) ;
extern ssize_t readlink (const char *__restrict __path,
    char *__restrict __buf, size_t __len)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)))
     __attribute__ ((__access__ (__write_only__, 2, 3)));
extern int symlinkat (const char *__from, int __tofd,
        const char *__to) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 3))) ;
extern ssize_t readlinkat (int __fd, const char *__restrict __path,
      char *__restrict __buf, size_t __len)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2, 3)))
     __attribute__ ((__access__ (__write_only__, 3, 4)));
extern int unlink (const char *__name) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern int unlinkat (int __fd, const char *__name, int __flag)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2)));
extern int rmdir (const char *__path) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern __pid_t tcgetpgrp (int __fd) __attribute__ ((__nothrow__ , __leaf__));
extern int tcsetpgrp (int __fd, __pid_t __pgrp_id) __attribute__ ((__nothrow__ , __leaf__));
extern char *getlogin (void);
extern int getlogin_r (char *__name, size_t __name_len) __attribute__ ((__nonnull__ (1)))
    __attribute__ ((__access__ (__write_only__, 1, 2)));
extern int setlogin (const char *__name) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));

extern char *optarg;
extern int optind;
extern int opterr;
extern int optopt;
extern int getopt (int ___argc, char *const *___argv, const char *__shortopts)
       __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2, 3)));



extern int gethostname (char *__name, size_t __len) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)))
    __attribute__ ((__access__ (__write_only__, 1, 2)));
extern int sethostname (const char *__name, size_t __len)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) __attribute__ ((__access__ (__read_only__, 1, 2)));
extern int sethostid (long int __id) __attribute__ ((__nothrow__ , __leaf__)) ;
extern int getdomainname (char *__name, size_t __len)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)))
     __attribute__ ((__access__ (__write_only__, 1, 2)));
extern int setdomainname (const char *__name, size_t __len)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) __attribute__ ((__access__ (__read_only__, 1, 2)));
extern int vhangup (void) __attribute__ ((__nothrow__ , __leaf__));
extern int revoke (const char *__file) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) ;
extern int profil (unsigned short int *__sample_buffer, size_t __size,
     size_t __offset, unsigned int __scale)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern int acct (const char *__name) __attribute__ ((__nothrow__ , __leaf__));
extern char *getusershell (void) __attribute__ ((__nothrow__ , __leaf__));
extern void endusershell (void) __attribute__ ((__nothrow__ , __leaf__));
extern void setusershell (void) __attribute__ ((__nothrow__ , __leaf__));
extern int daemon (int __nochdir, int __noclose) __attribute__ ((__nothrow__ , __leaf__)) ;
extern int chroot (const char *__path) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) ;
extern char *getpass (const char *__prompt) __attribute__ ((__nonnull__ (1)));
extern int fsync (int __fd);
extern long int gethostid (void);
extern void sync (void) __attribute__ ((__nothrow__ , __leaf__));
extern int getpagesize (void) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));
extern int getdtablesize (void) __attribute__ ((__nothrow__ , __leaf__));
extern int truncate (const char *__file, __off_t __length)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) ;
extern int ftruncate (int __fd, __off_t __length) __attribute__ ((__nothrow__ , __leaf__)) ;
extern int brk (void *__addr) __attribute__ ((__nothrow__ , __leaf__)) ;
extern void *sbrk (intptr_t __delta) __attribute__ ((__nothrow__ , __leaf__));
extern long int syscall (long int __sysno, ...) __attribute__ ((__nothrow__ , __leaf__));
extern int lockf (int __fd, int __cmd, __off_t __len) ;
extern int fdatasync (int __fildes);
extern char *crypt (const char *__key, const char *__salt)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
int getentropy (void *__buffer, size_t __length)
    __attribute__ ((__access__ (__write_only__, 1, 2)));

typedef uint32 tpl_stack_word;
typedef uint16 tpl_stack_size;
struct TPL_STACK {
    tpl_stack_word *stack_zone;
    tpl_stack_size stack_size;
};
typedef struct TPL_STACK *tpl_stack;
extern struct TPL_STACK idle_task_stack;
struct TPL_CONTEXT {
    jmp_buf initial;
    jmp_buf current;
};
typedef struct TPL_CONTEXT *tpl_context;
extern struct TPL_CONTEXT idle_task_context;
extern void tpl_sleep(void);
typedef tpl_proc_id tpl_task_id ;
typedef tpl_proc_id tpl_isr_id ;
typedef uint8 tpl_bool;
typedef uint8 tpl_status;
typedef uint8 tpl_proc_state;
struct ALARM_BASE_TYPE {
    tpl_tick maxallowedvalue;
    tpl_tick ticksperbase;
    tpl_tick mincycle;
};
typedef struct ALARM_BASE_TYPE tpl_alarm_base;
typedef sint8 tpl_application_mode;
typedef void (* tpl_callback_func)(void);
typedef tpl_status StatusType;
typedef uint8 Std_ReturnType;
typedef tpl_proc_state TaskStateType;
typedef tpl_proc_state * TaskStateRefType;
typedef tpl_task_id TaskType;
typedef tpl_task_id * TaskRefType;
typedef tpl_tick TickType;
typedef tpl_tick * TickRefType;
extern tpl_bool tpl_get_interrupt_lock_status(void);
typedef tpl_application_mode AppModeType;
extern const tpl_application_mode OSDEFAULTAPPMODE;
extern void StartOS(
  const AppModeType mode);
AppModeType GetActiveApplicationMode(void);
void ShutdownOS(
  const StatusType error);
void EnableAllInterrupts(void);
void DisableAllInterrupts(void);
void ResumeAllInterrupts(void);
void SuspendAllInterrupts(void);
void ResumeOSInterrupts(void);
void SuspendOSInterrupts(void);
StatusType ActivateTask(
  const TaskType task_id);
StatusType TerminateTask(void);
StatusType ChainTask(
  const TaskType task_id);
StatusType Schedule(void);
StatusType GetTaskID(
  TaskRefType task_id);
StatusType GetTaskState(
  const TaskType task_id,
  TaskStateRefType state);
typedef tpl_resource_id ResourceType;
extern const ResourceType RES_SCHEDULER;
StatusType GetResource(
  const ResourceType res_id);
StatusType ReleaseResource(
  const ResourceType res_id);
typedef tpl_alarm_base AlarmBaseType;
typedef tpl_alarm_base * AlarmBaseRefType;
typedef tpl_alarm_id AlarmType;
extern const tpl_tick OSMAXALLOWEDVALUE;
extern const tpl_tick OSTICKSPERBASE;
extern const tpl_tick OSMINCYCLE;
StatusType GetAlarmBase(
  const AlarmType alarm_id,
  AlarmBaseRefType info);
StatusType GetAlarm(
  const AlarmType alarm_id,
  TickRefType tick);
StatusType SetRelAlarm(
  const AlarmType alarm_id,
  const TickType increment,
  const TickType cycle);
StatusType SetAbsAlarm(
  const AlarmType alarm_id,
  const TickType start,
  const TickType cycle);
StatusType CancelAlarm(
  const AlarmType alarm_id);
extern const AppModeType std;
extern const TaskType t1;
extern const AlarmType Alarm1;
TestRef AlarmsTest_seq1_t1_instance(void);
int main(void)
{
 StartOS(OSDEFAULTAPPMODE);
 return 0;
}
void ShutdownHook(StatusType error)
{
 TestRunner_end();
}
extern const TaskType t1; void t1_function(void)
{
 TestRunner_start();
 TestRunner_runTest(AlarmsTest_seq1_t1_instance());
 ShutdownOS(0);
}
extern const char * const
  proc_name_table[1 + 0 + 1];
extern const tpl_tick OSTICKSPERBASE_Counter1;
extern const tpl_tick OSMAXALLOWEDVALUE_Counter1;
extern const tpl_tick OSMINCYCLE_Counter1;
extern const tpl_tick OSTICKSPERBASE;
extern const tpl_tick OSMAXALLOWEDVALUE;
extern const tpl_tick OSMINCYCLE;
extern const AlarmType Alarm1;
extern const AlarmType INVALID_ALARM;
static void test_t1_instance(void)
{
 StatusType result_inst_2, result_inst_4, result_inst_6, result_inst_7, result_inst_8, result_inst_9, result_inst_10, result_inst_11, result_inst_12, result_inst_13, result_inst_14, result_inst_15, result_inst_16, result_inst_17;
 AlarmBaseType result_inst_1, result_inst_5;
 TickType result_inst_3;
 { extern unsigned char test_number; if ((1) != (++test_number)){ assertImplementationInt((1),(test_number),52,"task1_instance.c"); };
 result_inst_2 = GetAlarmBase(INVALID_ALARM, &result_inst_1);
 if ((1) == (test_number)){ if (((3)) == ((result_inst_2))) {} else {assertImplementationInt(((3)),((result_inst_2)),54,"task1_instance.c");return;} }else{ assertImplementationInt((1),(test_number),54,"task1_instance.c"); } };
 { extern unsigned char test_number; if ((2) != (++test_number)){ assertImplementationInt((2),(test_number),56,"task1_instance.c"); };
 result_inst_4 = GetAlarm(INVALID_ALARM, &result_inst_3);
 if ((2) == (test_number)){ if (((3)) == ((result_inst_4))) {} else {assertImplementationInt(((3)),((result_inst_4)),58,"task1_instance.c");return;} }else{ assertImplementationInt((2),(test_number),58,"task1_instance.c"); } };
 { extern unsigned char test_number; if ((3) != (++test_number)){ assertImplementationInt((3),(test_number),60,"task1_instance.c"); };
 result_inst_6 = GetAlarmBase(Alarm1, &result_inst_5);
 if ((3) == (test_number)){ if (((OSMAXALLOWEDVALUE_Counter1)) == (((int)(result_inst_5.maxallowedvalue)))) {} else {assertImplementationInt(((OSMAXALLOWEDVALUE_Counter1)),(((int)(result_inst_5.maxallowedvalue))),62,"task1_instance.c");return;} }else{ assertImplementationInt((3),(test_number),62,"task1_instance.c"); };
 if ((3) == (test_number)){ if (((OSTICKSPERBASE_Counter1)) == (((int)(result_inst_5.ticksperbase)))) {} else {assertImplementationInt(((OSTICKSPERBASE_Counter1)),(((int)(result_inst_5.ticksperbase))),63,"task1_instance.c");return;} }else{ assertImplementationInt((3),(test_number),63,"task1_instance.c"); };
 if ((3) == (test_number)){ if (((OSMINCYCLE_Counter1)) == (((int)(result_inst_5.mincycle)))) {} else {assertImplementationInt(((OSMINCYCLE_Counter1)),(((int)(result_inst_5.mincycle))),64,"task1_instance.c");return;} }else{ assertImplementationInt((3),(test_number),64,"task1_instance.c"); };
 if ((3) == (test_number)){ if (((0)) == ((result_inst_6))) {} else {assertImplementationInt(((0)),((result_inst_6)),65,"task1_instance.c");return;} }else{ assertImplementationInt((3),(test_number),65,"task1_instance.c"); } };
 { extern unsigned char test_number; if ((4) != (++test_number)){ assertImplementationInt((4),(test_number),67,"task1_instance.c"); };
 result_inst_7 = SetRelAlarm(INVALID_ALARM, 0, 0);
 if ((4) == (test_number)){ if (((3)) == ((result_inst_7))) {} else {assertImplementationInt(((3)),((result_inst_7)),69,"task1_instance.c");return;} }else{ assertImplementationInt((4),(test_number),69,"task1_instance.c"); } };
 { extern unsigned char test_number; if ((5) != (++test_number)){ assertImplementationInt((5),(test_number),71,"task1_instance.c"); };
 result_inst_8 = SetRelAlarm(Alarm1, -1, 0);
 if ((5) == (test_number)){ if (((8)) == ((result_inst_8))) {} else {assertImplementationInt(((8)),((result_inst_8)),73,"task1_instance.c");return;} }else{ assertImplementationInt((5),(test_number),73,"task1_instance.c"); } };
 { extern unsigned char test_number; if ((6) != (++test_number)){ assertImplementationInt((6),(test_number),75,"task1_instance.c"); };
 result_inst_9 = SetRelAlarm(Alarm1, result_inst_5.maxallowedvalue + 1, 0);
 if ((6) == (test_number)){ if (((8)) == ((result_inst_9))) {} else {assertImplementationInt(((8)),((result_inst_9)),77,"task1_instance.c");return;} }else{ assertImplementationInt((6),(test_number),77,"task1_instance.c"); } };
 { extern unsigned char test_number; if ((7) != (++test_number)){ assertImplementationInt((7),(test_number),79,"task1_instance.c"); };
 result_inst_10 = SetRelAlarm(Alarm1, 0, result_inst_5.mincycle - 1);
 if ((7) == (test_number)){ if (((8)) == ((result_inst_10))) {} else {assertImplementationInt(((8)),((result_inst_10)),81,"task1_instance.c");return;} }else{ assertImplementationInt((7),(test_number),81,"task1_instance.c"); } };
 { extern unsigned char test_number; if ((8) != (++test_number)){ assertImplementationInt((8),(test_number),83,"task1_instance.c"); };
 result_inst_11 = SetRelAlarm(Alarm1, 0, result_inst_5.maxallowedvalue + 1);
 if ((8) == (test_number)){ if (((8)) == ((result_inst_11))) {} else {assertImplementationInt(((8)),((result_inst_11)),85,"task1_instance.c");return;} }else{ assertImplementationInt((8),(test_number),85,"task1_instance.c"); } };
 { extern unsigned char test_number; if ((9) != (++test_number)){ assertImplementationInt((9),(test_number),87,"task1_instance.c"); };
 result_inst_12 = SetAbsAlarm(INVALID_ALARM, 0, 0);
 if ((9) == (test_number)){ if (((3)) == ((result_inst_12))) {} else {assertImplementationInt(((3)),((result_inst_12)),89,"task1_instance.c");return;} }else{ assertImplementationInt((9),(test_number),89,"task1_instance.c"); } };
 { extern unsigned char test_number; if ((10) != (++test_number)){ assertImplementationInt((10),(test_number),91,"task1_instance.c"); };
 result_inst_13 = SetAbsAlarm(Alarm1, -1, 0);
 if ((10) == (test_number)){ if (((8)) == ((result_inst_13))) {} else {assertImplementationInt(((8)),((result_inst_13)),93,"task1_instance.c");return;} }else{ assertImplementationInt((10),(test_number),93,"task1_instance.c"); } };
 { extern unsigned char test_number; if ((11) != (++test_number)){ assertImplementationInt((11),(test_number),95,"task1_instance.c"); };
 result_inst_14 = SetAbsAlarm(Alarm1, result_inst_5.maxallowedvalue + 1, 0);
 if ((11) == (test_number)){ if (((8)) == ((result_inst_14))) {} else {assertImplementationInt(((8)),((result_inst_14)),97,"task1_instance.c");return;} }else{ assertImplementationInt((11),(test_number),97,"task1_instance.c"); } };
 { extern unsigned char test_number; if ((12) != (++test_number)){ assertImplementationInt((12),(test_number),99,"task1_instance.c"); };
 result_inst_15 = SetAbsAlarm(Alarm1, 0, result_inst_5.mincycle - 1);
 if ((12) == (test_number)){ if (((8)) == ((result_inst_15))) {} else {assertImplementationInt(((8)),((result_inst_15)),101,"task1_instance.c");return;} }else{ assertImplementationInt((12),(test_number),101,"task1_instance.c"); } };
 { extern unsigned char test_number; if ((13) != (++test_number)){ assertImplementationInt((13),(test_number),103,"task1_instance.c"); };
 result_inst_16 = SetAbsAlarm(Alarm1, 0, result_inst_5.maxallowedvalue + 1);
 if ((13) == (test_number)){ if (((8)) == ((result_inst_16))) {} else {assertImplementationInt(((8)),((result_inst_16)),105,"task1_instance.c");return;} }else{ assertImplementationInt((13),(test_number),105,"task1_instance.c"); } };
 { extern unsigned char test_number; if ((14) != (++test_number)){ assertImplementationInt((14),(test_number),107,"task1_instance.c"); };
 result_inst_17 = CancelAlarm(INVALID_ALARM);
 if ((14) == (test_number)){ if (((3)) == ((result_inst_17))) {} else {assertImplementationInt(((3)),((result_inst_17)),109,"task1_instance.c");return;} }else{ assertImplementationInt((14),(test_number),109,"task1_instance.c"); } };
}
TestRef AlarmsTest_seq1_t1_instance(void)
{
 static const TestFixture fixtures[] = {
  { "test_t1_instance", test_t1_instance, }
 };
 static const TestCaller AlarmsTest = { (TestImplement*)&TestCallerImplement, "AlarmsTest_sequence1", ((void *)0), ((void *)0), sizeof(fixtures)/sizeof(fixtures[0]), (TestFixture*)fixtures, };
 return (TestRef)&AlarmsTest;
}
typedef uint8 tpl_os_state;
typedef uint8 tpl_proc_type;
typedef void (* tpl_proc_function)(void);
typedef struct
{
  const tpl_priority
  ceiling_priority;
  tpl_priority
  owner_prev_priority;
  tpl_bool
  taken;
} tpl_internal_resource;
struct TPL_PROC_STATIC
{
  tpl_context
  context;
  tpl_stack
  stack;
  const tpl_proc_function
  entry;
  tpl_internal_resource * const
  internal_resource;
  const tpl_task_id
  id;
  const tpl_priority
  base_priority;
  const tpl_activate_counter
  max_activate_count;
  const tpl_proc_type
  type;
};
typedef struct TPL_PROC_STATIC tpl_proc_static;
struct TPL_PROC
{
  struct TPL_RESOURCE * resources;
  tpl_activate_counter
  activate_count;
  tpl_priority
  priority;
  tpl_proc_state
  state;
};
typedef struct TPL_PROC tpl_proc;
typedef struct
{
  const tpl_proc_static * s_running;
  const tpl_proc_static * s_elected;
  tpl_proc * running;
  tpl_proc * elected;
  sint32 running_id;
  sint32 elected_id;
  uint8 need_switch;
  tpl_bool need_schedule;
} tpl_kern_state;
typedef struct
{
  tpl_priority key;
  tpl_proc_id id;
} tpl_heap_entry;
extern tpl_kern_state tpl_kern;
extern tpl_internal_resource INTERNAL_RES_SCHEDULER;
extern tpl_heap_entry tpl_ready_list[];
extern tpl_rank_count tpl_tail_for_prio[];
extern const tpl_proc_static * const
    tpl_stat_proc_table[1 + 0 + 1];
extern tpl_proc * const
    tpl_dyn_proc_table[1 + 0 + 1];
void tpl_begin_alarm_callback(void);
void tpl_end_alarm_callback(void);
tpl_bool tpl_alarm_callback_running(void);
tpl_os_state tpl_current_os_state(void);
void tpl_schedule_from_running(void);
void tpl_start_scheduling(void);
void tpl_start(void);
const tpl_context *
tpl_run_elected(const tpl_bool save);
void tpl_block(void);
void tpl_release(const tpl_task_id task_id);
tpl_heap_entry tpl_front_proc(void);
void tpl_terminate(void);
void tpl_init_proc(const tpl_proc_id proc_id);
void
tpl_put_preempted_proc(const tpl_proc_id proc_id);
void tpl_put_new_proc(const tpl_proc_id proc_id);
void
tpl_init_os(const tpl_application_mode app_mode);
void
tpl_get_internal_resource(const tpl_proc_id task_id);
void
tpl_release_internal_resource(const tpl_proc_id task_id);
void tpl_call_terminate_task_service(void);
void tpl_call_terminate_isr2_service(void);
tpl_status
tpl_activate_task(const tpl_task_id task_id);
tpl_status
tpl_set_event(const tpl_task_id task_id,
              const tpl_event_mask incoming_event);
typedef tpl_bool (* tpl_isr_helper)(void);
typedef void (* tpl_it_handler)(const void * );
typedef void (* tpl_enable_disable_func)(void);
struct TPL_IT_VECTOR_ENTRY
{
  const tpl_it_handler
  func;
  void *
  args;
};
typedef struct TPL_IT_VECTOR_ENTRY tpl_it_vector_entry;
struct TPL_ISR_STATIC
{
  const tpl_isr_helper
  helper;
  struct TPL_ISR_STATIC * next;
  const tpl_isr_id
  isr_id;
};
typedef struct TPL_ISR_STATIC tpl_isr_static;
tpl_bool tpl_get_interrupt_lock_status(void);
void tpl_reset_interrupt_lock_status(void);
tpl_status tpl_terminate_isr2_service(void);
void tpl_central_interrupt_handler(const uint16 id);
void
tpl_fast_central_interrupt_handler(const uint16 id);
void
tpl_central_interrupt_handler_2(const void * id);
void tpl_null_it(const void * );
void tpl_enable_all_interrupts_service(void);
void tpl_disable_all_interrupts_service(void);
void tpl_resume_all_interrupts_service(void);
void tpl_suspend_all_interrupts_service(void);
void tpl_resume_os_interrupts_service(void);
void tpl_suspend_os_interrupts_service(void);
struct TPL_COUNTER;
struct TPL_TIME_OBJ;
typedef uint8 tpl_time_obj_state;
typedef void (* tpl_expire_func)(
    struct TPL_TIME_OBJ *
);
struct TPL_TIME_OBJ_STATIC {
  struct TPL_COUNTER *
    counter;
  const tpl_expire_func
    expire;
};
typedef struct TPL_TIME_OBJ_STATIC tpl_time_obj_static;
struct TPL_TIME_OBJ {
    tpl_time_obj_static * stat_part;
    struct TPL_TIME_OBJ * next_to;
    struct TPL_TIME_OBJ * prev_to;
    tpl_tick cycle;
    tpl_tick date;
    tpl_time_obj_state state;
};
typedef struct TPL_TIME_OBJ tpl_time_obj;
struct TPL_COUNTER {
  const tpl_tick
    ticks_per_base;
  const tpl_tick
    max_allowed_value;
  const tpl_tick
    min_cycle;
  tpl_tick
    current_tick;
  tpl_tick
    current_date;
  tpl_time_obj *
    first_to;
  tpl_time_obj *
    next_to;
};
typedef struct TPL_COUNTER tpl_counter;
extern tpl_counter SystemCounter_counter_desc;
void tpl_enable_counters(void);
void tpl_insert_time_obj(
    tpl_time_obj * time_obj);
void tpl_remove_time_obj(
    tpl_time_obj * time_obj);
void tpl_counter_tick(
    tpl_counter * counter);
struct TPL_TASK_EVENTS
{
  tpl_event_mask evt_set;
  tpl_event_mask evt_wait;
};
typedef struct TPL_TASK_EVENTS tpl_task_events;
tpl_status
tpl_activate_task_service(const tpl_task_id task_id);
tpl_status tpl_terminate_task_service(void);
tpl_status
tpl_chain_task_service(const tpl_task_id task_id);
tpl_status tpl_schedule_service(void);
tpl_status
tpl_get_task_id_service(tpl_task_id * const
                            task_id);
tpl_status
tpl_get_task_state_service(const tpl_task_id task_id,
                           tpl_proc_state * const
                               state);
struct TPL_ACTION;
typedef void (* tpl_action_func)(
  const struct TPL_ACTION *
);
struct TPL_ACTION {
  tpl_action_func action;
};
typedef struct TPL_ACTION tpl_action;
struct TPL_CALLBACK_ACTION {
  tpl_action b_desc;
  tpl_callback_func callback;
};
typedef struct TPL_CALLBACK_ACTION
tpl_callback_action;
struct TPL_TASK_ACTIVATION_ACTION {
  tpl_action b_desc;
  tpl_task_id task_id;
};
typedef struct TPL_TASK_ACTIVATION_ACTION
tpl_task_activation_action ;
struct TPL_SETEVENT_ACTION {
  tpl_action b_desc;
  tpl_task_id task_id;
  tpl_event_mask mask;
};
typedef struct TPL_SETEVENT_ACTION
tpl_setevent_action;
void tpl_action_callback(
  const tpl_action * action
);
void tpl_action_activate_task(
  const tpl_action * action
);
void tpl_action_setevent(
  const tpl_action * action
);
extern tpl_time_obj * const tpl_alarm_table[1];
struct TPL_ALARM_STATIC {
  tpl_time_obj_static b_desc;
  tpl_action * action;
};
typedef struct TPL_ALARM_STATIC tpl_alarm_static;
void tpl_raise_alarm(
    tpl_time_obj * time_obj);
tpl_status tpl_get_alarm_base_service(
    const tpl_alarm_id alarm_id,
    tpl_alarm_base * info);
tpl_status tpl_get_alarm_service(
    const tpl_alarm_id alarm_id,
    tpl_tick * tick);
tpl_status tpl_set_rel_alarm_service(
    const tpl_alarm_id alarm_id,
    const tpl_tick increment,
    const tpl_tick cycle);
tpl_status tpl_set_abs_alarm_service(
    const tpl_alarm_id alarm_id,
    const tpl_tick start,
    const tpl_tick cycle);
tpl_status tpl_cancel_alarm_service(
    const tpl_alarm_id alarm_id);
struct TPL_RESOURCE
{
  const tpl_priority
  ceiling_priority;
  tpl_priority
  owner_prev_priority;
  tpl_proc_id
  owner;
  struct TPL_RESOURCE * next_res;
};
typedef struct TPL_RESOURCE tpl_resource;
extern tpl_resource * const tpl_resource_table[1];
void
tpl_release_all_resources(const tpl_proc_id proc_id);
tpl_status
tpl_get_resource_service(const tpl_resource_id res_id);
tpl_status
tpl_release_resource_service(const tpl_resource_id res);
tpl_status tpl_set_event_service(
    const tpl_task_id task_id,
    const tpl_event_mask event);
tpl_status tpl_clear_event_service(
    const tpl_event_mask event);
tpl_status tpl_get_event_service(
    const tpl_task_id task_id,
    tpl_event_mask * const event);
tpl_status tpl_wait_event_service(
    const tpl_event_mask event);
typedef tpl_event_mask EventMaskType;
typedef tpl_event_mask * EventMaskRefType;
const tpl_application_mode std = 0;
const tpl_application_mode OSDEFAULTAPPMODE = 0;
const tpl_appmode_mask tpl_task_app_mode[1] = {
  1
};
const tpl_appmode_mask tpl_alarm_app_mode[1] = {
  0
};
const TaskType t1 = 0;
const AlarmType Alarm1 = 0;
tpl_resource res_sched_rez_desc = {
  2,
  0,
  -1,
  ((void *)0)
};
tpl_resource * const
tpl_resource_table[1] = {
  &res_sched_rez_desc
};
const tpl_tick OSTICKSPERBASE_Counter1 = 10;
const tpl_tick OSMAXALLOWEDVALUE_Counter1 = 16;
const tpl_tick OSMINCYCLE_Counter1 = 2;
tpl_counter Counter1_counter_desc = {
                              10,
                              16,
                              2,
                              0,
                              0,
                                ((void *)0),
                                ((void *)0)
};
const tpl_tick OSTICKSPERBASE = 1;
const tpl_tick OSMAXALLOWEDVALUE = 4294967295;
const tpl_tick OSMINCYCLE = 1;
tpl_counter SystemCounter_counter_desc = {
                              1,
                              4294967295,
                              1,
                              0,
                              0,
                                ((void *)0),
                                ((void *)0)
};
extern void tpl_switch_context(
  const tpl_context * const old_context,
  const tpl_context * const new_context
);
extern void tpl_switch_context_from_it(
  const tpl_context * const old_context,
  const tpl_context * const new_context
);
extern void tpl_init_context(
  const tpl_proc_id proc_id);
extern void tpl_disable_interrupts(void);
extern void tpl_enable_interrupts(void);
extern void tpl_disable_os_interrupts(void);
extern void tpl_enable_os_interrupts(void);
extern void tpl_get_task_lock(void);
extern void tpl_release_task_lock(void);
extern void tpl_init_machine(void);
extern void tpl_sleep(void);
extern void tpl_shutdown(void);
tpl_bool tpl_call_counter_tick(void)
{
  tpl_counter_tick(&Counter1_counter_desc);
  tpl_counter_tick(&SystemCounter_counter_desc);
  if (tpl_kern.need_schedule)
  {
    tpl_schedule_from_running();
    if (tpl_kern.need_switch != 0x0) { tpl_kern.need_switch = 0x0; tpl_switch_context(tpl_run_elected(((tpl_bool)1)), &(tpl_kern.s_elected->context)); }
  }
  return ((tpl_bool)1);
}
void idle_function(void);
tpl_stack_word IDLE_TASK_stack_zone[32768/sizeof(tpl_stack_word)];
struct TPL_STACK IDLE_TASK_stack = {IDLE_TASK_stack_zone, 32768};
struct TPL_CONTEXT IDLE_TASK_context;
const tpl_proc_static IDLE_TASK_task_stat_desc = {
                                  &IDLE_TASK_context,
                                  &IDLE_TASK_stack,
                                  idle_function,
                                  ((void *)0),
                                  1 + 0,
                                  0,
                                  1,
                                  0x0,
};
tpl_proc IDLE_TASK_task_desc = {
                                        ((void *)0),
                                        0,
                                        0,
                                        0x0
};
void t1_function(void);
tpl_stack_word t1_stack_zone[32768/sizeof(tpl_stack_word)];
struct TPL_STACK t1_stack = {t1_stack_zone, 32768};
struct TPL_CONTEXT t1_context;
const tpl_proc_static t1_task_stat_desc = {
                                  &t1_context,
                                  &t1_stack,
                                  t1_function,
                                  &INTERNAL_RES_SCHEDULER,
                                  0,
                                  1,
                                  1,
                                  0x0,
};
tpl_proc t1_task_desc = {
                                        ((void *)0),
                                        0,
                                        1,
                                        0x4
};
const tpl_proc_static * const
tpl_stat_proc_table[1 +0 +1] = {
  &t1_task_stat_desc,
  &IDLE_TASK_task_stat_desc
};
tpl_proc * const
tpl_dyn_proc_table[1 +0 +1] = {
  &t1_task_desc,
  &IDLE_TASK_task_desc
};
const tpl_task_activation_action Alarm1_action = {
  {
                            tpl_action_activate_task
  },
                            0
};
const tpl_alarm_static Alarm1_static = {
  {
                                        &Counter1_counter_desc,
                                        tpl_raise_alarm
  },
                              (tpl_action *)&Alarm1_action
};
tpl_time_obj Alarm1_alarm_desc = {
                                        (tpl_time_obj_static *)&Alarm1_static,
                                        ((void *)0),
                                        ((void *)0),
                                        0,
                                        0,
                                        0
};
tpl_time_obj * const
  tpl_alarm_table[1] = {
  &Alarm1_alarm_desc
};
tpl_heap_entry tpl_ready_list[4];
tpl_rank_count tpl_tail_for_prio[4] = {
  0,
  0,
  0
};
tpl_kern_state tpl_kern =
{
  ((void *)0),
  &IDLE_TASK_task_stat_desc,
  ((void *)0),
  &IDLE_TASK_task_desc,
  -1,
  -1,
  0x0,
  ((tpl_bool)0),
};
const char * const proc_name_table[1 + 0 + 1] = {
  "t1",
  "*idle*"
};
tpl_application_mode tpl_get_active_application_mode_service(
  void);
void tpl_start_os_service(
  const tpl_application_mode mode);
void tpl_call_shutdown_os(
    const tpl_status error);
void tpl_shutdown_os_service(
    const tpl_status error);
AppModeType GetActiveApplicationMode(void)
{
  return tpl_get_active_application_mode_service();
}
void tpl_start_os(const AppModeType mode)
{
  tpl_start_os_service(mode);
}
void ShutdownOS(const StatusType error)
{
  tpl_shutdown_os_service(error);
}
void EnableAllInterrupts(void)
{
  tpl_enable_all_interrupts_service();
}
void DisableAllInterrupts(void)
{
  tpl_disable_all_interrupts_service();
}
void ResumeAllInterrupts(void)
{
  tpl_resume_all_interrupts_service();
}
void SuspendAllInterrupts(void)
{
  tpl_suspend_all_interrupts_service();
}
void ResumeOSInterrupts(void)
{
  tpl_resume_os_interrupts_service();
}
void SuspendOSInterrupts(void)
{
  tpl_suspend_os_interrupts_service();
}
void CallTerminateISR2(void)
{
  tpl_call_terminate_isr2_service();
}
StatusType ActivateTask(const TaskType task_id)
{
  return tpl_activate_task_service(task_id);
}
StatusType TerminateTask(void)
{
  return tpl_terminate_task_service();
}
StatusType ChainTask(const TaskType task_id)
{
  return tpl_chain_task_service(task_id);
}
StatusType Schedule(void)
{
  return tpl_schedule_service();
}
StatusType GetTaskID(TaskRefType task_id)
{
  return tpl_get_task_id_service(task_id);
}
StatusType GetTaskState(const TaskType task_id,TaskStateRefType state)
{
  return tpl_get_task_state_service(task_id, state);
}
void CallTerminateTask(void)
{
  tpl_call_terminate_task_service();
}
StatusType GetResource(const ResourceType res_id)
{
  return tpl_get_resource_service(res_id);
}
StatusType ReleaseResource(const ResourceType res_id)
{
  return tpl_release_resource_service(res_id);
}
StatusType GetAlarmBase(const AlarmType alarm_id,AlarmBaseRefType info)
{
  return tpl_get_alarm_base_service(alarm_id, info);
}
StatusType GetAlarm(const AlarmType alarm_id,TickRefType tick)
{
  return tpl_get_alarm_service(alarm_id, tick);
}
StatusType SetRelAlarm(const AlarmType alarm_id,const TickType increment,const TickType cycle)
{
  return tpl_set_rel_alarm_service(alarm_id, increment, cycle);
}
StatusType SetAbsAlarm(const AlarmType alarm_id,const TickType start,const TickType cycle)
{
  return tpl_set_abs_alarm_service(alarm_id, start, cycle);
}
StatusType CancelAlarm(const AlarmType alarm_id)
{
  return tpl_cancel_alarm_service(alarm_id);
}
extern void ShutdownHook(StatusType error);
typedef uint8 tpl_trace_resource_state;
const tpl_proc_id INVALID_PROC = -1;
const tpl_proc_id INVALID_TASK = -1;
extern const tpl_appmode_mask tpl_task_app_mode[1];
extern const tpl_appmode_mask tpl_alarm_app_mode[1];
tpl_internal_resource
INTERNAL_RES_SCHEDULER = {
    2,
    0, ((tpl_bool)0)};
static tpl_bool alarm_callback_running = ((tpl_bool)0);
void tpl_begin_alarm_callback(void)
{
  alarm_callback_running = ((tpl_bool)1);
}
void tpl_end_alarm_callback(void)
{
  alarm_callback_running = ((tpl_bool)0);
}
tpl_bool tpl_alarm_callback_running(void)
{
  return alarm_callback_running;
}
int
tpl_compare_entries(const tpl_heap_entry * const first_entry,
                    const tpl_heap_entry * const
                        second_entry )
{
  uint32
  first_key = first_entry->key & (6 | 1);
  uint32
  second_key = second_entry->key & (6 | 1);
  uint32 first_tmp;
  uint32 second_tmp;
  first_tmp = ((first_key & 1) -
               tpl_tail_for_prio[first_key >> 1]);
  first_tmp = first_tmp & 1;
  first_key = (first_key & 6);
  first_key = first_key | first_tmp;
  second_tmp = ((second_key & 1) -
                tpl_tail_for_prio[second_key >> 1]);
  second_tmp = second_tmp & 1;
  second_key = (second_key & 6);
  second_key = second_key | second_tmp;
  return (first_key < second_key);
}
void
tpl_bubble_up(tpl_heap_entry * const heap,
              uint32
                  index )
{
  uint32 father = index >> 1;
  while ((index > 1) &&
         (tpl_compare_entries(heap + father,
                              heap + index )))
  {
    tpl_heap_entry tmp = heap[index];
    heap[index] = heap[father];
    heap[father] = tmp;
    index = father;
    father >>= 1;
  }
}
void
tpl_bubble_down(tpl_heap_entry * const heap,
                uint32
                    index )
{
  const uint32 size = heap[0].key;
  uint32 child;
  while ((child = index << 1) <= size)
  {
    const uint32 right = child + 1;
    if ((right <= size) &&
        tpl_compare_entries(heap + child,
                            heap + right ))
    {
      child = right;
    }
    if (tpl_compare_entries(heap + index,
                            heap + child ))
    {
      const tpl_heap_entry tmp = heap[index];
      heap[index] = heap[child];
      heap[child] = tmp;
      index = child;
    }
    else
    {
      break;
    }
  }
}
void tpl_put_new_proc(const tpl_proc_id proc_id)
{



  uint32 index = (uint32)(++(tpl_ready_list[0].key));
  tpl_priority dyn_prio;
  const tpl_priority
  prio = tpl_stat_proc_table[proc_id]->base_priority;
  dyn_prio = (prio << 1) |
             (--tpl_tail_for_prio[prio] & 1);

  tpl_ready_list[index].key = dyn_prio;
  tpl_ready_list[index].id = proc_id;
  tpl_bubble_up(tpl_ready_list, index );

}
void
tpl_put_preempted_proc(const tpl_proc_id proc_id)
{



  uint32 index = (uint32)(++(tpl_ready_list[0].key));
  const tpl_priority
  dyn_prio = tpl_dyn_proc_table[proc_id]->priority;
  ;
  tpl_ready_list[index].key = dyn_prio;
  tpl_ready_list[index].id = proc_id;
  tpl_bubble_up(tpl_ready_list, index );
  ;
}
tpl_heap_entry tpl_front_proc(void)
{

  return (tpl_ready_list[1]);
}
tpl_heap_entry tpl_remove_front_proc(void)
{


  const uint32 size = tpl_ready_list[0].key--;
  uint32 index = 1;
  tpl_heap_entry proc = tpl_ready_list[1];
  tpl_ready_list[index] = tpl_ready_list[size];
  tpl_bubble_down(tpl_ready_list,
                  index );
  return proc;
}
tpl_os_state tpl_current_os_state(void)
{
  tpl_os_state state = 5;

  if (tpl_alarm_callback_running())
  {
    state = 4;
  }
  else if (tpl_kern.running_id == -1)
  {
    state = 0;
  }
  else if (tpl_kern.running_id >= (1 + 0))
  {
    state = 2;
  }
  else if (tpl_kern.running_id < 1)
  {
    state = 1;
  }
  else if (tpl_kern.running_id < (1 + 0))
  {
    state = 3;
  }
  return state;
}
void
tpl_get_internal_resource(const tpl_proc_id task_id)
{


  tpl_internal_resource * const
  rez = tpl_stat_proc_table[task_id]->internal_resource;
  if ((((void *)0) != rez) && (((tpl_bool)0) == rez->taken))
  {
    rez->taken = ((tpl_bool)1);
    rez->owner_prev_priority = tpl_dyn_proc_table[task_id]->priority;
    tpl_dyn_proc_table[task_id]->priority =
        (((rez->ceiling_priority) << 1) | (--tpl_tail_for_prio[rez->ceiling_priority] & 1));
  }
}
void
tpl_release_internal_resource(const tpl_proc_id task_id)
{
  tpl_internal_resource * const
  rez = tpl_stat_proc_table[task_id]->internal_resource;
  if ((((void *)0) != rez) && (((tpl_bool)1) == rez->taken))
  {
    rez->taken = ((tpl_bool)0);
    tpl_dyn_proc_table[task_id]->priority = rez->owner_prev_priority;
  }
}
void tpl_preempt(void)
{

  if (tpl_kern.running_id != tpl_kern.elected_id)
  {
    ;
    tpl_kern.elected->state = (tpl_proc_state)0x1;

    tpl_put_preempted_proc((tpl_proc_id)tpl_kern.elected_id);
  }
}
const tpl_context *
tpl_run_elected(const tpl_bool save)
{


  const tpl_context * const
  old_context = save ? &(tpl_kern.s_running->context) : ((void *)0);
  ;
  if ((save) && (tpl_kern.running->state != 0x3))
  {

    ;
    tpl_kern.running->state = (tpl_proc_state)0x1;

    tpl_put_preempted_proc((tpl_proc_id)tpl_kern.running_id);
  }
  tpl_kern.running = tpl_kern.elected;
  tpl_kern.s_running = tpl_kern.s_elected;
  tpl_kern.running_id = tpl_kern.elected_id;
  ;
  ;
  tpl_kern.running->state = (tpl_proc_state)0x2;

  tpl_get_internal_resource((tpl_proc_id)tpl_kern.running_id);

  ;
  return old_context;
}
void tpl_start(void)
{

  const tpl_heap_entry
  proc = tpl_remove_front_proc();
  ;
  tpl_kern.elected_id = (uint32)proc.id;
  tpl_kern.elected = tpl_dyn_proc_table[proc.id];
  tpl_kern.s_elected = tpl_stat_proc_table[proc.id];
  if (tpl_kern.elected->state == 0x5)
  {
    ;
    tpl_init_proc(proc.id);
    tpl_dyn_proc_table[proc.id]->priority = proc.key;
  }
  tpl_kern.need_schedule = ((tpl_bool)0);
  ;
}
void tpl_schedule_from_running(void)
{


  uint8 need_switch = 0x0;
  ;

  if ((tpl_ready_list[1].key) >
      (tpl_dyn_proc_table[tpl_kern.elected_id]->priority))
  {
    tpl_preempt();
    need_switch = 0x1 | 0x2;
    tpl_start();
  }
  tpl_kern.need_switch = need_switch;
  ;
}
void tpl_terminate(void)
{


  ;

  tpl_release_internal_resource((tpl_proc_id)tpl_kern.running_id);
  if (tpl_kern.running->activate_count > 0)
  {
    tpl_kern.running->state = (tpl_proc_state)0x5;

  }
  else
  {
    tpl_kern.running->state = (tpl_proc_state)0x0;

  }
}
void tpl_block(void)
{


  ;

  tpl_kern.running->state = (tpl_proc_state)0x3;

  tpl_release_internal_resource((tpl_proc_id)tpl_kern.running_id);
  tpl_kern.need_switch = 0x1 | 0x2;
  tpl_start();
  if (tpl_kern.need_switch != 0x0) { tpl_kern.need_switch = 0x0; tpl_switch_context(tpl_run_elected(((tpl_bool)1)), &(tpl_kern.s_elected->context)); }
}
void tpl_start_scheduling(void)
{

  tpl_kern.need_switch = 0x1;
  tpl_start();
}
tpl_status
tpl_activate_task(const tpl_task_id task_id)
{
  tpl_status result = 4;
  tpl_proc * const
  task = tpl_dyn_proc_table[task_id];
  const tpl_proc_static * const
  s_task = tpl_stat_proc_table[task_id];
  ;
  if (task->activate_count < s_task->max_activate_count)
  {
      if (task->activate_count == 0)
      {

        task->state = (tpl_proc_state)0x5;

        tpl_kern.need_schedule = ((tpl_bool)1);
      }
      result = 0;
      tpl_put_new_proc(task_id);
      task->activate_count++;
  }
  return result;
}
void tpl_release(const tpl_task_id task_id)
{

  tpl_proc * const
  task = tpl_dyn_proc_table[task_id];
  task->state = (tpl_proc_state)0x1;

  tpl_put_new_proc(task_id);
  tpl_kern.need_schedule = ((tpl_bool)1);
}
tpl_status
tpl_set_event(const tpl_task_id task_id,
              const tpl_event_mask incoming_event)
{
  tpl_status result = 0;
  (void)task_id;
  (void)incoming_event;
  return result;
}
void tpl_init_proc(const tpl_proc_id proc_id)
{
  tpl_proc * const
  dyn = tpl_dyn_proc_table[proc_id];
  dyn->resources = ((void *)0);
  tpl_init_context(proc_id);
}
void tpl_init_os(const tpl_application_mode app_mode)
{


  uint16 i;
  const tpl_appmode_mask app_mode_mask = 1 << app_mode;
  tpl_status result = 0;
  tpl_time_obj * auto_time_obj;
  const tpl_proc_static * const
  idle_stat = tpl_stat_proc_table[1 + 0];
  tpl_proc * const
  idle = tpl_dyn_proc_table[1 + 0];
  tpl_ready_list[0].key = 0;
  tpl_kern.s_running = ((void *)0);
  tpl_kern.s_elected = idle_stat;
  tpl_kern.running = ((void *)0);
  tpl_kern.elected = idle;
  tpl_kern.running_id = -1;
  tpl_kern.elected_id = -1;
  tpl_kern.need_switch = 0x0;
  tpl_kern.need_schedule = ((tpl_bool)0);
  result = tpl_activate_task(1 + 0);
  for (i = 0; i < 1; i++)
  {
    if (tpl_task_app_mode[i] & app_mode_mask)
    {
      {
        result = tpl_activate_task(i);
      }
    }
  }
  for (i = 0; i < 1; i++)
  {
    if (tpl_alarm_app_mode[i] & app_mode_mask)
    {
      auto_time_obj =
          (tpl_time_obj * )tpl_alarm_table[i];
      {
        auto_time_obj->state = 1;
        tpl_insert_time_obj(auto_time_obj);
      }
    }
  }
}
void tpl_call_terminate_task_service(void)
{


  tpl_get_task_lock();
  if (((tpl_bool)0) != tpl_get_interrupt_lock_status())
  {
    tpl_reset_interrupt_lock_status();
  }
  if ((tpl_kern.running->resources) != ((void *)0))
  {
    tpl_release_all_resources((tpl_proc_id)tpl_kern.running_id);
  }
  ;
  tpl_release_task_lock();
  tpl_terminate_task_service();
}
void tpl_call_terminate_isr2_service(void)
{


  StatusType result = 0;
  tpl_get_task_lock();
  if (((tpl_bool)0) != tpl_get_interrupt_lock_status())
  {
    tpl_reset_interrupt_lock_status();
    result = 19;
  }
  if ((tpl_kern.running->resources) != ((void *)0))
  {
    tpl_release_all_resources((tpl_proc_id)tpl_kern.running_id);
    result = 6;
  }
  ;
  tpl_terminate_isr2_service();
  tpl_release_task_lock();
}
void
  print_counter(tpl_counter * const c);
void
  print_rez(const tpl_resource_id rez_id);
static tpl_bool tpl_counters_enabled = ((tpl_bool)0);
void tpl_enable_counters(void)
{
  tpl_counters_enabled = ((tpl_bool)1);
}
void
tpl_insert_time_obj(tpl_time_obj * time_obj)
{
  tpl_counter *
  counter = time_obj->stat_part->counter;
  tpl_time_obj *
  current_to = counter->first_to;
  tpl_time_obj *
  prev_to = ((void *)0);
  if (current_to == ((void *)0))
  {
    counter->first_to = time_obj;
    counter->next_to = time_obj;
    time_obj->next_to = time_obj->prev_to = ((void *)0);
  }
  else
  {
    while ((current_to != ((void *)0)) && (current_to->date <= time_obj->date))
    {
      prev_to = current_to;
      current_to = current_to->next_to;
    }
    time_obj->next_to = current_to;
    time_obj->prev_to = prev_to;
    if (current_to != ((void *)0))
    {
      current_to->prev_to = time_obj;
    }
    if (prev_to != ((void *)0))
    {
      prev_to->next_to = time_obj;
    }
    else
    {
      counter->first_to = time_obj;
    }
    if (counter->next_to->date < counter->current_date)
    {
      if ((time_obj->date > counter->current_date) ||
          (time_obj->date < counter->next_to->date))
      {
        counter->next_to = time_obj;
      }
    }
    else
    {
      if ((time_obj->date > counter->current_date) &&
          (time_obj->date < counter->next_to->date))
      {
        counter->next_to = time_obj;
      }
    }
  }
}
void
tpl_remove_time_obj(tpl_time_obj * time_obj)
{
  tpl_counter *
  counter = time_obj->stat_part->counter;
  if (time_obj == counter->first_to)
  {
    counter->first_to = time_obj->next_to;
  }
  if (time_obj == counter->next_to)
  {
    counter->next_to = time_obj->next_to;
  }
  if (time_obj->next_to != ((void *)0))
  {
    time_obj->next_to->prev_to = time_obj->prev_to;
  }
  if (time_obj->prev_to != ((void *)0))
  {
    time_obj->prev_to->next_to = time_obj->next_to;
  }
  if (counter->next_to == ((void *)0))
  {
    counter->next_to = counter->first_to;
  }
}
static tpl_time_obj *
    tpl_remove_timeobj_set(tpl_counter * counter)
{
  tpl_time_obj * first_to = counter->next_to;
  tpl_time_obj * real_next_to = ((void *)0);
  if (first_to != ((void *)0))
  {
    tpl_time_obj * last_to;
    tpl_time_obj * t_obj = first_to;
    tpl_time_obj * af_to;
    tpl_tick date = first_to->date;
    tpl_bool object = ((tpl_bool)0);
    do
    {
      object = ((tpl_bool)1);
      last_to = t_obj;
      t_obj = t_obj->next_to;
    } while ((t_obj != ((void *)0)) && (t_obj->date == date));
    t_obj = first_to->prev_to;
    af_to = last_to->next_to;
    if (t_obj != ((void *)0))
    {
      t_obj->next_to = af_to;
    }
    if (af_to != ((void *)0))
    {
      af_to->prev_to = t_obj;
    }
    if (counter->first_to == first_to)
    {
      counter->first_to = af_to;
    }
    if (object == ((tpl_bool)1))
    {
      real_next_to = counter->next_to;
    }
    if (af_to != ((void *)0))
    {
      counter->next_to = af_to;
    }
    else
    {
      counter->next_to = counter->first_to;
    }
    last_to->next_to = ((void *)0);
  }
  return real_next_to;
}
extern void printrl(char * msg);
void
tpl_counter_tick(tpl_counter * counter)
{
  tpl_time_obj * t_obj;
  tpl_time_obj * real_next_to_temp;
  tpl_expire_func expire;
  tpl_tick date;
  tpl_tick new_date;
  if (tpl_counters_enabled)
  {
    counter->current_tick++;
    if (counter->current_tick == counter->ticks_per_base)
    {
      date = counter->current_date;
      date++;
      if (date > counter->max_allowed_value)
      {
        date = 0;
      }
      counter->current_date = date;
      counter->current_tick = 0;
      t_obj = counter->next_to;
      if ((t_obj != ((void *)0)) && (t_obj->date == date))
      {
        real_next_to_temp = tpl_remove_timeobj_set(counter);
        if (real_next_to_temp != ((void *)0))
        {
          t_obj = real_next_to_temp;
          do
          {
            tpl_time_obj *next_to = t_obj->next_to;
            expire = t_obj->stat_part->expire;

            expire(t_obj);
            if (t_obj->cycle != 0)
            {
              new_date = t_obj->date + t_obj->cycle;
              if (new_date > counter->max_allowed_value)
              {
                new_date -= (counter->max_allowed_value + 1);
              }
              t_obj->date = new_date;
              tpl_insert_time_obj(t_obj);
            }
            else
            {
              t_obj->state = 0;

            }
            t_obj = next_to;
          } while (t_obj != ((void *)0));
        }
      }
    }
  }
}
void tpl_call_error_hook(
    const tpl_status error);
void
tpl_action_callback(const tpl_action * action)
{
  tpl_begin_alarm_callback();
  ((const tpl_callback_action * )action)->callback();
  tpl_end_alarm_callback();
}
void
tpl_action_activate_task(const tpl_action * action)
{
  StatusType result_action = 0;


  result_action = tpl_activate_task(
      ((const tpl_task_activation_action * )action)
          ->task_id);

}
static tpl_application_mode application_mode = (-1);
tpl_application_mode
tpl_get_active_application_mode_service(void)
{
  tpl_application_mode app_mode;
  tpl_status result = 0;
  tpl_get_task_lock();
  if (((tpl_bool)0) != tpl_get_interrupt_lock_status()) { result = 19; }

  app_mode = application_mode;

  tpl_release_task_lock();
  return app_mode;
}
void
tpl_start_os_service(const tpl_application_mode mode)
{

  tpl_status result = 0;
  tpl_get_task_lock();

  ;
  if ((result == (tpl_status)0) && (tpl_current_os_state() != 0)) { result = (tpl_status)7; }
  if ((result) == 0)
  {
    application_mode = mode;
    tpl_init_os(mode);
    tpl_enable_counters();


    tpl_start_scheduling();
    if (tpl_kern.need_switch != 0x0) { tpl_kern.need_switch = 0x0; tpl_switch_context(tpl_run_elected(((tpl_bool)0)), &(tpl_kern.s_elected->context)); }
  }

  tpl_release_task_lock();
}
void
tpl_call_shutdown_os(const tpl_status error )
{


  ShutdownHook(error);

  tpl_shutdown();
}
void
tpl_shutdown_os_service(const tpl_status error )
{

  tpl_get_task_lock();
  {

    tpl_call_shutdown_os(error);
  }
  tpl_release_task_lock();
}
extern void tpl_start_os(const AppModeType mode);
void StartOS(
  const AppModeType mode)
{

  if (tpl_current_os_state() == 0)
  {
      tpl_init_machine();
  }
  tpl_start_os(mode);
}

extern void __assert_fail (const char *__assertion, const char *__file,
      unsigned int __line, const char *__function)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__noreturn__)) __attribute__ ((__cold__));
extern void __assert_perror_fail (int __errnum, const char *__file,
      unsigned int __line, const char *__function)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__noreturn__)) __attribute__ ((__cold__));
extern void __assert (const char *__assertion, const char *__file, int __line)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__noreturn__)) __attribute__ ((__cold__));

volatile uint32 tpl_locking_depth = 0;
tpl_bool tpl_user_task_lock = ((tpl_bool)0);
uint32 tpl_cpt_user_task_lock_All = 0;
uint32 tpl_cpt_user_task_lock_OS = 0;
uint32 tpl_cpt_os_task_lock = 0;
tpl_bool tpl_get_interrupt_lock_status(void)
{

  tpl_bool result;
  if ((((tpl_bool)1) == tpl_user_task_lock) ||
      (tpl_cpt_user_task_lock_OS > 0) ||
      (tpl_cpt_user_task_lock_All > 0))
  {
    result = ((tpl_bool)1);
  }
  else
  {
    result = ((tpl_bool)0);
  }
  return result;
}
void tpl_reset_interrupt_lock_status(void)
{

  tpl_user_task_lock = ((tpl_bool)0);
  tpl_cpt_user_task_lock_All = 0;
  tpl_cpt_user_task_lock_OS = 0;
  tpl_locking_depth =
      tpl_cpt_os_task_lock;
}
void tpl_suspend_all_interrupts_service(void)
{

  tpl_disable_interrupts();
  tpl_locking_depth++;
  tpl_cpt_user_task_lock_All++;
}
void tpl_resume_all_interrupts_service(void)
{

  if (tpl_cpt_user_task_lock_All != 0)
  {
    tpl_locking_depth--;
    tpl_cpt_user_task_lock_All--;
    if (tpl_locking_depth == 0)
    {
      tpl_enable_interrupts();
    }
  }
}
void tpl_disable_all_interrupts_service(void)
{

  if ((0 == tpl_cpt_user_task_lock_All) &&
      (0 == tpl_cpt_user_task_lock_OS))
  {
    tpl_disable_interrupts();
    tpl_user_task_lock = ((tpl_bool)1);
  }
}
void tpl_enable_all_interrupts_service(void)
{

  if (tpl_user_task_lock != ((tpl_bool)0))
  {
    tpl_user_task_lock = ((tpl_bool)0);
    tpl_enable_interrupts();
  }
}
void tpl_suspend_os_interrupts_service(void)
{

  tpl_disable_os_interrupts();
  tpl_locking_depth++;
  tpl_cpt_user_task_lock_OS++;
}
void tpl_resume_os_interrupts_service(void)
{

  if (tpl_cpt_user_task_lock_OS != 0)
  {
    tpl_locking_depth--;
    tpl_cpt_user_task_lock_OS--;
    if (0 == tpl_locking_depth)
    {
      tpl_enable_os_interrupts();
    }
  }
}
tpl_status tpl_terminate_isr2_service(void)
{

  tpl_status result = 0;
  if (((tpl_bool)0) != tpl_get_interrupt_lock_status()) { result = 19; }
  if (result == (tpl_status)0) { result = (tpl_status)2; }
  if ((result == (tpl_status)0) && ((tpl_kern.running->resources) != ((void *)0))) { result = (tpl_status)6; }

  return result;
}
void tpl_null_it(const void * foo)
{
  (void)foo;
}
extern const tpl_proc_id INVALID_TASK;
StatusType
tpl_activate_task_service(const tpl_task_id task_id)
{


  StatusType result = 0;
  tpl_get_task_lock();
  if (((tpl_bool)0) != tpl_get_interrupt_lock_status()) { result = 19; }


  if ((result == (tpl_status)0) && tpl_alarm_callback_running()) { result = (tpl_status)2; }
  if ((result == (tpl_status)0) && (((task_id) >= (tpl_task_id)1) || ((task_id) < 0))) { result = (tpl_status)3; }

  if ((result) == 0)
  {
    ;
    result = tpl_activate_task(task_id);
    if (tpl_kern.need_schedule)
    {
      tpl_schedule_from_running();
      ;
      if (tpl_kern.need_switch != 0x0) { tpl_kern.need_switch = 0x0; tpl_switch_context(tpl_run_elected(((tpl_bool)1)), &(tpl_kern.s_elected->context)); }
    }
  }

  tpl_release_task_lock();
  return result;
}
StatusType tpl_terminate_task_service(void)
{

  StatusType result = 0;
  tpl_get_task_lock();

  if (((tpl_bool)0) != tpl_get_interrupt_lock_status()) { result = 19; }
  if ((result == (tpl_status)0) && (tpl_current_os_state() != (tpl_os_state)1)) { result = (tpl_status)2; }
  if ((result == (tpl_status)0) && ((tpl_kern.running->resources) != ((void *)0))) { result = (tpl_status)6; }

  if ((result) == 0)
  {
    tpl_kern.running->activate_count--;
    tpl_terminate();
    tpl_kern.need_switch = 0x1;
    tpl_start();
    if (tpl_kern.need_switch != 0x0) { tpl_kern.need_switch = 0x0; tpl_switch_context(tpl_run_elected(((tpl_bool)0)), &(tpl_kern.s_elected->context)); }
  }

  tpl_release_task_lock();
  return result;
}
StatusType
tpl_chain_task_service(const tpl_task_id task_id)
{

  StatusType result = 0;
  tpl_get_task_lock();
  if (((tpl_bool)0) != tpl_get_interrupt_lock_status()) { result = 19; }


  if ((result == (tpl_status)0) && (tpl_current_os_state() != (tpl_os_state)1)) { result = (tpl_status)2; }
  if ((result == (tpl_status)0) && (((task_id) >= (tpl_task_id)1) || ((task_id) < 0))) { result = (tpl_status)3; }
  if ((result == (tpl_status)0) && ((tpl_kern.running->resources) != ((void *)0))) { result = (tpl_status)6; }


  if ((result) == 0)
  {
    tpl_kern.running->activate_count--;
    ;
    result = tpl_activate_task(task_id);
    if (result == 0)
    {

      tpl_terminate();
      tpl_kern.need_switch = 0x1;
      tpl_start();
      if (tpl_kern.need_switch != 0x0) { tpl_kern.need_switch = 0x0; tpl_switch_context(tpl_run_elected(((tpl_bool)0)), &(tpl_kern.s_elected->context)); }
    }
    else
    {
      tpl_kern.running->activate_count++;
    }
  }

  tpl_release_task_lock();
  return result;
}
StatusType tpl_schedule_service(void)
{

  StatusType result = 0;
  tpl_get_task_lock();
  if (((tpl_bool)0) != tpl_get_interrupt_lock_status()) { result = 19; }

  if ((result == (tpl_status)0) && (tpl_current_os_state() != (tpl_os_state)1)) { result = (tpl_status)2; }
  if ((result == (tpl_status)0) && ((tpl_kern.running->resources) != ((void *)0))) { result = (tpl_status)6; }

  if ((result) == 0)
  {
    ;
    tpl_release_internal_resource((tpl_proc_id)tpl_kern.running_id);
    tpl_schedule_from_running();
    if (tpl_kern.running_id == tpl_kern.elected_id)
    {
      tpl_get_internal_resource((tpl_proc_id)tpl_kern.running_id);
    }
    if (tpl_kern.need_switch != 0x0) { tpl_kern.need_switch = 0x0; tpl_switch_context(tpl_run_elected(((tpl_bool)1)), &(tpl_kern.s_elected->context)); }
  }

  tpl_release_task_lock();
  return result;
}
StatusType
tpl_get_task_id_service(tpl_task_id * const
                            task_id)
{

  StatusType result = 0;
  tpl_get_task_lock();
  if (((tpl_bool)0) != tpl_get_interrupt_lock_status()) { result = 19; }


  if ((result == (tpl_status)0) && tpl_alarm_callback_running()) { result = (tpl_status)2; }
  ;
  if ((result) == 0)
  {
    if (tpl_kern.running_id < 1)
    {
      *task_id = (tpl_proc_id)tpl_kern.running_id;
    }
    else
    {
      *task_id = INVALID_TASK;
    }
  }

  tpl_release_task_lock();
  return result;
}
StatusType
tpl_get_task_state_service(const tpl_task_id task_id,
                           tpl_proc_state * const
                               state)
{

  StatusType result = 0;
  tpl_get_task_lock();
  if (((tpl_bool)0) != tpl_get_interrupt_lock_status()) { result = 19; }



  if ((result == (tpl_status)0) && tpl_alarm_callback_running()) { result = (tpl_status)2; }
  if ((result == (tpl_status)0) && (((task_id) >= (tpl_task_id)1) || ((task_id) < 0))) { result = (tpl_status)3; }

  ;
  if ((result) == 0)
  {
    *state = (tpl_dyn_proc_table[task_id]->state) & 0x3;
  }

  tpl_release_task_lock();
  return result;
}
extern const tpl_proc_id INVALID_TASK;
const tpl_resource_id RES_SCHEDULER = 1 - 1;
const tpl_resource_id INVALID_RESOURCE = (tpl_resource_id)(-1);
void
tpl_release_all_resources(const tpl_proc_id proc_id)
{
  tpl_resource *
  res = tpl_dyn_proc_table[proc_id]->resources;
  if (res != ((void *)0))
  {
    tpl_dyn_proc_table[proc_id]->resources = ((void *)0);
    do
    {
      tpl_resource * const
      next_res = res->next_res;
      res->owner = INVALID_TASK;
      res->next_res = ((void *)0);
      res = next_res;
    } while (res != ((void *)0));
  }
}
tpl_status
tpl_get_resource_service(const tpl_resource_id res_id)
{


  tpl_status result = 0;
  tpl_resource * res;
  tpl_get_task_lock();
  if (((tpl_bool)0) != tpl_get_interrupt_lock_status()) { result = 19; }


  if ((result == (tpl_status)0) && tpl_alarm_callback_running()) { result = (tpl_status)2; }
  if ((result == (tpl_status)0) && ((res_id) >= ((tpl_resource_id)1))) { result = (tpl_status)3; }

  if ((result) == 0)
  {
    res = tpl_resource_table[res_id];
    if ((result == (tpl_status)0) && (((res)->owner != INVALID_TASK) || (tpl_kern.s_running->base_priority > res->ceiling_priority))) { result = (tpl_status)1; }
    if ((result) == 0)
    {
      res->owner = (tpl_proc_id)tpl_kern.running_id;

      res->next_res = tpl_kern.running->resources;
      tpl_kern.running->resources = res;
      res->owner_prev_priority = tpl_kern.running->priority;
      ;
      if ((tpl_kern.running->priority >> 1) <
          res->ceiling_priority)
      {

        tpl_kern.running->priority =
            (((res->ceiling_priority) << 1) | (--tpl_tail_for_prio[res->ceiling_priority] & 1));
      }
    }
  }

  tpl_release_task_lock();
  return result;
}
tpl_status
tpl_release_resource_service(const tpl_resource_id res_id)
{

  tpl_status result = 0;
  tpl_resource * res;
  tpl_get_task_lock();
  if (((tpl_bool)0) != tpl_get_interrupt_lock_status()) { result = 19; }


  if ((result == (tpl_status)0) && tpl_alarm_callback_running()) { result = (tpl_status)2; }
  if ((result == (tpl_status)0) && ((res_id) >= ((tpl_resource_id)1))) { result = (tpl_status)3; }

  if ((result) == 0)
  {
    res = tpl_resource_table[res_id];
    if ((result == (tpl_status)0) && (tpl_kern.s_running->base_priority > (res)->ceiling_priority)) { result = (tpl_status)1; }
    if ((result == (tpl_status)0) && (tpl_kern.running->resources != (res))) { result = (tpl_status)5; }
    if ((result) == 0)
    {
      tpl_kern.running->priority = res->owner_prev_priority;
      ;
      tpl_kern.running->resources = res->next_res;
      res->next_res = ((void *)0);
      res->owner = INVALID_TASK;

      tpl_schedule_from_running();
      if (tpl_kern.need_switch != 0x0) { tpl_kern.need_switch = 0x0; tpl_switch_context(tpl_run_elected(((tpl_bool)1)), &(tpl_kern.s_elected->context)); }
    }
  }

  tpl_release_task_lock();
  return result;
}
const tpl_alarm_id INVALID_ALARM = (-1);
void
tpl_raise_alarm(tpl_time_obj * time_obj)
{
  tpl_alarm_static *
  stat_alarm = (tpl_alarm_static *)time_obj->stat_part;
  tpl_action * const
  action_desc = stat_alarm->action;
  (action_desc->action)(action_desc);
}
tpl_status
tpl_get_alarm_base_service(const tpl_alarm_id alarm_id,
                           tpl_alarm_base * info)
{

  tpl_status result = 0;
  tpl_time_obj * alarm;
  tpl_get_task_lock();
  if (((tpl_bool)0) != tpl_get_interrupt_lock_status()) { result = 19; }



  if ((result == (tpl_status)0) && tpl_alarm_callback_running()) { result = (tpl_status)2; }
  if ((result == (tpl_status)0) && ((alarm_id) >= (tpl_alarm_id)1)) { result = (tpl_status)3; }

  ;
  if ((result) == 0)
  {
    alarm = tpl_alarm_table[alarm_id];
    info->ticksperbase = alarm->stat_part->counter->ticks_per_base;
    info->maxallowedvalue = alarm->stat_part->counter->max_allowed_value;
    info->mincycle = alarm->stat_part->counter->min_cycle;
  }

  tpl_release_task_lock();
  return result;
}
tpl_status
tpl_get_alarm_service(const tpl_alarm_id alarm_id,
                      tpl_tick * tick)
{

  tpl_status result = 0;
  tpl_time_obj * alarm;
  tpl_get_task_lock();
  if (((tpl_bool)0) != tpl_get_interrupt_lock_status()) { result = 19; }



  if ((result == (tpl_status)0) && tpl_alarm_callback_running()) { result = (tpl_status)2; }
  if ((result == (tpl_status)0) && ((alarm_id) >= (tpl_alarm_id)1)) { result = (tpl_status)3; }

  ;
  if ((result) == 0)
  {
    alarm = tpl_alarm_table[alarm_id];
    ;
    if (alarm->state == (tpl_time_obj_state)1)
    {
      tpl_tick alarm_date = alarm->date;
      tpl_tick
      current_date = alarm->stat_part->counter->current_date;
      if (alarm_date < current_date)
      {
        alarm_date += alarm->stat_part->counter->max_allowed_value;
      }
      *tick = alarm_date - current_date;
    }
    else
    {
      result = 5;
    }
    ;
  }

  tpl_release_task_lock();
  return result;
}
tpl_status
tpl_set_rel_alarm_service(const tpl_alarm_id alarm_id,
                          const tpl_tick increment,
                          const tpl_tick cycle)
{

  tpl_status result = 0;
  tpl_time_obj * alarm;
  tpl_counter * cnt;
  tpl_tick date;
  tpl_get_task_lock();
  if (((tpl_bool)0) != tpl_get_interrupt_lock_status()) { result = 19; }




  if ((result == (tpl_status)0) && tpl_alarm_callback_running()) { result = (tpl_status)2; }
  if ((result == (tpl_status)0) && ((alarm_id) >= (tpl_alarm_id)1)) { result = (tpl_status)3; }

  if ((result == (tpl_status)0) && (((increment) > tpl_alarm_table[(alarm_id)]->stat_part->counter->max_allowed_value))) { result = (tpl_status)8; }
  if ((result == (tpl_status)0) && ((cycle) != 0) && (((cycle) > tpl_alarm_table[(alarm_id)]->stat_part->counter->max_allowed_value) || ((cycle) < tpl_alarm_table[(alarm_id)]->stat_part->counter->min_cycle))) { result = (tpl_status)8; }
  if ((result) == 0)
  {
    alarm = tpl_alarm_table[alarm_id];
    ;
    if (alarm->state == (tpl_time_obj_state)0)
    {
      cnt = alarm->stat_part->counter;
      date = cnt->current_date + increment;
      if (date > cnt->max_allowed_value)
      {
        date -= (cnt->max_allowed_value + 1);
      }
      alarm->date = date;
      alarm->cycle = cycle;
      alarm->state = 1;

      tpl_insert_time_obj(alarm);
    }
    else
    {
      result = 7;
    }
    ;
  }

  tpl_release_task_lock();
  return result;
}
tpl_status
tpl_set_abs_alarm_service(const tpl_alarm_id alarm_id,
                          const tpl_tick start,
                          const tpl_tick cycle)
{

  tpl_status result = 0;
  tpl_time_obj * alarm;
  tpl_get_task_lock();
  if (((tpl_bool)0) != tpl_get_interrupt_lock_status()) { result = 19; }




  if ((result == (tpl_status)0) && tpl_alarm_callback_running()) { result = (tpl_status)2; }
  if ((result == (tpl_status)0) && ((alarm_id) >= (tpl_alarm_id)1)) { result = (tpl_status)3; }

  if ((result == (tpl_status)0) && (((start) > tpl_alarm_table[(alarm_id)]->stat_part->counter->max_allowed_value))) { result = (tpl_status)8; }
  if ((result == (tpl_status)0) && ((cycle) != 0) && (((cycle) > tpl_alarm_table[(alarm_id)]->stat_part->counter->max_allowed_value) || ((cycle) < tpl_alarm_table[(alarm_id)]->stat_part->counter->min_cycle))) { result = (tpl_status)8; }
  if ((result) == 0)
  {
    alarm = tpl_alarm_table[alarm_id];
    ;
    if (alarm->state == (tpl_time_obj_state)0)
    {
      alarm->date = start;
      alarm->cycle = cycle;
      alarm->state = 1;

      tpl_insert_time_obj(alarm);
    }
    else
    {
      result = 7;
    }
    ;
  }

  tpl_release_task_lock();
  return result;
}
tpl_status
tpl_cancel_alarm_service(const tpl_alarm_id alarm_id)
{

  tpl_status result = 0;
  tpl_time_obj * alarm;
  tpl_get_task_lock();
  if (((tpl_bool)0) != tpl_get_interrupt_lock_status()) { result = 19; }


  if ((result == (tpl_status)0) && tpl_alarm_callback_running()) { result = (tpl_status)2; }
  if ((result == (tpl_status)0) && ((alarm_id) >= (tpl_alarm_id)1)) { result = (tpl_status)3; }

  if ((result) == 0)
  {
    alarm = tpl_alarm_table[alarm_id];
    ;
    if (alarm->state == (tpl_time_obj_state)1)
    {
      tpl_remove_time_obj(alarm);
      alarm->state = 0;

    }
    else
    {
      result = 5;
    }
    ;
  }

  tpl_release_task_lock();
  return result;
}
extern const int signal_for_counters;
void tpl_create_context(tpl_proc_id proc_id);
void tpl_posix_sigblock(const char* error_message);
void tpl_posix_sigunblock(const char* error_message);
void tpl_posix_siginit(void);
extern void tpl_viper_init(void);
extern void tpl_viper_start_one_shot_timer(int sig, unsigned long delay);
extern void tpl_viper_start_auto_timer(int sig, unsigned long delay);
extern int tpl_viper_get_motor_pos(int motor);
extern void tpl_viper_set_motor_csg(int motor, int csg);
typedef int wchar_t;

typedef struct
  {
    int quot;
    int rem;
  } div_t;
typedef struct
  {
    long int quot;
    long int rem;
  } ldiv_t;
__extension__ typedef struct
  {
    long long int quot;
    long long int rem;
  } lldiv_t;
extern size_t __ctype_get_mb_cur_max (void) __attribute__ ((__nothrow__ , __leaf__)) ;
extern double atof (const char *__nptr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1))) ;
extern int atoi (const char *__nptr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1))) ;
extern long int atol (const char *__nptr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1))) ;
__extension__ extern long long int atoll (const char *__nptr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1))) ;
extern double strtod (const char *__restrict __nptr,
        char **__restrict __endptr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern float strtof (const char *__restrict __nptr,
       char **__restrict __endptr) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern long double strtold (const char *__restrict __nptr,
       char **__restrict __endptr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern long int strtol (const char *__restrict __nptr,
   char **__restrict __endptr, int __base)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern unsigned long int strtoul (const char *__restrict __nptr,
      char **__restrict __endptr, int __base)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
__extension__
extern long long int strtoq (const char *__restrict __nptr,
        char **__restrict __endptr, int __base)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
__extension__
extern unsigned long long int strtouq (const char *__restrict __nptr,
           char **__restrict __endptr, int __base)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
__extension__
extern long long int strtoll (const char *__restrict __nptr,
         char **__restrict __endptr, int __base)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
__extension__
extern unsigned long long int strtoull (const char *__restrict __nptr,
     char **__restrict __endptr, int __base)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern char *l64a (long int __n) __attribute__ ((__nothrow__ , __leaf__)) ;
extern long int a64l (const char *__s)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1))) ;

typedef __u_char u_char;
typedef __u_short u_short;
typedef __u_int u_int;
typedef __u_long u_long;
typedef __quad_t quad_t;
typedef __u_quad_t u_quad_t;
typedef __fsid_t fsid_t;
typedef __loff_t loff_t;
typedef __ino_t ino_t;
typedef __dev_t dev_t;
typedef __mode_t mode_t;
typedef __nlink_t nlink_t;
typedef __id_t id_t;
typedef __daddr_t daddr_t;
typedef __caddr_t caddr_t;
typedef __key_t key_t;
typedef __clock_t clock_t;
typedef __clockid_t clockid_t;
typedef __timer_t timer_t;
typedef unsigned long int ulong;
typedef unsigned short int ushort;
typedef unsigned int uint;
typedef __uint8_t u_int8_t;
typedef __uint16_t u_int16_t;
typedef __uint32_t u_int32_t;
typedef __uint64_t u_int64_t;
typedef int register_t __attribute__ ((__mode__ (__word__)));
static __inline __uint16_t
__bswap_16 (__uint16_t __bsx)
{
  return __builtin_bswap16 (__bsx);
}
static __inline __uint32_t
__bswap_32 (__uint32_t __bsx)
{
  return __builtin_bswap32 (__bsx);
}
__extension__ static __inline __uint64_t
__bswap_64 (__uint64_t __bsx)
{
  return __builtin_bswap64 (__bsx);
}
static __inline __uint16_t
__uint16_identity (__uint16_t __x)
{
  return __x;
}
static __inline __uint32_t
__uint32_identity (__uint32_t __x)
{
  return __x;
}
static __inline __uint64_t
__uint64_identity (__uint64_t __x)
{
  return __x;
}
struct timeval
{
  __time_t tv_sec;
  __suseconds_t tv_usec;
};
typedef __suseconds_t suseconds_t;
typedef long int __fd_mask;
typedef struct
  {
    __fd_mask __fds_bits[1024 / (8 * (int) sizeof (__fd_mask))];
  } fd_set;
typedef __fd_mask fd_mask;

extern int select (int __nfds, fd_set *__restrict __readfds,
     fd_set *__restrict __writefds,
     fd_set *__restrict __exceptfds,
     struct timeval *__restrict __timeout);
extern int pselect (int __nfds, fd_set *__restrict __readfds,
      fd_set *__restrict __writefds,
      fd_set *__restrict __exceptfds,
      const struct timespec *__restrict __timeout,
      const __sigset_t *__restrict __sigmask);

typedef __blksize_t blksize_t;
typedef __blkcnt_t blkcnt_t;
typedef __fsblkcnt_t fsblkcnt_t;
typedef __fsfilcnt_t fsfilcnt_t;

extern long int random (void) __attribute__ ((__nothrow__ , __leaf__));
extern void srandom (unsigned int __seed) __attribute__ ((__nothrow__ , __leaf__));
extern char *initstate (unsigned int __seed, char *__statebuf,
   size_t __statelen) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2)));
extern char *setstate (char *__statebuf) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
struct random_data
  {
    int32_t *fptr;
    int32_t *rptr;
    int32_t *state;
    int rand_type;
    int rand_deg;
    int rand_sep;
    int32_t *end_ptr;
  };
extern int random_r (struct random_data *__restrict __buf,
       int32_t *__restrict __result) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern int srandom_r (unsigned int __seed, struct random_data *__buf)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2)));
extern int initstate_r (unsigned int __seed, char *__restrict __statebuf,
   size_t __statelen,
   struct random_data *__restrict __buf)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2, 4)));
extern int setstate_r (char *__restrict __statebuf,
         struct random_data *__restrict __buf)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern int rand (void) __attribute__ ((__nothrow__ , __leaf__));
extern void srand (unsigned int __seed) __attribute__ ((__nothrow__ , __leaf__));
extern int rand_r (unsigned int *__seed) __attribute__ ((__nothrow__ , __leaf__));
extern double drand48 (void) __attribute__ ((__nothrow__ , __leaf__));
extern double erand48 (unsigned short int __xsubi[3]) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern long int lrand48 (void) __attribute__ ((__nothrow__ , __leaf__));
extern long int nrand48 (unsigned short int __xsubi[3])
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern long int mrand48 (void) __attribute__ ((__nothrow__ , __leaf__));
extern long int jrand48 (unsigned short int __xsubi[3])
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern void srand48 (long int __seedval) __attribute__ ((__nothrow__ , __leaf__));
extern unsigned short int *seed48 (unsigned short int __seed16v[3])
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern void lcong48 (unsigned short int __param[7]) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
struct drand48_data
  {
    unsigned short int __x[3];
    unsigned short int __old_x[3];
    unsigned short int __c;
    unsigned short int __init;
    __extension__ unsigned long long int __a;
  };
extern int drand48_r (struct drand48_data *__restrict __buffer,
        double *__restrict __result) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern int erand48_r (unsigned short int __xsubi[3],
        struct drand48_data *__restrict __buffer,
        double *__restrict __result) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern int lrand48_r (struct drand48_data *__restrict __buffer,
        long int *__restrict __result)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern int nrand48_r (unsigned short int __xsubi[3],
        struct drand48_data *__restrict __buffer,
        long int *__restrict __result)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern int mrand48_r (struct drand48_data *__restrict __buffer,
        long int *__restrict __result)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern int jrand48_r (unsigned short int __xsubi[3],
        struct drand48_data *__restrict __buffer,
        long int *__restrict __result)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern int srand48_r (long int __seedval, struct drand48_data *__buffer)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2)));
extern int seed48_r (unsigned short int __seed16v[3],
       struct drand48_data *__buffer) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern int lcong48_r (unsigned short int __param[7],
        struct drand48_data *__buffer)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern __uint32_t arc4random (void)
     __attribute__ ((__nothrow__ , __leaf__)) ;
extern void arc4random_buf (void *__buf, size_t __size)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern __uint32_t arc4random_uniform (__uint32_t __upper_bound)
     __attribute__ ((__nothrow__ , __leaf__)) ;
extern void *malloc (size_t __size) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__malloc__))
     __attribute__ ((__alloc_size__ (1))) ;
extern void *calloc (size_t __nmemb, size_t __size)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__malloc__)) __attribute__ ((__alloc_size__ (1, 2))) ;
extern void *realloc (void *__ptr, size_t __size)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__warn_unused_result__)) __attribute__ ((__alloc_size__ (2)));
extern void free (void *__ptr) __attribute__ ((__nothrow__ , __leaf__));
extern void *reallocarray (void *__ptr, size_t __nmemb, size_t __size)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__warn_unused_result__))
     __attribute__ ((__alloc_size__ (2, 3)))
    __attribute__ ((__malloc__ (__builtin_free, 1)));
extern void *reallocarray (void *__ptr, size_t __nmemb, size_t __size)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__malloc__ (reallocarray, 1)));

extern void *alloca (size_t __size) __attribute__ ((__nothrow__ , __leaf__));

extern void *valloc (size_t __size) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__malloc__))
     __attribute__ ((__alloc_size__ (1))) ;
extern int posix_memalign (void **__memptr, size_t __alignment, size_t __size)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) ;
extern void *aligned_alloc (size_t __alignment, size_t __size)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__malloc__)) __attribute__ ((__alloc_align__ (1)))
     __attribute__ ((__alloc_size__ (2))) ;
extern void abort (void) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__noreturn__)) __attribute__ ((__cold__));
extern int atexit (void (*__func) (void)) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern int at_quick_exit (void (*__func) (void)) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern int on_exit (void (*__func) (int __status, void *__arg), void *__arg)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern void exit (int __status) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__noreturn__));
extern void quick_exit (int __status) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__noreturn__));
extern void _Exit (int __status) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__noreturn__));
extern char *getenv (const char *__name) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) ;
extern int putenv (char *__string) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern int setenv (const char *__name, const char *__value, int __replace)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2)));
extern int unsetenv (const char *__name) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern int clearenv (void) __attribute__ ((__nothrow__ , __leaf__));
extern char *mktemp (char *__template) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern int mkstemp (char *__template) __attribute__ ((__nonnull__ (1))) ;
extern int mkstemps (char *__template, int __suffixlen) __attribute__ ((__nonnull__ (1))) ;
extern char *mkdtemp (char *__template) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) ;
extern int system (const char *__command) ;
extern char *realpath (const char *__restrict __name,
         char *__restrict __resolved) __attribute__ ((__nothrow__ , __leaf__)) ;
typedef int (*__compar_fn_t) (const void *, const void *);
extern void *bsearch (const void *__key, const void *__base,
        size_t __nmemb, size_t __size, __compar_fn_t __compar)
     __attribute__ ((__nonnull__ (1, 2, 5))) ;
extern void qsort (void *__base, size_t __nmemb, size_t __size,
     __compar_fn_t __compar) __attribute__ ((__nonnull__ (1, 4)));
extern int abs (int __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)) ;
extern long int labs (long int __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)) ;
__extension__ extern long long int llabs (long long int __x)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)) ;
extern div_t div (int __numer, int __denom)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)) ;
extern ldiv_t ldiv (long int __numer, long int __denom)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)) ;
__extension__ extern lldiv_t lldiv (long long int __numer,
        long long int __denom)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)) ;
extern char *ecvt (double __value, int __ndigit, int *__restrict __decpt,
     int *__restrict __sign) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (3, 4))) ;
extern char *fcvt (double __value, int __ndigit, int *__restrict __decpt,
     int *__restrict __sign) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (3, 4))) ;
extern char *gcvt (double __value, int __ndigit, char *__buf)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (3))) ;
extern char *qecvt (long double __value, int __ndigit,
      int *__restrict __decpt, int *__restrict __sign)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (3, 4))) ;
extern char *qfcvt (long double __value, int __ndigit,
      int *__restrict __decpt, int *__restrict __sign)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (3, 4))) ;
extern char *qgcvt (long double __value, int __ndigit, char *__buf)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (3))) ;
extern int ecvt_r (double __value, int __ndigit, int *__restrict __decpt,
     int *__restrict __sign, char *__restrict __buf,
     size_t __len) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (3, 4, 5)));
extern int fcvt_r (double __value, int __ndigit, int *__restrict __decpt,
     int *__restrict __sign, char *__restrict __buf,
     size_t __len) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (3, 4, 5)));
extern int qecvt_r (long double __value, int __ndigit,
      int *__restrict __decpt, int *__restrict __sign,
      char *__restrict __buf, size_t __len)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (3, 4, 5)));
extern int qfcvt_r (long double __value, int __ndigit,
      int *__restrict __decpt, int *__restrict __sign,
      char *__restrict __buf, size_t __len)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (3, 4, 5)));
extern int mblen (const char *__s, size_t __n) __attribute__ ((__nothrow__ , __leaf__));
extern int mbtowc (wchar_t *__restrict __pwc,
     const char *__restrict __s, size_t __n) __attribute__ ((__nothrow__ , __leaf__));
extern int wctomb (char *__s, wchar_t __wchar) __attribute__ ((__nothrow__ , __leaf__));
extern size_t mbstowcs (wchar_t *__restrict __pwcs,
   const char *__restrict __s, size_t __n) __attribute__ ((__nothrow__ , __leaf__))
    __attribute__ ((__access__ (__read_only__, 2)));
extern size_t wcstombs (char *__restrict __s,
   const wchar_t *__restrict __pwcs, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__))
  __attribute__ ((__access__ (__write_only__, 1, 3)))
  __attribute__ ((__access__ (__read_only__, 2)));
extern int rpmatch (const char *__response) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1))) ;
extern int getsubopt (char **__restrict __optionp,
        char *const *__restrict __tokens,
        char **__restrict __valuep)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2, 3))) ;
extern int getloadavg (double __loadavg[], int __nelem)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern void *memcpy (void *__restrict __dest, const void *__restrict __src,
       size_t __n) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern void *memmove (void *__dest, const void *__src, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern void *memccpy (void *__restrict __dest, const void *__restrict __src,
        int __c, size_t __n)
    __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2))) __attribute__ ((__access__ (__write_only__, 1, 4)));
extern void *memset (void *__s, int __c, size_t __n) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern int memcmp (const void *__s1, const void *__s2, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));
extern int __memcmpeq (const void *__s1, const void *__s2, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));
extern void *memchr (const void *__s, int __c, size_t __n)
      __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));
extern char *strcpy (char *__restrict __dest, const char *__restrict __src)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern char *strncpy (char *__restrict __dest,
        const char *__restrict __src, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern char *strcat (char *__restrict __dest, const char *__restrict __src)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern char *strncat (char *__restrict __dest, const char *__restrict __src,
        size_t __n) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern int strcmp (const char *__s1, const char *__s2)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));
extern int strncmp (const char *__s1, const char *__s2, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));
extern int strcoll (const char *__s1, const char *__s2)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));
extern size_t strxfrm (char *__restrict __dest,
         const char *__restrict __src, size_t __n)
    __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2))) __attribute__ ((__access__ (__write_only__, 1, 3)));
struct __locale_struct
{
  struct __locale_data *__locales[13];
  const unsigned short int *__ctype_b;
  const int *__ctype_tolower;
  const int *__ctype_toupper;
  const char *__names[13];
};
typedef struct __locale_struct *__locale_t;
typedef __locale_t locale_t;
extern int strcoll_l (const char *__s1, const char *__s2, locale_t __l)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2, 3)));
extern size_t strxfrm_l (char *__dest, const char *__src, size_t __n,
    locale_t __l) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2, 4)))
     __attribute__ ((__access__ (__write_only__, 1, 3)));
extern char *strdup (const char *__s)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__malloc__)) __attribute__ ((__nonnull__ (1)));
extern char *strndup (const char *__string, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__malloc__)) __attribute__ ((__nonnull__ (1)));
extern char *strchr (const char *__s, int __c)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));
extern char *strrchr (const char *__s, int __c)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));
extern char *strchrnul (const char *__s, int __c)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));
extern size_t strcspn (const char *__s, const char *__reject)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));
extern size_t strspn (const char *__s, const char *__accept)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));
extern char *strpbrk (const char *__s, const char *__accept)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));
extern char *strstr (const char *__haystack, const char *__needle)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));
extern char *strtok (char *__restrict __s, const char *__restrict __delim)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2)));
extern char *__strtok_r (char *__restrict __s,
    const char *__restrict __delim,
    char **__restrict __save_ptr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2, 3)));
extern char *strtok_r (char *__restrict __s, const char *__restrict __delim,
         char **__restrict __save_ptr)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2, 3)));
extern char *strcasestr (const char *__haystack, const char *__needle)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));
extern void *memmem (const void *__haystack, size_t __haystacklen,
       const void *__needle, size_t __needlelen)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 3)))
    __attribute__ ((__access__ (__read_only__, 1, 2)))
    __attribute__ ((__access__ (__read_only__, 3, 4)));
extern void *__mempcpy (void *__restrict __dest,
   const void *__restrict __src, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern void *mempcpy (void *__restrict __dest,
        const void *__restrict __src, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern size_t strlen (const char *__s)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));
extern size_t strnlen (const char *__string, size_t __maxlen)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));
extern char *strerror (int __errnum) __attribute__ ((__nothrow__ , __leaf__));
extern int strerror_r (int __errnum, char *__buf, size_t __buflen) __asm__ ("" "__xpg_strerror_r") __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2)))
    __attribute__ ((__access__ (__write_only__, 2, 3)));
extern char *strerror_l (int __errnum, locale_t __l) __attribute__ ((__nothrow__ , __leaf__));

extern int bcmp (const void *__s1, const void *__s2, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));
extern void bcopy (const void *__src, void *__dest, size_t __n)
  __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern void bzero (void *__s, size_t __n) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern char *index (const char *__s, int __c)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));
extern char *rindex (const char *__s, int __c)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));
extern int ffs (int __i) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));
extern int ffsl (long int __l) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));
__extension__ extern int ffsll (long long int __ll)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));
extern int strcasecmp (const char *__s1, const char *__s2)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));
extern int strncasecmp (const char *__s1, const char *__s2, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));
extern int strcasecmp_l (const char *__s1, const char *__s2, locale_t __loc)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2, 3)));
extern int strncasecmp_l (const char *__s1, const char *__s2,
     size_t __n, locale_t __loc)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2, 4)));

extern void explicit_bzero (void *__s, size_t __n) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)))
    __attribute__ ((__access__ (__write_only__, 1, 2)));
extern char *strsep (char **__restrict __stringp,
       const char *__restrict __delim)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern char *strsignal (int __sig) __attribute__ ((__nothrow__ , __leaf__));
extern char *__stpcpy (char *__restrict __dest, const char *__restrict __src)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern char *stpcpy (char *__restrict __dest, const char *__restrict __src)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern char *__stpncpy (char *__restrict __dest,
   const char *__restrict __src, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern char *stpncpy (char *__restrict __dest,
        const char *__restrict __src, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));
extern size_t strlcpy (char *__restrict __dest,
         const char *__restrict __src, size_t __n)
  __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2))) __attribute__ ((__access__ (__write_only__, 1, 3)));
extern size_t strlcat (char *__restrict __dest,
         const char *__restrict __src, size_t __n)
  __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2))) __attribute__ ((__access__ (__read_write__, 1, 3)));


typedef enum
{
  P_ALL,
  P_PID,
  P_PGID,
  P_PIDFD,
} idtype_t;
extern __pid_t wait (int *__stat_loc);
extern __pid_t waitpid (__pid_t __pid, int *__stat_loc, int __options);
extern int waitid (idtype_t __idtype, __id_t __id, siginfo_t *__infop,
     int __options);
struct rusage;
extern __pid_t wait3 (int *__stat_loc, int __options,
        struct rusage * __usage) __attribute__ ((__nothrow__));
extern __pid_t wait4 (__pid_t __pid, int *__stat_loc, int __options,
        struct rusage *__usage) __attribute__ ((__nothrow__));

void tpl_osek_func_stub( tpl_proc_id task_id );
void tpl_shutdown(void);
extern void tpl_posixvp_irq_gen_init(void);
void set_leds(uint8_t led);
void reset_leds(uint8_t led);
extern volatile uint32 tpl_locking_depth;
extern tpl_bool tpl_user_task_lock;
extern uint32 tpl_cpt_os_task_lock;
extern void CallTerminateTask(void);
extern void viper_kill(void);
void idle_function(void)
{
    while(1) pause();
}
void tpl_shutdown(void)
{
    tpl_posix_sigblock("tpl_shutdown_failed");
    viper_kill();
    exit(0);
}
volatile int x = 0;
int cnt = 0;
void tpl_get_task_lock(void)
{
    if(0 == tpl_locking_depth) {
        tpl_posix_sigblock("tpl_get_lock failed");
    }
    tpl_locking_depth++;
    tpl_cpt_os_task_lock++;
}
void tpl_release_task_lock(void)
{
    ((void) sizeof ((tpl_locking_depth > 0) ? 1 : 0), __extension__ ({ if (tpl_locking_depth > 0) ; else __assert_fail ("tpl_locking_depth > 0", "../../../machines/posix/tpl_machine_posix.c", 102, __extension__ __PRETTY_FUNCTION__); }));
    tpl_locking_depth--;
    tpl_cpt_os_task_lock--;
    if ( (tpl_locking_depth == 0) && (((tpl_bool)0) == tpl_user_task_lock) )
    {
        tpl_posix_sigunblock("tpl_release_lock failed");
    }
}
    void tpl_switch_context(
            const tpl_context * const old_context,
            const tpl_context * const new_context)
{
    if( ((void *)0) == old_context)
    {
        _longjmp((*new_context)->current, 1);
    }
    else if ( 0 == _setjmp((*old_context)->current) )
    {
        _longjmp((*new_context)->current, 1);
    }
    return;
}
    void tpl_switch_context_from_it(
            const tpl_context * const old_context,
            const tpl_context * const new_context)
{
    if( ((void *)0) == old_context )
    {
        _longjmp((*new_context)->current, 1);
    }
    else if ( 0 == _setjmp((*old_context)->current) )
    {
        _longjmp((*new_context)->current, 1);
    }
    return;
}
void tpl_init_context(
        const tpl_proc_id proc_id)
{
    memcpy( tpl_stat_proc_table[proc_id]->context->current,
            tpl_stat_proc_table[proc_id]->context->initial,
            sizeof(jmp_buf));
}
void tpl_osek_func_stub( tpl_proc_id task_id )
{
    tpl_proc_function func = tpl_stat_proc_table[task_id]->entry;
    tpl_proc_type type = tpl_stat_proc_table[task_id]->type;
    tpl_release_task_lock();
    (*func)();
    if (type == 0x2) {
    }
    else
    {
        CallTerminateTask();
        fprintf(stderr, "[OSEK/VDX Spec. 2.2.3 Sec. 4.7] Ending the task without a call to TerminateTask or ChainTask is strictly forbidden and causes undefined behaviour.\n");
        exit(1);
    }
}
void quit(int n)
{
    (void) n;
    ShutdownOS(0);
}
void tpl_init_machine(void)
{
    tpl_posixvp_irq_gen_init();
    tpl_proc_id proc_id;
    for( proc_id = 0;
            proc_id < 1 +0 +1;
            proc_id++)
    {
        tpl_create_context(proc_id);
    }
    signal(2, quit);
    signal(1, quit);
    tpl_posix_siginit();
    tpl_viper_init();
    tpl_viper_start_auto_timer(signal_for_counters,10000);
}
struct VP_TIMER_PARAM {
 int type;
 unsigned long delay;
 int sig;
};
struct VP_EVENT_PARAM {
    char file_name[256];
    int sig;
};
typedef struct VP_TIMER_PARAM vp_timer_param;
typedef struct VP_EVENT_PARAM vp_event_param;
struct VP_COMMAND
{
 int command;
 union {
  vp_event_param event;
  vp_timer_param timer;
 } params;
};
typedef struct VP_COMMAND vp_command;
struct VP_CTRL
{
    int motor_csg[2];
};
typedef struct VP_CTRL vp_ctrl;
struct VP_STAT
{
    int motor_pos[2];
};
typedef struct VP_STAT vp_stat;

struct flock
  {
    short int l_type;
    short int l_whence;
    __off_t l_start;
    __off_t l_len;
    __pid_t l_pid;
  };


struct stat
  {
    __dev_t st_dev;
    __ino_t st_ino;
    __nlink_t st_nlink;
    __mode_t st_mode;
    __uid_t st_uid;
    __gid_t st_gid;
    int __pad0;
    __dev_t st_rdev;
    __off_t st_size;
    __blksize_t st_blksize;
    __blkcnt_t st_blocks;
    struct timespec st_atim;
    struct timespec st_mtim;
    struct timespec st_ctim;
    __syscall_slong_t __glibc_reserved[3];
  };
extern int fcntl (int __fd, int __cmd, ...);
extern int open (const char *__file, int __oflag, ...) __attribute__ ((__nonnull__ (1)));
extern int openat (int __fd, const char *__file, int __oflag, ...)
     __attribute__ ((__nonnull__ (2)));
extern int creat (const char *__file, mode_t __mode) __attribute__ ((__nonnull__ (1)));
extern int posix_fadvise (int __fd, off_t __offset, off_t __len,
     int __advise) __attribute__ ((__nothrow__ , __leaf__));
extern int posix_fallocate (int __fd, off_t __offset, off_t __len);

typedef union
{
  char __size[32];
  long int __align;
} sem_t;

extern int sem_init (sem_t *__sem, int __pshared, unsigned int __value)
  __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern int sem_destroy (sem_t *__sem) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern sem_t *sem_open (const char *__name, int __oflag, ...)
  __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern int sem_close (sem_t *__sem) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern int sem_unlink (const char *__name) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern int sem_wait (sem_t *__sem) __attribute__ ((__nonnull__ (1)));
extern int sem_timedwait (sem_t *__restrict __sem,
     const struct timespec *__restrict __abstime)
  __attribute__ ((__nonnull__ (1, 2)));
extern int sem_trywait (sem_t *__sem) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));
extern int sem_post (sem_t *__sem) __attribute__ ((__nothrow__)) __attribute__ ((__nonnull__ (1)));
extern int sem_getvalue (sem_t *__restrict __sem, int *__restrict __sval)
  __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));


extern void *mmap (void *__addr, size_t __len, int __prot,
     int __flags, int __fd, __off_t __offset) __attribute__ ((__nothrow__ , __leaf__));
extern int munmap (void *__addr, size_t __len) __attribute__ ((__nothrow__ , __leaf__));
extern int mprotect (void *__addr, size_t __len, int __prot) __attribute__ ((__nothrow__ , __leaf__));
extern int msync (void *__addr, size_t __len, int __flags);
extern int madvise (void *__addr, size_t __len, int __advice) __attribute__ ((__nothrow__ , __leaf__));
extern int posix_madvise (void *__addr, size_t __len, int __advice) __attribute__ ((__nothrow__ , __leaf__));
extern int mlock (const void *__addr, size_t __len) __attribute__ ((__nothrow__ , __leaf__))
    __attribute__ ((__access__ (__none__, 1)));
extern int munlock (const void *__addr, size_t __len) __attribute__ ((__nothrow__ , __leaf__))
    __attribute__ ((__access__ (__none__, 1)));
extern int mlockall (int __flags) __attribute__ ((__nothrow__ , __leaf__));
extern int munlockall (void) __attribute__ ((__nothrow__ , __leaf__));
extern int mincore (void *__start, size_t __len, unsigned char *__vec)
     __attribute__ ((__nothrow__ , __leaf__));
extern int shm_open (const char *__name, int __oflag, mode_t __mode);
extern int shm_unlink (const char *__name);

static char ctrl_file_path[32];
static char stat_file_path[32];
static char data_file_path[32];
static char r_sem_file_path[32];
static char w_sem_file_path[32];
static char synchro_sem_file_path[32];
static sem_t *r_com_sem = ((void *)0);
static sem_t *w_com_sem = ((void *)0);
static sem_t *synchro_sem = ((void *)0);
static int sh_mem = -1;
static vp_command *command = ((void *)0);
static pid_t viper_pid = -1;
static int ctrl_sh_mem = -1;
static int stat_sh_mem = -1;
static vp_ctrl *ctrl = ((void *)0);
static vp_stat *status = ((void *)0);
void viper_kill(void)
{
  if (viper_pid != -1)
  {
    if (kill(viper_pid, 1) != 0)
      perror("error viper: ");
  }
}
void tpl_viper_init(void)
{
  int viper_exe_ok = 0;
  char *viper_args[] = {((void *)0), ((void *)0)};
  char *viper_env[] = {((void *)0)};
  char *viper_path = getenv("VIPER_PATH");
  char viper_exe[256];
  if (viper_path != ((void *)0))
  {
    strncpy(viper_exe, viper_path, 255);
    strcat(viper_exe, "/viper");
    if (access(viper_exe, 1) == 0)
    {
      viper_exe_ok = 1;
    }
    else
    {
      printf(
          "VIPER_PATH is defined but viper is not accessible or executable\n");
    }
  }
  else
  {
    viper_path = "../viper";
    strncpy(viper_exe, viper_path, 256 - 1 - strlen("/viper"));
    strcat(viper_exe, "/viper");
    if (access(viper_exe, 1) != 0)
    {
      fprintf(stderr, "Error: VIPER_PATH is not defined. Exiting\n");
      exit(1);
    }
    else
    {
      viper_exe_ok = 1;
    }
  }
  if (viper_exe_ok == 1)
  {
    viper_args[0] = viper_exe;
    sprintf(data_file_path, "/viper.data.%d", getpid());
    sprintf(r_sem_file_path, "/viper.rsem.%d", getpid());
    sprintf(w_sem_file_path, "/viper.wsem.%d", getpid());
    sprintf(synchro_sem_file_path, "/viper.wsem.%d", getpid());
    sprintf(ctrl_file_path, "/viper.ctrl.%d", getpid());
    sprintf(stat_file_path, "/viper.stat.%d", getpid());
    sh_mem = shm_open(data_file_path, (0100 | 02), 0600);
    if (sh_mem < 0)
    {
      perror("viper: fail to create the shared memory object");
      exit(-1);
    }
    ftruncate(sh_mem, sizeof(vp_command));
    ctrl_sh_mem = shm_open(ctrl_file_path, (0100 | 02), 0600);
    if (ctrl_sh_mem < 0)
    {
      perror("viper: fail to open the control shared memory object");
      exit(-1);
    }
    ftruncate(ctrl_sh_mem, sizeof(vp_ctrl));
    stat_sh_mem = shm_open(stat_file_path, (0100 | 02), 0600);
    if (stat_sh_mem < 0)
    {
      perror("viper: fail to open the status shared memory object");
      exit(-1);
    }
    ftruncate(stat_sh_mem, sizeof(vp_stat));
    command = mmap(0, sizeof(vp_command), (0x2 | 0x1), 0x01,
                   sh_mem, 0);
    if (command == (void *)-1)
    {
      perror("viper: unable to map the shared memory object");
      exit(-1);
    }
    ctrl = mmap(0, sizeof(vp_ctrl), (0x2 | 0x1), 0x01,
                ctrl_sh_mem, 0);
    if (ctrl == (void *)-1)
    {
      perror("viper: unable to map the control shared memory object");
      exit(-1);
    }
    status = mmap(0, sizeof(vp_stat), (0x2 | 0x1), 0x01,
                  stat_sh_mem, 0);
    if (status == (void *)-1)
    {
      perror("viper: unable to map the status shared memory object");
      exit(-1);
    }
    ctrl->motor_csg[0] = 0;
    ctrl->motor_csg[1] = 0;
    r_com_sem = sem_open(r_sem_file_path, 0100, 0600, 0);
    if (r_com_sem == (void *)((sem_t *) 0))
    {
      perror("viper: unable to create the reader semaphore");
    }
    w_com_sem = sem_open(w_sem_file_path, 0100, 0600, 0);
    if (w_com_sem == (void *)((sem_t *) 0))
    {
      perror("viper: unable to create the reading semaphore");
    }
    synchro_sem = sem_open(synchro_sem_file_path, 0100, 0600, 0);
    if (synchro_sem == (void *)((sem_t *) 0))
    {
      perror("viper: unable to create the synchro semaphore");
    }
    if ((viper_pid = fork()) == 0)
    {
      if (execve(viper_exe, viper_args, viper_env) < 0)
      {
        printf("%s\n", viper_exe);
        perror("viper: unable to launch viper");
        exit(1);
      }
      perror("viper : why I'm here ?");
      exit(-1);
    }
    else if (1 != viper_pid)
    {
      if (0 != sem_wait(synchro_sem))
      {
        fprintf(stderr, "[%d] %s\n", 228, "../../../machines/posix/tpl_viper_interface.c");
        perror("tpl : sem_wait(viper)");
      }
    }
  }
  else
  {
    exit(1);
  }
}
void send_viper_command(vp_command *i_com)
{
  memcpy(command, i_com, sizeof(vp_command));
  if (sem_post(r_com_sem) < 0)
  {
    perror("viper_test: fail while posting reader semaphore");
  }
  if (sem_wait(w_com_sem) < 0)
  {
    perror("viper_test: fail while waiting writer semaphore");
  }
}
void tpl_viper_start_one_shot_timer(int sig, unsigned long delay)
{
  vp_command command_to_send;
  command_to_send.command = 1;
  command_to_send.params.timer.type = 0;
  command_to_send.params.timer.delay = delay;
  command_to_send.params.timer.sig = sig;
  send_viper_command(&command_to_send);
}
void tpl_viper_start_auto_timer(int sig, unsigned long delay)
{
  vp_command command_to_send;
  command_to_send.command = 1;
  command_to_send.params.timer.type = 1;
  command_to_send.params.timer.delay = delay;
  command_to_send.params.timer.sig = sig;
  send_viper_command(&command_to_send);
}
int tpl_viper_get_motor_pos(int motor)
{
  if (motor >= 0 && motor < 2)
  {
    return status->motor_pos[motor];
  }
  else
  {
    return 0;
  }
}
void tpl_viper_set_motor_csg(int motor, int csg)
{
  if (motor >= 0 && motor < 2)
  {
    ctrl->motor_csg[motor] = csg;
  }
}

struct timezone
  {
    int tz_minuteswest;
    int tz_dsttime;
  };
extern int gettimeofday (struct timeval *__restrict __tv,
    void *__restrict __tz) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern int settimeofday (const struct timeval *__tv,
    const struct timezone *__tz)
     __attribute__ ((__nothrow__ , __leaf__));
extern int adjtime (const struct timeval *__delta,
      struct timeval *__olddelta) __attribute__ ((__nothrow__ , __leaf__));
enum __itimer_which
  {
    ITIMER_REAL = 0,
    ITIMER_VIRTUAL = 1,
    ITIMER_PROF = 2
  };
struct itimerval
  {
    struct timeval it_interval;
    struct timeval it_value;
  };
typedef int __itimer_which_t;
extern int getitimer (__itimer_which_t __which,
        struct itimerval *__value) __attribute__ ((__nothrow__ , __leaf__));
extern int setitimer (__itimer_which_t __which,
        const struct itimerval *__restrict __new,
        struct itimerval *__restrict __old) __attribute__ ((__nothrow__ , __leaf__));
extern int utimes (const char *__file, const struct timeval __tvp[2])
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern int lutimes (const char *__file, const struct timeval __tvp[2])
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));
extern int futimes (int __fd, const struct timeval __tvp[2]) __attribute__ ((__nothrow__ , __leaf__));

const int signal_for_counters = 12;
extern volatile uint32 tpl_locking_depth;
extern tpl_bool tpl_user_task_lock;
extern uint32 tpl_cpt_os_task_lock;
sigset_t signal_set;
extern void tpl_call_counter_tick(void);
void tpl_enable_interrupts(void)
{
  if (-1 == sigprocmask(1, &signal_set, ((void *)0)))
  {
    perror("tpl_enable_interrupt failed");
    exit(-1);
  }
}
void tpl_enable_os_interrupts(void)
{
  tpl_enable_interrupts();
}
void tpl_disable_interrupts(void)
{
  if (-1 == sigprocmask(0, &signal_set, ((void *)0)))
  {
    perror("tpl_disable_interrupts failed");
    exit(-1);
  }
}
void tpl_disable_os_interrupts(void)
{
  tpl_disable_interrupts();
}
void tpl_signal_handler(int sig)
{
  tpl_locking_depth++;
  tpl_cpt_os_task_lock++;
  if (signal_for_counters == sig)
  {
    tpl_call_counter_tick();
  }
  else
  {
  }
  tpl_locking_depth--;
  tpl_cpt_os_task_lock--;
}
void tpl_posix_sigblock(const char *error_message)
{
  if (sigprocmask(0, &signal_set, ((void *)0)) == -1)
  {
    perror(error_message);
    exit(-1);
  }
}
void tpl_posix_sigunblock(const char *error_message)
{
  if (sigprocmask(1, &signal_set, ((void *)0)) == -1)
  {
    perror(error_message);
    exit(-1);
  }
}
void tpl_posix_siginit(void)
{
  struct sigaction sa;
  sigemptyset(&signal_set);
  sigaddset(&signal_set, signal_for_counters);
  sa.__sigaction_handler.sa_handler = tpl_signal_handler;
  sa.sa_mask = signal_set;
  sa.sa_flags = 0x10000000;
  sigaction(signal_for_counters, &sa, ((void *)0));
}
sigset_t saved_mask;
sig_atomic_t handler_has_been_triggered;
tpl_proc_id new_proc_id;
void tpl_create_context_boot(void)
{
    tpl_proc_id context_owner_proc_id;
    sigprocmask(2, &saved_mask, ((void *)0));
    context_owner_proc_id = new_proc_id;
    if( 0 == _setjmp (tpl_stat_proc_table[context_owner_proc_id]->context->initial) )
    {
        longjmp(tpl_stat_proc_table[1 + 0]->context->current, 1);
    }
    tpl_osek_func_stub(tpl_kern.running_id);
    abort();
    return;
}
void tpl_create_context_trampoline(int sigid)
{
    (void) sigid;
    if( 0==_setjmp (tpl_stat_proc_table[new_proc_id]->context->initial) )
    {
        handler_has_been_triggered = ((tpl_bool)1);
        return;
    }
    tpl_create_context_boot();
    return;
}
void tpl_create_context(
        const tpl_proc_id proc_id)
{
    struct sigaction new_action;
    struct sigaction old_action;
    stack_t new_stack;
    stack_t old_stack;
    sigset_t new_mask;
    sigset_t old_mask;
    sigemptyset(&new_mask);
    sigaddset(&new_mask, 10);
    sigprocmask(0, &new_mask, &old_mask);
    memset((void*)&new_action, 0, sizeof(new_action));
    new_action.__sigaction_handler.sa_handler = tpl_create_context_trampoline;
    new_action.sa_flags = 0x08000000;
    sigemptyset(&new_action.sa_mask);
    sigaction(10, &new_action, &old_action);
    new_stack.ss_sp = (tpl_stat_proc_table[proc_id]->stack)->stack_zone;
    new_stack.ss_size = (tpl_stat_proc_table[proc_id]->stack)->stack_size;
    new_stack.ss_flags = 0;
    sigaltstack(&new_stack, &old_stack);
    new_proc_id = proc_id;
    saved_mask = old_mask;
    handler_has_been_triggered = ((tpl_bool)0);
    kill(getpid(), 10);
    sigfillset(&new_mask);
    sigdelset(&new_mask, 10);
    while(((tpl_bool)0) == handler_has_been_triggered)
        sigsuspend(&new_mask);
    sigaltstack(((void *)0), &new_stack);
    new_stack.ss_flags = SS_DISABLE;
    sigaltstack(&new_stack, ((void *)0));
    if( ! (old_stack.ss_flags & SS_DISABLE) )
        sigaltstack(&old_stack, ((void *)0));
    sigaction(10, &old_action, ((void *)0));
    sigprocmask(2, &old_mask, ((void *)0));
    if ( 0 == _setjmp (tpl_stat_proc_table[1 + 0]->context->current) )
        longjmp(tpl_stat_proc_table[new_proc_id]->context->initial,1);
    return;
}

extern int *__errno_location (void) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


typedef unsigned char cc_t;
typedef unsigned int speed_t;
typedef unsigned int tcflag_t;
struct termios
  {
    tcflag_t c_iflag;
    tcflag_t c_oflag;
    tcflag_t c_cflag;
    tcflag_t c_lflag;
    cc_t c_line;
    cc_t c_cc[32];
    speed_t c_ispeed;
    speed_t c_ospeed;
  };
extern speed_t cfgetospeed (const struct termios *__termios_p) __attribute__ ((__nothrow__ , __leaf__));
extern speed_t cfgetispeed (const struct termios *__termios_p) __attribute__ ((__nothrow__ , __leaf__));
extern int cfsetospeed (struct termios *__termios_p, speed_t __speed) __attribute__ ((__nothrow__ , __leaf__));
extern int cfsetispeed (struct termios *__termios_p, speed_t __speed) __attribute__ ((__nothrow__ , __leaf__));
extern int cfsetspeed (struct termios *__termios_p, speed_t __speed) __attribute__ ((__nothrow__ , __leaf__));
extern int tcgetattr (int __fd, struct termios *__termios_p) __attribute__ ((__nothrow__ , __leaf__));
extern int tcsetattr (int __fd, int __optional_actions,
        const struct termios *__termios_p) __attribute__ ((__nothrow__ , __leaf__));
extern void cfmakeraw (struct termios *__termios_p) __attribute__ ((__nothrow__ , __leaf__));
extern int tcsendbreak (int __fd, int __duration) __attribute__ ((__nothrow__ , __leaf__));
extern int tcdrain (int __fd);
extern int tcflush (int __fd, int __queue_selector) __attribute__ ((__nothrow__ , __leaf__));
extern int tcflow (int __fd, int __action) __attribute__ ((__nothrow__ , __leaf__));
extern __pid_t tcgetsid (int __fd) __attribute__ ((__nothrow__ , __leaf__));

static pid_t tpl_pid = -1;
static _Bool mode_is_raw = 0;
static struct termios saved_mode;
static volatile sig_atomic_t quit_vp = 0;
static uint8_t tpl_posixvp_leds[4] = {0};
static const char *tpl_posixvp_leds_on[4] = {
    "\033[41m \033[0m", "\033[42m \033[0m", "\033[44m \033[0m",
    "\033[43m \033[0m"};
static const char *tpl_posixvp_leds_off = "_";
void print_leds(void)
{
  char output_string[64] = {'\0'};
  strcat(output_string, "LEDS: ");
  for (uint8_t led = 0; led < 4; led++)
  {
    if (tpl_posixvp_leds[led])
    {
      strcat(output_string, tpl_posixvp_leds_on[led]);
    }
    else
    {
      strcat(output_string, tpl_posixvp_leds_off);
    }
  }
  strcat(output_string, "\r\n");
  write(1, output_string, 64);
}
void set_leds(uint8_t leds)
{
  size_t led = 0;
  while (leds > 0 && led < 4)
  {
    if (leds & 0x1)
    {
      tpl_posixvp_leds[led] = 0x1;
    }
    led++;
    leds = leds >> 1;
  }
  print_leds();
}
void reset_leds(uint8_t leds)
{
  size_t led = 0;
  while (leds > 0 && led < 4)
  {
    if (leds & 0x1)
    {
      tpl_posixvp_leds[led] = 0x0;
    }
    led++;
    leds = leds >> 1;
  }
  print_leds();
}
void switch_to_raw(void)
{
  struct termios new_mode;
  if (!mode_is_raw)
  {
    tcgetattr(0, &saved_mode);
    new_mode = saved_mode;
    cfmakeraw(&new_mode);
    tcsetattr(0, 0, &new_mode);
    mode_is_raw = 1;
  }
}
void switch_to_cooked(void)
{
  if (mode_is_raw)
  {
    tcsetattr(0, 0, &saved_mode);
    mode_is_raw = 0;
  }
}
void set_quit_vp(int sig)
{
  quit_vp = 1;
  if (sig == 17)
  {
    wait(((void *)0));
  }
}
void tpl_posixvp_irq_gen_init(void)
{
  struct sigaction set_quit_vp_act;
  struct sigaction prev_chld_act;
  struct sigaction prev_int_act;
  memset(&set_quit_vp_act, 0, sizeof(set_quit_vp_act));
  set_quit_vp_act.__sigaction_handler.sa_handler = set_quit_vp;
  sigaction(17, &set_quit_vp_act, &prev_chld_act);
  sigaction(2, &set_quit_vp_act, &prev_int_act);
  tpl_pid = fork();
  if (tpl_pid == -1)
  {
    perror("Erreur lors de la creation de trampoline\n");
    exit(-1);
  }
  else if (tpl_pid > 0)
  {
    switch_to_raw();
    while (!quit_vp)
    {
      int read_char;
      read_char = getchar();
      switch (read_char)
      {
      case 'a':
        if (kill(tpl_pid, 15) == -1)
        {
          fprintf(stderr, "posixvp:a:%s\r\n", strerror((*__errno_location ())));
        }
        break;
      case 'b':
        if (kill(tpl_pid, 5) == -1)
        {
          fprintf(stderr, "posixvp:b:%s\r\n", strerror((*__errno_location ())));
        }
        break;
      case 'q':
        quit_vp = 1;
      default:;
      }
    }
    kill(tpl_pid, 2);
  }
  else
  {
    sigaction(17, &prev_chld_act, ((void *)0));
    sigaction(2, &prev_int_act, ((void *)0));
    struct sigaction ign_act;
    memset(&ign_act, 0, sizeof(ign_act));
    ign_act.__sigaction_handler.sa_handler = ((__sighandler_t) 1);
    sigaction(12, &ign_act, ((void *)0));
    sigaction(5, &ign_act, ((void *)0));
    return;
  }
  switch_to_cooked();
  fprintf(stderr, "Exiting virtual platform.\n");
  exit(0);
}
extern tpl_time_obj * const tpl_alarm_table[1];
void WaitActivationPeriodicAlarm(AlarmType Alarm)
{
  uint32 temp, result_inst_;
  TickType result_inst_tt;
  result_inst_tt = 0;
  do
  {
    temp = result_inst_tt;
    result_inst_ = GetAlarm(Alarm, &result_inst_tt);
  } while ((temp >= result_inst_tt) || (temp == (0)));
}
void WaitActivationOneShotAlarm(AlarmType Alarm)
{
  int result_inst_;
  TickType result_inst_tt;
  do
  {
    GetAlarm(Alarm, &result_inst_tt);
  } while ((
      SetRelAlarm(Alarm,
                  tpl_alarm_table[Alarm]->stat_part->counter->max_allowed_value,
                  0) == 7));
  result_inst_ = CancelAlarm(
      Alarm);
  if ((0) == (result_inst_)) {} else {assertImplementationInt((0),(result_inst_),105,"../../../tests/machines/common/commonTestConfig.c");return;};
}
void SyncAllCores_Init(void)
{
}
