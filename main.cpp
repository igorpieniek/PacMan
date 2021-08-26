#define STB_IMAGE_IMPLEMENTATION


#include "PacManApp.h"

int main() {
	try {
		PacManApp app;
		return app.process();
	}
	catch (std::exception& err) {
		std::cerr << err.what() << std::endl;
		system("pause");
		exit(1);
	}

}