#include "globals.h"

// Globals
ID3D12Device* device = nullptr;
ID3D12DescriptorHeap* cbv_srv_uav_cpu_rd_desc_heap = nullptr;
ID3D12DescriptorHeap* cbv_srv_uav_desc_heap = nullptr;
ComPtr<ID3D12DescriptorHeap> descriptorHeap;

ComPtr <ID3D12CommandQueue> commandQueue = nullptr;
ComPtr<ID3D12CommandAllocator> commandAllocator = nullptr;
ComPtr<ID3D12GraphicsCommandList> commandList = nullptr;

ID3D12Fence* fence = nullptr;
HANDLE fenceEvent = nullptr;
UINT64 fenceValue = 0;
ID3D12PipelineState* computePSO = nullptr;
ComPtr<ID3D12RootSignature> rootSignature;

D3D12_GPU_DESCRIPTOR_HANDLE inputTextureDescriptor = {};
ComPtr<ID3D12Resource> uploadHeap;