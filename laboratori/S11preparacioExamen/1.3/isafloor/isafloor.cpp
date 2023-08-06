#include "isafloor.h"
#include "glwidget.h"

//producto escalar -> dot()
//producto vectorial -> cross()

void Isafloor::onPluginLoad()
{
	GLWidget & g = *glwidget();
    g.makeCurrent();
    // Carregar shader, compile & link 
    vs = new QOpenGLShader(QOpenGLShader::Vertex, this);
    vs->compileSourceFile(g.getPluginPath()+"/../isafloor/isafloor.vert");

    fs = new QOpenGLShader(QOpenGLShader::Fragment, this);
    fs->compileSourceFile(g.getPluginPath()+"/../isafloor/isafloor.frag");

    program = new QOpenGLShaderProgram(this);
    program->addShader(vs);
    program->addShader(fs); 
    program->link(); 
	
	Scene* scn = scene(); 
	float valid_faces = 0;
    const Object &obj=scn->objects()[0];
    for (int j=0; j<(int)obj.faces().size(); ++j) {
      	const Face &face = obj.faces()[j];
		Vector world = Vector(0, 0, 1);
      	if (Vector::dotProduct((face.normal().normalized()), world) > 0.7) ++valid_faces;
    }

	cout << valid_faces << endl; 
	cout << (int)obj.faces().size() << endl;
	ambda = valid_faces / (int)obj.faces().size();	
	cout << "TERRA: " << ambda << endl;
}

void Isafloor::preFrame()
{ 
	// bind shader and define uniforms
  	program -> bind();
	program -> setUniformValue("ambda", float(ambda));
  	QMatrix3x3 NM = camera() -> viewMatrix().normalMatrix();
  	program -> setUniformValue("normalMatrix", NM); 
  	QMatrix4x4 MVP = camera() -> projectionMatrix()*camera() -> viewMatrix();
  	program -> setUniformValue("modelViewProjectionMatrix", MVP); 
}

void Isafloor::postFrame()
{
	// unbind shader
  	program->release(); 
}



