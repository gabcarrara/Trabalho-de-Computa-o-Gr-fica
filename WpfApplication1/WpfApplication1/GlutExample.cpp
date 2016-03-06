//
//  main.cpp
//  glsl_sampleCodes
//
//  Created by Cristina Vasconcelos on 1/20/16.
//  Copyright © 2016 Cristina Vasconcelos. All rights reserved.
//

#include <GL/glew.h>
#define FREEGLUT_STATIC
#include <GL/freeglut.h>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

#define WINDOW_TITLE_PREFIX "Simple openGL code"


// This will identify our vertex buffer
GLuint vertexbuffer, vertexbufferColor;


GLuint VboId;
GLuint VaoId;
GLuint programID;


int CurrentWidth=800, CurrentHeight=600,  WindowHandle=0;
void Initialize(int, char*[]);
void ResizeFunction(int, int);
void RenderFunction(void);

void InitScene(void);
void InitShaders(void);


void checkError(void){
    
    
    
    GLenum ErrorCheckValue = glGetError();
    if (ErrorCheckValue != GL_NO_ERROR)
    {
          fprintf(     stderr,     "ERROR: Could not create a VBO: %s\n",
             gluErrorString(ErrorCheckValue));
        
        fprintf( stderr, "ERROR: Could not create a VBO: %d\n",
                ErrorCheckValue);
        
        
        //exit(-1);
    }
}

void InitWindow(int argc, char* argv[]){
 

 glutInit(&argc, argv);
 
    glutInitContextVersion(2, 1);
 //only for opengl >4
    // glutInitContextFlags(GLUT_FORWARD_COMPATIBLE);
 // glutInitContextProfile(GLUT_CORE_PROFILE);
//  glutSetOption(  GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS );
 glutInitWindowSize(CurrentWidth, CurrentHeight);
 glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
 WindowHandle = glutCreateWindow(WINDOW_TITLE_PREFIX);
 if(WindowHandle < 1) {
   fprintf(     stderr,"ERROR: Could not create a new rendering window.\n");
   exit(EXIT_FAILURE);
 }
 glutReshapeFunc(ResizeFunction);
 glutDisplayFunc(RenderFunction);

}


int main(int argc, char* argv[])
{
    Initialize(argc, argv);
    glutMainLoop();
    exit(EXIT_SUCCESS);
}

void Initialize(int argc, char* argv[]){
 
    InitWindow(argc, argv);
//openGL context is ready... we can call gl functions 
    
    //active context is required for calling glewInit:
    glewExperimental = GL_TRUE;
    GLenum GlewInitResult = glewInit();
    if (GLEW_OK != GlewInitResult) {
        fprintf(stderr, "ERROR: %s\n", glewGetErrorString(GlewInitResult) );
        exit(EXIT_FAILURE);
    }
    cout << "Status: Using GLEW " << glewGetString(GLEW_VERSION) << endl;
    cout << "OpenGL version " << glGetString(GL_VERSION) << " supported" << endl;

    fprintf( stdout, "INFO: OpenGL  Version:%s\n",glGetString(GL_VERSION));
    
    InitScene();
    InitShaders();


    
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

}

void ResizeFunction(int Width, int Height){
    CurrentWidth = Width;
    CurrentHeight = Height;
    glViewport(0, 0, CurrentWidth, CurrentHeight);
}
void RenderFunction(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

   
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
   
    //1 triangle: 3 indices starting at 0
    glDrawArrays(GL_TRIANGLES, 0, 3);
    
    glutSwapBuffers();
 //   glutPostRedisplay();
}



