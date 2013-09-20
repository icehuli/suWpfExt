# Copyright 2013, ice.huli
# MIT license



require 'sketchup.rb'
require 'extensions.rb'

#Register the Sandbox Tools with SU's extension manager
myWpfExtension = SketchupExtension.new("My WPF Extension", "su_sandbox/myWpfExt.rb")

myWpfExtension.description = "An Extension using WPF(c#)"
myWpfExtension.version = "0.0.1"
myWpfExtension.creator = "ice.huli"
myWpfExtension.copyright = "2013, ice.huli"

#Default on in pro and off in free                        
Sketchup.register_extension myWpfExtension, true


