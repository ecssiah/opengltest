#ifndef APP_H
#define APP_H 1

#include "jsk.h"

typedef struct App App;
struct App
{
};

App* app_create();
void app_destroy(App* app);

boolean app_init(App* app);

#endif
