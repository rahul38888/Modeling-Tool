
GLfloat light_ambient[] = {0.2f, 0.2f, 0.2f, 0.0f};
 GLfloat light_diffuse[] = {1.0f, 1.0f, 1.0f, 1.0f};
 GLfloat light_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
 GLfloat light_position0[] = {5.0f, 5.0f, 5.0f, 1.0f};
 GLfloat light_position1[] = {-5.0f, -5.0f, -5.0f, 1.0f};

// Lights for the scene
void create_light(int l0, int l1){

    if(l0){
            glDisable(GL_LIGHTING);
            glPushMatrix();
            glColor3f(1,1,1);
                glTranslated(light_position0[0],light_position0[1],light_position0[2]);
                glutSolidSphere(0.2,8,8);
            glPopMatrix();
            glEnable(GL_LIGHTING);
            glEnable(GL_LIGHT0);
    }
    else glDisable(GL_LIGHT0);
    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0,GL_POSITION, light_position0);
    //draw_light(0,light_position0);

    if(l1){
            glEnable(GL_LIGHT1);
            glDisable(GL_LIGHTING);
            glPushMatrix();
            glColor3f(1,1,1);
                glTranslated(light_position1[0],light_position1[1],light_position1[2]);
                glutSolidSphere(0.2,8,8);
            glPopMatrix();
            glEnable(GL_LIGHTING);
    }
    else glDisable(GL_LIGHT1);
    glLightfv(GL_LIGHT1, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT1,GL_POSITION, light_position1);
    //draw_light(1,light_position1);

    //glLightModelfv(GL_LIGHT_MODEL_AMBIENT, model);

    glShadeModel(GL_SMOOTH);

    glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

}
