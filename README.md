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


Currently it only supports PHP 7.x, but the support for the other versions will be added shortly.



