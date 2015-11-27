void drawSolidCuboid(struct object *obj){

    GLfloat l=obj->variables[0]/2, b=obj->variables[1]/2, h=obj->variables[2]/2;

            glNormal3f(1,0,0);
            glBegin(GL_POLYGON);
                glTexCoord2f(0,0);
                glVertex3f(l,h,b);
                glTexCoord2f(1,0);
                glVertex3f(l,-h,b);
                glTexCoord2f(1,1);
                glVertex3f(-l,-h,b);
                glTexCoord2f(0,1);
                glVertex3f(-l,h,b);
            glEnd();

            glNormal3f(-1,0,0);
            glBegin(GL_POLYGON);
                glTexCoord2f(0,0);
                glVertex3f(l,h,-b);
                glTexCoord2f(0,1);
                glVertex3f(l,-h,-b);
                glTexCoord2f(1,1);
                glVertex3f(-l,-h,-b);
                glTexCoord2f(1,0);
                glVertex3f(-l,h,-b);
            glEnd();

            glNormal3f(0,0,1);
            glBindTexture(GL_TEXTURE_2D, obj->mat->texture);
            glBegin(GL_POLYGON);
                glTexCoord2f(0,0);
                glVertex3f(l,h,b);
                glTexCoord2f(0,1);
                glVertex3f(l,h,-b);
                glTexCoord2f(1,1);
                glVertex3f(l,-h,-b);
                glTexCoord2f(1,0);
                glVertex3f(l,-h,b);
            glEnd();

            glNormal3f(0,0,-1);
            glBegin(GL_POLYGON);
                glTexCoord2f(0,0);
                glVertex3f(-l,h,b);
                glTexCoord2f(0,1);
                glVertex3f(-l,h,-b);
                glTexCoord2f(1,1);
                glVertex3f(-l,-h,-b);
                glTexCoord2f(1,0);
                glVertex3f(-l,-h,b);
            glEnd();

            glNormal3f(0,1,0);
            glBegin(GL_POLYGON);
                glTexCoord2f(0,0);
                glVertex3f(l,h,b);
                glTexCoord2f(0,1);
                glVertex3f(-l,h,b);
                glTexCoord2f(1,1);
                glVertex3f(-l,h,-b);
                glTexCoord2f(1,0);
                glVertex3f(l,h,-b);
            glEnd();

            glNormal3f(0,-1,0);
            glBegin(GL_POLYGON);
                glTexCoord2f(0,0);
                glVertex3f(l,-h,b);
                glTexCoord2f(0,1);
                glVertex3f(-l,-h,b);
                glTexCoord2f(1,1);
                glVertex3f(-l,-h,-b);
                glTexCoord2f(1,0);
                glVertex3f(l,-h,-b);
            glEnd();

}

void drawSolidSphere(struct object * obj){
    int i, j;
    double lat0, z0, zr0, lat1, z1, zr1, lng, x, y;
    float r = obj->variables[0];

    for(i = 0; i <= obj->variables[1]; i++) {
        lat0 = M_PI * (-0.5 + (double) (i - 1) / obj->variables[1]);
        z0  = r*sin(lat0);
        zr0 =  cos(lat0);

        lat1 = M_PI * (-0.5 + (double) i / obj->variables[1]);
        z1 = r*sin(lat1);
        zr1 = cos(lat1);

        glBegin(GL_QUAD_STRIP);
        for(j = 0; j <= obj->variables[2]; j++) {
            lng = 2 * M_PI * (double) (j - 1) / obj->variables[2];
            x = r*cos(lng);
            y = r*sin(lng);

            glNormal3f(x * zr0, y * zr0, z0);
            glVertex3f(x * zr0, y * zr0, z0);
            glNormal3f(x * zr1, y * zr1, z1);
            glVertex3f(x * zr1, y * zr1, z1);
        }
        glEnd();
    }
}

void drawSolidCone(struct object * obj){
    int i, j;
    float h, r;
    double latg, latgcos, latgsin, lat0, lat1, latgap, hgap, prht, prad, lat0cos, lat0sin, lat1cos, lat1sin  ;

    h=obj->variables[1];
    r=obj->variables[0];

    latg=(double)r/(double)h;
    latgsin=1/sqrt(1+latg*latg);
    latgcos=1/sqrt(1+latg*latg);
    hgap=(double)h/(double)obj->variables[2];
    latgap=2*M_PI/(double)obj->variables[3];

    lat0=(-latgap);
    lat1=0;

    for(i=0;i<=obj->variables[3];i++){
        prht=h;
        lat0+=latgap;
        lat1+=latgap;
        lat0sin=sin(lat0);lat0cos=cos(lat0);
        lat1sin=sin(lat1);lat1cos=cos(lat1);
        glBegin(GL_QUAD_STRIP);
            for(j=0,prad=0.2;j<=obj->variables[2];j++){
                prad=double(j)*latg*hgap;

                glNormal3f(lat0cos*latgsin,latgcos,lat0sin*latgsin);
                glVertex3f(prad*lat0cos,prht,prad*lat0sin);
                glNormal3f(lat1cos*latgsin,latgcos,lat1sin*latgsin);
                glVertex3f(prad*lat1cos,prht,prad*lat1sin);

                prht-=hgap;
            }
        glEnd();
    }

    lat0=(-latgap);
    lat1=0;

    glNormal3f(0,-1,0);
    for(i=0;i<=obj->variables[3];i++){
        lat0+=latgap;
        lat1+=latgap;
        glBegin(GL_TRIANGLES);
            glVertex3f(0,0,0);
            glVertex3f(r*cos(lat0),0,r*sin(lat0));
            glVertex3f(r*cos(lat1),0,r*sin(lat1));
        glEnd();
    }

}

