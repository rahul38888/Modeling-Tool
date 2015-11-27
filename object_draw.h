GLint floorTexture;
// Draw 3d-Objects
void object_draw(object *obj, object *selected, int isWired, GLenum globalSmooth){

    glPushMatrix();
    glTranslatef(obj->position[0],obj->position[1],obj->position[2]);

    glRotatef(obj->rotation[0],1,0,0);
    glRotatef(obj->rotation[1],0,1,0);
    glRotated(obj->rotation[2],0,0,1);

    glScalef(obj->scale[0],obj->scale[1],obj->scale[2]);
    struct materialType * material=obj->mat;

    if(obj->mat!=NULL){

            //glEnable(GL_CULL_FACE);

            if(material->matEnable){
                glEnable(GL_COLOR_MATERIAL);

                //glShadeModel(material->smooth);

                GLfloat mat_ambient[] = {material->mat_ambient[0],material->mat_ambient[1],
                                            material->mat_ambient[2],material->mat_ambient[3]};
                GLfloat mat_diffuse[] = {material->mat_diffuse[0],material->mat_diffuse[1],
                                            material->mat_diffuse[2],material->mat_diffuse[3]};
                GLfloat mat_specular[] = {material->mat_specular[0],material->mat_specular[1],
                                            material->mat_specular[2],material->mat_specular[3]};
                GLfloat mat_shininess[] = {material->mat_shininess};

                glMaterialfv(GL_FRONT, GL_AMBIENT,  mat_ambient);
                glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
                glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
                glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
            }

    }

    //glColor4f(1,0,0,1);
    if(material->texture==NULL) glColor4f(material->color[0],material->color[1],material->color[2],material->color[3]);

    else{
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, material->texture);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    }

    if(isWired==0){
        if(obj->type==1){
            //glutSolidCube(obj->variable[0]);
            drawSolidCuboid(obj);
        }
        else if(obj->type==2){
            //glutWireSphere(obj->variables[0],obj->variables[1],obj->variables[2]);
            drawSolidSphere(obj);
        }
        else if(obj->type==3){
            //glutSolidCone(obj->variables[0],obj->variables[1],obj->variables[2],obj->variables[3]);
            drawSolidCone(obj);
        }
        else if(obj->type==4){
            //glutSolidTorus(obj->variables[0],obj->variables[1],obj->variables[2],obj->variables[3]);
            drawSolidTorus(obj);
        }
        else if(obj->type==5){
            drawSolidCylinder(obj);
        }
        else if(obj->type==6){
            drawSolidPlane(obj);
        }
        else if(obj->type==7){
            glutSolidTeapot(obj->variables[0]);
        }


        //glDisable(GL_CULL_FACE);
        glShadeModel(globalSmooth);
    }
    else{

        if(obj->type==1){
            if(isWired==2) drawSolidCuboid(obj);
            glDisable(GL_LIGHTING);
            if(selected==obj) glColor4f(1,1,1,1);
            drawWireCuboid(obj);
            glEnable(GL_LIGHTING);
        }
        else if(obj->type==2){
            if(isWired==3) drawBlockSphere(obj);
            else{
                if(isWired==2) drawSolidSphere(obj);
                glDisable(GL_LIGHTING);
                if(selected==obj) glColor4f(1,1,1,1);
                drawWireSphere(obj);
                glEnable(GL_LIGHTING);
            }
        }
        else if(obj->type==3){
            if(isWired==2) drawSolidCone(obj);
            glDisable(GL_LIGHTING);
            if(selected==obj) glColor4f(1,1,1,1);
            drawWireCone(obj);
            glEnable(GL_LIGHTING);
        }
        else if(obj->type==4){
            if(isWired==2) drawSolidTorus(obj);
            glDisable(GL_LIGHTING);
            if(selected==obj) glColor4f(1,1,1,1);
            glutWireTorus(obj->variables[0],obj->variables[1],obj->variables[2],obj->variables[3]);
            glEnable(GL_LIGHTING);
        }
        else if(obj->type==5){
            if(isWired==3) drawBlockCylinder(obj);
            else{
                if(isWired==2) drawSolidCylinder(obj);
                glDisable(GL_LIGHTING);
                if(selected==obj) glColor4f(1,1,1,1);
                drawWireCylinder(obj);
                glEnable(GL_LIGHTING);
            }
        }
        else if(obj->type==6){
            if(isWired==2) drawSolidPlane(obj);
            glDisable(GL_LIGHTING);
            if(selected==obj) glColor4f(1,1,1,1);
            drawWirePlane(obj);
            glEnable(GL_LIGHTING);
        }
        else if(obj->type==7){
            if(isWired==2) glutSolidTeapot(obj->variables[0]);
            glDisable(GL_LIGHTING);
            if(selected==obj) glColor4f(1,1,1,1);
            glutWireTeapot(obj->variables[0]);
            glEnable(GL_LIGHTING);
        }

    }
    //glDisable(GL_COLOR_MATERIAL);
    glPopMatrix();
}
//1->cuboid, 2->sphere, 3->cone, 4->torus, 5->teapot

