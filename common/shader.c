#include "shader.h"

const char *vertexShaderSource = 
    "#version 330 core\n"
    "layout (location = 0) in vec2 aPos;\n"
    "layout (location = 1) in vec2 aTexCoord;\n"
    "uniform float aspectRatio;\n"
    "uniform float cellSize;\n"
    "out vec2 texCoord;\n"
    "out vec3 fColor;\n"
    "uniform vec2 offsets[1024]; \n"
    "void main()\n"
    "{\n"
    "    vec2 pos = aPos * cellSize + offsets[gl_InstanceID];\n"
    "    pos.x /= aspectRatio;\n"
    "    gl_Position = vec4(pos, 0.0, 1.0);\n"
    "    texCoord = aTexCoord;\n"
    "}";


const char *fragmentShaderSource = 
    "#version 330 core\n"
    "out vec4 FragColor;\n"
    "in vec3 fColor;\n"
    "in vec2 texCoord;\n"
    "uniform sampler2D tex;"
    "void main()\n"
    "{\n"
    "    FragColor = texture(tex, texCoord);\n"
    "}";

GLuint compileShader(const char* prog, GLenum shaderType) {
    unsigned int shader;
    shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &prog, NULL);
    glCompileShader(shader);
    int  success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if(!success) {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        printf("ERROR::SHADER::VERTEX::COMPILATION_FAILED %s\n", infoLog);
    }
    return shader;
}

GLuint getBasicProgram() {
    GLuint vert = compileShader(vertexShaderSource, GL_VERTEX_SHADER);
    GLuint frag = compileShader(fragmentShaderSource, GL_FRAGMENT_SHADER);
    GLuint shaderProgram;
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vert);
    glAttachShader(shaderProgram, frag);
    glLinkProgram(shaderProgram);
    return shaderProgram;
}