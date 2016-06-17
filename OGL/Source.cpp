#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Shader.h"

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

bool isWireFrameOn = false;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    // When a user presses the escape key, we set the WindowShouldClose property to true, 
    // closing the application
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_TRUE);
    else if (key == GLFW_KEY_W && action == GLFW_PRESS)
        isWireFrameOn = !isWireFrameOn;
}

// Window dimensions
const GLuint WIDTH = 800, HEIGHT = 600;

string readFile(const char* file)
{
    string content;
    ifstream fs(file, ios::in);

    if (!fs.is_open())
    {
        cerr << "Could not open file " << file << endl;
    }

    string line = "";
    while (!fs.eof())
    {
        getline(fs, line);
        content.append(line + "\n");
    }

    fs.close();
    return content;
}

int main()
{
    // Init GLFW and set options
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    // Create GLFW window
    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Hello OpenGL", nullptr, nullptr);
    if (window == nullptr)
    {
        cout << "Failed to create GLFW window" << endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Set keypress Callbacks
    glfwSetKeyCallback(window, key_callback);

    glewExperimental = GL_TRUE;
    // Initialize GLEW
    if (glewInit() != GLEW_OK)
    {
        cout << "Failed to initialize GLEW" << endl;
        return -1;
    }

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);

    Shader myShader("vs.glsl", "fs.glsl");

    // Specify unique vertex data
    GLfloat vertices[] = {
         0.5f,  0.5f,  0.0f,  // Top Right
         0.5f, -0.5f,  0.0f,  // Bottom Right
        -0.5f,  0.5f,  0.0f,  // Top Left
        -0.5f, -0.5f,  0.0f   // Bottom Left
    };

    GLfloat vertex_colors[] = {
        1.0f,  0.0f,  0.0f,  // Top Right Color
        0.0f,  1.0f,  0.0f,  // Bottom Right Color
        0.0f,  0.0f,  1.0f,  // Top Left Color
        0.0f,  0.0f,  0.0f   // Bottom Left Color
    };


    // Vertices for 2 triangles
    GLfloat vertices1[] = {
        // Triangle 1
        -0.9f, -0.5f, 0.0f,
        -0.5f, 0.5f, 0.0f,
        -0.1f, -0.5f, 0.0f
    };
    GLfloat vertices2[] = {
        // Triangle 2
        0.1f, 0.5f, 0.0f,
        0.9f, 0.5f, 0.0f,
        0.5f, -0.5f, 0.0f
    };

    // Specify triangles to draw
    GLuint indices[] = {
        0, 1, 2, // First Triangle
        1, 3, 2  // Second Triangle
    };

    GLuint EBO, VBO, VAO;
    glGenBuffers(1, &EBO);
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    // Vertex Init
    // 1. Bind VAO
    glBindVertexArray(VAO);
    // 2. Bind and copy index array into EBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
    // 3. Bind and copy vertex array into VBO
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices)+sizeof(vertex_colors), NULL, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
    glBufferSubData(GL_ARRAY_BUFFER, sizeof(vertices), sizeof(vertex_colors), vertex_colors);
    // 4. Set Vertex Attribute Pointer
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)(sizeof(vertices)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // 5.  Unbind VAO but not the EBO
    glBindVertexArray(0);



    // Game loop
    while (!glfwWindowShouldClose(window))
    {
        // Check and call events
        glfwPollEvents();
        if (isWireFrameOn)
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        }
        else
        {
            glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        }

        // Rendering commands
        // Clear the color buffer
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Calculate color
        GLfloat timeValue = glfwGetTime();
        GLfloat greenValue = (sin(timeValue) / 2) + 0.5;
        GLuint ourColorLocation = glGetUniformLocation(myShader.GetProgram(), "ourColor");
        myShader.Use();
        glUniform4f(ourColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

        // Draw triangles
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        //glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);

        // Swap the buffers
        glfwSwapBuffers(window);
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    glfwTerminate();
    return 0;
}