#include "jsk.h"

#include <stdio.h>

#include "app.h"

int main()
{
  App* app = app_create();
  app_init(app);

  app_destroy(app);
  
  return 0;
}
