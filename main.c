#include <stdio.h>
#include <stdlib.h>
#include <GL/gl3w.h>
#include <GLFW/glfw3.h>

#include "common/globals.h"
#include "mineMap/mineMap.h"
#include "texture/textureProgram.h"

static int width = 600, height = 600;

MineMap_t m;

static void display(GLFWwindow *window)
{
	glClearColor(0.2, 0.2, 0.2, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    vec4 a;
    MineMap_render( &m, a );
	glfwSwapBuffers(window);
}

static void reshape(GLFWwindow *window, int w, int h)
{
	width = w > 1 ? w : 1;
	height = h > 1 ? h : 1;
	glViewport(0, 0, width, height);
	glClearDepth(1.0);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glEnable(GL_DEPTH_TEST);
	G_Globals.aspectRatio = ( float ) width / height; 

}

int main(int argc, char **argv)
{
	GLFWwindow *window;

	glfwInit();

    MineMap_assignSize( &m, 16, 16 );

	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	window = glfwCreateWindow(width, height, "cookie", NULL, NULL);

	glfwSetFramebufferSizeCallback(window, reshape);
	glfwSetWindowRefreshCallback(window, display);
	
	glfwMakeContextCurrent(window);

	if ( gl3wInit() ) {
		fprintf(stderr, "failed to initialize OpenGL\n");
		return -1;
	}
	if ( !gl3wIsSupported( 3, 2 ) ) {
		fprintf(stderr, "OpenGL 3.2 not supported\n");
		return -1;
	}

	Texture_t t;
	Texture_init( 16, 16, &t );

	TextureProg_t tP;
	tP.dataAndCommands = malloc(700);
	DataForLine_t d4l;
	d4l.x0 = 0;
	d4l.x1 = 16;
	d4l.y0 = 0;
	d4l.y1 = 16;
	d4l.rgba = 0xffff00ff;

	*tP.dataAndCommands = 1;
	memcpy( tP.dataAndCommands+1, &d4l, sizeof( DataForLine_t ) );
	tP.dataAndCommands[ sizeof( DataForLine_t ) + 1 ] = 0;
	TextureProg_run( &tP, &t );

    MineMap_renderPrepare( &m, &t );


	printf("OpenGL %s, GLSL %s\n", glGetString(GL_VERSION),
	       glGetString(GL_SHADING_LANGUAGE_VERSION));

	while (!glfwWindowShouldClose(window)) {
		display(window);
		glfwPollEvents();
	}
	
	glfwTerminate();
	return 0;
}