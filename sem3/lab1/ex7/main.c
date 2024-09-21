#include "ex7.h"


int main(int argc, char ** argv){
    kOpts opt = 0;
	int (*handlers[6])(char **) = {HandlerOptR};

	if (GetOpts(argc, argv, &opt)) {
		printf("%s", "Incorrect option\n");
		return 1;
	}
	int mistake = handlers[opt](argv);
    switch (mistake)
    {
    case 1:
        printf("Input files didnt open\n");
        return 1;
    case 2:
        printf("Output files didnt open\n");
        return 1;
    case 3:
        printf("Mistake in reading file\n");
        return 1;
    default:
        break;
    }

}