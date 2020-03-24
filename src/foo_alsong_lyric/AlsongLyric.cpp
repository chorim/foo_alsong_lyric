/*
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

#include "AlsongLyric.h"

AlsongLyric::AlsongLyric(const pugi::xml_node &node)
{
	if(!node) {
		MessageBox(NULL, L"데이터가 없서용.", L"테스트", MB_OK);
		return;
	}

	if(!node.child("lyricID").child_value()) {

		// GETLYRIC

		MessageBox(NULL, L"테스트 MessageBox입니다2.", L"테스트", MB_OK);

		m_Title = node.child("strTitle").child_value();
		m_Artist = node.child("strArtist").child_value();
		m_Album = node.child("strAlbum").child_value();
		m_Registrant = node.child("strRegisterFirstName").child_value();
		m_Lyric = node.child("strLyric").child_value();

		if(!m_Album.compare(m_Title))
			m_Album.clear();

		m_nInfoID = -1;

	} else {


		MessageBox(NULL, L"테스트 MessageBox입니다.7575", L"테스트", MB_OK);

		m_Album = node.child("album").child_value();
		m_Title = node.child("title").child_value();
		m_Artist = node.child("artist").child_value();
		//m_Registrant = node.child("strRegisterFirstName").child_value();
		m_Registrant = "작성자 안얄랴쥼";
		//m_Lyric = node.child("strLyric").child_value();
		m_Lyric = "[00:00.00] 가사 바로 안나옴w";
		m_nInfoID = boost::lexical_cast<int>(node.child("lyricID").child_value());

	}

	Split("<br>");
}
