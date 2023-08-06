#include "modelInfo2.h"
#include "glwidget.h"

// número total d’objectes carregats, 
// número total de polígons, 
// número total de vèrtexs, 
// i el percentatge de polígons que són triangles
void ModelInfo2::printModelInfo2() {
  	// do count
  	Scene* scn = scene();
  	nobj = scn -> objects().size();
  	npol = nver = ntri = 0;
  	for (int i = 0; i < (int)scn -> objects().size(); ++i) {
    	const Object &obj = scn->objects()[i];
    	for (int  j = 0; j < (int)obj.faces().size(); ++j) {
      		const Face &face = obj.faces()[j];
      		int fver = face.numVertices();
      		++npol;
      		nver += fver;
      		ntri += fver == 3;
    	}
  	}
}

void ModelInfo2::onPluginLoad()
{
	printModelInfo2();
}

void ModelInfo2::postFrame()
{
	printModelInfo2();
	painter.begin(glwidget());
    QFont font;
    font.setPixelSize(15);
    painter.setFont(font);
    int x = 20;
    int y = 350;

    painter.drawText(x, y, QString("INFO: "));
    painter.drawText(x, y + 20, QString(" - Objectes: %1").arg(nobj));
    painter.drawText(x, y + 40, QString(" - Polígons: %1").arg(npol));
    painter.drawText(x, y + 60, QString(" - Vèrtexs: %1").arg(nver));
    painter.drawText(x, y + 80, QString(" - Triangles: %1").arg(ntri));
    if (npol != 0) painter.drawText(x, y + 100, QString(" - Percentatge de triangles: %1%").arg(double(ntri/npol) * 100));
    else painter.drawText(x, y + 100, QString(" - Percentatge de triangles: NULL"));
    painter.end();
}

void ModelInfo2::onObjectAdd()
{
	printModelInfo2();
}


