dnl $Id$
dnl config.m4 for extension lttng

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

dnl PHP_ARG_WITH(lttng, for lttng support,
dnl Make sure that the comment is aligned:
dnl [  --with-lttng             Include lttng support])

dnl Otherwise use enable:

PHP_ARG_ENABLE(lttng, whether to enable lttng supp!= "no"; thenort,
dnl Make sure that the comment is aligned:
[  --enable-lttng           Enable LTTng tracing support])

if test "$PHP_LTTNG" != "no"; then
  PHP_CHECK_LIBRARY(lttng-ust, lttng_ust_exit,
   [
     AC_DEFINE(HAVE_LTTNGUST,1,[ ])
     PHP_ADD_LIBRARY(dl, 1, LTTNG_SHARED_LIBADD)
     PHP_ADD_LIBRARY(lttng-ust, 1, LTTNG_SHARED_LIBADD)
     PHP_ADD_LIBRARY(lttng-ust-ctl, 1, LTTNG_SHARED_LIBADD)
     PHP_ADD_LIBRARY(lttng-ust-dl, 1, LTTNG_SHARED_LIBADD)
     PHP_ADD_LIBRARY(lttng-ust-fork, 1, LTTNG_SHARED_LIBADD)
     PHP_ADD_LIBRARY(lttng-ust-cyg-profile, 1, LTTNG_SHARED_LIBADD)
     PHP_ADD_LIBRARY(lttng-ust-python-agent, 1, LTTNG_SHARED_LIBADD)
     PHP_ADD_LIBRARY(lttng-ust-tracepoint, 1, LTTNG_SHARED_LIBADD)
   ],[
     AC_MSG_ERROR([wrong lttng lib version or lib not found])
   ],[
    dnl -L$LTTNG_DIR/$PHP_LIBDIR -lm
    -llttng-ust -ldl -llttng-ust-ctl -llttng-ust-dl -llttng-ust-fork -llttng-ust-cyg-profile -llttng-ust-python-agent -llttng-ust-tracepoint
   ])
  
   PHP_SUBST(LTTNG_SHARED_LIBADD)

  PHP_NEW_EXTENSION(lttng, lttng.c, $ext_shared,, -DZEND_ENABLE_STATIC_TSRMLS_CACHE=1)
fi
