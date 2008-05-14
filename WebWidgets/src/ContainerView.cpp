//
// ContainerView.cpp
//
// $Id: //poco/Main/WebWidgets/src/ContainerView.cpp#4 $
//
// Library: WebWidgets
// Package: Views
// Module:  ContainerView
//
// Copyright (c) 2008, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// Permission is hereby granted, free of charge, to any person or organization
// obtaining a copy of the software and accompanying documentation covered by
// this license (the "Software") to use, reproduce, display, distribute,
// execute, and transmit the Software, and to prepare derivative works of the
// Software, and to permit third-parties to whom the Software is furnished to
// do so, all subject to the following:
// 
// The copyright notices in the Software and this entire statement, including
// the above license grant, this restriction and the following disclaimer,
// must be included in all copies of the Software, in whole or in part, and
// all derivative works of the Software, unless such copies or derivative
// works are solely in the form of machine-executable object code generated by
// a source language processor.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
// FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
//


#include "Poco/WebWidgets/ContainerView.h"


namespace Poco {
namespace WebWidgets {


ContainerView::ContainerView():
	View(typeid(ContainerView))
{
}

	
ContainerView::ContainerView(const std::string& name):
	View(name, typeid(ContainerView))
{
}


ContainerView::ContainerView(const std::string& name, const std::type_info& type):
	View(name, type)
{
}

	
ContainerView::ContainerView(const std::type_info& type):
	View(type)
{
}


ContainerView::~ContainerView()
{
}


void ContainerView::add(View::Ptr pView)
{
	_views.push_back(pView);
	adoptChild(pView);
}


void ContainerView::remove(View::Ptr pView)
{
	rejectChild(pView);
	for (Iterator it = begin(); it != end(); ++it)
	{
		if (*it == pView)
		{
			_views.erase(it);
			break;
		}
	}
}


View::Ptr ContainerView::findChild(const std::string& name) const
{
	for (ConstIterator it = begin(); it != end(); ++it)
	{
		if (*it && (*it)->getName() == name)
		{
			return *it;
		}
	}

	return View::findChild(name);
}


} } // namespace Poco::WebWidgets