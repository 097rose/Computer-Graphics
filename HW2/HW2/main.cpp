#include <iostream>
#include <math.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Object.h"

using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
unsigned int createShader(const char* filename, const char* type);
unsigned int createProgram(unsigned int vertexShader, unsigned int fragmentShader);
unsigned int ModelVAO(Object* model);
void DrawModel(const char* target, glm::mat4 M, glm::mat4 V, glm::mat4 P);
void LoadTexture(unsigned int& texture, const char* tFileName);
glm::mat4 getPerspective();
glm::mat4 getView();
//CardboardBox1
Object* catModel = new Object("obj/cat.obj");
Object* boxModel = new Object("obj/CardboardBox1.obj");
Object* ballModel = new Object("obj/tennis_ball.obj");

unsigned int catVAO, boxVAO, ballVAO;
unsigned int shaderProgram;
unsigned int catTexture, boxTexture, ballTexture, tigerTexture, fireTexture;
int windowWidth = 800, windowHeight = 600;
int deformation = 0;
int change_color = 0;
int bonus_1 = 0;
int bonus_2 = 0;


int main()
{
	
	// Initialization
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
	glfwWindowHint(GLFE_OPENGL_FORWARD_COMPACT, GL_TRUE);
#endif

	GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "HW2", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	glfwSetKeyCallback(window, keyCallback);
	glfwSwapInterval(1);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// Shaders
	unsigned int vertexShader, fragmentShader;
	//unsigned int vertexShader, fragmentShader, shaderProgram;
	vertexShader = createShader("vertexShader.vert", "vert");
	fragmentShader = createShader("fragmentShader.frag", "frag");
	shaderProgram = createProgram(vertexShader, fragmentShader);
	//glUseProgram(shaderProgram);

	// Texture
	//unsigned int catTexture, boxTexture;
	LoadTexture(catTexture, "obj/Cat_diffuse.jpg");
	LoadTexture(ballTexture, "obj/ball.jpg");
	LoadTexture(tigerTexture, "obj/tiger.jpg");
	LoadTexture(fireTexture, "obj/fire.jpg");
	LoadTexture(boxTexture, "obj/CardboardBox1_Albedo.tga");

	// TO DO:
	// Create VAO, VBO
	boxVAO = ModelVAO(boxModel);
	catVAO = ModelVAO(catModel);
	ballVAO = ModelVAO(ballModel);

	// Display loop
	// TO DO:
	// Draw the models with shaders
	glfwGetFramebufferSize(window, &windowWidth, &windowHeight);
	glViewport(0, 0, windowWidth, windowHeight);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);


	while (!glfwWindowShouldClose(window))
	{
		
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glm::mat4 V = getView();
		glm::mat4 P = getPerspective();

		//box
		glm::mat4 model1 = glm::mat4(1.0f);
		glm::mat4 model1_s = glm::mat4(1.0f);
		glm::mat4 model1_r = glm::mat4(1.0f);
		model1_s = glm::scale(model1_s, glm::vec3(0.0625, 0.05, 0.05));
		model1_r = glm::rotate(model1_r, glm::radians(90.0f)*(float)glfwGetTime(), glm::vec3(0, 1, 0));
		model1 = model1_r * model1_s;
		DrawModel("box", model1, V, P);

		if (bonus_1 == 1) {
			//cat
			glm::mat4 model2 = glm::mat4(1.0f);
			glm::mat4 model2_r = glm::mat4(1.0f);
			glm::mat4 model2_rr = glm::mat4(1.0f);
			glm::mat4 model2_s = glm::mat4(1.0f);
			glm::mat4 model2_t = glm::mat4(1.0f);
			model2_t = glm::translate(model2_t, glm::vec3(1.5, 0, 0));
			//model2_s = glm::scale(model2_s, glm::vec3(1.5, 1.5, 1.5));
			model2_rr = glm::rotate(model2_rr, glm::radians(180.0f), glm::vec3(0, 1, 0));
			model2_r = glm::rotate(model2_r, glm::radians(90.0f) * (float)glfwGetTime(), glm::vec3(0, 1, 0));
			model2 = model2_r * model2_t  * model2_rr * model2;
			DrawModel("cat", model2, V, P);

			//ball
			glm::mat4 model3 = glm::mat4(1.0f);
			glm::mat4 model3_r = glm::mat4(1.0f);
			glm::mat4 model3_s = glm::mat4(1.0f);
			glm::mat4 model3_t = glm::mat4(1.0f);
			glm::mat4 model3_tt = glm::mat4(1.0f);
			model3_s = glm::scale(model3_s, glm::vec3(0.5, 0.5, 0.5));

			model3_r = glm::rotate(model3_r, glm::radians(90.0f) * (float)glfwGetTime(), glm::vec3(0, 1, 0));
			model3_t = glm::translate(model3_t, glm::vec3(-0.7, 1.5, -1.0));
			model3_tt = glm::translate(model3_tt, glm::vec3(1.5, 0, 0));
			//model3 =model3_t * model3_r * model3_tt * model3_s * model3;
			model3 = model2_r * model2_t * model3_t*model3_s;
			DrawModel("ball", model3, V, P);
		}
		else {
			//cat
			glm::mat4 model2 = glm::mat4(1.0f);
			glm::mat4 model2_r = glm::mat4(1.0f);
			glm::mat4 model2_rr = glm::mat4(1.0f);
			glm::mat4 model2_s = glm::mat4(1.0f);
			//model2_s = glm::scale(model2_s, glm::vec3(1.5, 1.5, 1.5));
			model2_rr = glm::rotate(model2_rr, glm::radians(90.0f), glm::vec3(0, 1, 0));
			model2_r = glm::rotate(model2_r, glm::radians(90.0f) * (float)glfwGetTime(), glm::vec3(0, 1, 0));
			model2 = model2_r * model2_rr * model2;
			DrawModel("cat", model2, V, P);
		}
		
		
		if (bonus_1 == 2) {
			//ball
			glm::mat4 model3 = glm::mat4(1.0f);
			glm::mat4 model3_r = glm::mat4(1.0f);
			glm::mat4 model3_s = glm::mat4(1.0f);
			glm::mat4 model3_t = glm::mat4(1.0f);
			glm::mat4 model3_tt = glm::mat4(1.0f);
			model3_s = glm::scale(model3_s, glm::vec3(0.5, 0.5, 0.5));

			model3_r = glm::rotate(model3_r, glm::radians(90.0f) * (float)glfwGetTime(), glm::vec3(0, 1, 0));
			model3_t = glm::translate(model3_t, glm::vec3(0, 1.5, 0));
			model3_tt = glm::translate(model3_tt, glm::vec3(1.5, 0, 0));
			model3 = model3_t * model3_r * model3_tt* model3_s * model3;
			DrawModel("ball", model3, V, P);
		}
		
		


		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}

