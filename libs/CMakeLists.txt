message("Building libraries")

add_library(extLibs AssetManager.cpp Game.cpp InputManager.cpp Bot.cpp SplashState.cpp State.cpp StateMachine.cpp Car.cpp MainMenuState.cpp GameState.cpp GameOverState.cpp Cars.cpp)
target_link_libraries(extLibs ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
message("SFML_LIBRARIES LOCATION:${SFML_LIBRARIES}")
message("Build successful")

