GLfloat ctrlpoints[4][3] = {
        { -4.0, 0.0, -4.0}, { 2.0, 0.0, -2.0},
        {-2.0, 0.0, 2.0}, {4.0, 0.0, 4.0}};

GLfloat ctrlpoint[4][4][3] = {
   {{-1.5, -1.5, 4.0}, {-0.5, -1.5, 2.0},
    {0.5, -1.5, -1.0}, {1.5, -1.5, 2.0}},
   {{-1.5, -0.5, 1.0}, {-0.5, -0.5, 3.0},
    {0.5, -0.5, 0.0}, {1.5, -0.5, -1.0}},
   {{-1.5, 0.5, 4.0}, {-0.5, 0.5, 0.0},
    {0.5, 0.5, 3.0}, {1.5, 0.5, 4.0}},
   {{-1.5, 1.5, -2.0}, {-0.5, 1.5, -2.0},
    {0.5, 1.5, 0.0}, {1.5, 1.5, -1.0}}
};

void draw_circle(GLfloat r,int div){
    double latgap, prlat;

    latgap=2*M_PI/(double)div;
    prlat=0;

    glDisable(GL_LIGHTING);
    glBegin(GL_LINE_STRIP);
    for(int i=0;i<=div;i++){
        glVertex3f(r*cos(prlat),0,r*sin(prlat));
        //glVertex3f(r*cos(prlat+latgap),0,r*sin(prlat+latgap));
        prlat+=latgap;
    }
    glEnd();
    glEnable(GL_LIGHTING);
}

void draw_nurbs(){
    glMap1f(GL_MAP1_VERTEX_3, 0.0, 1.0, 3, 4, &ctrlpoints[0][0]);
    glEnable(GL_MAP1_VERTEX_3);

    int i;

    glDisable(GL_LIGHTING);
   glColor3f(1.0, 1.0, 0.0);
   glBegin(GL_LINE_STRIP);
      for (i = 0; i <= 30; i++)
         glEvalCoord1f((GLfloat) i/30.0);
   glEnd();
   /* The following code displays the control points as dots. */
   glPointSize(5.0);
   glColor3f(1.0, 1.0, 1.0);
   glBegin(GL_POINTS);
      for (i = 0; i < 4; i++){
        if(i==0 || i==3) glColor3f(1.0, 0.0, 0.0);
        else glColor3f(1.0, 1.0, 0.0);
         glVertex3fv(&ctrlpoints[i][0]);
      }
   glEnd();
   glEnable(GL_LIGHTING);
   glFlush();
}

void bezierSolidCurve(){

    glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4,
           0, 1, 12, 4, &ctrlpoint[0][0][0]);
   glEnable(GL_MAP2_VERTEX_3);
   glEnable(GL_AUTO_NORMAL);
   glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);
    glPushMatrix();
        glRotatef(-45.0, 1.0, 0.0, 0.0);
        glEvalMesh2(GL_FILL, 0, 20, 0, 20);
    glPopMatrix();
    //glFlush();

}

void bezierWireCurve(){
    int i, j;

    glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4,
           0, 1, 12, 4, &ctrlpoint[0][0][0]);
   glEnable(GL_MAP2_VERTEX_3);
   glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);

    glDisable(GL_LIGHTING);
   glPushMatrix ();
       glRotatef(-45.0, 1.0, 0.0, 0.0);
       for (j = 0; j <= 8; j++) {
          glBegin(GL_LINE_STRIP);
          for (i = 0; i <= 30; i++)
             glEvalCoord2f((GLfloat)i/30.0, (GLfloat)j/8.0);
          glEnd();
          glBegin(GL_LINE_STRIP);
          for (i = 0; i <= 30; i++)
             glEvalCoord2f((GLfloat)j/8.0, (GLfloat)i/30.0);
          glEnd();
       }
   glPopMatrix ();
   glEnable(GL_LIGHTING);
}
