#include <fstream>

int get_fileName(char* n){
    char t;
    scanf("%c", &t);
    int i=1;
    while(t!='\n' && i<=20){
        n[i-1]=t;
    }
    return i;
}


void file_saver(struct object *head, struct object *tail, struct camera *cam,struct light *lght[], const char *file_name){

    struct object *temp;
    temp=head;
    //int cnt=get_fileName(name);
    ofstream myfile;
    myfile.open (file_name);

    // Objects
    if(tail!=NULL){
        while(temp!=tail->next){

            myfile << temp->type << " " << temp->serial_no << " ";

            myfile << temp->position[0] << " " << temp->position[1] << " " << temp->position[2] << " " << temp->rotation[0] << " " << temp->rotation[1] << " " << temp->rotation[2] << " " << temp->scale[0] << " " << temp->scale[1] << " " << temp->scale[2] << " ";

            if(temp->type==1 || temp->type==2){
                myfile << temp->variables[0] << " " << temp->variables[1] << " " << temp->variables[2] << " ";
            }
            else if(temp->type==3 || temp->type==4 || temp->type==5 || temp->type==6){
                myfile << temp->variables[0] << " " << temp->variables[1] << " " << temp->variables[2] << " " << temp->variables[3] << " ";
            }
            else if(temp->type==7){
                myfile << temp->variables[0] << " ";
            }

            struct materialType *mat = temp->mat;
            if(mat!=NULL){

                myfile << mat->matEnable << " " << mat->smooth << " ";
                myfile << mat->color[0] << " " << mat->color[1] << " " << mat->color[2] << " " << mat->color[3] << " ";
                myfile << mat->mat_ambient[0] << " " << mat->mat_ambient[1] << " " << mat->mat_ambient[2] << " ";
                myfile << mat->mat_diffuse[0] << " " << mat->mat_diffuse[1] << " " << mat->mat_diffuse[2] << " ";
                myfile << mat->mat_specular[0] << " " << mat->mat_specular[1] << " " << mat->mat_specular[2] << " ";
                myfile << mat->mat_shininess;
            }

            temp=temp->next;
            myfile << "\n";
        }
    }
    myfile << "#\n";

    // Camera
    myfile << cam->radius << " ";
    myfile << cam->sideAngle << " " << cam->upAngle << " ";
    myfile << cam->center[0] << " " << cam->center[1] << " " << cam->center[2] << " ";
    myfile << cam->up[0] << " " << cam->up[1] << " " << cam->up[2];

    myfile << "\n#\n";
    // Lights
    struct light *templ;
    for(int i=0;i<8;i++){
        templ=lght[i];
        myfile << templ->on << " " << templ->number << " ";
        myfile << templ->light_ambient[0] << " " << templ->light_ambient[1] << " " << templ->light_ambient[2] << " ";
        myfile << templ->light_diffuse[0] << " " << templ->light_diffuse[1] << " " << templ->light_diffuse[2] << " ";
        myfile << templ->light_specular[0] << " " << templ->light_specular[1] << " " << templ->light_specular[2] << " ";
        myfile << templ->light_position[0] << " " << templ->light_position[1] << " " << templ->light_position[2] << " ";
        myfile << templ->light_attenuation[0] << " " << templ->light_attenuation[1];

        myfile << "\n";
    }

    myfile.close();
}
