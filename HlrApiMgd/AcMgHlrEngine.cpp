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
#include "StdAfx.h"
#include "accmd.h"
#include  <tchar.h>
#include "AcMgHlrEngine.h"


using namespace System::Runtime::InteropServices;

namespace Autodesk 
{
	namespace AutoCAD
	{
		namespace HLR
		{
			//Madhukar: Wrapping Callback in managed
			
			public delegate void Delegate_AcisCallback(int);
			void  AcisCallback(int p)
			{
				acutPrintf(_T("Percent :%d\n"), p);
			}
			public delegate void Delegate_AhlCallback(int);
			void  AhlCallback(int p)
			{
				acutPrintf(_T("Percent :%d\n"), p);
			}
			public delegate void Delegate_AcadCallback(int);
			void  AcadCallback(int p)
			{
				acutPrintf(_T("Percent :%d\n"), p);
			}


			
			AcMgHlrEngine::AcMgHlrEngine(int ctrl)
			{
				m_imp = (System::IntPtr)new AsdkHlrEngine(ctrl);
			}

			AcMgHlrEngine::AcMgHlrEngine(ObjectId id, int ctrl)
			{
				m_imp = (System::IntPtr)new AsdkHlrEngine((*reinterpret_cast<AcDbObjectId*>(&(id))), ctrl);
			}

			AcMgHlrEngine::AcMgHlrEngine(Viewport ^pViewport, int ctrl)
			{
				m_imp = (System::IntPtr)new AsdkHlrEngine(static_cast<AcDbViewport*>(pViewport->UnmanagedObject.ToPointer()), ctrl);
			}

			AcMgHlrEngine::AcMgHlrEngine(Point3d viewTarget, Vector3d viewDirection, int ctrl)
			{
				m_imp = (System::IntPtr)new AsdkHlrEngine(*reinterpret_cast<AcGePoint3d*>(&(viewTarget)),
														  *reinterpret_cast<AcGeVector3d*>(&(viewDirection)),
														  ctrl);
			}

			AcMgHlrEngine::~AcMgHlrEngine()
			{
				delete GetImpObj();
			}
			//typedef void (__cdecl * ProgressCB) (int percent_completed);
			int AcMgHlrEngine::run(AcMgHlrCollector ^collector)
			{
				AsdkHlrEngine    *pEngine    = GetImpObj();
				AsdkHlrCollector *pCollector = static_cast<AsdkHlrCollector*>(collector->UnmanagedObject.ToPointer());
				Delegate_AcisCallback^ fpAcis = gcnew Delegate_AcisCallback(&AcisCallback);
				Delegate_AcadCallback^ fpAcad = gcnew Delegate_AcadCallback(&AcadCallback);
				Delegate_AhlCallback^ fpAhl =	gcnew Delegate_AhlCallback(&AhlCallback);
				GCHandle gch1 = GCHandle::Alloc(fpAcis);
				GCHandle gch2 = GCHandle::Alloc(fpAcad);
				GCHandle gch3 = GCHandle::Alloc(fpAhl);

				IntPtr ip = Marshal::GetFunctionPointerForDelegate(fpAcis);
				_ProgressCallbackFct pcbfpAcis = static_cast<_ProgressCallbackFct>(ip.ToPointer());
				
				 ip = Marshal::GetFunctionPointerForDelegate(fpAcad);
				_ProgressCallbackFct pcbfpAcad = static_cast<_ProgressCallbackFct>(ip.ToPointer());

				ip = Marshal::GetFunctionPointerForDelegate(fpAhl);
				_ProgressCallbackFct pcbfpAhl = static_cast<_ProgressCallbackFct>(ip.ToPointer());

				pEngine->setAcisConversionProgressCallBack(pcbfpAcis);
				pEngine->setAcadConversionProgressCallBack(pcbfpAcad);
				pEngine->setAhlProgressCallBack(pcbfpAhl);
					
				
			
				//force garbage collection cycle to prove that the delegate doesn't get disposed, so that our objects are kept alive until we come back to managed stack
				GC::Collect();
			    Acad::ErrorStatus es =  pEngine->run(*pCollector);
				gch1.Free();
				gch2.Free();
				gch3.Free();
				return es;
				//return HlrRun(pEngine, pCollector);
			}

			void AcMgHlrEngine::cleanHlrCache()
			{
				AsdkHlrEngine::cleanHlrCache();
			}

			void AcMgHlrEngine::cleanHlrCache(Entity ^pEnt, Viewport ^pVp)
			{
				AsdkHlrEngine::cleanHlrCache(static_cast<AcDbEntity*>(pEnt->UnmanagedObject.ToPointer()),
											 static_cast<AcDbViewport*>(pVp->UnmanagedObject.ToPointer()));
			}

			void AcMgHlrEngine::cleanHlrCache(Entity ^pEnt, Point3d viewTarget, Vector3d viewDir)
			{
				AsdkHlrEngine::cleanHlrCache(static_cast<AcDbEntity*>(pEnt->UnmanagedObject.ToPointer()),
											 *reinterpret_cast<AcGePoint3d*>(&(viewTarget)),
											 *reinterpret_cast<AcGeVector3d*>(&(viewDir)));
			}
		}
	}
}
