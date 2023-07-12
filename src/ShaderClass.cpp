/*
 * Class for handling parsing and creation of shaders
 */

#include "ShaderClass.h"

// Function to parse text file containing shaders
static ShaderClass::ShaderProgramSrc ParseShader(const std::string& path)
{
    // Open file containing shaders
    std::ifstream stream(path);

    // Using an enum to signify shader type
    enum class shaderType
    {
        NONE = -1,
        VERTEX = 0,
        FRAGMENT = 1,
    };

    shaderType type = shaderType::NONE;
    std::string line;
    std::stringstream ss[2];

    // While there are lines to read in the file
    while (getline(stream, line))
    {
        // If line contains the shader identification
        if (line.find("#shader") != std::string::npos)
        {
            // If the line is where the vertex shader starts
            if (line.find("vertex") != std::string::npos)
                // Set enum type to vertex
                type = shaderType::VERTEX;
            // If the line is where the fragment shader starts
            else if (line.find("fragment") != std::string::npos)
                type = shaderType::FRAGMENT;
        }
        else
        {
            // Use the type to signify the index of the stringstream array then add each line to that stringstream
            ss[(int)type] << line << '\n';
        }
    }

    // Return each respective index of the stringstream to the struct as a string
    return { ss[0].str(), ss[1].str()};
}

// Taking in shader source code to compile each shader and return an identifer for the shader
static GLuint CompileShader(unsigned int type, const std::string& source)
{
    // Declaring variables for error reporting
    int compileResult;
    char infoLog[512];

    // Create a shader object with the type specified (vertex, fragment etc.)
    GLuint id = glCreateShader(type);
    const char* sourceRaw = source.c_str();           // Converting source string into raw string rather than a C++ string

    // Specify shader source. Calling the shader id, 1 for only a single source code, and a pointer to the source
    glShaderSource(id, 1, &sourceRaw, nullptr);
    glCompileShader(id);

    glGetShaderiv(id, GL_COMPILE_STATUS, &compileResult);       // Storing result of compilation

    // Printing error if shader failed to compile
    if (compileResult == GL_FALSE)
    {
        glGetShaderInfoLog(id, 512, NULL, infoLog);
        std::cout << "ERROR: SHADER COMPILATION FAILED\n" << infoLog << std::endl;
        glDeleteShader(id);

        return 0;
    }

    return id;
}

// Calling compile function and combining all individual shaders
static GLuint CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
    int success = 0;    // Error reporting variable
    char infoLog[512];  // Error reporting variable

    GLuint program = glCreateProgram();
    GLuint vShader = CompileShader(GL_VERTEX_SHADER, vertexShader);       // Compile vertex shader
    GLuint fShader = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);   // Compile fragment shader

    glAttachShader(program, vShader);       // Attach compiled vertex shader to the program
    glAttachShader(program, fShader);       // Attach compiled fragment shader to the program

    glLinkProgram(program);                 // Link and validate the program. Stores the programs state in a callable way
    glValidateProgram(program);

    // Check to ensure shader was linked properly
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(program, sizeof(infoLog), NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;

        return 0;
    }

    glDeleteShader(vShader);                // Deleting intermediate compilation files as they are no longer needed
    glDeleteShader(fShader);

    return program;
}

// Constructor which takes in shader file, parses it, compiles the shaders, and sets the ID for the program
ShaderClass::ShaderClass()
{
    ShaderProgramSrc source = ParseShader("res/shaders/default.shader");
    ID = CreateShader(source.VertexSource, source.FragmentSource);
    ShaderProgramSrc sourceLight = ParseShader("res/shaders/light.shader");
    lightID = CreateShader(sourceLight.VertexSource, sourceLight.FragmentSource);
}

// Activates the Shader Program
void ShaderClass::Activate()
{
    glUseProgram(ID);
}

// Deactivates the Shader Program
void ShaderClass::Deactivate()
{
    glUseProgram(0);
}

// Deletes the Shader Program
void ShaderClass::Delete()
{
    glDeleteProgram(ID);
}

void ShaderClass::ActivateLight()
{
    glUseProgram(lightID);
}

void ShaderClass::DeactivateLight()
{
    glUseProgram(0);
}

void ShaderClass::DeleteLight()
{
    glDeleteProgram(lightID);
}