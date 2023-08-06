#include "modelInfo.h"
#include "glwidget.h"
#include <cstdio>

void ModelInfo::printInfo() {
  	// do count
  	Scene* scn = scene();
  	int nobj, npol, nver, ntri;
  	nobj = scn->objects().size();
  	npol = nver = ntri = 0;
  	for (int i = 0; i < (int)scn->objects().size(); ++i) {
    	const Object &obj = scn->objects()[i];
    	for (int j = 0; j < (int)obj.faces().size(); ++j) {
      		const Face &face = obj.faces()[j];
      		int fver = face.numVertices();
      		++npol;
      		nver += fver;
      		ntri += fver == 3;
    	}
  	}
  	// print model info
  	printf("Numero objectes: %d\n", nobj);
  	printf("Numero poligons: %d\n", npol);
  	printf("Numero vertex: %d\n", nver);
  	printf("Percentatge triangles: %f\n\n", ((double)ntri)/npol);
}

void ModelInfo::onPluginLoad()
{
	printInfo();
}

void ModelInfo::postFrame()
{
	printInfo();
}

void ModelInfo::onObjectAdd()
{
	printInfo();	
} 

