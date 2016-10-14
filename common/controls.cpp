// Include GLFW
#include <glfw3.h>
extern GLFWwindow* window; // The "extern" keyword here is to access the variable "window" declared in tutorialXXX.cpp. This is a hack to keep the tutorials simple. Please avoid this.

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#include "controls.hpp"
glm::mat4 ViewMatrix;
glm::mat4 ProjectionMatrix;
glm::mat4 ModelMatrix;

glm::mat4 BackgroundModelMatrix;



bool animation = false;

glm::mat4 getViewMatrix(){
	return ViewMatrix;
}
glm::mat4 getProjectionMatrix(){
	return ProjectionMatrix;
}
glm::mat4 getModelMatrix(){
    return ModelMatrix;
}
glm::mat4 getBackgroundModelMatrix(){
    
    BackgroundModelMatrix[3].z = (double) -15;
    BackgroundModelMatrix[0].x = (double) 15*(1.25);
    BackgroundModelMatrix[1].y = (double) 15;
    BackgroundModelMatrix[2].z = (double) 1;
    
    
    return BackgroundModelMatrix;
}


bool AnimationRequested(){
    
    if(animation){
        animation = false;
        return true;
    }
    return false;
}

void DisableAnimation(){
    animation = false;
}

void SetModelMatrix(mat4 _ModelMatrix){
    ModelMatrix = _ModelMatrix;
}


// Initial position : on +Z
glm::vec3 position = glm::vec3( 0, 0, 5 );

//Initial model position
glm::vec3 modelposition = glm::vec3(0,0,0);

//Arrows vectors
glm::vec3 vright = glm::vec3(1,0,0);
glm::vec3 vup = glm::vec3(0,1,0);
float vscale = 1;

//Diferential Quantities
glm::vec3 Dmodelposition = glm::vec3(0,0,0);
float Dvscale = 0;



// Initial horizontal angle : toward -Z
float horizontalAngle = 3.14f;
// Initial vertical angle : none
float verticalAngle = 0.0f;
// Initial Field of View
float initialFoV = 45.0f;

float speed = 3.0f; // 3 units / second
float mouseSpeed = 0.005f;






void computeMatricesFromInputs(){

	// glfwGetTime is called only once, the first time this function is called
	static double lastTime = glfwGetTime();

	// Compute time difference between current and last frame
	double currentTime = glfwGetTime();
	float deltaTime = float(currentTime - lastTime);

	// Get mouse position
	double xpos, ypos;
	glfwGetCursorPos(window, &xpos, &ypos);

	// Reset mouse position for next frame
	glfwSetCursorPos(window, 1024/2, 768/2);

	// Compute new orientation
	horizontalAngle += mouseSpeed * float(1024/2 - xpos );
	verticalAngle   += mouseSpeed * float( 768/2 - ypos );

	// Direction : Spherical coordinates to Cartesian coordinates conversion
	glm::vec3 direction(
		cos(verticalAngle) * sin(horizontalAngle), 
		sin(verticalAngle),
		cos(verticalAngle) * cos(horizontalAngle)
	);
	
	// Right vector
	glm::vec3 right = glm::vec3(
		sin(horizontalAngle - 3.14f/2.0f), 
		0,
		cos(horizontalAngle - 3.14f/2.0f)
	);
	
	// Up vector
	glm::vec3 up = glm::cross( right, direction );

	// Move forward
	if (glfwGetKey( window, GLFW_KEY_UP ) == GLFW_PRESS){
		Dmodelposition = vup * deltaTime * speed;
	}
	// Move backward
	if (glfwGetKey( window, GLFW_KEY_DOWN ) == GLFW_PRESS){
		Dmodelposition = - vup * deltaTime * speed;
	}
	// Strafe right
	if (glfwGetKey( window, GLFW_KEY_RIGHT ) == GLFW_PRESS){
        Dmodelposition = vright * deltaTime * speed;
	}
	// Strafe left
	if (glfwGetKey( window, GLFW_KEY_LEFT ) == GLFW_PRESS){
		Dmodelposition = - vright * deltaTime * speed;
	}
    // Scale Up
    if (glfwGetKey( window, GLFW_KEY_Q )== GLFW_PRESS){
        Dvscale =  - 1 * deltaTime * speed;
    }
    // Scale down
    if (glfwGetKey( window, GLFW_KEY_A ) == GLFW_PRESS){
        Dvscale = 1 * deltaTime * speed;
    }
    // Disposal Animation
    if (glfwGetKey( window, GLFW_KEY_D ) == GLFW_PRESS){
        animation = true;
    }

    
    
    
    float FoV = initialFoV;// - 5 * glfwGetMouseWheel(); // Now GLFW 3 requires setting up a callback for this. It's a bit too complicated for this beginner's tutorial, so it's disabled instead.

	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	ProjectionMatrix = glm::perspective(FoV, 4.0f / 3.0f, 0.1f, 100.0f);
	// Camera matrix
	ViewMatrix       = glm::lookAt(
								position,           // Camera is here
								position+direction, // and looks here : at the same position, plus "direction"
								up                  // Head is up (set to 0,-1,0 to look upside-down)
						   );
    
    
    ///////////// On my Own Modification /////////////////////
    
    ModelMatrix[3].x += Dmodelposition.x;
    ModelMatrix[3].y += Dmodelposition.y;
    ModelMatrix[3].z += Dmodelposition.z;
    
    ModelMatrix[0].x += Dvscale;
    ModelMatrix[1].y += Dvscale;
    ModelMatrix[2].z += Dvscale;
    
    Dvscale = 0;
    Dmodelposition = vec3(0,0,0);

    
	// For the next frame, the "last time" will be "now"
	lastTime = currentTime;
}