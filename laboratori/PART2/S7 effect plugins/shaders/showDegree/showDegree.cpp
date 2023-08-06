#include "showDegree.h"
#include "glwidget.h"

void ShowDegree::onPluginLoad()
{
	const Object &obj = scene() -> objects()[0];
    const int nCares = obj.faces().size();
    const int nVertexCares = nCares*3; // cada cara te 3 vertex (trianges)
    const int nVertex = obj.vertices().size();
    degree = double(nVertexCares)/nVertex;
}


void ShowDegree::preFrame()
{

}

void ShowDegree::postFrame()
{
	painter.begin(glwidget());
    QFont font;
    font.setPixelSize(15);
    painter.setFont(font);
    int x = 20;
    int y = 20;
    painter.drawText(x, y, QString("DEGREE: %1").arg(degree));
    painter.end();
}


