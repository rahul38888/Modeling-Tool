#include <windows.h>
#include <stdio.h>
//#include <GL/glew.h>
#include <GL/glui.h>
//#include <GL/glut.h>
//#include <GL/gl.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>

//#include <cstring>
#include <iostream>
#include <sstream>

float scale_factor=100;
float cam_scale=100;

#include "plugin/dat_stuct.h"
#include "plugin/texture.h"
#include "plugin/splines.h"
#include "plugin/object.h"
#include "plugin/minecraft_mode.h"
#include "plugin/object_draw.h"
#include "plugin/create_object.h"
#include "plugin/default_objects.h"
#include "plugin/light.h"
#include "plugin/text_info.h"
#include "plugin/control_info.h"
#include "plugin/gravity_physics.h"
#include "plugin/save_file.h"
#include "plugin/load_file.h"
#include "plugin/shaderReader.h"

#include "shaders/shaderLoad.h"

#define PI 3.14159

#define SHRINK 1
#define NORMAL 2

GLuint _textureId;

char select_type;

struct object *temp;

int fillMenu, shrinkMenu, mainMenu, lightMenu, bezierType, fileMenu;

/*Camera Atributes*/
struct camera *cam=(struct camera*)malloc(sizeof(struct camera));

struct object *head;
struct object *tail;
struct object *selected;

struct emittor *emm;

int selected_light;

struct light *lght[8];
int turn_light=0;
int light_no;
int started_light=1;

int new_obj=0;
int started=1;
int type=5;
int serial_no=-1;
int l0=0, l1=0;
int sl=-1;
int isWired=0;
int isCam=0;

char transTool='n';
char transDim='x';
char camMode = 'o';

int deltaUp=0;
int deltaSide=0;
int deltaUpMode=0;
int deltaSideMode=0;

int gridMode=1;

int winW=1350;
int winH=690;

int winInW=200;
int winInH=200;

int textUpLimit=580;
int nurb=0, bezcrv=0, parf=0;

int viewport;
int controles=0;

int save_on=0;
int load_on=0;
char file_name[100] = "example.3d";

GLenum globalSmooth=GL_SMOOTH;

void cameraUpdate();
float xy_aspect;

GLUI_Panel *object_type, *object_info, *save_load;
GLUI_Button *cube, *sphere, *cone, *torus, *cylinder, *plane, *teapot;
GLUI_Button *cam_dolly, *cam_truck, *cam_orbit, *confirm, *cancel;
GLUI_StaticText *ob_name, *ob_serial, *ob_pos, *ob_rot, *ob_scal;
GLUI_Panel *transform_panel, *camera, *sl_panel, *mat_panel, *color_panel, *ambient_panel, *diffuse_panel, *specular_panel;
GLUI_Panel *lght_panel, *amb_lght, *dif_lght, *spe_lght, *pos_lght, *att_lght, *lght_panel0, *lght_panel1;
GLUI_Spinner *x_axis, *y_axis, *z_axis, *var1, *var2, *var3, *var4, *shininess;
GLUI *glui_right, *glui_bottom, *glui_top, *glui_left, *new_win=0, *new_win1=0, *mat_win=0, *lght_win=0;
GLUI_Checkbox *mat_enable, *smooth;
GLUI_Scrollbar *color0, *color1, *color2, *color3, *ambient0, *ambient1, *ambient2, *ambient3, *diffuse0, *diffuse1, *diffuse2, *diffuse3, *specular0, *specular1, *specular2, *specular3;
GLUI_Scrollbar *l_amb0,  *l_amb1, *l_amb2, *l_amb3, *l_spe0, *l_spe1, *l_spe2, *l_spe3, *l_dif0, *l_dif1, *l_dif2, *l_dif3;
GLUI_Spinner *l_pos0, *l_pos1, *l_pos2, *l_pos3, *l_att1;
GLUI_Checkbox *lght_enable, *l_att0;
GLUI_EditText *col0, *col1, *col2, *col3, *amb0, *amb1, *amb2, *amb3, *dif0, *dif1, *dif2, *dif3, *spe0, *spe1, *spe2, *spe3;
GLUI_EditText *amb_10, *amb_l1, *amb_l2, *amb_l3, *dif_l0, *dif_l1, *dif_l2, *dif_l3, *spe_l0, *spe_l1, *spe_l2, *spe_l3;
GLUI_EditText *file_nm;
GLUI_FileBrowser * browse;
GLUI_Rollout *obj_roll;

float x_var, y_var, z_var, vara, varb, varc, vard, testvar=0;
float c0, c1, c2, c3, a0, a1, a2, a3, d0, d1, d2, d3, s0, s1, s2, s3, sn, attn;
int me, st;
int enbl;

int button_w=65;
int spinner_w=0;
char slmode='l';

// Manage aspect Ratio on Resize Window
void ResizeWin(int w, int h){
    int tx, ty, tw, th;
    GLUI_Master.get_viewport_area( &tx, &ty, &tw, &th );
    glViewport( tx, ty, tw, th );

    xy_aspect = (float)tw / (float)th;

    //glutPostRedisplay();

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-xy_aspect,xy_aspect, -1.0, 1.0, 2.0f, 100000.0f);
    glMatrixMode(GL_MODELVIEW);
    //glLoadIdentity();
}

// Enabler Function before Rendering objects
void initRendering(){

    if ( glutGetWindow() != viewport )
    glutSetWindow(viewport);


    //glutPostRedisplay();

    glui_bottom->sync_live();
    glui_right->sync_live();

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    //glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);

    GLfloat values[2];
    glGetFloatv (GL_LINE_WIDTH_GRANULARITY, values);
    glGetFloatv (GL_LINE_WIDTH_RANGE, values);

    glEnable (GL_LINE_SMOOTH);
    glEnable (GL_BLEND);
    glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glHint (GL_LINE_SMOOTH_HINT, GL_DONT_CARE);
    glLineWidth (1);
}


void textInfo(){
    std::string text;
    glColor3f(1, 1, 0);

    if(transTool=='n'){
        text="Tool Selected - Null";
    }
    else if(transTool=='p'){
        text="Tool Selected - Position";
    }
    else if(transTool=='r'){
        text="Tool Selected - Rotation";
    }
    else if(transTool=='s'){
        text="Tool Selected - Scale";
    }
    drawText(text.data(), text.size(), 10,textUpLimit);

    text="Axis - ";
    drawText(text.data(), text.size(), 10,textUpLimit-20);

    if(transDim=='x'){
        glColor3f(1, 0, 0);
        text= "X";
    }

    else if(transDim=='y'){
        glColor3f(0, 1, 0);
        text="Y";
    }

    else if(transDim=='z'){
        glColor3f(0, 0, 1);
        text="Z";
    }
    drawText(text.data(), text.size(), 45,textUpLimit-20);

    if(selected!=NULL){
        object_info_show(selected);
    }
}

void createCamera(){
    if(isCam==0){
        create_camera(cam);
        isCam=1;
    }
    gluLookAt(cam->center[0]+cam->radius*sin(cam->upAngle*2*PI/360)*sin(cam->sideAngle*2*PI/360),
              cam->center[1]+cam->radius*cos(cam->upAngle*2*PI/360),
              cam->center[2]+cam->radius*sin(cam->upAngle*2*PI/360)*cos(cam->sideAngle*2*PI/360),
              cam->center[0],cam->center[1],cam->center[2],
              cam->up[0],cam->up[1],cam->up[2]);
}

