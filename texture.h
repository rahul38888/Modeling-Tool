//support function to get size of image
static unsigned int getint(FILE *fp)
{
  int c, c1, c2, c3;

  // get 4 bytes
  c = getc(fp);
  c1 = getc(fp);
  c2 = getc(fp);
  c3 = getc(fp);

  return ((unsigned int) c) +
    (((unsigned int) c1) << 8) +
    (((unsigned int) c2) << 16) +
    (((unsigned int) c3) << 24);
}

//support function to get size of image
static unsigned int getshort(FILE *fp)
{
  int c, c1;

  c = getc(fp);
  c1 = getc(fp);

  return ((unsigned int) c) + (((unsigned int) c1) << 8);
}

int ImageLoad(char *filename, Image *image)
{
    FILE *file;
    unsigned long size;
    unsigned long i;
    unsigned short int planes;
    unsigned short int bpp;
    char temp;
    if ((file = fopen(filename, "rb"))==NULL) //load image
    {
        //printf("a");
        return 0;
    }
    fseek(file, 18, SEEK_CUR);
    image->sizeX = getint (file);   //get size of image
    image->sizeY = getint (file);   //get size of image
    size = image->sizeX * image->sizeY * 3;
    planes = getshort(file);
    if (planes != 1)
    {
        printf("b");
        return 0;
    }
    bpp = getshort(file);
    if (bpp != 24)
    {
        printf("c");
        return 0;
    }
    fseek(file, 24, SEEK_CUR);
    image->data = (char *) malloc(size);
    if (image->data == NULL)
    {
        printf("d");
        return 0;
    }
    if ((i = fread(image->data, size, 1, file)) != 1)
    {
        printf("e");
        return 0;
    }

    for (i=0;i<size;i+=3)
    {
        temp = image->data[i];
        image->data[i] = image->data[i+2];
        image->data[i+2] = temp;
    }
    return 1;
}



//function to load textures
void LoadGLTextures(GLuint texture)
{

    Image *image;

    image = (Image *) malloc(sizeof(Image));
    ImageLoad("bricks.bmp",image);

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST);      //set mipmap to lienear nearest
    gluBuild2DMipmaps(GL_TEXTURE_2D, 3, image->sizeX, image->sizeY, GL_RGB, GL_UNSIGNED_BYTE, image->data);
    //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image->sizeX, image->sizeY, 0,GL_RGB, GL_UNSIGNED_BYTE, image->data);
    delete(image);

}
