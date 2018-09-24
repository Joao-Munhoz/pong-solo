FLAGS=-lncurses -lpthread -lportaudio -std=c++11

all: model

model: model_mainloop.cpp oo_model.cpp sound_model.cpp keyboard_model.cpp screen_model.cpp sound_model.hpp oo_model.hpp
	g++ -omodel model_mainloop.cpp oo_model.cpp sound_model.cpp keyboard_model.cpp screen_model.cpp $(FLAGS)

test: model
	./model 2>/dev/null

