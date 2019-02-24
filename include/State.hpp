#ifndef STATE_HPP
#define STATE_HPP

namespace cp
{
	class State {
		public:
		virtual void init			() = 0;
		virtual void handle_input	(float delta) = 0;
		virtual void update			(float delta) = 0;
		virtual void draw			(float delta) = 0;
		virtual void pause			(){}
		virtual void resume			(){}
	};
} // namespace cp
#endif //STATE_HPP