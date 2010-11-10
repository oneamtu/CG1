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

		cout<<"No shading ..."<<endl;
		trig.setShading(NONE);
		i.projectTriangleMesh(&trig);
		i.output("image.ppm");
		i.clear();

		cout<<"Flat shading ..."<<endl;
		trig.setShading(FLAT);
		i.projectTriangleMesh(&trig);
		i.output("image_flat.ppm");
		i.clear();

		cout<<"Gouraud shading ..."<<endl;
		trig.setShading(GOURAUD);
		i.projectTriangleMesh(&trig);
		i.output("image_gouraud.ppm");
		i.clear();

		cout<<"Phong shading ..."<<endl;
		trig.setShading(PHONG);
		i.projectTriangleMesh(&trig);
		i.output("image_phong.ppm");
		i.clear();
	}
	else {
		cerr << argv[0] << " <filename> " << endl;
		//exit(1);
	}
}
