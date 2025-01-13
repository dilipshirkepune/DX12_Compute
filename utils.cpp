#include "globals.h"
#include "utils.h"
#include <iostream>
#include "d3dx12.h"
#include <d3dcompiler.h>

void TransWStrToString(char dstBuf[], const WCHAR srcBuf[])
{
    if (dstBuf == NULL || srcBuf == NULL) return;

    const int len = WideCharToMultiByte(CP_UTF8, 0, srcBuf, -1, NULL, 0, NULL, NULL);
    WideCharToMultiByte(CP_UTF8, 0, srcBuf, -1, dstBuf, len, NULL, NULL);
    dstBuf[len] = '\0';
}

ComPtr<ID3D12RootSignature> CreateRootSignature(ID3D12Device* device)
{
    // Define the descriptor range (SRV and UAV)
    D3D12_DESCRIPTOR_RANGE1 ranges[2] = {};
    ranges[0].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
    ranges[0].NumDescriptors = 1;
    ranges[0].BaseShaderRegister = 0;
    ranges[0].RegisterSpace = 0;
    ranges[0].Flags = D3D12_DESCRIPTOR_RANGE_FLAG_NONE;
    ranges[0].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

    ranges[1].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_UAV;
    ranges[1].NumDescriptors = 1;
    ranges[1].BaseShaderRegister = 0;
    ranges[1].RegisterSpace = 0;
    ranges[1].Flags = D3D12_DESCRIPTOR_RANGE_FLAG_NONE;
    ranges[1].OffsetInDescriptorsFromTableStart = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND;

    // Define the root parameters
    D3D12_ROOT_PARAMETER1 rootParameters[1] = {};
    rootParameters[0].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
    rootParameters[0].DescriptorTable.NumDescriptorRanges = _countof(ranges);
    rootParameters[0].DescriptorTable.pDescriptorRanges = &ranges[0];
    rootParameters[0].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;

    /*rootParameters[1].ParameterType = D3D12_ROOT_PARAMETER_TYPE_DESCRIPTOR_TABLE;
    rootParameters[1].DescriptorTable.NumDescriptorRanges = 1;
    rootParameters[1].DescriptorTable.pDescriptorRanges = &ranges[1];
    rootParameters[1].ShaderVisibility = D3D12_SHADER_VISIBILITY_ALL;*/

    // Define the root signature
    D3D12_VERSIONED_ROOT_SIGNATURE_DESC rootSignatureDesc = {};    
    rootSignatureDesc.Version = D3D_ROOT_SIGNATURE_VERSION_1_1;
    rootSignatureDesc.Desc_1_1.NumParameters = _countof(rootParameters);
    rootSignatureDesc.Desc_1_1.pParameters = rootParameters;
    rootSignatureDesc.Desc_1_1.NumStaticSamplers = 0;
    rootSignatureDesc.Desc_1_1.pStaticSamplers = nullptr;    
    rootSignatureDesc.Desc_1_1.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;

    // Create the root signature
    ComPtr<ID3D12RootSignature> rootSignature;
    ComPtr<ID3DBlob> signature;
    ComPtr<ID3DBlob> error;
    HRESULT hr = D3D12SerializeVersionedRootSignature(&rootSignatureDesc, &signature, &error);
    if (FAILED(hr)) {
        std::cout << "Error: Failed to serialize root signature!" << std::endl;
        return nullptr;
    }

    hr = device->CreateRootSignature(0, signature->GetBufferPointer(), signature->GetBufferSize(), IID_PPV_ARGS(&rootSignature));
    if (FAILED(hr)) {
        std::cout << "Error: Failed to create root signature!" << std::endl;
        return nullptr;
    }

    return rootSignature;
}

