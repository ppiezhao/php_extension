dnl $Id$
dnl config.m4 for extension xfapp

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

dnl PHP_ARG_WITH(xfapp, for xfapp support,
dnl Make sure that the comment is aligned:
dnl [  --with-xfapp             Include xfapp support])

dnl Otherwise use enable:

 PHP_ARG_ENABLE(xfapp, whether to enable xfapp support,
dnl Make sure that the comment is aligned:
 [  --enable-xfapp           Enable xfapp support])

if test "$PHP_XFAPP" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-xfapp -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/xfapp.h"  # you most likely want to change this
  dnl if test -r $PHP_XFAPP/$SEARCH_FOR; then # path given as parameter
  dnl   XFAPP_DIR=$PHP_XFAPP
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for xfapp files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       XFAPP_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$XFAPP_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the xfapp distribution])
  dnl fi

  dnl # --with-xfapp -> add include path
  dnl PHP_ADD_INCLUDE($XFAPP_DIR/include)

  dnl # --with-xfapp -> check for lib and symbol presence
  dnl LIBNAME=xfapp # you may want to change this
  dnl LIBSYMBOL=xfapp # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $XFAPP_DIR/$PHP_LIBDIR, XFAPP_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_XFAPPLIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong xfapp lib version or lib not found])
  dnl ],[
  dnl   -L$XFAPP_DIR/$PHP_LIBDIR -lm
  dnl ])
  dnl
  dnl PHP_SUBST(XFAPP_SHARED_LIBADD)

  PHP_NEW_EXTENSION(xfapp, xfapp.c, $ext_shared,, -DZEND_ENABLE_STATIC_TSRMLS_CACHE=1)
fi
