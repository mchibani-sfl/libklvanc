/*
 * Copyright: TODO.
 *
 */

#include <stdio.h>
#include <string.h>
#include <assert.h>

#define LOG_DEBUG(...)  printf("[D] "); printf (__VA_ARGS__); printf("\n")
#define LOG_WARN(...)   printf("[W] "); printf (__VA_ARGS__); printf("\n")
#define LOG_ERROR(...)  printf("[E] "); printf (__VA_ARGS__); printf("\n")
#define LOG_MSG(...)  printf (__VA_ARGS__); printf("\n")

#ifdef _WINDOWS
#define TOOLS_COUNT 2
#else
#define TOOLS_COUNT 8
#endif

/* External tool hooks */
extern int demo_main(int argc, char *argv[]);
extern int smpte12_2_main(int argc, char *argv[]);
#ifndef _WINDOWS
extern int parse_main(int argc, char *argv[]);
extern int smpte2038_main(int argc, char *argv[]);
extern int scte104_main(int argc, char *argv[]);
extern int genscte104_main(int argc, char *argv[]);
extern int eia708_main(int argc, char *argv[]);
extern int afd_main(int argc, char *argv[]);
#endif

typedef int (*func_ptr)(int, char *argv[]);

struct app_s
{
    char *name;
    func_ptr func;
};

// Gets the index of tool.
// On success, the tool name will be removed from the arguments list
// in order to pass the arguments as the tool expects them.
int getToolIndex(int* argc, char* argv[], int toolsCount, const struct app_s tools[])
{
    if (*argc == 1) {
        LOG_DEBUG("No tool specified, running the demo ...");
        return 0;
    }

    char *const param = argv[1];
    int ind = 0;
    while (param[ind] != 0 && param[ind] == '-') {
        ind ++;
    }

    if (param[ind] == 0) {
        LOG_ERROR("Invalid argument: %s", param);
        return -1;
    }

    if (strcmp(&param[ind], "h") == 0 || strcmp(&param[ind], "help") == 0) {
        // Print the help.
        return toolsCount;
    }


    int toolIndex = -1;
    for (int i=0; i < toolsCount; i++) {
        if (strcmp(&param[ind], tools[i].name) == 0) {
            toolIndex = i;
            break;
        }
    }

    if (toolIndex == -1) {
        LOG_ERROR("Tool [%s] not found", &param[ind]);
        return toolsCount;
    }

    // Remove the tool name from the arg list
    for (int i=2; i < *argc; i++) {
        argv[i-1] = argv[i];
    }
    *argc -= 1;

    return toolIndex;
}

int main(int argc, char *argv[])
{
    struct app_s tools[TOOLS_COUNT + 1] = {
        {
            "demo",
            demo_main,
        },
        {
            "smpte12_2",
            smpte12_2_main,
        },
#ifndef _WINDOWS
        {
            "parse",
            parse_main,
        },
        {
            "smpte2038",
            smpte2038_main,
        },
        {
            "scte104",
            scte104_main,
        },
        {
            "eia708",
            eia708_main,
        },
        {
            "genscte104",
            genscte104_main,
        },
        {
            "afd",
            afd_main,
        },
#endif // !_WINDOWS
        {0, 0},
    };

    int index = getToolIndex(&argc, argv, TOOLS_COUNT, tools);
    if (index < 0) {
        LOG_ERROR("Failed to get the tool index");
        return -1;
    }
    
    if (index == TOOLS_COUNT) {
        LOG_MSG("List of available tools");
        for (int i=0; i < TOOLS_COUNT; i++) {
            LOG_MSG("- %s", tools[i].name);
        }
        return 0;
    }

    assert(index < TOOLS_COUNT);
    struct app_s *app = &tools[index];
    assert(app->func != NULL);
    return app->func(argc, argv);
}

