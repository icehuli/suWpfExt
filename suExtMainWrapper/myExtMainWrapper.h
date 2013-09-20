// suExtMainWrapper.h

#pragma once
#include <myExtMain.h>

#pragma make_public(MyExtMain) 

using namespace System;

namespace suExtMainWrapper {

	public ref class MyExtMainWrapper
	{
		// TODO: Add your methods for this class here.
		
	public:
		MyExtMainWrapper(MyExtMain* aMyExtMain);
		~MyExtMainWrapper();
	};
}