void drawSolidTorus(struct object *obj){
    GLfloat r=obj->variables[1], th=obj->variables[0];
    int numc=obj->variables[2], numt=obj->variables[3];
    int i, j, k;
   double s, t, x, y, z, twopi;

   twopi = 2 * (double)M_PI;
   for (i = 0; i < numc; i++) {
      glBegin(GL_QUAD_STRIP);
      for (j = 0; j <= numt; j++) {
         for (k = 1; k >= 0; k--) {
            s = (i + k) % numc + 0.5;
            t = j % numt;

            x = (r+th*cos(s*twopi/numc))*cos(t*twopi/numt);
            y = (r+th*cos(s*twopi/numc))*sin(t*twopi/numt);
            z = th * sin(s * twopi / numc);
            glNormal3f(cos(s*twopi/numc)*cos(t*twopi/numt),cos(s*twopi/numc)*sin(t*twopi/numt),sin(s*twopi/numc));
            glVertex3f(x, y, z);
         }
      }
      glEnd();
   }
}

void drawSolidCylinder(struct object *obj){
    int i, j;
    double r=(double)obj->variables[0];
    double h=(double)obj->variables[1];

    double hgap, latgap, lat0, lat1, prht, lat0sin, lat0cos, lat1sin, lat1cos;

    hgap=h/obj->variables[3];
    latgap=2*M_PI/obj->variables[2];
    lat0=-latgap;
    lat1=0;

    for(i=0;i<=obj->variables[2];i++){
        prht=h;
        lat0+=latgap;
        lat1+=latgap;
        lat0sin=sin(lat0);lat0cos=cos(lat0);
        lat1sin=sin(lat1);lat1cos=cos(lat1);
        glBegin(GL_QUAD_STRIP);
            for(j=0;j<=obj->variables[3];j++){

                glNormal3f(lat0cos,0,lat0sin);
                glVertex3f(r*lat0cos,prht,r*lat0sin);
                glNormal3f(lat1cos,0,lat1sin);
                glVertex3f(r*lat1cos,prht,r*lat1sin);

                prht-=hgap;
            }
        glEnd();
    }

    glNormal3f(0,-1,0);
    for(i=0;i<=obj->variables[3];i++){
        lat0+=latgap;
        lat1+=latgap;
        glBegin(GL_TRIANGLES);
            glVertex3f(0,0,0);
            glVertex3f(r*cos(lat0),0,r*sin(lat0));
            glVertex3f(r*cos(lat1),0,r*sin(lat1));
        glEnd();
    }

    glNormal3f(0,1,0);
    for(i=0;i<=obj->variables[3];i++){
        lat0+=latgap;
        lat1+=latgap;
        glBegin(GL_TRIANGLES);
            glVertex3f(0,h,0);
            glVertex3f(r*cos(lat0),h,r*sin(lat0));
            glVertex3f(r*cos(lat1),h,r*sin(lat1));
        glEnd();
    }
}

void drawSolidPlane(struct object *obj){

    GLfloat x0, z0, xgap, zgap;

    xgap=obj->variables[0]/obj->variables[2];
    zgap=obj->variables[1]/obj->variables[3];


    for(x0=obj->variables[0]/2;x0>-obj->variables[0]/2;x0-=xgap){
        glBegin(GL_QUAD_STRIP);
            for(z0=obj->variables[1]/2;z0>=-obj->variables[1]/2;z0-=zgap){
                glNormal3f(0.0f, 1.0f, 0.0f);
                glVertex3f(x0,0,z0);
                glNormal3f(0.0f, 1.0f, 0.0f);
                glVertex3f(x0-xgap,0,z0);
            }
        glEnd();
    }

}

