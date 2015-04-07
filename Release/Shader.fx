uniform extern float4x4 gWorld;
uniform extern float4x4 gWorldInverseTranspose;
uniform extern float4x4 gWVP;

uniform extern float4 gAmbientLight;
uniform extern float4 gDiffuseMtrl;
uniform extern float4 gDiffuseLight;
uniform extern float4 gSpecularMtrl;
uniform extern float4 gSpecularLight;
uniform extern float  gSpecularPower;
uniform extern float3 gLightVecW;
uniform extern float3 gEyePosW;

struct OutputVS
{
    float4 posH    : POSITION0;
    float3 normalW : TEXCOORD0;
	float3 posW    : TEXCOORD1;
	float4 color   : COLOR0;
};


OutputVS ShaderVS(float3 posL : POSITION0, float3 normalL : NORMAL0, float4 color: COLOR0)
{
	OutputVS outVS = (OutputVS)0;
	
	// Transform normal to world space.
	outVS.normalW = mul(float4(normalL, 0.0f), gWorldInverseTranspose).xyz;
	outVS.normalW = normalize(outVS.normalW);
	
	// Transform vertex position to world space.
	outVS.posW  = mul(float4(posL, 1.0f), gWorld).xyz;
	
	// Transform to homogeneous clip space.
	outVS.posH = mul(float4(posL, 1.0f), gWVP);
	
	outVS.color = color;

	// Done--return the output.
    return outVS;
}

float4 ShaderPS(float3 normalW : TEXCOORD0,
					  float3 posW : TEXCOORD1, 
						float4 color : COLOR0) : COLOR
{
	normalW = normalize(normalW);

	// Compute the vector from the vertex to the eye position.
	float3 toEye = normalize(gEyePosW - posW);
	
	// Compute the reflection vector.
	float3 r = reflect(-gLightVecW, normalW);
	
	// Determine how much (if any) specular light makes it into the eye.
	float t  = pow(max(dot(r, toEye), 0.0f), gSpecularPower);
	
	// Determine the diffuse light intensity that strikes the vertex.
	float s = max(dot(gLightVecW, normalW), 0.0f);
	
	// Compute the ambient, diffuse and specular terms separatly. 
	float3 spec = t*(gSpecularMtrl*gSpecularLight).rgb;
	float3 diffuse = s*(color*(gDiffuseLight*0.5f)).rgb;// here
	float3 ambient = color*gAmbientLight;//here
	
	// Sum all the terms together and copy over the diffuse alpha.
	return float4(ambient + diffuse + spec, color.a);
}

technique ShaderTech
{
    pass P0
    {
        // Specify the vertex and pixel shader associated with this pass.
        vertexShader = compile vs_2_0 ShaderVS();
		pixelShader = compile ps_2_0 ShaderPS();
		//FillMode = WireFrame;
    }
}