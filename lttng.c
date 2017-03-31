/**
 *
 * Copyright (C) 2017 Naser Ezzati <ezzati@gmail.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/* $Id$ */

#define TRACEPOINT_CREATE_PROBES
#define TRACEPOINT_DEFINE

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif
#include "php.h"
#include "php_ini.h"
#include "SAPI.h"
#include "ext/standard/info.h"
#include "zend_errors.h"
#include "zend_exceptions.h"
#include "ext/standard/php_string.h"    
#include "ext/spl/spl_exceptions.h"

#include "php_lttng.h"
#include "lttngust_php_trace.h"

#define SAFE_FILENAME(f) ((f)?(f):"-")
#define ZSTR_VAL(zstr)  (zstr)->val
#define ZSTR_LEN(zstr)  (zstr)->len

zend_module_entry lttng_module_entry = {
#if ZEND_MODULE_API_NO >= 20010901
    STANDARD_MODULE_HEADER,
#endif
    PHP_LTTNG_WORLD_EXTNAME,
    NULL,
    PHP_MINIT(lttng), 
    PHP_MSHUTDOWN(lttng),
    PHP_RINIT(lttng),
    PHP_RSHUTDOWN(lttng),
    PHP_MINFO(lttng),
#if ZEND_MODULE_API_NO >= 20010901
    PHP_LTTNG_WORLD_VERSION,
#endif
    STANDARD_MODULE_PROPERTIES
};

#ifdef COMPILE_DL_LTTNG
ZEND_GET_MODULE(lttng)
#endif

static void (*old_execute_ex)(zend_execute_data *execute_data);
static void lttng_execute_ex(zend_execute_data *execute_data);
static void (*old_execute_internal)(zend_execute_data *execute_data, zval *return_value);
static void lttng_execute_internal(zend_execute_data *execute_data,  zval *return_value);
static zend_op_array* (*old_compile_file)(zend_file_handle *file_handle, int type);
static zend_op_array* lttng_compile_file(zend_file_handle *file_handle, int type);
static zend_op_array* (*old_compile_string) (zval *source_string, char *filename);
static zend_op_array* lttng_compile_string(zval *source_string, char *filename);
static void (*old_error_cb)(int type, const char *error_filename, const uint error_lineno, const char *format, va_list args);
static void lttng_error_cb(int type, const char *error_filename, const uint error_lineno, const char *format, va_list args);
static void (*old_throw_exception_hook)(zval *ex TSRMLS_DC);
static void lttng_throw_exception_hook(zval *ex TSRMLS_DC);

PHP_MINIT_FUNCTION(lttng)
{   
    old_compile_file = zend_compile_file;
    zend_compile_file = lttng_compile_file;
    old_compile_string = zend_compile_string;
    zend_compile_string = lttng_compile_string;
    old_execute_ex = zend_execute_ex;
    zend_execute_ex = lttng_execute_ex;
    old_execute_internal = zend_execute_internal;
    zend_execute_internal = lttng_execute_internal;
    old_error_cb = zend_error_cb;
    zend_error_cb = lttng_error_cb;
    old_throw_exception_hook = zend_throw_exception_hook;
    zend_throw_exception_hook = lttng_throw_exception_hook;
    
    return SUCCESS;
}

PHP_MSHUTDOWN_FUNCTION(lttng)
{
    zend_compile_file = old_compile_file;
    zend_compile_string = old_compile_string;
    zend_execute_ex = old_execute_ex;
    zend_execute_internal = old_execute_internal;
    zend_error_cb = old_error_cb;
    zend_throw_exception_hook = old_throw_exception_hook;
    
    return SUCCESS;
}

PHP_MINFO_FUNCTION(lttng)
{
    php_info_print_table_start();
    php_info_print_table_header(2, "LTTng tracing support", "enabled");
    php_info_print_table_end();
}

PHP_RINIT_FUNCTION(lttng)
{
    tracepoint(ust_php, request_entry, (char *)SAFE_FILENAME(SG(request_info).path_translated), (char *)SAFE_FILENAME(SG(request_info).request_uri), (char *)SAFE_FILENAME(SG(request_info).request_method), (char *) SG(request_info).query_string);
    return SUCCESS;
}

