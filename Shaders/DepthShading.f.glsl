#version 330 

out vec4 FragmentColor;
void main() {
	FragmentColor = vec4(1.0f-gl_FragCoord.zzz+0.5f,1.0f);
}

