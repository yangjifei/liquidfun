#include "api.h"
#include "stdlib.h"

void *api_buffer = 0;
size_t api_buffer_size = 0;
float *GetFloatBuffer(int size)
{
    return nullptr;
}

int *GetIntBuffer(int size)
{
    return nullptr;
}

void CheckBufferSize(int size){
    if(api_buffer_size == 0){
        api_buffer = malloc(size);
    }else{
        if(size > api_buffer_size){
            api_buffer = realloc(api_buffer, size);
        }
    }
    api_buffer_size = size;
}
