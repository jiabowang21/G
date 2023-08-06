#ifndef _ISAFLOOR_H
#define _ISAFLOOR_H

#include "plugin.h" 
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>


class Isafloor: public QObject, public Plugin
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "Plugin") 
	Q_INTERFACES(Plugin)

  	public:
	 	void onPluginLoad();
	 	void preFrame();
	 	void postFrame();

  	private:
		float ambda;
		QOpenGLShaderProgram* program;  //programa
    	QOpenGLShader *fs, *vs;         //vertex shader y fragment shader
};

#endif
