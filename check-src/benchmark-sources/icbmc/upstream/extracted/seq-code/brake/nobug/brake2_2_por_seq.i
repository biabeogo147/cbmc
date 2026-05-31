# 1 "brake2_2_por_seq.c"
# 1 "<built-in>"
# 1 "<command-line>"
# 1 "/usr/include/stdc-predef.h" 1 3 4
# 1 "<command-line>" 2
# 1 "brake2_2_por_seq.c"
# 27 "brake2_2_por_seq.c"
# 1 "/usr/include/stdio.h" 1 3 4
# 27 "/usr/include/stdio.h" 3 4
# 1 "/usr/include/features.h" 1 3 4
# 364 "/usr/include/features.h" 3 4
# 1 "/usr/include/sys/cdefs.h" 1 3 4
# 385 "/usr/include/sys/cdefs.h" 3 4
# 1 "/usr/include/bits/wordsize.h" 1 3 4
# 386 "/usr/include/sys/cdefs.h" 2 3 4
# 365 "/usr/include/features.h" 2 3 4
# 388 "/usr/include/features.h" 3 4
# 1 "/usr/include/gnu/stubs.h" 1 3 4
# 10 "/usr/include/gnu/stubs.h" 3 4
# 1 "/usr/include/gnu/stubs-64.h" 1 3 4
# 11 "/usr/include/gnu/stubs.h" 2 3 4
# 389 "/usr/include/features.h" 2 3 4
# 28 "/usr/include/stdio.h" 2 3 4





# 1 "/usr/lib/gcc/x86_64-redhat-linux/4.8.3/include/stddef.h" 1 3 4
# 212 "/usr/lib/gcc/x86_64-redhat-linux/4.8.3/include/stddef.h" 3 4
typedef long unsigned int size_t;
# 34 "/usr/include/stdio.h" 2 3 4

# 1 "/usr/include/bits/types.h" 1 3 4
# 27 "/usr/include/bits/types.h" 3 4
# 1 "/usr/include/bits/wordsize.h" 1 3 4
# 28 "/usr/include/bits/types.h" 2 3 4


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







typedef long int __quad_t;
typedef unsigned long int __u_quad_t;
# 121 "/usr/include/bits/types.h" 3 4
# 1 "/usr/include/bits/typesizes.h" 1 3 4
# 122 "/usr/include/bits/types.h" 2 3 4


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
typedef __quad_t *__qaddr_t;
typedef char *__caddr_t;


typedef long int __intptr_t;


typedef unsigned int __socklen_t;
# 36 "/usr/include/stdio.h" 2 3 4
# 44 "/usr/include/stdio.h" 3 4
struct _IO_FILE;



typedef struct _IO_FILE FILE;





# 64 "/usr/include/stdio.h" 3 4
typedef struct _IO_FILE __FILE;
# 74 "/usr/include/stdio.h" 3 4
# 1 "/usr/include/libio.h" 1 3 4
# 31 "/usr/include/libio.h" 3 4
# 1 "/usr/include/_G_config.h" 1 3 4
# 15 "/usr/include/_G_config.h" 3 4
# 1 "/usr/lib/gcc/x86_64-redhat-linux/4.8.3/include/stddef.h" 1 3 4
# 16 "/usr/include/_G_config.h" 2 3 4




# 1 "/usr/include/wchar.h" 1 3 4
# 82 "/usr/include/wchar.h" 3 4
typedef struct
{
  int __count;
  union
  {

    unsigned int __wch;



    char __wchb[4];
  } __value;
} __mbstate_t;
# 21 "/usr/include/_G_config.h" 2 3 4
typedef struct
{
  __off_t __pos;
  __mbstate_t __state;
} _G_fpos_t;
typedef struct
{
  __off64_t __pos;
  __mbstate_t __state;
} _G_fpos64_t;
# 32 "/usr/include/libio.h" 2 3 4
# 49 "/usr/include/libio.h" 3 4
# 1 "/usr/lib/gcc/x86_64-redhat-linux/4.8.3/include/stdarg.h" 1 3 4
# 40 "/usr/lib/gcc/x86_64-redhat-linux/4.8.3/include/stdarg.h" 3 4
typedef __builtin_va_list __gnuc_va_list;
# 50 "/usr/include/libio.h" 2 3 4
# 144 "/usr/include/libio.h" 3 4
struct _IO_jump_t; struct _IO_FILE;
# 154 "/usr/include/libio.h" 3 4
typedef void _IO_lock_t;





struct _IO_marker {
  struct _IO_marker *_next;
  struct _IO_FILE *_sbuf;



  int _pos;
# 177 "/usr/include/libio.h" 3 4
};


enum __codecvt_result
{
  __codecvt_ok,
  __codecvt_partial,
  __codecvt_error,
  __codecvt_noconv
};
# 245 "/usr/include/libio.h" 3 4
struct _IO_FILE {
  int _flags;




  char* _IO_read_ptr;
  char* _IO_read_end;
  char* _IO_read_base;
  char* _IO_write_base;
  char* _IO_write_ptr;
  char* _IO_write_end;
  char* _IO_buf_base;
  char* _IO_buf_end;

  char *_IO_save_base;
  char *_IO_backup_base;
  char *_IO_save_end;

  struct _IO_marker *_markers;

  struct _IO_FILE *_chain;

  int _fileno;



  int _flags2;

  __off_t _old_offset;



  unsigned short _cur_column;
  signed char _vtable_offset;
  char _shortbuf[1];



  _IO_lock_t *_lock;
# 293 "/usr/include/libio.h" 3 4
  __off64_t _offset;
# 302 "/usr/include/libio.h" 3 4
  void *__pad1;
  void *__pad2;
  void *__pad3;
  void *__pad4;
  size_t __pad5;

  int _mode;

  char _unused2[15 * sizeof (int) - 4 * sizeof (void *) - sizeof (size_t)];

};


typedef struct _IO_FILE _IO_FILE;


struct _IO_FILE_plus;

extern struct _IO_FILE_plus _IO_2_1_stdin_;
extern struct _IO_FILE_plus _IO_2_1_stdout_;
extern struct _IO_FILE_plus _IO_2_1_stderr_;
# 338 "/usr/include/libio.h" 3 4
typedef __ssize_t __io_read_fn (void *__cookie, char *__buf, size_t __nbytes);







typedef __ssize_t __io_write_fn (void *__cookie, const char *__buf,
     size_t __n);







typedef int __io_seek_fn (void *__cookie, __off64_t *__pos, int __w);


typedef int __io_close_fn (void *__cookie);
# 390 "/usr/include/libio.h" 3 4
extern int __underflow (_IO_FILE *);
extern int __uflow (_IO_FILE *);
extern int __overflow (_IO_FILE *, int);
# 434 "/usr/include/libio.h" 3 4
extern int _IO_getc (_IO_FILE *__fp);
extern int _IO_putc (int __c, _IO_FILE *__fp);
extern int _IO_feof (_IO_FILE *__fp) __attribute__ ((__nothrow__ , __leaf__));
extern int _IO_ferror (_IO_FILE *__fp) __attribute__ ((__nothrow__ , __leaf__));

extern int _IO_peekc_locked (_IO_FILE *__fp);





extern void _IO_flockfile (_IO_FILE *) __attribute__ ((__nothrow__ , __leaf__));
extern void _IO_funlockfile (_IO_FILE *) __attribute__ ((__nothrow__ , __leaf__));
extern int _IO_ftrylockfile (_IO_FILE *) __attribute__ ((__nothrow__ , __leaf__));
# 464 "/usr/include/libio.h" 3 4
extern int _IO_vfscanf (_IO_FILE * __restrict, const char * __restrict,
   __gnuc_va_list, int *__restrict);
extern int _IO_vfprintf (_IO_FILE *__restrict, const char *__restrict,
    __gnuc_va_list);
extern __ssize_t _IO_padn (_IO_FILE *, int, __ssize_t);
extern size_t _IO_sgetn (_IO_FILE *, void *, size_t);

extern __off64_t _IO_seekoff (_IO_FILE *, __off64_t, int, int);
extern __off64_t _IO_seekpos (_IO_FILE *, __off64_t, int);

extern void _IO_free_backup_area (_IO_FILE *) __attribute__ ((__nothrow__ , __leaf__));
# 75 "/usr/include/stdio.h" 2 3 4




typedef __gnuc_va_list va_list;
# 90 "/usr/include/stdio.h" 3 4
typedef __off_t off_t;
# 102 "/usr/include/stdio.h" 3 4
typedef __ssize_t ssize_t;







typedef _G_fpos_t fpos_t;




# 164 "/usr/include/stdio.h" 3 4
# 1 "/usr/include/bits/stdio_lim.h" 1 3 4
# 165 "/usr/include/stdio.h" 2 3 4



extern struct _IO_FILE *stdin;
extern struct _IO_FILE *stdout;
extern struct _IO_FILE *stderr;







extern int remove (const char *__filename) __attribute__ ((__nothrow__ , __leaf__));

extern int rename (const char *__old, const char *__new) __attribute__ ((__nothrow__ , __leaf__));




extern int renameat (int __oldfd, const char *__old, int __newfd,
       const char *__new) __attribute__ ((__nothrow__ , __leaf__));








extern FILE *tmpfile (void) ;
# 209 "/usr/include/stdio.h" 3 4
extern char *tmpnam (char *__s) __attribute__ ((__nothrow__ , __leaf__)) ;





extern char *tmpnam_r (char *__s) __attribute__ ((__nothrow__ , __leaf__)) ;
# 227 "/usr/include/stdio.h" 3 4
extern char *tempnam (const char *__dir, const char *__pfx)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__malloc__)) ;








extern int fclose (FILE *__stream);




extern int fflush (FILE *__stream);

# 252 "/usr/include/stdio.h" 3 4
extern int fflush_unlocked (FILE *__stream);
# 266 "/usr/include/stdio.h" 3 4






extern FILE *fopen (const char *__restrict __filename,
      const char *__restrict __modes) ;




extern FILE *freopen (const char *__restrict __filename,
        const char *__restrict __modes,
        FILE *__restrict __stream) ;
# 295 "/usr/include/stdio.h" 3 4

# 306 "/usr/include/stdio.h" 3 4
extern FILE *fdopen (int __fd, const char *__modes) __attribute__ ((__nothrow__ , __leaf__)) ;
# 319 "/usr/include/stdio.h" 3 4
extern FILE *fmemopen (void *__s, size_t __len, const char *__modes)
  __attribute__ ((__nothrow__ , __leaf__)) ;




extern FILE *open_memstream (char **__bufloc, size_t *__sizeloc) __attribute__ ((__nothrow__ , __leaf__)) ;






extern void setbuf (FILE *__restrict __stream, char *__restrict __buf) __attribute__ ((__nothrow__ , __leaf__));



extern int setvbuf (FILE *__restrict __stream, char *__restrict __buf,
      int __modes, size_t __n) __attribute__ ((__nothrow__ , __leaf__));





extern void setbuffer (FILE *__restrict __stream, char *__restrict __buf,
         size_t __size) __attribute__ ((__nothrow__ , __leaf__));


extern void setlinebuf (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__));








extern int fprintf (FILE *__restrict __stream,
      const char *__restrict __format, ...);




extern int printf (const char *__restrict __format, ...);

extern int sprintf (char *__restrict __s,
      const char *__restrict __format, ...) __attribute__ ((__nothrow__));





extern int vfprintf (FILE *__restrict __s, const char *__restrict __format,
       __gnuc_va_list __arg);




extern int vprintf (const char *__restrict __format, __gnuc_va_list __arg);

extern int vsprintf (char *__restrict __s, const char *__restrict __format,
       __gnuc_va_list __arg) __attribute__ ((__nothrow__));





extern int snprintf (char *__restrict __s, size_t __maxlen,
       const char *__restrict __format, ...)
     __attribute__ ((__nothrow__)) __attribute__ ((__format__ (__printf__, 3, 4)));

extern int vsnprintf (char *__restrict __s, size_t __maxlen,
        const char *__restrict __format, __gnuc_va_list __arg)
     __attribute__ ((__nothrow__)) __attribute__ ((__format__ (__printf__, 3, 0)));

# 412 "/usr/include/stdio.h" 3 4
extern int vdprintf (int __fd, const char *__restrict __fmt,
       __gnuc_va_list __arg)
     __attribute__ ((__format__ (__printf__, 2, 0)));
