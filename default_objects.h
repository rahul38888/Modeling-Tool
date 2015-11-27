GLfloat lineWidth=1.0;
int coneDiv1=16;
int coneDiv2=1;
int circleDiv1=4;
int circleDiv2=40;


// Draw transform tool for selected objects
void transformer_tool(struct object * selected, char t, char d){
    GLfloat lineHeight=1.5*cam_scale;

    GLfloat circleRadius=1.2*cam_scale;

    GLfloat cubeSide=0.1*cam_scale;

    GLfloat coneRadius=0.05*cam_scale;
    GLfloat coneHeight=0.2*cam_scale;

    if(selected!=NULL){

        glDisable(GL_LIGHTING);
        if(t=='n'){
            //X-axis
            glColor3f(1.0,0.0,0.0);
            //glLineWidth(2.0f);
            glBegin(GL_LINES);
                glVertex3f(selected->position[0],selected->position[1],selected->position[2]);
                glVertex3f(selected->position[0]+lineHeight,selected->position[1],selected->position[2]);
            glEnd();

            // Y-axis
            glColor3f(0.0,1.0,0.0);
            glBegin(GL_LINES);
                glVertex3f(selected->position[0],selected->position[1],selected->position[2]);
                glVertex3f(selected->position[0],selected->position[1]+lineHeight,selected->position[2]);
            glEnd();

            //Z-axis
            glColor3f(0.0,0.0,1.0);
            glBegin(GL_LINES);
                glVertex3f(selected->position[0],selected->position[1],selected->position[2]);
                glVertex3f(selected->position[0],selected->position[1],selected->position[2]+lineHeight);
            glEnd();
        }
        else if(t=='p'){
            //X-axis
            if(d=='x') glColor3f(1.0,1.0,0.0);
            else glColor3f(1.0,0.0,0.0);
            glPushMatrix();
                glTranslatef(selected->position[0]+lineHeight,selected->position[1],selected->position[2]);
                glRotatef(90,0,1,0);
                glutSolidCone(coneRadius,coneHeight,coneDiv1,coneDiv2);
            glPopMatrix();

            glBegin(GL_LINES);
                glVertex3f(selected->position[0],selected->position[1],selected->position[2]);
                glVertex3f(selected->position[0]+lineHeight,selected->position[1],selected->position[2]);
            glEnd();

            // Y-axis
            if(d=='y') glColor3f(1.0,1.0,0.0);
            else glColor3f(0.0,1.0,0.0);
            glPushMatrix();
                glTranslatef(selected->position[0],selected->position[1]+lineHeight,selected->position[2]);
                glRotatef(-90,1,0,0);
                glutSolidCone(coneRadius,coneHeight,coneDiv1,coneDiv2);
            glPopMatrix();

            glBegin(GL_LINES);
                glVertex3f(selected->position[0],selected->position[1],selected->position[2]);
                glVertex3f(selected->position[0],selected->position[1]+lineHeight,selected->position[2]);
            glEnd();

            //Z-axis
            if(d=='z') glColor3f(1.0,1.0,0.0);
            else glColor3f(0.0,0.0,1.0);
            glPushMatrix();
                glTranslatef(selected->position[0],selected->position[1],selected->position[2]+lineHeight);
                glutSolidCone(coneRadius,coneHeight,coneDiv1,coneDiv2);
            glPopMatrix();

            glBegin(GL_LINES);
                glVertex3f(selected->position[0],selected->position[1],selected->position[2]);
                glVertex3f(selected->position[0],selected->position[1],selected->position[2]+lineHeight);
            glEnd();
        }
        else if(t=='r'){

            glPushMatrix();

                /*glRotatef(selected->rotation[0],1,0,0);
                glRotatef(selected->rotation[1],0,1,0);
                glRotated(selected->rotation[2],0,0,1);*/

                //X-axis
                if(d=='x') glColor3f(1.0,1.0,0.0);
                else glColor3f(1.0,0.0,0.0);
                glPushMatrix();
                    glTranslatef(selected->position[0],selected->position[1],selected->position[2]);
                    glRotatef(90,0,0,1);
                    //glutSolidTorus(circleThickness,circleRadius,circleDiv1,circleDiv2);
                    draw_circle(circleRadius,32);
                glPopMatrix();
                glBegin(GL_LINES);
                    glVertex3f(selected->position[0],selected->position[1],selected->position[2]);
                    glVertex3f(selected->position[0]+lineHeight/2,selected->position[1],selected->position[2]);
                glEnd();

                // Y-axis
                if(d=='y') glColor3f(1.0,1.0,0.0);
                else glColor3f(0.0,1.0,0.0);
                glPushMatrix();
                    glTranslatef(selected->position[0],selected->position[1],selected->position[2]);
                    //glRotatef(-90,1,0,0);
                    //glutSolidTorus(circleThickness,circleRadius,circleDiv1,circleDiv2);
                    draw_circle(circleRadius,32);
                glPopMatrix();
                glBegin(GL_LINES);
                    glVertex3f(selected->position[0],selected->position[1],selected->position[2]);
                    glVertex3f(selected->position[0],selected->position[1]+lineHeight/2,selected->position[2]);
                glEnd();


                //Z-axis
                if(d=='z') glColor3f(1.0,1.0,0.0);
                else glColor3f(0.0,0.0,1.0);
                glPushMatrix();
                    glTranslatef(selected->position[0],selected->position[1],selected->position[2]);
                    glRotatef(-90,1,0,0);
                    //glutSolidTorus(circleThickness,circleRadius,circleDiv1,circleDiv2);
                    draw_circle(circleRadius,32);
                glPopMatrix();

                glBegin(GL_LINES);
                    glVertex3f(selected->position[0],selected->position[1],selected->position[2]);
                    glVertex3f(selected->position[0],selected->position[1],selected->position[2]+lineHeight/2);
                glEnd();

            glPopMatrix();
        }
        else if(t=='s'){

            glPushMatrix();

                /*glRotatef(selected->rotation[0],1,0,0);
                glRotatef(selected->rotation[1],0,1,0);
                glRotated(selected->rotation[2],0,0,1);*/

                glTranslatef(selected->position[0],selected->position[1],selected->position[2]);

                glPushMatrix();

                    //X-axis
                    if(d=='x') glColor3f(1.0,1.0,0.0);
                    else glColor3f(1.0,0.0,0.0);

                        glPushMatrix();
                            glTranslatef(lineHeight,0,0);
                            glutSolidCube(cubeSide);
                        glPopMatrix();

                        glBegin(GL_LINES);
                            glVertex3f(0,0,0);
                            glVertex3f(lineHeight,0,0);
                        glEnd();

                    // Y-axis
                    if(d=='y') glColor3f(1.0,1.0,0.0);
                    else glColor3f(0.0,1.0,0.0);

                        glPushMatrix();
                            glTranslatef(0,lineHeight,0);
                            glutSolidCube(cubeSide);
                        glPopMatrix();

                        glBegin(GL_LINES);
                            glVertex3f(0,0,0);
                            glVertex3f(0,lineHeight,0);
                        glEnd();

                    //Z-axis
                    if(d=='z') glColor3f(1.0,1.0,0.0);
                    else glColor3f(0.0,0.0,1.0);

                        glPushMatrix();
                            glTranslatef(0,0,lineHeight);
                            glutSolidCube(cubeSide);
                        glPopMatrix();

                        glBegin(GL_LINES);
                            glVertex3f(0,0,0);
                            glVertex3f(0,0,lineHeight);
                        glEnd();
                glPopMatrix();

            glPopMatrix();
        }
        glEnable(GL_LIGHTING);

    }
}

// Draw 10*10 z=0 grid
void base_grid(){
        int i;
        glDisable(GL_LIGHTING);
        for(i=10;i>=-10;i--){
            if(i==0) glColor3f(0.0,0.0,0.0);
            else glColor3f(0.7,0.7,0.7);
            glLineWidth(lineWidth);
            glBegin(GL_LINES);
                glVertex3d(i*scale_factor,0,10*scale_factor);
                glVertex3d(i*scale_factor,0,-10*scale_factor);
            glEnd();
            glBegin(GL_LINES);
                glVertex3d(10*scale_factor,0,i*scale_factor);
                glVertex3d(-10*scale_factor,0,i*scale_factor);
            glEnd();
        }
        glEnable(GL_LIGHTING);

}
