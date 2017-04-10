PHP LTTng tracing extension
======
An extension to enable PHP requests tracing using LTTng tracer. You can trace all your php requests and extract runtime information about them. Using the Trace Compass tool you can have graphical views of Call Stack, Flame Graph, Top Requests and other interesting runtime information about your php requests.


## Installation

You can build and install the LTTng extension from source which is straightforward:

      git clone https://github.com/naser/LTTng-php-tracing-module.git
      cd LTTng-php-tracing-module
      phpize
      
      /* Before configuration, make sure you have LTTng 2.X installed in your machine. For installation manual refer to: http://lttng.org/docs/v2.9/#doc-installing-lttng */
      
      ./configure     
      make
      sudo make install
      
Currently it supports PHP 7.x, and  LTTng >= 2.8. To install LTTng 2.9 in Ubuntu you can use these commands:

      apt-add-repository ppa:lttng/stable-2.9
      apt-get update
      apt-get install lttng-tools liblttng-ust-dev
      
       
Also, for the php, make sure you have installed php7.X-dev:

      apt-get install php7.0-dev  

## Enabling the extension

After installation you will need to add `extension=lttng.so` to your primary *php.ini* file. To do so, run php -m in the command line to check if lttng is among the installed php extensions. If it is not there, you should manually enable it. 

      # To see where .ini files are located
      php -i | grep "\.ini"
      
Open the php.ini with an editor , search for 'Exentions' (or 'Dynamic Extensions') within the ini file and add this line there:
      
      extension=lttng.so
      # then save the file
      
Now run the php -m (or php -m | grep lttng) in the command line and this time you should see the lttng in the installed and enabled modules 
```bash
      # To see if lttng extension is loaded
      php -m | grep lttng
 ```
 


**Note**: You can also enable the extension temporarily using the command line:

```bash
      php -d extension=lttng.so
```

## Usage

1- Tracing:

To use this extension, you should first run LTTng and enable the lttng-ust tracing. To run the LTTng do the following commands:
```bash
      lttng create
      lttng enable-channel ss -u --subbuf-size 8M;
      lttng add-context -u -t vtid -c ss; 
      lttng enable-event -u -a -c ss
      lttng start
      ... run your php code
      lttng stop
      lttng view
  ```
  
 There are two scripts in the folder called trace-start and trace-stop that you can run to do all those above commands: 
 
```bash
      ./trace-start

      # run your php script ...

      ./trace-stop
```

A sample output of what you would get from tracing your script is shown in the following image:

      [15:52:23.512328851] (+0.001567556) naserez-desktop ust_php:request_entry: { cpu_id = 4 }, { vtid = 26387 }, { path = "/usr/local/apache2/htdocs/simple.php", uri = "-", method = "-", querystring = "(null)" }
      [15:52:23.512378022] (+0.000049171) naserez-desktop ust_php:compile_file_entry: { cpu_id = 4 }, { vtid = 26387 }, { filename = "simple.php", type = 8 }
      [15:52:23.512404852] (+0.000026830) naserez-desktop ust_php:compile_file_exit: { cpu_id = 4 }, { vtid = 26387 }, { filename = "simple.php", type = 8 }
      [15:52:23.512416960] (+0.000012108) naserez-desktop ust_php:execute_entry: { cpu_id = 4 }, { vtid = 26387 }, { filename = "/usr/local/apache2/htdocs/simple.php", lineno = 3 }
      [15:52:23.512417407] (+0.000000447) naserez-desktop ust_php:function_entry: { cpu_id = 4 }, { vtid = 26387 }, { funcname = "main", filename = "/usr/local/apache2/htdocs/simple.php", lineno = 3, class_name = "", scope = "" }
      [15:52:23.512429890] (+0.000012483) naserez-desktop ust_php:execute_entry: { cpu_id = 4 }, { vtid = 26387 }, { filename = "/usr/local/apache2/htdocs/simple.php", lineno = 3 }
      [15:52:23.512432382] (+0.000002492) naserez-desktop ust_php:trace_print: { cpu_id = 4 }, { vtid = 26387 }, { marker = "start" }
      [15:52:23.512433312] (+0.000000930) naserez-desktop ust_php:execute_exit: { cpu_id = 4 }, { vtid = 26387 }, { filename = "/usr/local/apache2/htdocs/simple.php", lineno = 3 }
      [15:52:23.512441214] (+0.000007902) naserez-desktop ust_php:execute_entry: { cpu_id = 4 }, { vtid = 26387 }, { filename = "/usr/local/apache2/htdocs/simple.php", lineno = 7 }
      [15:52:23.512441602] (+0.000000388) naserez-desktop ust_php:trace_print: { cpu_id = 4 }, { vtid = 26387 }, { marker = "end" }
      [15:52:23.512441823] (+0.000000221) naserez-desktop ust_php:execute_exit: { cpu_id = 4 }, { vtid = 26387 }, { filename = "/usr/local/apache2/htdocs/simple.php", lineno = 7 }
      [15:52:23.512442456] (+0.000000633) naserez-desktop ust_php:function_exit: { cpu_id = 4 }, { vtid = 26387 }, { funcname = "main", filename = "/usr/local/apache2/htdocs/simple.php", lineno = 3, class_name = "", scope = "" }
      [15:52:23.512442803] (+0.000000347) naserez-desktop ust_php:execute_exit: { cpu_id = 4 }, { vtid = 26387 }, { filename = "/usr/local/apache2/htdocs/simple.php", lineno = 3 }
      [15:52:23.512444673] (+0.000001870) naserez-desktop ust_php:request_exit: { cpu_id = 4 }, { vtid = 26387 }, { path = "/usr/local/apache2/htdocs/simple.php", uri = "-", method = "-", querystring = "(null)" }

As you see in the above output, different trace events are generated for your php script:

      | Event | Description |
      | ----- | ---------- |
      | request_entry | Fires when a request starts.	 |
      | request_exit  | Fires when a request exits.	 |
      | compile_file_entry | Fires when a file compilation starts.	 |
      | compile_file_exit | Fires when a file compilation ends. |
      | function_entry | Fires when the PHP engine calls a function/method.	 |
      | function_exit | Fires when the PHP engine returns from a function/method. |
      | execute_entry | Fires when a line code is to be executed.  |
      | execute_exit | Fires after execution of a line code.	 |
      | php_error_start | Fires just before logging a PHP error |
      | php_error_exit | Fires just after logging a PHP error  |
      | php_exception_thrown_entry| Fires just before logging a thrown PHP exception |
      | php_exception_thrown_exit |  Fires just after logging a thrown PHP exception |
      | trace_print | a PHP function that you can put in your script to output a string in the trace  |
This module also adds a builtin function called trace_print (the last entry in the above table) to the PHP which you can call directly from your php file;

     <!-- language: php -->
     <?php
            trace_print('step1');
            #...
            echo 'hi ;)';
            #...
            trace_print('step2');
            
      ?>
      
 This function enables you to add custom markers to the output trace data and is used when you would like to get information about a block of code, to print some variable values, or to just simplyfing the reading and following of your tracing output.

2- Analysis:

To play with the resulting logs, do your analysis using a graphical interface, you can install Trace Compass (http://tracecompass.org/) and import your trace there. 

It is also possible to use python codes to analyse the trace events which will be uploaded here shortly. For the moment, you can use my other project to play with the events and do your analysis: 
https://github.com/naser/lttnganalyses-for-lampstacktraces

      
      