extern int dprintf (int __fd, const char *__restrict __fmt, ...)
     __attribute__ ((__format__ (__printf__, 2, 3)));








extern int fscanf (FILE *__restrict __stream,
     const char *__restrict __format, ...) ;




extern int scanf (const char *__restrict __format, ...) ;

extern int sscanf (const char *__restrict __s,
     const char *__restrict __format, ...) __attribute__ ((__nothrow__ , __leaf__));
# 443 "/usr/include/stdio.h" 3 4
extern int fscanf (FILE *__restrict __stream, const char *__restrict __format, ...) __asm__ ("" "__isoc99_fscanf")

                               ;
extern int scanf (const char *__restrict __format, ...) __asm__ ("" "__isoc99_scanf")
                              ;
extern int sscanf (const char *__restrict __s, const char *__restrict __format, ...) __asm__ ("" "__isoc99_sscanf") __attribute__ ((__nothrow__ , __leaf__))

                      ;
# 463 "/usr/include/stdio.h" 3 4








extern int vfscanf (FILE *__restrict __s, const char *__restrict __format,
      __gnuc_va_list __arg)
     __attribute__ ((__format__ (__scanf__, 2, 0))) ;





extern int vscanf (const char *__restrict __format, __gnuc_va_list __arg)
     __attribute__ ((__format__ (__scanf__, 1, 0))) ;


extern int vsscanf (const char *__restrict __s,
      const char *__restrict __format, __gnuc_va_list __arg)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__format__ (__scanf__, 2, 0)));
# 494 "/usr/include/stdio.h" 3 4
extern int vfscanf (FILE *__restrict __s, const char *__restrict __format, __gnuc_va_list __arg) __asm__ ("" "__isoc99_vfscanf")



     __attribute__ ((__format__ (__scanf__, 2, 0))) ;
extern int vscanf (const char *__restrict __format, __gnuc_va_list __arg) __asm__ ("" "__isoc99_vscanf")

     __attribute__ ((__format__ (__scanf__, 1, 0))) ;
extern int vsscanf (const char *__restrict __s, const char *__restrict __format, __gnuc_va_list __arg) __asm__ ("" "__isoc99_vsscanf") __attribute__ ((__nothrow__ , __leaf__))



     __attribute__ ((__format__ (__scanf__, 2, 0)));
# 522 "/usr/include/stdio.h" 3 4









extern int fgetc (FILE *__stream);
extern int getc (FILE *__stream);





extern int getchar (void);

# 550 "/usr/include/stdio.h" 3 4
extern int getc_unlocked (FILE *__stream);
extern int getchar_unlocked (void);
# 561 "/usr/include/stdio.h" 3 4
extern int fgetc_unlocked (FILE *__stream);











extern int fputc (int __c, FILE *__stream);
extern int putc (int __c, FILE *__stream);





extern int putchar (int __c);

# 594 "/usr/include/stdio.h" 3 4
extern int fputc_unlocked (int __c, FILE *__stream);







extern int putc_unlocked (int __c, FILE *__stream);
extern int putchar_unlocked (int __c);






extern int getw (FILE *__stream);


extern int putw (int __w, FILE *__stream);








extern char *fgets (char *__restrict __s, int __n, FILE *__restrict __stream)
     ;
# 638 "/usr/include/stdio.h" 3 4
extern char *gets (char *__s) __attribute__ ((__deprecated__));


# 665 "/usr/include/stdio.h" 3 4
extern __ssize_t __getdelim (char **__restrict __lineptr,
          size_t *__restrict __n, int __delimiter,
          FILE *__restrict __stream) ;
extern __ssize_t getdelim (char **__restrict __lineptr,
        size_t *__restrict __n, int __delimiter,
        FILE *__restrict __stream) ;







extern __ssize_t getline (char **__restrict __lineptr,
       size_t *__restrict __n,
       FILE *__restrict __stream) ;








extern int fputs (const char *__restrict __s, FILE *__restrict __stream);





extern int puts (const char *__s);






extern int ungetc (int __c, FILE *__stream);






extern size_t fread (void *__restrict __ptr, size_t __size,
       size_t __n, FILE *__restrict __stream) ;




extern size_t fwrite (const void *__restrict __ptr, size_t __size,
        size_t __n, FILE *__restrict __s);

# 737 "/usr/include/stdio.h" 3 4
extern size_t fread_unlocked (void *__restrict __ptr, size_t __size,
         size_t __n, FILE *__restrict __stream) ;
extern size_t fwrite_unlocked (const void *__restrict __ptr, size_t __size,
          size_t __n, FILE *__restrict __stream);








extern int fseek (FILE *__stream, long int __off, int __whence);




extern long int ftell (FILE *__stream) ;




extern void rewind (FILE *__stream);

# 773 "/usr/include/stdio.h" 3 4
extern int fseeko (FILE *__stream, __off_t __off, int __whence);




extern __off_t ftello (FILE *__stream) ;
# 792 "/usr/include/stdio.h" 3 4






extern int fgetpos (FILE *__restrict __stream, fpos_t *__restrict __pos);




extern int fsetpos (FILE *__stream, const fpos_t *__pos);
# 815 "/usr/include/stdio.h" 3 4

# 824 "/usr/include/stdio.h" 3 4


extern void clearerr (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__));

extern int feof (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__)) ;

extern int ferror (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__)) ;




extern void clearerr_unlocked (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__));
extern int feof_unlocked (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__)) ;
extern int ferror_unlocked (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__)) ;








extern void perror (const char *__s);






# 1 "/usr/include/bits/sys_errlist.h" 1 3 4
# 26 "/usr/include/bits/sys_errlist.h" 3 4
extern int sys_nerr;
extern const char *const sys_errlist[];
# 854 "/usr/include/stdio.h" 2 3 4




extern int fileno (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__)) ;




extern int fileno_unlocked (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__)) ;
# 873 "/usr/include/stdio.h" 3 4
extern FILE *popen (const char *__command, const char *__modes) ;





extern int pclose (FILE *__stream);





extern char *ctermid (char *__s) __attribute__ ((__nothrow__ , __leaf__));
# 913 "/usr/include/stdio.h" 3 4
extern void flockfile (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__));



extern int ftrylockfile (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__)) ;


extern void funlockfile (FILE *__stream) __attribute__ ((__nothrow__ , __leaf__));
# 943 "/usr/include/stdio.h" 3 4

# 28 "brake2_2_por_seq.c" 2
# 1 "/usr/include/assert.h" 1 3 4
# 64 "/usr/include/assert.h" 3 4



extern void __assert_fail (const char *__assertion, const char *__file,
      unsigned int __line, const char *__function)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__noreturn__));


extern void __assert_perror_fail (int __errnum, const char *__file,
      unsigned int __line, const char *__function)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__noreturn__));




extern void __assert (const char *__assertion, const char *__file, int __line)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__noreturn__));



# 29 "brake2_2_por_seq.c" 2


# 1 "brake_acc_nodiv_ctrl.c" 1
# 18 "brake_acc_nodiv_ctrl.c"
# 1 "brake_acc_nodiv_ctrl.h" 1
# 22 "brake_acc_nodiv_ctrl.h"
# 1 "/usr/include/math.h" 1 3 4
# 28 "/usr/include/math.h" 3 4




# 1 "/usr/include/bits/huge_val.h" 1 3 4
# 33 "/usr/include/math.h" 2 3 4

# 1 "/usr/include/bits/huge_valf.h" 1 3 4
# 35 "/usr/include/math.h" 2 3 4
# 1 "/usr/include/bits/huge_vall.h" 1 3 4
# 36 "/usr/include/math.h" 2 3 4


# 1 "/usr/include/bits/inf.h" 1 3 4
# 39 "/usr/include/math.h" 2 3 4


# 1 "/usr/include/bits/nan.h" 1 3 4
# 42 "/usr/include/math.h" 2 3 4



# 1 "/usr/include/bits/mathdef.h" 1 3 4
# 28 "/usr/include/bits/mathdef.h" 3 4
typedef float float_t;
typedef double double_t;
# 46 "/usr/include/math.h" 2 3 4
# 69 "/usr/include/math.h" 3 4
# 1 "/usr/include/bits/mathcalls.h" 1 3 4
# 52 "/usr/include/bits/mathcalls.h" 3 4


