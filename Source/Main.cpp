#include <iostream>
#include <fstream>
#include <sstream>

#define GLM_FORCE_RADIANS
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/string_cast.hpp>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <Camera.h>
#include <ShaderBuilder.h>
#include <ShaderProgramBuilder.h>
#include <ShaderProgram.h>
#define COMPONENTS_PER_POSITION 4

int Width = 800;
int Height = 600;
float FOV = 90.0f;
float zNear = 0.1f;
float zFar = 100.0f;
Camera MainCamera(Width,Height,FOV,zNear,zFar);

const GLfloat VertexPositions[] = { //Vertex positions in X,Y,Z,W format, W is a scalar that transforms the first 3, typically you will just want to set it to 1 and forget it
	1.0f, 1.0f, 0.0f, 1.0f,
	1.0f, -1.0f, 0.0f, 1.0f,
	-1.0f, -1.0f, 0.0f, 1.0f,
};
const size_t VertexCount = sizeof(VertexPositions)/sizeof(VertexPositions[0])/COMPONENTS_PER_POSITION;
glm::mat4 TransformationMatrix;

ShaderProgram* MainShader;
GLuint MainVAO;

GLFWwindow* MainWindow;

std::string ReadFile(char const * const fname)
{
    std::ifstream ifile(fname);
    std::string filetext;

    while( ifile.good() ) {
        std::string line;
        std::getline(ifile, line);
        filetext.append(line + "\n");
    }

    return filetext;
}

void Setup() {
	//Shader program creation
	ShaderBuilder VertexShader = ShaderBuilder(GL_VERTEX_SHADER);
		std::string VertexSource = ReadFile("Shaders/Projection.v.glsl");
		VertexShader.Add_Source(VertexSource);
	ShaderBuilder FragmentShader = ShaderBuilder(GL_FRAGMENT_SHADER);
		std::string FragmentSource = ReadFile("Shaders/DepthShading.f.glsl");
		FragmentShader.Add_Source(FragmentSource);
	ShaderProgramBuilder MainProgramBuilder = ShaderProgramBuilder();
		MainProgramBuilder.Attach_Shader(VertexShader.Compile());
		MainProgramBuilder.Attach_Shader(FragmentShader.Compile());
		MainProgramBuilder.Declare_Uniform("TransformationMatrix");
	MainShader = MainProgramBuilder.Build();
	MainShader->BindFragDataLocation(0, "FragmentColor"); //tells OpenGL what variable in the fragment shader we will write color data to, and which "color slot" on the framebuffer to put the data into
	MainShader->Activate();
	
	//Create the VBO&VAO for the triangle
	GLuint TriangleVBO;
	glCreateBuffers(1, &TriangleVBO);
		glNamedBufferStorage(TriangleVBO, VertexCount*COMPONENTS_PER_POSITION*sizeof(GLfloat), (void*)VertexPositions, GL_DYNAMIC_STORAGE_BIT);
	
	GLuint VertexAttributeLocation = 0;
	GLuint VertexBufferLocation = 0;
	glCreateVertexArrays(1, &MainVAO);
		glEnableVertexArrayAttrib(MainVAO, VertexAttributeLocation); //Enable the vertex attribute location
		glVertexArrayAttribFormat(MainVAO, VertexAttributeLocation, COMPONENTS_PER_POSITION, GL_FLOAT, GL_FALSE, 0); //Tell opengl that the vertex attribute is made up of four floats that shouldn't be normalized on access, and have no offset(dunno what that actually means lol)
		glVertexArrayVertexBuffer(MainVAO, VertexBufferLocation, TriangleVBO, 0, sizeof(VertexPositions[0])*COMPONENTS_PER_POSITION); //Attach our VBO to the VAO with no offset and a stride the size of four GLfloats, basically telling OpenGL where to find our vertex pos data and how large in bytes each position is
		glVertexArrayAttribBinding(MainVAO, VertexAttributeLocation, VertexBufferLocation); //Bind our vertex attribute to the source of the vertex data
	glBindVertexArray(MainVAO); //Bind the VAO we just created for drawing
	
	glm::vec3 ModelPos = glm::vec3(0.0f,0.0f,0.0f);
	TransformationMatrix = glm::translate(ModelPos);
	
	glm::vec3 CameraPos = glm::vec3(0.0f,0.0f,2.0f);
	MainCamera.Transform = glm::translate(CameraPos);

	glEnable(GL_DEPTH_TEST); //Enable depth testing
	glDepthFunc(GL_LEQUAL); //Sets the depth comparison to <=, meaning fragments with depth values > an already written fragment, will be skipped 
	glDepthRange(0.0f, 1.0f); //Tells OpenGL values written to the depth buffer should be between 0.0f and 1.0f, 0 is close, 1 is far
	glEnable(GL_DEPTH_CLAMP); //Tells opengl to clamp depth values to the previously defined values
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f); //Set the clear color to black
	glClearDepth(1.0f); //Set the depth clear value
}

static void Resize(GLFWwindow* Window, int NewWidth, int NewHeight) {
	glViewport(0,0,NewWidth,NewHeight);
	MainCamera.Projection.SetDimensions((float)NewWidth,(float)NewHeight);
}

void Update() {
	TransformationMatrix = glm::rotate(TransformationMatrix,0.01f,glm::vec3(0.0f,1.0f,0.0f));
}

void Render() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glUniformMatrix4fv(
		MainShader->Get_UniformLocation("TransformationMatrix"),
		1,
		GL_FALSE,
		glm::value_ptr(MainCamera.Projection.GetProjectionMatrix() * glm::inverse(MainCamera.Transform) * TransformationMatrix)
	);
	
	glDrawArrays(GL_TRIANGLES,0,COMPONENTS_PER_POSITION*VertexCount);
	glUniformMatrix4fv(
		MainShader->Get_UniformLocation("TransformationMatrix"),
		1,
		GL_FALSE,
		glm::value_ptr(MainCamera.Projection.GetProjectionMatrix() * glm::inverse(MainCamera.Transform))
	);
	glDrawArrays(GL_TRIANGLES,0,COMPONENTS_PER_POSITION*VertexCount);
}

int main() {
		if (glfwInit()) {
			MainWindow = glfwCreateWindow(Width,Height,"Sup",NULL,NULL);
			if (MainWindow) {
				glfwMakeContextCurrent(MainWindow);
				glfwSetWindowSizeCallback(MainWindow,Resize);
				glewInit();
				Setup();
				while (!glfwWindowShouldClose(MainWindow)) {
					Update();
					Render();
					glfwSwapBuffers(MainWindow);
					glfwPollEvents();
				}
				glfwTerminate();
				return 0;
			} else {
				glfwTerminate();
				return -1;
			}
		} else {
			return -1;
		}
}
