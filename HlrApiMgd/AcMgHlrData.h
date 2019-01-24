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

//---------------------------------------------------------------------
#pragma once

//---------------------------------------------------------------------
using namespace System ;
using namespace System::Runtime ;
using namespace System::Runtime::InteropServices ;
using namespace Autodesk::AutoCAD::Runtime ;
using namespace Autodesk::AutoCAD::DatabaseServices ;

//---------------------------------------------------------------------
namespace Autodesk {
 namespace AutoCAD {
  namespace HLR {

//---------------------------------------------------------------------
	[Autodesk::AutoCAD::Runtime::Wrapper("AsdkHlrData::Visibility")]
	public enum class Visibility {
		Visible =AsdkHlrData::kVisible,			//- Not hidden by anything
		Hidden =AsdkHlrData::kHidden,			//- Hidden by a face
		Occluded =AsdkHlrData::kOccluded,		//- Hidden by another edge
		InternallyHidden =AsdkHlrData::kInternallyHidden,	//- Hidden because of entity internal visibility of a edge
															//- (i.e. AcDbPolyFaceMesh / ACIS internal common edge)
		Undefined =AsdkHlrData::kUndefined		//- Visibility not yet defined
	} ;

	//[Autodesk::AutoCAD::Runtime::Wrapper("AsdkHlrData")]
	public ref class AcMgHlrData /*: public DisposableWrapper*/ {
		System::IntPtr m_imp ;

	public:
	//	AcMgHlrData (System::IntPtr unmanagedPointer)
	//		: DisposableWrapper (unmanagedPointer, true) {}

		property System::IntPtr UnmanagedObject {
			System::IntPtr get() {
				System::GC::KeepAlive (this) ; //make fxcop happy
				return (m_imp) ;
			}
		}

	internal:
		//- Returns the unmanaged ARX Object
		inline AsdkHlrData* GetImpObj () {
			return (static_cast<AsdkHlrData *>(UnmanagedObject.ToPointer ())) ;
		}

	protected:
		AcMgHlrData () {}
	public:
		AcMgHlrData (System::IntPtr unmanagedPointer) ;
		virtual ~AcMgHlrData () ;

		property Entity^ RootEntity {
			Entity^ get () ; //- Gets entity causing this curve
		}
		property ObjectIdCollection^ ObjectIds {
			ObjectIdCollection^ get () ; //- Gets ObjectIds causing this curve
		}
		property Entity^ ResultEntity {
			Entity^ get () ; //- Curve itself. This is the actual curve stored by the class.
							 //- !In case of point, the resulting entity would be a point and not a curve!
            void set(Entity^ pEntity);
		}
		property Visibility EntityVisibility {
			Visibility get () ; //- Obtains visiblity of this curve
		}
		property Visibility HlrVisibility {
			Visibility get () ;
		}
		property SubentityId SubentId {
			SubentityId get () ; //- Obtains the subentities of the curve
		}
	} ;

//---------------------------------------------------------------------
  }
 }
}