extern double acos (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __acos (double __x) __attribute__ ((__nothrow__ , __leaf__));

extern double asin (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __asin (double __x) __attribute__ ((__nothrow__ , __leaf__));

extern double atan (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __atan (double __x) __attribute__ ((__nothrow__ , __leaf__));

extern double atan2 (double __y, double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __atan2 (double __y, double __x) __attribute__ ((__nothrow__ , __leaf__));


extern double cos (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __cos (double __x) __attribute__ ((__nothrow__ , __leaf__));

extern double sin (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __sin (double __x) __attribute__ ((__nothrow__ , __leaf__));

extern double tan (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __tan (double __x) __attribute__ ((__nothrow__ , __leaf__));




extern double cosh (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __cosh (double __x) __attribute__ ((__nothrow__ , __leaf__));

extern double sinh (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __sinh (double __x) __attribute__ ((__nothrow__ , __leaf__));

extern double tanh (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __tanh (double __x) __attribute__ ((__nothrow__ , __leaf__));

# 86 "/usr/include/bits/mathcalls.h" 3 4


extern double acosh (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __acosh (double __x) __attribute__ ((__nothrow__ , __leaf__));

extern double asinh (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __asinh (double __x) __attribute__ ((__nothrow__ , __leaf__));

extern double atanh (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __atanh (double __x) __attribute__ ((__nothrow__ , __leaf__));







extern double exp (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __exp (double __x) __attribute__ ((__nothrow__ , __leaf__));


extern double frexp (double __x, int *__exponent) __attribute__ ((__nothrow__ , __leaf__)); extern double __frexp (double __x, int *__exponent) __attribute__ ((__nothrow__ , __leaf__));


extern double ldexp (double __x, int __exponent) __attribute__ ((__nothrow__ , __leaf__)); extern double __ldexp (double __x, int __exponent) __attribute__ ((__nothrow__ , __leaf__));


extern double log (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __log (double __x) __attribute__ ((__nothrow__ , __leaf__));


extern double log10 (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __log10 (double __x) __attribute__ ((__nothrow__ , __leaf__));


extern double modf (double __x, double *__iptr) __attribute__ ((__nothrow__ , __leaf__)); extern double __modf (double __x, double *__iptr) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2)));

# 126 "/usr/include/bits/mathcalls.h" 3 4


extern double expm1 (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __expm1 (double __x) __attribute__ ((__nothrow__ , __leaf__));


extern double log1p (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __log1p (double __x) __attribute__ ((__nothrow__ , __leaf__));


extern double logb (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __logb (double __x) __attribute__ ((__nothrow__ , __leaf__));






extern double exp2 (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __exp2 (double __x) __attribute__ ((__nothrow__ , __leaf__));


extern double log2 (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __log2 (double __x) __attribute__ ((__nothrow__ , __leaf__));








extern double pow (double __x, double __y) __attribute__ ((__nothrow__ , __leaf__)); extern double __pow (double __x, double __y) __attribute__ ((__nothrow__ , __leaf__));


extern double sqrt (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __sqrt (double __x) __attribute__ ((__nothrow__ , __leaf__));





extern double hypot (double __x, double __y) __attribute__ ((__nothrow__ , __leaf__)); extern double __hypot (double __x, double __y) __attribute__ ((__nothrow__ , __leaf__));






extern double cbrt (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __cbrt (double __x) __attribute__ ((__nothrow__ , __leaf__));








extern double ceil (double __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern double __ceil (double __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


extern double fabs (double __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern double __fabs (double __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


extern double floor (double __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern double __floor (double __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


extern double fmod (double __x, double __y) __attribute__ ((__nothrow__ , __leaf__)); extern double __fmod (double __x, double __y) __attribute__ ((__nothrow__ , __leaf__));




extern int __isinf (double __value) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


extern int __finite (double __value) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));





extern int isinf (double __value) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


extern int finite (double __value) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


extern double drem (double __x, double __y) __attribute__ ((__nothrow__ , __leaf__)); extern double __drem (double __x, double __y) __attribute__ ((__nothrow__ , __leaf__));



extern double significand (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __significand (double __x) __attribute__ ((__nothrow__ , __leaf__));





extern double copysign (double __x, double __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern double __copysign (double __x, double __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));






extern double nan (const char *__tagb) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern double __nan (const char *__tagb) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));





extern int __isnan (double __value) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));



extern int isnan (double __value) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


extern double j0 (double) __attribute__ ((__nothrow__ , __leaf__)); extern double __j0 (double) __attribute__ ((__nothrow__ , __leaf__));
extern double j1 (double) __attribute__ ((__nothrow__ , __leaf__)); extern double __j1 (double) __attribute__ ((__nothrow__ , __leaf__));
extern double jn (int, double) __attribute__ ((__nothrow__ , __leaf__)); extern double __jn (int, double) __attribute__ ((__nothrow__ , __leaf__));
extern double y0 (double) __attribute__ ((__nothrow__ , __leaf__)); extern double __y0 (double) __attribute__ ((__nothrow__ , __leaf__));
extern double y1 (double) __attribute__ ((__nothrow__ , __leaf__)); extern double __y1 (double) __attribute__ ((__nothrow__ , __leaf__));
extern double yn (int, double) __attribute__ ((__nothrow__ , __leaf__)); extern double __yn (int, double) __attribute__ ((__nothrow__ , __leaf__));






extern double erf (double) __attribute__ ((__nothrow__ , __leaf__)); extern double __erf (double) __attribute__ ((__nothrow__ , __leaf__));
extern double erfc (double) __attribute__ ((__nothrow__ , __leaf__)); extern double __erfc (double) __attribute__ ((__nothrow__ , __leaf__));
extern double lgamma (double) __attribute__ ((__nothrow__ , __leaf__)); extern double __lgamma (double) __attribute__ ((__nothrow__ , __leaf__));






extern double tgamma (double) __attribute__ ((__nothrow__ , __leaf__)); extern double __tgamma (double) __attribute__ ((__nothrow__ , __leaf__));





extern double gamma (double) __attribute__ ((__nothrow__ , __leaf__)); extern double __gamma (double) __attribute__ ((__nothrow__ , __leaf__));






extern double lgamma_r (double, int *__signgamp) __attribute__ ((__nothrow__ , __leaf__)); extern double __lgamma_r (double, int *__signgamp) __attribute__ ((__nothrow__ , __leaf__));







extern double rint (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __rint (double __x) __attribute__ ((__nothrow__ , __leaf__));


extern double nextafter (double __x, double __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern double __nextafter (double __x, double __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));

extern double nexttoward (double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern double __nexttoward (double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));



extern double remainder (double __x, double __y) __attribute__ ((__nothrow__ , __leaf__)); extern double __remainder (double __x, double __y) __attribute__ ((__nothrow__ , __leaf__));



extern double scalbn (double __x, int __n) __attribute__ ((__nothrow__ , __leaf__)); extern double __scalbn (double __x, int __n) __attribute__ ((__nothrow__ , __leaf__));



extern int ilogb (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern int __ilogb (double __x) __attribute__ ((__nothrow__ , __leaf__));




extern double scalbln (double __x, long int __n) __attribute__ ((__nothrow__ , __leaf__)); extern double __scalbln (double __x, long int __n) __attribute__ ((__nothrow__ , __leaf__));



extern double nearbyint (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern double __nearbyint (double __x) __attribute__ ((__nothrow__ , __leaf__));



extern double round (double __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern double __round (double __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));



extern double trunc (double __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern double __trunc (double __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));




extern double remquo (double __x, double __y, int *__quo) __attribute__ ((__nothrow__ , __leaf__)); extern double __remquo (double __x, double __y, int *__quo) __attribute__ ((__nothrow__ , __leaf__));






extern long int lrint (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long int __lrint (double __x) __attribute__ ((__nothrow__ , __leaf__));
__extension__
extern long long int llrint (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long long int __llrint (double __x) __attribute__ ((__nothrow__ , __leaf__));



extern long int lround (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long int __lround (double __x) __attribute__ ((__nothrow__ , __leaf__));
__extension__
extern long long int llround (double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long long int __llround (double __x) __attribute__ ((__nothrow__ , __leaf__));



extern double fdim (double __x, double __y) __attribute__ ((__nothrow__ , __leaf__)); extern double __fdim (double __x, double __y) __attribute__ ((__nothrow__ , __leaf__));


extern double fmax (double __x, double __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern double __fmax (double __x, double __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


extern double fmin (double __x, double __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern double __fmin (double __x, double __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));



extern int __fpclassify (double __value) __attribute__ ((__nothrow__ , __leaf__))
     __attribute__ ((__const__));


extern int __signbit (double __value) __attribute__ ((__nothrow__ , __leaf__))
     __attribute__ ((__const__));



extern double fma (double __x, double __y, double __z) __attribute__ ((__nothrow__ , __leaf__)); extern double __fma (double __x, double __y, double __z) __attribute__ ((__nothrow__ , __leaf__));




# 371 "/usr/include/bits/mathcalls.h" 3 4
extern double scalb (double __x, double __n) __attribute__ ((__nothrow__ , __leaf__)); extern double __scalb (double __x, double __n) __attribute__ ((__nothrow__ , __leaf__));
# 70 "/usr/include/math.h" 2 3 4
# 88 "/usr/include/math.h" 3 4
# 1 "/usr/include/bits/mathcalls.h" 1 3 4
# 52 "/usr/include/bits/mathcalls.h" 3 4


extern float acosf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __acosf (float __x) __attribute__ ((__nothrow__ , __leaf__));

extern float asinf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __asinf (float __x) __attribute__ ((__nothrow__ , __leaf__));

extern float atanf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __atanf (float __x) __attribute__ ((__nothrow__ , __leaf__));

extern float atan2f (float __y, float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __atan2f (float __y, float __x) __attribute__ ((__nothrow__ , __leaf__));


extern float cosf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __cosf (float __x) __attribute__ ((__nothrow__ , __leaf__));

extern float sinf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __sinf (float __x) __attribute__ ((__nothrow__ , __leaf__));

extern float tanf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __tanf (float __x) __attribute__ ((__nothrow__ , __leaf__));




extern float coshf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __coshf (float __x) __attribute__ ((__nothrow__ , __leaf__));

extern float sinhf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __sinhf (float __x) __attribute__ ((__nothrow__ , __leaf__));

extern float tanhf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __tanhf (float __x) __attribute__ ((__nothrow__ , __leaf__));

# 86 "/usr/include/bits/mathcalls.h" 3 4


extern float acoshf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __acoshf (float __x) __attribute__ ((__nothrow__ , __leaf__));

extern float asinhf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __asinhf (float __x) __attribute__ ((__nothrow__ , __leaf__));

extern float atanhf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __atanhf (float __x) __attribute__ ((__nothrow__ , __leaf__));







extern float expf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __expf (float __x) __attribute__ ((__nothrow__ , __leaf__));


extern float frexpf (float __x, int *__exponent) __attribute__ ((__nothrow__ , __leaf__)); extern float __frexpf (float __x, int *__exponent) __attribute__ ((__nothrow__ , __leaf__));


extern float ldexpf (float __x, int __exponent) __attribute__ ((__nothrow__ , __leaf__)); extern float __ldexpf (float __x, int __exponent) __attribute__ ((__nothrow__ , __leaf__));


extern float logf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __logf (float __x) __attribute__ ((__nothrow__ , __leaf__));


extern float log10f (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __log10f (float __x) __attribute__ ((__nothrow__ , __leaf__));


extern float modff (float __x, float *__iptr) __attribute__ ((__nothrow__ , __leaf__)); extern float __modff (float __x, float *__iptr) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2)));

# 126 "/usr/include/bits/mathcalls.h" 3 4


extern float expm1f (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __expm1f (float __x) __attribute__ ((__nothrow__ , __leaf__));


extern float log1pf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __log1pf (float __x) __attribute__ ((__nothrow__ , __leaf__));


extern float logbf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __logbf (float __x) __attribute__ ((__nothrow__ , __leaf__));






extern float exp2f (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __exp2f (float __x) __attribute__ ((__nothrow__ , __leaf__));


extern float log2f (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __log2f (float __x) __attribute__ ((__nothrow__ , __leaf__));








extern float powf (float __x, float __y) __attribute__ ((__nothrow__ , __leaf__)); extern float __powf (float __x, float __y) __attribute__ ((__nothrow__ , __leaf__));


extern float sqrtf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __sqrtf (float __x) __attribute__ ((__nothrow__ , __leaf__));





extern float hypotf (float __x, float __y) __attribute__ ((__nothrow__ , __leaf__)); extern float __hypotf (float __x, float __y) __attribute__ ((__nothrow__ , __leaf__));






extern float cbrtf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __cbrtf (float __x) __attribute__ ((__nothrow__ , __leaf__));








extern float ceilf (float __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern float __ceilf (float __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


extern float fabsf (float __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern float __fabsf (float __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


extern float floorf (float __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern float __floorf (float __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


extern float fmodf (float __x, float __y) __attribute__ ((__nothrow__ , __leaf__)); extern float __fmodf (float __x, float __y) __attribute__ ((__nothrow__ , __leaf__));




extern int __isinff (float __value) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


extern int __finitef (float __value) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));





extern int isinff (float __value) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


extern int finitef (float __value) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


extern float dremf (float __x, float __y) __attribute__ ((__nothrow__ , __leaf__)); extern float __dremf (float __x, float __y) __attribute__ ((__nothrow__ , __leaf__));



extern float significandf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __significandf (float __x) __attribute__ ((__nothrow__ , __leaf__));





extern float copysignf (float __x, float __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern float __copysignf (float __x, float __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));






extern float nanf (const char *__tagb) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern float __nanf (const char *__tagb) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));





extern int __isnanf (float __value) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));



extern int isnanf (float __value) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


extern float j0f (float) __attribute__ ((__nothrow__ , __leaf__)); extern float __j0f (float) __attribute__ ((__nothrow__ , __leaf__));
extern float j1f (float) __attribute__ ((__nothrow__ , __leaf__)); extern float __j1f (float) __attribute__ ((__nothrow__ , __leaf__));
extern float jnf (int, float) __attribute__ ((__nothrow__ , __leaf__)); extern float __jnf (int, float) __attribute__ ((__nothrow__ , __leaf__));
extern float y0f (float) __attribute__ ((__nothrow__ , __leaf__)); extern float __y0f (float) __attribute__ ((__nothrow__ , __leaf__));
extern float y1f (float) __attribute__ ((__nothrow__ , __leaf__)); extern float __y1f (float) __attribute__ ((__nothrow__ , __leaf__));
extern float ynf (int, float) __attribute__ ((__nothrow__ , __leaf__)); extern float __ynf (int, float) __attribute__ ((__nothrow__ , __leaf__));






extern float erff (float) __attribute__ ((__nothrow__ , __leaf__)); extern float __erff (float) __attribute__ ((__nothrow__ , __leaf__));
extern float erfcf (float) __attribute__ ((__nothrow__ , __leaf__)); extern float __erfcf (float) __attribute__ ((__nothrow__ , __leaf__));
extern float lgammaf (float) __attribute__ ((__nothrow__ , __leaf__)); extern float __lgammaf (float) __attribute__ ((__nothrow__ , __leaf__));






extern float tgammaf (float) __attribute__ ((__nothrow__ , __leaf__)); extern float __tgammaf (float) __attribute__ ((__nothrow__ , __leaf__));





extern float gammaf (float) __attribute__ ((__nothrow__ , __leaf__)); extern float __gammaf (float) __attribute__ ((__nothrow__ , __leaf__));






extern float lgammaf_r (float, int *__signgamp) __attribute__ ((__nothrow__ , __leaf__)); extern float __lgammaf_r (float, int *__signgamp) __attribute__ ((__nothrow__ , __leaf__));







extern float rintf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __rintf (float __x) __attribute__ ((__nothrow__ , __leaf__));


extern float nextafterf (float __x, float __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern float __nextafterf (float __x, float __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));

extern float nexttowardf (float __x, long double __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern float __nexttowardf (float __x, long double __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));



extern float remainderf (float __x, float __y) __attribute__ ((__nothrow__ , __leaf__)); extern float __remainderf (float __x, float __y) __attribute__ ((__nothrow__ , __leaf__));



extern float scalbnf (float __x, int __n) __attribute__ ((__nothrow__ , __leaf__)); extern float __scalbnf (float __x, int __n) __attribute__ ((__nothrow__ , __leaf__));



extern int ilogbf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern int __ilogbf (float __x) __attribute__ ((__nothrow__ , __leaf__));




extern float scalblnf (float __x, long int __n) __attribute__ ((__nothrow__ , __leaf__)); extern float __scalblnf (float __x, long int __n) __attribute__ ((__nothrow__ , __leaf__));



extern float nearbyintf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern float __nearbyintf (float __x) __attribute__ ((__nothrow__ , __leaf__));



extern float roundf (float __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern float __roundf (float __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));



extern float truncf (float __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern float __truncf (float __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));




extern float remquof (float __x, float __y, int *__quo) __attribute__ ((__nothrow__ , __leaf__)); extern float __remquof (float __x, float __y, int *__quo) __attribute__ ((__nothrow__ , __leaf__));






extern long int lrintf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern long int __lrintf (float __x) __attribute__ ((__nothrow__ , __leaf__));
__extension__
extern long long int llrintf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern long long int __llrintf (float __x) __attribute__ ((__nothrow__ , __leaf__));



extern long int lroundf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern long int __lroundf (float __x) __attribute__ ((__nothrow__ , __leaf__));
__extension__
extern long long int llroundf (float __x) __attribute__ ((__nothrow__ , __leaf__)); extern long long int __llroundf (float __x) __attribute__ ((__nothrow__ , __leaf__));



extern float fdimf (float __x, float __y) __attribute__ ((__nothrow__ , __leaf__)); extern float __fdimf (float __x, float __y) __attribute__ ((__nothrow__ , __leaf__));


extern float fmaxf (float __x, float __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern float __fmaxf (float __x, float __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


extern float fminf (float __x, float __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern float __fminf (float __x, float __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));



extern int __fpclassifyf (float __value) __attribute__ ((__nothrow__ , __leaf__))
     __attribute__ ((__const__));


extern int __signbitf (float __value) __attribute__ ((__nothrow__ , __leaf__))
     __attribute__ ((__const__));



extern float fmaf (float __x, float __y, float __z) __attribute__ ((__nothrow__ , __leaf__)); extern float __fmaf (float __x, float __y, float __z) __attribute__ ((__nothrow__ , __leaf__));




# 371 "/usr/include/bits/mathcalls.h" 3 4
extern float scalbf (float __x, float __n) __attribute__ ((__nothrow__ , __leaf__)); extern float __scalbf (float __x, float __n) __attribute__ ((__nothrow__ , __leaf__));
# 89 "/usr/include/math.h" 2 3 4
# 132 "/usr/include/math.h" 3 4
# 1 "/usr/include/bits/mathcalls.h" 1 3 4
# 52 "/usr/include/bits/mathcalls.h" 3 4


extern long double acosl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __acosl (long double __x) __attribute__ ((__nothrow__ , __leaf__));

extern long double asinl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __asinl (long double __x) __attribute__ ((__nothrow__ , __leaf__));

extern long double atanl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __atanl (long double __x) __attribute__ ((__nothrow__ , __leaf__));

extern long double atan2l (long double __y, long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __atan2l (long double __y, long double __x) __attribute__ ((__nothrow__ , __leaf__));


extern long double cosl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __cosl (long double __x) __attribute__ ((__nothrow__ , __leaf__));

extern long double sinl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __sinl (long double __x) __attribute__ ((__nothrow__ , __leaf__));

extern long double tanl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __tanl (long double __x) __attribute__ ((__nothrow__ , __leaf__));




extern long double coshl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __coshl (long double __x) __attribute__ ((__nothrow__ , __leaf__));

extern long double sinhl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __sinhl (long double __x) __attribute__ ((__nothrow__ , __leaf__));

extern long double tanhl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __tanhl (long double __x) __attribute__ ((__nothrow__ , __leaf__));

# 86 "/usr/include/bits/mathcalls.h" 3 4


extern long double acoshl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __acoshl (long double __x) __attribute__ ((__nothrow__ , __leaf__));

extern long double asinhl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __asinhl (long double __x) __attribute__ ((__nothrow__ , __leaf__));

extern long double atanhl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __atanhl (long double __x) __attribute__ ((__nothrow__ , __leaf__));







extern long double expl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __expl (long double __x) __attribute__ ((__nothrow__ , __leaf__));


extern long double frexpl (long double __x, int *__exponent) __attribute__ ((__nothrow__ , __leaf__)); extern long double __frexpl (long double __x, int *__exponent) __attribute__ ((__nothrow__ , __leaf__));


extern long double ldexpl (long double __x, int __exponent) __attribute__ ((__nothrow__ , __leaf__)); extern long double __ldexpl (long double __x, int __exponent) __attribute__ ((__nothrow__ , __leaf__));


extern long double logl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __logl (long double __x) __attribute__ ((__nothrow__ , __leaf__));


extern long double log10l (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __log10l (long double __x) __attribute__ ((__nothrow__ , __leaf__));


extern long double modfl (long double __x, long double *__iptr) __attribute__ ((__nothrow__ , __leaf__)); extern long double __modfl (long double __x, long double *__iptr) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2)));

# 126 "/usr/include/bits/mathcalls.h" 3 4


extern long double expm1l (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __expm1l (long double __x) __attribute__ ((__nothrow__ , __leaf__));


extern long double log1pl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __log1pl (long double __x) __attribute__ ((__nothrow__ , __leaf__));


extern long double logbl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __logbl (long double __x) __attribute__ ((__nothrow__ , __leaf__));






extern long double exp2l (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __exp2l (long double __x) __attribute__ ((__nothrow__ , __leaf__));


extern long double log2l (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __log2l (long double __x) __attribute__ ((__nothrow__ , __leaf__));








extern long double powl (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__)); extern long double __powl (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__));


extern long double sqrtl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __sqrtl (long double __x) __attribute__ ((__nothrow__ , __leaf__));





extern long double hypotl (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__)); extern long double __hypotl (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__));






extern long double cbrtl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __cbrtl (long double __x) __attribute__ ((__nothrow__ , __leaf__));








extern long double ceill (long double __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern long double __ceill (long double __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


extern long double fabsl (long double __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern long double __fabsl (long double __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


extern long double floorl (long double __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern long double __floorl (long double __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


extern long double fmodl (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__)); extern long double __fmodl (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__));




extern int __isinfl (long double __value) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


extern int __finitel (long double __value) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));





extern int isinfl (long double __value) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


extern int finitel (long double __value) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


extern long double dreml (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__)); extern long double __dreml (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__));



extern long double significandl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __significandl (long double __x) __attribute__ ((__nothrow__ , __leaf__));





extern long double copysignl (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern long double __copysignl (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));






extern long double nanl (const char *__tagb) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern long double __nanl (const char *__tagb) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));





extern int __isnanl (long double __value) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));



extern int isnanl (long double __value) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


extern long double j0l (long double) __attribute__ ((__nothrow__ , __leaf__)); extern long double __j0l (long double) __attribute__ ((__nothrow__ , __leaf__));
extern long double j1l (long double) __attribute__ ((__nothrow__ , __leaf__)); extern long double __j1l (long double) __attribute__ ((__nothrow__ , __leaf__));
extern long double jnl (int, long double) __attribute__ ((__nothrow__ , __leaf__)); extern long double __jnl (int, long double) __attribute__ ((__nothrow__ , __leaf__));
extern long double y0l (long double) __attribute__ ((__nothrow__ , __leaf__)); extern long double __y0l (long double) __attribute__ ((__nothrow__ , __leaf__));
extern long double y1l (long double) __attribute__ ((__nothrow__ , __leaf__)); extern long double __y1l (long double) __attribute__ ((__nothrow__ , __leaf__));
extern long double ynl (int, long double) __attribute__ ((__nothrow__ , __leaf__)); extern long double __ynl (int, long double) __attribute__ ((__nothrow__ , __leaf__));






extern long double erfl (long double) __attribute__ ((__nothrow__ , __leaf__)); extern long double __erfl (long double) __attribute__ ((__nothrow__ , __leaf__));
extern long double erfcl (long double) __attribute__ ((__nothrow__ , __leaf__)); extern long double __erfcl (long double) __attribute__ ((__nothrow__ , __leaf__));
extern long double lgammal (long double) __attribute__ ((__nothrow__ , __leaf__)); extern long double __lgammal (long double) __attribute__ ((__nothrow__ , __leaf__));






extern long double tgammal (long double) __attribute__ ((__nothrow__ , __leaf__)); extern long double __tgammal (long double) __attribute__ ((__nothrow__ , __leaf__));





extern long double gammal (long double) __attribute__ ((__nothrow__ , __leaf__)); extern long double __gammal (long double) __attribute__ ((__nothrow__ , __leaf__));






extern long double lgammal_r (long double, int *__signgamp) __attribute__ ((__nothrow__ , __leaf__)); extern long double __lgammal_r (long double, int *__signgamp) __attribute__ ((__nothrow__ , __leaf__));







extern long double rintl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __rintl (long double __x) __attribute__ ((__nothrow__ , __leaf__));


extern long double nextafterl (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern long double __nextafterl (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));

extern long double nexttowardl (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern long double __nexttowardl (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));



extern long double remainderl (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__)); extern long double __remainderl (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__));



extern long double scalbnl (long double __x, int __n) __attribute__ ((__nothrow__ , __leaf__)); extern long double __scalbnl (long double __x, int __n) __attribute__ ((__nothrow__ , __leaf__));



extern int ilogbl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern int __ilogbl (long double __x) __attribute__ ((__nothrow__ , __leaf__));




extern long double scalblnl (long double __x, long int __n) __attribute__ ((__nothrow__ , __leaf__)); extern long double __scalblnl (long double __x, long int __n) __attribute__ ((__nothrow__ , __leaf__));



extern long double nearbyintl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long double __nearbyintl (long double __x) __attribute__ ((__nothrow__ , __leaf__));



extern long double roundl (long double __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern long double __roundl (long double __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));



extern long double truncl (long double __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern long double __truncl (long double __x) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));




extern long double remquol (long double __x, long double __y, int *__quo) __attribute__ ((__nothrow__ , __leaf__)); extern long double __remquol (long double __x, long double __y, int *__quo) __attribute__ ((__nothrow__ , __leaf__));






extern long int lrintl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long int __lrintl (long double __x) __attribute__ ((__nothrow__ , __leaf__));
__extension__
extern long long int llrintl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long long int __llrintl (long double __x) __attribute__ ((__nothrow__ , __leaf__));



extern long int lroundl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long int __lroundl (long double __x) __attribute__ ((__nothrow__ , __leaf__));
__extension__
extern long long int llroundl (long double __x) __attribute__ ((__nothrow__ , __leaf__)); extern long long int __llroundl (long double __x) __attribute__ ((__nothrow__ , __leaf__));



extern long double fdiml (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__)); extern long double __fdiml (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__));


extern long double fmaxl (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern long double __fmaxl (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));


extern long double fminl (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__)); extern long double __fminl (long double __x, long double __y) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));



extern int __fpclassifyl (long double __value) __attribute__ ((__nothrow__ , __leaf__))
     __attribute__ ((__const__));


extern int __signbitl (long double __value) __attribute__ ((__nothrow__ , __leaf__))
     __attribute__ ((__const__));



extern long double fmal (long double __x, long double __y, long double __z) __attribute__ ((__nothrow__ , __leaf__)); extern long double __fmal (long double __x, long double __y, long double __z) __attribute__ ((__nothrow__ , __leaf__));




# 371 "/usr/include/bits/mathcalls.h" 3 4
extern long double scalbl (long double __x, long double __n) __attribute__ ((__nothrow__ , __leaf__)); extern long double __scalbl (long double __x, long double __n) __attribute__ ((__nothrow__ , __leaf__));
# 133 "/usr/include/math.h" 2 3 4
# 148 "/usr/include/math.h" 3 4
extern int signgam;
# 189 "/usr/include/math.h" 3 4
enum
  {
    FP_NAN =

      0,
    FP_INFINITE =

      1,
    FP_ZERO =

      2,
    FP_SUBNORMAL =

      3,
    FP_NORMAL =

      4
  };
# 301 "/usr/include/math.h" 3 4
typedef enum
{
  _IEEE_ = -1,
  _SVID_,
  _XOPEN_,
  _POSIX_,
  _ISOC_
} _LIB_VERSION_TYPE;




extern _LIB_VERSION_TYPE _LIB_VERSION;
# 326 "/usr/include/math.h" 3 4
struct exception

  {
    int type;
    char *name;
    double arg1;
    double arg2;
    double retval;
  };




extern int matherr (struct exception *__exc);
# 488 "/usr/include/math.h" 3 4

# 23 "brake_acc_nodiv_ctrl.h" 2
# 1 "/usr/lib/gcc/x86_64-redhat-linux/4.8.3/include/float.h" 1 3 4
# 24 "brake_acc_nodiv_ctrl.h" 2
# 1 "/usr/lib/gcc/x86_64-redhat-linux/4.8.3/include/stddef.h" 1 3 4
# 147 "/usr/lib/gcc/x86_64-redhat-linux/4.8.3/include/stddef.h" 3 4
typedef long int ptrdiff_t;
# 324 "/usr/lib/gcc/x86_64-redhat-linux/4.8.3/include/stddef.h" 3 4
typedef int wchar_t;
# 25 "brake_acc_nodiv_ctrl.h" 2
# 1 "/usr/include/string.h" 1 3 4
# 27 "/usr/include/string.h" 3 4





# 1 "/usr/lib/gcc/x86_64-redhat-linux/4.8.3/include/stddef.h" 1 3 4
# 33 "/usr/include/string.h" 2 3 4









extern void *memcpy (void *__restrict __dest, const void *__restrict __src,
       size_t __n) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));


extern void *memmove (void *__dest, const void *__src, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));






extern void *memccpy (void *__restrict __dest, const void *__restrict __src,
        int __c, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));





extern void *memset (void *__s, int __c, size_t __n) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern int memcmp (const void *__s1, const void *__s2, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));
# 92 "/usr/include/string.h" 3 4
extern void *memchr (const void *__s, int __c, size_t __n)
      __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));


# 123 "/usr/include/string.h" 3 4


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
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2)));






# 1 "/usr/include/xlocale.h" 1 3 4
# 27 "/usr/include/xlocale.h" 3 4
typedef struct __locale_struct
{

  struct __locale_data *__locales[13];


  const unsigned short int *__ctype_b;
  const int *__ctype_tolower;
  const int *__ctype_toupper;


  const char *__names[13];
} *__locale_t;


typedef __locale_t locale_t;
# 160 "/usr/include/string.h" 2 3 4


extern int strcoll_l (const char *__s1, const char *__s2, __locale_t __l)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2, 3)));

extern size_t strxfrm_l (char *__dest, const char *__src, size_t __n,
    __locale_t __l) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (2, 4)));





extern char *strdup (const char *__s)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__malloc__)) __attribute__ ((__nonnull__ (1)));






extern char *strndup (const char *__string, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__malloc__)) __attribute__ ((__nonnull__ (1)));
# 207 "/usr/include/string.h" 3 4

# 232 "/usr/include/string.h" 3 4
extern char *strchr (const char *__s, int __c)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));
# 259 "/usr/include/string.h" 3 4
extern char *strrchr (const char *__s, int __c)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));


