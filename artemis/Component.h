#ifndef COMPONENT_H
#define COMPONENT_H

namespace artemis {
	/**
	 * A tag class. All components in the system must extend this class.
	 */
	class Component {
	public:
		virtual ~Component() = 0;
		virtual bool isDirty();
		virtual bool isActive();
		virtual void setDirty(bool dirty);
		virtual void setActive(bool active);
	protected:
		Component() :mActive(true), mDirty(true) {};
		bool mActive;
		bool mDirty;
	};

};

#endif
