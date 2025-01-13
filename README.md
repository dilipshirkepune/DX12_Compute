Very basic DX12 Computer shader application. Where we are trying to read texture data as input and output process data staring with R8_UNORM format. 
Once process through computer shader read back those values to CPU memory and print into main application.

Hiting following errors 
D3D12 ERROR: ID3D12DescriptorHeap::GetGPUDescriptorHandleForHeapStart: GetGPUDescriptorHandleForHeapStart is invalid to call on a descriptor heap that does not have DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE set. If the heap is not supposed to be shader visible, then GetCPUDescriptorHandleForHeapStart would be the appropriate method to call. That call is valid both for shader visible and non shader visible descriptor heaps. [ STATE_GETTING ERROR #1315: DESCRIPTOR_HEAP_NOT_SHADER_VISIBLE]



previsious errors resolved -
D3D12 WARNING: ID3D12Device::CreateCommittedResource: Ignoring InitialState D3D12_RESOURCE_STATE_UNORDERED_ACCESS. Buffers are effectively created in state D3D12_RESOURCE_STATE_COMMON. [ STATE_CREATION WARNING #1328: CREATERESOURCE_STATE_IGNORED]
D3D12 ERROR: CGraphicsCommandList::SetComputeRootDescriptorTable: Specified GPU Descriptor Handle (ptr = 0x24d7fa72820 at 0 offsetInDescriptorsFromDescriptorHeapStart) of type UAV, for Root Signature (0x0000024D02544460:'Unnamed ID3D12RootSignature Object')'s Descriptor Table (at Parameter Index [0])'s Descriptor Range (at Range Index [0] of type D3D12_DESCRIPTOR_RANGE_TYPE_SRV) have mismatching types. All descriptors of descriptor ranges declared STATIC (not-DESCRIPTORS_VOLATILE) in a root signature must be initialized prior to being set on the command list. [ EXECUTION ERROR #646: INVALID_DESCRIPTOR_HANDLE]
D3D12 ERROR: CGraphicsCommandList::SetComputeRootDescriptorTable: Specified GPU Descriptor Handle (ptr = 0x24d7fa72820 at 1 offsetInDescriptorsFromDescriptorHeapStart), for Root Signature (0x0000024D02544460:'Unnamed ID3D12RootSignature Object')'s Descriptor Table (at Parameter Index [0])'s Descriptor Range (at Range Index [1] of type D3D12_DESCRIPTOR_RANGE_TYPE_UAV) has not been initialized. All descriptors of descriptor ranges declared STATIC (not-DESCRIPTORS_VOLATILE) in a root signature must be initialized prior to being set on the command list. [ EXECUTION ERROR #646: INVALID_DESCRIPTOR_HANDLE]
D3D12 ERROR: ID3D12CommandList::Dispatch: No pipeline state has been set in this command list.  The runtime will use a default no-op pipeline state. [ EXECUTION ERROR #1045: COMMAND_LIST_PIPELINE_STATE_NOT_SET]



D3D12 ERROR: CGraphicsCommandList::SetComputeRootDescriptorTable: Specified GPU Descriptor Handle (ptr = 0x258b6191810 at 1 offsetInDescriptorsFromDescriptorHeapStart), for Root Signature (0x00000258B896C8E0:'Unnamed ID3D12RootSignature Object')'s Descriptor Table (at Parameter Index [0])'s Descriptor Range (at Range Index [1] of type D3D12_DESCRIPTOR_RANGE_TYPE_UAV) has not been initialized. All descriptors of descriptor ranges declared STATIC (not-DESCRIPTORS_VOLATILE) in a root signature must be initialized prior to being set on the command list. [ EXECUTION ERROR #646: INVALID_DESCRIPTOR_HANDLE]


D3D12 ERROR: CGraphicsCommandList::SetComputeRootDescriptorTable: Specified GPU Descriptor Handle (ptr = 0x168304e21e0 at 1 offsetInDescriptorsFromDescriptorHeapStart), for Root Signature (0x0000016832CFE990:'Unnamed ID3D12RootSignature Object')'s Descriptor Table (at Parameter Index [0])'s Descriptor Range (at Range Index [1] of type D3D12_DESCRIPTOR_RANGE_TYPE_UAV) has not been initialized. All descriptors of descriptor ranges declared STATIC (not-DESCRIPTORS_VOLATILE) in a root signature must be initialized prior to being set on the command list. [ EXECUTION ERROR #646: INVALID_DESCRIPTOR_HANDLE]


D3D12 WARNING: ID3D12Device::CreateCommittedResource: Ignoring InitialState D3D12_RESOURCE_STATE_UNORDERED_ACCESS. Buffers are effectively created in state D3D12_RESOURCE_STATE_COMMON. [ STATE_CREATION WARNING #1328: CREATERESOURCE_STATE_IGNORED]
D3D12 ERROR: CGraphicsCommandList::SetComputeRootDescriptorTable: Specified GPU Descriptor Handle (ptr = 0x22ca3aca9a8 at 1 offsetInDescriptorsFromDescriptorHeapStart), for Root Signature (0x0000022CA40FEBE0:'Unnamed ID3D12RootSignature Object')'s Descriptor Table (at Parameter Index [0])'s Descriptor Range (at Range Index [0] of type D3D12_DESCRIPTOR_RANGE_TYPE_SRV) has not been initialized. All descriptors of descriptor ranges declared STATIC (not-DESCRIPTORS_VOLATILE) in a root signature must be initialized prior to being set on the command list. [ EXECUTION ERROR #646: INVALID_DESCRIPTOR_HANDLE]
D3D12 ERROR: CGraphicsCommandList::SetComputeRootDescriptorTable: Descriptor handle is not set or initialized because of insufficient descriptors in the provided Descriptor Heap. Root Signature (0x0000022CA40FEBE0:'Unnamed ID3D12RootSignature Object')'s Descriptor Table (at Parameter Index [0])'s Descriptor Range (at Range Index [1]) is at 1 offsetInDescriptorsFromTableStart, but provided GPU Descriptor Handle (ptr=0x22ca3aca9a8) is at 2 offsetInDescriptorsFromDescriptorHeapStart from Heap (0x0000022CA4172CD0:'Unnamed ID3D12DescriptorHeap Object'), which has 2 NumDescriptors, which can only provide 0 descriptors. All descriptors of descriptor ranges declared STATIC (not-DESCRIPTORS_VOLATILE) in a root signature must be initialized prior to being set on the command list. [ EXECUTION ERROR #646: INVALID_DESCRIPTOR_HANDLE]
D3D12 ERROR: ID3D12CommandList::Dispatch: No pipeline state has been set in this command list.  The runtime will use a default no-op pipeline state. [ EXECUTION ERROR #1045: COMMAND_LIST_PIPELINE_STATE_NOT_SET]



'test2.exe' (Win32): Loaded 'C:\Windows\System32\dxilconv.dll'. 
D3D12 WARNING: ID3D12Device::CreateCommittedResource: Ignoring InitialState D3D12_RESOURCE_STATE_UNORDERED_ACCESS. Buffers are effectively created in state D3D12_RESOURCE_STATE_COMMON. [ STATE_CREATION WARNING #1328: CREATERESOURCE_STATE_IGNORED]
D3D12 ERROR: CGraphicsCommandList::SetComputeRootDescriptorTable: Specified GPU Descriptor Handle (ptr = 0x2c8c4153210 at 1 offsetInDescriptorsFromDescriptorHeapStart), for Root Signature (0x000002C8C481E320:'Unnamed ID3D12RootSignature Object')'s Descriptor Table (at Parameter Index [0])'s Descriptor Range (at Range Index [1] of type D3D12_DESCRIPTOR_RANGE_TYPE_UAV) has not been initialized. All descriptors of descriptor ranges declared STATIC (not-DESCRIPTORS_VOLATILE) in a root signature must be initialized prior to being set on the command list. [ EXECUTION ERROR #646: INVALID_DESCRIPTOR_HANDLE]
D3D12 ERROR: ID3D12CommandList::Dispatch: No pipeline state has been set in this command list.  The runtime will use a default no-op pipeline state. [ EXECUTION ERROR #1045: COMMAND_LIST_PIPELINE_STATE_NOT_SET]



C:\Users\dilip.shirke\source\repos\test4\ComputeShader.hlsl(21,5-30): warning X3583: race condition writing to shared resource detected, note that threads will be writing the same value, but performance may be diminished due to contention.
'test2.exe' (Win32): Loaded 'C:\Windows\System32\dxilconv.dll'. 
D3D12 WARNING: ID3D12Device::CreateCommittedResource: Ignoring InitialState D3D12_RESOURCE_STATE_UNORDERED_ACCESS. Buffers are effectively created in state D3D12_RESOURCE_STATE_COMMON. [ STATE_CREATION WARNING #1328: CREATERESOURCE_STATE_IGNORED]
D3D12 ERROR: ID3D12CommandQueue::ExecuteCommandLists: Using CGraphicsCommandList::SetComputeRootDescriptorTable on Command List (0x00000162B1EB7480:'Unnamed ID3D12GraphicsCommandList Object'): Resource state (0x8771DC10: D3D12_RESOURCE_STATE_COPY_DEST) of resource (0x00000162B1E5ED40:'Unnamed ID3D12Resource Object') (subresource: 0) is invalid for use as a NON_PIXEL_SHADER_RESOURCE.  Expected State Bits (all): 0x8771DBF0: D3D12_RESOURCE_STATE_NON_PIXEL_SHADER_RESOURCE, Actual State: 0x8771DBD0: D3D12_RESOURCE_STATE_COPY_DEST, Missing State: 0x40: D3D12_RESOURCE_STATE_NON_PIXEL_SHADER_RESOURCE. [ EXECUTION ERROR #538: INVALID_SUBRESOURCE_STATE]
D3D12 ERROR: ID3D12Device::CreateCommittedResource: A buffer cannot be created on a D3D12_HEAP_TYPE_UPLOAD or D3D12_HEAP_TYPE_READBACK heap when either D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET or D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS is used. [ STATE_CREATION ERROR #638: CREATERESOURCEANDHEAP_INVALIDHEAPPROPERTIES]
Exception thrown at 0x00007FFA1B3AFB4C in test2.exe: Microsoft C++ exception: _com_error at memory location 0x000000108771E2F0.



'test2.exe' (Win32): Loaded 'C:\Windows\System32\dxilconv.dll'. 
D3D12 WARNING: ID3D12Device::CreateCommittedResource: Ignoring InitialState D3D12_RESOURCE_STATE_UNORDERED_ACCESS. Buffers are effectively created in state D3D12_RESOURCE_STATE_COMMON. [ STATE_CREATION WARNING #1328: CREATERESOURCE_STATE_IGNORED]
D3D12 ERROR: ID3D12CommandQueue::ExecuteCommandLists: Using CGraphicsCommandList::SetComputeRootDescriptorTable on Command List (0x0000022D1A6DC310:'Unnamed ID3D12GraphicsCommandList Object'): Resource state (0xF42FE210: D3D12_RESOURCE_STATE_COPY_DEST) of resource (0x0000022D1A694150:'Unnamed ID3D12Resource Object') (subresource: 0) is invalid for use as a NON_PIXEL_SHADER_RESOURCE.  Expected State Bits (all): 0xF42FE1F0: D3D12_RESOURCE_STATE_NON_PIXEL_SHADER_RESOURCE, Actual State: 0xF42FE1D0: D3D12_RESOURCE_STATE_COPY_DEST, Missing State: 0x40: D3D12_RESOURCE_STATE_NON_PIXEL_SHADER_RESOURCE. [ EXECUTION ERROR #538: INVALID_SUBRESOURCE_STATE]


Resource state (D3D12_RESOURCE_STATE_COPY_DEST) of resource, (subresource: 0) is invalid for use as a NON_PIXEL_SHADER_RESOURCE.  Expected State Bits (all) D3D12_RESOURCE_STATE_NON_PIXEL_SHADER_RESOURCE, Actual State: D3D12_RESOURCE_STATE_COPY_DEST, Missing State:  D3D12_RESOURCE_STATE_NON_PIXEL_SHADER_RESOURCE. [ EXECUTION ERROR #538: INVALID_SUBRESOURCE_STATE]


D3D12 WARNING: ID3D12Device::CreateCommittedResource: Ignoring InitialState D3D12_RESOURCE_STATE_UNORDERED_ACCESS. Buffers are effectively created in state D3D12_RESOURCE_STATE_COMMON. [ STATE_CREATION WARNING #1328: CREATERESOURCE_STATE_IGNORED]
D3D12 ERROR: ID3D12CommandQueue::ExecuteCommandLists: Using CGraphicsCommandList::SetComputeRootDescriptorTable on Command List (0x00000231C14EEEA0:'Unnamed ID3D12GraphicsCommandList Object'): Resource state (0x263DE0D0: D3D12_RESOURCE_STATE_COPY_DEST) of resource (0x00000231C1492FC0:'Unnamed ID3D12Resource Object') (subresource: 0) is invalid for use as a NON_PIXEL_SHADER_RESOURCE.  Expected State Bits (all): 0x263DE0B0: D3D12_RESOURCE_STATE_NON_PIXEL_SHADER_RESOURCE, Actual State: 0x263DE090: D3D12_RESOURCE_STATE_COPY_DEST, Missing State: 0x40: D3D12_RESOURCE_STATE_NON_PIXEL_SHADER_RESOURCE. [ EXECUTION ERROR #538: INVALID_SUBRESOURCE_STATE]
D3D12 ERROR: ID3D12Device::CreateCommittedResource: A buffer cannot be created on a D3D12_HEAP_TYPE_UPLOAD or D3D12_HEAP_TYPE_READBACK heap when either D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET or D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS is used. [ STATE_CREATION ERROR #638: CREATERESOURCEANDHEAP_INVALIDHEAPPROPERTIES]
Exception thrown at 0x00007FFA1B3AFB4C in test2.exe: Microsoft C++ exception: _com_error at memory location 0x0000006F263DE7B0.
The thread 0x7b28 has exited with code 0 (0x0).


D3D12 ERROR: ID3D12Device::CreateCommittedResource: A buffer cannot be created on a D3D12_HEAP_TYPE_UPLOAD or D3D12_HEAP_TYPE_READBACK heap when either D3D12_RESOURCE_FLAG_ALLOW_RENDER_TARGET or D3D12_RESOURCE_FLAG_ALLOW_UNORDERED_ACCESS is used. [ STATE_CREATION ERROR #638: CREATERESOURCEANDHEAP_INVALIDHEAPPROPERTIES]
Exception thrown at 0x00007FFA1B3AFB4C in test2.exe: Microsoft C++ exception: _com_error at memory location 0x0000000270FFE240.


execution error:547 - command_list_closed
- resolved after reset the cmd allocator and list


D3D12 ERROR: ID3D12Resource2::ID3D12Resource::Map: Map and Unmap can not be called on a resource associated with a heap that has the CPU page properties of D3D12_CPU_PAGE_PROPERTY_NOT_AVAILABLE. Heaps of the type D3D12_HEAP_TYPE_DEFAULT should be assumed to have these properties. [ EXECUTION ERROR #822: MAP_INVALIDHEAP]
The program '[0x25D8] test2.exe' has exited with code 0 (0x0).


Exception thrown at 0x00007FFA1B3AFB4C in test2.exe: Microsoft C++ exception: _com_error at memory location 0x000000A6A4AFEB40.
