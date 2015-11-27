//function reads a string and stores it in a string
void readstr(FILE *f, char *string)
{
    do {
    fgets(string, 255, f);
    } while ((string[0] == '/') || (string[0] == '\n'));
    return;
}

struct object * file_loader(float * num, struct object *last, struct camera *cam, struct light *lght, int type)
{
    if(type==1){
        last->type = (int)num[0];

        last->serial_no = (int)num[1];

        last->position[0]= (GLfloat)num[2];
        last->position[1]= (GLfloat)num[3];
        last->position[2]= (GLfloat)num[4];

        last->rotation[0]= (GLfloat)num[5];
        last->rotation[1]= (GLfloat)num[6];
        last->rotation[2]= (GLfloat)num[7];

        last->scale[0]= (GLfloat)num[8];
        last->scale[1]= (GLfloat)num[9];
        last->scale[2]= (GLfloat)num[10];

        if(last->type==1 || last->type==2){
            last->variables[0] = (GLfloat)num[11];
            last->variables[1] = (GLfloat)num[12];
            last->variables[2] = (GLfloat)num[13];

            last->mat = (struct materialType *)malloc(sizeof(struct materialType));

            struct materialType *mat = last->mat;
            mat->matEnable = (int)num[14];
            mat->smooth = (GLenum)num[15];

            mat->color[0]=(GLfloat)num[16];
            mat->color[1]=(GLfloat)num[17];
            mat->color[2]=(GLfloat)num[18];
            mat->color[3]=(GLfloat)num[19];

            mat->mat_ambient[0]=(GLfloat)num[20];
            mat->mat_ambient[1]=(GLfloat)num[21];
            mat->mat_ambient[2]=(GLfloat)num[22];

            mat->mat_diffuse[0]=(GLfloat)num[23];
            mat->mat_diffuse[1]=(GLfloat)num[24];
            mat->mat_diffuse[2]=(GLfloat)num[25];

            mat->mat_specular[0]=(GLfloat)num[26];
            mat->mat_specular[1]=(GLfloat)num[27];
            mat->mat_specular[2]=(GLfloat)num[28];

            mat->mat_shininess=(GLfloat)num[29];
        }
        else if(last->type==3 || last->type==4 || last->type==5 || last->type==6){
            last->variables[0]= (GLfloat)num[11];
            last->variables[1]= (GLfloat)num[12];
            last->variables[2]= (GLfloat)num[13];
            last->variables[3]= (GLfloat)num[14];

            last->mat = (struct materialType *)malloc(sizeof(struct materialType));

            struct materialType *mat = last->mat;
            mat->matEnable = (int)num[15];
            mat->smooth = (GLenum)num[16];

            mat->color[0]=(GLfloat)num[17];
            mat->color[1]=(GLfloat)num[18];
            mat->color[2]=(GLfloat)num[19];
            mat->color[3]=(GLfloat)num[20];

            mat->mat_ambient[0]=(GLfloat)num[21];
            mat->mat_ambient[1]=(GLfloat)num[22];
            mat->mat_ambient[2]=(GLfloat)num[23];

            mat->mat_diffuse[0]=(GLfloat)num[24];
            mat->mat_diffuse[1]=(GLfloat)num[25];
            mat->mat_diffuse[2]=(GLfloat)num[26];

            mat->mat_specular[0]=(GLfloat)num[27];
            mat->mat_specular[1]=(GLfloat)num[28];
            mat->mat_specular[2]=(GLfloat)num[29];

            mat->mat_shininess=(GLfloat)num[30];
        }
        else if(last->type==7){
            last->variables[0]= (GLfloat)num[11];

            last->mat = (struct materialType *)malloc(sizeof(struct materialType));

            struct materialType *mat = last->mat;
            mat->matEnable = (int)num[12];
            mat->smooth = (GLenum)num[13];

            mat->color[0]=(GLfloat)num[14];
            mat->color[1]=(GLfloat)num[15];
            mat->color[2]=(GLfloat)num[16];
            mat->color[3]=(GLfloat)num[17];

            mat->mat_ambient[0]=(GLfloat)num[18];
            mat->mat_ambient[1]=(GLfloat)num[19];
            mat->mat_ambient[2]=(GLfloat)num[20];

            mat->mat_diffuse[0]=(GLfloat)num[21];
            mat->mat_diffuse[1]=(GLfloat)num[22];
            mat->mat_diffuse[2]=(GLfloat)num[23];

            mat->mat_specular[0]=(GLfloat)num[24];
            mat->mat_specular[1]=(GLfloat)num[25];
            mat->mat_specular[2]=(GLfloat)num[26];

            mat->mat_shininess=(GLfloat)num[27];

        }
    }
    else if(type==2){

        cam->radius = (GLfloat)num[0];

        cam->sideAngle = (GLfloat)num[1];

        cam->upAngle = (GLfloat)num[2];

        cam->center[0] = (GLfloat)num[3];
        cam->center[1] = (GLfloat)num[4];
        cam->center[2] = (GLfloat)num[5];

        cam->up[0] = (GLfloat)num[6];
        cam->up[1] = (GLfloat)num[7];
        cam->up[2] = (GLfloat)num[8];
    }
    else if(type==3){

        lght->on = (int)num[0];

        lght->number = (int)num[1];

        lght->light_ambient[0] = (GLfloat)num[2];
        lght->light_ambient[1] = (GLfloat)num[3];
        lght->light_ambient[2] = (GLfloat)num[4];

        lght->light_diffuse[0] = (GLfloat)num[5];
        lght->light_diffuse[1] = (GLfloat)num[6];
        lght->light_diffuse[2] = (GLfloat)num[7];

        lght->light_specular[0] = (GLfloat)num[8];
        lght->light_specular[1] = (GLfloat)num[9];
        lght->light_specular[2] = (GLfloat)num[10];

        lght->light_position[0] = (GLfloat)num[11];
        lght->light_position[1] = (GLfloat)num[12];
        lght->light_position[2] = (GLfloat)num[13];

        lght->light_attenuation[0] = (GLfloat)num[14];
        lght->light_attenuation[1] = (GLfloat)num[15];

    }

}
