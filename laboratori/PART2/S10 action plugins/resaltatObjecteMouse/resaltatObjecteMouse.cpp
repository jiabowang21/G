#include "resaltatObjecteMouse.h"
#include "glwidget.h"

void ResaltatObjecteMouse::setSelectedObject(int selected) {
  if (selected<0 || selected>=(int)scene()->objects().size()) selected=-1;
  scene()->setSelectedObject(selected);
}

void encodeID(int index, GLubyte *color) {
  color[0]=color[1]=color[2]=index;
}

// Pintar l'escena assegurant-se que cada objecte es pinta amb un color únic 
// que permeti identificar l'objecte (i diferent del color de fons)
void ResaltatObjecteMouse::drawDrawColorScene() {
  // enviar la modelViewProjectionMatrix, i el color identificador dels objectes
  QMatrix4x4 MVP=camera()->projectionMatrix()*camera()->viewMatrix();
  programColor->setUniformValue("modelViewProjectionMatrix", MVP);
  for (unsigned int i=0; i<scene()->objects().size(); ++i) {
    GLubyte color[4];
    encodeID(i, color);
    programColor->setUniformValue("color", QVector4D(color[0]/255., color[1]/255., color[2]/255., 1));
    drawPlugin()->drawObject(i);
  }
}

int decodeID(GLubyte *color) {
  if (color[0]==255) return -1;
  return color[0];
}

void ResaltatObjecteMouse::onPluginLoad()
{
	QString vs_box_src =
    	"#version 330 core\n"
    	"layout (location=0) in vec3 vertex;"
    	"layout (location=2) in vec3 color;"
    	"uniform mat4 modelViewProjectionMatrix;"
    	"uniform vec3 boundingBoxMin;"
    	"uniform vec3 boundingBoxMax;"
    	"out vec4 FrontColor;"
    	"void main() {"
    	"   FrontColor=vec4(color, 1);"
    	"   mat4 scale=mat4(vec4(boundingBoxMax.x - boundingBoxMin.x, 0, 0, 0),"
    	"       vec4(0, boundingBoxMax.y - boundingBoxMin.y, 0, 0),"
    	"       vec4(0, 0, boundingBoxMax.z - boundingBoxMin.z, 0),"
    	"       vec4(0, 0, 0, 1));"
    	"   vec4 centre=vec4((boundingBoxMax + boundingBoxMin)/2, 0);"
    	"   vec4 V=scale*vec4(vertex - vec3(0.5), 1);"
    	"   gl_Position=modelViewProjectionMatrix * (centre + V);"
		"}";
    vsBox = new QOpenGLShader(QOpenGLShader::Vertex, this);
	vsBox-> compileSourceCode(vs_box_src);
	cout << "VS Box log: " << vsBox->log().toStdString() << endl;
	
    QString fs_box_src =
    "#version 330 core\n"
    "in vec4 FrontColor;"
    "out vec4 fragColor;"
    "void main() {"
    "   fragColor=FrontColor;"
    "}";
	fsBox= new QOpenGLShader(QOpenGLShader::Fragment, this);
    fsBox->compileSourceCode(fs_box_src);
    cout << "FS Box log:" << fsBox->log().toStdString() << endl;

    programBox = new QOpenGLShaderProgram(this);
    programBox->addShader(vsBox);
    programBox->addShader(fsBox);
    programBox->link();
    cout << "Link Box log:" << programBox->log().toStdString() << endl;
    
    QString vs_color_src =
    "#version 330 core\n"
    "layout (location=0) in vec3 vertex;"
    "uniform mat4 modelViewProjectionMatrix;"
    "void main() {"
    "   gl_Position = modelViewProjectionMatrix * (vec4(vertex, 1));"
	"}";
    vsColor = new QOpenGLShader(QOpenGLShader::Vertex, this);
	vsColor-> compileSourceCode(vs_color_src);
	cout << "VS Color log: " << vsColor->log().toStdString() << endl;
	
    QString fs_color_src =
    "#version 330 core\n"
    "uniform vec4 color;"
    "out vec4 fragColor;"
    "void main() {"
    "   fragColor = color;"
    "}";
	fsColor = new QOpenGLShader(QOpenGLShader::Fragment, this);
    fsColor->compileSourceCode(fs_color_src);
    cout << "FS Color log:" << fsColor->log().toStdString() << endl;

    programColor = new QOpenGLShaderProgram(this);
    programColor->addShader(vsColor);
    programColor->addShader(fsColor);
    programColor->link();
    cout << "Link Color log:" << programColor->log().toStdString() << endl;
    
    created=false;
    scene()->setSelectedObject(-1);
}

