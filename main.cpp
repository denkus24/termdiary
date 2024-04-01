#include <ftxui/component/component.hpp>
#include "ftxui/screen/screen.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/dom/elements.hpp"
#include "ftxui/component/component_options.hpp"
#include "diary.h"

using namespace ftxui;

Component ModalComponent(std::function<void()> deleteEntry,
                         std::function<void()> hideModal) {
    auto component = Container::Horizontal({
                                                   Button("Delete", deleteEntry, ButtonOption::Animated(Color::Green)) |
                                                   borderEmpty,
                                                   Button("No, exit", hideModal, ButtonOption::Animated(Color::Red)) |
                                                   borderEmpty
                                           });

    component |= Renderer([&](Element inner) {
        return vbox({
                            separatorEmpty(),
                            text("  Do you want to delete this entry?  "),
                            separatorEmpty(),
                            separator(),
                            inner | hcenter,
                    })                               //
               | size(WIDTH, GREATER_THAN, 30)  //
               | border;                        //
    });
    return component;
}

void design(vector<std::string> _titles, Diary *_diary) {
    //Variables initialization
    auto screen = ScreenInteractive::Fullscreen();

    Diary *diaryExample = _diary;

    int leftSide_size = 19;

    std::vector<std::string> noteChoosingVariants = _titles;
    std::vector<Entry> currentEntries = diaryExample->getEntries();

    std::vector<std::string> typesVariants{"Note", "Event", "Contact"};

    int selected = 0;
    int tab_selected;
    int newRightTabSelected;
    int rightSidePageSelect = 0;
    int radioButtonSelected = 0;

    std::string title = "     ";
    std::string text, name, surname, notes, contact, location, description, time;

    bool modal_shown = false;

    auto show_modal = [&] { modal_shown = true; };
    auto hide_modal = [&] { modal_shown = false; };
    auto exit = screen.ExitLoopClosure();
    auto deleteEntry = [&] {
        noteChoosingVariants.erase(
                next(noteChoosingVariants.begin(), selected));
        currentEntries.erase(next(currentEntries.begin(), selected));
        rightSidePageSelect = 0;
        diaryExample->deleteEntry(selected);
        hide_modal();
    };
    // Choosing menu
    MenuOption option;
    option.on_enter = screen.ExitLoopClosure();
    option.on_change = [&] {
        rightSidePageSelect = 1;
        title = noteChoosingVariants[selected];

        if (currentEntries[selected].getType() == "Contact") {
            tab_selected = 1;

            name = currentEntries[selected].name;
            surname = currentEntries[selected].surname;
            notes = currentEntries[selected].notes;
        } else if (currentEntries[selected].getType() == "Event") {
            tab_selected = 2;

            time = currentEntries[selected].fromToTime;
            description = currentEntries[selected].description;
            location = currentEntries[selected].location;
        } else {
            tab_selected = 0;

            text = currentEntries[selected].text;
        }

    };

    auto noteChoosingMenu = ftxui::Menu(&noteChoosingVariants, &selected, option);
    //Add note button
    auto addButtonArea = Container::Horizontal({
                                                       Button("Add new note ＋", [&] {
                                                                  rightSidePageSelect = 2;
                                                              },
                                                              ButtonOption::Animated(Color::Green)) | center,
                                               });

    // Button + menu container
    auto leftSideContainer = Container::Vertical({
                                                         addButtonArea | flex | center,
                                                         noteChoosingMenu | border | flex
                                                 });


    auto leftSide = Renderer(leftSideContainer, [&] {
        return vbox({
                            addButtonArea->Render() | hcenter,
                            separator(),
                            noteChoosingMenu->Render() | flex | vscroll_indicator
                    });
    });

    leftSide->Add(noteChoosingMenu);
    // Text input
    auto textInput = Input(&text, "Text");

    // Manipulation buttons
    auto deleteButton = Container::Horizontal({
                                                      Button("Delete", show_modal, ButtonOption::Animated(Color::Red)),
                                              });

    auto saveButton = Container::Horizontal({
                                                    Button("Save", [&] {
                                                        if (currentEntries[selected].getType() == "Contact") {
                                                            Contact newContact = Contact(currentEntries[selected].title,
                                                                                         name, surname, notes);
                                                            diaryExample->entryUpdate(currentEntries[selected],
                                                                                      newContact, selected);
                                                            currentEntries[selected].name = name;
                                                            currentEntries[selected].surname = surname;
                                                            currentEntries[selected].notes = notes;

                                                        } else if (currentEntries[selected].getType() == "Event") {
                                                            Accident newEvent = Accident(currentEntries[selected].title,
                                                                                         time, description, location);
                                                            diaryExample->entryUpdate(currentEntries[selected],
                                                                                      newEvent, selected);
                                                            currentEntries[selected].fromToTime = time;
                                                            currentEntries[selected].description = description;
                                                            currentEntries[selected].location = location;
                                                        } else {
                                                            Note newNote = Note(currentEntries[selected].title, text);
                                                            diaryExample->entryUpdate(currentEntries[selected], newNote,
                                                                                      selected);
                                                            currentEntries[selected].text = text;
                                                        }
                                                        //diaryExample->entryUpdate(currentEntries[selected], )
                                                    }, ButtonOption::Animated(Color::BlueLight)),
                                            });


    auto noteConatiner = Container::Vertical({
                                                     textInput
                                             });
    // Note page
    auto notePage = Renderer(noteConatiner, [&] {
        return vbox(
                //ftxui::text(noteChoosingVariants[selected]),
                ftxui::text(title) | bold | border | center,
                hbox(ftxui::text("Text:") | bold, textInput->Render()) | flex
        );
    });
    // Also inputs :D
    auto nameInput = Input(&name, "Name");
    auto surnameInput = Input(&surname, "Surname");
    auto notesInput = Input(&notes, "Notes");

    auto timeInput = Input(&time, "Time");
    auto descriptionInput = Input(&description, "Description");
    auto locationInput = Input(&location, "Location");

    // Event page
    auto eventContainer = Container::Vertical({
                                                      timeInput,
                                                      locationInput,
                                                      descriptionInput,
                                              });

    auto eventPage = Renderer(eventContainer, [&] {
        return vbox(
                ftxui::text(title) | bold | border | center,
                hbox({ftxui::text("Time:") | bold, timeInput->Render()}),
                separatorEmpty(),
                hbox({ftxui::text("Location:") | bold, locationInput->Render()}),
                separatorEmpty(),
                hbox({ftxui::text("Description:") | bold, descriptionInput->Render()}) | flex
        );
    });

    // Contact page
    auto contactContainer = Container::Vertical({
                                                        nameInput,
                                                        surnameInput,
                                                        notesInput
                                                });

    auto contactPage = Renderer(contactContainer, [&] {
        return vbox(
                ftxui::text(title) | bold | border | center,
                hbox({ftxui::text("Name:") | bold, nameInput->Render()}),
                separatorEmpty(),
                hbox({ftxui::text("Surname:") | bold, surnameInput->Render()}),
                separatorEmpty(),
                hbox({ftxui::text("Notes:") | bold, notesInput->Render()}) | flex
        );
    });

    // Page when nothing picked
    auto nothingPage = Renderer([&] {
        return dbox(
                ftxui::text("Pick note to see it here") | center | bold
        );
    });

    auto tab_container = Container::Tab({
                                                notePage,
                                                contactPage,
                                                eventPage
                                        }, &tab_selected);
    // Right side of screen setting up
    auto rightSideContainer = Container::Vertical({
                                                          deleteButton,
                                                          saveButton,
                                                          tab_container
                                                  });

    auto rightSide = Renderer(rightSideContainer, [&] {
        return vbox(
                tab_container->Render() | flex,
                separator(),
                hbox(separatorEmpty(), deleteButton->Render(), separatorEmpty(), saveButton->Render())
        );
    });

    // Modal widnow
    auto dialogWindow = ModalComponent(deleteEntry, hide_modal);

    // Add new note page
    auto choosingTypeRadioButton = Radiobox(&typesVariants, &radioButtonSelected);
    auto continueButton = Button("Select ✓", [&] {
                                     newRightTabSelected = radioButtonSelected;
                                     rightSidePageSelect = 3;
                                 },
                                 ButtonOption::Animated(Color::Green));

    auto choosingTypeRadioContainer = Container::Vertical({choosingTypeRadioButton,
                                                           continueButton});
    auto choosingTypePage = Renderer(choosingTypeRadioContainer, [&] {
        return vbox(
                choosingTypeRadioButton->Render(),
                separatorEmpty(),
                continueButton->Render()
        ) | center | flex;
    });

    // New note page
    string newNoteTitle;
    string newConatactTitle;
    string newEventTitle;
    string newText, newName, newSurname, newNotes, newTime, newDescription, newLocation;

    auto newNoteTitleInput = Input(&newNoteTitle, "Title");
    auto newTextInput = Input(&newText, "Text");

    auto newContactTitleInput = Input(&newConatactTitle, "Title");
    auto newNameInput = Input(&newName, "Name");
    auto newSurnameInput = Input(&newSurname, "Surname");
    auto newNotesInput = Input(&newNotes, "Notes");

    auto newEventTitleInput = Input(&newEventTitle, "Title");
    auto newTimeInput = Input(&newTime, "Time");
    auto newDescriptionInput = Input(&newDescription, "Description");
    auto newLocationInput = Input(&newLocation, "Location");

    auto newNoteContainer = Container::Vertical({newNoteTitleInput, newTextInput});
    auto newContactContainer = Container::Vertical(
            {newContactTitleInput, newNameInput, newSurnameInput, newNotesInput});
    auto newEventContainer = Container::Vertical(
            {newEventTitleInput, newTimeInput, newLocationInput, newDescriptionInput});


    auto newNotePage = Renderer(newNoteContainer, [&] {
        return vbox(
                newNoteTitleInput->Render() | bold | border | center,
                hbox(ftxui::text("Text:") | bold, newTextInput->Render()) | flex
        ) | flex;
    });

    auto newContactPage = Renderer(newContactContainer, [&] {
        return vbox(
                newContactTitleInput->Render() | bold | border | center,
                hbox(ftxui::text("Name:") | bold, newNameInput->Render()),
                hbox(ftxui::text("Surname:") | bold, newSurnameInput->Render()),
                hbox(ftxui::text("Notes:") | bold, newNotesInput->Render()) | flex
        ) | flex;
    });

    auto newEventPage = Renderer(newEventContainer, [&] {
        return vbox(
                newEventTitleInput->Render() | bold | border | center,
                hbox(ftxui::text("Time:") | bold, newTimeInput->Render()),
                hbox(ftxui::text("Location:") | bold, newLocationInput->Render()),
                hbox(ftxui::text("Description:") | bold, newDescriptionInput->Render()) | flex
        ) | flex;
    });

    auto newRightSideTab = Container::Tab({newNotePage, newEventPage, newContactPage}, &newRightTabSelected);
    auto saveEntryButton = Container::Horizontal({Button("Save and continue", [&] {
        Entry addibleEntry;
        switch (radioButtonSelected) {
            case 0: { // Note
                addibleEntry = Note(newNoteTitle, newText);
                break;
            }
            case 1: { // Event
                addibleEntry = Accident(newEventTitle, newTime, newDescription, newLocation);
                break;
            }
            case 2: { // Contact
                addibleEntry = Contact(newConatactTitle, newName, newSurname, newNotes);
                break;
            }
        };

        diaryExample->addNewEntry(addibleEntry);
        noteChoosingVariants.push_back(addibleEntry.title);
        currentEntries.push_back(addibleEntry);

        rightSidePageSelect = 0;


    }, ButtonOption::Animated(Color::Green3))});

    auto newEntryPageContainer = Container::Vertical({newRightSideTab, saveEntryButton});

    auto newEntryPage = Renderer(newEntryPageContainer, [&] {
        return vbox(
                newRightSideTab->Render() | flex,
                separator(),
                saveEntryButton->Render()
        );
    });

    auto rightSideTab = Container::Tab({
                                               nothingPage,
                                               rightSide,
                                               choosingTypePage,
                                               newEntryPage
                                       }, &rightSidePageSelect);

    // Add right side and left side resizable
    notePage = ResizableSplitLeft(leftSide,
                                  rightSideTab,
                                  &leftSide_size) | border;



    // Setting up a modal window
    notePage |= Modal(dialogWindow, &modal_shown);

    // Main window
    auto mainWindow = Renderer(notePage,[&]{
        return vbox(
                ftxui::text("Termdiary v1.0.0") | hcenter | bold,
                notePage->Render() | flex
                );
    });

    screen.Loop(mainWindow);
}


int main(void) {

    Diary diary = Diary();
    std::vector<string> titlesVector;
    for (Entry item: diary.getEntries()) {
        titlesVector.push_back(item.title);
    }

    design(titlesVector, &diary);

}