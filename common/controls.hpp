#ifndef CONTROLS_HPP
#define CONTROLS_HPP

void computeMatricesFromInputs();
glm::mat4 getViewMatrix();
glm::mat4 getProjectionMatrix();
glm::mat4 getModelMatrix();
glm::mat4 SetModelMatrix();
glm::mat4 getBackgroundModelMatrix();
bool AnimationRequested();
void DisableAnimation();
void SetModelMatrix(glm::mat4 _ModelMatrix);

#endif