# 278 "/usr/include/string.h" 3 4



extern size_t strcspn (const char *__s, const char *__reject)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));


extern size_t strspn (const char *__s, const char *__accept)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));
# 311 "/usr/include/string.h" 3 4
extern char *strpbrk (const char *__s, const char *__accept)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));
# 338 "/usr/include/string.h" 3 4
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
# 393 "/usr/include/string.h" 3 4


extern size_t strlen (const char *__s)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));





extern size_t strnlen (const char *__string, size_t __maxlen)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));





extern char *strerror (int __errnum) __attribute__ ((__nothrow__ , __leaf__));

# 423 "/usr/include/string.h" 3 4
extern int strerror_r (int __errnum, char *__buf, size_t __buflen) __asm__ ("" "__xpg_strerror_r") __attribute__ ((__nothrow__ , __leaf__))

                        __attribute__ ((__nonnull__ (2)));
# 441 "/usr/include/string.h" 3 4
extern char *strerror_l (int __errnum, __locale_t __l) __attribute__ ((__nothrow__ , __leaf__));





extern void __bzero (void *__s, size_t __n) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));



extern void bcopy (const void *__src, void *__dest, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1, 2)));


extern void bzero (void *__s, size_t __n) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__nonnull__ (1)));


extern int bcmp (const void *__s1, const void *__s2, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));
# 485 "/usr/include/string.h" 3 4
extern char *index (const char *__s, int __c)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));
# 513 "/usr/include/string.h" 3 4
extern char *rindex (const char *__s, int __c)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1)));




