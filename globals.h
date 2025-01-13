#pragma once
#include <wrl.h>
#include <d3d12.h>
#include <dxgi1_4.h>
#include <vector>
#include <iostream>

using namespace Microsoft::WRL;

// Globals
extern ID3D12Device* device;
extern ID3D12DescriptorHeap* cbv_srv_uav_cpu_rd_desc_heap;
extern ID3D12DescriptorHeap* cbv_srv_uav_desc_heap;
extern ComPtr<ID3D12DescriptorHeap> descriptorHeap;

extern ComPtr <ID3D12CommandQueue> commandQueue;
extern ComPtr<ID3D12CommandAllocator> commandAllocator;
extern ComPtr<ID3D12GraphicsCommandList> commandList;

extern ID3D12Fence* fence;
extern HANDLE fenceEvent;
extern UINT64 fenceValue;
extern ID3D12PipelineState* computePSO;
extern ComPtr<ID3D12RootSignature> rootSignature;

extern D3D12_GPU_DESCRIPTOR_HANDLE inputTextureDescriptor;

extern ComPtr<ID3D12Resource> uploadHeap;