void ResaltatObjecteMouse::postFrame()
{
	int seleccionat=scene() -> selectedObject();
    if (seleccionat >= 0 && seleccionat<(int)scene()->objects().size()) {
        programBox->bind();
        
        // crear buffers
        GLWidget& g = *glwidget();
        g.makeCurrent();
        if (!created) {
            created=true;
            // dades
            GLfloat cube_vertices[]={
                0,0,0,
                0,0,1,
                0,1,0,
                
                0,0,1,
                0,1,0,
                0,1,1,
                
                1,0,0,
                1,0,1,
                1,1,0,
                
                1,0,1,
                1,1,0,
                1,1,1,
                
                0,0,0,
                0,0,1,
                1,0,0,
                
                0,0,1,
                1,0,0,
                1,0,1,
                
                0,1,0,
                0,1,1,
                1,1,0,
                
                0,1,1,
                1,1,0,
                1,1,1,
                
                0,0,0,
                0,1,0,
                1,0,0,
                
                0,1,0,
                1,0,0,
                1,1,0,
                
                0,0,1,
                0,1,1,
                1,0,1,
                
                0,1,1,
                1,0,1,
                1,1,1
            };
            GLfloat cube_colors[]={
                1,0,0,
                1,0,0,
                1,0,0,
                1,0,0,
                1,0,0,
                1,0,0,
                1,0,0,
                1,0,0,
                1,0,0,
                1,0,0,
                1,0,0,
                1,0,0,
                1,0,0,
                1,0,0,
                1,0,0,
                1,0,0,
                1,0,0,
                1,0,0,
                1,0,0,
                1,0,0,
                1,0,0,
                1,0,0,
                1,0,0,
                1,0,0,
                1,0,0,
                1,0,0,
                1,0,0,
                1,0,0,
                1,0,0,
                1,0,0,
                1,0,0,
                1,0,0,
                1,0,0,
                1,0,0,
                1,0,0,
                1,0,0
            };
            // VAO Capsa
            g.glGenVertexArrays(1, &cubeVAO);
            g.glBindVertexArray(cubeVAO);
            
            // VBOs Capsa  
            g.glGenBuffers(1, &verticesVBO);
            g.glBindBuffer(GL_ARRAY_BUFFER, verticesVBO);
            g.glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertices), cube_vertices, GL_STATIC_DRAW);
            g.glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
            g.glEnableVertexAttribArray(0);
            
            g.glGenBuffers(1, &colorVBO);
            g.glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
            g.glBufferData(GL_ARRAY_BUFFER, sizeof(cube_colors), cube_colors, GL_STATIC_DRAW);
            g.glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, 0);
            g.glEnableVertexAttribArray(2);
            
            g.glBindVertexArray(0);
        }
        
        // establir modelViewProjection
        QMatrix4x4 MVP=camera()->projectionMatrix()*camera()->viewMatrix();
        programBox->setUniformValue("modelViewProjectionMatrix", MVP);
        
        const Object &obj = scene()->objects()[seleccionat];
        programBox->setUniformValue("boundingBoxMin",obj.boundingBox().min());
        programBox->setUniformValue("boundingBoxMax",obj.boundingBox().max());
        g.glBindVertexArray(cubeVAO);
        g.glPolygonMode( GL_FRONT_AND_BACK, GL_LINE ); // activar pintar nomes linies
        g.glDrawArrays(GL_TRIANGLES, 0, 36);
        g.glPolygonMode( GL_FRONT_AND_BACK, GL_FILL ); // desactivar
        g.glBindVertexArray(0);
    }
}

void ResaltatObjecteMouse::mouseMoveEvent(QMouseEvent *e)
{	/*
	//apartat a comprovar que s'ha fet click als botons adients
	if (!(e->button() & Qt::rightButton)) return;
    if ((e->modifiers() & (Qt::ShiftModifier))) return;
    if (!(e->modifiers() & (Qt::ControlModifier))) return;
    GLWidget &g = *glwidget();
    g.makeCurrent();

	//apartat b esborrar buffers amb color de fons blanc
	g.glClearColor(1,0,0,0);
    g.glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	//apartat c activar(bind) dels shaders de colors
	programColor -> bind();

	//apartat d enviar uniforms
	QMatrix4x4 MVP = camera()->projectionMatrix() * camera()->viewMatrix();
    programColor -> setUniformValue("modelViewProjectionMatrix", MVP); 

	//apartat e pintar tots els objectes de l'escena
	for(unsigned int i = 0; i < scene()->objects().size(); ++i)
    {
        GLubyte color[4];
        color[0] = i + 1;
        color[1] = color[2] = 0;
        programColor -> setUniformValue("color", QVector4D(color[0]/255.0,color[1]/255.,color[2]/255.,1.0));
        drawPlugin() -> drawObject(i);
    }

	//apartat f llegir color buffer
	int x = e -> x();
    int y = glwidget() -> height() - e->y();
    GLubyte read[4];
    glReadPixels(x,y,1,1,GL_RGBA,GL_UNSIGNED_BYTE,read); 

	//apartat g establir l'objecte seleccionat
	if(read[0] != 0) scene()->setSelectedObject(read[0] - 1);

	//apartat h cridar update
	g.update();*/
	if (!(e->button()&Qt::RightButton)) return;          // boto esquerre del ratoli
  	if (e->modifiers()&(Qt::ShiftModifier)) return;     // res de tenir shift pulsat
  	if (!(e->modifiers()&Qt::ControlModifier)) return;  // la tecla control ha d'estar pulsada
	GLWidget &g = *glwidget();
    g.makeCurrent();  

  	glClearColor(1, 1, 1, 1);                           // esborrar els buffers amb un color de fons únic (blanc)
  	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  
  	programColor -> bind();                               // activar (bind) el shader program amb el VS+FS d’abans
  	drawDrawColorScene();
  	programColor -> release();

  	int x = e->x();                                       // llegir el color del buffer de color sota la posició del cursor
  	int y = glwidget()->height()-e->y();
  	GLubyte read[4];
  	glReadPixels(x, y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, read);
  
  	int seleccio = decodeID(&read[0]);                    // obtenir l'identificador de l'objecte corresponent i, 
  	setSelectedObject(seleccio);                        // si no és color de fons, establir l'objecte seleccionat
  
  	g.update();                             			// cridar a updateGL per tal que es repinti l'escena
}



