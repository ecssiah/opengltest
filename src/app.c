#include "app.h"

#include <stdlib.h>
#include <stdio.h>
#include <GLFW/glfw3.h>

#include "jsk.h"

App* app_create()
{
  App* app = malloc(sizeof (App));

  return app;
}

void app_destroy(App* app)
{
  free(app);
}

boolean app_init(App* app)
{
  int glfw_result = glfwInit();

  printf("%d", glfw_result);
  
  return True;
}
