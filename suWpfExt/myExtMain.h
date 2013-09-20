#pragma once

#include <ruby.h>

#define SU_ID_DECLARE(idname) static ID ID##idname;
#define SU_ID_DEFINE(classname, idname) ID classname::ID##idname = rb_intern(#idname);
#define X_IDS \
	X(active_model			) \
	X(entities				) \
	X(selection				) \
	X(attribute_dictionaries) \
	X(get_attribute			) \
	X(name					) \
	X(to_s					) \
	X(typename				)

#ifdef MyExtMain_CPP_
#include <memory>
#include <msclr/marshal.h>
using namespace System;
using namespace System::IO;
using namespace System::Xml;
using namespace msclr::interop;
using namespace System::Runtime::InteropServices;
using std::shared_ptr;
#endif

class MyExtMain
{

	//useful constants
	static VALUE cSketchup;// = rb_const_get(mGeom, rb_intern("Sketchup"));
	//static ID IDactive_model;
#define X(var) SU_ID_DECLARE(var)
	X_IDS
#undef X

		//useful inlines (SketchUp methods)
		static VALUE m_active_model(){ return rb_funcall(cSketchup, IDactive_model, 0); }
	static VALUE m_active_model__entities(){return rb_funcall(m_active_model(), IDentities, 0);}
	static VALUE m_active_model__seletcion(){return rb_funcall(m_active_model(), IDselection, 0);}
	static VALUE m_entities(VALUE obj){return rb_funcall(obj, IDentities, 0);}
	static VALUE m_name(VALUE obj){return rb_funcall(obj, IDname, 0);}
	static VALUE m_typename(VALUE obj){return rb_funcall(obj, IDtypename, 0);}
	static VALUE m_attribute_dictionaries(VALUE obj){return rb_funcall(obj, IDattribute_dictionaries,0);};
	static VALUE m_to_s(VALUE obj){return rb_funcall(obj, IDto_s,0);};

	

public:
	MyExtMain(VALUE a_rb_dll_wrapper);
	~MyExtMain(void);

	void toggle_ext_main_window();
	void update_dictionary_view(VALUE selection);


private:
	void SetMainWindowXmlData();
private:
	VALUE rb_dll_wrapper;
	void* mainWindowWrapperPtr;  //gcroot<MainWindowWrapper^>*
	void* extMainWrapperPtr; //gcroot<MyExtMainWrapperPtr^>*
	void* dictsXmlDocPtr; //gcroot<XmlDocument^>*

#ifdef MyExtMain_CPP_

	//additional statics
	static VALUE sel_iterfunc(VALUE entity, gcroot<XmlElement^>* elem);
	static VALUE dicts_iterfunc(VALUE dict, gcroot<XmlElement^>* dicts);
	static VALUE hsh_iterfunc(VALUE pair, gcroot<XmlElement^>* dict);


	//using namespace System;
	static VALUE SystemString2RString(System::String^ systemString)
	{
		//marshal_context ^ context = gcnew marshal_context();
		//const char* cstr = context->marshal_as<const char*>(systemString);
		//VALUE rstr = rb_str_new2(cstr);
		//delete context;

		//method 2
		char* cstr = (char*)Marshal::StringToHGlobalAnsi(systemString).ToPointer();
		VALUE rstr = rb_str_new2(cstr);
		Marshal::FreeHGlobal((IntPtr)cstr);
		return rstr;
	}

	static System::String^ RString2SystemString(VALUE rstr)
	{
		return gcnew System::String(StringValueCStr(rstr));
	}
	
	static System::String^ RVALUE2SystemString(VALUE var)
	{
		VALUE rstr = m_to_s(var);
		return gcnew System::String(StringValueCStr(rstr));
	}
	

#endif
};


