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
using namespace Autodesk::AutoCAD::Geometry;

#include "AcMgHlrCollector.h"


//-----------------------------------------------------------------------------
namespace Autodesk {
 namespace AutoCAD {
  namespace HLR {

//-----------------------------------------------------------------------------
    [Autodesk::AutoCAD::Runtime::Wrapper("AsdkHlrControl")]
    public enum class HlrControl {
        Project         =/*AsdkHlrControl::*/kProject,          // Should the curves be projected to a plane?
        ShowAll         =/*AsdkHlrControl::*/kShowAll,          // Should all curves be returned, or just visible ones?
        Entity          =/*AsdkHlrControl::*/kEntity,           // Is it required to return the entity which caused
                                                                // a particular curve to be created?
        Block           =/*AsdkHlrControl::*/kBlock,            // Are the objectIds for the generating entities
                                                                // required, including those of the nested blocks?
        Subentity       =/*AsdkHlrControl::*/kSubentity,        // Should the subentity information be returned for solids or graphic
                                                                // primitives?
        HideTangents    =/*AsdkHlrControl::*/kHideTangents,     // Should tangent edges be suppressed?
        Cleanup         =/*AsdkHlrControl::*/kCleanup,          // Should stored data be cleaned after use?
        Isolines        =/*AsdkHlrControl::*/kIsolines,         // Should isolines be shown (same as would be seen in AutoCAD)?
        Unite           =/*AsdkHlrControl::*/kUnite,            // Should the entities be united before hidden lines?
                                                                // Will be much slower, but more accurate for intersecting entities.
        Reuse           =/*AsdkHlrControl::*/kReuse,            // Should the algorithm use the data which were created previously?
        Progress        =/*AsdkHlrControl::*/kProgress,         // Should the progress & abort callbacks be called?
        HandlePoints    =/*AsdkHlrControl::*/kHandlePoints,     // Should we show single points (requires bit more processing)?
        ProcessAll      =/*AsdkHlrControl::*/kProcessAll,       // Process all entities without looking at their layer state
                                                                // on which they lie on.
        HonorInternals  =/*AsdkHlrControl::*/kHonorInternals,
                                                                // Should we process internal edges' visibility (i.e. AcDbPolyFaceMesh /
                                                                // ACIS internal common edge / custom entity mesh/shell promitives)
                                                                // Will be much slower, but more accurate for internal edges' visibility
                                                                // processing.
        MeshSilhouettes =/*AsdkHlrControl::*/kMeshSilhouettes,  // Should we generate silhouettes for AcDbPolyFaceMesh
        SingleCacheVp   =/*AsdkHlrControl::*/kSingleCacheVp     // The HLR object cache is unique for all viewports
    } ;

    //[Autodesk::AutoCAD::Runtime::Wrapper("AsdkHlrEngine")]
    public ref class AcMgHlrEngine /*: public DisposableWrapper*/ {
        System::IntPtr m_imp ;

    public:
    //  AcMgHlrEngine (System::IntPtr unmanagedPointer)
    //      : DisposableWrapper (unmanagedPointer, true) {}

        property System::IntPtr UnmanagedObject {
            System::IntPtr get() {
                System::GC::KeepAlive (this) ; //make fxcop happy
                return (m_imp) ;
            }
        }

    internal:
        //- Returns the unmanaged ARX Object
        inline AsdkHlrEngine* GetImpObj () {
            return (static_cast<AsdkHlrEngine *>(UnmanagedObject.ToPointer ())) ;
        }

    public:
        AcMgHlrEngine (int ctrl /*=kShowAll | kEntity | kBlock | kSubentity | kReuse*/) ;
        AcMgHlrEngine (ObjectId id, int ctrl /*=kShowAll | kEntity | kBlock | kSubentity | kReuse*/) ;
        AcMgHlrEngine (Viewport ^pViewport, int ctrl /*=kShowAll | kEntity | kBlock | kSubentity | kReuse*/) ;
        AcMgHlrEngine (Point3d viewTarget, Vector3d viewDirection, int ctrl /*=kShowAll | kEntity | kBlock | kSubentity | kReuse*/) ;

        virtual ~AcMgHlrEngine () ;

        int run (AcMgHlrCollector ^collector) ;

//      void setAbortCallback (_AbortCallbackFct fct) ;

        //void setAcisConversionProgressCallBack (ProgressCallback ^callback);
        //void setAhlProgressCallBack            (ProgressCallback ^callback);
        //void setAcadConversionProgressCallBack (ProgressCallback ^callback);

        static void cleanHlrCache () ;
        static void cleanHlrCache (Entity ^pEnt, Viewport ^pVp) ;
        static void cleanHlrCache (Entity ^pEnt, Point3d viewTarget, Vector3d viewDir) ;

    } ;

//-----------------------------------------------------------------------------
  }
 }
}
