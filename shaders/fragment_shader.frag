#version 330 core

in vec3 ourColor; // Couleur du fragment
out vec4 FragColor; // Couleur du fragment

void main() {
    
    FragColor = vec4(ourColor, 1.0); // Définir la couleur finale du fragment
}