#ifndef ICOMPONENT_H
#define ICOMPONENT_H

// 
class IComponent
{
public:
	enum ComponentFlags {								// BITS								// VAL			
		COMPONENT_NONE = 0,								// 0000 0000 0000 0000 0000			0
		COMPONENT_RIGID_BODY = 1 << 1,					// 0000 0000 0000 0000 0010			2
		COMPONENT_COLLIDABLE = 1 << 2,					// 0000 0000 0000 0000 0100			4	
		COMPONENT_DIRECTIONAL_LIGHT = 1 << 3,			// 0000 0000 0000 0000 1000			8
		COMPONENT_SPOTLIGHT = 1 << 4,					// 0000 0000 0000 0001 0000			16
		COMPONENT_POINTLIGHT = 1 << 5,					// 0000 0000 0000 0010 0000			32
		COMPONENT_SHADOW_CASTER = 1 << 6,				// 0000 0000 0000 0100 0000			64
	};

	IComponent(ComponentFlags& componentType);
	~IComponent();

	ComponentFlags GetComponentType();

private:
	ComponentFlags componentType;
};
#endif