void update_var(){
    if(selected!=NULL){
        if(transTool=='p'){
            selected->position[0] = x_axis->get_float_val();
            selected->position[1] = y_axis->get_float_val();
            selected->position[2] = z_axis->get_float_val();
        }
        else if(transTool=='r'){
            selected->rotation[0] = x_axis->get_float_val();
            selected->rotation[1] = y_axis->get_float_val();
            selected->rotation[2] = z_axis->get_float_val();
        }
        else if(transTool=='s'){
            selected->scale[0] = x_axis->get_float_val();
            selected->scale[1] = y_axis->get_float_val();
            selected->scale[2] = z_axis->get_float_val();
        }

        /** Variables **/
        if(selected->type==1){
            selected->variables[0] = var1->get_float_val();
            selected->variables[1] = var2->get_float_val();
            selected->variables[2] = var3->get_float_val();
            //glutSolidCube(obj->variable[0]);
            //drawSolidCuboid(obj);
        }
        else if(selected->type==2){
            selected->variables[0] = var1->get_float_val();
            selected->variables[1] = var2->get_int_val();
            selected->variables[2] = var3->get_int_val();
            //glutWireSphere(obj->variables[0],obj->variables[1],obj->variables[2]);
            //drawSolidSphere(obj);
        }
        else if(selected->type==3){
            selected->variables[0] = var1->get_float_val();
            selected->variables[1] = var2->get_float_val();
            selected->variables[2] = var3->get_int_val();
            selected->variables[3] = var4->get_int_val();
            //glutSolidCone(obj->variables[0],obj->variables[1],obj->variables[2],obj->variables[3]);
            //drawSolidCone(obj);
        }
        else if(selected->type==4){
            selected->variables[0] = var1->get_float_val();
            selected->variables[1] = var2->get_float_val();
            selected->variables[2] = var3->get_int_val();
            selected->variables[3] = var4->get_int_val();
            //glutSolidTorus(obj->variables[0],obj->variables[1],obj->variables[2],obj->variables[3]);
            //drawSolidTorus(obj);
        }
        else if(selected->type==5){
            selected->variables[0] = var1->get_float_val();
            selected->variables[1] = var2->get_float_val();
            selected->variables[2] = var3->get_int_val();
            selected->variables[3] = var4->get_int_val();
            //drawSolidCylinder(obj);
        }
        else if(selected->type==6){
            selected->variables[0] = var1->get_float_val();
            selected->variables[1] = var2->get_float_val();
            selected->variables[2] = var3->get_int_val();
            selected->variables[3] = var4->get_int_val();
            //drawSolidPlane(obj);
        }
        else if(selected->type==7){
            selected->variables[0] = var1->get_float_val();
            //glutSolidTeapot(obj->variables[0]);
        }
    }
}

void update_gui(){
    // Transformation
    if(selected!=NULL){

        obj_roll->enable();
        if(transTool=='p'){
            transform_panel->set_name("Translate");
            transform_panel->enable();

            /**** selected->position[0] = x_axis->get_float_val();
            selected->position[1] = y_axis->get_float_val();
            selected->position[2] = z_axis->get_float_val(); ****/

            x_axis->set_float_val(selected->position[0]);
            y_axis->set_float_val(selected->position[1]);
            z_axis->set_float_val(selected->position[2]);
        }
        else if(transTool=='r'){
            transform_panel->set_name("Rotate");
            transform_panel->enable();

            /**** selected->rotation[0] = x_axis->get_float_val();
            selected->rotation[1] = y_axis->get_float_val();
            selected->rotation[2] = z_axis->get_float_val(); ****/

            x_axis->set_float_val(selected->rotation[0]);
            y_axis->set_float_val(selected->rotation[1]);
            z_axis->set_float_val(selected->rotation[2]);
        }
        else if(transTool=='s'){
            transform_panel->set_name("Scale");
            transform_panel->enable();

            /**** selected->scale[0] = x_axis->get_float_val();
            selected->scale[1] = y_axis->get_float_val();
            selected->scale[2] = z_axis->get_float_val(); ****/

            x_axis->set_float_val(selected->scale[0]);
            y_axis->set_float_val(selected->scale[1]);
            z_axis->set_float_val(selected->scale[2]);

        }
        ob_name->set_text(nameType(selected->type));

        if(selected->type==1){
            //printf("%d", selected->type);

            var1->enable();
            var1->set_name("Length");
            var1->data_type = GLUI_SPINNER_FLOAT;
            var1->set_float_limits(1,20,GLUI_LIMIT_NONE);
            var1->set_float_val(selected->variables[0]);

            var2->enable();
            var2->set_name("Breadth");
            var2->data_type = GLUI_SPINNER_FLOAT;
            var2->set_float_limits(1,20,GLUI_LIMIT_NONE);
            var2->set_float_val(selected->variables[1]);

            var3->enable();
            var3->set_name("Height");
            var3->data_type = GLUI_SPINNER_INT;
            var3->set_int_limits(1,20,GLUI_LIMIT_NONE);
            var3->set_int_val(selected->variables[2]);

            var4->disable();
            var4->set_int_val(0);

            //printf("%d", selected->type);
        }
        else if(selected->type==2){
            var1->enable();
            var1->set_name("Radius");
            var1->data_type = GLUI_SPINNER_FLOAT;
            var1->set_float_limits(1,20,GLUI_LIMIT_NONE);
            var1->set_float_val(selected->variables[0]);

            var2->enable();
            var2->set_name("Rings");
            var2->data_type = GLUI_SPINNER_INT;
            var2->set_int_limits(3,200,GLUI_LIMIT_CLAMP);
            var2->set_int_val(selected->variables[1]);

            var3->enable();
            var3->set_name("Division");
            var3->data_type = GLUI_SPINNER_INT;
            var3->set_int_limits(3,200,GLUI_LIMIT_CLAMP);
            var3->set_int_val(selected->variables[2]);

            var4->disable();
            var4->set_int_val(0);
        }
        else if(selected->type==3){
            var1->enable();
            var1->set_name("Radius");
            var1->data_type = GLUI_SPINNER_FLOAT;
            var1->set_float_limits(1,20,GLUI_LIMIT_NONE);
            var1->set_float_val(selected->variables[0]);

            var2->enable();
            var2->set_name("Height");
            var2->data_type = GLUI_SPINNER_FLOAT;
            var2->set_float_limits(1,20,GLUI_LIMIT_NONE);
            var2->set_float_val(selected->variables[1]);

            var3->enable();
            var3->set_name("Rings");
            var3->data_type = GLUI_SPINNER_INT;
            var3->set_int_limits(1,200,GLUI_LIMIT_CLAMP);
            var3->set_int_val(selected->variables[2]);

            var4->enable();
            var3->set_name("Division");
            var4->data_type = GLUI_SPINNER_INT;
            var4->set_int_limits(3,200,GLUI_LIMIT_CLAMP);
            var4->set_int_val(selected->variables[3]);
        }
        else if(selected->type==4){
            var1->enable();
            var1->set_name("Radius1");
            var1->data_type = GLUI_SPINNER_FLOAT;
            var1->set_float_limits(1,20,GLUI_LIMIT_NONE);
            var1->set_float_val(selected->variables[0]);

            var2->enable();
            var2->set_name("Radius2");
            var2->data_type = GLUI_SPINNER_FLOAT;
            var2->set_float_limits(1,20,GLUI_LIMIT_NONE);
            var2->set_float_val(selected->variables[1]);

            var3->enable();
            var3->set_name("Rings");
            var3->data_type = GLUI_SPINNER_INT;
            var3->set_int_limits(3,200,GLUI_LIMIT_CLAMP);
            var3->set_int_val(selected->variables[2]);

            var4->enable();
            var3->set_name("Division");
            var4->data_type = GLUI_SPINNER_INT;
            var4->set_int_limits(3,200,GLUI_LIMIT_CLAMP);
            var4->set_int_val(selected->variables[3]);
        }
        else if(selected->type==5){
            var1->enable();
            var1->set_name("Radius");
            var1->data_type = GLUI_SPINNER_FLOAT;
            var1->set_float_limits(1,20,GLUI_LIMIT_NONE);
            var1->set_float_val(selected->variables[0]);

            var2->enable();
            var2->set_name("Height");
            var2->data_type = GLUI_SPINNER_FLOAT;
            var2->set_float_limits(1,20,GLUI_LIMIT_NONE);
            var2->set_float_val(selected->variables[1]);

            var3->enable();
            var3->set_name("Rings");
            var3->data_type = GLUI_SPINNER_INT;
            var3->set_int_limits(1,200,GLUI_LIMIT_CLAMP);
            var3->set_int_val(selected->variables[2]);

            var4->enable();
            var3->set_name("Division");
            var4->data_type = GLUI_SPINNER_INT;
            var4->set_int_limits(3,200,GLUI_LIMIT_CLAMP);
            var4->set_int_val(selected->variables[3]);
        }
        else if(selected->type==6){
            var1->enable();
            var1->set_name("Length");
            var1->data_type = GLUI_SPINNER_FLOAT;
            var1->set_float_limits(1,20,GLUI_LIMIT_NONE);
            var1->set_float_val(selected->variables[0]);

            var2->enable();
            var2->set_name("Breadth");
            var2->data_type = GLUI_SPINNER_FLOAT;
            var2->set_float_limits(1,20,GLUI_LIMIT_NONE);
            var2->set_float_val(selected->variables[1]);

            var3->enable();
            var3->set_name("Division 1");
            var3->data_type = GLUI_SPINNER_INT;
            var3->set_int_limits(1,200,GLUI_LIMIT_CLAMP);
            var3->set_int_val(selected->variables[2]);

            var4->enable();
            var3->set_name("Division 2");
            var4->data_type = GLUI_SPINNER_INT;
            var4->set_int_limits(1,200,GLUI_LIMIT_CLAMP);
            var4->set_int_val(selected->variables[3]);
        }
        else if(selected->type==7){
            var1->set_name("Size");
            var1->data_type = GLUI_SPINNER_FLOAT;
            var1->set_float_limits(1,20,GLUI_LIMIT_NONE);
            var1->set_float_val(selected->variables[0]);
            var1->enable();

            var2->disable();
            var2->set_float_val(0);

            var3->disable();
            var3->set_int_val(0);

            var4->disable();
            var4->set_int_val(0);
        }

        if(mat_win!=0){
            struct materialType * matt = selected->mat;

            c0 = matt->color[0];
            c1 = matt->color[1];
            c2 = matt->color[2];
            c3 = matt->color[3];

            a0 = matt->mat_ambient[0];
            a1 = matt->mat_ambient[1];
            a2 = matt->mat_ambient[2];
            a3 = matt->mat_ambient[3];

            d0 = matt->mat_diffuse[0];
            d1 = matt->mat_diffuse[1];
            d2 = matt->mat_diffuse[2];
            d3 = matt->mat_diffuse[3];

            s0 = matt->mat_specular[0];
            s1 = matt->mat_specular[1];
            s2 = matt->mat_specular[2];
            s3 = matt->mat_specular[3];

            sn = matt->mat_shininess;

            col0->set_float_val(c0);
            col1->set_float_val(c1);
            col2->set_float_val(c2);
            col3->set_float_val(c3);

            amb0->set_float_val(a0);
            amb1->set_float_val(a1);
            amb2->set_float_val(a2);
            amb3->set_float_val(a3);

            dif0->set_float_val(d0);
            dif1->set_float_val(d1);
            dif2->set_float_val(d2);
            dif3->set_float_val(d3);

            spe0->set_float_val(s0);
            spe1->set_float_val(s1);
            spe2->set_float_val(s2);
            spe3->set_float_val(s3);
        }

    }
    else{
        x_axis->set_float_val(0);
        y_axis->set_float_val(0);
        z_axis->set_float_val(0);
        transform_panel->disable();

        ob_name->set_text("Type : ");
        ob_serial->set_text("Serial No. :");
        ob_pos->set_text("Position : ");
        ob_rot->set_text("Rotate : ");
        ob_scal->set_text("Scale : ");

        obj_roll->disable();
        var1->set_name("Variable-1");
        var2->set_name("Variable-2");
        var3->set_name("Variable-3");
        var3->set_name("Variable-4");

        var1->set_float_val(0);
        var2->set_float_val(0);
        var3->set_int_val(0);
        var4->set_int_val(0);

    }

    if(lght_win!=0){
        lght_enable->set_int_val(lght[selected_light]->on);

        /** Position **/
        l_pos0->set_float_val(lght[selected_light]->light_position[0]);
        l_pos1->set_float_val(lght[selected_light]->light_position[1]);
        l_pos2->set_float_val(lght[selected_light]->light_position[2]);
        l_pos3->set_float_val(lght[selected_light]->light_position[3]);

        /** Ambient **/
        l_amb0->set_float_val(lght[selected_light]->light_ambient[0]);
        l_amb1->set_float_val(lght[selected_light]->light_ambient[1]);
        l_amb2->set_float_val(lght[selected_light]->light_ambient[2]);
        l_amb3->set_float_val(lght[selected_light]->light_ambient[3]);

        amb_10->set_float_val(lght[selected_light]->light_ambient[0]);
        amb_l1->set_float_val(lght[selected_light]->light_ambient[1]);
        amb_l2->set_float_val(lght[selected_light]->light_ambient[2]);
        amb_l3->set_float_val(lght[selected_light]->light_ambient[3]);

        /** Diffuse **/
        l_dif0->set_float_val(lght[selected_light]->light_diffuse[0]);
        l_dif1->set_float_val(lght[selected_light]->light_diffuse[1]);
        l_dif2->set_float_val(lght[selected_light]->light_diffuse[2]);
        l_dif3->set_float_val(lght[selected_light]->light_diffuse[3]);

        dif_l0->set_float_val(lght[selected_light]->light_diffuse[0]);
        dif_l1->set_float_val(lght[selected_light]->light_diffuse[1]);
        dif_l2->set_float_val(lght[selected_light]->light_diffuse[2]);
        dif_l3->set_float_val(lght[selected_light]->light_diffuse[3]);

        /** Specular **/
        l_spe0->set_float_val(lght[selected_light]->light_specular[0]);
        l_spe1->set_float_val(lght[selected_light]->light_specular[1]);
        l_spe2->set_float_val(lght[selected_light]->light_specular[2]);
        l_spe3->set_float_val(lght[selected_light]->light_specular[3]);

        spe_l0->set_float_val(lght[selected_light]->light_specular[0]);
        spe_l1->set_float_val(lght[selected_light]->light_specular[1]);
        spe_l2->set_float_val(lght[selected_light]->light_specular[2]);
        spe_l3->set_float_val(lght[selected_light]->light_specular[3]);

        /** Attinuation **/
        //l_att0->set_int_val(lght[selected_light]->light_attenuation[0]);
        l_att1->set_float_val(lght[selected_light]->light_attenuation[1]);

    }

}

