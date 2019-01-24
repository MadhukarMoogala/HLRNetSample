// (C) Copyright 2005-2007 by Autodesk, Inc. 
//
// Permission to use, copy, modify, and distribute this software in
// object code form for any purpose and without fee is hereby granted, 
// provided that the above copyright notice appears in all copies and 
// that both that copyright notice and the limited warranty and
// restricted rights notice below appear in all supporting 
// documentation.
//
// AUTODESK PROVIDES THIS PROGRAM "AS IS" AND WITH ALL FAULTS. 
// AUTODESK SPECIFICALLY DISCLAIMS ANY IMPLIED WARRANTY OF
// MERCHANTABILITY OR FITNESS FOR A PARTICULAR USE.  AUTODESK, INC. 
// DOES NOT WARRANT THAT THE OPERATION OF THE PROGRAM WILL BE
// UNINTERRUPTED OR ERROR FREE.
//
// Use, duplication, or disclosure by the U.S. Government is subject to 
// restrictions set forth in FAR 52.227-19 (Commercial Computer
// Software - Restricted Rights) and DFAR 252.227-7013(c)(1)(ii)
// (Rights in Technical Data and Computer Software), as applicable.

//-----------------------------------------------------------------------------
#pragma once

//-----------------------------------------------------------------------------
using namespace System ;
using namespace System::Runtime ;
using namespace System::Runtime::InteropServices ;
using namespace Autodesk::AutoCAD::Runtime ;
using namespace Autodesk::AutoCAD::DatabaseServices ;

#include "AcMgHlrData.h"

//-----------------------------------------------------------------------------
namespace Autodesk {
 namespace AutoCAD {
  namespace HLR {

//-----------------------------------------------------------------------------
	//[Autodesk::AutoCAD::Runtime::Wrapper("AsdkHlrCollector")]
	public ref class AcMgHlrCollector /*: public DisposableWrapper*/ {
		System::IntPtr m_imp ;

	public:
//		AcMgHlrCollector (System::IntPtr unmanagedPointer)
//			: DisposableWrapper (unmanagedPointer, true) {}

		property System::IntPtr UnmanagedObject {
			System::IntPtr get() {
				System::GC::KeepAlive (this) ; //make fxcop happy
				return (m_imp) ;
			}
		}

	internal:
		//- Returns the unmanaged ARX Object
		inline AsdkHlrCollector* GetImpObj () {
			return (static_cast<AsdkHlrCollector *>(UnmanagedObject.ToPointer ())) ;
		}

	public:
		AcMgHlrCollector () ;
		AcMgHlrCollector (ObjectIdCollection ids) ;
		AcMgHlrCollector (DBObjectCollection ^entities, bool deleteInDestructor) ;
		//AcMgHlrCollector (AsdkHlrCollector &collector) ;
		virtual ~AcMgHlrCollector () ;

	public:
		property int OutputDataLength {
			int get () ;
		}

		AcMgHlrData^ OutputData (int index) ;

		property bool DeleteState {
			bool get () ;
			void set (bool) ;
		}

		property DBObjectCollection^ InputEntities {
			DBObjectCollection^ get () ;
		}

		property ObjectIdCollection^ InputEntityIds {
			ObjectIdCollection^ get () ;
		}

		void addEntity (Entity ^pEnt) ;
		void addEntities (DBObjectCollection ^pEnts) ;
		void addEntity (ObjectId id) ;
		void addEntities (ObjectIdCollection ^ids) ;
		void removeEntity (Entity ^pEnt) ;
		void removeEntities (DBObjectCollection ^pEnts) ;
		void removeEntity (ObjectId id) ;
		void removeEntities (ObjectIdCollection ^ids) ;

		void clear () ;

	} ;

//-----------------------------------------------------------------------------
  }
 }
}
