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

#endif /* _UST_PHP_H */
#include <lttng/tracepoint-event.h>

