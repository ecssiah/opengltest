#include <stdio.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "jsk.h"
#include "jsk_gl.h"

#define WINDOW_WIDTH 1024
#define WINDOW_HEIGHT 768
#define WINDOW_TITLE "OpenGL Test"

typedef struct VertexData VertexData;
struct VertexData
{
    f32 position_array[3];
    f32 color_array[3];
};

int main()
{
    if (!glfwInit())
    {
      	printf("Failed to init GLFW\n");
	
	return False;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH,	WINDOW_HEIGHT, WINDOW_TITLE, NULL, NULL);

    if (!window)
    {
	printf("Failed to create window\n");
	return False;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGL())
    {
	printf("Failed to load OpenGL\n");
	return False;
    }

    char* vert_src = read_file("assets/shaders/test.vert");
    char* frag_src = read_file("assets/shaders/test.frag");
    
    GLuint vert_shader = compile_shader(GL_VERTEX_SHADER, vert_src);
    GLuint frag_shader = compile_shader(GL_FRAGMENT_SHADER, frag_src);

    GLuint program_id = glCreateProgram();
    glAttachShader(program_id, vert_shader);
    glAttachShader(program_id, frag_shader);
    glLinkProgram(program_id);

    glDeleteShader(vert_shader);
    glDeleteShader(frag_shader);

    free(vert_src);
    free(frag_src);

    VertexData vertex_array[] = {
	{
	    {-0.5f, -0.5f, +0.0f},
	    {+1.0f, +0.0f, +0.0f}
	},
	{
	    {+0.5f, -0.5f, +0.0f},
	    {+0.0f, +1.0f, +0.0f}
	},
	{
	    {+0.0f, +0.5f, +0.0f},
	    {+0.0f, +0.0f, +1.0f}
	},
    };

    GLuint vao_id;
    GLuint vbo_id;

    glGenVertexArrays(1, &vao_id);
    glGenBuffers(1, &vbo_id);

    glBindVertexArray(vao_id);

    glBindBuffer(GL_ARRAY_BUFFER, vbo_id);

    glVertexAttribPointer(
	0,
	3,
	GL_FLOAT,
	GL_FALSE,
	sizeof(VertexData),
	(void*)0
    );

    glVertexAttribPointer(
	1,
	3,
	GL_FLOAT,
	GL_FALSE,
	sizeof(VertexData),
	(void*)(offsetof(VertexData, color_array))
    );

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_array), vertex_array, GL_STATIC_DRAW);

    while (!glfwWindowShouldClose(window))
    {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
	    glfwSetWindowShouldClose(window, 1);
	}
	
	glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(program_id);
        glBindVertexArray(vao_id);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
}
