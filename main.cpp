#include <cstdio>

#include "easylogging++.h"

INITIALIZE_EASYLOGGINGPP

int main(int argc, char** argv) {
	START_EASYLOGGINGPP(argc, argv);
	LOG(TRACE) << "Logging initialized.";

	return 0;
}
