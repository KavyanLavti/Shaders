float sdBox(in vec2 p, in vec2 b)
{
	vec2 d = abs(p) - b;
    return length(max(d, vec2(0))) + min(max(d.x, d.y), 0.0);
}

void mainImage( out vec4 fragColor, in vec2 fragCoord )
{
    vec2 uv = fragCoord/iResolution.xy*2.-1.;
    float angle = iTime*0.01;
    vec3 col = vec3(1);
    for(int i=0; i<60; i++)
    {
        uv = abs(uv);
        uv = uv-0.5;
        uv = uv*mat2(cos(angle),-sin(angle),sin(angle),cos(angle));
        float d = sdBox(uv,vec2(sin(iTime*0.01)))+length(uv);
        col += vec3(d+sin(iTime*0.01+vec3(0,2,4)));
        col = fract(col);
    }
    fragColor = vec4(col,1.0);
}
