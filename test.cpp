/*

To analyze and refactor `test.cpp` to follow DirectX 12 guidelines for finding the maximum texel value, we need to ensure proper initialization, resource creation, command list execution, and synchronization. We'll also move global variables to a separate file for better organization.

### Step-by-Step Plan:
1. **Initialize DirectX 12**: Create the device, command queue, command allocator, and command list.
2. **Create Descriptor Heaps**: Create descriptor heaps for CBV/SRV/UAV.
3. **Create Root Signature and Pipeline State Object (PSO)**: Create the root signature and compute PSO.
4. **Create and Upload Texture**: Create a texture resource and upload data to it.
5. **Set Descriptor Heaps and Root Descriptor Table**: Set the descriptor heaps and root descriptor table on the command list.
6. **Execute Command List and Synchronize**: Execute the command list and synchronize with the GPU using a fence.
7. **Find Maximum Texel Value**: Implement the compute shader to find the maximum texel value.

### Summary:
1. **Globals**: Moved global variables to `globals.h` and `globals.cpp`.
2. **Utility Functions**: Created utility functions in `utils.h` and `utils.cpp` for common tasks.
3. **Main File**: Refactored `test.cpp` to initialize DirectX 12, create resources, and find the maximum texel value.

This refactored code follows DirectX 12 guidelines and ensures proper initialization, resource creation, command list execution, and synchronization.

*/


#include "globals.h"
#include "utils.h"
#include <iostream>
#include "test.h"
using namespace std;