// Main Rendering function
void Renderer(){
    glClearColor(0.3f, 0.3f, 0.3f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    if(started_light){
        for(int i=0;i<8;i++){
            //printf("e");
            lght[i]=(struct light*)malloc(sizeof(struct light));
            create_light(lght[i],i);
            lght[i]->on=0;
        }
        lght[0]->on=1;
        emm=(struct emittor *)malloc(sizeof(struct emittor));
        create_emittor(emm,1);

        started_light=0;
    }

    // Object List
    if(new_obj){
        serial_no++;
        if(!started){
            tail->next=(struct object *)malloc(sizeof(struct object));
            temp=tail->next;
            temp->pre=tail;
            tail=temp;
            selected=tail;
            create_object(tail,type,serial_no);
            update_gui();
        }
        else{
            head=(struct object *)malloc(sizeof(struct object));
            create_object(head,type,serial_no);
            tail=head;
            selected=tail;
            head->pre=NULL;
            started=0;
            update_gui();
        }
        new_obj=0;
    }

    /**** Camera Transform of World ****/
    createCamera();
    cam_scale = cam->radius/7;

    /**** Lights Shader ****/
    draw_light(lght,globalSmooth);
    //loadShader();

    /**** Nurbs ****/
    if(nurb) draw_nurbs();

    /**** Bezier Curve ****/
    if(bezcrv){
        glPushMatrix();
            glColor3f(0.5,0.5,0);
            if(isWired==1 || isWired==2) bezierWireCurve();
            if(isWired==0 || isWired==2) bezierSolidCurve();
        glPopMatrix();
    }

    /**** Particle fountain ****/
    if(parf) render_fountain(emm,cam);

    /**** Draw Objects ****/
    transformer_tool(selected,transTool,transDim);
    if(gridMode) base_grid();

    temp=head;
    if(head!=NULL && tail!=NULL){
        do
        {
            object_draw(temp,selected,isWired,globalSmooth);
            temp=temp->next;
        }while(temp!=tail->next);
    }

    update_var();
    //update_gui();

    //draw_circle(2,32);
    //animation();

    /**** Text Information ****/
    textInfo();
    if(controles) writeControles();
    //deleteShader();

    glui_right->sync_live();
    glui_bottom->sync_live();
    if(new_win!=0){
        new_win->sync_live();
    }
    if(mat_win!=0){
        mat_win->sync_live();
    }

    glutSwapBuffers();
}

/**** Loop Repeate timer ****/
void update(int value){
    glutPostRedisplay();
    glutTimerFunc(50,update,0);
}

// Basic MouseButton Function
void mouseFunction(int button, int state, int x, int y){

    int mod = glutGetModifiers();
    if(state== GLUT_DOWN){
        if(button==GLUT_MIDDLE_BUTTON){
            switch(mod){
                case GLUT_ACTIVE_ALT:
                    deltaUpMode=1;
                    deltaSideMode=1;
                break;
            }
        }
        if(button==GLUT_LEFT_BUTTON){
            if(transDim=='x') transDim='y';
            else if(transDim=='y') transDim='z';
            else transDim='x';
        }
    }
    else if(state== GLUT_UP){
        if(button==GLUT_MIDDLE_BUTTON){
            deltaUpMode=0;
            deltaSideMode=0;
        }
    }
}

// Mouse Movement Function
void mouseMotion(int x, int y){

        if(deltaUpMode){
            if(deltaUp<y){
                    cam->upAngle = cam->upAngle - y*0.005f;
                    if(cam->upAngle<0.1f){
                        cam->upAngle=0.1f;
                    }
            }
            else if(deltaUp>y){
                    cam->upAngle = cam->upAngle + y*0.005f;
                    if(cam->upAngle>179.1f){
                        cam->upAngle=179.1f;
                    }
            }

            deltaUp=y;
        }

        if(deltaSideMode){
            if(deltaSide<x){
                    cam->sideAngle = cam->sideAngle - x*0.002f;
                    if(cam->sideAngle<0){
                        cam->sideAngle=355.0f;
                    }
            }
            else if(deltaSide>x){
                    cam->sideAngle = cam->sideAngle + x*0.002f;
                    if(cam->sideAngle>360){
                        cam->sideAngle=5.0f;
                    }
            }
            deltaSide=x;
        }
}

void object_control(GLUI_Control* option){

    switch (option->get_id()) {
		case 1:
            new_obj=1;
            type=1;
        break;
        case 2:
            new_obj=1;
            type=2;
        break;
        case 3:
            new_obj=1;
            type=3;
        break;
        case 4:
            new_obj=1;
            type=4;
        break;
        case 5:
            new_obj=1;
            type=5;
        break;
        case 6:
            new_obj=1;
            type=6;
        break;
        case 7:
            new_obj=1;
            type=7;
        break;
	}

}

void exit_err(GLUI_Control *option){
        new_win1->close();
}

void error_msg(int option){
    switch(option){

        case 1:{
            new_win1 = GLUI_Master.create_glui( "Load", 0, 600, 300 );

            new GLUI_StaticText(new_win1," ");
            new GLUI_StaticText(new_win1,"      File Name Column is blank.      ");
            new GLUI_StaticText(new_win1,"      Please Type File name!      ");
            new GLUI_StaticText(new_win1," ");
            new GLUI_Button(new_win1,"Ok", 1, exit_err);
        }
        break;

        case 2:{
            new_win1 = GLUI_Master.create_glui( "Load", 0, 600, 300 );

            new GLUI_StaticText(new_win1," ");
            new GLUI_StaticText(new_win1,"      This file does not exist.     ");
            new GLUI_StaticText(new_win1," ");
            new GLUI_Button(new_win1,"Ok", 1, exit_err);
        }
        break;

    }
}

void load_file(FILE *file){

    head=NULL;
    tail=NULL;
    selected=NULL;

    float num[50];
    char buff[100];
    started=1;


    fscanf(file, "%s", buff);
    while(buff[0]!='#'){

        num[0]=atof(buff);
        //printf("%f ", num[0]);

        if(num[0]==1 || num[0]==2){
            for(int i=1;i<30;i++){
                fscanf(file, "%s", buff);

                num[i] = atof(buff);
                //printf("%f ", num[i]);
            }
        }
        else if(num[0]==3 || num[0]==4 || num[0]==5 || num[0]==6){
            for(int i=1;i<31;i++){
                fscanf(file, "%s", buff);

                num[i] = atof(buff);
                //printf("%f ", num[i]);
            }
        }
        else if(num[0]==7){
            for(int i=1;i<28;i++){
                fscanf(file, "%s", buff);

                num[i] = atof(buff);
                //printf("%f ", num[i]);
            }
        }
        //printf("%\n");

        if(started){
            head=(struct object *)malloc(sizeof(struct object));
            tail=head;
            selected=tail;
            head->pre=NULL;
            tail=head;
            //printf("h ");
            file_loader(num,tail,cam,lght[0],1);
            started=0;
        }
        else{
            tail->next=(struct object *)malloc(sizeof(struct object));
            temp=tail->next;
            temp->pre=tail;
            tail=temp;
            //printf("n ");
            selected=tail;
            file_loader(num,tail,cam,lght[0],1);
        }

        fscanf(file, "%s", buff);
    }
    //printf("%\n");

    /*** For Camera ***/
    for(int i=0;i<9;i++){
        fscanf(file, "%s", buff);
        num[i]=atof(buff);
        //printf("%f ", num[i]);
    }
    file_loader(num,tail,cam,lght[0],2);
    fscanf(file, "%s", buff);
    //printf("%\n");

    /*** For Lights ***/
    struct light *lastl;
    for(int i=0;i<8;i++){
        for(int i=0;i<16;i++){
            fscanf(file, "%s", buff);
            num[i]=atof(buff);
            //printf("%f ", num[i]);
        }
        //printf("%\n");
        lastl=lght[i];
        file_loader(num,tail,cam,lastl,3);
    }
}


void saveOrLoad(GLUI_Control *option){

    if(option->get_id() == 1){
            if(slmode=='l'){

                FILE *file;
                if(file_nm->get_text()==NULL){
                    error_msg(1);
                }
                else{
                    file = fopen(file_name, "r");
                    if(file==NULL){
                        error_msg(2);
                    }
                    else{
                            load_file(file);

                            fclose(file);
                            new_win->close();
                            new_win=0;
                    }
                }
            }
            else if(slmode=='s'){
                if(file_nm->get_text()==NULL){
                    error_msg(1);
                }
                else{
                    file_saver(head, tail, cam,lght,file_name);

                    new_win->close();
                    new_win=0;
                }
            }
    }
    else if(option->get_id()==2)
    {
        new_win->close();
        new_win=NULL;
    }
}

void lightCB(GLUI_Control *option){

    switch(option->get_id()){
        case 0:{
            if(enbl){
                lght[selected_light]->on=1;
                pos_lght->enable();
                lght_panel1->enable();

            }
            else{
                lght[selected_light]->on=0;
                pos_lght->disable();
                lght_panel1->disable();
            }
        }
        break;
        case 1:{
            lght[selected_light]->light_position[0] = l_pos0->get_float_val();
            lght[selected_light]->light_position[1] = l_pos1->get_float_val();
            lght[selected_light]->light_position[2] = l_pos2->get_float_val();
            lght[selected_light]->light_position[3] = l_pos3->get_float_val();
        }
        break;
        case 2:{
            lght[selected_light]->light_ambient[0] = l_amb0->get_float_val();
            lght[selected_light]->light_ambient[1] = l_amb1->get_float_val();
            lght[selected_light]->light_ambient[2] = l_amb2->get_float_val();
            lght[selected_light]->light_ambient[3] = l_amb3->get_float_val();

            amb_10->set_float_val(lght[selected_light]->light_ambient[0]);
            amb_l1->set_float_val(lght[selected_light]->light_ambient[1]);
            amb_l2->set_float_val(lght[selected_light]->light_ambient[2]);
            amb_l3->set_float_val(lght[selected_light]->light_ambient[3]);
        }
        break;
        case 3:{
            lght[selected_light]->light_diffuse[0] = l_dif0->get_float_val();
            lght[selected_light]->light_diffuse[1] = l_dif1->get_float_val();
            lght[selected_light]->light_diffuse[2] = l_dif2->get_float_val();
            lght[selected_light]->light_diffuse[3] = l_dif3->get_float_val();

            dif_l0->set_float_val(lght[selected_light]->light_diffuse[0]);
            dif_l1->set_float_val(lght[selected_light]->light_diffuse[1]);
            dif_l2->set_float_val(lght[selected_light]->light_diffuse[2]);
            dif_l3->set_float_val(lght[selected_light]->light_diffuse[3]);
        }
        break;
        case 4:{
            lght[selected_light]->light_specular[0] = l_spe0->get_float_val();
            lght[selected_light]->light_specular[1] = l_spe1->get_float_val();
            lght[selected_light]->light_specular[2] = l_spe2->get_float_val();
            lght[selected_light]->light_specular[3] = l_spe3->get_float_val();

            spe_l0->set_float_val(lght[selected_light]->light_specular[0]);
            spe_l1->set_float_val(lght[selected_light]->light_specular[1]);
            spe_l2->set_float_val(lght[selected_light]->light_specular[2]);
            spe_l3->set_float_val(lght[selected_light]->light_specular[3]);
        }
        break;
        case 5:{
            lght[selected_light]->light_attenuation[1] = l_att1->get_float_val();
        }
        break;
        case 6:{
            lght_win->close();
            lght_win=0;
        }
        break;
    }

}

void materialCb(GLUI_Control *option){

    switch(option->get_id()){

        /** Material Enable **/
        case 1:{
            struct materialType *matt = selected->mat;
            matt->matEnable = me;
        }
        break;
        /** Smoothness **/
        case 2:{
            struct materialType *matt = selected->mat;
            matt->smooth= st;
        }
        break;
        /** Color **/
        case 3:{
            if(selected!=NULL){
                struct materialType *matt = selected->mat;
                matt->color[0] = c0;
                matt->color[1] = c1;
                matt->color[2] = c2;
                matt->color[3] = c3;

                col0->set_float_val(c0);
                col1->set_float_val(c1);
                col2->set_float_val(c2);
                col3->set_float_val(c3);
            }
        }
            break;

        /** Ambient **/
        case 4:{
            if(selected!=NULL){
                struct materialType *matt = selected->mat;
                matt->mat_ambient[0] = a0;
                matt->mat_ambient[1] = a1;
                matt->mat_ambient[2] = a2;
                matt->mat_ambient[3] = a3;

                amb0->set_float_val(a0);
                amb1->set_float_val(a1);
                amb2->set_float_val(a2);
                amb3->set_float_val(a3);
            }
        }
            break;

        /** Diffuse **/
        case 5:{
            if(selected!=NULL){
                struct materialType *matt = selected->mat;
                matt->mat_diffuse[0] = d0;
                matt->mat_diffuse[1] = d1;
                matt->mat_diffuse[2] = d2;
                matt->mat_diffuse[3] = d3;

                dif0->set_float_val(d0);
                dif1->set_float_val(d1);
                dif2->set_float_val(d2);
                dif3->set_float_val(d3);
            }
        }
            break;

        /** Specular **/
        case 6:{
            if(selected!=NULL){
                struct materialType *matt = selected->mat;
                matt->mat_specular[0] = s0;
                matt->mat_specular[1] = s1;
                matt->mat_specular[2] = s2;
                matt->mat_specular[3] = s3;

                spe0->set_float_val(s0);
                spe1->set_float_val(s1);
                spe2->set_float_val(s2);
                spe3->set_float_val(s3);
            }
        }
            break;

        /** Shininess **/
        case 8:{
            if(selected!=NULL){
                struct materialType *matt = selected->mat;
                matt->mat_shininess = sn;
            }
        }
            break;

        case 7:
            mat_win->close();
            mat_win=0;
        break;

    }
}

void browseCB(GLUI_Control *option){
    file_nm->set_text(browse->get_file());
}

void pop_window(char option){
    switch(option){

        case 'l':{
            new_win = GLUI_Master.create_glui( "Load", 0, 400, 200 );

            browse = new GLUI_FileBrowser(new_win, "Files", GLUI_PANEL_EMBOSSED,1,browseCB);
            browse->set_w( 400 );

            file_nm = new GLUI_EditText(new_win, "File Name", file_name);
            file_nm->set_w( 400 );
            browse->set_h(200);

            sl_panel = new GLUI_Panel(new_win,"", GLUI_PANEL_NONE);
            confirm = new GLUI_Button(sl_panel, "Load", 1, saveOrLoad);
            new GLUI_Column(sl_panel, false);
            cancel = new GLUI_Button(sl_panel, "Cancel", 2, saveOrLoad);

            new_win->set_main_gfx_window( viewport );
        }
        break;

        case 's':{
            new_win = GLUI_Master.create_glui( "Save", 0, 400, 200 );

            browse = new GLUI_FileBrowser(new_win, "Files", GLUI_PANEL_EMBOSSED,1,browseCB);
            browse->set_w( 400 );
            browse->set_h(200);

            file_nm = new GLUI_EditText(new_win, "File Name", file_name);
            file_nm->set_w( 400 );

            sl_panel = new GLUI_Panel(new_win,"", GLUI_PANEL_NONE);
            confirm = new GLUI_Button(sl_panel, "Save", 1, saveOrLoad);
            new GLUI_Column(sl_panel, false);
            cancel = new GLUI_Button(sl_panel, "Cancel", 2, saveOrLoad);

            new_win->set_main_gfx_window( viewport );
        }
        break;

    }
}

void info(){

    object_info = new GLUI_Panel(glui_right,"Info");
    object_info->set_w( 163 );

    ob_name = new GLUI_StaticText(object_info,"Type : ");
    ob_serial = new GLUI_StaticText(object_info,"Serial No. :");
    ob_pos = new GLUI_StaticText(object_info,"Position : ");
    ob_rot = new GLUI_StaticText(object_info,"Rotate : ");
    ob_scal = new GLUI_StaticText(object_info,"Scale : ");

    //object_info->set_name("Try");

}

void light_prop(){
    if(selected_light==1) lght_win = GLUI_Master.create_glui( "Light-1 Properties", 0, 500, 200 );
    else if(selected_light==2) lght_win = GLUI_Master.create_glui( "Light-2 Properties", 0, 500, 200 );
    else if(selected_light==3) lght_win = GLUI_Master.create_glui( "Light-3 Properties", 0, 500, 200 );
    else if(selected_light==4) lght_win = GLUI_Master.create_glui( "Light-4 Properties", 0, 500, 200 );
    else if(selected_light==5) lght_win = GLUI_Master.create_glui( "Light-5 Properties", 0, 500, 200 );
    else if(selected_light==6) lght_win = GLUI_Master.create_glui( "Light-6 Properties", 0, 500, 200 );
    else if(selected_light==7) lght_win = GLUI_Master.create_glui( "Light-7 Properties", 0, 500, 200 );

    lght_panel = new GLUI_Panel(lght_win,"", GLUI_PANEL_NONE);
        lght_enable = new GLUI_Checkbox(lght_panel,"Enabled", &enbl, 0, lightCB);

    lght_panel0 = new GLUI_Panel(lght_panel, "", GLUI_PANEL_NONE);
        pos_lght = new GLUI_Panel(lght_panel0,"Position");
            l_pos0 = new GLUI_Spinner(pos_lght, "X",GLUI_SPINNER_FLOAT, 1, lightCB);
            l_pos1 = new GLUI_Spinner(pos_lght, "Y",GLUI_SPINNER_FLOAT, 1, lightCB);
            l_pos2 = new GLUI_Spinner(pos_lght, "Z",GLUI_SPINNER_FLOAT, 1, lightCB);
            l_pos3 = new GLUI_Spinner(pos_lght, "F",GLUI_SPINNER_FLOAT, 1, lightCB);

    lght_panel1 = new GLUI_Panel(lght_panel, "", GLUI_PANEL_NONE);
        amb_lght = new GLUI_Panel(lght_panel1,"Ambient");
            amb_10 = new GLUI_EditText(amb_lght,"Red",GLUI_EDITTEXT_FLOAT,2,lightCB);
            amb_l1 = new GLUI_EditText(amb_lght,"Green",GLUI_EDITTEXT_FLOAT,2,lightCB);
            amb_l2 = new GLUI_EditText(amb_lght,"Blue",GLUI_EDITTEXT_FLOAT,2,lightCB);
            amb_l3 = new GLUI_EditText(amb_lght,"Alpha",GLUI_EDITTEXT_FLOAT,2,lightCB);

            new GLUI_Column( amb_lght, false );
            l_amb0 = new GLUI_Scrollbar(amb_lght,"Red", GLUI_SCROLL_HORIZONTAL, &c0, 2, lightCB);
            l_amb1 = new GLUI_Scrollbar(amb_lght,"Green", GLUI_SCROLL_HORIZONTAL, &c1, 2, lightCB);
            l_amb2 = new GLUI_Scrollbar(amb_lght,"Blue", GLUI_SCROLL_HORIZONTAL, &c2, 2, lightCB);
            l_amb3 = new GLUI_Scrollbar(amb_lght,"Alpha", GLUI_SCROLL_HORIZONTAL, &c3, 2, lightCB);

        dif_lght = new GLUI_Panel(lght_panel1,"Diffuse");
            dif_l0 = new GLUI_EditText(dif_lght,"Red",GLUI_EDITTEXT_FLOAT,3,lightCB);
            dif_l1 = new GLUI_EditText(dif_lght,"Green",GLUI_EDITTEXT_FLOAT,3,lightCB);
            dif_l2 = new GLUI_EditText(dif_lght,"Blue",GLUI_EDITTEXT_FLOAT,3,lightCB);
            dif_l3 = new GLUI_EditText(dif_lght,"Alpha",GLUI_EDITTEXT_FLOAT,3,lightCB);

            new GLUI_Column( dif_lght, false );
            l_dif0 = new GLUI_Scrollbar(dif_lght,"Red", GLUI_SCROLL_HORIZONTAL, &a0, 3, lightCB);
            l_dif1 = new GLUI_Scrollbar(dif_lght,"Green", GLUI_SCROLL_HORIZONTAL, &a1, 3, lightCB);
            l_dif2 = new GLUI_Scrollbar(dif_lght,"Blue", GLUI_SCROLL_HORIZONTAL, &a2, 3, lightCB);
            l_dif3 = new GLUI_Scrollbar(dif_lght,"Alpha", GLUI_SCROLL_HORIZONTAL, &a3, 3, lightCB);


        new GLUI_Column( lght_panel1, false );
        spe_lght = new GLUI_Panel(lght_panel1,"Specular");
            spe_l0 = new GLUI_EditText(spe_lght,"Red",GLUI_EDITTEXT_FLOAT,4,lightCB);
            spe_l1 = new GLUI_EditText(spe_lght,"Green",GLUI_EDITTEXT_FLOAT,4,lightCB);
            spe_l2 = new GLUI_EditText(spe_lght,"Blue",GLUI_EDITTEXT_FLOAT,4,lightCB);
            spe_l3 = new GLUI_EditText(spe_lght,"Alpha",GLUI_EDITTEXT_FLOAT,4,lightCB);

            new GLUI_Column( spe_lght, false );
            l_spe0 = new GLUI_Scrollbar(spe_lght,"Red", GLUI_SCROLL_HORIZONTAL, &d0, 4, lightCB);
            l_spe1 = new GLUI_Scrollbar(spe_lght,"Green", GLUI_SCROLL_HORIZONTAL, &d1, 4, lightCB);
            l_spe2 = new GLUI_Scrollbar(spe_lght,"Blue", GLUI_SCROLL_HORIZONTAL, &d2, 4, lightCB);
            l_spe3 = new GLUI_Scrollbar(spe_lght,"Alpha", GLUI_SCROLL_HORIZONTAL, &d3, 4, lightCB);

        att_lght = new GLUI_Panel(lght_panel1, "Attenuation");
            //l_att0 = new GLUI_Checkbox(att_lght, "Enabled", &attn, 5, lightCB);
            l_att1 = new GLUI_Spinner(att_lght, "Value", GLUI_SPINNER_FLOAT, 5, lightCB);

    new GLUI_Button(lght_win, "Exit", 6, lightCB);

    update_gui();

}

void obj_material(){
    mat_win = GLUI_Master.create_glui( "Material Properties", 0, 500, 200 );

    mat_panel = new GLUI_Panel(mat_win,"", GLUI_PANEL_NONE);

    //mat_win->add_checkbox("Enable Material", &testvar, 1, materialCb);
    //mat_win->add_checkbox_to_panel(mat_panel, "Smooth", &testvar, 2, materialCb);

    //mat_enable = new GLUI_Checkbox(mat_panel, "Enable Material", &testvar, 1, materialCb);
    //smooth = new GLUI_Checkbox(mat_panel, "Smooth", &testvar, 2, materialCb);

    color_panel = new GLUI_Panel(mat_panel,"Color");
        col0 = new GLUI_EditText(color_panel,"Red",GLUI_EDITTEXT_FLOAT,3,materialCb);
        col1 = new GLUI_EditText(color_panel,"Green",GLUI_EDITTEXT_FLOAT,3,materialCb);
        col2 = new GLUI_EditText(color_panel,"Blue",GLUI_EDITTEXT_FLOAT,3,materialCb);
        col3 = new GLUI_EditText(color_panel,"Alpha",GLUI_EDITTEXT_FLOAT,3,materialCb);

        new GLUI_Column( color_panel, false );
        color0 = new GLUI_Scrollbar(color_panel,"Red", GLUI_SCROLL_HORIZONTAL, &c0, 3, materialCb);
        color1 = new GLUI_Scrollbar(color_panel,"Green", GLUI_SCROLL_HORIZONTAL, &c1, 3, materialCb);
        color2 = new GLUI_Scrollbar(color_panel,"Blue", GLUI_SCROLL_HORIZONTAL, &c2, 3, materialCb);
        color3 = new GLUI_Scrollbar(color_panel,"Alpha", GLUI_SCROLL_HORIZONTAL, &c3, 3, materialCb);

    ambient_panel = new GLUI_Panel(mat_panel,"Ambient");
        amb0 = new GLUI_EditText(ambient_panel,"Red",GLUI_EDITTEXT_FLOAT,4,materialCb);
        amb1 = new GLUI_EditText(ambient_panel,"Green",GLUI_EDITTEXT_FLOAT,4,materialCb);
        amb2 = new GLUI_EditText(ambient_panel,"Blue",GLUI_EDITTEXT_FLOAT,4,materialCb);
        amb3 = new GLUI_EditText(ambient_panel,"Alpha",GLUI_EDITTEXT_FLOAT,4,materialCb);

        new GLUI_Column( ambient_panel, false );
        ambient0 = new GLUI_Scrollbar(ambient_panel,"Red", GLUI_SCROLL_HORIZONTAL, &a0, 4, materialCb);
        ambient1 = new GLUI_Scrollbar(ambient_panel,"Green", GLUI_SCROLL_HORIZONTAL, &a1, 4, materialCb);
        ambient2 = new GLUI_Scrollbar(ambient_panel,"Blue", GLUI_SCROLL_HORIZONTAL, &a2, 4, materialCb);
        ambient3 = new GLUI_Scrollbar(ambient_panel,"Alpha", GLUI_SCROLL_HORIZONTAL, &a3, 4, materialCb);

    shininess = new GLUI_Spinner(mat_panel, "Shininess", GLUI_SPINNER_FLOAT, &sn, 8, materialCb);

    new GLUI_Column( mat_panel, false );
    diffuse_panel = new GLUI_Panel(mat_panel,"Diffuse");
        dif0 = new GLUI_EditText(diffuse_panel,"Red",GLUI_EDITTEXT_FLOAT,5,materialCb);
        dif1 = new GLUI_EditText(diffuse_panel,"Green",GLUI_EDITTEXT_FLOAT,5,materialCb);
        dif2 = new GLUI_EditText(diffuse_panel,"Blue",GLUI_EDITTEXT_FLOAT,5,materialCb);
        dif3 = new GLUI_EditText(diffuse_panel,"Alpha",GLUI_EDITTEXT_FLOAT,5,materialCb);

        new GLUI_Column( diffuse_panel, false );
        diffuse0 = new GLUI_Scrollbar(diffuse_panel,"Red", GLUI_SCROLL_HORIZONTAL, &d0, 5, materialCb);
        diffuse1 = new GLUI_Scrollbar(diffuse_panel,"Green", GLUI_SCROLL_HORIZONTAL, &d1, 5, materialCb);
        diffuse2 = new GLUI_Scrollbar(diffuse_panel,"Blue", GLUI_SCROLL_HORIZONTAL, &d2, 5, materialCb);
        diffuse3 = new GLUI_Scrollbar(diffuse_panel,"Alpha", GLUI_SCROLL_HORIZONTAL, &d3, 5, materialCb);

    specular_panel = new GLUI_Panel(mat_panel,"Specular");
        spe0 = new GLUI_EditText(specular_panel,"Red",GLUI_EDITTEXT_FLOAT,3,materialCb);
        spe1 = new GLUI_EditText(specular_panel,"Green",GLUI_EDITTEXT_FLOAT,3,materialCb);
        spe2 = new GLUI_EditText(specular_panel,"Blue",GLUI_EDITTEXT_FLOAT,3,materialCb);
        spe3 = new GLUI_EditText(specular_panel,"Alpha",GLUI_EDITTEXT_FLOAT,3,materialCb);

        new GLUI_Column( specular_panel, false );
        specular0 = new GLUI_Scrollbar(specular_panel,"Red", GLUI_SCROLL_HORIZONTAL, &s0, 6, materialCb);
        specular1 = new GLUI_Scrollbar(specular_panel,"Green", GLUI_SCROLL_HORIZONTAL, &s1, 6, materialCb);
        specular2 = new GLUI_Scrollbar(specular_panel,"Blue", GLUI_SCROLL_HORIZONTAL, &s2, 6, materialCb);
        specular3 = new GLUI_Scrollbar(specular_panel,"Alpha", GLUI_SCROLL_HORIZONTAL, &s3, 6, materialCb);

    new GLUI_Button(mat_win, "Exit", 7, materialCb);

    update_gui();

}

void obj_edit(){
    obj_roll = new GLUI_Rollout(glui_right,"Object",false,GLUI_PANEL_EMBOSSED);
    obj_roll->set_w( 163 );

    var1 = new GLUI_Spinner(obj_roll, "Variable-1", GLUI_SPINNER_FLOAT, &vara);
    var2 = new GLUI_Spinner(obj_roll, "Variable-2", GLUI_SPINNER_FLOAT, &varb);
    var3 = new GLUI_Spinner(obj_roll, "Variable-3", GLUI_SPINNER_FLOAT, &varc);
    var4 = new GLUI_Spinner(obj_roll, "Variable-4", GLUI_SPINNER_INT, &vard);

    float speed = 0.1;

    var1->set_float_val(0);
    var1->set_speed(speed);
    var2->set_float_val(0);
    var2->set_speed(speed);
    var3->set_int_val(0);
    var3->set_speed(speed);
    var4->set_int_val(0);
    var4->set_speed(speed);

    obj_roll->disable();
}

void camera_handler(int mode){

}

void user_interface_right(){

    glui_right = GLUI_Master.create_glui_subwindow( viewport, GLUI_SUBWINDOW_RIGHT);

    info();

    object_type = new GLUI_Panel(glui_right,"Objects");
        //object_type->alignment=GLUI;


    cube = new GLUI_Button(object_type, "Cuboid", 1, object_control);
        cube->set_w(button_w);

    cone = new GLUI_Button(object_type, "Cone", 3, object_control);
        cone->set_w(button_w);

    cylinder = new GLUI_Button(object_type, "Cylinder", 5, object_control);
        cylinder->set_w(button_w);

    teapot = new GLUI_Button(object_type, "Teapot", 7, object_control);
        teapot->set_w(button_w);



    new GLUI_Column( object_type, false );
    sphere = new GLUI_Button(object_type, "Sphere", 2, object_control);
        sphere->set_w(button_w);

    torus = new GLUI_Button(object_type, "Torus", 4, object_control);
        torus->set_w(button_w);

    plane = new GLUI_Button(object_type, "Plane", 6, object_control);
        plane->set_w(button_w);

    obj_edit();
    //save();

}

void user_interface_bottom(){

    glui_bottom = GLUI_Master.create_glui_subwindow( viewport, GLUI_SUBWINDOW_BOTTOM);

    transform_panel = new GLUI_Panel(glui_bottom, "Transform");

        x_axis = new GLUI_Spinner( transform_panel, "X: ", GLUI_SPINNER_FLOAT, &x_var);
            x_axis->set_speed(1);
            //x_axis->set_w(spinner_w);

        new GLUI_Column( transform_panel, false );
        y_axis = new GLUI_Spinner( transform_panel, "Y: ", GLUI_SPINNER_FLOAT, &y_var);
            y_axis->set_speed(1);
            //y_axis->set_w(spinner_w);


        new GLUI_Column( transform_panel, false );
        z_axis = new GLUI_Spinner( transform_panel, "Z: ", GLUI_SPINNER_FLOAT, &z_var);
            z_axis->set_speed(1);
            //z_axis->set_w(spinner_w);

        transform_panel->disable();

}

void GUI_interface(){

    user_interface_right();

    user_interface_bottom();

    glutPostRedisplay();

}

// Normal KeyBoard UserInterface
static void KeyFunction(unsigned char key, int x, int y){
    switch(key){
        // Exit
        case 27:
            exit(0);
        break;

        case 'g':
            if(gridMode) gridMode=0;
            else gridMode=1;
        break;

        // Transformation Modes
        case 'q':
            transTool='n';
            transform_panel->set_name("Transform");
            transform_panel->disable();
        break;
        case 'w':
            transTool='p';
            transform_panel->set_name("Translate");
            if(selected!=NULL){
                if(selected!=NULL){
                    transform_panel->enable();
                    //x_axis->ptr_val = &selected->position[0];
                    //y_axis->ptr_val = &selected->position[1];
                    //z_axis->ptr_val = &selected->position[2];

                    x_axis->set_float_val(selected->position[0]);
                    //x_var = &(selected->position[0]);

                    y_axis->set_float_val(selected->position[1]);
                    //y_var = &selected->position[1];

                    z_axis->set_float_val(selected->position[2]);
                    //z_var = &selected->position[2];
                }
            }
            else{
                transform_panel->disable();
            }
        break;
        case 'e':
            transTool='r';
            transform_panel->set_name("Rotate");
            if(selected!=NULL){
                if(selected!=NULL){
                    transform_panel->enable();
                    //x_axis->ptr_val = &selected->rotation[0];
                    //y_axis->ptr_val = &selected->rotation[1];
                    //z_axis->ptr_val = &selected->rotation[2];

                    x_axis->set_float_val(selected->rotation[0]);
                    //x_var = &selected->rotation[0];

                    y_axis->set_float_val(selected->rotation[1]);
                    //y_var = &selected->rotation[1];

                    z_axis->set_float_val(selected->rotation[2]);
                    //z_var = &selected->rotation[2];
                }
            }
            else{
                transform_panel->disable();
            }
        break;
        case 'r':
            transTool='s';
            transform_panel->set_name("Scale");
            if(selected!=NULL){
                if(selected!=NULL){
                    transform_panel->enable();
                    //x_axis->ptr_val = &selected->scale[0];
                    //y_axis->ptr_val = &selected->scale[1];
                    //z_axis->ptr_val = &selected->scale[2];

                    x_axis->set_float_val(selected->scale[0]);
                    //x_var = &selected->scale[0];

                    y_axis->set_float_val(selected->scale[1]);
                    //y_var = &selected->scale[1];

                    z_axis->set_float_val(selected->scale[2]);
                    //z_var = &selected->scale[2];
                }
            }
            else{
                transform_panel->disable();
            }
        break;

        // Transform Dimension
        case 'd':
            if(transDim=='x') transDim='y';
            else if(transDim=='y') transDim='z';
            else transDim='x';
        break;

        // Transforms
        /**** case '=':
            if(transDim=='x'){
                if(transTool=='p') selected->position[0]+=0.1f;
                else if(transTool=='r'){
                        selected->rotation[0]+=1.0f;
                        if(selected->rotation[0]>360){
                            selected->rotation[0]=selected->rotation[0]-360.0f;
                        }
                }
                else if(transTool=='s') selected->scale[0]+=0.1f;
            }
            else if(transDim=='y'){
                if(transTool=='p') selected->position[1]+=0.1f;
                else if(transTool=='r'){
                        selected->rotation[1]+=1.0f;
                        if(selected->rotation[1]>360){
                            selected->rotation[1]=selected->rotation[1]-360.0f;
                        }
                }
                else if(transTool=='s') selected->scale[1]+=0.1f;
            }
            else{
                if(transTool=='p') selected->position[2]+=0.1f;
                else if(transTool=='r'){
                        selected->rotation[2]+=1.0f;
                        if(selected->rotation[2]>360){
                            selected->rotation[2]=selected->rotation[2]-360.0f;
                        }
                }
                else if(transTool=='s') selected->scale[2]+=0.1f;
            }
        break;
        case '-':
            if(transDim=='x'){
                if(transTool=='p') selected->position[0]-=0.1f;
                else if(transTool=='r'){
                        selected->rotation[0]-=1.0f;
                        if(selected->rotation[0]<0){
                            selected->rotation[0]=selected->rotation[0]+360.0f;
                        }
                }
                else if(transTool=='s') selected->scale[0]-=0.1f;
            }
            else if(transDim=='y'){
                if(transTool=='p') selected->position[1]-=0.1f;
                else if(transTool=='r'){
                        selected->rotation[1]-=1.0f;
                        if(selected->rotation[1]<0){
                            selected->rotation[1]=selected->rotation[1]+360.0f;
                        }
                }
                else if(transTool=='s') selected->scale[1]-=0.1f;
            }
            else{
                if(transTool=='p') selected->position[2]-=0.1f;
                else if(transTool=='r'){
                        selected->rotation[2]-=1.0f;
                        if(selected->rotation[2]<0){
                            selected->rotation[2]=selected->rotation[1]+360.0f;
                        }
                }
                else if(transTool=='s') selected->scale[2]-=0.1f;
            }
        break; ****/

        case 'm':
            if(selected!=NULL) obj_material();
            /*if(selected!=NULL){
                if(selected->mat->matEnable)selected->mat->matEnable=0;
                else selected->mat->matEnable=1;
            }*/
        break;

        // selecting objects
        case 'p':
            if(selected!=NULL){
                if(selected->pre!=NULL) selected = selected->pre;
                update_gui();
            }
        break;
        case 'n':
            if(selected!=NULL){
                if(selected->next!=NULL) selected = selected->next;
                update_gui();
            }
        break;

        // Undo Or Redo Or Delete
        case 'z':
            if(tail!=NULL){
                    tail=tail->pre;
                    selected=tail;
                    if(tail==NULL) started=1;
                    update_gui();
            }
        break;
        case 'y':
            if(tail==NULL){
                    tail=head;
                    selected=tail;
                    update_gui();
            }
            else if(tail->next!=NULL){
                    tail=tail->next;
                    selected=tail;
                    update_gui();
            }
        break;
        case 'x':
            /* if(selected!=NULL){
                struct object *temp1 = selected->pre;
                struct object *temp2 = selected->next;
                if(temp1 == NULL && temp2 == NULL){
                    head=NULL;
                    tail=NULL;
                    selected=NULL;
                    started=1;
                }
                if(temp1==NULL){
                    head = temp2;
                    selected= temp2;
                    head->pre = NULL;
                }
                else if(temp2 == NULL){
                    temp1->next=NULL;
                    tail=temp1;
                }
                else{
                    temp1->next=temp2;
                    temp2->pre=temp1;
                }
            } */

            /**** if(selected!=NULL){
                struct object *d, *e;
                if(selected->pre!=NULL && selected->pre!=NULL){
                    d=selected->next;
                    e=selected->pre;
                    e->next=d;
                    d->pre=e;
                }
                else{
                    d = selected;
                    if(d->pre==NULL && d->next==NULL){
                            started=1;
                            head=NULL;
                            tail=NULL;
                            selected=NULL;
                    }
                    else if(d->pre==NULL){
                        head=d->next;
                        selected=d->next;
                    }
                    else if(d->next==NULL){
                        tail=d->pre;
                        selected=d->pre;
                    }
                    //printf("t");
                }

            } ****/
        break;

        // Copy Selected Object
        case 'c':
            if(selected!=NULL){
                tail->next=(struct object *)malloc(sizeof(struct object));
                serial_no=tail->serial_no+1;
                temp=tail->next;
                temp->pre=tail;
                tail=temp;
                temp=NULL;
                copy_object(selected,tail,serial_no);
                selected=tail;

                update_gui();
            }
        break;

        // Camera Dolly
        case '[':
            cam->radius+=0.1*cam_scale;
        break;
        case ']':
            cam->radius-=0.1*cam_scale;
        break;

        // Camera Truck in Y-axis;
        case '.':
            cam->center[1]+=0.1*cam_scale;
        break;
        case ',':
            cam->center[1]-=0.1*cam_scale;
        break;
        case 'l':
            //file_loader(head,tail, selected,cam,lght);
        break;

    }
    //glutPostRedisplay();
}

// KeyBoard function for Special Keys
void specialKeyFunction(int key, int x, int y){
    switch(key){
    // Wired Mode
    case GLUT_KEY_F5:
        if(isWired==3) isWired=0;
        else isWired=3;
    break;
    case GLUT_KEY_F4:
        if(isWired==1) isWired=0;
        else isWired=1;
    break;
    case GLUT_KEY_F3:
        if(isWired==2) isWired=0;
        else isWired=2;
    break;
    case GLUT_KEY_F2:
        if(globalSmooth==GL_SMOOTH) globalSmooth=GL_FLAT;
        else globalSmooth=GL_SMOOTH;
    break;

    case GLUT_KEY_F1:
        if(controles) controles=0;
        else controles=1;
    break;

    case GLUT_KEY_F11:
        glutFullScreen();
    break;

    case GLUT_KEY_UP:
            cam->center[2]+=0.1*scale_factor;
    break;

    case GLUT_KEY_DOWN:
            cam->center[2]-=0.1*scale_factor;
    break;

    case GLUT_KEY_RIGHT:
            cam->center[0]+=0.1*scale_factor;
    break;

    case GLUT_KEY_LEFT:
            cam->center[0]-=0.1*scale_factor;
    break;
    }

}

void mainRender(){
    glutInitWindowPosition(10,10);
    glutInitWindowSize(winW,winH);
    viewport=glutCreateWindow("Mozoo3d");

    GUI_interface();

    glui_right->set_main_gfx_window( viewport);
    glui_bottom->set_main_gfx_window( viewport );

    GLUI_Master.set_glutIdleFunc( initRendering );

    glutKeyboardFunc(KeyFunction);

    //glutKeyboardFunc(KeyFunction);

    glutMouseFunc(mouseFunction);
    glutMotionFunc(mouseMotion);
    glutSpecialFunc(specialKeyFunction);

    glutDisplayFunc(Renderer);

    glutReshapeFunc(ResizeWin);
}

void processMenuStatus(int status, int x, int y) {

	if (status == GLUT_MENU_IN_USE){
        glutPostRedisplay();
	}
	else{
        glutPostRedisplay();
	}
}

void processShrinkMenu(int option) {

	switch (option) {

		case SHRINK:
            glutPostRedisplay();
        break;
		case NORMAL:
            glutPostRedisplay();
        break;
	}
}

void processMainMenu(int option) {

	// nothing to do in here
	// all actions are for submenus
	switch(option){
        case 1:
            nurb=!nurb;
        break;
        case 2:
            bezcrv=!bezcrv;
        break;
        case 3:
            parf=!parf;
            if(parf) create_emittor(emm,emm->type);
        break;
	}
}

void processObjectMenu(int option) {

	switch (option) {

		case 1:
            new_obj=1;
            type=1;
        break;
        case 2:
            new_obj=1;
            type=2;
        break;
        case 3:
            new_obj=1;
            type=3;
        break;
        case 4:
            new_obj=1;
            type=4;
        break;
        case 5:
            new_obj=1;
            type=5;
        break;
        case 6:
            new_obj=1;
            type=6;
        break;
        case 7:
            new_obj=1;
            type=7;
        break;
	}
}

void processLightMenu(int option) {

	switch (option) {
		case 1:
		    selected_light=1;
            if(lght[1]->on){
                lght[1]->on=0;
                light_prop();
            }
            else{
                lght[1]->on=1;
                light_prop();
            }
        break;
        case 2:
            selected_light=2;
            if(lght[2]->on){
                lght[2]->on=0;
                light_prop();
            }
            else{
                lght[2]->on=1;
                light_prop();
            }
        break;
        case 3:
            selected_light=3;
            if(lght[3]->on){
                lght[3]->on=0;
                light_prop();
            }
            else{
                lght[3]->on=1;
                light_prop();
            }
        break;
        case 4:
            selected_light=4;
            if(lght[4]->on){
                lght[4]->on=0;
                light_prop();
            }
            else{
                lght[4]->on=1;
                light_prop();
            }
        break;
        case 5:
            selected_light=5;
            if(lght[5]->on){
                lght[5]->on=0;
                light_prop();
            }
            else{
                lght[5]->on=1;
                light_prop();
            }
        break;
        case 6:
            selected_light=6;
            if(lght[6]->on){
                lght[6]->on=0;
                light_prop();
            }
            else{
                lght[6]->on=1;
                light_prop();
            }
        break;
        case 7:
            selected_light=1;
            if(lght[7]->on){
                lght[7]->on=0;
                light_prop();
            }
            else{
                lght[7]->on=1;
                light_prop();
            }
        break;
	}
}

void fileMenuOp(int option){

        if(option==1){
            //cam=(struct camera*)malloc(sizeof(struct camera));

            head=NULL;
            tail=NULL;
            selected=NULL;

            turn_light=0;
            started_light=1;

            new_obj=0;
            started=1;
            serial_no=-1;
            isWired=0;

            transTool='n';
            transDim='x';

            //deltaUp=0;
            //deltaSide=0;
            //deltaUpMode=0;
            //deltaSideMode=0;

            gridMode=1;;

            nurb=0;
            bezcrv=0;
            parf=0;
            isCam=0;

            globalSmooth=GL_SMOOTH;
        }
        else if(option==2){
            pop_window('l');
            slmode = 'l';
        }

        if(option==3){
            pop_window('s');
            slmode = 's';
        }

        if(option==4){
            exit(0);
        }

}

void createPopupMenus() {

	shrinkMenu = glutCreateMenu(processShrinkMenu);

	glutAddMenuEntry("Shrink",SHRINK);
	glutAddMenuEntry("NORMAL",NORMAL);

	fillMenu = glutCreateMenu(processObjectMenu);

	glutAddMenuEntry("Cuboid",1);
	glutAddMenuEntry("Sphere",2);
	glutAddMenuEntry("Cone",3);
	glutAddMenuEntry("Torus",4);
	glutAddMenuEntry("Cylinder",5);
	glutAddMenuEntry("Plane",6);
	glutAddMenuEntry("Teapot",7);;

    fileMenu = glutCreateMenu(fileMenuOp);
    glutAddMenuEntry("New",1);
	glutAddMenuEntry("Open",2);
	glutAddMenuEntry("Save",3);
	glutAddMenuEntry("Exit",4);

	lightMenu = glutCreateMenu(processLightMenu);
	glutAddMenuEntry("Light 1",1);
	glutAddMenuEntry("Light 2",2);
	glutAddMenuEntry("Light 3",3);
	glutAddMenuEntry("Light 4",4);
	glutAddMenuEntry("Light 5",5);
	glutAddMenuEntry("Light 6",6);
	glutAddMenuEntry("Light 7",7);

	mainMenu = glutCreateMenu(processMainMenu);
	glutAddSubMenu("File", fileMenu);
	glutAddSubMenu("Objects", fillMenu);
	glutAddSubMenu("Lights",lightMenu);
	glutAddMenuEntry("Bezier Curve",1);
	glutAddMenuEntry("Bezier Surface",2);
	glutAddMenuEntry("Particle System",3);


	// attach the menu to the right button
	glutAttachMenu(GLUT_RIGHT_BUTTON);

	// this will allow us to know if the menu is active
	glutMenuStatusFunc(processMenuStatus);
}

// Main
int main(int argc, char * argv[]){
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    srand(time(NULL));
    //glewInit();

    mainRender();

    glutTimerFunc(25,update,0);

    createPopupMenus();

    glutMainLoop();

    return 0;
}






