message("Building libraries")

add_library(extLibs
AssetManager.cpp
Game.cpp
InputManager.cpp
Bot.cpp
SplashState.cpp
StateMachine.cpp
Car.cpp
MainMenuState.cpp
GameState.cpp
GameOverState.cpp
PlayerCar.cpp
GameMap.cpp
NetworkManager.cpp
PauseState.cpp
BustedState.cpp
Bullet.cpp
ClientState.cpp
ServerState.cpp
GameSimulator.cpp
)
target_link_libraries(extLibs ${SFML_LIBRARIES} ${SFML_DEPENDENCIES} -pthread)
message("SFML_LIBRARIES LOCATION:${SFML_LIBRARIES}")
message("Build successful")

