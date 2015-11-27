
static char* readShaderFile(const char* filename){
    FILE* fp = fopen(filename,"r");

    fseek(fp,0,SEEK_END);
    long fileLength = ftell(fp);
    fseek(fp,0,SEEK_SET);
    char * contents = new char[fileLength+1];
    for(int i=0;i<=fileLength;i++){
        contents[i]=0;
    }
    fread(contents,1,fileLength,fp);
    contents[fileLength+1]='\0';
    fclose(fp);
    return contents;
}
