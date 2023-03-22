// Include GLFW
#include <GLFW/glfw3.h>
extern GLFWwindow* window; // The "extern" keyword here is to access the variable "window" declared in tutorialXXX.cpp. This is a hack to keep the tutorials simple. Please avoid this.

// Include GLM
#include <glm/glm.hpp>
#include <windows.h>
#include <math.h>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;
#include "controls.hpp"


glm::mat4 ViewMatrix;
glm::mat4 ProjectionMatrix;
glm::mat4 ModelMatrix = glm::mat4(1.0);
glm::mat4 ModelMatrix2 = glm::mat4(1.0);
glm::mat4 ModelMatrix3 = glm::mat4(1.0);
glm::mat4 getModelMatrix() {
	return ModelMatrix;
}
glm::mat4 getModelMatrix2() {
	return ModelMatrix2;
}
glm::mat4 getModelMatrix3() {
	return ModelMatrix3;
}
glm::mat4 getViewMatrix() {
	return ViewMatrix;
}
glm::mat4 getProjectionMatrix() {
	return ProjectionMatrix;
}
bool CheckKeyState1() {
	if ((GetKeyState(VK_CAPITAL) & 0X0001) == 0) {
		return true;
	}

	return false;
}
int caps_state = 0;


// Initial position : on +Z
glm::vec3 position = glm::vec3(10.0f, 10.0f, 80.0f);
glm::vec3 target = glm::vec3(0, 0, 0);
glm::vec3 upVector = glm::vec3(0, 1, 0);
glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 0.0f, 1.0f));
// Initial horizontal angle : toward -Z
float horizontalAngle = 3.0;
// Initial vertical angle : none
float verticalAngle = 0.0f;
// Initial Field of View
float initialFoV = 45.0f;
int collision = 0;
int MeteorMovement = 0;
int able_to_press_space = 1;
float Meteor_x = position[0];
float Meteor_y = position[1];
float Meteor_z = position[2];
float Planet_x = 0.0;
float Planet_y = 0.0;
float Planet_z = 0.0;
float speedOfX = 0.1;
float ratioX2Y = position[1] / position[0];
float ratioX2Z = position[2] / position[0];
float distance_of_planets = 0.0;
float angle = 0.0;



bool checkForCollision(float M_x,float M_y, float M_z) {
	
	Planet_x = 25*ModelMatrix2[0][0];
	Planet_y = 0.0;
	Planet_z = -25*ModelMatrix2[2][0];
	
    //printf("Planet x = %f ", Planet_x);
	//printf("Planet y = %f ", Planet_y);
	//printf("Planet z = %f ", Planet_z);
	//printf("\n");
	distance_of_planets = pow((pow((Planet_x - M_x),2) + (pow((Planet_y - M_y), 2)) + pow((Planet_z - M_z), 2)),0.5);
	if (distance_of_planets <= 7){
		collision = 1;

	}
	
	return true;
	
}

float speed = 3.0f; // 3 units / second


