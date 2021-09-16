#version 330


uniform sampler2D tex;

out vec4 pixelColor; //Zmienna wyjsciowa fragment shadera. Zapisuje sie do niej ostateczny (prawie) kolor piksela

//Zmienne interpolowane
//in float i_nl;
//in vec2 i_tc;
in vec4 n;
in vec4 v;
in vec4 l1;
in vec4 l2;
in vec4 l3;
in vec4 l4;
in vec2 iTexCoord0;

void main(void) {
    //vec4 color=texture(tex,i_tc);
	//pixelColor=vec4(color.rgb*i_nl,color.a);

	vec4 mn = normalize(n);
	vec4 mv = normalize(v);

	vec4 ml1 = normalize(l1);
	vec4 mr1 = reflect(-ml1,mn);
	float nl1 = pow(clamp(dot(mn, ml1), 0, 1),2);
    float rv1 = pow(clamp(dot(mr1, mv), 0, 1),4);

	vec4 ml2 = normalize(l2);
	vec4 mr2 = reflect(-ml2,mn);
	float nl2 = pow(clamp(dot(mn, ml2), 0, 1),3);
    float rv2 = pow(clamp(dot(mr2, mv), 0, 1),50);

	vec4 ml3 = normalize(l3);
	vec4 mr3 = reflect(-ml3,mn);
	float nl3 = pow(clamp(dot(mn, ml3), 0, 1),3);
    float rv3 = pow(clamp(dot(mr3, mv), 0, 1),50);

	vec4 ml4 = normalize(l4);
	vec4 mr4 = reflect(-ml4,mn);
	float nl4 = pow(clamp(dot(mn, ml4), 0, 1),3);
    float rv4 = pow(clamp(dot(mr4, mv), 0, 1),50);

	vec4 kd = texture(tex, iTexCoord0);
	vec4 ks = texture(tex, iTexCoord0);

	pixelColor = vec4(kd.rgb * nl1, kd.a) + vec4(ks.rgb*rv1, 0);
	pixelColor += vec4(kd.rgb * nl2, kd.a) + vec4(ks.rgb*rv2, 0);
	pixelColor += vec4(kd.rgb * nl3, kd.a) + vec4(ks.rgb*rv3, 0);
	pixelColor += vec4(kd.rgb * nl4, kd.a) + vec4(ks.rgb*rv4, 0);
}
