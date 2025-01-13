#pragma once
#include <wrl.h>
#include <d3d12.h>
#include <dxgi1_4.h>
#include <vector>
#include <random>

using namespace Microsoft::WRL;

void TransWStrToString(char dstBuf[], const WCHAR srcBuf[]);
ComPtr<ID3D12RootSignature> CreateRootSignature(ID3D12Device* device);
ComPtr<ID3D12Resource> CreateTestTexture(ID3D12Device* device, ID3D12GraphicsCommandList* commandList, ID3D12CommandQueue* commandQueue, UINT width, UINT height);
void FindMaxValueInTexture(ID3D12Device* device, ID3D12CommandQueue* commandQueue, ID3D12Resource* texture);
std::vector<float> generate_random_floats(int num_values, float min_value, float max_value);