void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	if ((key == GLFW_KEY_1 || key == GLFW_KEY_KP_1) && action == GLFW_PRESS ) {
		deformation = 1;
		//cout << speed;
	}
	else if(action == GLFW_RELEASE){
		deformation = 0;
	}

	if ((key == GLFW_KEY_2 || key == GLFW_KEY_KP_2) && action == GLFW_PRESS) {
		change_color = 1;
		//cout << speed;
	}
	else if (action == GLFW_RELEASE) {
		change_color = 0;
	}

	if ((key == GLFW_KEY_3 || key == GLFW_KEY_KP_3) && action == GLFW_PRESS) {
		bonus_1 = 1;
		//cout << speed;
	}
	else if (action == GLFW_RELEASE) {
		bonus_1 = 0;
	}

	if ((key == GLFW_KEY_4 || key == GLFW_KEY_KP_4) && action == GLFW_PRESS) {
		bonus_2 = 1;
		cout << bonus_2;
	}
	else if (action == GLFW_RELEASE) {
		bonus_2 = 0;
	}
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
	windowWidth = width;
	windowHeight = height;
}

unsigned int createShader(const char* filename, const char* type)
{
	unsigned int shader;
	if (strcmp(type, "vert") == 0)
		shader = glCreateShader(GL_VERTEX_SHADER);
	else if (strcmp(type, "frag") == 0)
		shader = glCreateShader(GL_FRAGMENT_SHADER);
	else
	{
		cout << "Unknown Shader Type.\n";
		return 0;
	}

	FILE* fp = fopen(filename, "rb");
	fseek(fp, 0, SEEK_END);
	long fsize = ftell(fp);
	fseek(fp, 0, SEEK_SET);  //same as rewind(fp);

	char* source = (char*)malloc(sizeof(char) * (fsize + 1));
	fread(source, fsize, 1, fp);
	fclose(fp);

	source[fsize] = 0;

	glShaderSource(shader, 1, &source, NULL);
	glCompileShader(shader);

	int success;
	char infoLog[512];
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(shader, 512, NULL, infoLog);
		cout << "ERROR::SHADER::" << type << "::COMPLIATION_FAILED\n" << infoLog << endl;
		return -1;
	}

	return shader;
}

