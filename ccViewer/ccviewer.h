//##########################################################################
//#                                                                        #
//#                   CLOUDCOMPARE LIGHT VIEWER                            #
//#                                                                        #
//#  This project has been initiated under funding from ANR/CIFRE          #
//#                                                                        #
//#  This program is free software; you can redistribute it and/or modify  #
//#  it under the terms of the GNU General Public License as published by  #
//#  the Free Software Foundation; version 2 of the License.               #
//#                                                                        #
//#  This program is distributed in the hope that it will be useful,       #
//#  but WITHOUT ANY WARRANTY; without even the implied warranty of        #
//#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         #
//#  GNU General Public License for more details.                          #
//#                                                                        #
//#      +++ COPYRIGHT: EDF R&D + TELECOM ParisTech (ENST-TSI) +++         #
//#                                                                        #
//##########################################################################

#ifndef CCVIEWER_H
#define CCVIEWER_H

//Qt
#include <QtGui/QMainWindow>

//GUIs
#include <ui_ccviewer.h>
//#include <ui_ccviewerAbout.h>

//System
#include <set>

class ccGLWindow;
class ccHObject;
class Mouse3DInput;

//! Application main window
class ccViewer : public QMainWindow
{
	Q_OBJECT

public:
	//! Default constructor
	ccViewer(QWidget *parent = 0, Qt::WindowFlags flags = 0);

	//! Default destructor
	~ccViewer();

	//! Adds entity to display db
	void addToDB(ccHObject* entity);

	//! Checks for loaded entities
	/** If none, a message is displayed to invite the user
        to drag & drop files.
    **/
	bool checkForLoadedEntities();

public slots:

	//! Tries to load (and then adds to main db) a list of entity (files)
    /** \param filenames list of all filenames
    **/
    void addToDB(const QStringList& filenames);

protected slots:

	//! Shows display parameters dialog
	void showDisplayParameters();

	//! Updates display to match display parameters
	void updateDisplay();

	//! Selects entity
	void selectEntity(int uniqueID);
	
	//! Selects multiple entities
	//void selectEntities(std::set<int> entIDs); //not supported yet!

	//! Delete selected entity
	void doActionDeleteSelectedEntity();

    void doActionEditCamera();
    void toggleSunLight(bool);
    void toggleCustomLight(bool);
	void toggleFullScreen(bool);
    void doActionAbout();
    void doActionDisplayShortcuts();
	void setPivotAlwaysOn();
	void setPivotRotationOnly();
	void setPivotOff();
	void setOrthoView();
	void setCenteredPerspectiveView();
	void setViewerPerspectiveView();
    void setGlobalZoom();
    void zoomOnSelectedEntity();

	//default views
	void setFrontView();
    void setBottomView();
    void setTopView();
    void setBackView();
    void setLeftView();
    void setRightView();
	void setIsoView1();
	void setIsoView2();

	//selected entity properties
	void toggleColorsShown(bool);
	void toggleNormalsShown(bool);
	void toggleScalarShown(bool);
	void toggleColorbarShown(bool);
	void changeCurrentScalarField(bool);

	//3D mouse
	void on3DMouseMove(std::vector<float>&);
	void on3DMouseKeyUp(int);
	void on3DMouseKeyDown(int);
	void setup3DMouse(bool);

	//GL filters
    void doEnableGLFilter();
    void doDisableGLFilter();

protected:

	//! Loads plugins (from files)
    void loadPlugins();
	//! Loads a specific plugin
    bool loadPlugin(QObject* plugin);

	//! Makes the GL frame background gradient match the OpenGL window one
	void updateGLFrameGradient();

	//! Updates perspective UI elements
	void reflectPerspectiveState();

	//! Updates pivot UI elements
	void reflectPivotVisibilityState();

	//! Updates lights UI elements
	void reflectLightsState();

	//! Releases any connected 3D mouse (if any)
	void release3DMouse();

	//! Trys to enable (or disable) a 3D mouse device
	/** \param state whether to enable or disable the device
		\param silent whether to issue an error message in case of failure
	**/
	void enable3DMouse(bool state, bool silent);

	//! Associated GL context
	ccGLWindow* m_glWindow;

	//! Currently selected object
	ccHObject* m_selectedObject;

	//! 3D mouse handler
	Mouse3DInput* m_3dMouseInput;

private:
	//! Associated GUI
	Ui::ccViewerClass ui;
};

#endif // CCVIEWER_H
