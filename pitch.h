#ifndef MICFX_PITCH_H
#define MICFX_PITCH_H
#include <stdint.h>
#define MF_RING 16384u
#define MF_MASK (MF_RING-1u)
typedef struct { float ring[MF_RING]; uint32_t cursor, filled; float phase; } MFPitch;
static inline void mf_reset(MFPitch *s) { s->cursor=0; s->filled=0; s->phase=0; }
static inline float mf_clip(float x) { return x>1.f?1.f:x< -1.f?-1.f:x; }
static inline float mf_read(MFPitch *s,float delay) { unsigned n=(unsigned)delay; float f=delay-n; float a=s->ring[(s->cursor-n)&MF_MASK]; float b=s->ring[(s->cursor-n-1u)&MF_MASK]; return a+(b-a)*f; }
static inline float mf_sample(MFPitch *s,float x,float ratio,float gain,float mix,unsigned sampleRate) {
    const float span=0.040f*sampleRate, minDelay=0.004f*sampleRate+2.f;
    s->ring[s->cursor]=x; if(s->filled<MF_RING) ++s->filled;
    float y=x;
    if (mix>0.f && (ratio<0.9999f || ratio>1.0001f) && s->filled>(unsigned)(span+minDelay+2.f)) {
        float p=s->phase, q=p+0.5f; if(q>=1.f) q-=1.f;
        float w=1.f-(p>0.5f?2.f*p-1.f:1.f-2.f*p); w=w*w*(3.f-2.f*w);
        float a=mf_read(s,minDelay+p*span), b=mf_read(s,minDelay+q*span);
        y=x*(1.f-mix)+(a*w+b*(1.f-w))*mix;
        p+=(1.f-ratio)/span; if(p>=1.f)p-=1.f; if(p<0.f)p+=1.f; s->phase=p;
    }
    s->cursor=(s->cursor+1u)&MF_MASK; return mf_clip(y*gain);
}
#endif
