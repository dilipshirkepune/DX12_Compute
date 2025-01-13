#pragma once

int main()
{
    // Initialize DirectX 12
    UINT dxgiFactoryFlags = 0;
#if defined(_DEBUG)
    ComPtr<ID3D12Debug> debugController;
    if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController)))) {
        debugController->EnableDebugLayer();
        dxgiFactoryFlags |= DXGI_CREATE_FACTORY_DEBUG;
    }
#endif

    ComPtr<IDXGIFactory4> factory;
    HRESULT hr = CreateDXGIFactory2(dxgiFactoryFlags, IID_PPV_ARGS(&factory));
    if (FAILED(hr)) {
        std::cout << "Error: Failed to create DXGI factory!" << std::endl;
        return -1;
    }

    ComPtr<IDXGIAdapter1> hardwareAdapter;
    for (UINT adapterIndex = 0; DXGI_ERROR_NOT_FOUND != factory->EnumAdapters1(adapterIndex, &hardwareAdapter); ++adapterIndex) {
        DXGI_ADAPTER_DESC1 desc;
        hardwareAdapter->GetDesc1(&desc);

        if (desc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE) {
            continue;
        }

        hr = D3D12CreateDevice(hardwareAdapter.Get(), D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&device));
        if (SUCCEEDED(hr)) {
            break;
        }
    }

    if (FAILED(hr)) {
        std::cout << "Error: Failed to create D3D12 device!" << std::endl;
        return -1;
    }

    // Create command queue
    D3D12_COMMAND_QUEUE_DESC queueDesc = {};
    queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
    queueDesc.Type = D3D12_COMMAND_LIST_TYPE_COMPUTE;

    hr = device->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(&commandQueue));
    if (FAILED(hr))
    {
        std::cout << "Error: Failed to create command queue!" << std::endl;
        return -1;
    }


    // Create a command allocator and command list   
    hr = device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_COMPUTE, IID_PPV_ARGS(&commandAllocator));
    if (FAILED(hr)) {
        std::cout << "Error: Failed to create command allocator!" << std::endl;
        return -1;
    }

    hr = device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_COMPUTE, commandAllocator.Get(), nullptr, IID_PPV_ARGS(&commandList));
    if (FAILED(hr)) {
        std::cout << "Error: Failed to create command list!" << std::endl;
        return -1;
    }


    // Create a test texture with random float values    
    ComPtr<ID3D12Resource> testTexture = CreateTestTexture(device, commandList.Get(), commandQueue.Get(), 4, 4);
    if (testTexture == nullptr) {
        std::cout << "Failed to generate texture" << std::endl;
        return -1;
    }

    FindMaxValueInTexture(device, commandQueue.Get(), testTexture.Get());
    
    std::cout << "Press number" << std::endl;
    int temp = 0;
    std::cin >> temp;

    std::cout << "Done!" << std::endl;  

    return 0;
}
