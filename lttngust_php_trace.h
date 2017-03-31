#undef TRACEPOINT_PROVIDER
#define TRACEPOINT_PROVIDER ust_php
 
#undef TRACEPOINT_INCLUDE
#define TRACEPOINT_INCLUDE "lttngust_php_trace.h"
 
#if !defined(_UST_PHP_H) || defined(TRACEPOINT_HEADER_MULTI_READ)
#define _UST_PHP_H
#include <stdint.h>
#include <unistd.h>
#include <lttng/ust-events.h>
#include <lttng/tracepoint.h>

TRACEPOINT_EVENT(ust_php,
        function_entry,
        TP_ARGS(const char *,funcname, const char *, filename, int, lineno, const char *,class_name, const char *, scope),
        TP_FIELDS(
            ctf_string(funcname, funcname)
            ctf_string(filename, filename)
            ctf_integer(int, lineno, lineno)
            ctf_string(class_name, class_name)
            ctf_string(scope, scope)
            )
        )
TRACEPOINT_EVENT(ust_php,
        function_exit,
        TP_ARGS(const char *,funcname, const char *, filename, int, lineno, const char *,class_name, const char *, scope),
        TP_FIELDS(
            ctf_string(funcname, funcname)
            ctf_string(filename, filename)
            ctf_integer(int, lineno, lineno)
            ctf_string(class_name, class_name)
            ctf_string(scope, scope)
            )
        )

TRACEPOINT_EVENT(ust_php,
        compile_file_entry,
        TP_ARGS(char *, filename, int, type),
        TP_FIELDS(
            ctf_string(filename, filename)
            ctf_integer(int, type, type)
            )
        )

TRACEPOINT_EVENT(ust_php,
        compile_file_exit,
        TP_ARGS(char *, filename, int, type),
        TP_FIELDS(
            ctf_string(filename, filename)
            ctf_integer(int, type, type)
            )
        )

TRACEPOINT_EVENT(ust_php,
        compile_string_entry,
        TP_ARGS(char *, source_string, char *, filename),
        TP_FIELDS(
            ctf_string(source_string,source_string)
            ctf_string(filename, filename)
            )
        )

TRACEPOINT_EVENT(ust_php,
        compile_string_exit,
        TP_ARGS(char *, source_string, char *, filename),
        TP_FIELDS(
            ctf_string(source_string,source_string)
            ctf_string(filename, filename)
            )
        )

TRACEPOINT_EVENT(ust_php,
        execute_entry,
        TP_ARGS(const char *, filename, int, lineno),
        TP_FIELDS(
            ctf_string(filename, filename)
            ctf_integer(int, lineno, lineno)
           )
        )
TRACEPOINT_EVENT(ust_php,
        execute_exit,
        TP_ARGS(const char *, filename, int, lineno),
        TP_FIELDS(
            ctf_string(filename, filename)
            ctf_integer(int, lineno, lineno)
            )
        )

TRACEPOINT_EVENT(ust_php,
        request_entry,
        TP_ARGS(char *, path, char *,uri, char *,method, char *, querystring),
        //TP_ARGS(char *, path, char *,uri, char *,method),
        TP_FIELDS(
            ctf_string(path, path)
            ctf_string(uri, uri)
            ctf_string(method, method)
            ctf_string(querystring, querystring)
            )
        )

TRACEPOINT_EVENT(ust_php,
        request_exit,
        TP_ARGS(char *, path, char *,uri, char *,method, char *, querystring),
        TP_FIELDS(
            ctf_string(path, path)
            ctf_string(uri, uri)
            ctf_string(method, method)
            ctf_string(querystring, querystring)
            )
        )

TRACEPOINT_EVENT(ust_php,
        php_error_entry,
        TP_ARGS(char *, error, char *, filename,int, lineno),
        TP_FIELDS(
            ctf_string(error, error)
            ctf_string(filename, filename)
            ctf_integer(int, lineno, lineno)
            )
        )

TRACEPOINT_EVENT(ust_php,
        php_error_exit,
        TP_ARGS(char *, error, char *, filename,int, lineno),
        TP_FIELDS(
            ctf_string(error, error)
            ctf_string(filename, filename)
            ctf_integer(int, lineno, lineno)
            )
        )


TRACEPOINT_EVENT(ust_php,
        php_exception_caught,
        TP_ARGS(char *, exception),
        TP_FIELDS(
            ctf_string(exception, exception)
            )
        )

TRACEPOINT_EVENT(ust_php,
        php_exception_thrown_entry,
        TP_ARGS(char *, error, char *, filename,int, lineno),
        TP_FIELDS(
            ctf_string(error, error)
            ctf_string(filename, filename)
            ctf_integer(int, lineno, lineno)
            )   
        )

TRACEPOINT_EVENT(ust_php,
        php_exception_thrown_exit,
        TP_ARGS(char *, error, char *, filename,int, lineno),
        TP_FIELDS(
            ctf_string(error, error)
            ctf_string(filename, filename)
            ctf_integer(int, lineno, lineno)
            )   
        )

TRACEPOINT_EVENT(ust_php,
        php_mysql_connect,
        TP_ARGS(int, connection_id, char *,user, char *, host),
        TP_FIELDS(
            ctf_integer(int, connection_id, connection_id)
            ctf_string(user, user)
            ctf_string(host, host)
            )
        )
TRACEPOINT_EVENT(ust_php,
        php_mysql_close,
        TP_ARGS(int, connection_id, int, ret),
        TP_FIELDS(
            ctf_integer(int, connection_id, connection_id)
            ctf_integer(int, ret, ret)
            )
        )
TRACEPOINT_EVENT(ust_php,
        shared_lock_start,
        TP_ARGS(char *, filepath),
        TP_FIELDS(
            ctf_string(filepath, filepath)
            )
        )
TRACEPOINT_EVENT(ust_php,
        shared_lock_done,
        TP_ARGS(char *, filepath),
        TP_FIELDS(
            ctf_string(filepath, filepath)
            )
        )


#endif /* _UST_PHP_H */

#include <lttng/tracepoint-event.h>

