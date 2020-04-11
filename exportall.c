#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <err.h>

static void
usage(void)
{
        errx(1, "usage: exportall { var val ...} prog ...");
}

int
main(int argc, char **argv)
{
        const char *envname, *envval;

        argv++;
        argc--;
        if (argc <= 0) usage();
        while (argc && strcmp(argv[0], "")) {
                if (argc < 2)
                        usage();
                envname = *argv++;
                envval = *argv++;
                argc -= 2;
                /* eat block quoting */
                if (*envname++ != ' ' || *envval++ != ' ')
                        usage();
                if (setenv(envname, envval, 1) < 0)
                        err(1, "setenv");
        }
        /* eat block delimiter */
        if (!argc-- || strcmp(*argv++, "")) usage();
        if (!argc) return 0;
        if (execvp(argv[0], argv) < 0)
                err(1, "execve");
        return 0;
}
