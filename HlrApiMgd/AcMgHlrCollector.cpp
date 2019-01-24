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
#include "AcMgHlrCollector.h"

//---------------------------------------------------------------------
namespace Autodesk {
	namespace AutoCAD {
		namespace HLR {

			//---------------------------------------------------------------------
			AcMgHlrCollector::AcMgHlrCollector() {
				m_imp = (System::IntPtr)new AsdkHlrCollector();
			}

			AcMgHlrCollector::AcMgHlrCollector(ObjectIdCollection ids) {
				m_imp = (System::IntPtr)new AsdkHlrCollector(
					*static_cast<AcDbObjectIdArray *>(ids.UnmanagedObject.ToPointer())
				);
			}

			AcMgHlrCollector::AcMgHlrCollector(DBObjectCollection ^entities, bool deleteInDestructor) {
				m_imp = (System::IntPtr)new AsdkHlrCollector(
					*static_cast<AcArray<AcDbEntity*> *>(entities->UnmanagedObject.ToPointer()),
					deleteInDestructor
				);
			}

			//AcMgHlrCollector::AcMgHlrCollector (ObjectIdCollection ids) {}

			AcMgHlrCollector::~AcMgHlrCollector() {
				delete m_imp;
			}

			int AcMgHlrCollector::OutputDataLength::get() {
				return (GetImpObj()->mOutputData.logicalLength());
			}

			AcMgHlrData^ AcMgHlrCollector::OutputData(int index) {
				AcMgHlrData^ tmp = gcnew AcMgHlrData((System::IntPtr)GetImpObj()->mOutputData[index]);
				return (tmp);
			}

			bool AcMgHlrCollector::DeleteState::get() {
				return (GetImpObj()->getDeleteState());
			}

			void AcMgHlrCollector::DeleteState::set(bool deleteState) {
				GetImpObj()->setDeleteState(deleteState);
			}

			DBObjectCollection^ AcMgHlrCollector::InputEntities::get() {
				DBObjectCollection^ tmp = gcnew DBObjectCollection();
				*static_cast<AcArray<AcDbEntity*> *>(tmp->UnmanagedObject.ToPointer()) = GetImpObj()->getInputEntities();
				return (tmp);
			}

			ObjectIdCollection^ AcMgHlrCollector::InputEntityIds::get() {
				ObjectIdCollection^ tmp = gcnew ObjectIdCollection();
				*static_cast<AcDbObjectIdArray *>(tmp->UnmanagedObject.ToPointer()) = GetImpObj()->getInputEntityIds();
				return (tmp);
			}

			void AcMgHlrCollector::addEntity(Entity ^pEnt) {
				GetImpObj()->addEntity(static_cast<AcDbEntity*>(pEnt->UnmanagedObject.ToPointer()));
			}

			void AcMgHlrCollector::addEntities(DBObjectCollection ^pEnts) {
				AcArray<AcDbEntity*> ents = *static_cast<AcArray<AcDbEntity*> *>(pEnts->UnmanagedObject.ToPointer());
				GetImpObj()->addEntities(ents);
			}

			void AcMgHlrCollector::addEntity(ObjectId id) {
				GetImpObj()->addEntity((*reinterpret_cast<AcDbObjectId*>(&(id))));
			}

			void AcMgHlrCollector::addEntities(ObjectIdCollection ^ids) {
				AcDbObjectIdArray list = *static_cast<AcDbObjectIdArray *>(ids->UnmanagedObject.ToPointer());
				GetImpObj()->addEntities(list);
			}

			void AcMgHlrCollector::removeEntity(Entity ^pEnt) {
				GetImpObj()->removeEntity(static_cast<AcDbEntity*>(pEnt->UnmanagedObject.ToPointer()));
			}

			void AcMgHlrCollector::removeEntities(DBObjectCollection ^pEnts) {
				AcArray<AcDbEntity*> ents = *static_cast<AcArray<AcDbEntity*> *>(pEnts->UnmanagedObject.ToPointer());
				GetImpObj()->removeEntities(ents);
			}

			void AcMgHlrCollector::removeEntity(ObjectId id) {
				GetImpObj()->removeEntity((*reinterpret_cast<AcDbObjectId*>(&(id))));
			}

			void AcMgHlrCollector::removeEntities(ObjectIdCollection ^ids) {
				AcDbObjectIdArray list = *static_cast<AcDbObjectIdArray *>(ids->UnmanagedObject.ToPointer());
				GetImpObj()->removeEntities(list);
			}

			void AcMgHlrCollector::clear() {
				GetImpObj()->clear();
			}

			//---------------------------------------------------------------------
		}
	}
}
