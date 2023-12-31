#ifndef _MODELINFO2_H
#define _MODELINFO2_H

#include "plugin.h" 
#include <QPainter>

class ModelInfo2: public QObject, public Plugin
{
		Q_OBJECT
		Q_PLUGIN_METADATA(IID "Plugin") 
		Q_INTERFACES(Plugin)

  	public:
	 	void printModelInfo2();
	 	void onPluginLoad();
	 	void postFrame();

	 	void onObjectAdd();
	private:
		QPainter painter;
		int nobj, npol, nver, ntri;
};

#endif
