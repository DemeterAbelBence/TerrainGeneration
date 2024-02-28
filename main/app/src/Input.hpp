#pragma once

#include "util/glfw/glfw.hpp"

#include <vector>

namespace Input {
	template<typename T>
	struct Event {
		glfw::Key* key;
		void(T::*operation)(float) = nullptr;
		int sign;
		Event(glfw::Key* k, void(T::*o)(float), int s) { key = k; operation = o; sign = s; }
	};

	template<typename T>
	class InputHandler {
	private:
		std::vector<Event<T>> events;
		float event_param = 0.0f;

	public:
		InputHandler() {}

		inline void setEventParamValue(float value) { event_param = value; }
		inline void addEvent(Event<T> event) { events.push_back(event); }
		bool handleEvents(GLFWwindow* window, T* t);

		~InputHandler();
	};

	template<typename T>
	bool InputHandler<T>::handleEvents(GLFWwindow* window, T* t) {
		bool event_occured = false;
		for (const auto& e : events) {
			if (e.key->isPressed(window)) {
				(t->*e.operation)(e.sign * event_param);
				event_occured = true;
			}
		}
		return event_occured;
	}

	template<typename T>
	InputHandler<T>::~InputHandler() {
		for (const auto& e : events)
			delete e.key;
	}
};