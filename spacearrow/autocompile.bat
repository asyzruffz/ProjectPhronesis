g++ main.cpp core.cpp resource_manager.cpp scene_handler.cpp scene.cpp level_scene.cpp entity.cpp component.cpp game_object.cpp transform_2d.cpp game_object_2d.cpp sprite.cpp rigidbody_2d.cpp contact_listener_2d.cpp script_component.cpp test_script.cpp -o SpaceArrow -std=c++11 -I"C:\SFML-2.1\include" -L"C:\SFML-2.1\lib" -I"C:\Box2D"  -L"C:\Box2D\Build\Box2D" -lBox2D -lsfml-system -lsfml-window -lopengl32 -lglu32 -lsfml-graphics -lsfml-main -lsfml-audio -lsfml-network