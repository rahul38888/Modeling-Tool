//image data
typedef struct {
    unsigned long sizeX;
    unsigned long sizeY;
    char *data;
} Image;


// Data Structure for 3d-Objects
struct object{
    int serial_no;
    int type;

    //position
    GLfloat position[3];

    //rotate
    GLfloat rotation[3];

    //scale
    GLfloat scale[3];

    //other variables
    float variables[20];

    //next object
    struct object *next;
    struct object *pre;

    struct materialType *mat;
};

struct particle{

    GLfloat position[3];
    GLfloat velocity[3];
    GLfloat spin[3];

    GLfloat life;

    struct particle * next;
};

struct emittor{
    int type;
    int on;
    float time;
    int parCount;

    GLfloat position[3];
    GLfloat velocity[3];

    GLfloat diverge;

    struct particle * par;
};

// Data Structure for camera
struct camera{
    /*Refrence Position*/
    GLfloat center[3];

    /*Eye Position*/
    GLfloat radius;

    /*Rotation Angles*/
    GLfloat sideAngle;
    GLfloat upAngle;

    /*Camera Plane axis vectors*/
    //GLfloat camPlaneX[3];
    //GLfloat camPlaneY[3];

    /*Up Vector Components*/
    GLfloat up[3];

};

/*
    spherical data type/elements
    center x, y z
    dist
    up_angle
    plane_angle

*/

// Data Structure for lights
struct light{

    int on;
    int number;
    GLfloat light_ambient[4];
    GLfloat light_diffuse[4];
    GLfloat light_specular[4];
    GLfloat light_position[4];
    GLfloat light_attenuation[2];

};

struct materialType{

    int matEnable;
    GLenum smooth;

    GLuint texture;
    //color
    GLfloat color[4];
    GLfloat mat_ambient[4];
    GLfloat mat_diffuse[4];
    GLfloat mat_specular[4];
    GLfloat mat_shininess;

};

struct point{
    GLfloat cord[3];
};

struct spline{
    struct point pointList[4];
};

struct bezierCurve{
    GLenum smooth;
    struct point pointList[16];
};





