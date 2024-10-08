float theta = 0.;
float sdSphere( vec3 p, float s )
{
  return length(p) - s;
}
void mainImage( out vec4 fragColor, in vec2 fragCoord )
{
    vec2 uv = fragCoord.xy/iResolution.y*2.-iResolution.xy/iResolution.y;
    float d = sdSphere(vec3(uv.x+0.5,uv.y-0.2,0),0.5);
    float x = d;
    float finalTheta = 1.;
    theta = iTime;
    if(cos(theta)<=uv.x+0.6&&cos(theta)>=uv.x+0.4)finalTheta=10.;
    d= smoothstep(d,.1,.2);
    if(x>0.4)d=0.;
    //if(x<0.)d=fract(1.-abs(d));
    vec3 col = vec3(d*0.6,d*0.5,0.)*finalTheta;
    fragColor = vec4(col,1.0);
}