PHP_RSHUTDOWN_FUNCTION(lttng)
{
    tracepoint(ust_php, request_exit, (char *)SAFE_FILENAME(SG(request_info).path_translated), (char *)SAFE_FILENAME(SG(request_info).request_uri), (char *)SAFE_FILENAME(SG(request_info).request_method), SG(request_info).query_string);
}

static inline const char *lttng_get_executed_filename(void)
{
    zend_execute_data *ex = EG(current_execute_data);

    while (ex && (!ex->func || !ZEND_USER_CODE(ex->func->type))) {
        ex = ex->prev_execute_data;
    }
    if (ex) {
        return ZSTR_VAL(ex->func->op_array.filename);
    } else {
        return zend_get_executed_filename();
    }
}

static void lttng_execute_ex(zend_execute_data *execute_data)
{
    int lineno;
    const char *scope, *filename, *funcname, *classname;
    scope = filename = funcname = classname = NULL;
    classname = get_active_class_name(&scope);
    filename = lttng_get_executed_filename();
    funcname = get_active_function_name();
    lineno = zend_get_executed_lineno();

    tracepoint(ust_php, execute_entry, filename, lineno);
    if (funcname != NULL){
        tracepoint(ust_php, function_entry, funcname, filename, lineno, classname,  scope);
    }
    execute_ex(execute_data);
    if (funcname != NULL)
        tracepoint(ust_php, function_exit, funcname, filename, lineno, classname, scope);
    tracepoint(ust_php, execute_exit, filename, lineno);
}

static void lttng_execute_internal(zend_execute_data *execute_data,  zval *return_value)
{
    int lineno;
    const char *filename;
    filename = lttng_get_executed_filename();
    lineno = zend_get_executed_lineno();

    tracepoint(ust_php, execute_entry, filename, lineno);
    execute_internal(execute_data, return_value);
    tracepoint(ust_php, execute_exit, filename, lineno);
}

static zend_op_array *lttng_compile_file(zend_file_handle *file_handle, int type)
{
    zend_op_array *res;
    tracepoint(ust_php, compile_file_entry, (char *)file_handle->filename, type);
    res = compile_file(file_handle, type);
    tracepoint(ust_php, compile_file_exit, (char *)file_handle->filename, type);
    return res;
}

static zend_op_array *lttng_compile_string(zval *source_string, char *filename )
{
    zend_op_array *res;
    tracepoint(ust_php, compile_string_entry, (char *)source_string, (char *)filename);
    res = compile_string(source_string, filename);
    tracepoint(ust_php, compile_string_exit, (char *)source_string, (char *)filename);
    return res;
}

static void lttng_error_cb(int type, const char *error_filename, const uint error_lineno, const char *format, va_list args)
{
    tracepoint(ust_php, php_error_entry, (char *)format, (char *)error_filename, error_lineno);
    old_error_cb(type, error_filename, error_lineno, format, args);
    tracepoint(ust_php, php_error_exit, (char *)format, (char *)error_filename, error_lineno);
}

static void lttng_throw_exception_hook(zval *exception TSRMLS_DC)
{
    zval *message, *filename, *lineno;
    zend_class_entry *default_ce;
    zval *rv;
    if (!exception) {
        return;
    }
    default_ce = zend_exception_get_default(TSRMLS_C);
    message =  zend_read_property(default_ce, exception, "message", sizeof("message")-1, 0 TSRMLS_CC, rv);
    filename = zend_read_property(default_ce, exception, "filename", sizeof("filename")-1, 0 TSRMLS_CC, rv);
    lineno = zend_read_property(default_ce, exception, "lineno", sizeof("lineno")-1, 0 TSRMLS_CC, rv);

    tracepoint(ust_php, php_exception_thrown_entry, (char *)Z_STRVAL_P(message), (char *)Z_STRVAL_P(filename),Z_LVAL_P(lineno));
    zend_throw_exception_hook(exception);
    tracepoint(ust_php, php_exception_thrown_exit, (char *)Z_STRVAL_P(message), (char *)Z_STRVAL_P(filename),Z_LVAL_P(lineno));
}