extern int ffs (int __i) __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__const__));
# 530 "/usr/include/string.h" 3 4
extern int strcasecmp (const char *__s1, const char *__s2)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));


extern int strncasecmp (const char *__s1, const char *__s2, size_t __n)
     __attribute__ ((__nothrow__ , __leaf__)) __attribute__ ((__pure__)) __attribute__ ((__nonnull__ (1, 2)));
# 553 "/usr/include/string.h" 3 4
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
# 640 "/usr/include/string.h" 3 4

# 26 "brake_acc_nodiv_ctrl.h" 2
# 1 "rtwtypes.h" 1
# 21 "rtwtypes.h"
# 1 "tmwtypes.h" 1
# 12 "tmwtypes.h"
        
# 43 "tmwtypes.h"
# 1 "/usr/lib/gcc/x86_64-redhat-linux/4.8.3/include/limits.h" 1 3 4
# 34 "/usr/lib/gcc/x86_64-redhat-linux/4.8.3/include/limits.h" 3 4
# 1 "/usr/lib/gcc/x86_64-redhat-linux/4.8.3/include/syslimits.h" 1 3 4






# 1 "/usr/lib/gcc/x86_64-redhat-linux/4.8.3/include/limits.h" 1 3 4
# 168 "/usr/lib/gcc/x86_64-redhat-linux/4.8.3/include/limits.h" 3 4
# 1 "/usr/include/limits.h" 1 3 4
# 143 "/usr/include/limits.h" 3 4
# 1 "/usr/include/bits/posix1_lim.h" 1 3 4
# 160 "/usr/include/bits/posix1_lim.h" 3 4
# 1 "/usr/include/bits/local_lim.h" 1 3 4
# 38 "/usr/include/bits/local_lim.h" 3 4
# 1 "/usr/include/linux/limits.h" 1 3 4
# 39 "/usr/include/bits/local_lim.h" 2 3 4
# 161 "/usr/include/bits/posix1_lim.h" 2 3 4
# 144 "/usr/include/limits.h" 2 3 4



# 1 "/usr/include/bits/posix2_lim.h" 1 3 4
# 148 "/usr/include/limits.h" 2 3 4
# 169 "/usr/lib/gcc/x86_64-redhat-linux/4.8.3/include/limits.h" 2 3 4
# 8 "/usr/lib/gcc/x86_64-redhat-linux/4.8.3/include/syslimits.h" 2 3 4
# 35 "/usr/lib/gcc/x86_64-redhat-linux/4.8.3/include/limits.h" 2 3 4
# 44 "tmwtypes.h" 2
# 86 "tmwtypes.h"
typedef unsigned char uchar_T;
typedef unsigned short ushort_T;
typedef unsigned long ulong_T;





typedef unsigned long long ulonglong_T;
# 217 "tmwtypes.h"
 typedef signed char int8_T;
# 232 "tmwtypes.h"
 typedef unsigned char uint8_T;
# 248 "tmwtypes.h"
 typedef short int16_T;
# 264 "tmwtypes.h"
 typedef unsigned short uint16_T;
# 280 "tmwtypes.h"
 typedef int int32_T;
# 296 "tmwtypes.h"
 typedef unsigned int uint32_T;
# 357 "tmwtypes.h"
 typedef float real32_T;
# 371 "tmwtypes.h"
 typedef double real64_T;
# 413 "tmwtypes.h"
  __extension__

 typedef long int64_T;
# 453 "tmwtypes.h"
  __extension__

 typedef unsigned long uint64_T;
# 513 "tmwtypes.h"
 typedef float real_T;
# 522 "tmwtypes.h"
 typedef real_T time_T;
# 534 "tmwtypes.h"
typedef unsigned char boolean_T;





typedef char char_T;





typedef int int_T;





typedef unsigned uint_T;





typedef unsigned char byte_T;
# 568 "tmwtypes.h"
    typedef struct {
      real32_T re, im;
    } creal32_T;






    typedef struct {
      real64_T re, im;
    } creal64_T;






    typedef struct {
      real_T re, im;
    } creal_T;
# 597 "tmwtypes.h"
    typedef struct {
      int8_T re, im;
    } cint8_T;






    typedef struct {
      uint8_T re, im;
    } cuint8_T;






    typedef struct {
      int16_T re, im;
    } cint16_T;






    typedef struct {
      uint16_T re, im;
    } cuint16_T;






    typedef struct {
      int32_T re, im;
    } cint32_T;






    typedef struct {
      uint32_T re, im;
    } cuint32_T;






    typedef struct {
      int64_T re, im;
    } cint64_T;






    typedef struct {
      uint64_T re, im;
    } cuint64_T;
# 773 "tmwtypes.h"
typedef boolean_T bool;
# 803 "tmwtypes.h"
# 1 "/usr/lib/gcc/x86_64-redhat-linux/4.8.3/include/stddef.h" 1 3 4
# 804 "tmwtypes.h" 2






typedef size_t mwSize;
typedef size_t mwIndex;
typedef ptrdiff_t mwSignedIndex;
# 837 "tmwtypes.h"
typedef unsigned short CHAR16_T;
# 22 "rtwtypes.h" 2




typedef void * pointer_T;
# 27 "brake_acc_nodiv_ctrl.h" 2
# 1 "builtin_typeid_types.h" 1
# 26 "builtin_typeid_types.h"
typedef enum {
  SS_DOUBLE = 0,
  SS_SINGLE = 1,
  SS_INT8 = 2,
  SS_UINT8 = 3,
  SS_INT16 = 4,
  SS_UINT16 = 5,
  SS_INT32 = 6,
  SS_UINT32 = 7,
  SS_BOOLEAN = 8
} BuiltInDTypeId;




typedef int_T DTypeId;
# 28 "brake_acc_nodiv_ctrl.h" 2
# 1 "multiword_types.h" 1
# 26 "multiword_types.h"
typedef int64_T chunk_T;
typedef uint64_T uchunk_T;




typedef long long longlong_T;




typedef struct {
  uint64_T chunks[2];
} int128m_T;

typedef struct {
  int128m_T re;
  int128m_T im;
} cint128m_T;

typedef struct {
  uint64_T chunks[2];
} uint128m_T;

typedef struct {
  uint128m_T re;
  uint128m_T im;
} cuint128m_T;

typedef struct {
  uint64_T chunks[3];
} int192m_T;

typedef struct {
  int192m_T re;
  int192m_T im;
} cint192m_T;

typedef struct {
  uint64_T chunks[3];
} uint192m_T;

typedef struct {
  uint192m_T re;
  uint192m_T im;
} cuint192m_T;

typedef struct {
  uint64_T chunks[4];
} int256m_T;

typedef struct {
  int256m_T re;
  int256m_T im;
} cint256m_T;

typedef struct {
  uint64_T chunks[4];
} uint256m_T;

typedef struct {
  uint256m_T re;
  uint256m_T im;
} cuint256m_T;

typedef struct {
  uint64_T chunks[5];
} int320m_T;

typedef struct {
  int320m_T re;
  int320m_T im;
} cint320m_T;

typedef struct {
  uint64_T chunks[5];
} uint320m_T;

typedef struct {
  uint320m_T re;
  uint320m_T im;
} cuint320m_T;

typedef struct {
  uint64_T chunks[6];
} int384m_T;

typedef struct {
  int384m_T re;
  int384m_T im;
} cint384m_T;

typedef struct {
  uint64_T chunks[6];
} uint384m_T;

typedef struct {
  uint384m_T re;
  uint384m_T im;
} cuint384m_T;

typedef struct {
  uint64_T chunks[7];
} int448m_T;

typedef struct {
  int448m_T re;
  int448m_T im;
} cint448m_T;

typedef struct {
  uint64_T chunks[7];
} uint448m_T;

typedef struct {
  uint448m_T re;
  uint448m_T im;
} cuint448m_T;

typedef struct {
  uint64_T chunks[8];
} int512m_T;

typedef struct {
  int512m_T re;
  int512m_T im;
} cint512m_T;

typedef struct {
  uint64_T chunks[8];
} uint512m_T;

typedef struct {
  uint512m_T re;
  uint512m_T im;
} cuint512m_T;

typedef struct {
  uint64_T chunks[9];
} int576m_T;

typedef struct {
  int576m_T re;
  int576m_T im;
} cint576m_T;

