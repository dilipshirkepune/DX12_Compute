// Compute shader to find the maximum value in a 2D texture
Texture2D<float> inputTexture : register(t0);
RWStructuredBuffer<float> outputMaxValue : register(u0);

[numthreads(8, 8, 1)]
void main(uint3 DTid : SV_DispatchThreadID)
{
    float texel = inputTexture.Load(int3(DTid.xy, 0)).r;
    
    max(outputMaxValue[0], texel);
}