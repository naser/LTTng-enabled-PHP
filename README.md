LTTng PHP tracing extension

## Installation

You can build and install the LTTng extension from source which is straightforward:

      git clone https://github.com/naser/LTTng-php-tracing-module.git
      cd LTTng-php-tracing-module
      phpize
      
      /* Before configuration, make sure you have LTTng 2.X installed in your machine. For installation manual refer to: http://lttng.org/docs/v2.9/#doc-installing-lttng */
      
      ./configure     
      make
      sudo make install
      
      /* After installation, run php -m in the command line to check if lttng is among the installed php extensions. If it is not there, you should manually enable it. To do so: */
      open the php.ini with an editor (to find its location run ' php -i | grep Load '.
      search for 'Exentions' (or 'Dynamic Extensions') within the ini file and add this line there:
      extension=lttng.so
      save the file
      
      now run the php -m (or php -m | grep lttng) in the command line and this time you should see the lttng in the installed and enabled modules 
      
      
      


Currently it only supports PHP 7.x, but the support for the other versions will be added shortly.


## Usage


1- Tracing:

To use this extension, you should first run LTTng and enable the lttng-ust tracing. To run LTTng run the following commands:

      lttng create
      lttng enable-channel ss -u --subbuf-size 8M;
      lttng add-context -u -t vtid -c ss; 
      lttng enable-event -u -a -c ss
      lttng start
 There is a script in the files named trace-start that you can run it to do all those above commands. 

When you are done, just run the the following command to stop the tracing and display the outputs.
      lttng stop 
      lttng view
      
2- Analysis:

To play with the resulting logs, do your analysis using a graphical interface, you can install Trace Compass (http://tracecompass.org/) and import your trace there. 

It is also possible to use python codes to analyse the trace events which will be uploaded here shortly. For the moment, you can use my other project to play with the events and do your analysis: 
https://github.com/naser/lttnganalyses-for-lampstacktraces

      
      
