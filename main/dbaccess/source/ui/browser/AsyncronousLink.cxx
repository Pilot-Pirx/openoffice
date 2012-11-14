/**************************************************************
 * 
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 * 
 *   http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 * 
 *************************************************************/



// MARKER(update_precomp.py): autogen include statement, do not remove
#include "precompiled_dbui.hxx"
#ifndef DBAUI_ASYNCRONOUSLINK_HXX
#include "AsyncronousLink.hxx"
#endif
#ifndef _SV_SVAPP_HXX 
#include <vcl/svapp.hxx>
#endif
#ifndef _TOOLS_DEBUG_HXX
#include <tools/debug.hxx>
#endif

//==================================================================
//= OAsyncronousLink
//==================================================================
using namespace dbaui;
DBG_NAME(OAsyncronousLink)
//------------------------------------------------------------------
OAsyncronousLink::OAsyncronousLink( const Link& _rHandler )
	:m_aHandler(_rHandler)
	,m_aEventSafety()
	,m_aDestructionSafety()
	,m_nEventId(0)
{
    DBG_CTOR(OAsyncronousLink,NULL);
}

//------------------------------------------------------------------
OAsyncronousLink::~OAsyncronousLink()
{
	{
		::osl::MutexGuard aEventGuard( m_aEventSafety );
		if ( m_nEventId )
			Application::RemoveUserEvent(m_nEventId);
		m_nEventId = 0;
	}

	{
		::osl::MutexGuard aDestructionGuard( m_aDestructionSafety );
		// this is just for the case we're deleted while another thread just handled the event :
		// if this other thread called our link while we were deleting the event here, the
		// link handler blocked. With leaving the above block it continued, but now we are prevented
		// to leave this destructor 'til the link handler recognizes that nEvent == 0 and leaves.
	}
    DBG_DTOR(OAsyncronousLink,NULL);
}


//------------------------------------------------------------------
void OAsyncronousLink::Call( void* _pArgument )
{
	::osl::MutexGuard aEventGuard( m_aEventSafety );
	if (m_nEventId)
		Application::RemoveUserEvent(m_nEventId);
	m_nEventId = Application::PostUserEvent( LINK( this, OAsyncronousLink, OnAsyncCall ), _pArgument );
}

//------------------------------------------------------------------
void OAsyncronousLink::CancelCall()
{
	::osl::MutexGuard aEventGuard( m_aEventSafety );
	if ( m_nEventId )
		Application::RemoveUserEvent( m_nEventId );
	m_nEventId = 0;
}

//------------------------------------------------------------------
IMPL_LINK(OAsyncronousLink, OnAsyncCall, void*, _pArg)
{
	{
		::osl::MutexGuard aDestructionGuard( m_aDestructionSafety );
		{
			::osl::MutexGuard aEventGuard( m_aEventSafety );
			if (!m_nEventId)
				// our destructor deleted the event just while we we're waiting for m_aEventSafety
				// -> get outta here
				return 0;
			m_nEventId = 0;
		}
	}
	if (m_aHandler.IsSet())
		return m_aHandler.Call(_pArg);

	return 0L;
}
