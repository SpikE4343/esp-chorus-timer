
#include "filters.h"

float lpfAlpha(float cutoff, float sampleRate)
{
    float rc = 1.0/(cutoff*2*3.14169); 
    float dt = 1.0/sampleRate; 
    return dt/(rc+dt);
}

float lowPassFilter(float value, float sample, float alpha)
{
    //float rc = 1.0/(cutoff*2*3.14); 
    //float dt = 1.0/sampleRate; 
    //float alpha = dt/(rc+dt);
     
    return value + (alpha*(sample - value));
    
}