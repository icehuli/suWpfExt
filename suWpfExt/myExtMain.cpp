


#include <vcclr.h> //for gcroot

#define MyExtMain_CPP_
#include "myExtMain.h"

using namespace System::Windows;
using namespace System::Windows::Threading;
using namespace System::Runtime::InteropServices;


using namespace suExtMainWrapper;
using namespace suWpfUI;

//useful constants
VALUE MyExtMain::cSketchup = rb_const_get(rb_cObject, rb_intern("Sketchup"));
//ID MyExtMain::IDactive_model = rb_intern("active_model");
#define X(var) SU_ID_DEFINE(MyExtMain,var)
X_IDS
#undef X



	MyExtMain::MyExtMain(VALUE a_rb_dll_wrapper)
	: rb_dll_wrapper(a_rb_dll_wrapper)
	, mainWindowWrapperPtr(new gcroot<MainWindowWrapper^>)
	, extMainWrapperPtr(new gcroot<MyExtMainWrapper^>)
	, dictsXmlDocPtr(new gcroot<XmlDocument^>)
{
	gcroot<MyExtMainWrapper^>* extMainWrapper = (gcroot<MyExtMainWrapper^>*)extMainWrapperPtr;
	*extMainWrapper = gcnew MyExtMainWrapper((MyExtMain*)this);
	//(*csWrapper)->SetCallback_SelectRectangleTool(&SODMain::select_sod_tool
	//  );
	//(*csWrapper)->SetCallback_UpdadeSodBarInsketchup(&SODMain::updade_sodbar_insketchup
	//  );
	//(*csWrapper)->SetCallback_AddMarkedSODBarsToSODBuilding(&SODMain::AddMarkedSODBarsToSODBuilding
	//  );

	gcroot<MainWindowWrapper^>* mainWindowWrapper = (gcroot<MainWindowWrapper^>*)mainWindowWrapperPtr;
	*mainWindowWrapper = gcnew MainWindowWrapper(*extMainWrapper, 1);
}

MyExtMain::~MyExtMain(void)
{
	if ( mainWindowWrapperPtr != nullptr) 
	{
		delete mainWindowWrapperPtr; mainWindowWrapperPtr = nullptr;
	}
	if ( extMainWrapperPtr != nullptr) 
	{
		delete extMainWrapperPtr; extMainWrapperPtr = nullptr;
	}
	if ( dictsXmlDocPtr != nullptr) 
	{
		delete dictsXmlDocPtr; dictsXmlDocPtr = nullptr;
	}
}

void MyExtMain::toggle_ext_main_window(){
	gcroot<MainWindowWrapper^>* mainWindowWrapper = (gcroot<MainWindowWrapper^>*)mainWindowWrapperPtr;
	(*mainWindowWrapper)->ToggleMainWindow();
}

//XmlNode root = doc.DocumentElement;

////Create a new node.
//XmlElement elem = doc.CreateElement("price");
//elem.InnerText="19.95";

////Add the node to the document.
//root.AppendChild(elem);

VALUE MyExtMain::sel_iterfunc(VALUE entity, gcroot<XmlElement^>* sel) {

	rb_funcall(rb_mKernel, rb_intern("puts"), 1, entity);
	VALUE dictionaries = m_attribute_dictionaries(entity);
	if (dictionaries == Qnil)
		return entity;
	XmlElement^ elem = (*sel)->OwnerDocument->CreateElement(RString2SystemString(m_typename(entity)));
	(*sel)->AppendChild(elem);
	std::auto_ptr<gcroot<XmlElement^>> elemPtr(new gcroot<XmlElement^>(elem));

	rb_iterate(rb_each, dictionaries, (VALUE (*)(...))dicts_iterfunc, (VALUE)elemPtr.get());
	return entity;
}

VALUE MyExtMain::dicts_iterfunc(VALUE dict, gcroot<XmlElement^>* dicts) {
	rb_funcall(rb_mKernel, rb_intern("puts"), 1, m_name(dict));

	System::String^ dicName = RString2SystemString(m_name(dict));
	if (dicName == nullptr || dicName == "")
	{
		dicName = "-";
	}
	XmlElement^ elem = (*dicts)->OwnerDocument->CreateElement(dicName);
	//elem->SetAttribute("name", RString2SystemString(m_name(dict)));
	(*dicts)->AppendChild(elem);
	std::auto_ptr<gcroot<XmlElement^>> elemPtr(new gcroot<XmlElement^>(elem));

	rb_iterate(rb_each, dict, (VALUE (*)(...))hsh_iterfunc, (VALUE)elemPtr.get());
	return dict;
}

VALUE MyExtMain::hsh_iterfunc(VALUE pair, gcroot<XmlElement^>* dict) {
	VALUE key = rb_ary_entry(pair, 0);
	VALUE value = rb_ary_entry(pair, 1);
	rb_funcall(rb_mKernel, rb_intern("puts"), 2, key, value);

	//System::String^ keyStr = RVALUE2SystemString(key);
	//if (keyStr == nullptr || keyStr == "")
	//{
	//	keyStr = "-";
	//}
	//XmlElement^ elem = (*dict)->OwnerDocument->CreateElement(keyStr);
	//System::String^ valueStr = RVALUE2SystemString(value);
	//if (valueStr == nullptr)
	//	valueStr = "";
	//elem->InnerText = valueStr;
	//(*dict)->AppendChild(elem);

	(*dict)->SetAttribute(RVALUE2SystemString(key), RVALUE2SystemString(value));

	return pair;
}

void MyExtMain::update_dictionary_view(VALUE sel)
{
	//rb_funcall(, rb_intern("select_sod_tool"), 1, INT2FIX(i));
	//VALUE rb_iterate(VALUE (*func1)(), void *arg1, VALUE (*func2)(), void *arg2)
	//   Calls the function func1, supplying func2 as the block.  func1 will be
	//   called with the argument arg1.  func2 receives the value from yield as
	//   the first argument, arg2 as the second argument.
	*(gcroot<XmlDocument^>*)dictsXmlDocPtr = gcnew XmlDocument();
	XmlDocument^ doc = (*(gcroot<XmlDocument^>*)dictsXmlDocPtr);
	XmlDeclaration^ dec = doc->CreateXmlDeclaration("1.0", nullptr, nullptr);
	doc->AppendChild(dec);// Create the root element
	XmlElement^ root = doc->CreateElement("selection");
	doc->AppendChild(root);
	std::auto_ptr<gcroot<XmlElement^>> rootPtr(new gcroot<XmlElement^>(root));

	rb_iterate(rb_each, sel, (VALUE (*)(...))sel_iterfunc, (VALUE)(rootPtr.get()));

	SetMainWindowXmlData();
}


void MyExtMain::SetMainWindowXmlData()
{

	gcroot<MainWindowWrapper^>* mainWindowWrapper = (gcroot<MainWindowWrapper^>*)mainWindowWrapperPtr;
	(*mainWindowWrapper)->SetDictionaries( *(gcroot<XmlDocument^>*)dictsXmlDocPtr );
}
