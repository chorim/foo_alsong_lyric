/*
* foo_alsong_lyric														
* Copyright (C)
*
* This library is free software; you can redistribute it and/or modify it 
* under the terms of the GNU Lesser General Public License as published 
* by the Free Software Foundation; version 2.1 of the License.
*
* This library is distributed in the hope that it will be useful, 
* but WITHOUT ANY WARRANTY; without even the implied warranty of 
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
* See the GNU Lesser General Public License for more details.
*
* You can receive a copy of the GNU Lesser General Public License from 
* http://www.gnu.org/
*/

#pragma once
#define DUMMY_KEY "4e06a8c06f189e54e0f22e7f645f172bc6ba2702618c445c2973848e004d4709d745cad80f1fc63654bae492019e771af038de6822b1123687d6598f0064cae237c4e1ac873f4d3aa267a6c27197878a0638cf29b571f049d50add1f4303b8d46c05020516d5ca8000d05a10371829da7a90aad4f4c68a62c0c6083ede28f247"

class SoapHelper
{
private:
	pugi::xml_document m_Document;
	pugi::xml_node m_Body;
	pugi::xml_node m_Query;
	std::string m_MethodName;
public:
	SoapHelper();
	void SetMethod(const char *MethodName);
	void AddParameter(const char *ParameterName, const char *value);

	boost::shared_ptr<pugi::xml_document> Execute();
	boost::shared_ptr<pugi::xml_document> Execute(int newserver);
};

class SoapReceiveException : public std::exception
{
	virtual const char *what() const
	{
		return "Exception occured while receiving soap data";
	}
};

