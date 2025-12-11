#include "bn_core.h"
#include "intro.h"
#include "main_menu.h"
#include "option_menu.h"
#include "title_screen.h"

int main() {
    bn::core::init();
    
    enum class State {
        Intro,
        TitleScreen,
        MainMenu,
        OptionMenu,
        Exit
    };

    State state = State::Intro;
    bn::optional<Intro> intro;
    bn::optional<TitleScreen> title_screen;
    bn::optional<MainMenu> main_menu;
    bn::optional<OptionMenu> option_menu;
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
                    MainMenu::Choice choice = main_menu->get_choice();

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
                            main_menu.reset();
                            option_menu.emplace();
                            state = State::OptionMenu;
                            break;
                        case MainMenu::Choice::BackToTitle:
                            main_menu.reset();
                            title_screen.emplace();
                            state = State::TitleScreen;
                            break;
                        case MainMenu::Choice::None:
                        default:
                            break;
                    }
                }

                break;
            case State::OptionMenu:
                if(option_menu && option_menu->update()) {
                    option_menu.reset();
                    main_menu.emplace();
                    state = State::MainMenu;
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
