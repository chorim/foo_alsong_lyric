﻿/*
* foo_alsong_lyric														
* Copyright (C) 2007-2010 Inseok Lee <dlunch@gmail.com>
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

#include "stdafx.h"

#include "SoapHelper.h"
#include "Socket.h"

#include <boost/algorithm/string.hpp>

SoapHelper::SoapHelper()
{
	pugi::xml_node envelope = m_Document.append_child();
	envelope.set_name("SOAP-ENV:Envelope");
	envelope.append_attribute("xmlns:SOAP-ENV").set_value("http://www.w3.org/2003/05/soap-envelope");
	envelope.append_attribute("xmlns:SOAP-ENC").set_value("http://www.w3.org/2003/05/soap-encoding");
	envelope.append_attribute("xmlns:xsi").set_value("http://www.w3.org/2001/XMLSchema-instance");
	envelope.append_attribute("xmlns:xsd").set_value("http://www.w3.org/2001/XMLSchema");
	//envelope.append_attribute("xmlns:ns2").set_value("ALSongWebServer/Service1Soap");
	envelope.append_attribute("xmlns:ns1").set_value("ALSongWebServer");
	//envelope.append_attribute("xmlns:ns3").set_value("ALSongWebServer/Service1Soap12");
	envelope.append_child().set_name("SOAP-ENV:Body");

	m_Body = envelope.child("SOAP-ENV:Body");
}

void SoapHelper::SetMethod(const char *MethodName)
{
	pugi::xml_node 
		method = m_Body.append_child();
	method.set_name(MethodName);
	
	if ( boost::iequals(MethodName, "ns1:GetResembleLyricList2") ) {
		//m_Query = method.append_child();
		//m_Query.set_name("ns1:GetResembleLyricList2");
		m_Query = method;
	} else if ( boost::iequals(MethodName, "ns1:GetLyric7") ) {
		
		pugi::xml_node param = method.append_child();
		param.set_name("ns1:encData");
		param.append_child(pugi::node_pcdata).set_value(DUMMY_KEY);

		m_Query = method.append_child();
		m_Query.set_name("ns1:stQuery");

		
	} else {
		m_Query = method.append_child();
		m_Query.set_name("ns1:stQuery");
	}

	m_MethodName = MethodName;

}

void SoapHelper::AddParameter(const char *ParameterName, const char *value)
{

	pugi::xml_node param = m_Query.append_child();
	param.set_name(ParameterName);
	param.append_child(pugi::node_pcdata).set_value(value);

}

boost::shared_ptr<pugi::xml_document> SoapHelper::Execute()
{
	std::stringstream str;
	pugi::xml_writer_stream writer(str);
	m_Document.save(writer, "", pugi::format_raw);

	Socket s("lyrics.alsong.co.kr", 80);
	char buf[255];

	CHAR Header[] = "POST /alsongwebservice/service1.asmx HTTP/1.1\r\n"
		"Host: lyrics.alsong.co.kr\r\n"
		"User-Agent: gSOAP/2.8\r\n"
		"Content-Type: application/soap+xml; charset=utf-8; action=\"ALSongWebServer/GetLyric7\"\r\n"
		"Content-Length: %d\r\n"
		"Connection: close\r\n"
		"SOAPAction: \"ALSongWebServer/%s\"\r\n\r\n";

	
	wsprintfA(buf, Header, str.str().length(), &*(boost::find_first(m_MethodName, "ns1:")).begin() + 4);

	s.Send(buf, lstrlenA(buf));
	s.Send(str.str().c_str(), str.str().length());

	std::vector<char> data = s.ReceiveUntilEOF();
	if(data.size() == 0)
		throw SoapReceiveException();

	boost::shared_ptr<pugi::xml_document> ret = boost::shared_ptr<pugi::xml_document>(new pugi::xml_document());
	ret->load(&*boost::find_first(data, "\r\n\r\n").begin());


}

boost::shared_ptr<pugi::xml_document> SoapHelper::Execute(int newserver)
{
	std::stringstream str;
	pugi::xml_writer_stream writer(str);
	m_Document.save(writer, "", pugi::format_raw);

	Socket s("lyrics.alsong.co.kr", 80);
	char buf[255];

	//char *Header;

	CHAR Header[] = "POST /alsongwebservice/service1.asmx HTTP/1.1\r\n"
		"Host: lyrics.alsong.co.kr\r\n"
		"User-Agent: gSOAP/2.8\r\n"
		"Content-Type: application/soap+xml; charset=utf-8\r\n"
		"Content-Length: %d\r\n"
		"Connection: close\r\n"
		"SOAPAction: \"ALSongWebServer/%s\"\r\n\r\n";
	
	wsprintfA(buf, Header, str.str().length(), &*(boost::find_first(m_MethodName, "ns1:")).begin() + 4);

	s.Send(buf, lstrlenA(buf));
	s.Send(str.str().c_str(), str.str().length());

	std::vector<char> data = s.ReceiveUntilEOF();
	if(data.size() == 0)
		throw SoapReceiveException();

	boost::shared_ptr<pugi::xml_document> ret = boost::shared_ptr<pugi::xml_document>(new pugi::xml_document());
	ret->load(&*boost::find_first(data, "\r\n\r\n").begin());


	return ret;
}
