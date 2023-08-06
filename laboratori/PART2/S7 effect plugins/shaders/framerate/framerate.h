#ifndef _FRAMERATE_H
#define _FRAMERATE_H

#include "plugin.h" 
#include <QPainter>

class Framerate: public QObject, public Plugin
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "Plugin") 
	Q_INTERFACES(Plugin)

	public:
		void onPluginLoad();
	 	void preFrame();
	 	void postFrame();
	
	private:
      	int frames;
		QPainter painter;

  	public slots:
      	void printFPS();
};

#endif
