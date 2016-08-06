#include "RenderSortableComponent.hpp"

RenderSortableComponent::RenderSortableComponent()
{
	mPiority = 100;
}

RenderSortableComponent::~RenderSortableComponent()
{
}

void RenderSortableComponent::setPiority(int piority)
{
	mPiority = piority;
}

int RenderSortableComponent::getPiority()
{
	return mPiority;
}
