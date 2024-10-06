float sdBox( in vec2 p, in vec2 b )
{
    vec2 d = abs(p)-b;
    return length(max(d,0.0)) + min(max(d.x,d.y),0.0);
}
vec3 palette( in float t)
{
    vec3 a = vec3(0.137,0.471,0.772);
    vec3 b = vec3(0.337, 0.827, 0.899);
    vec3 c = vec3(1.537 ,0.761, 1.460);
    vec3 d = vec3(1.716, 0.641, 1.350);
    return a + b*cos( 6.283185*(c*t+d) );
}
void mainImage( out vec4 fragColor, in vec2 fragCoord )
{
    vec2 uv = (fragCoord.xy*2./iResolution.y-iResolution.xy/iResolution.y);
    vec2 uv0 = uv;
    vec3 finalcol = vec3(0);
    uv = fract(uv);
    uv=uv*2.;
    uv=uv-1.;
    for(int i=0; i<4; i++)
    {
        float d = sdBox(uv,vec2(0.5,0.5))*exp(-length(uv0));
        vec3 col = vec3(palette(length(uv0)+iTime +float(i)*0.02));
        d=sin(d*10.+iTime*0.5)/10.;
        d=abs(d);
        d=pow(0.01/d,1.1);
        col *=d;
        finalcol += col;
    }
    fragColor = vec4(finalcol,1.0);
}
