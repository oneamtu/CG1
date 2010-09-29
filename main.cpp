
#include "TriangleMesh.h"

using namespace std;

TriangleMesh trig;

int main(int argc, char **argv)
{
	if (argc >  1)  {
		trig.loadFile(argv[1]);
	}
	else {
		cerr << argv[0] << " <filename> " << endl;
		//exit(1);
	}
}