void drawWireCuboid(struct object *obj){

    GLfloat l=obj->variables[0]/2, b=obj->variables[1]/2, h=obj->variables[2]/2;

            glBegin(GL_LINE_STRIP);
                glVertex3f(l,h,b);
                glVertex3f(-l,h,b);
                glVertex3f(-l,h,-b);
                glVertex3f(l,h,-b);
                glVertex3f(l,h,b);
            glEnd();

            glBegin(GL_LINE_STRIP);
                glVertex3f(l,-h,b);
                glVertex3f(-l,-h,b);
                glVertex3f(-l,-h,-b);
                glVertex3f(l,-h,-b);
                glVertex3f(l,-h,b);
            glEnd();

            glBegin(GL_LINES);
                glVertex3f(l,h,b);
                glVertex3f(l,-h,b);
            glEnd();

            glBegin(GL_LINES);
                glVertex3f(-l,h,b);
                glVertex3f(-l,-h,b);
            glEnd();

            glBegin(GL_LINES);
                glVertex3f(-l,h,-b);
                glVertex3f(-l,-h,-b);
            glEnd();
            glBegin(GL_LINES);
                glVertex3f(l,h,-b);
                glVertex3f(l,-h,-b);
            glEnd();

}

void drawWireSphere(struct object * obj){
    int i;
    double prrd, prht, pang, agap;
    float r = obj->variables[0];
    agap=M_PI/obj->variables[1];
    pang=0;

    for(i=1;i<obj->variables[2];i++){
        pang+=agap;
        prht=r*cos(pang);
        prrd=r*sin(pang);
        glPushMatrix();
            glTranslatef(0,0,prht);
            glRotatef(90,1,0,0);
            draw_circle(prrd,obj->variables[1]);
        glPopMatrix();
    }

    agap=360/obj->variables[1];
    pang=0;
    for(i=0;i<obj->variables[1]/2;i++){
        glPushMatrix();
            glRotatef(90,0,1,0);
            glRotatef(pang,1,0,0);
            draw_circle(r+0.01,obj->variables[2]);
        glPopMatrix();
        pang+=agap;
    }
}

void drawWireCone(struct object * obj){
    int i, j;
    float h, r;
    double latg, lat0, lat1, latgap, hgap, prht, prad;

    h=obj->variables[1];
    r=obj->variables[0];

    latg=(double)r/(double)h;
    hgap=(double)h/(double)obj->variables[2];

    prht=h;
    for(j=0,prad=0.2;j<=obj->variables[2];j++){
        prad=double(j)*latg*hgap;
        glPushMatrix();
            glTranslatef(0,prht,0);
            draw_circle(prad,obj->variables[3]);
        glPopMatrix();
        prht-=hgap;
    }


    lat0=0;
    latgap=2*M_PI/(double)obj->variables[3];
    for(i=0;i<=obj->variables[3];i++){
        glBegin(GL_LINES);
            glVertex3f(0,h,0);
            glVertex3f(r*cos(lat0),0,r*sin(lat0));
        glEnd();
        lat0+=latgap;
    }

    lat0=(-latgap);
    lat1=0;

    glNormal3f(0,-1,0);
    for(i=0;i<=obj->variables[3];i++){
        lat0+=latgap;
        lat1+=latgap;
        glBegin(GL_LINE_STRIP);
            glVertex3f(0,0,0);
            glVertex3f(r*cos(lat0),0,r*sin(lat0));
            glVertex3f(r*cos(lat1),0,r*sin(lat1));
        glEnd();
    }

}

void drawWireCylinder(struct object *obj){
    int i, j;
    double r=(double)obj->variables[0];
    double h=(double)obj->variables[1];

    double hgap, latgap, lat0, lat1, prht;

    hgap=h/obj->variables[3];
    latgap=2*M_PI/obj->variables[2];
    lat0=-latgap;

    for(i=0;i<=obj->variables[2];i++){
        lat0+=latgap;
        glBegin(GL_LINES);
            glVertex3f(r*cos(lat0),0,r*sin(lat0));
            glVertex3f(r*cos(lat0),h,r*sin(lat0));
        glEnd();
    }

    prht=h;
    /*for(j=0;j<=obj->variables[3];j++){
        glPushMatrix();
            glTranslated(0,prht,0);
            draw_circle(r,obj->variables[2]);
        glPopMatrix();
        prht-=hgap;
    }*/

}

void drawWirePlane(struct object *obj){

    GLfloat a, b, xgap, zgap, x0, z0;

    a=obj->variables[0]/2;
    b=obj->variables[1]/2;

    xgap=obj->variables[0]/obj->variables[2];
    zgap=obj->variables[1]/obj->variables[3];

    for(x0=a;x0>=-a;x0-=xgap){
        glBegin(GL_LINES);
            glVertex3f(x0,0,b);
            glVertex3f(x0,0,-b);
        glEnd();
    }

    for(z0=b;z0>=-b;z0-=zgap){
        glBegin(GL_LINES);
            glVertex3f(a,0,z0);
            glVertex3f(-a,0,z0);
        glEnd();
    }

}







