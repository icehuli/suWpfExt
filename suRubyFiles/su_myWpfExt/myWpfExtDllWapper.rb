module DictionaryViewer

    class MyWpfExtDllWapper


        require "su_myWpfExt/MyExtMain"
        require "su_myWpfExt/MySelectionObserver"

        attr_accessor :extMain

        def initialize
            create_tools
            create_observers
            create_commands
            create_toolbar
            create_menu_item

            @extMain = MyExtMain::MyExtMain.new(self)

        end

        def create_tools

        end

        def create_observers
            # Attach the observer.
            Sketchup.active_model.selection.add_observer(MySelectionObserver.new)
        end

        def create_commands
            @ext_main_window_cmd = UI::Command.new("Dictionary Viewer") {
                toggle_main_window
            }
            @ext_main_window_cmd.large_icon = File.dirname(__FILE__) + "/dictionary.png"
            @ext_main_window_cmd.small_icon = File.dirname(__FILE__) + "/dictionary.png"
            @ext_main_window_cmd.tooltip = "Toggle Dictionary Viewer"
            @ext_main_window_cmd.status_bar_text = "Toggle Dictionary Viewer"

        end

        def create_toolbar
            @toolbar = UI::Toolbar.new "Dictionary Viewer"
            @toolbar.add_item(@ext_main_window_cmd)
            @toolbar.show
        end

        def create_menu_item
            UI.menu("PlugIns").add_item("Dictionary Viewer") {
                show_main_window
            }
        end

        def toggle_main_window
            puts "toggle_main_window"
            @extMain.toggle_ext_main_window
        end


        def update_dictionary_view sel
            @extMain.update_dictionary_view sel
            # sel.each{|ent|
            #     p "================="
            #     p ent
            #     dicts = ent.attribute_dictionaries
            #     next unless dicts
            #     dicts.each{ |dict|
            #         p "- - - - - - - -"
            #         print  "<"
            #         print  dict.name
            #         p  ">"
            #         dict.each_pair { | key, value |
            #             print key
            #             print " \t-> \t"
            #             p value
            #         }
            #     }
            # }

        end
    end

end