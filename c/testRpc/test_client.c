/*
 * This is sample code generated by rpcgen.
 * These are only templates and you can use them
 * as a guideline for developing your own functions.
 */

#include "test.h"


void
test_prog_2(char *host)
{
	CLIENT *clnt;
	struct TEST  *result_1;
	struct TEST  test_proc_2_arg;
	char * *result_2;
	char * test_proc2_2_arg = "a a a aaaa aaaaaaa!!";

    //input parameter cannot be null or will get RPC: Can't encode arguments error
#ifndef	DEBUG
	clnt = clnt_create (host, TEST_PROG, TEST_VER, "udp");
	if (clnt == NULL) {
		clnt_pcreateerror (host);
		exit (1);
	}
#endif	/* DEBUG */

    char c;

    printf("choose the operation:\n\t0---ADD\n\t1---SUB\n\t2---MUL\n\t3---DIV\n");
    c = getchar();
    switch(c) {
        case '0':
            test_proc_2_arg.op = ADD;
            break;
        case '1':
            test_proc_2_arg.op = SUB;
            break;
        case '2':
            test_proc_2_arg.op = MUL;
            break;
        case '3':
            test_proc_2_arg.op = DIV;
            break;
        default:
            printf("error:operate/n");
            exit(1);
    }
    printf("input the first number:");
    scanf("%f", &test_proc_2_arg.arg1);

    printf("input the second number:");
    scanf("%f", &test_proc_2_arg.arg2);

	result_1 = test_proc_2(&test_proc_2_arg, clnt);
	if (result_1 == (struct TEST *) NULL) {
		clnt_perror (clnt, "call failed");
	}
    
	result_2 = test_proc2_2(&test_proc2_2_arg, clnt);
	if (result_2 == (char **) NULL) {
		clnt_perror (clnt, "call failed");
	}
    
    printf("receive %s %.3f\n", *result_2, result_1->result);
#ifndef	DEBUG
	clnt_destroy (clnt);
#endif	 /* DEBUG */
}


int
main (int argc, char *argv[])
{
	char *host;

	if (argc < 2) {
		printf ("usage: %s server_host\n", argv[0]);
		exit (1);
	}
	host = argv[1];
	test_prog_2 (host);
exit (0);
}
