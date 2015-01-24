g++ code/main.cpp code/phro_game.cpp code/phro_state_stack.cpp code/phro_state.cpp code/states/phro_title_state.cpp code/states/phro_menu_state.cpp code/states/phro_game_state.cpp code/states/phro_pause_state.cpp code/resourceshandling/phro_resource_manager.cpp code/resourceshandling/phro_animation_manager.cpp code/resourceshandling/phro_anim_unit.cpp code/resourceshandling/phro_frame_info.cpp code/mechanics/phro_character.cpp code/mechanics/phro_tile.cpp code/mechanics/phro_section.cpp code/mechanics/phro_world.cpp code/structures/phro_entity.cpp code/structures/phro_scene_node.cpp code/structures/phro_sprite_node.cpp -o Phronesis -std=c++11 -I"c:\SFML-2.1\include" -I"c:\Thor\include" -L"c:\SFML-2.1\lib" -L"c:\Thor\lib" -lsfml-system -lsfml-window -lopengl32 -lglu32 -lsfml-graphics -lsfml-main -lsfml-audio -lsfml-network -lthor && Phronesis