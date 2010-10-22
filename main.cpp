
#include "TriangleMesh.h"
#include "Image.h"
#include "Vector.h"

using namespace std;

TriangleMesh trig;

int main(int argc, char **argv)
{
	if (argc >  1)  {
		trig.loadFile(argv[1]);
		Image i;
		trig.translate(Vector3f(0.0f, 0.0f, 2000.0f));
		cout<<"Projecting vertices ..."<<endl;
		i.projectTriangleMesh(trig);
		//i.projectVertices(trig.getVertices());
		cout<<"Creating ppm file ..."<<endl;
		i.output("image.ppm");
		//i.clear();

	}
	else {
		cerr << argv[0] << " <filename> " << endl;
		//exit(1);
	}
}
