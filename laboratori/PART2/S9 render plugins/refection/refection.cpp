// GLarena, a plugin based platform to teach OpenGL programming
// © Copyright 2012-2018, ViRVIG Research Group, UPC, https://www.virvig.eu
// 
// This file is part of GLarena
//
// GLarena is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#include "refection.h"
#include <QCoreApplication>

const int IMAGE_WIDTH = 1024;
const int IMAGE_HEIGHT = IMAGE_WIDTH;

void Refection::onPluginLoad()
{
	GLWidget & g = *glwidget();
	g.makeCurrent();
     // Carregar shader, compile & link
    m_pVs = new QOpenGLShader(QOpenGLShader::Vertex, this);
    m_pVs->compileSourceFile(g.getPluginPath()+"/../refection/refection.vert");

    m_pFs = new QOpenGLShader(QOpenGLShader::Fragment, this);
    m_pFs->compileSourceFile(g.getPluginPath()+"/../refection/refection.frag");

    m_pProgram = new QOpenGLShaderProgram(this);
    m_pProgram->addShader(m_pVs);
    m_pProgram->addShader(m_pFs);
    m_pProgram->link();


    // Setup texture
    g.glActiveTexture(GL_TEXTURE0);
    g.glGenTextures( 1, &m_textureId);
    g.glBindTexture(GL_TEXTURE_2D, m_textureId);
    g.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    g.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    g.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR );
    g.glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    g.glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, glwidget()->width(), glwidget()->height(), 0, GL_RGB, GL_FLOAT,
                 NULL);
    g.glBindTexture(GL_TEXTURE_2D, 0);

    // Create & bind empty VAO
    g.glGenVertexArrays(1, &m_VAO_rect);
    g.glBindVertexArray(m_VAO_rect);

    // Create VBO with (x,y,z) coordinates
    float coords[] = { -1, -1, -1,
                       1,  -1, -1,
                       -1,  -1,  1,
                       1,  -1,  1 };

    GLuint VBO_coords;
    g.glGenBuffers(1, &VBO_coords);
    g.glBindBuffer(GL_ARRAY_BUFFER, VBO_coords);
    g.glBufferData(GL_ARRAY_BUFFER, sizeof(coords), coords, GL_STATIC_DRAW);
    g.glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    g.glEnableVertexAttribArray(0);
    g.glBindVertexArray(0);
}

bool Refection::paintGL()
{
	GLWidget & g = *glwidget();
	 // Pass 1. Draw scene reversed and store it to the texture
	 g.glClearColor(1,1,1,0);
    g.glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    if (drawPlugin()) drawPlugin()->drawScene();

    m_pProgram->bind();
    m_pProgram->setUniformValue("factor", (float)-1.0);
    m_pProgram->setUniformValue("texture", false);
    m_pProgram->setUniformValue("colorMap", 0);
    m_pProgram->setUniformValue("SIZE", QVector2D(glwidget()->width(), glwidget()->height()));
    
    m_pProgram->setUniformValue("radius", scene()->boundingBox().radius());
    m_pProgram->setUniformValue("boundingMin", scene()->boundingBox().min());
    m_pProgram->setUniformValue("boundingMax", scene()->boundingBox().max());
    
    m_pProgram->setUniformValue("modelViewProjectionMatrix", g.camera()->projectionMatrix()*g.camera()->viewMatrix());
    m_pProgram->setUniformValue("modelViewMatrix", g.camera()->viewMatrix());
    m_pProgram->setUniformValue("normalMatrix", g.camera()->viewMatrix().normalMatrix());

    // Ligth specs
    m_pProgram->setUniformValue("lightAmbient", QVector4D(1., 1., 1., 1.));
    m_pProgram->setUniformValue("lightDiffuse", QVector4D(1., 1., 1., 1.));
    m_pProgram->setUniformValue("lightSpecular", QVector4D(1., 1., 1., 1.));
    m_pProgram->setUniformValue("lightPosition", QVector4D(100., 100., 100., 1.));

    m_pProgram->setUniformValue("matAmbient", QVector4D(.5, .4, .0, 1.));
    m_pProgram->setUniformValue("matDiffuse", QVector4D(.5, .4, .0, 1.));
    m_pProgram->setUniformValue("matSpecular", QVector4D(1., 1., 1., 1.));
    m_pProgram->setUniformValue("matShininess", (float) 30.);

    drawPlugin()->drawScene();

    // Get texture
    g.glBindTexture(GL_TEXTURE_2D, m_textureId);
    g.glCopyTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 0, 0, glwidget()->width(), glwidget()->height());
    g.glGenerateMipmap(GL_TEXTURE_2D);

    // Pass 2 Draw Scene norma;
    g.glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    m_pProgram->setUniformValue("factor", (float)1.0);

    
    drawPlugin()->drawScene();

    // Pass 3 Draw quad using texture
    m_pProgram->setUniformValue("texture", true);
    g.glBindVertexArray(m_VAO_rect);
    g.glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    g.glBindVertexArray(0);

    m_pProgram->release();
    g.glBindTexture(GL_TEXTURE_2D, 0);

    return true;
}