void CreateVBO(void)
{
   static const GLfloat g_vertex_buffer_data[] = {
       -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        0.0f,  1.0f, 0.0f,
     };
    
    static const GLfloat colours[] = {	1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f };
    
    
    
    
    //1o VAO: opengl >4
    //glGenVertexArrays(1, &VaoId);
    //glBindVertexArray(VaoId);

   
    
    checkError();
    
    
    // VBO for vertex data:
    // Generate 1 buffer, put the resulting identifier in vertexbuffer
    glGenBuffers(1, &vertexbuffer);
    // The following commands will talk about our 'vertexbuffer' buffer
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    // Give our vertices to OpenGL.
    glBufferData(GL_ARRAY_BUFFER, 9*sizeof(GLfloat), g_vertex_buffer_data, GL_STATIC_DRAW);
    
    glVertexAttribPointer((GLuint)0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);
    
    //return;
    
    // VBO for colour data
    glGenBuffers(1, &vertexbufferColor);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbufferColor);
    glBufferData(GL_ARRAY_BUFFER, 9*sizeof(GLfloat), colours, GL_STATIC_DRAW);
    
    
    glVertexAttribPointer((GLuint)1, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(1);

    
    
    checkError();
    
    return;
}


void InitScene(void){

	CreateVBO();



}


// loadFile - loads text file into char* fname
// allocates memory - so need to delete after use
// size of file returned in fSize
char* loadFile(char *fname, GLint &fSize)
{
    ifstream::pos_type size;
    char * memblock;
    string text;
    
    // file read based on example in cplusplus.com tutorial
    ifstream file (fname, ios::in|ios::binary|ios::ate);
    if (file.is_open())
    {
        size = file.tellg();
        fSize = (GLuint) size;
        memblock = new char [size];
        file.seekg (0, ios::beg);
        file.read (memblock, size);
        file.close();
        cout << "file " << fname << " loaded" << endl;
        text.assign(memblock);
    }
    else
    {
        cout << "Unable to open file " << fname << endl;
        exit(1);
    }
    return memblock;
}


// printShaderInfoLog
// From OpenGL Shading Language 3rd Edition, p215-216
// Display (hopefully) useful error messages if shader fails to compile
void printShaderInfoLog(GLint shader)
{
    int infoLogLen = 0;
    int charsWritten = 0;
    GLchar *infoLog;
    
    glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLen);
    
    // should additionally check for OpenGL errors here
    
    if (infoLogLen > 0)
    {
        infoLog = new GLchar[infoLogLen];
        // error check for fail to allocate memory omitted
        glGetShaderInfoLog(shader,infoLogLen, &charsWritten, infoLog);
        cout << "InfoLog:" << endl << infoLog << endl;
        delete [] infoLog;
    }
    
    // should additionally check for OpenGL errors here
}

void InitShaders(void)
{
    GLuint p, f, v;
    
    char *vs,*fs;
    
    v = glCreateShader(GL_VERTEX_SHADER);
    f = glCreateShader(GL_FRAGMENT_SHADER);
    
    // load shaders & get length of each
    GLint vlen;
    GLint flen;
    vs = loadFile("minimal.vert",vlen);
    fs = loadFile("minimal.frag",flen);
    
    const char * vv = vs;
    const char * ff = fs;
    
    glShaderSource(v, 1, &vv,&vlen);
    glShaderSource(f, 1, &ff,&flen);
    
    GLint compiled;
    
    glCompileShader(v);
    glGetShaderiv(v, GL_COMPILE_STATUS, &compiled);
    if (!compiled)
    {
        cout << "Vertex shader not compiled." << endl;
        printShaderInfoLog(v);
    }
    
    glCompileShader(f);
    glGetShaderiv(f, GL_COMPILE_STATUS, &compiled);
    if (!compiled)
    {
        cout << "Fragment shader not compiled." << endl;
        printShaderInfoLog(f);
    }
    
    p = glCreateProgram();
    
    glBindAttribLocation(p,0, "in_Position");
    glBindAttribLocation(p,1, "in_Color");
    
    glAttachShader(p,v);
    glAttachShader(p,f);
    
    glLinkProgram(p);
    glUseProgram(p);
    
    delete [] vs; // dont forget to free allocated memory
    delete [] fs; // we allocated this in the loadFile function...
}

