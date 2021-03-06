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


#ifndef DBAUI_TYPEINFO_HXX
#define DBAUI_TYPEINFO_HXX


#ifndef _RTL_USTRING_HXX_
#include <rtl/ustring.hxx>
#endif
#ifndef _COM_SUN_STAR_SDBC_DATATYPE_HPP_
#include <com/sun/star/sdbc/DataType.hpp>
#endif
#ifndef _COM_SUN_STAR_SDBC_COLUMNSEARCH_HPP_
#include <com/sun/star/sdbc/ColumnSearch.hpp>
#endif
#ifndef _COM_SUN_STAR_SDBC_COLUMNVALUE_HPP_
#include <com/sun/star/sdbc/ColumnValue.hpp>
#endif
#include <boost/shared_ptr.hpp>
#include <map>



namespace dbaui
{
//========================================================================
// Anhand dieser Ids werden die sprachabhaengigen ::rtl::OUString aus der Resource geholt
const sal_uInt16 TYPE_UNKNOWN	= 0;
const sal_uInt16 TYPE_TEXT		= 1;
const sal_uInt16 TYPE_NUMERIC	= 2;
const sal_uInt16 TYPE_DATETIME	= 3;
const sal_uInt16 TYPE_DATE		= 4;
const sal_uInt16 TYPE_TIME		= 5;
const sal_uInt16 TYPE_BOOL		= 6;
const sal_uInt16 TYPE_CURRENCY	= 7;
const sal_uInt16 TYPE_MEMO		= 8;
const sal_uInt16 TYPE_COUNTER	= 9;
const sal_uInt16 TYPE_IMAGE		= 10;
const sal_uInt16 TYPE_CHAR		= 11;
const sal_uInt16 TYPE_DECIMAL	= 12;
const sal_uInt16 TYPE_BINARY	= 13;
const sal_uInt16 TYPE_VARBINARY	= 14;
const sal_uInt16 TYPE_BIGINT	= 15;
const sal_uInt16 TYPE_DOUBLE	= 16;
const sal_uInt16 TYPE_FLOAT		= 17;
const sal_uInt16 TYPE_REAL		= 18;
const sal_uInt16 TYPE_INTEGER	= 19;
const sal_uInt16 TYPE_SMALLINT	= 20;
const sal_uInt16 TYPE_TINYINT	= 21;
const sal_uInt16 TYPE_SQLNULL	= 22;
const sal_uInt16 TYPE_OBJECT	= 23;
const sal_uInt16 TYPE_DISTINCT	= 24;
const sal_uInt16 TYPE_STRUCT	= 25;
const sal_uInt16 TYPE_ARRAY		= 26;
const sal_uInt16 TYPE_BLOB		= 27;
const sal_uInt16 TYPE_CLOB		= 28;
const sal_uInt16 TYPE_REF		= 29;
const sal_uInt16 TYPE_OTHER		= 30;
const sal_uInt16 TYPE_BIT		= 31;

	class OTypeInfo
	{
	public:
		::rtl::OUString	aUIName;		// the name which is the user see (a combination of resource text and aTypeName)
		::rtl::OUString	aTypeName;		// Name des Types in der Datenbank
		::rtl::OUString	aLiteralPrefix; // Prefix zum Quoten
		::rtl::OUString	aLiteralSuffix; // Suffix zum Quoten
		::rtl::OUString	aCreateParams;  // Parameter zum Erstellen
		::rtl::OUString	aLocalTypeName;
						
		sal_Int32		nPrecision;		// Laenge des Types
        sal_Int32		nType;			// Datenbanktyp
		
		sal_Int16		nMaximumScale;	// Nachkommastellen
		sal_Int16		nMinimumScale;  // Min Nachkommastellen
						
		sal_Int16		nSearchType;	// kann nach dem Typen gesucht werden
		
						
		sal_Bool		bCurrency		: 1,	// Waehrung
						bAutoIncrement	: 1,	// Ist es ein automatisch incrementierendes Feld
						bNullable		: 1,	// Kann das Feld NULL annehmen
						bCaseSensitive	: 1,	// Ist der Type Casesensitive
						bUnsigned		: 1;	// Ist der Type Unsigned	

		OTypeInfo()
                :nPrecision(0)
				,nType(::com::sun::star::sdbc::DataType::OTHER)
				,nMaximumScale(0)
				,nMinimumScale(0)
				,nSearchType(::com::sun::star::sdbc::ColumnSearch::FULL)
				,bCurrency(sal_False)
				,bAutoIncrement(sal_False)
				,bNullable(sal_True)
				,bCaseSensitive(sal_False)
				,bUnsigned(sal_False)
		{}
		sal_Bool operator == (const OTypeInfo& lh) const { return lh.nType == nType; }
		sal_Bool operator != (const OTypeInfo& lh) const { return lh.nType != nType; }
		inline ::rtl::OUString	getDBName() const { return aTypeName; }

	};

	typedef ::boost::shared_ptr<OTypeInfo>			TOTypeInfoSP;
	typedef ::std::multimap<sal_Int32,TOTypeInfoSP>	OTypeInfoMap;
	/** return the most suitable typeinfo for a requested type
		@param	_rTypeInfo		contains a map of type to typeinfo
		@param	_nType			the requested type
		@param	_sTypeName		the typename
		@param	_sCreateParams	the create params
		@param	_nPrecision		the precision
		@param	_nScale			the	scale
		@param	_bAutoIncrement	if it is a auto increment
		@param	_brForceToType	true when type was found which has some differenes
	*/
	TOTypeInfoSP getTypeInfoFromType(const OTypeInfoMap& _rTypeInfo,
							   sal_Int32 _nType,
							   const ::rtl::OUString& _sTypeName,
							   const ::rtl::OUString& _sCreateParams,
							   sal_Int32 _nPrecision,
							   sal_Int32 _nScale,
							   sal_Bool _bAutoIncrement,
							   sal_Bool& _brForceToType);
}

#endif // DBAUI_TYPEINFO_HXX


