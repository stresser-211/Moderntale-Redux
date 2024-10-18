#pragma once

#include "../incl.hpp"
#include "../utility.hpp"
#include "basic_objects.hpp"

static class trig_base : protected object, protected button {
	uint32_t activations;
protected:
	trig_base(void) = delete;
	virtual void main(void) = 0;
}

class TRGmove : public trig_base {
public:
	TRGmove(void) = delete;
}
class TRGrotate : public trig_base {
public:
	TRGrotate(void) = delete;
}
class TRGalpha : public trig_base {
public:
	TRGalpha(void) = delete;
}
class TRGscale : public trig_base {
public:
	TRGscale(void) = delete;
}
class TRGfollow : public trig_base {
public:
	TRGfollow(void) = delete;
}
class TRGcollision : public trig_base {
public:
	TRGcollision(void) = delete;
}
class TRGcounter : public trig_base {
public:
	TRGcounter(void) = delete;
}
class TRGevent : public trig_base {
public:
	TRGevent(void) = delete;
}