typedef struct {
  uint64_T chunks[9];
} uint576m_T;

typedef struct {
  uint576m_T re;
  uint576m_T im;
} cuint576m_T;

typedef struct {
  uint64_T chunks[10];
} int640m_T;

typedef struct {
  int640m_T re;
  int640m_T im;
} cint640m_T;

typedef struct {
  uint64_T chunks[10];
} uint640m_T;

typedef struct {
  uint640m_T re;
  uint640m_T im;
} cuint640m_T;

typedef struct {
  uint64_T chunks[11];
} int704m_T;

typedef struct {
  int704m_T re;
  int704m_T im;
} cint704m_T;

typedef struct {
  uint64_T chunks[11];
} uint704m_T;

typedef struct {
  uint704m_T re;
  uint704m_T im;
} cuint704m_T;

typedef struct {
  uint64_T chunks[12];
} int768m_T;

typedef struct {
  int768m_T re;
  int768m_T im;
} cint768m_T;

typedef struct {
  uint64_T chunks[12];
} uint768m_T;

typedef struct {
  uint768m_T re;
  uint768m_T im;
} cuint768m_T;

typedef struct {
  uint64_T chunks[13];
} int832m_T;

typedef struct {
  int832m_T re;
  int832m_T im;
} cint832m_T;

typedef struct {
  uint64_T chunks[13];
} uint832m_T;

typedef struct {
  uint832m_T re;
  uint832m_T im;
} cuint832m_T;

typedef struct {
  uint64_T chunks[14];
} int896m_T;

typedef struct {
  int896m_T re;
  int896m_T im;
} cint896m_T;

typedef struct {
  uint64_T chunks[14];
} uint896m_T;

typedef struct {
  uint896m_T re;
  uint896m_T im;
} cuint896m_T;

typedef struct {
  uint64_T chunks[15];
} int960m_T;

typedef struct {
  int960m_T re;
  int960m_T im;
} cint960m_T;

typedef struct {
  uint64_T chunks[15];
} uint960m_T;

typedef struct {
  uint960m_T re;
  uint960m_T im;
} cuint960m_T;

typedef struct {
  uint64_T chunks[16];
} int1024m_T;

typedef struct {
  int1024m_T re;
  int1024m_T im;
} cint1024m_T;

typedef struct {
  uint64_T chunks[16];
} uint1024m_T;

typedef struct {
  uint1024m_T re;
  uint1024m_T im;
} cuint1024m_T;

typedef struct {
  uint64_T chunks[17];
} int1088m_T;

typedef struct {
  int1088m_T re;
  int1088m_T im;
} cint1088m_T;

typedef struct {
  uint64_T chunks[17];
} uint1088m_T;

typedef struct {
  uint1088m_T re;
  uint1088m_T im;
} cuint1088m_T;

typedef struct {
  uint64_T chunks[18];
} int1152m_T;

typedef struct {
  int1152m_T re;
  int1152m_T im;
} cint1152m_T;

typedef struct {
  uint64_T chunks[18];
} uint1152m_T;

typedef struct {
  uint1152m_T re;
  uint1152m_T im;
} cuint1152m_T;

typedef struct {
  uint64_T chunks[19];
} int1216m_T;

typedef struct {
  int1216m_T re;
  int1216m_T im;
} cint1216m_T;

typedef struct {
  uint64_T chunks[19];
} uint1216m_T;

typedef struct {
  uint1216m_T re;
  uint1216m_T im;
} cuint1216m_T;

typedef struct {
  uint64_T chunks[20];
} int1280m_T;

typedef struct {
  int1280m_T re;
  int1280m_T im;
} cint1280m_T;

typedef struct {
  uint64_T chunks[20];
} uint1280m_T;

typedef struct {
  uint1280m_T re;
  uint1280m_T im;
} cuint1280m_T;

typedef struct {
  uint64_T chunks[21];
} int1344m_T;

typedef struct {
  int1344m_T re;
  int1344m_T im;
} cint1344m_T;

typedef struct {
  uint64_T chunks[21];
} uint1344m_T;

typedef struct {
  uint1344m_T re;
  uint1344m_T im;
} cuint1344m_T;

typedef struct {
  uint64_T chunks[22];
} int1408m_T;

typedef struct {
  int1408m_T re;
  int1408m_T im;
} cint1408m_T;

typedef struct {
  uint64_T chunks[22];
} uint1408m_T;

typedef struct {
  uint1408m_T re;
  uint1408m_T im;
} cuint1408m_T;

typedef struct {
  uint64_T chunks[23];
} int1472m_T;

typedef struct {
  int1472m_T re;
  int1472m_T im;
} cint1472m_T;

typedef struct {
  uint64_T chunks[23];
} uint1472m_T;

typedef struct {
  uint1472m_T re;
  uint1472m_T im;
} cuint1472m_T;

typedef struct {
  uint64_T chunks[24];
} int1536m_T;

typedef struct {
  int1536m_T re;
  int1536m_T im;
} cint1536m_T;

typedef struct {
  uint64_T chunks[24];
} uint1536m_T;

typedef struct {
  uint1536m_T re;
  uint1536m_T im;
} cuint1536m_T;

typedef struct {
  uint64_T chunks[25];
} int1600m_T;

typedef struct {
  int1600m_T re;
  int1600m_T im;
} cint1600m_T;

typedef struct {
  uint64_T chunks[25];
} uint1600m_T;

typedef struct {
  uint1600m_T re;
  uint1600m_T im;
} cuint1600m_T;

typedef struct {
  uint64_T chunks[26];
} int1664m_T;

typedef struct {
  int1664m_T re;
  int1664m_T im;
} cint1664m_T;

typedef struct {
  uint64_T chunks[26];
} uint1664m_T;

typedef struct {
  uint1664m_T re;
  uint1664m_T im;
} cuint1664m_T;

typedef struct {
  uint64_T chunks[27];
} int1728m_T;

typedef struct {
  int1728m_T re;
  int1728m_T im;
} cint1728m_T;

typedef struct {
  uint64_T chunks[27];
} uint1728m_T;

typedef struct {
  uint1728m_T re;
  uint1728m_T im;
} cuint1728m_T;

typedef struct {
  uint64_T chunks[28];
} int1792m_T;

typedef struct {
  int1792m_T re;
  int1792m_T im;
} cint1792m_T;

typedef struct {
  uint64_T chunks[28];
} uint1792m_T;

typedef struct {
  uint1792m_T re;
  uint1792m_T im;
} cuint1792m_T;

typedef struct {
  uint64_T chunks[29];
} int1856m_T;

typedef struct {
  int1856m_T re;
  int1856m_T im;
} cint1856m_T;

typedef struct {
  uint64_T chunks[29];
} uint1856m_T;

typedef struct {
  uint1856m_T re;
  uint1856m_T im;
} cuint1856m_T;

typedef struct {
  uint64_T chunks[30];
} int1920m_T;

typedef struct {
  int1920m_T re;
  int1920m_T im;
} cint1920m_T;

typedef struct {
  uint64_T chunks[30];
} uint1920m_T;

typedef struct {
  uint1920m_T re;
  uint1920m_T im;
} cuint1920m_T;

typedef struct {
  uint64_T chunks[31];
} int1984m_T;

typedef struct {
  int1984m_T re;
  int1984m_T im;
} cint1984m_T;

typedef struct {
  uint64_T chunks[31];
} uint1984m_T;

typedef struct {
  uint1984m_T re;
  uint1984m_T im;
} cuint1984m_T;

typedef struct {
  uint64_T chunks[32];
} int2048m_T;

typedef struct {
  int2048m_T re;
  int2048m_T im;
} cint2048m_T;

typedef struct {
  uint64_T chunks[32];
} uint2048m_T;

typedef struct {
  uint2048m_T re;
  uint2048m_T im;
} cuint2048m_T;
# 29 "brake_acc_nodiv_ctrl.h" 2



# 1 "rt_nonfinite.h" 1
# 21 "rt_nonfinite.h"
# 1 "/usr/lib/gcc/x86_64-redhat-linux/4.8.3/include/stddef.h" 1 3 4
# 22 "rt_nonfinite.h" 2


extern real_T rtInf;
extern real_T rtMinusInf;
extern real_T rtNaN;
extern real32_T rtInfF;
extern real32_T rtMinusInfF;
extern real32_T rtNaNF;
extern void rt_InitInfAndNaN(size_t realSize);
extern boolean_T rtIsInf(real_T value);
extern boolean_T rtIsInfF(real32_T value);
extern boolean_T rtIsNaN(real_T value);
extern boolean_T rtIsNaNF(real32_T value);
typedef struct {
  struct {
    uint32_T wordH;
    uint32_T wordL;
  } words;
} BigEndianIEEEDouble;

typedef struct {
  struct {
    uint32_T wordL;
    uint32_T wordH;
  } words;
} LittleEndianIEEEDouble;

typedef struct {
  union {
    real32_T wordLreal;
    uint32_T wordLuint;
  } wordL;
} IEEESingle;
# 33 "brake_acc_nodiv_ctrl.h" 2


# 1 "brake_acc_nodiv_ctrl_types.h" 1
# 25 "brake_acc_nodiv_ctrl_types.h"
typedef struct P_ABS_RR_Wheel_brake_acc_nodi_T_ P_ABS_RR_Wheel_brake_acc_nodi_T;


typedef struct P_brake_acc_nodiv_ctrl_T_ P_brake_acc_nodiv_ctrl_T;


typedef struct tag_RTM_brake_acc_nodiv_ctrl_T RT_MODEL_brake_acc_nodiv_ctrl_T;
# 36 "brake_acc_nodiv_ctrl.h" 2
# 87 "brake_acc_nodiv_ctrl.h"
typedef struct {
  real_T Threshold_10kmh;
} B_ABS_RR_Wheel_brake_acc_nodi_T;


typedef struct {
} DW_ABS_RR_Wheel_brake_acc_nod_T;


typedef struct {
  real_T RT_h;
  real_T RT4;
  real_T RT1;
  real_T RT2;
  real_T RT3;
  real_T RT14;
  real_T RT9;
  real_T RT10;
  real_T RT11;
  real_T RT12;
  real_T vkmh;
  real_T Distribution[4];
  real_T Gain1;
  B_ABS_RR_Wheel_brake_acc_nodi_T ABS_FL_Wheel;
  B_ABS_RR_Wheel_brake_acc_nodi_T ABS_FR_Wheel;
  B_ABS_RR_Wheel_brake_acc_nodi_T ABS_RL_Wheel;
  B_ABS_RR_Wheel_brake_acc_nodi_T ABS_RR_Wheel;
} B_brake_acc_nodiv_ctrl_T;


typedef struct {
  real_T RT_Buffer0;
  real_T RT4_Buffer0;
  real_T RT1_Buffer0;
  real_T RT2_Buffer0;
  real_T RT3_Buffer0;
  DW_ABS_RR_Wheel_brake_acc_nod_T ABS_FL_Wheel;
  DW_ABS_RR_Wheel_brake_acc_nod_T ABS_FR_Wheel;
  DW_ABS_RR_Wheel_brake_acc_nod_T ABS_RL_Wheel;
  DW_ABS_RR_Wheel_brake_acc_nod_T ABS_RR_Wheel;
} DW_brake_acc_nodiv_ctrl_T;


typedef struct {
  real_T In_BrakePedal;
  real_T In_RRRotation;
  real_T In_RLRotation;
  real_T In_FRRotation;
  real_T In_FLRotation;
} ExtU_brake_acc_nodiv_ctrl_T;


typedef struct {
  real_T Out_TQ_RRBrake;
  real_T Out_TQ_RLBrake;
  real_T Out_TQ_FRBrake;
  real_T Out_TQ_FLBrake;
} ExtY_brake_acc_nodiv_ctrl_T;


struct P_ABS_RR_Wheel_brake_acc_nodi_T_ {
  real_T wheSpdms_Gain;


  real_T vms_Gain;


  real_T positive_UpperSat;


  real_T positive_LowerSat;


  real_T times_10_Gain;


  real_T slip_abs_on_times_10_Gain;


  real_T Threshold_10kmh_Threshold;


  uint8_T ReleaseBrake_Value;


};


struct P_brake_acc_nodiv_ctrl_T_ {
  real_T Gain1_Gain;


  real_T Distribution_Gain[4];


  real_T average_rpm_Gain;


  real_T wgrads_Gain;


  real_T vkmh_Gain;


  real_T RT_X0;


  real_T RT4_X0;


  real_T RT1_X0;


