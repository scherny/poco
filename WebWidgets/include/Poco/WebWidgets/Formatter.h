//
// Formatter.h
//
// $Id: //poco/Main/WebWidgets/include/Poco/WebWidgets/Formatter.h#2 $
//
// Library: WebWidgets
// Package: Formatters
// Module:  Formatter
//
// Definition of the Formatter class.
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


#ifndef WebWidgets_Formatter_INCLUDED
#define WebWidgets_Formatter_INCLUDED


#include "Poco/WebWidgets/WebWidgets.h"
#include "Poco/RefCountedObject.h"
#include "Poco/AutoPtr.h"
#include "Poco/Any.h"


namespace Poco {
namespace WebWidgets {


class WebWidgets_API Formatter: public Poco::RefCountedObject
	/// A formatter is responsible for converting a generic Cell value,
	/// stored in a Poco::Any, into a string suitable for display by
	/// the Cell.
{
public:
	typedef Poco::AutoPtr<Formatter> Ptr;
	
	virtual std::string format(const Poco::Any& value) const = 0;
		/// Returns a string representation of the given value, suitable
		/// for displaying in a Cell.
		
	virtual Poco::Any parse(const std::string& value) const = 0;
		/// Parses the given string and returns an Any containing a
		/// variable of the correct type.
		///
		/// Throws a Poco::SyntaxException if the value cannot be parsed.
	
protected:
	Formatter();
	virtual ~Formatter();
	
private:
	Formatter(const Formatter&);
	Formatter& operator = (const Formatter&);
};


} } // namespace Poco::WebWidgets


#endif // WebWidgets_Formatter_INCLUDED