GLfloat mat_ambient[] = {0.7f, 0.7f, 0.7f, 1.0f};
GLfloat mat_diffuse[] = {0.8f, 0.8f, 0.8f, 1.0f};
GLfloat mat_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
GLfloat mat_shininess[] = {100.0f};
GLfloat model[]= { 0.4f, 0.4f, 0.4f, 1.0f };

GLfloat dirVector0[]={ -1.0, -1.0, -1.0, 0.0};

GLenum return_light(int i){
    if(i==0)  return GL_LIGHT0;
    else if(i==1) return GL_LIGHT1;
    else if(i==2) return GL_LIGHT2;
    else if(i==3) return GL_LIGHT3;
    else if(i==4) return GL_LIGHT4;
    else if(i==5) return GL_LIGHT5;
    else if(i==6) return GL_LIGHT6;
    else if(i==7) return GL_LIGHT7;
}

/*Draw Lights Function - yet not Implemented*/
void draw_light(struct light *lght[], GLenum globalSmooth){

        for(int i=0;i<8;i++){
            GLfloat light_ambient[] = {lght[i]->light_ambient[0], lght[i]->light_ambient[1],
                                            lght[i]->light_ambient[2], lght[i]->light_ambient[3]};
            GLfloat light_diffuse[] = {lght[i]->light_diffuse[0],lght[i]->light_diffuse[1],
                                            lght[i]->light_diffuse[2],lght[i]->light_diffuse[3]};
            GLfloat light_specular[] = {lght[i]->light_specular[0],lght[i]->light_specular[1],
                                            lght[i]->light_specular[2],lght[i]->light_specular[3]};
            GLfloat light_position[] = {lght[i]->light_position[0],lght[i]->light_position[1],
                                            lght[i]->light_position[2],lght[i]->light_position[3]};
            GLfloat light_attenuation = lght[i]->light_attenuation[1];

            glLightfv(return_light(lght[i]->number), GL_AMBIENT,  light_ambient);
            glLightfv(return_light(lght[i]->number), GL_DIFFUSE, light_diffuse);
            glLightfv(return_light(lght[i]->number), GL_SPECULAR, light_specular);
            glLightfv(return_light(lght[i]->number),GL_POSITION, light_position);
            if(lght[i]->number){
                if(lght[i]->light_attenuation[0]){
                        glLightf( return_light(lght[i]->number),GL_LINEAR_ATTENUATION , light_attenuation);
                }
            }

            if(lght[i]->on){
                if(lght[i]->number) glDisable(GL_LIGHT0);

                glEnable(return_light(lght[i]->number));
                if(lght[i]->number){
                    glDisable(GL_LIGHTING);
                    glPushMatrix();
                    glColor3f(1,1,0);
                        glTranslated(light_position[0],light_position[1],light_position[2]);
                        glutSolidCube(0.2*scale_factor);
                    glPopMatrix();
                    glEnable(GL_LIGHTING);
                }
                /*else{
                    glDisable(GL_LIGHTING);
                    glPushMatrix();
                    glColor3f(1,1,0);
                        glTranslated(light_position[0],light_position[1],light_position[2]);
                        glutSolidSphere(0.1*scale_factor,8,8);
                    glPopMatrix();
                    glEnable(GL_LIGHTING);
                }*/
            }
            else{
                glDisable(return_light(lght[i]->number));
            }
        }

        glEnable(GL_COLOR_MATERIAL);
        //glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

        glShadeModel(globalSmooth);
        //glFrontFace(GL_CCW);

        glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
        glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
        glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
}





