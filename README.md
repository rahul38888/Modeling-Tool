# Modeling-Tool
A basic modeling tool with basic user interface.

##This is 3D Modelling tool with basic Models Like Cube, Sphere, Cone, Torus, Teapot and Plane

						% % ALL CONTROLES AND USERINTERFACE % %
			1# DRAW OBJECTS
				Right click then select Objects option -> There are 7 types of object

			2# Lights
				Right click then select Lights option -> There are 7 types of lights

			3# Nurbs
				Right click then select Nurbs opion

			4# Bezier
				Right click then select Bezier option

			5# Particle System
				Right click then select Particle System option

			6# RE-POSITION / ROTATE / SCALE MODES
				'q' -> No Transform Mode
				'w' -> Re-Position Mode
				'e' -> Rotation Mode
				'r' -> Scaling Mode
				
					AFTER THAT
					
				6.1# AXIS SELECTION
					'd' -> X-axis to Y-axis to Z-axis to X-axis.
				
					6.1.1# Changing corresponding value of the transformed
						'=' -> Increment the value
						'-' -> Decreasing the value
			
			7# ON / OFF THE SECOND LIGHT
				'l' -> ON to OFF to ON
				
			8# CAMERA TRANSFORM
				8.1# DOLLY Camera
					'[' -> ZoomIn
					']' -> ZoomOut
					
				8.2# TRUCK CAMEAR
					RIGHT ARROW KEY -> Positive X-axis.
					LEFT ARROW KEY 	-> Negative X-axis.
					'.' 			-> Positive Y-axis.
					',' 			-> Negative Y-axis.
					UP ARROW KEY 	-> Positive Z-axis.
					LEFT ARROW KEY 	-> Negative Z-axis.
					
				8.3# ORBIT CAMERA
					Hold MIDDLE MOUSE KEY and move the mouse.
					
			9# OBJECT SELECTION
				'p' -> Select previous object.
				'n' -> Select next object.
			
			10# UNDO / REDO AND DELETE SELECTED OBJECT
				'z' -> Delete the last available formed object.
				'r' -> Recreate the latest object deleted by 'd'.
				'x' -> Delete the selected object.*
						
						*This change can't be Redo.
						
			11# WIREFRAME / SMOOTH MODES
				F4 Key -> Wireframe to Smooth to Wireframe
			12# SOLID AND WIREFRAME BOTH TOGETHER
				F5 Key -> Solid and Wireframe to Smooth to Solid and Wireframe


	#User Interface
		GUI is still to be developed but some of the user input and controls has been implemented
		
		1. Like to Draw any of the 6 objects Number Keys 1 to 6 are defined as
			1->cube, 2->sphere, 3->cone, 4->torus, 5->teapot, 6->plane
		
		2. Multiple objects can be drawn in any sequence and following properties are observed
			a. Any new objects are formed at origin, with zero rotation and scaled 1 in all direction.
			b. A Gizmo tool (Tool to reposition, rotate and scale in any axis) is observed to be 
				automatically at the position of the presently drawn object.
			c. Red -> X-axis, Green -> Y-axis and Blue -> Z-axis.
			
	# Properties of Gizmo and uses
		1. Red -> X-axis, Green -> Y-axis and Blue -> Z-axis.
		2. the Gizmo's functionality can be changed as following key, following Gizmo type.
			a. 'q' -> No tool selected.
			b. 'w' -> Re-positioning tool.
			c. 'e' -> Rotation tool.
			d. 'r' -> Scaling tool.
		3. Now while switching to positioning, rotation and scaling Gizmo one might observe one of the 
			axis being yellow color. This means that the axis is being selected to modify the object in that axis.
			Axis can be switched by pressing 'd' in following sequence:
				a. X-axis to Y-axis to Z-axis
				b. X-axis is selected by default.
		4. The selected transformed in selected axis cam be implemented as following:
			a. '=' -> Increasing corresponding variable.
			b. '-' -> Decreasing corresponding variable.
			
	# Lighting
		The software provide 2 lights:
			a. LIGHT0 is on by default.
			b. LIGHT1 is off but can be On by pressing 'l';

	# Camera Transform
		1. DOLLY CAMERA - the camera zoom in or out.
			This can be done by 
				a. '[' -> ZoomIn.
				b. ']' -> Zoom Out.
		
		2. TRUCK CAMEAR - the Focusing point is moved.
				a. RIGHT ARROW KEY -> Positive X-axis.
				b. LEFT ARROW KEY -> Negative X-axis.
				c. '.' -> Positive Y-axis.
				d. ',' -> Negative Y-axis.
				e. UP ARROW KEY -> Positive Z-axis.
				f. LEFT ARROW KEY -> Negative Z-axis.
		
		3. ORBIT CAMERA - the camera rotate about it Focusing point on a sphere of radius.
			This can be done by holding MIDDLE MOUSE KEY and moving the mouse.
			

	#Selected object's properties
		1. Selected object's properties are shown in Top-Right corner of the screen, which automatically updated.
		2. Selection can be changed in the sequence of the object formation as follow:
			a. 'p' -> Select previous object.
			b. 'n' -> Select next object.

	#Undo/Redo and deleting selected object
		1. 'z' -> Delete the last formed object and then its previous on further press.
		2. 'r' -> Recreate the object just deleted by 'd'.
		3. 'x' -> Delete the selected object. This change can't be Redo.
	


	
						% % FILES EXPLANATION % %
	1. main.cpp -> Its contain main functions, initializers and variables.
		
		# MAIN FUNCTIONS #
		
		a. nameOBJECT() 		-> Return object's name by its type variable.
		b. ResizeWin() 			-> Resize window with proper frustum transformed.
		c. initRendering() 		-> enable basic modes.
		d. Renderer() 			-> Main Rendering Function.
		e. update() 			-> Updates Screen on in fixed intervals.
		f. KeyFunction() 		-> Capture KeyBoard events and make changes as defined by developer.
		g. specialKeyFunction() -> Capture Special Keys (like Function keys) of KeyBoard and make changes
										 as defined by developer.
		h. mouseFunction() 		-> Capture MouseKey events to initialize various events.
		i. mouseMotion() 		-> Captures Mouse Position change.
		j. main() 				-> Program initiator.
	
	2. dat_stuct.h -> This header file contain the data structures for objects, camera and lights.
		
		a. object -> Defined to save all possible variables for a 3d-Object
			# serial_no		- A unique id, different for each object.
			# type			- States the type of object. (1->cube, 2->sphere, 3->cone, 4->torus, 5->teapot, 6->plane)
			# color[]		- Color of object.
			# position[]	- Position coordinates.
			# rotation[]	- Rotated angles.
			# scale[]		- Scale measures.
			# next			- Next object pointer.
			# pre			- Previous object pointer.
			
		b. camera -> Defined to save all possible variables for a camera
			# center[]		- Focus Point.
			# radius		- Distance of camera from center.
			# sideAngle		- Angle projection made by camera-vector with positive Z-axis in X-Z plane.
										(Anti-Clockwise as seen from Positive Y-axis)
			# upAngle		- Angle made by camera vector with Positive Y-axis.
			# up[]			- Up Vector of camera.
			
		c. light -> Defined to save all possible variables for a Lights.
			
	3. craete_object.h -> This header file create/initialize the objects like 3d-models, camera and lights.
										The all variables are given default values.
	
	4. object_draw.h -> This header file contain functions which help in realizing objects in the view port, i.e draw them.
	
	5. default_objects.h -> This header file's function create default objects like Base-Grid and different types of Gizmos.
	
	6. light.h -> This file help in enabling lights.
	
	7.text_info.h -> This file has function with help in creating text in the Top-Right side of the screen.
