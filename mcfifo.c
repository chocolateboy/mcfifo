#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define MCFIFO_BUFSIZE 1024
#define MCFIFO_ARGS_LENGTH 32768 /* Windows default/max */
#define MCFIFO_USAGE 1
#define MCFIFO_BAD_ARGS 2
#define MCFIFO_BAD_CREATE 3
#define MCFIFO_BAD_CONNECT 4
#define MCFIFO_BAD_PROCESS 5

static char MCFIFO_ARGS[MCFIFO_ARGS_LENGTH] = { 0 };

int usage(char* prgname) {
    fprintf(stderr, "usage: %s \\\\.\\pipe\\name cmd [ arg1, ... ]\r\n", prgname);
    return MCFIFO_USAGE;
}

int append(size_t offset, const char *str, size_t len) {
    if ((offset + len) >= MCFIFO_ARGS_LENGTH) {
        fprintf(stderr, "Error: Args length exceeds buffer size (%u bytes)\r\n", MCFIFO_ARGS_LENGTH);
        /*
            fprintf(stderr, "OFFSET: %u\r\n", offset);
            fprintf(stderr, "LEN: %u\r\n", len);
            fprintf(stderr, "ARGSLEN: %u\r\n", MCFIFO_ARGS_LENGTH);
        */
        exit(MCFIFO_BAD_ARGS);
    } else {
        strncat(MCFIFO_ARGS + offset, str, len);
    }

    return offset + len;
}

int main(int argc, char **argv) {
    char *pipe, *cmd;
    int i;
    size_t j;
    HANDLE hPipe;
    STARTUPINFOA stinfo = { 0, NULL, NULL, NULL, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, NULL, NULL, NULL, NULL };
    PROCESS_INFORMATION pinfo = { NULL, NULL, 0, 0 };
    SECURITY_ATTRIBUTES sa = { sizeof(SECURITY_ATTRIBUTES), NULL, TRUE }; // TRUE: allow handles to be inherited

    if (argc < 3)
        return usage(argv[0]);

    pipe = argv[1];
    cmd = argv[2];

    for (i = 2, j = 0; i < argc; ++i) {
        if (i > 2)
            j = append(j, " ", 1);
        j = append(j, argv[i], strlen(argv[i]));
    }

    /*
        fprintf(stderr, "Debug: PIPE: \"%s\"\r\n", pipe);
        fprintf(stderr, "Debug: CMD: \"%s\"\r\n", cmd);
        fprintf(stderr, "Debug: ARGS: \"%s\"\r\n", MCFIFO_ARGS);
    */

    hPipe = CreateNamedPipeA(
        pipe,
        PIPE_ACCESS_DUPLEX,
        PIPE_TYPE_BYTE | PIPE_READMODE_BYTE | PIPE_WAIT,
        PIPE_UNLIMITED_INSTANCES,
        MCFIFO_BUFSIZE,
        MCFIFO_BUFSIZE,
        0,
        &sa
    );

    if (hPipe == INVALID_HANDLE_VALUE) {
        fprintf(stderr, "Error: Can't create named pipe %s: %lu\r\n", pipe, GetLastError());
        return MCFIFO_BAD_CREATE;
    }

    if (ConnectNamedPipe(hPipe, NULL) == 0) {
        fprintf(stderr, "Error: Can't connect to named pipe %s: %lu", pipe, GetLastError());
        CloseHandle(hPipe);
        return MCFIFO_BAD_CONNECT;
    }

    stinfo.cb = sizeof(STARTUPINFO);
    stinfo.dwFlags = STARTF_USESTDHANDLES;
    stinfo.hStdInput = hPipe; /* redirect */
    stinfo.hStdOutput = GetStdHandle(STD_OUTPUT_HANDLE); /* inherit */
    stinfo.hStdError = GetStdHandle(STD_ERROR_HANDLE); /* inherit */

    if (CreateProcess(NULL, MCFIFO_ARGS, 0, 0, TRUE, 0, NULL, NULL, &stinfo, &pinfo)) {
        WaitForSingleObject(pinfo.hProcess, INFINITE);
    } else {
        const char * space = argc > 3 ? " " : "";
        fprintf(stderr, "Error: Can't create process %s%s%s: %lu\r\n", cmd, space, MCFIFO_ARGS, GetLastError());
        CloseHandle(hPipe);
        return MCFIFO_BAD_PROCESS;
    }

    return S_OK;
}
