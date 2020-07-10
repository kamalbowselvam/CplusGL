#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>

static int CompileShader(unsigned int type, const std::string& source){

    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id,1,&src,nullptr);
    glCompileShader(id);

    int result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    
    if(result == GL_FALSE){
        
        int length;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
        
        char* message = (char*)alloca(length * sizeof(char));
        glGetShaderInfoLog(id, length, &length, message);
        std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader!" << std::endl;
        std::cout << message << std::endl;
        glDeleteShader(id);
        return 0;
    }

    return id;
}


static int CreateShader(const std::string& vertexShader, const std::string& fragmentShader){

    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

    glAttachShader(program,vs);
    glAttachShader(program,fs);
    glLinkProgram(program);
    glValidateProgram(program);

    glDeleteShader(vs);
    glDeleteShader(fs);

    return program;

}




int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);



    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK){
        std::cout << "Error ! Glew" << std::endl;
    }

    std::cout << glGetString(GL_VERSION) << std::endl;
    printf("Supported GLSL version is %s.\n", (char *)glGetString(GL_SHADING_LANGUAGE_VERSION));

    // 3 vertex
    float positions[6] = {
        -0.5f, -0.5f,
         0.0f, 0.5f,
         0.5f, -0.5f,
    };

     float positionsx[6] = {
        -0.75f, -0.25f,
         1.0f, 0.25f,
         0.5f, -0.25f,
    };


    unsigned int buffer;
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(float), positions, GL_STATIC_DRAW);
    /// Tell openGL layout of the buffer data 

    GLuint vao = 0; // vertex array object
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE, 2 * sizeof(float), 0);


    std::string vertexShader = 
        "#version 330 \n"
        "\n"
        ""
        "layout(location = 0) in vec4 position;\n"
        "\n"
        "void main()\n"
        "{\n"
        " gl_Position = position; \n"
        "}\n";

    std::string fragmentShader = 
        "#version 330 core\n"
        "\n"
        ""
        "layout(location = 0) out vec4 color;\n"
        "\n"
        "void main()\n"
        "{\n"
        " color = vec4(1.0,0.0,0.0,1.0); \n"
        "}\n";

    unsigned int program = CreateShader(vertexShader,fragmentShader);
    glUseProgram(program);
    //glBindVertexArray(vao);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT );

        // function to draw the data from the buffer 
        // shaders read the data and display on the monitor 
        // shader reads the buffer while running eg. vertex , texture cordinates etc etc 

        glDrawArrays(GL_TRIANGLES,0,3);
        /* Swap front and back buffers */
        glfwSwapBuffers(window);
        /* Poll for and process events */
        glfwPollEvents();
    }

    glDeleteProgram(program);

    glfwTerminate();
    return 0;
}