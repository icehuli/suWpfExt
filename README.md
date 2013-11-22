# suWpfExt
========

## a SketchUp Ruby extension using WPF(c#)

This is a sample project to show how to build a SketchUp Ruby extension using Wpf for the user interface.
It thanks to swig ( full name is Simplified Wrapper and Interface Generator ), http://www.swig.org/.

There are three Visual Studio projects, *suWpfExt*, *suWpfUI*, *suExtMainWrapper* and one ruby project *suRubyFiles*. 
You will get three dlls compiled by Visual Studio:
    
    suWpfExt->myExtMain.dll
    suWpfUI->suWpfUI.dll
    suExtMainWrapper->suExtMainWrapper.dll.

The files under *suRubyFiles* should be copied into SketchUp's Plugins folder, e.g.

    C:\Program Files (x86)\SketchUp\SketchUp 2013\Plugins

*myExtMain.dll* should be copied into the extesion folder under Plugins folder, e.g.

    C:\Program Files (x86)\SketchUp\SketchUp 2013\Plugins\su_myWpfExt

*suWpfUI.dll* and *suExtMainWrapper.dll* should be copied into the SketchUp folder, e.g. 
    
    C:\Program Files (x86)\SketchUp\SketchUp 2013
  
In complete all files should be placed as following:

    C:\Program Files (x86)\SketchUp\SketchUp 2013
                                        |
                                        |--- suWpfUI.dll
                                        |
                                        |--- suExtMainWrapper.dll
                                        |
                                        |=== Plugins
                                                |
                                                |--- su_myWpfExt.rb
                                                |
                                                |=== su_myWpfExt
                                                        |
                                                        |--- myExtMain.dll
                                                        |
                                                        |--- xxx.rb
                                                        |
                                                        |--- xxx.rb
                                                        |
                                                        |... ...
                                                        
                                                        
## Pre-Requirements:        
Install Ruby version ruby-1.8.6-p287-i386-mswin32: Download from 
[http://files.rubyforge.vm.bytemark.co.uk/rubyinstaller/ruby186-27_rc2.exe](http://files.rubyforge.vm.bytemark.co.uk/rubyinstaller/ruby186-27_rc2.exe) or 
[ftp://ftp.fu-berlin.de/unix/languages/ruby/binaries/mswin32/ruby-1.8.6-p287-i386-mswin32.zip](ftp://ftp.fu-berlin.de/unix/languages/ruby/binaries/mswin32/ruby-1.8.6-p287-i386-mswin32.zip) 
and install it e.g. into *C:\Ruby186p287* 

Set Environment Variables for Ruby
Go to *“Advanced system settings”* -> *“Advanced”* -> *“Environment Variables”*
Add following three *“User Variables”*:

    RUBY_HOME 	 C:\Ruby186p287
    RUBY_INCLUDE 	 C:\Ruby186p287\lib\ruby\1.8\i386-mswin32
    RUBY_LIB		 C:\Ruby186p287\lib\msvcrt-ruby18.lib
    
(optional, you can also add C:\Ruby186p287\bin to your PATH Variable, if you do want to run ruby or irb from command line)

Install SWIG: download the newest swig for windows (currently it is swigwin-2.0.11, [http://www.swig.org/download.html](http://www.swig.org/download.html)) and install it e.g. into *C:\swigwin-2.0.11* 
    

Set Environment Variable for SWIG

    SWIG_HOME 	 C:\swigwin-2.0.11

