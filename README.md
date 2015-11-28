# Modeling-Tool

###This is 3D Modelling tool with basic Models Like Cube, Sphere, Cone, Torus, Teapot and Plane

Codes with pre-compiled executable, all libraries and related files can be access through folowing link
https://drive.google.com/folderview?id=0B3rW_i_M0kWzb0FqVG9DQlhFc0E&usp=sharing

####ALL CONTROLES AND USERINTERFACE
#####1 DRAW OBJECTS
Click the button of object you wish to create, in right side. You can also right click, then select Objects option -> There are 7 types of object. 
If some object is selected, user can find the Object Properties Dropdown on Right side of screen. This will help change the variables related to the selcted object.

#####2 Lights
Right click then select Lights option -> There are 7 types of lights. 
On clicking any one of the lights, a input window will apear which can be used to change attributes related to the light. 
Light can be switched off by selcting the light in same way. 

#####3 Bezeir Curve
Right click then select Bezeir Curve. 

#####4 Bezier Surface
Right click then select Bezier Surface. 

#####5 Particle System
Right click then select Particle System option (a simple simulation of water using planes facing the camera). 

#####6 RE-POSITION / ROTATE / SCALE MODES
'q' -> Idle Mode. 
'w' -> Re-Position Mode. 
'e' -> Rotation Mode. 
'r' -> Scaling Mode. 

AFTER THAT

#####7 AXIS SELECTION
>Use three Input boxes in botton to change Position, rotation and Scale's corresponding X, Y or Z values. 

#####8 CAMERA TRANSFORM
>######8.1 DOLLY Camera
>>'[' -> ZoomIn. 
>>']' -> ZoomOut. 

>######8.2 TRUCK CAMEAR
>>RIGHT ARROW KEY -> Positive X-axis. 
>>LEFT ARROW KEY -> Negative X-axis. 
>>'.' -> Positive Y-axis. 
>>',' -> Negative Y-axis. 
>>UP ARROW KEY -> Positive Z-axis. 
>>LEFT ARROW KEY -> Negative Z-axis. 

>######8.3 ORBIT CAMERA
>>Hold MIDDLE MOUSE KEY and move the mouse. 

#####9 OBJECT SELECTION
'p' -> Select previous object. 
'n' -> Select next object. 

#####10 UNDO / REDO AND DELETE SELECTED OBJECT
'z' -> Delete the last available formed object. 
'y' -> Recreate the latest object deleted by 'd'. 

#####11 MATERIALS PROPERTIES
'm' -> If you have and object selected and want to change its material properties press. 
Now a new window will appear which will containt various inputs. You can change how object should look like by changing them.

#####12 HELP and OBJECT DISPLAY MODES
ONSCREEN HELP : F1
SMOOTH vs EDGY MODE : F2 -> Smooth to Edgy to Smooth
SOLID AND WIREFRAME : F3 Key -> Solid and Wireframe to Smooth to Solid and Wireframe
WIREFRAME : F4 Key -> Wireframe to Normal to Wireframe
MINECRAFT MODE : F5 Key -> Minecraft(Blocks) to Normal to Minecraft

1. Multiple objects can be drawn in any sequence and following properties are observed
>a. Any new objects are formed at origin, with zero rotation and scaled 1 in all direction.
>b. A Gizmo tool (Tool to reposition, rotate and scale in any axis) is observed to be automatically at the position of the presently drawn object.
>c. Red -> X-axis, Green -> Y-axis and Blue -> Z-axis.
	
### Properties of Gizmo and uses
1. Red -> X-axis, Green -> Y-axis and Blue -> Z-axis.
2. the Gizmo's functionality can be changed as following key, following Gizmo type.
>a. 'q' -> No tool selected.
>b. 'w' -> Re-positioning tool.
>c. 'e' -> Rotation tool.
>d. 'r' -> Scaling tool.
3. Now while switching to positioning, rotation and scaling Gizmo one might observe one of the 
axis being yellow color. This means that the axis is being selected to modify the object in that axis.
Axis can be switched by pressing 'd' in following sequence:
>a. X-axis to Y-axis to Z-axis
>b. X-axis is selected by default.

### Lighting
The software provide 8 lights:
a. LIGHT0 is on by default.
b. LIGHT1, LIGHT2, .... are off but can be On by selcting from right click menu. This makes LIGHT0 to switch Off.

### Camera Transform
1. DOLLY CAMERA - the camera zoom in or out.
This can be done by 
>a. '[' -> ZoomIn.
>b. ']' -> Zoom Out.

2. TRUCK CAMEAR - the Focusing point is moved.
>a. RIGHT ARROW KEY -> Positive X-axis.
>b. LEFT ARROW KEY -> Negative X-axis.
>c. '.' -> Positive Y-axis.
>d. ',' -> Negative Y-axis.
>e. UP ARROW KEY -> Positive Z-axis.
>f. LEFT ARROW KEY -> Negative Z-axis.

3. ORBIT CAMERA - the camera rotate about it Focusing point on a sphere of radius.
>This can be done by holding MIDDLE MOUSE KEY and moving the mouse.


### Selected object's properties
1. Selected object's properties are shown in Top-Right corner of the screen, which automatically updated.
2. Selection can be changed in the sequence of the object formation as follow:
>a. 'p' -> Select previous object.
>b. 'n' -> Select next object.

### Undo/Redo and deleting selected object
1. 'z' -> Delete the last formed object and then its previous on further press.
2. 'y' -> Recreate the object just deleted by 'd'.


####FILES EXPLANATION
1. main.cpp -> Its contain main functions, initializers and variables.

### MAIN FUNCTIONS

a. nameOBJECT() -> Return object's name by its type variable

b. ResizeWin() -> Resize window with proper frustum transformed

c. initRendering() -> enable basic modes

d. Renderer() -> Main Rendering Function

e. update() -> Updates Screen on in fixed intervals

f. KeyFunction() -> Capture KeyBoard events and make changes as defined by developer

g. specialKeyFunction() -> Capture Special Keys (like Function keys) of KeyBoard and make changes
as defined by developer

h. mouseFunction() -> Capture MouseKey events to initialize various events

i. mouseMotion() -> Captures Mouse Position change

j. main() -> Program initiator

2. dat_stuct.h -> This header file contain the data structures for objects, camera and lights

a. object -> Defined to save all possible variables for a 3d-Object

 serial_no - A unique id, different for each object

 type - States the type of object (1->cube, 2->sphere, 3->cone, 4->torus, 5->teapot, 6->plane)

 color[] - Color of object

 position[] - Position coordinates

 rotation[] - Rotated angles

 scale[] - Scale measures

 next - Next object pointer

 pre - Previous object pointer

b. camera -> Defined to save all possible variables for a camera

 center[] - Focus Point

 radius - Distance of camera from center

 sideAngle - Angle projection made by camera-vector with positive Z-axis in X-Z plane(Anti-Clockwise as seen from Positive Y-axis)

 upAngle - Angle made by camera vector with Positive Y-axis

 up[] - Up Vector of camera

c. light -> Defined to save all possible variables for a Lights

3. create_object.h -> This header file create/initialize the objects like 3d-models, camera and lights
The all variables are given default values

4. object_draw.h -> This header file contain functions which help in realizing objects in the view port, i.e draw them

5. default_objects.h -> This header file's function create default objects like Base-Grid and different types of Gizmos

6. light.h -> This file help in enabling lights

7.text_info.h -> This file has function with help in creating text in the Top-Right side of the screen