  real_T RT2_X0;


  real_T RT3_X0;


  real_T Pedal_map_UpperSat;


  real_T Pedal_map_LowerSat;


  P_ABS_RR_Wheel_brake_acc_nodi_T ABS_FL_Wheel;
  P_ABS_RR_Wheel_brake_acc_nodi_T ABS_FR_Wheel;
  P_ABS_RR_Wheel_brake_acc_nodi_T ABS_RL_Wheel;
  P_ABS_RR_Wheel_brake_acc_nodi_T ABS_RR_Wheel;
};


struct tag_RTM_brake_acc_nodiv_ctrl_T {





  struct {
    time_T taskTime0;
    uint32_T clockTick0;
    uint32_T clockTickH0;
    time_T stepSize0;
    struct {
      uint8_T TID[3];
      uint8_T cLimit[3];
    } TaskCounters;

    struct {
      uint8_T TID1_2;
    } RateInteraction;

    time_T tFinal;
    boolean_T stopRequestedFlag;
  } Timing;
};



extern P_brake_acc_nodiv_ctrl_T brake_acc_nodiv_ctrl_P;
# 255 "brake_acc_nodiv_ctrl.h"
extern ExtU_brake_acc_nodiv_ctrl_T brake_acc_nodiv_ctrl_U;





extern void brake_acc_nodiv_ctrl_initialize(void);

extern void brake_acc_nodiv_ctrl_terminate(void);
# 19 "brake_acc_nodiv_ctrl.c" 2
# 1 "brake_acc_nodiv_ctrl_private.h" 1
# 41 "brake_acc_nodiv_ctrl_private.h"
extern real_T rt_roundd_snf(real_T u);
extern void brake_acc_nodiv_ct_ABS_RR_Wheel(real_T rtu_vVehicleVelocitykmh,
  real_T rtu_TRequestedTorqueNm, real_T rtu_wwheelRotationrpm,
  B_ABS_RR_Wheel_brake_acc_nodi_T *localB, P_ABS_RR_Wheel_brake_acc_nodi_T
  localP);

extern void brake_acc_nodiv_ctrl_step0(void);
extern void brake_acc_nodiv_ctrl_step1(void);
extern void brake_acc_nodiv_ctrl_step2(void);
# 20 "brake_acc_nodiv_ctrl.c" 2







real_T RT9;
real_T RT10;
real_T RT11;
real_T RT12;
real_T RT14;




real_T RT_Buffer0;
real_T RT1_Buffer0;
real_T RT2_Buffer0;
real_T RT3_Buffer0;
real_T RT4_Buffer0;


ExtU_brake_acc_nodiv_ctrl_T brake_acc_nodiv_ctrl_U;
# 72 "brake_acc_nodiv_ctrl.c"
void brake_acc_nodiv_ct_ABS_RR_Wheel(real_T rtu_vVehicleVelocitykmh, real_T
  rtu_TRequestedTorqueNm, real_T rtu_wwheelRotationrpm,
  B_ABS_RR_Wheel_brake_acc_nodi_T *localB, P_ABS_RR_Wheel_brake_acc_nodi_T
  localP)
{


  boolean_T rtb_RelationalOperator;
  real_T rtb_vms;
  real_T u;



  rtb_vms = localP.vms_Gain * rtu_vVehicleVelocitykmh;




  u = rtb_vms - localP.wheSpdms_Gain * rtu_wwheelRotationrpm;


  if (u >= localP.positive_UpperSat) {
    u = localP.positive_UpperSat;
  } else {
    if (u <= localP.positive_LowerSat) {
      u = localP.positive_LowerSat;
    }
  }






  rtb_RelationalOperator = (localP.times_10_Gain * u >
    localP.slip_abs_on_times_10_Gain * rtb_vms);


  if (rtu_vVehicleVelocitykmh >= localP.Threshold_10kmh_Threshold) {




    if (rtb_RelationalOperator) {
      localB->Threshold_10kmh = localP.ReleaseBrake_Value;
    } else {
      localB->Threshold_10kmh = rtu_TRequestedTorqueNm;
    }


  } else {


    localB->Threshold_10kmh = rtu_TRequestedTorqueNm;


  }


}
# 196 "brake_acc_nodiv_ctrl.c"
real_T rt_roundd_snf(real_T u)
{
  real_T y;
  if (fabs(u) < 4.503599627370496E+15) {
    if (u >= 0.5) {
      y = floor(u + 0.5);
    } else if (u > -0.5) {
      y = u * 0.0;
    } else {
      y = ceil(u - 0.5);
    }
  } else {
    y = u;
  }

  return y;
}
# 477 "brake_acc_nodiv_ctrl.c"
void brake_acc_nodiv_ctrl_initialize(void)
{



  rt_InitInfAndNaN(sizeof(real_T));



  brake_acc_nodiv_ctrl_P.ABS_FL_Wheel.positive_UpperSat = rtInf;
  brake_acc_nodiv_ctrl_P.ABS_FR_Wheel.positive_UpperSat = rtInf;
  brake_acc_nodiv_ctrl_P.ABS_RL_Wheel.positive_UpperSat = rtInf;
  brake_acc_nodiv_ctrl_P.ABS_RR_Wheel.positive_UpperSat = rtInf;
# 535 "brake_acc_nodiv_ctrl.c"
  RT_Buffer0 = brake_acc_nodiv_ctrl_P.RT_X0;


  RT4_Buffer0 = brake_acc_nodiv_ctrl_P.RT4_X0;


  RT1_Buffer0 = brake_acc_nodiv_ctrl_P.RT1_X0;


  RT2_Buffer0 = brake_acc_nodiv_ctrl_P.RT2_X0;


  RT3_Buffer0 = brake_acc_nodiv_ctrl_P.RT3_X0;

}


void brake_acc_nodiv_ctrl_terminate(void)
{

}
# 32 "brake2_2_por_seq.c" 2
# 1 "brake_acc_nodiv_ctrl_data.c" 1
# 26 "brake_acc_nodiv_ctrl_data.c"
P_brake_acc_nodiv_ctrl_T brake_acc_nodiv_ctrl_P = {
  30.0,






  { 0.31, 0.29, 0.21, 0.19 },
  0.25,


  0.10471975511965977,


  1.8,


  0.0,


  0.0,


  0.0,


  0.0,


  0.0,


  100.0,


  0.0,




  {
    0.052359877559829883,


    0.27777777777777779,


    0.0,


    0.0,


    10.0,


    1.0,


    10.0,


    0U


  }

  ,


  {
    0.052359877559829883,


    0.27777777777777779,


    0.0,


    0.0,


    10.0,


    1.0,


    10.0,


    0U


  }

  ,


  {
    0.052359877559829883,


    0.27777777777777779,


    0.0,


    0.0,


    10.0,


    1.0,


    10.0,


    0U


  }

  ,


  {
    0.052359877559829883,


    0.27777777777777779,


    0.0,


    0.0,


    10.0,


    1.0,


    10.0,


    0U


  }

};
# 33 "brake2_2_por_seq.c" 2
# 1 "rtGetNaN.c" 1
# 23 "rtGetNaN.c"
# 1 "rtGetNaN.h" 1
# 21 "rtGetNaN.h"
# 1 "/usr/lib/gcc/x86_64-redhat-linux/4.8.3/include/stddef.h" 1 3 4
# 22 "rtGetNaN.h" 2



extern real_T rtGetNaN(void);
extern real32_T rtGetNaNF(void);
# 24 "rtGetNaN.c" 2






real_T rtGetNaN(void)
{
  size_t bitsPerReal = sizeof(real_T) * (8U);
  real_T nan = 0.0;
  if (bitsPerReal == 32U) {
    nan = rtGetNaNF();
  } else {


((0) ? (void) (0) : __assert_fail ("0", "rtGetNaN.c", 39, __PRETTY_FUNCTION__));
# 76 "rtGetNaN.c"
  }

  return nan;
}





real32_T rtGetNaNF(void)
{
  IEEESingle nanF = { { 0 } };

  uint16_T one = 1U;
  enum {
    LittleEndian,
    BigEndian
  } machByteOrder = (*((uint8_T *) &one) == 1U) ? LittleEndian : BigEndian;
  switch (machByteOrder) {
   case LittleEndian:
    {
      nanF.wordL.wordLuint = 0xFFC00000U;
      break;
    }

   case BigEndian:
    {
      nanF.wordL.wordLuint = 0x7FFFFFFFU;
      break;
    }
  }

  return nanF.wordL.wordLreal;
}
# 34 "brake2_2_por_seq.c" 2
# 1 "rtGetInf.c" 1
# 23 "rtGetInf.c"
# 1 "rtGetInf.h" 1
# 21 "rtGetInf.h"
# 1 "/usr/lib/gcc/x86_64-redhat-linux/4.8.3/include/stddef.h" 1 3 4
# 22 "rtGetInf.h" 2



extern real_T rtGetInf(void);
extern real32_T rtGetInfF(void);
extern real_T rtGetMinusInf(void);
extern real32_T rtGetMinusInfF(void);
# 24 "rtGetInf.c" 2






real_T rtGetInf(void)
{
  size_t bitsPerReal = sizeof(real_T) * (8U);
  real_T inf = 0.0;
  if (bitsPerReal == 32U) {
    inf = rtGetInfF();
  } else {


((0) ? (void) (0) : __assert_fail ("0", "rtGetInf.c", 39, __PRETTY_FUNCTION__));
# 76 "rtGetInf.c"
  }

  return inf;
}





real32_T rtGetInfF(void)
{
  IEEESingle infF;
  infF.wordL.wordLuint = 0x7F800000U;
  return infF.wordL.wordLreal;
}





real_T rtGetMinusInf(void)
{
  size_t bitsPerReal = sizeof(real_T) * (8U);
  real_T minf = 0.0;
  if (bitsPerReal == 32U) {
    minf = rtGetMinusInfF();
  } else {


((0) ? (void) (0) : __assert_fail ("0", "rtGetInf.c", 105, __PRETTY_FUNCTION__));
# 142 "rtGetInf.c"
  }

  return minf;
}





real32_T rtGetMinusInfF(void)
{
  IEEESingle minfF;
  minfF.wordL.wordLuint = 0xFF800000U;
  return minfF.wordL.wordLreal;
}
# 35 "brake2_2_por_seq.c" 2
# 1 "rt_nonfinite.c" 1
# 30 "rt_nonfinite.c"
real_T rtInf;
real_T rtMinusInf;
real_T rtNaN;
real32_T rtInfF;
real32_T rtMinusInfF;
real32_T rtNaNF;





void rt_InitInfAndNaN(size_t realSize)
{
  (void) (realSize);
  rtNaN = rtGetNaN();
  rtNaNF = rtGetNaNF();
  rtInf = rtGetInf();
  rtInfF = rtGetInfF();
  rtMinusInf = rtGetMinusInf();
  rtMinusInfF = rtGetMinusInfF();
}


boolean_T rtIsInf(real_T value)
{
  return (boolean_T)((value==rtInf || value==rtMinusInf) ? 1U : 0U);
}


boolean_T rtIsInfF(real32_T value)
{
  return (boolean_T)(((value)==rtInfF || (value)==rtMinusInfF) ? 1U : 0U);
}


boolean_T rtIsNaN(real_T value)
{
  return (boolean_T)((value!=value) ? 1U : 0U);
}


boolean_T rtIsNaNF(real32_T value)
{
  return (boolean_T)(((value!=value) ? 1U : 0U));
}
# 36 "brake2_2_por_seq.c" 2
# 1 "cbmc-math.c" 1
# 37 "brake2_2_por_seq.c" 2




void task_compute(void);
void task_RR_Wheel(void);
void task_RL_Wheel(void);
void task_FR_Wheel(void);
void task_FL_Wheel(void);




extern _Bool __VERIFIER_nondet_bool();
extern int __VERIFIER_nondet_int();
extern void __VERIFIER_assume(int);

void __VERIFIER_assert(int x)
{
  if(!x)
   ERROR: goto ERROR;
}

int fabs(float x)
{
  if(x<0) return -x;
  return x;
}





const int __CPROVER_thread_priorities[] = {5, 5, 22};
const char* __CPROVER_threads[] = {"c::task_RR_Wheel", "c::task_FL_Wheel", "c::task_compute"};

int num_irqs = 3;
int count = 3;

int irq_enabled[] = {0, 0, 0};

void enable_irq(int i) {
  irq_enabled[i] = 1;
}