unsigned int createProgram(unsigned int vertexShader, unsigned int fragmentShader)
{
	unsigned int program = glCreateProgram();

	//Attach our shaders to our program
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);

	//Link our program
	glLinkProgram(program);

	//Note the different functions here: glGetProgram* instead of glGetShader*.
	int success = 0;
	glGetProgramiv(program, GL_LINK_STATUS, &success);

	if (!success)
	{
		int maxLength = 0;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

		//The maxLength includes the NULL character
		char* infoLog = (char*)malloc(sizeof(char) * (maxLength));
		glGetProgramInfoLog(program, maxLength, &maxLength, infoLog);

		//We don't need the program anymore.
		glDeleteProgram(program);
		//Don't leak shaders either.
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);

		puts(infoLog);
		free(infoLog);

		return -1;
	}

	//Always detach shaders after a successful link.
	glDetachShader(program, vertexShader);
	glDetachShader(program, fragmentShader);

	return program;
}

unsigned int ModelVAO(Object* model) {
	unsigned int VAO, VBO[3];
	glGenVertexArrays(1, &VAO);
	glGenBuffers(3, VBO);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GL_FLOAT) * (model->positions.size()), &(model->positions[0]), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT) * 3, 0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GL_FLOAT) * (model->normals.size()), &(model->normals[0]), GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT) * 3, 0);
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GL_FLOAT) * (model->texcoords.size()), &(model->texcoords[0]), GL_STATIC_DRAW);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(GL_FLOAT) * 2, 0);
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
	return VAO;
}

