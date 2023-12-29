#include "api.h"
#include "stdlib.h"
#include "api_body.h"
#include "api_contacts.h"
#include "api_fixture.h"
#include "api_joint.h"
#include "api_particlegroups.h"
#include "api_particles.h"
#include "api_particlesystem.h"
#include "api_raycast.h"
#include "api_shape.h"
#include "api_utility.h"
#include "api_world.h"

void *api_buffer = 0;
size_t api_buffer_size = 0;

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

float *GetFloatBuffer(int size)
{
    CheckBufferSize(size*sizeof(int));
    return (float*)api_buffer;
}

int *GetIntBuffer(int size)
{
    CheckBufferSize(size*sizeof(float));
    return (int*)api_buffer;
}

