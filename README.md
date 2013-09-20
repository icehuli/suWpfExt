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
                                                        
                                                        
        
