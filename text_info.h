using namespace std;

char * nameType(int t){
    switch(t){
        case 1:
            return "CUBE";
        break;
        case 2:
            return "SPHERE";
        break;
        case 3:
            return "CONE";
        break;
        case 4:
            return "TORUS";
        break;
        case 5:
            return "CYLINDER";
        break;
        case 6:
            return "PLANE";
        break;
        case 7:
            return "TEAPOT";
        break;
    }
}

// Returns Names for a type of objects
string nameObject(int t){
    switch(t){
        case 1:
            return "CUBE";
        break;
        case 2:
            return "SPHERE";
        break;
        case 3:
            return "CONE";
        break;
        case 4:
            return "TORUS";
        break;
        case 5:
            return "CYLINDER";
        break;
        case 6:
            return "PLANE";
        break;
        case 7:
            return "TEAPOT";
        break;
    }
}

// Draw 2D-Text on screen
void drawText(const char *text, int length, int x, int y){
    glDisable(GL_LIGHTING);
    glMatrixMode(GL_PROJECTION); // change the current matrix to PROJECTION

    double matrix[16]; // 16 doubles in stack memory
    glGetDoublev(GL_PROJECTION_MATRIX, matrix); // get the values from PROJECTION matrix to local variable
    glLoadIdentity(); // reset PROJECTION matrix to identity matrix

    glOrtho(0, 800, 0, 600, -5, 5); // orthographic perspective
    glMatrixMode(GL_MODELVIEW); // change current matrix to MODELVIEW matrix again
    glLoadIdentity(); // reset it to identity matrix

    glPushMatrix(); // push current state of MODELVIEW matrix to stack
    glLoadIdentity(); // reset it again. (may not be required, but it my convention)
    glRasterPos2i(x, y); // raster position in 2D

    for(int i=0; i<length; i++){
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, (int)text[i]); // generation of characters in our text with 9 by 15 GLU font
    }

    glPopMatrix(); // get MODELVIEW matrix value from stack
    glMatrixMode(GL_PROJECTION); // change current matrix mode to PROJECTION
    glLoadMatrixd(matrix); // reset

    glMatrixMode(GL_MODELVIEW); // change current matrix mode to MODELVIEW
    glEnable(GL_LIGHTING);
}

// Show information about the selected object
void object_info_show(struct object *selected){
        stringstream nme, pos, rot, scl, var;
        std::string text;

        int textUpLimit = 580;
        int sideLimit = 650;

        glColor3f(1, 1, 0);

        text=nameObject(selected->type);
        nme << text << "    00" <<selected->serial_no;
        text=nme.str();
        drawText(text.data(), text.size(), sideLimit, textUpLimit);

        pos << "Position : [" << selected->position[0] << " ," << selected->position[1] << " ," << selected->position[2] << " ]";
        text = pos.str();
        drawText(text.data(), text.size(), sideLimit, textUpLimit-20);

        rot << "Rotation : [" << selected->rotation[0] << " ," << selected->rotation[1] << " ," << selected->rotation[2] << " ]";
        text = rot.str();
        drawText(text.data(), text.size(), sideLimit, textUpLimit-40);

        scl << "Scaleing : [" << selected->scale[0] << " ," << selected->scale[1] << " ," << selected->scale[2] << " ]";
        text = scl.str();
        drawText(text.data(), text.size(), sideLimit, textUpLimit-60);

        if(selected->type==1){
            var<< "Length : " << selected->variables[0];
            text=var.str();
            drawText(text.data(), text.size(), sideLimit, textUpLimit-80);
            var.str("");

            var<< "Breadth : " << selected->variables[1];
            text=var.str();
            drawText(text.data(), text.size(), sideLimit, textUpLimit-100);
            var.str("");

            var<< "Height : " << selected->variables[2];
            text=var.str();
            drawText(text.data(), text.size(), sideLimit, textUpLimit-120);
            var.str("");
        }
        else if(selected->type==2){
            var<< "Radius : " << selected->variables[0];
            text=var.str();
            drawText(text.data(), text.size(), sideLimit, textUpLimit-80);
            var.str("");

            var<< "Rings : " << selected->variables[1];
            text=var.str();
            drawText(text.data(), text.size(), sideLimit, textUpLimit-100);
            var.str("");

            var<< "Sectors : " << selected->variables[2];
            text=var.str();
            drawText(text.data(), text.size(), sideLimit, textUpLimit-120);
            var.str("");
        }
        else if(selected->type==3){
            var<< "Base Radius : " << selected->variables[0];
            text=var.str();
            drawText(text.data(), text.size(), sideLimit, textUpLimit-80);
            var.str("");

            var<< "Height : " << selected->variables[1];
            text=var.str();
            drawText(text.data(), text.size(), sideLimit, textUpLimit-100);
            var.str("");

            var<< "Verticle Div. : " << selected->variables[2];
            text=var.str();
            drawText(text.data(), text.size(), sideLimit, textUpLimit-120);
            var.str("");

            var<< "Radial Div. : " << selected->variables[3];
            text=var.str();
            drawText(text.data(), text.size(), sideLimit, textUpLimit-140);
            var.str("");
        }
        else if(selected->type==4){
            var<< "Inner Radius : " << selected->variables[0];
            text=var.str();
            drawText(text.data(), text.size(), sideLimit, textUpLimit-80);
            var.str("");

            var<< "Outer Radius : " << selected->variables[1];
            text=var.str();
            drawText(text.data(), text.size(), sideLimit, textUpLimit-100);
            var.str("");

            var<< "N-sides : " << selected->variables[2];
            text=var.str();
            drawText(text.data(), text.size(), sideLimit, textUpLimit-120);
            var.str("");

            var<< "Rings : " << selected->variables[3];
            text=var.str();
            drawText(text.data(), text.size(), sideLimit, textUpLimit-140);
            var.str("");
        }
        else if(selected->type==5){
            var<< "Radius : " << selected->variables[0];
            text=var.str();
            drawText(text.data(), text.size(), sideLimit, textUpLimit-80);
            var.str("");

            var<< "Height : " << selected->variables[1];
            text=var.str();
            drawText(text.data(), text.size(), sideLimit, textUpLimit-100);
            var.str("");

            var<< "Verticle Div. : " << selected->variables[2];
            text=var.str();
            drawText(text.data(), text.size(), sideLimit, textUpLimit-120);
            var.str("");

            var<< "Radial Div. : " << selected->variables[3];
            text=var.str();
            drawText(text.data(), text.size(), sideLimit, textUpLimit-140);
            var.str("");
        }
        else if(selected->type==6){
            var<< "Length : " << selected->variables[0];
            text=var.str();
            drawText(text.data(), text.size(), sideLimit, textUpLimit-80);
            var.str("");

            var<< "Breadth : " << selected->variables[1];
            text=var.str();
            drawText(text.data(), text.size(), sideLimit, textUpLimit-100);
            var.str("");

            var<< "X-Div. : " << selected->variables[2];
            text=var.str();
            drawText(text.data(), text.size(), sideLimit, textUpLimit-120);
            var.str("");

            var<< "Y-Div. : " << selected->variables[3];
            text=var.str();
            drawText(text.data(), text.size(), sideLimit, textUpLimit-140);
            var.str("");
        }
        else if(selected->type==7){
            var<< "Size : " << selected->variables[0];
            text=var.str();
            drawText(text.data(), text.size(), sideLimit, textUpLimit-80);
            var.str("");
        }


}

