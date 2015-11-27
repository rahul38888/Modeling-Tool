
//Write UserInterface on screen
void writeControles(){
    string text;
    glColor3f(0.0f,1.0f,0.0f);
    text="Draw Objects : ";
    drawText(text.data(), text.size(), 5, 200);

    glColor3f(1,1,0);
    text="Right Click -> Object -> Select the object type" ;
    drawText(text.data(), text.size(), 85, 200);

    glColor3f(0.0f,1.0f,0.0f);
    text="Lights : ";
    drawText(text.data(), text.size(), 5, 180);

    glColor3f(1,1,0);
    text="Right Click -> Lights -> Select the Light to Enable and Select again to disable" ;
    drawText(text.data(), text.size(), 85, 180);

    glColor3f(0.0f,1.0f,0.0f);
    text="Gizmo : ";
    drawText(text.data(), text.size(), 5, 160);

    glColor3f(1,1,0);
    text="q->Normal w->Translate e->Rotate r->Scale" ;
    drawText(text.data(), text.size(), 50, 160);

    glColor3f(0.0f,1.0f,0.0f);
    text="Gizmo Operation : ";
    drawText(text.data(), text.size(), 300, 160);

    glColor3f(1,1,0);
    text="d->ChangeAxis  '='->IncreaseAxis '-'->DecreaseAxis l->SecondaryLights";
    drawText(text.data(), text.size(), 400, 160);

    glColor3f(0.0f,1.0f,0.0f);
    text="CameraTransforms : ";
    drawText(text.data(), text.size(), 5, 140);

    glColor3f(1,1,0);
    text="Orbit:{Hold Alt+MiddleMouse and move mouse} Zoom:{']'->ZoomIn '['->ZoomOut} Truck:{ArrowKeys -> X-axis/Z-axis ',' and '.'-> Y-axis}" ;
    drawText(text.data(), text.size(), 103, 140);

    glColor3f(0.0f,1.0f,0.0f);
    text="Undo/Redo/Copy : ";
    drawText(text.data(), text.size(), 5, 120);

    glColor3f(1,1,0);
    text="z->Delete last available object y->Redo last deleted object c->Copy selected object";
    drawText(text.data(), text.size(), 90, 120);

    glColor3f(0.0f,1.0f,0.0f);
    text="Change Selection : ";
    drawText(text.data(), text.size(), 5, 100);

    glColor3f(1,1,0);
    text="p->SelectPrevious n->SelectNext";
    drawText(text.data(), text.size(), 110, 100);

    glColor3f(1,1,0);
    text="F2->FlatSurface Mode   F3->VisibleEdge Mode   F4->WireFrame View   F5->Particle Mode for Cylinder and Sphere";
    drawText(text.data(), text.size(), 5, 80);

    glColor3f(1,1,0);
    text="Nurbs, Bezier and Particle System can be found in right click menu.";
    drawText(text.data(), text.size(), 5, 60);

    glColor3f(1,1,0);
    text="To Disable this Control-Info press -> i";
    drawText(text.data(), text.size(), 5, 60);

}
