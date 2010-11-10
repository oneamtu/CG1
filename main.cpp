#include "TriangleMesh.h"
#include "Image.h"
#include "Vector.h"

using namespace std;

//where the magic happens
int main(int argc, char **argv)
{
	if (argc >  1)  {
		TriangleMesh trig(argv[1]);
		Camera cam(0.78f, Vector3f(0.0f, 0.0f, -11.0f));
		Image i(&cam);
		trig.translate(cam.getLocation());
		trig.update();
		cout<<"Projecting vertices ..."<<endl;
		i.projectTriangleMesh(&trig);
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
