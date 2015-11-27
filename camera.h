#include <math.h>

GLfloat x, y, z;
GLfloat up_angle, plane_angle;
GLfloat radius;

void variable_trans(struct camera *cam){
    x=cam->eyex - cam->centerx;
    y=cam->eyey - cam->centery;
    z=cam->eyez - cam->centerz;

    if(z!=0){
        up_angle=y/z;
        plane_angle=x/z;
    }
}

radius=sqrt(x*x+y*y+z*z);

void camera_switch(struct camera *cam, int c){

}

void camera_dolly(struct camera *cam){

    // increase or decrease radius

}

void camera_roll(struct camera *cam){

    // rotate upVector

}

void camera_truck(struct camera *cam){

    // move eyePosition and centerPosition equally

}

void camera_orbit(struct camera *cam){

    // rotate eyePosition on shpere of 'radius' about centerPosition

}



