//#version 120

varying vec3 frag_Color;

void main()
{
    
    // Output color = red
    // gl_FragColor = vec4(1,0,0,1);
    
    gl_FragColor = vec4(frag_Color, 1);
    
}