void DrawModel(const char* target, glm::mat4 M, glm::mat4 V, glm::mat4 P) {
	unsigned int mLoc, vLoc, pLoc, tLoc, dLoc, cLoc;
	if (deformation == 1 && (strcmp(target, "cat") == 0)) {

		glm::mat4 m_s = glm::mat4(1.0f);
		glm::mat4 m_t = glm::mat4(1.0f);
		glm::mat4 m_r = glm::mat4(1.0f);
		glm::mat4 m = glm::mat4(1.0f);
		//glm::vec4 c = glm::vec4(1.0, 1.0, 1.0, 2.0);
		m_s = glm::scale(m_s, glm::vec3(0.5, 0.5, 0.5));
		//m_r = glm::rotate(m_r, glm::radians(720.0f) * (float)glfwGetTime(), glm::vec3(0, 1, 0));
		//m_t = glm::translate(m_t, glm::vec3(0, 1.5, 0) );
		m = m_t * m_r * m_s;
		int c = 0;
		//M = m_s * M;
		mLoc = glGetUniformLocation(shaderProgram, "M");
		vLoc = glGetUniformLocation(shaderProgram, "V");
		pLoc = glGetUniformLocation(shaderProgram, "P");
		tLoc = glGetUniformLocation(shaderProgram, "ourTexture");
		dLoc = glGetUniformLocation(shaderProgram, "deformation");
		cLoc = glGetUniformLocation(shaderProgram, "color");
		glUseProgram(shaderProgram);
		glUniformMatrix4fv(mLoc, 1, GL_FALSE, glm::value_ptr(M));
		glUniformMatrix4fv(vLoc, 1, GL_FALSE, glm::value_ptr(V));
		glUniformMatrix4fv(pLoc, 1, GL_FALSE, glm::value_ptr(P));
		glUniformMatrix4fv(dLoc, 1, GL_FALSE, glm::value_ptr(m));
		//glUniformMatrix4fv(cLoc, 1, GL_FALSE, glm::value_ptr(c));
		glUniform1i(cLoc, c);
	}
	else if (change_color == 1 && (strcmp(target, "cat") == 0)) {
		glm::mat4 m_s = glm::mat4(1.0f);
		m_s = glm::scale(m_s, glm::vec3(1, 1, 1));
		int c = 1
			;
		//glm::vec4 c = glm::vec4(1.0, 2.0, 2.0, 2.0);
		mLoc = glGetUniformLocation(shaderProgram, "M");
		vLoc = glGetUniformLocation(shaderProgram, "V");
		pLoc = glGetUniformLocation(shaderProgram, "P");
		tLoc = glGetUniformLocation(shaderProgram, "ourTexture");
		dLoc = glGetUniformLocation(shaderProgram, "deformation");
		cLoc = glGetUniformLocation(shaderProgram, "color");
		glUseProgram(shaderProgram);
		glUniformMatrix4fv(mLoc, 1, GL_FALSE, glm::value_ptr(M));
		glUniformMatrix4fv(vLoc, 1, GL_FALSE, glm::value_ptr(V));
		glUniformMatrix4fv(pLoc, 1, GL_FALSE, glm::value_ptr(P));
		glUniformMatrix4fv(dLoc, 1, GL_FALSE, glm::value_ptr(m_s));
		//glUniformMatrix4fv(cLoc, 1, GL_FALSE, glm::value_ptr(c));
		glUniform1i(cLoc, c);
	}
	else if (bonus_1 == 1 && (strcmp(target, "cat") == 0)) {
		glm::mat4 m_s = glm::mat4(1.0f);
		glm::mat4 m_t = glm::mat4(1.0f);
		glm::mat4 m_tt = glm::mat4(1.0f);
		glm::mat4 m_r = glm::mat4(1.0f);
		glm::mat4 m = glm::mat4(1.0f);
		//glm::vec4 c = glm::vec4(1.0, 1.0, 1.0, 2.0);
		m_s = glm::scale(m_s, glm::vec3(0.5, 0.5, 0.5));
		//m_r = glm::rotate(m_r, glm::radians(720.0f) * (float)glfwGetTime(), glm::vec3(0, 1, 0));
		m_t = glm::translate(m_t, glm::vec3(0, 1.5, 0));
		m_tt = glm::translate(m_tt, glm::vec3(1.5, 0, 0));
		m = m_t * m_r * m_s;
		int c = 0;
		//M = m_s * M;
		mLoc = glGetUniformLocation(shaderProgram, "M");
		vLoc = glGetUniformLocation(shaderProgram, "V");
		pLoc = glGetUniformLocation(shaderProgram, "P");
		tLoc = glGetUniformLocation(shaderProgram, "ourTexture");
		dLoc = glGetUniformLocation(shaderProgram, "deformation");
		cLoc = glGetUniformLocation(shaderProgram, "color");
		glUseProgram(shaderProgram);
		glUniformMatrix4fv(mLoc, 1, GL_FALSE, glm::value_ptr(M));
		glUniformMatrix4fv(vLoc, 1, GL_FALSE, glm::value_ptr(V));
		glUniformMatrix4fv(pLoc, 1, GL_FALSE, glm::value_ptr(P));
		glUniformMatrix4fv(dLoc, 1, GL_FALSE, glm::value_ptr(m));
		//glUniformMatrix4fv(cLoc, 1, GL_FALSE, glm::value_ptr(c));
		glUniform1i(cLoc, c);
	}
	else if (bonus_2 == 1 && (strcmp(target, "cat") == 0)) {
		glm::mat4 m_s = glm::mat4(1.0f);
		glm::mat4 m_t = glm::mat4(1.0f);
		glm::mat4 m_tt = glm::mat4(1.0f);
		glm::mat4 m_r = glm::mat4(1.0f);
		glm::mat4 m = glm::mat4(1.0f);
		//glm::vec4 c = glm::vec4(1.0, 1.0, 1.0, 2.0);
		m_s = glm::scale(m_s, glm::vec3(1.2, 1.2, 1.5));
		//m_r = glm::rotate(m_r, glm::radians(720.0f) * (float)glfwGetTime(), glm::vec3(0, 1, 0));
		//m_t = glm::translate(m_t, glm::vec3(0, 1.5, 0));
		//m_tt = glm::translate(m_tt, glm::vec3(1.5, 0, 0));
		m = m_t * m_r * m_s;
		int c = 0;
		//M = m_s * M;
		mLoc = glGetUniformLocation(shaderProgram, "M");
		vLoc = glGetUniformLocation(shaderProgram, "V");
		pLoc = glGetUniformLocation(shaderProgram, "P");
		tLoc = glGetUniformLocation(shaderProgram, "ourTexture");
		dLoc = glGetUniformLocation(shaderProgram, "deformation");
		cLoc = glGetUniformLocation(shaderProgram, "color");
		glUseProgram(shaderProgram);
		glUniformMatrix4fv(mLoc, 1, GL_FALSE, glm::value_ptr(M));
		glUniformMatrix4fv(vLoc, 1, GL_FALSE, glm::value_ptr(V));
		glUniformMatrix4fv(pLoc, 1, GL_FALSE, glm::value_ptr(P));
		glUniformMatrix4fv(dLoc, 1, GL_FALSE, glm::value_ptr(m));
		//glUniformMatrix4fv(cLoc, 1, GL_FALSE, glm::value_ptr(c));
		glUniform1i(cLoc, c);
	}
	else {
		glm::mat4 m_s = glm::mat4(1.0f);
		m_s = glm::scale(m_s, glm::vec3(1, 1, 1));
		//glm::vec4 c = glm::vec4(1.0, 1.0, 1.0, 1.0);
		int c = 0;
		//M = m_s * M;
		mLoc = glGetUniformLocation(shaderProgram, "M");
		vLoc = glGetUniformLocation(shaderProgram, "V");
		pLoc = glGetUniformLocation(shaderProgram, "P");
		tLoc = glGetUniformLocation(shaderProgram, "ourTexture");
		dLoc = glGetUniformLocation(shaderProgram, "deformation");
		cLoc = glGetUniformLocation(shaderProgram, "color");
		glUseProgram(shaderProgram);
		glUniformMatrix4fv(mLoc, 1, GL_FALSE, glm::value_ptr(M));
		glUniformMatrix4fv(vLoc, 1, GL_FALSE, glm::value_ptr(V));
		glUniformMatrix4fv(pLoc, 1, GL_FALSE, glm::value_ptr(P));
		glUniformMatrix4fv(dLoc, 1, GL_FALSE, glm::value_ptr(m_s));
		//glUniformMatrix4fv(cLoc, 1, GL_FALSE, glm::value_ptr(c));
		glUniform1i(cLoc, c);
	}
	/*
	mLoc = glGetUniformLocation(shaderProgram, "M");
	vLoc = glGetUniformLocation(shaderProgram, "V");
	pLoc = glGetUniformLocation(shaderProgram, "P");
	tLoc = glGetUniformLocation(shaderProgram, "ourTexture");
	glUseProgram(shaderProgram);
	glUniformMatrix4fv(mLoc, 1, GL_FALSE, glm::value_ptr(M));
	glUniformMatrix4fv(vLoc, 1, GL_FALSE, glm::value_ptr(V));
	glUniformMatrix4fv(pLoc, 1, GL_FALSE, glm::value_ptr(P));
	*/

	if (strcmp(target, "box") == 0 && bonus_2 == 0)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, boxTexture);
		glUniform1i(tLoc, 0);
		glBindVertexArray(boxVAO);
		glDrawArrays(GL_TRIANGLES, 0, boxModel->positions.size());
	}
	else if (strcmp(target, "box") == 0 && bonus_2 == 1)
	{
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, fireTexture);
		glUniform1i(tLoc, 0);
		glBindVertexArray(boxVAO);
		glDrawArrays(GL_TRIANGLES, 0, boxModel->positions.size());
	}
	else if (strcmp(target, "cat") == 0 && bonus_2 == 0)
	{
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, catTexture);
		glUniform1i(tLoc, 1);
		glBindVertexArray(catVAO);
		glDrawArrays(GL_TRIANGLES, 0, catModel->positions.size());
	}
	else if (strcmp(target, "cat") == 0 && bonus_2 == 1)
	{

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, tigerTexture);
		glUniform1i(tLoc, 0);
		glBindVertexArray(catVAO);
		glDrawArrays(GL_TRIANGLES, 0, catModel->positions.size());
	}
	else if (strcmp(target, "ball") == 0)
	{
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, ballTexture);
		glUniform1i(tLoc, 1);
		glBindVertexArray(ballVAO);
		glDrawArrays(GL_TRIANGLES, 0, ballModel->positions.size());
	}
	glBindVertexArray(0);
	glUseProgram(0);

}

void LoadTexture(unsigned int& texture, const char* tFileName) {
	glEnable(GL_TEXTURE_2D);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int width, height, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(tFileName, &width, &height, &nrChannels, 0);

	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	glBindTexture(GL_TEXTURE_2D, 0);
	stbi_image_free(data);
}

glm::mat4 getPerspective()
{
	return glm::perspective(
		glm::radians(45.0f),
		(float)windowWidth / (float)windowHeight, 
		0.1f, 100.0f);
}

glm::mat4 getView()
{
	return glm::lookAt(
		glm::vec3(0, 5, 5),
		glm::vec3(0, 0, 0),
		glm::vec3(0, 1, 0));
}