void disable_irq(int i) {
  irq_enabled[i] = 0;
}

void schedule_irq(void) {
  int j = count;
  int irq;

  for (int i = 0; i < j; i++) {
    irq = __VERIFIER_nondet_int();
    __VERIFIER_assume(irq >= 0 && irq < num_irqs);

    if(irq_enabled[irq] && __VERIFIER_nondet_bool()) {
      count--;

      switch(irq) {
        case 0:
          task_RR_Wheel();
          break;
        case 1:
          task_FL_Wheel();
          break;
        case 2:
          task_compute();
          break;
        default:
          ;
      }
    }
  }
}
# 143 "brake2_2_por_seq.c"
extern void brake_acc_nodiv_ctrl_initialize(void);
extern void brake_acc_nodiv_ctrl_terminate(void);
extern void brake_acc_nodiv_ctrl_step(int_T tid);
# 165 "brake2_2_por_seq.c"
static void rt_OneStep(void)
{
    int_T i;




    brake_acc_nodiv_ctrl_step(0);




    for (i = 0 +1; i < 4; i++) {




      brake_acc_nodiv_ctrl_step(i);
    }

}







void rt_InitModel(void)
{
    brake_acc_nodiv_ctrl_initialize();
}







int_T rt_TermModel(void)
{
    brake_acc_nodiv_ctrl_terminate();
    return(0);
}
# 241 "brake2_2_por_seq.c"
void havocInputs(ExtU_brake_acc_nodiv_ctrl_T *_inputs) {
  ExtU_brake_acc_nodiv_ctrl_T inputs;


  __VERIFIER_assume(0<=inputs.In_BrakePedal && inputs.In_BrakePedal<=100 &&
              -10000<=inputs.In_RRRotation && inputs.In_RRRotation <= 10000 &&
              -10000<=inputs.In_RLRotation && inputs.In_RLRotation <= 10000 &&
              -10000<=inputs.In_FRRotation && inputs.In_FRRotation <= 10000 &&
              -10000<=inputs.In_FLRotation && inputs.In_FLRotation <= 10000);


  *_inputs = inputs;
}




void task_compute(void)
{
disable_irq(0);
disable_irq(1);
disable_irq(2);


  B_brake_acc_nodiv_ctrl_T brake_acc_nodiv_ctrl_B_local;


  brake_acc_nodiv_ctrl_B_local.RT_h = brake_acc_nodiv_ctrl_P.RT_X0;


  brake_acc_nodiv_ctrl_B_local.RT4 = brake_acc_nodiv_ctrl_P.RT4_X0;


  brake_acc_nodiv_ctrl_B_local.RT1 = brake_acc_nodiv_ctrl_P.RT1_X0;


  brake_acc_nodiv_ctrl_B_local.RT2 = brake_acc_nodiv_ctrl_P.RT2_X0;


  brake_acc_nodiv_ctrl_B_local.RT3 = brake_acc_nodiv_ctrl_P.RT3_X0;






  real_T vkmh;
  real_T Distribution_idx;
  real_T Distribution_idx_0;
  real_T Distribution_idx_1;





  Distribution_idx = brake_acc_nodiv_ctrl_P.Distribution_Gain[1] *
    brake_acc_nodiv_ctrl_B_local.RT14;
  Distribution_idx_0 = brake_acc_nodiv_ctrl_P.Distribution_Gain[2] *
    brake_acc_nodiv_ctrl_B_local.RT14;
  Distribution_idx_1 = brake_acc_nodiv_ctrl_P.Distribution_Gain[3] *
    brake_acc_nodiv_ctrl_B_local.RT14;
# 312 "brake2_2_por_seq.c"
  vkmh = (((RT9 + RT10) + RT11) + RT12) *
    brake_acc_nodiv_ctrl_P.average_rpm_Gain * brake_acc_nodiv_ctrl_P.wgrads_Gain
    * brake_acc_nodiv_ctrl_P.vkmh_Gain;


  {
    real_T tmp = (((RT9 + RT10) + RT11) + RT12) *
    brake_acc_nodiv_ctrl_P.average_rpm_Gain * brake_acc_nodiv_ctrl_P.wgrads_Gain
    * brake_acc_nodiv_ctrl_P.vkmh_Gain;

    __VERIFIER_assert(fabs(vkmh-tmp)<=0.001);


  }
# 334 "brake2_2_por_seq.c"
  RT_Buffer0 = brake_acc_nodiv_ctrl_P.Distribution_Gain
    [0] * brake_acc_nodiv_ctrl_B_local.RT14;


  RT4_Buffer0 = vkmh;


  RT1_Buffer0 = Distribution_idx;


  RT2_Buffer0 = Distribution_idx_0;


  RT3_Buffer0 = Distribution_idx_1;

enable_irq(0);
enable_irq(1);
enable_irq(2);
}

void task_RR_Wheel(void)
{
disable_irq(0);
disable_irq(1);
enable_irq(2);


  B_brake_acc_nodiv_ctrl_T brake_acc_nodiv_ctrl_B_local;


  brake_acc_nodiv_ctrl_B_local.RT_h = brake_acc_nodiv_ctrl_P.RT_X0;


  brake_acc_nodiv_ctrl_B_local.RT4 = brake_acc_nodiv_ctrl_P.RT4_X0;


  brake_acc_nodiv_ctrl_B_local.RT1 = brake_acc_nodiv_ctrl_P.RT1_X0;


  brake_acc_nodiv_ctrl_B_local.RT2 = brake_acc_nodiv_ctrl_P.RT2_X0;


  brake_acc_nodiv_ctrl_B_local.RT3 = brake_acc_nodiv_ctrl_P.RT3_X0;







  real_T rtb_to_int;


schedule_irq();
  brake_acc_nodiv_ctrl_B_local.RT_h = RT_Buffer0;


schedule_irq();
  brake_acc_nodiv_ctrl_B_local.RT4 = RT4_Buffer0;




  rtb_to_int = rt_roundd_snf(brake_acc_nodiv_ctrl_U.In_RRRotation);




  brake_acc_nodiv_ct_ABS_RR_Wheel(brake_acc_nodiv_ctrl_B_local.RT4,
    brake_acc_nodiv_ctrl_B_local.RT_h, rtb_to_int,
    &brake_acc_nodiv_ctrl_B_local.ABS_RR_Wheel,
    brake_acc_nodiv_ctrl_P.ABS_RR_Wheel);






schedule_irq();
  brake_acc_nodiv_ctrl_B_local.RT1 = RT1_Buffer0;
# 422 "brake2_2_por_seq.c"
schedule_irq();
  RT9 = rtb_to_int;
schedule_irq();

enable_irq(0);
enable_irq(1);
}

void task_FL_Wheel(void)
{
disable_irq(0);
disable_irq(1);
enable_irq(2);





  B_brake_acc_nodiv_ctrl_T brake_acc_nodiv_ctrl_B_local;


  brake_acc_nodiv_ctrl_B_local.RT_h = brake_acc_nodiv_ctrl_P.RT_X0;


  brake_acc_nodiv_ctrl_B_local.RT4 = brake_acc_nodiv_ctrl_P.RT4_X0;


  brake_acc_nodiv_ctrl_B_local.RT1 = brake_acc_nodiv_ctrl_P.RT1_X0;


  brake_acc_nodiv_ctrl_B_local.RT2 = brake_acc_nodiv_ctrl_P.RT2_X0;


  brake_acc_nodiv_ctrl_B_local.RT3 = brake_acc_nodiv_ctrl_P.RT3_X0;






  real_T rtb_to_int1;
  real_T tmp;




  rtb_to_int1 = rt_roundd_snf(brake_acc_nodiv_ctrl_U.In_FLRotation);


schedule_irq();
  brake_acc_nodiv_ctrl_B_local.RT_h = RT_Buffer0;


schedule_irq();
  brake_acc_nodiv_ctrl_B_local.RT4 = RT4_Buffer0;




  brake_acc_nodiv_ct_ABS_RR_Wheel(brake_acc_nodiv_ctrl_B_local.RT4,
    brake_acc_nodiv_ctrl_B_local.RT3, rtb_to_int1,
    &brake_acc_nodiv_ctrl_B_local.ABS_FL_Wheel,
    brake_acc_nodiv_ctrl_P.ABS_FL_Wheel);
# 493 "brake2_2_por_seq.c"
  if (brake_acc_nodiv_ctrl_U.In_BrakePedal >=
      brake_acc_nodiv_ctrl_P.Pedal_map_UpperSat) {
    tmp = brake_acc_nodiv_ctrl_P.Pedal_map_UpperSat;
  } else if (brake_acc_nodiv_ctrl_U.In_BrakePedal <=
      brake_acc_nodiv_ctrl_P.Pedal_map_LowerSat) {
    tmp = brake_acc_nodiv_ctrl_P.Pedal_map_LowerSat;
  } else {
    tmp = brake_acc_nodiv_ctrl_U.In_BrakePedal;
  }




  RT14 = brake_acc_nodiv_ctrl_P.Gain1_Gain *
    rt_roundd_snf(tmp);


schedule_irq();
  RT12 = rtb_to_int1;
schedule_irq();

enable_irq(0);
enable_irq(1);
}

void task_FR_Wheel(void)
{




  B_brake_acc_nodiv_ctrl_T brake_acc_nodiv_ctrl_B_local;


  brake_acc_nodiv_ctrl_B_local.RT_h = brake_acc_nodiv_ctrl_P.RT_X0;


  brake_acc_nodiv_ctrl_B_local.RT4 = brake_acc_nodiv_ctrl_P.RT4_X0;


  brake_acc_nodiv_ctrl_B_local.RT1 = brake_acc_nodiv_ctrl_P.RT1_X0;


  brake_acc_nodiv_ctrl_B_local.RT2 = brake_acc_nodiv_ctrl_P.RT2_X0;


  brake_acc_nodiv_ctrl_B_local.RT3 = brake_acc_nodiv_ctrl_P.RT3_X0;






  real_T rtb_to_int_k;


  brake_acc_nodiv_ctrl_B_local.RT4 = RT4_Buffer0;




  rtb_to_int_k = rt_roundd_snf(brake_acc_nodiv_ctrl_U.In_FRRotation);




  brake_acc_nodiv_ct_ABS_RR_Wheel(brake_acc_nodiv_ctrl_B_local.RT4,
    brake_acc_nodiv_ctrl_B_local.RT2, rtb_to_int_k,
    &brake_acc_nodiv_ctrl_B_local.ABS_FR_Wheel,
    brake_acc_nodiv_ctrl_P.ABS_FR_Wheel);






  brake_acc_nodiv_ctrl_B_local.RT3 = RT3_Buffer0;




  RT11 = rtb_to_int_k;
}

void task_RL_Wheel(void)
{




  B_brake_acc_nodiv_ctrl_T brake_acc_nodiv_ctrl_B_local;


  brake_acc_nodiv_ctrl_B_local.RT_h = brake_acc_nodiv_ctrl_P.RT_X0;


  brake_acc_nodiv_ctrl_B_local.RT4 = brake_acc_nodiv_ctrl_P.RT4_X0;


  brake_acc_nodiv_ctrl_B_local.RT1 = brake_acc_nodiv_ctrl_P.RT1_X0;


  brake_acc_nodiv_ctrl_B_local.RT2 = brake_acc_nodiv_ctrl_P.RT2_X0;


  brake_acc_nodiv_ctrl_B_local.RT3 = brake_acc_nodiv_ctrl_P.RT3_X0;






  real_T rtb_to_int_g;


  brake_acc_nodiv_ctrl_B_local.RT4 = RT4_Buffer0;




  brake_acc_nodiv_ct_ABS_RR_Wheel(brake_acc_nodiv_ctrl_B_local.RT4,
    brake_acc_nodiv_ctrl_B_local.RT1, rtb_to_int_g,
    &brake_acc_nodiv_ctrl_B_local.ABS_RL_Wheel,
    brake_acc_nodiv_ctrl_P.ABS_RL_Wheel);






  brake_acc_nodiv_ctrl_B_local.RT2 = RT2_Buffer0;




  RT10 = rtb_to_int_g;
}







int_T main(int_T argc, const char *argv[])
{
  rt_InitModel();






    havocInputs(&brake_acc_nodiv_ctrl_U);


    enable_irq(0);
    enable_irq(1);
    enable_irq(2);
    schedule_irq();
# 670 "brake2_2_por_seq.c"
  const int_T result = rt_TermModel();
  return result;
}
