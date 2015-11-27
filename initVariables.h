float scale_factor=100;
float cam_scale=100;

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
