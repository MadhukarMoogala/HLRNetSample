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
#include "AcMgHlrData.h"

//---------------------------------------------------------------------
namespace Autodesk {
	namespace AutoCAD {
		namespace HLR {

			//-----------------------------------------------------------------------------
			AcMgHlrData::AcMgHlrData(System::IntPtr unmanagedPointer) {
				m_imp = (System::IntPtr)unmanagedPointer;
			}

			AcMgHlrData::~AcMgHlrData() {
			}

			Entity^ AcMgHlrData::RootEntity::get() {
				Entity^ pEntity = safe_cast<Entity^>(Entity::Create(System::IntPtr(GetImpObj()->getEntity()), false));
				return (pEntity);
			}

			ObjectIdCollection^ AcMgHlrData::ObjectIds::get() {
				ObjectIdCollection^ tmp = gcnew ObjectIdCollection();
				*static_cast<AcDbObjectIdArray *>(tmp->UnmanagedObject.ToPointer()) = GetImpObj()->getObjectIds();
				return (tmp);
			}

			Entity^ AcMgHlrData::ResultEntity::get() {
				Entity^ pEntity = safe_cast<Entity^>(Entity::Create(System::IntPtr(GetImpObj()->getResultEntity()), false));
				return (pEntity);
			}

			void AcMgHlrData::ResultEntity::set(Entity^ pEntity) {
				AcDbEntity *entity;

				if (pEntity)
					entity = static_cast<AcDbEntity *>(pEntity->UnmanagedObject.ToPointer());
				else
					entity = NULL;

				GetImpObj()->setResultEntity(entity);
			}

			Visibility AcMgHlrData::EntityVisibility::get() {
				return (static_cast<Visibility>(GetImpObj()->getVisibility()));
			}

			Visibility AcMgHlrData::HlrVisibility::get() {
				return (static_cast<Visibility>(GetImpObj()->getHlrVisibility()));
			}

			SubentityId AcMgHlrData::SubentId::get() {
				SubentityId tmp;
				pin_ptr<SubentityId> pinner = &tmp;
				GETSUBENTITYID(*pinner) = GetImpObj()->getSubentId();
				return (tmp);
			}

			//---------------------------------------------------------------------
		}
	}
}
