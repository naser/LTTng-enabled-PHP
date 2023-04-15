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

#ifndef PHP_LTTNG_H
#define PHP_LTTNG_H 1
#define PHP_LTTNG_WORLD_VERSION "1.1"
#define PHP_LTTNG_WORLD_EXTNAME "lttng"

PHP_FUNCTION(trace_print);
PHP_MINIT_FUNCTION(lttng);
PHP_MSHUTDOWN_FUNCTION(lttng);
PHP_RINIT_FUNCTION(lttng);      /* Replace with NULL if there's nothing to do at request start */
PHP_RSHUTDOWN_FUNCTION(lttng);  /* Replace with NULL if there's nothing to do at request end */
PHP_MINFO_FUNCTION(lttng);


extern zend_module_entry lttng_module_entry;
#define phpext_lttng_ptr &lttng_module_entry

#endif
