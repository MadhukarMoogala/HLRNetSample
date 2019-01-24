using System;
using System.Collections.Generic;
using System.Text;

using Autodesk.AutoCAD.Runtime;
using Autodesk.AutoCAD.ApplicationServices;
using Autodesk.AutoCAD.DatabaseServices;
using Autodesk.AutoCAD.EditorInput;
using Autodesk.AutoCAD.Geometry;
using Autodesk.AutoCAD.HLR;

[assembly: ExtensionApplication(null)]
[assembly: CommandClass(typeof(HlrNetSample.MyCommands))]

namespace HlrNetSample {

    
    public class MyCommands {

		[CommandMethod("test")]
		public void Test() {
			Application.DocumentManager.MdiActiveDocument.Editor.WriteMessage("Hello World!\n");

			PromptSelectionResult res = Application.DocumentManager.MdiActiveDocument.Editor.GetSelection();
			if (res.Status != PromptStatus.OK )
				return ;

			AcMgHlrCollector collector =new AcMgHlrCollector ();
			collector.DeleteState =true ;
			ObjectId [] ids =res.Value.GetObjectIds ();
			for ( int i =0 ; i < ids.Length ; i++ )
				collector.addEntity (ids [0]) ;

			// Get current viewport settings
			Vector3d viewdir = new Vector3d(1,1,1);// Application.GetSystemVariable("viewdir");
			Point3d target = new Point3d(0, 0, 0);// Application.GetSystemVariable("target");

			// Process hidden line removal
			
			AcMgHlrEngine hlr =new AcMgHlrEngine (
				target, viewdir,
				(int)(HlrControl.Entity | HlrControl.Block| HlrControl.Subentity | HlrControl.ShowAll | HlrControl.MeshSilhouettes | HlrControl.Progress) //Madhukar, progress param needed
			) ;
			hlr.run (collector) ;

			//- Assign color to the resulting entities
			//- red for visible edges
			//- blue for non-visible edges
			//- yellow for internal edges
			Database db =Application.DocumentManager.MdiActiveDocument.Database ;
			Transaction tr =Application.DocumentManager.MdiActiveDocument.TransactionManager.StartTransaction () ;
			try {
				BlockTable bt = (BlockTable)tr.GetObject (db.BlockTableId, OpenMode.ForRead) ;
				BlockTableRecord ms = (BlockTableRecord)tr.GetObject(bt[BlockTableRecord.ModelSpace], OpenMode.ForWrite) ;

				int n =collector.OutputDataLength ;
				for (int i = 0; i < n; i++) {
					AcMgHlrData p = collector.OutputData(i);

					Entity pEnt = p.ResultEntity;
					Autodesk.AutoCAD.HLR.Visibility vis = p.EntityVisibility;
					if (vis == Autodesk.AutoCAD.HLR.Visibility.Visible) {
						pEnt.ColorIndex = 1; //----- Red
					} else if (vis == Autodesk.AutoCAD.HLR.Visibility.InternallyHidden) {
						if ( p.HlrVisibility == Autodesk.AutoCAD.HLR.Visibility.Visible)
							pEnt.ColorIndex = 2; //----- Yellow
						else
							pEnt.ColorIndex = 3; //----- Green
					} else {
						pEnt.ColorIndex = 5; //----- Blue
					}

					ms.AppendEntity (pEnt) ; 
					tr.AddNewlyCreatedDBObject (pEnt, true) ;

				}
				tr.Commit () ;
			} catch (System.Exception) {
				tr.Abort () ;
			} finally {
				tr.Dispose () ;
			}
		}

	}

}
