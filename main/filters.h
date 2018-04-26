#ifndef _filters_INCLUDED_
#define _filters_INCLUDED_

float lpfAlpha(float cutoff, float sampleRate);
float lowPassFilter(float value, float sample, float alpha);

#endif