void computeMatricesFromInputs() {

	if (CheckKeyState1() == true) {
		caps_state = 1;
	}
	else if (CheckKeyState1() == false) {
		caps_state = 0;
	}
	static double lastTime = glfwGetTime();

	double currentTime = glfwGetTime();
	float deltaTime = float(currentTime - lastTime);

	// Direction : Spherical coordinates to Cartesian coordinates conversion
	glm::vec3 direction = glm::normalize(position - target);
	// Right vector
	glm::vec3 right = glm::normalize(glm::cross(upVector, direction));
	// Up vector
	glm::vec3 up = glm::cross(direction, right);



	if (glfwGetKey(window, GLFW_KEY_EQUAL) == GLFW_PRESS) {
		

		if (position[0] >= 0) {
			position[0] -= 0.1 * abs(position[0]) * deltaTime;
		}
		else {
			position[0] += 0.1 * abs(position[0]) * deltaTime;
		}

		if (position[1] >= 0) {
			position[1] -= 0.1 * abs(position[1]) * deltaTime;
		}
		else {
			position[1] += 0.1 * abs(position[1]) * deltaTime;
		}

		if (position[2] >= 0) {
			position[2] -= 0.1 * abs(position[2]) * deltaTime;
		}
		else {
			position[2] += 0.1 * abs(position[2]) * deltaTime;
		}
	}
	if (glfwGetKey(window, GLFW_KEY_MINUS) == GLFW_PRESS) {
		
		if (position[0] <= 0) {
			position[0] -= 0.1 * abs(position[0]) * deltaTime;
		}
		else {
			position[0] += 0.1 * abs(position[0]) * deltaTime;
		}
		if (position[1] <= 0) {
			position[1] -= 0.1 * abs(position[1]) * deltaTime;
		}
		else {
			position[1] += 0.1 * abs(position[1]) * deltaTime;
		}
		if (position[2] <= 0) {
			position[2] -= 0.1 * abs(position[2]) * deltaTime;
		}
		else {
			position[2] += 0.1 * abs(position[2]) * deltaTime;
		}

	}

	if ((glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) && (caps_state == 1)) {
		glm::mat4 rotationMatrix = glm::rotate(ModelMatrix, 0.0005f, glm::vec3(0, 0, 1));
		glm::vec4 myVec = glm::vec4(position[0], position[1], position[2], 0.1f);
		glm::vec4 myNewVec = rotationMatrix * myVec;
		for (int i = 0; i <= 2; i++) {
			position[i] = myNewVec[i];
		}
	}
	if ((glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) && (caps_state == 1)) {
		glm::mat4 rotationMatrix = glm::rotate(ModelMatrix, 0.0005f, glm::vec3(0, 0, -1));
		glm::vec4 myVec = glm::vec4(position[0], position[1], position[2], 0.1f);
		glm::vec4 myNewVec = rotationMatrix * myVec;
		for (int i = 0; i <= 2; i++) {
			position[i] = myNewVec[i];
		}

	}
	if ((glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS) && (caps_state == 1)) {
		glm::mat4 rotationMatrix = glm::rotate(ModelMatrix, 0.0005f, glm::vec3(1, 0, 0));
		glm::vec4 myVec = glm::vec4(position[0], position[1], position[2], 0.1f);
		glm::vec4 myNewVec = rotationMatrix * myVec;
		for (int i = 0; i <= 2; i++) {
			position[i] = myNewVec[i];
		}

	}
	if ((glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) && (caps_state == 1)) {
		glm::mat4 rotationMatrix = glm::rotate(ModelMatrix, 0.0005f, glm::vec3(-1, 0, 0));
		glm::vec4 myVec = glm::vec4(position[0], position[1], position[2], 0.1f);
		glm::vec4 myNewVec = rotationMatrix * myVec;
		for (int i = 0; i <= 2; i++) {
			position[i] = myNewVec[i];
		}

	}
	
	if (collision == 0){
		ModelMatrix2 = glm::rotate(ModelMatrix2, 0.0005f, glm::vec3(0, 1, 0));
	
	}

	if (collision == 1) {
		ModelMatrix2 = glm::translate(ModelMatrix2, glm::vec3(0.1, 0.1, 0));
		ModelMatrix3 = glm::translate(ModelMatrix3, glm::vec3(-0.1,0,-0.1));

	}
	if ((glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) && able_to_press_space == 1) {
		able_to_press_space = 0;
		MeteorMovement = 1;
		ModelMatrix3 = glm::translate(ModelMatrix3, glm::vec3(position[0],position[1], position[2]));
		 Meteor_x = position[0];
		 Meteor_y = position[1];
		 Meteor_z = position[2];
		 printf("x=%f", Meteor_x);
		 printf("y=%f", Meteor_y);
		 printf("z=%f", Meteor_z);
		 speedOfX = 0.0005;
		 ratioX2Y = position[1] / position[0];
		 ratioX2Z = position[2] / position[0];
		
			
		
	}
	if (MeteorMovement == 1 && collision == 0) {
		checkForCollision(Meteor_x, Meteor_y, Meteor_z);
		if (Meteor_x < 0 && Meteor_y < 0 && Meteor_z < 0) {
			
			ModelMatrix3 = glm::translate(ModelMatrix3, glm::vec3(speedOfX, speedOfX * ratioX2Y, speedOfX * ratioX2Z));
		}
		else if (Meteor_x < 0 && Meteor_y > 0 && Meteor_z < 0) {
			ModelMatrix3 = glm::translate(ModelMatrix3, glm::vec3(speedOfX, speedOfX * ratioX2Y, speedOfX * ratioX2Z));
		}
		else if (Meteor_x < 0 && Meteor_y < 0 && Meteor_z > 0) {
			ModelMatrix3 = glm::translate(ModelMatrix3, glm::vec3(speedOfX, speedOfX * ratioX2Y, speedOfX * ratioX2Z));
		}
		else if (Meteor_x < 0 && Meteor_y > 0 && Meteor_z > 0) {
			ModelMatrix3 = glm::translate(ModelMatrix3, glm::vec3(speedOfX, speedOfX * ratioX2Y, speedOfX * ratioX2Z));
		}
		else {
			ModelMatrix3 = glm::translate(ModelMatrix3, glm::vec3(-speedOfX, -speedOfX * ratioX2Y, -speedOfX * ratioX2Z));
		}

		if (Meteor_x > 0) {
			Meteor_x -= speedOfX;}
		else {
			Meteor_x += speedOfX;}

		if (Meteor_x > 0) {
			Meteor_y -= speedOfX * ratioX2Y;}
		else {
			Meteor_y += speedOfX * ratioX2Y;}

		if (Meteor_x > 0) {
			Meteor_z -= speedOfX * ratioX2Z;}
		else {
			Meteor_z += speedOfX * ratioX2Z;}

		if (Meteor_x >= -1 && Meteor_x <= 1 && Meteor_y >= -1 && Meteor_y <= 1 && Meteor_z >= -1 && Meteor_z <= 1) {
			ModelMatrix3 = glm::translate(ModelMatrix3, glm::vec3(-Meteor_x,-Meteor_y,-Meteor_z));
			MeteorMovement = 0;
			able_to_press_space = 1;
		}
		

	}
	




	float FoV = initialFoV;// - 5 * glfwGetMouseWheel(); // Now GLFW 3 requires setting up a callback for this. It's a bit too complicated for this beginner's tutorial, so it's disabled instead.

	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	ProjectionMatrix = glm::perspective(glm::radians(FoV), 1.0f / 1.0f, 0.1f, 500.0f);

	ViewMatrix = glm::lookAt(
		position,           // Camera is here
		target, // and looks here : at the same position, plus "direction"
		upVector  // Head is up (set to 0,-1,0 to look upside-down)
	);


	lastTime = currentTime;
}