ComPtr<ID3D12Resource> CreateTestTexture(ID3D12Device* device, ID3D12GraphicsCommandList* commandList, ID3D12CommandQueue* commandQueue, UINT width, UINT height)
{
    // Create a texture resource
    D3D12_RESOURCE_DESC textureDesc = {};
    textureDesc.Dimension = D3D12_RESOURCE_DIMENSION_TEXTURE2D;
    textureDesc.Width = width;
    textureDesc.Height = height;
    textureDesc.DepthOrArraySize = 1;
    textureDesc.MipLevels = 1;
    textureDesc.Format = DXGI_FORMAT_R8_UNORM;
    textureDesc.SampleDesc.Count = 1;
    textureDesc.Layout = D3D12_TEXTURE_LAYOUT_UNKNOWN;
    textureDesc.Flags = D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS;    

    D3D12_HEAP_PROPERTIES heapProperties = {};
    heapProperties.Type = D3D12_HEAP_TYPE_DEFAULT;
    heapProperties.CreationNodeMask = 1;
    heapProperties.VisibleNodeMask = 1;
    heapProperties.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
    heapProperties.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;


    ComPtr<ID3D12Resource> texture;
    

    HRESULT hr = device->CreateCommittedResource(
        &heapProperties,
        D3D12_HEAP_FLAG_NONE,
        &textureDesc,
        D3D12_RESOURCE_STATE_COPY_DEST,
        nullptr,
        IID_PPV_ARGS(&texture));
    if (FAILED(hr)) {
        std::cout << "Error: Failed to create texture resource!" << std::endl;
        return nullptr;
    }

    texture->SetName(L"texture2D");

    // Upload data to the texture     
    const UINT64 uploadBufferSize = GetRequiredIntermediateSize(texture.Get(), 0, 1);

    heapProperties = {};
    heapProperties.Type = D3D12_HEAP_TYPE_UPLOAD;
    heapProperties.CreationNodeMask = 1;
    heapProperties.VisibleNodeMask = 1;
    heapProperties.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
    heapProperties.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;

    D3D12_RESOURCE_DESC bufferDesc = {};
    bufferDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
    bufferDesc.Width = uploadBufferSize;
    bufferDesc.Alignment = 0;
    bufferDesc.Height = 1;
    bufferDesc.DepthOrArraySize = 1;
    bufferDesc.MipLevels = 1;
    bufferDesc.Format = DXGI_FORMAT_UNKNOWN;
    bufferDesc.SampleDesc.Count = 1;
    bufferDesc.SampleDesc.Quality = 0;
    bufferDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
    bufferDesc.Flags = D3D12_RESOURCE_FLAG_NONE;

    hr = device->CreateCommittedResource(
        &heapProperties,
        D3D12_HEAP_FLAG_NONE,
        &bufferDesc,
        D3D12_RESOURCE_STATE_GENERIC_READ,
        nullptr,
        IID_PPV_ARGS(&uploadHeap));
    if (FAILED(hr)) {
        std::cout << "Error: Failed to create upload heap!" << std::endl;
        return nullptr;
    }
    
    uploadHeap->SetName(L"uploadHeap");
    // Create a test texture with specific values
    //std::vector<uint8_t> texelValues = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
    std::vector<float> texelValues = generate_random_floats(256, 0.0, 255.0);

    D3D12_SUBRESOURCE_DATA textureData = {};
    textureData.pData = texelValues.data();
    textureData.RowPitch = width;
    textureData.SlicePitch = textureData.RowPitch * height;

    UpdateSubresources(commandList, texture.Get(), uploadHeap.Get(), 0, 0, 1, &textureData);

    D3D12_RESOURCE_BARRIER barrier0 = {};
    barrier0.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
    barrier0.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
    barrier0.Transition.pResource = texture.Get();
    barrier0.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
    barrier0.Transition.StateBefore = D3D12_RESOURCE_STATE_COPY_DEST;
    barrier0.Transition.StateAfter = D3D12_RESOURCE_STATE_UNORDERED_ACCESS;
    commandList->ResourceBarrier(1, &barrier0);

    //commandList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(texture.Get(), D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_UNORDERED_ACCESS));

    return texture;
}



std::vector<float> generate_random_floats(int num_values, float min_value, float max_value) 
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dist(min_value, max_value);

    std::vector<float> random_values;
    for (int i = 0; i < num_values; ++i) {
        random_values.push_back(dist(gen));
    }

    return random_values;
}

