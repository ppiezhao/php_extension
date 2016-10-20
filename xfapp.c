/*
  +----------------------------------------------------------------------+
  | PHP Version 7                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2015 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author:                                                              |
  +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_xfapp.h"
#include "Linux_voice/src/xfapp.c"
/* If you declare any globals in php_xfapp.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(xfapp)
*/

/* True global resources - no need for thread safety here */
static int le_xfapp;

/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("xfapp.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_xfapp_globals, xfapp_globals)
    STD_PHP_INI_ENTRY("xfapp.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_xfapp_globals, xfapp_globals)
PHP_INI_END()
*/
/* }}} */

/* Remove the following function when you have successfully modified config.m4
   so that your module can be compiled into PHP, it exists only for testing
   purposes. */

/* Every user-visible function in PHP should document itself in the source */
/* {{{ proto string confirm_xfapp_compiled(string arg)
   Return a string to confirm that the module is compiled in */
PHP_FUNCTION(confirm_xfapp_compiled)
{
	char *arg = NULL;
	size_t arg_len, len;
	zend_string *strg;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "s", &arg, &arg_len) == FAILURE) {
		return;
	}

	strg = strpprintf(0, "Congratulations! You have successfully modified ext/%.78s/config.m4. Module %.78s is now compiled into PHP.", "xfapp", arg);

	RETURN_STR(strg);
}

PHP_FUNCTION(xfapp_text_to_speech)
{
	char *text = NULL;
	char *filename = NULL;
	char *session_begin_params = NULL;
	int         ret                  = MSP_SUCCESS;
	char* login_params         = NULL;//"appid = 5801a133, work_dir = .";//登录参数,appid与msc库绑定,请勿随意改动
	size_t text_len,filename_len,session_len,login_len;
	if(zend_parse_parameters(ZEND_NUM_ARGS(), "ssss", &text, &text_len, &filename, &filename_len, &session_begin_params, &session_len, &login_params, &login_len) == FAILURE) 
	{
		return;
	}
	
	/* 用户登录 */
	ret = MSPLogin(NULL, NULL, login_params);//第一个参数是用户名，第二个参数是密码，第三个参数是登录参数，用户名和密码可在http://open.voicecloud.cn注册获取
	if (MSP_SUCCESS != ret)
	{
		goto exit ;//登录失败，退出登录
	}
	ret = text_to_speech(text, filename, session_begin_params);
	exit:
		//printf("按任意键退出 ...\n");
		////getchar();
	MSPLogout(); //退出登录
	RETURN_LONG(ret);
	
}
/* }}} */
/* The previous line is meant for vim and emacs, so it can correctly fold and
   unfold functions in source code. See the corresponding marks just before
   function definition, where the functions purpose is also documented. Please
   follow this convention for the convenience of others editing your code.
*/


/* {{{ php_xfapp_init_globals
 */
/* Uncomment this function if you have INI entries
static void php_xfapp_init_globals(zend_xfapp_globals *xfapp_globals)
{
	xfapp_globals->global_value = 0;
	xfapp_globals->global_string = NULL;
}
*/
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(xfapp)
{
	/* If you have INI entries, uncomment these lines
	REGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(xfapp)
{
	/* uncomment this line if you have INI entries
	UNREGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(xfapp)
{
#if defined(COMPILE_DL_XFAPP) && defined(ZTS)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(xfapp)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(xfapp)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "xfapp support", "enabled");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}
/* }}} */

/* {{{ xfapp_functions[]
 *
 * Every user visible function must have an entry in xfapp_functions[].
 */
const zend_function_entry xfapp_functions[] = {
	PHP_FE(confirm_xfapp_compiled,	NULL)		/* For testing, remove later. */
	PHP_FE(xfapp_text_to_speech,NULL)
	PHP_FE_END	/* Must be the last line in xfapp_functions[] */
};
/* }}} */

/* {{{ xfapp_module_entry
 */
zend_module_entry xfapp_module_entry = {
	STANDARD_MODULE_HEADER,
	"xfapp",
	xfapp_functions,
	PHP_MINIT(xfapp),
	PHP_MSHUTDOWN(xfapp),
	PHP_RINIT(xfapp),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(xfapp),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(xfapp),
	PHP_XFAPP_VERSION,
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_XFAPP
#ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE();
#endif
ZEND_GET_MODULE(xfapp)
#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
