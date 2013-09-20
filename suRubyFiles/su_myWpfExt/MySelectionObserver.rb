
# This is an example of an observer that watches the selection for
# changes.
class MySelectionObserver < Sketchup::SelectionObserver
	def onSelectionBulkChange(selection)
		MyWpfExtDllWapper.update_dictionary_view selection
	end
end
