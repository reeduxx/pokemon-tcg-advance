#include "bn_blending.h"
#include "bn_core.h"
#include "bn_log.h"
#include "bn_regular_bg_ptr.h"
#include "bn_sprite_ptr.h"
#include "intro.h"
#include "main_menu.h"
#include "titlescreen.h"
#include "bn_regular_bg_items_pokemon_logo.h"
#include "bn_sprite_items_tcg_left.h"
#include "bn_sprite_items_tcg_right.h"

int main() {
    bn::core::init();
    
    enum class State {
        Intro,
        TitleScreen,
        MainMenu,
        Exit
    };

    State state = State::Intro;
    bn::optional<Intro> intro;
    bn::optional<TitleScreen> title_screen;
    bn::optional<MainMenu> main_menu;
    intro.emplace();

    while(state != State::Exit) {
        switch(state) {
            case State::Intro:
                if(intro && intro->update()) {
                    intro.reset();
                    title_screen.emplace();
                    state = State::TitleScreen;
                }

                break;
            case State::TitleScreen:
                if(title_screen && title_screen->update()) {
                    title_screen.reset();
                    main_menu.emplace();
                    state = State::MainMenu;
                }

                break;
            case State::MainMenu:
                if(main_menu && main_menu->update()) {
                    MainMenu::Choice choice = main_menu->choice();

                    switch(choice) {
                        case MainMenu::Choice::Continue:
                            // TODO: Load save and continue from last save
                            state = State::Exit;
                            break;
                        case MainMenu::Choice::NewGame:
                            // TODO: Transition to new game scene
                            state = State::Exit;
                            break;
                        case MainMenu::Choice::EReader:
                            // TODO: Transition to E-Reader scene
                            state = State::Exit;
                            break;
                        case MainMenu::Choice::Option:
                            // TODO: Transition to option scene
                            state = State::Exit;
                            break;
                        case MainMenu::Choice::None:
                        default:
                            break;
                    }
                }

                break;
            case State::Exit:
            default:
                break;
        }

        bn::core::update();
    }

    return 0;
}
