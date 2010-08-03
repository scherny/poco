//
// BinaryReader.cpp
//
// $Id: //poco/1.3/Foundation/src/BinaryReader.cpp#3 $
//
// Library: Foundation
// Package: Streams
// Module:  BinaryReaderWriter
//
// Copyright (c) 2004-2006, Applied Informatics Software Engineering GmbH.
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


#include "Poco/BinaryReader.h"
#include "Poco/ByteOrder.h"


namespace Poco {


BinaryReader::BinaryReader(std::istream& istr, StreamByteOrder byteOrder):
	_istr(istr)
{
#if defined(POCO_ARCH_BIG_ENDIAN)
	_flipBytes = (byteOrder == LITTLE_ENDIAN_BYTE_ORDER);
#else
	_flipBytes = (byteOrder == BIG_ENDIAN_BYTE_ORDER);
#endif
}


BinaryReader::~BinaryReader()
{
}


BinaryReader& BinaryReader::operator >> (bool& value)
{
	_istr.read((char*) &value, sizeof(value));
	return *this;
}


BinaryReader& BinaryReader::operator >> (char& value)
{
	_istr.read((char*) &value, sizeof(value));
	return *this;
}


BinaryReader& BinaryReader::operator >> (unsigned char& value)
{
	_istr.read((char*) &value, sizeof(value));
	return *this;
}


BinaryReader& BinaryReader::operator >> (signed char& value)
{
	_istr.read((char*) &value, sizeof(value));
	return *this;
}


BinaryReader& BinaryReader::operator >> (short& value)
{
	_istr.read((char*) &value, sizeof(value));
	if (_flipBytes) value = ByteOrder::flipBytes(value);
	return *this;
}


BinaryReader& BinaryReader::operator >> (unsigned short& value)
{
	_istr.read((char*) &value, sizeof(value));
	if (_flipBytes) value = ByteOrder::flipBytes(value);
	return *this;
}


BinaryReader& BinaryReader::operator >> (int& value)
{
	_istr.read((char*) &value, sizeof(value));
	if (_flipBytes) value = ByteOrder::flipBytes(value);
	return *this;
}


BinaryReader& BinaryReader::operator >> (unsigned int& value)
{
	_istr.read((char*) &value, sizeof(value));
	if (_flipBytes) value = ByteOrder::flipBytes(value);
	return *this;
}


BinaryReader& BinaryReader::operator >> (long& value)
{
	_istr.read((char*) &value, sizeof(value));
#if defined(POCO_LONG_IS_64_BIT)
	if (_flipBytes) value = ByteOrder::flipBytes((Int64) value);
#else
	if (_flipBytes) value = ByteOrder::flipBytes((Int32) value);
#endif
	return *this;
}


BinaryReader& BinaryReader::operator >> (unsigned long& value)
{
	_istr.read((char*) &value, sizeof(value));
#if defined(POCO_LONG_IS_64_BIT)
	if (_flipBytes) value = ByteOrder::flipBytes((UInt64) value);
#else
	if (_flipBytes) value = ByteOrder::flipBytes((UInt32) value);
#endif
	return *this;
}


BinaryReader& BinaryReader::operator >> (float& value)
{
	if (_flipBytes)
	{
		char* ptr = (char*) &value;
		ptr += sizeof(value);
		for (unsigned i = 0; i < sizeof(value); ++i)
			_istr.read(--ptr, 1);
	}
	else
	{
		_istr.read((char*) &value, sizeof(value));
	}
	return *this;
}


BinaryReader& BinaryReader::operator >> (double& value)
{
	if (_flipBytes)
	{
		char* ptr = (char*) &value;
		ptr += sizeof(value);
		for (unsigned i = 0; i < sizeof(value); ++i)
			_istr.read(--ptr, 1);
	}
	else
	{
		_istr.read((char*) &value, sizeof(value));
	}
	return *this;
}


#if defined(POCO_HAVE_INT64) && !defined(POCO_LONG_IS_64_BIT)


BinaryReader& BinaryReader::operator >> (Int64& value)
{
	_istr.read((char*) &value, sizeof(value));
	if (_flipBytes) value = ByteOrder::flipBytes(value);
	return *this;
}


BinaryReader& BinaryReader::operator >> (UInt64& value)
{
	_istr.read((char*) &value, sizeof(value));
	if (_flipBytes) value = ByteOrder::flipBytes(value);
	return *this;
}


#endif


BinaryReader& BinaryReader::operator >> (std::string& value)
{
	UInt32 size = 0;
	read7BitEncoded(size);
	value.clear();
	value.reserve(size);
	while (size--)
	{
		char c;
		_istr.read(&c, 1);
		value += c;
	}
	return *this;
}


void BinaryReader::read7BitEncoded(UInt32& value)
{
	char c;
	value = 0;
	int s = 0;
	do
	{
		c = 0;
		_istr.read(&c, 1);
		UInt32 x = (c & 0x7F);
		x <<= s;
		value += x;
		s += 7;
	}
	while (c & 0x80);
}


#if defined(POCO_HAVE_INT64)


void BinaryReader::read7BitEncoded(UInt64& value)
{
	char c;
	value = 0;
	int s = 0;
	do
	{
		c = 0;
		_istr.read(&c, 1);
		UInt64 x = (c & 0x7F);
		x <<= s;
		value += x;
		s += 7;
	}
	while (c & 0x80);
}


#endif


void BinaryReader::readRaw(std::streamsize length, std::string& value)
{
	value.clear();
	value.reserve(static_cast<std::string::size_type>(length));
	while (length--)
	{
		char c;
		_istr.read(&c, 1);
		value += c;
	}
}


void BinaryReader::readRaw(char* buffer, std::streamsize length)
{
	_istr.read(buffer, length);
}


void BinaryReader::readBOM()
{
	UInt16 bom;
	_istr.read((char*) &bom, sizeof(bom));
	_flipBytes = bom != 0xFEFF;
}


} // namespace Poco