void FindMaxValueInTexture(ID3D12Device* device, ID3D12CommandQueue* commandQueue, ID3D12Resource* texture)
{
    // Set up the compute shader
    // Compile the compute shader    
    ID3DBlob* computeShader;
    ID3DBlob* errorBlob;

#if defined(_DEBUG)
    // Enable better shader debugging with the graphics debugging tools.
    UINT compileFlags = D3DCOMPILE_DEBUG | D3DCOMPILE_SKIP_OPTIMIZATION;
#else
    UINT compileFlags = 0;
#endif

    D3DCompileFromFile(L"ComputeShader.hlsl", nullptr, nullptr, "main", "cs_5_0", compileFlags, 0, &computeShader, &errorBlob);
    if (errorBlob)
    {
        OutputDebugStringA((char*)errorBlob->GetBufferPointer());
        errorBlob->Release();
        //return;
    }

    // Create the root signature
    rootSignature = CreateRootSignature(device);
    if (!rootSignature) 
    {
        std::cout << "Error: Failed to create root signature!" << std::endl;
        return;
    }

    // Assume the compute shader is already compiled and loaded into a blob
    ComPtr<ID3D12PipelineState> computePSO;
    D3D12_COMPUTE_PIPELINE_STATE_DESC psoDesc = {};
    psoDesc.pRootSignature = rootSignature.Get();
    psoDesc.CS = { reinterpret_cast<BYTE*>(computeShader->GetBufferPointer()), computeShader->GetBufferSize() };
    HRESULT hr = device->CreateComputePipelineState(&psoDesc, IID_PPV_ARGS(&computePSO));
    if (FAILED(hr)) 
    {
        std::cout << "Error: Failed to create CreateComputePipelineState!" << std::endl;
        return;
    }
     
    

    
   // Create a descriptor heap for CBV/SRV/UAV
    D3D12_DESCRIPTOR_HEAP_DESC heapDesc = {};
    heapDesc.NumDescriptors = 2;
    heapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV;
    heapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE;
    ComPtr<ID3D12DescriptorHeap> descriptorHeap;
    hr = device->CreateDescriptorHeap(&heapDesc, IID_PPV_ARGS(&descriptorHeap));
    if (FAILED(hr)) 
    {
        std::cout << "Error: Failed to create descriptor heap!" << std::endl;
        return;
    }
       
    // Create a UAV for the texture
    D3D12_UNORDERED_ACCESS_VIEW_DESC uavDesc = {};
    uavDesc.ViewDimension = D3D12_UAV_DIMENSION_TEXTURE2D;
    uavDesc.Format = DXGI_FORMAT_R8_UNORM;
    uavDesc.Texture2D.MipSlice = 0;
    uavDesc.Texture2D.PlaneSlice = 0;

    device->CreateUnorderedAccessView(texture, nullptr, &uavDesc, descriptorHeap->GetCPUDescriptorHandleForHeapStart());

    // Create an output buffer for maximum texel value
    D3D12_RESOURCE_DESC bufferDesc = {};
    bufferDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
    bufferDesc.Width = sizeof(float);
    bufferDesc.Height = 1;
    bufferDesc.DepthOrArraySize = 1;
    bufferDesc.MipLevels = 1;
    bufferDesc.Format = DXGI_FORMAT_UNKNOWN;
    bufferDesc.SampleDesc.Count = 1;
    bufferDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
    bufferDesc.Flags = D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS;

    ComPtr<ID3D12Resource> outputBuffer;
    
    D3D12_HEAP_PROPERTIES heapProperties = {};
    heapProperties.Type = D3D12_HEAP_TYPE_DEFAULT;
    heapProperties.CreationNodeMask = 1;
    heapProperties.VisibleNodeMask = 1;
    heapProperties.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
    heapProperties.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
    
    hr = device->CreateCommittedResource(
        &heapProperties,
        D3D12_HEAP_FLAG_NONE,
        &bufferDesc,
        D3D12_RESOURCE_STATE_UNORDERED_ACCESS,
        nullptr,
        IID_PPV_ARGS(&outputBuffer));
    if (FAILED(hr)) 
    {
        std::cout << "Error: Failed to create output buffer!" << std::endl;
        return;
    }
    outputBuffer->SetName(L"outputBuffer");

    // Create a UAV for output buffer    
    D3D12_UNORDERED_ACCESS_VIEW_DESC outputUAVDesc = {};
    outputUAVDesc.ViewDimension = D3D12_UAV_DIMENSION_BUFFER;
    outputUAVDesc.Format = DXGI_FORMAT_R32_FLOAT;
    outputUAVDesc.Texture2D.MipSlice = 0;
    outputUAVDesc.Texture2D.PlaneSlice = 0;
    outputUAVDesc.Buffer.FirstElement = 0;
    outputUAVDesc.Buffer.NumElements = 1;
    outputUAVDesc.Buffer.StructureByteStride = 0;
    outputUAVDesc.Buffer.CounterOffsetInBytes = 0;
    outputUAVDesc.Buffer.Flags = D3D12_BUFFER_UAV_FLAG_NONE;
    
    D3D12_CPU_DESCRIPTOR_HANDLE uavHandle = descriptorHeap->GetCPUDescriptorHandleForHeapStart();
    uavHandle.ptr += device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV);
    device->CreateUnorderedAccessView(outputBuffer.Get(), nullptr, &outputUAVDesc, uavHandle);

    D3D12_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
    srvDesc.Format = DXGI_FORMAT_R8_UNORM;
    srvDesc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
    srvDesc.Texture2D.MostDetailedMip = 0;
    srvDesc.Texture2D.MipLevels = 1;
    srvDesc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;

    D3D12_CPU_DESCRIPTOR_HANDLE srvHandle = descriptorHeap->GetCPUDescriptorHandleForHeapStart();
    device->CreateShaderResourceView(texture, &srvDesc, srvHandle);

    D3D12_RESOURCE_BARRIER barrier = {};
    barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
    barrier.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
    barrier.Transition.pResource = texture;
    barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
    barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_UNORDERED_ACCESS;
    barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_NON_PIXEL_SHADER_RESOURCE;
    commandList->ResourceBarrier(1, &barrier);

    // Set the descriptor heap on the command list
    ID3D12DescriptorHeap* ppHeaps[] = { descriptorHeap.Get() };
    commandList->SetDescriptorHeaps(_countof(ppHeaps), ppHeaps);

    // Set root signature
    commandList->SetComputeRootSignature(rootSignature.Get());

    // Set Pipeline State
    commandList->SetPipelineState(computePSO.Get());

    // Set the root descriptor table
    D3D12_GPU_DESCRIPTOR_HANDLE gpuHandle = descriptorHeap->GetGPUDescriptorHandleForHeapStart();
    commandList->SetComputeRootDescriptorTable(0, gpuHandle);

    commandList->Dispatch(1, 1, 1);

    // Close and execute the command list
    hr = commandList->Close();
    if (FAILED(hr)) {
        std::cout << "Error: Failed to close command list!" << std::endl;
        return;
    }

    ID3D12CommandList* ppCommandLists[] = { commandList.Get() };
    commandQueue->ExecuteCommandLists(_countof(ppCommandLists), ppCommandLists);

    // Wait for the GPU to finish executing the command list
    ComPtr<ID3D12Fence> fence;
    hr = device->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&fence));
    if (FAILED(hr)) {
        std::cout << "Error: Failed to create fence!" << std::endl;
        return;
    }

    HANDLE fenceEvent = CreateEvent(nullptr, FALSE, FALSE, nullptr);
    if (fenceEvent == nullptr) 
    {
        std::cout << "Error: Failed to create fence event!" << std::endl;
        return;
    }

    hr = commandQueue->Signal(fence.Get(), 1);
    if (FAILED(hr)) 
    {
        std::cout << "Error: Failed to signal command queue!" << std::endl;
        return;
    }

    if (fence->GetCompletedValue() < 1) 
    {
        hr = fence->SetEventOnCompletion(1, fenceEvent);
        if (FAILED(hr)) {
            std::cout << "Error: Failed to set event on completion!" << std::endl;
            return;
        }
        WaitForSingleObject(fenceEvent, INFINITE);
    }

    CloseHandle(fenceEvent);

    //Reset command allocator and command list for readback
    hr = commandAllocator->Reset();
    if (FAILED(hr)) 
    {
        std::cout << "Error: Command allocator reset failed!" << std::endl;
        return;
    }

    hr = commandList->Reset(commandAllocator.Get(), nullptr);
    if (FAILED(hr))
    {
        std::cout << "Error: Command list reset failed!" << std::endl;
        return;
    }

    // read back
    ComPtr<ID3D12Resource> readbackBuffer;    
    heapProperties = {};
    heapProperties.Type = D3D12_HEAP_TYPE_READBACK;
    heapProperties.CreationNodeMask = 1;
    heapProperties.VisibleNodeMask = 1;
    heapProperties.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
    heapProperties.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;

    D3D12_RESOURCE_DESC readbackBufferDesc = {};
    readbackBufferDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
    readbackBufferDesc.Width = sizeof(float);
    readbackBufferDesc.Height = 1;
    readbackBufferDesc.DepthOrArraySize = 1;
    readbackBufferDesc.MipLevels = 1;
    readbackBufferDesc.Format = DXGI_FORMAT_UNKNOWN;
    readbackBufferDesc.SampleDesc.Count = 1;
    readbackBufferDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;
    readbackBufferDesc.Flags = D3D12_RESOURCE_FLAG_NONE;

    hr = device->CreateCommittedResource(
        &heapProperties,
        D3D12_HEAP_FLAG_NONE,
        &readbackBufferDesc,
        D3D12_RESOURCE_STATE_COPY_DEST,
        nullptr,
        IID_PPV_ARGS(&readbackBuffer));    
    if (FAILED(hr)) 
    {
        std::cout << "Error: Failed to create readback buffer!" << std::endl;
        return;
    }

    readbackBuffer->SetName(L"readbackBuffer");

    D3D12_RESOURCE_BARRIER barrier1 = {};
    barrier1.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
    barrier1.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
    barrier1.Transition.pResource = outputBuffer.Get();
    barrier1.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
    barrier1.Transition.StateBefore = D3D12_RESOURCE_STATE_UNORDERED_ACCESS;
    barrier1.Transition.StateAfter = D3D12_RESOURCE_STATE_COPY_SOURCE;
    commandList->ResourceBarrier(1, &barrier1);

    //commandList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(outputBuffer.Get(), D3D12_RESOURCE_STATE_UNORDERED_ACCESS, D3D12_RESOURCE_STATE_COPY_SOURCE));
    commandList->CopyResource(readbackBuffer.Get(), outputBuffer.Get());
    
    D3D12_RESOURCE_BARRIER barrier2 = {};
    barrier2.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
    barrier2.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE;
    barrier2.Transition.pResource = outputBuffer.Get();
    barrier2.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
    barrier2.Transition.StateBefore = D3D12_RESOURCE_STATE_COPY_SOURCE;
    barrier2.Transition.StateAfter = D3D12_RESOURCE_STATE_UNORDERED_ACCESS;
    commandList->ResourceBarrier(1, &barrier2);

    //commandList->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(outputBuffer.Get(), D3D12_RESOURCE_STATE_COPY_SOURCE, D3D12_RESOURCE_STATE_UNORDERED_ACCESS));

    hr = commandList->Close();
    if (FAILED(hr)) {
        std::cout << "Error: Failed to close command list!" << std::endl;
        return;
    }

    commandQueue->ExecuteCommandLists(_countof(ppCommandLists), ppCommandLists);

    hr = commandQueue->Signal(fence.Get(), 2);
    if (FAILED(hr)) 
    {
        std::cout << "Error: Failed to signal command queue!" << std::endl;
        return;
    }

    if (fence->GetCompletedValue() < 2) 
    {
        hr = fence->SetEventOnCompletion(2, fenceEvent);
        if (FAILED(hr)) 
        {
            std::cout << "Error: Failed to set event on completion!" << std::endl;
            return;
        }
        WaitForSingleObject(fenceEvent, INFINITE);
    }

    float maxValue;
    void* pData;
    CD3DX12_RANGE readRange(0, sizeof(float));
    hr = readbackBuffer->Map(0, &readRange, &pData);
    if (FAILED(hr)) 
    {
        std::cout << "Error: Failed to map readback buffer!" << std::endl;
        return;
    }

    maxValue = *reinterpret_cast<float*>(pData);   
    readbackBuffer->Unmap(0, nullptr);

    std::cout << "Maximum Texel Value: " << maxValue << std::endl;

}