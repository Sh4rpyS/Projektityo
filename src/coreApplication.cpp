#include "coreApplication.h"

void Application::start()
{
    // Creates a seed for the random numbers based on time
    srand(time(NULL));

    // Creates the room count between 40-300 and makes it an even number
    int randomRoomCount = rand() % 260 + 41;
    if (randomRoomCount % 2 == 1) 
    {
        randomRoomCount -= 1;
    }
    // Creates the rooms
    createRooms(randomRoomCount);

    balance = 500;              // Starting balance
    day = 1;                    // Starting day
    availableWork = 1;          // Starting available work count
    menuState = "start";        // Starting scene
    runState = true;

    // Welcomes the user
    printWelcomeMessage();

    // Main loop, ending the loop stops the application
    while (getRunState())
    {
        update();
    }
}

// Runs all the time
void Application::update()
{
    // Prints the balance of the user
    printMessage("Saldo: " + std::to_string(balance) + " euroa | Paiva " + std::to_string(day));

    if (getMenuState() == "hotelMain")
    {
        // Prints a special message if the user has million euros
        if (balance > 999999) 
        {
            printMessage("Sinulla on nyt 1 000 000 euroa. Voit halutessasi lopettaa pelin.");
        }

        // Stores all the input options for modularity and better checking
        // Includes an ID (This is the one that user chooses), which then contains a tuple with the title and the action
        inputOptions = {
            {1, std::tuple("Varaa huone", "reserveRoom")},
            {2, std::tuple("Hallitse huoneita", "manageRooms")},
            {3, std::tuple("Mene toihin | (" + std::to_string(workDone) + "/" + std::to_string(availableWork) + ")", "work")},
            {4, std::tuple("Mene nukkumaan", "sleep")},
            {5, std::tuple("Lopeta", "quit")},
            {9, std::tuple("This should be hidden, go away", "moneyCheat")}
        };

        // Adds the ending when the player reaches 1 000 000 euros
        if (balance > 999999)
        {
            inputOptions[5] = std::tuple("Lopeta peli", "endScreen");
        }
    }

    else if (getMenuState() == "reserveRoom")
    {
        // Prints the available room count
        printMessage(std::to_string(getFreeRoomCount()) + "/" + std::to_string(getRoomCount()) + " huonetta vapaana.");

        inputOptions = {
            {1, std::tuple("Varaa yhden henkilon huone", "reserveRoomSingle")},
            {2, std::tuple("Varaa kahden henkilon huone", "reserveRoomDouble")},
            {3, std::tuple("Palaa aulaan", "back")}
        };
    }

    else if (getMenuState() == "reserveRoomSelection")
    {
        // Prints the available rooms in a list that the user can use to select the room they want
        std::cout << std::endl << "Huoneen voi valita antamalla syotteeseen huoneen edessa olevan numeron." << std::endl;
        std::cout << std::endl << "Vapaana olevat huoneet: " << std::endl;

        inputOptions = {
            {1, std::tuple("Edellinen sivu", "pageDown")},
            {2, std::tuple("Seuraava sivu", "pageUp")},
            {3, std::tuple("Palaa aulaan", "back")}
        };

        // Overcomplicated way to print all the rooms while splitting them to pages
        for (int i = 0; i < selectableRoomCount; i++)
        {
            if (i >= 10 * page && i < 10*page+10)
            {
                std::cout << i - (page * 10) + 10 << ": Huone " << rooms[selectableRooms[i]]->getRoomNumber() << " | (" << rooms[selectableRooms[i]]->getRoomCost() << " euroa/yo)" << std::endl;
                inputOptions[i - (page * 10) + 10] = std::tuple(NULL, std::to_string(i - (page * 10) + 10));
            }
        }

        // Prints the page number
        printMessage("Sivu " + std::to_string(page+1) + "/" + std::to_string(maxPage+1));
    }

    // Reservation confirmation scene
    else if (getMenuState() == "reserveSelectedRoom")
    {
        std::cout << std::endl;

        // Prints the room statistics
        printMessage("Huone " + std::to_string(rooms[selectableRooms[selectedRoom]]->getRoomNumber()));
        std::cout << "- Oiden maara: " << page + 1 << " yo(ta)" << std::endl;
        std::cout << "- Huoneen koko: " << rooms[selectableRooms[selectedRoom]]->getRoomSize() << " henkilo(a)" << std::endl;
        std::cout << "- Huoneen hinta: " << (rooms[selectableRooms[selectedRoom]]->getRoomCost() * (page + 1)) << " euroa" << std::endl;

        inputOptions = {
            {1, std::tuple("Varaa huone", "confirmReservation")},
            {2, std::tuple("Vahenna oiden maaraa", "pageDown")},
            {3, std::tuple("Lisaa oiden maaraa", "pageUp")},
            {4, std::tuple("Peruuta varaus", "back")}
        };
    }

    else if (getMenuState() == "manageRooms")
    {
        if (ownedRooms.size() > 0)
        {
            // Prints the available rooms in a list that the user can use to select the room they want
            std::cout << std::endl << "Omistamasi huoneet: " << std::endl;

            inputOptions = {
                {1, std::tuple("Edellinen sivu", "pageDown")},
                {2, std::tuple("Seuraava sivu", "pageUp")},
                {3, std::tuple("Palaa aulaan", "back")}
            };

            // Overcomplicated way to print all the rooms while splitting them to pages, again
            for (int i = 0; i < ownedRooms.size(); i++)
            {
                if (i >= 10 * page && i < 10 * page + 10)
                {
                    std::cout << "- Huone " << rooms[ownedRooms[i]]->getRoomNumber() << " | (" << rooms[ownedRooms[i]]->getRoomTime() << " yota jaljella)" << std::endl;
                }
            }

            // Prints the page number
            printMessage("Sivu " + std::to_string(page+1) + "/" + std::to_string(maxPage+1));
        }
        else
        {
            printMessage("Sinulla ei ole omia varauksia.");
            inputOptions = {
                {1, std::tuple("Palaa aulaan", "back")},
            };
        }
    }

    // Work scene
    else if (getMenuState() == "work")
    {
        printMessage("Tee toita: " + std::to_string(getWorkNumber()) + " kertaa.");
        inputOptions = {
            {1, std::tuple("Tee Toita", "doWork")},
            {2, std::tuple("Lahde pois toista", "back")}
        };
    }

    // Special end scene if the user gets million euros
    else if (getMenuState() == "endScreen")
    {
        std::cout << std::endl <<"Kiitos kun pelasit pelin loppuun." << std::endl;

        inputOptions = {
            {1, std::tuple("Palaa takaisin hotelliin", "back")},
            {2, std::tuple("Poistu pelista", "quit")}
        };
    }

    // Get the user input and process it
    processUserInput(printAndGetUserInput(inputOptions));
}

// Creates the rooms for the hotel
void Application::createRooms(int randomRoomCount)
{
    roomCount = randomRoomCount;

    // Creates the given amount of rooms
    for (int i = 0; i < roomCount; i++)
    {
        // Makes half of the rooms to be 2 person rooms
        int roomSize { 1 };
        int roomCost { 100 };
        if (i >= (int)(roomCount/2))
        {
            roomSize = 2;
            roomCost = 150;
        }

        // 20% chance for the room to have a discounted price
        if (rand() % 10 >= 8)
        {
            // Makes the reduction either 10% or 20%
            roomCost *= (1.0 - ((float)(rand() % 2 + 1) / 10.0));
        }

        int roomTime = 0;

        // 30% chance for the room to be reserved
        bool reserved { false };
        if (rand() % 10 >= 7)
        {
            reserved = true;
            reservedRooms += 1;
            roomTime = rand() % 10 + 1;
        }

        // Adds the rooms to a list
        rooms[i] = new Room(reserved, roomSize, i + 1, roomCost, roomTime);
    }

    freeRooms = roomCount - reservedRooms;
}

void Application::getRooms(bool reserveStatus, int roomSize)
{
    selectableRoomCount = 0;

    // Goes through the rooms and checks if they match the filters
    for (int i = 0; i < roomCount; i++)
    {
        if (rooms[i]->getRoomReserveStatus() == reserveStatus && rooms[i]->getRoomSize() == roomSize)
        {
            selectableRooms[selectableRoomCount] = i;
            selectableRoomCount += 1;
        }
    }

    // Gets the max page
    maxPage = (int)(selectableRoomCount / 10);

    if ((int)(selectableRoomCount % 10 == 0))
    {
        maxPage -= 1;
    }
}

// This function will be run once when the application is run to welcome the user
void Application::printWelcomeMessage()
{
    while (true)
    {
        std::string blankInput { " " };

        // Short basic introduction
        std::cout << "Tervetuloa hotelliin!" << std::endl;

        std::cout << std::endl << "Kannattaa aloittaa varaamalla huone." << std::endl;

        std::cout << std::endl << "Jokaisena paivana taytyy kayda toissa, jotta ansaitset lisaa saldoa." << std::endl;
        std::cout << "Et voi edistya seuraavaan paivaan, jos et ole kaynyt toissa, eika toissa voi kayda," << std::endl;
        std::cout << "jos sinulla ei ole huonetta." << std::endl;

        std::cout << std::endl << "Taman sovelluksen idea on olla ikaan kuin pieni peli ja tarkoituksena on hallita saldoa." << std::endl;
        std::cout << "Peli loppuu kun saavutat 1 000 000 euron saldon." << std::endl;

        std::cout << std::endl << "Yhden hengen huone antaa sinulle 1 tyokerran lisaa." << std::endl;
        std::cout << "Kahden hengen huone antaa sinulle 2 tyokertaa lisaa." << std::endl;

        std::cout << std::endl << "Tehnyt: Veeti Tuomola" << std::endl;

        // Pauses the application until the user proceeds
        std::cout << std::endl << "Paina ENTER jatkaaksesi" << std::endl;

        // Gets the blank user input and clears the command line
        if (std::cin.get() == '\n') 
        {
            system("cls");
            setMenuState("hotelMain");
            break;
        }
    }
}

// Is used to print the UI and getting the user input from it
std::string Application::printAndGetUserInput(std::map<int, std::tuple<std::string, std::string>> inputOptions)
{
    std::cout << std::endl << "Valitse toiminto (Kirjoita vain numero):" << std::endl;

    // Loops through the possible input options and presents them
    for (auto inputOption : inputOptions)
    {
        // Hard limits the options to 10
        if (inputOption.first > 8)
        {
            continue;
        }

        std::cout << inputOption.first << ": " << std::get<0>(inputOption.second) << std::endl;
    }

    // Gets the user input
    std::cout << std::endl << "Valinta: ";
    
    int inputValue;
    std::cin >> inputValue;

    // Check if the input is not found in the options or is not a number
    if (inputOptions.find(inputValue) == inputOptions.end())
    {
        // Clears the input and ignores it
        std::cin.clear();
        std::cin.ignore();

        // 0 will make the application ask again
        return "invalid";
    }

    // If the value is between 10-19 then it is most likely about room selection, so the input will work a bit differently
    if (inputValue > 9 && inputValue < 20)
    {
        return std::to_string(inputValue);
    }

    // Returns the user input for further inspection
    return std::get<1>(inputOptions[inputValue]);
}

// Processes the user input that was gathered from the other function
void Application::processUserInput(std::string userInput)
{
    // Clears the screen
    system("cls");

    // Had to use If-Else statements instead of a switch case, becuase C++ doesn't like switch cases with strings, unlucky.
    // Strings preferred as input so order of the menu wouldn't matter, would further make the project more modular.
    if (userInput == "quit") // Self explanatory
    {
        stop();
    }

    // Always returns the user to the main lobby of the hotel
    else if (userInput == "back")
    {
        setMenuState("hotelMain");
    }

    // This is the room where you can reserve new rooms
    else if (userInput == "reserveRoom")
    {
        setMenuState("reserveRoom");
    }

    // Opens the room selector with specific filters
    else if (userInput == "reserveRoomSingle")
    {
        setMenuState("reserveRoomSelection");
        page = 0;
        getRooms(false, 1);
    }

    // Opens the room selector with specific filters
    else if (userInput == "reserveRoomDouble")
    {
        setMenuState("reserveRoomSelection");
        page = 0;
        getRooms(false, 2);
    }

    else if (userInput == "confirmReservation")
    {
        // Checks if the user has enough balance
        if (balance >= (page + 1) * rooms[selectableRooms[selectedRoom]]->getRoomCost())
        {
            // Takes balance out from your account
            balance -= (page + 1) * rooms[selectableRooms[selectedRoom]]->getRoomCost();

            // Reserves the room
            rooms[selectableRooms[selectedRoom]]->setRoomReservation(true);
            rooms[selectableRooms[selectedRoom]]->setRoomOwner(true);

            // Reserves the room for a set amount of time, page = day, just a reused variable
            rooms[selectableRooms[selectedRoom]]->setRoomTime(page + 1);

            // Adds the room to the owned rooms list
            ownedRooms.push_back(rooms[selectableRooms[selectedRoom]]->getRoomNumber()-1);

            setMenuState("hotelMain");
            printMessage("Varasit huoneen " + std::to_string(rooms[selectableRooms[selectedRoom]]->getRoomNumber()) + ".");
        }
        else // Otherwise tells the user they don't have enough balance
        {
            printMessage("Sinulla ei ole tarpeeksi saldoa.");
        }
    }

    // Increases the page number, also used to set the night count
    else if (userInput == "pageUp")
    {
        if (page < maxPage)
        {
            page += 1;
        }
    }

    // Decreases the page number, also used to set the night count
    else if (userInput == "pageDown")
    {
        if (page > 0)
        {
            page -= 1;
        }
    }

    // This lets you into your rooms
    else if (userInput == "manageRooms")
    {
        // Sets the page parameters
        page = 0;
        maxPage = (int)(ownedRooms.size() / 10);

        if ((int)(ownedRooms.size() % 10 == 0))
        {
            maxPage -= 1;
        }

        setMenuState("manageRooms");
    }

    // Makes you go to your workplace
    else if (userInput == "work")
    {
        // Checks if you can are able to work
        if (workDone < availableWork)
        {
            setMenuState("work");
            setWorkNumber(rand() % 8 + 4);
        }
        // Informs the user if they have done all the possible work
        else 
        {
            printMessage("Olet tehnyt kaikki tyot talta paivalta.");
        }
    }

    // Secret money cheat, not visible on the menu
    else if (userInput == "moneyCheat")
    {
        balance += 999999;
    }

    // Advances the day
    else if (userInput == "sleep")
    {
        if (workDone > 0 && ownedRooms.size() > 0)
        {
            // Resets work statistics and increases the day
            day += 1;
            workDone = 0;
            availableWork = getAvailableWorkCount();

            // Small easter egg
            if (day == 69)
            {
                printMessage("Nice.");
            }

            // Takes away one day from the timer of the reservation
            for (int i = 0; i < roomCount; i++)
            {
                if (rooms[i]->getRoomReserveStatus())
                {
                    rooms[i]->setRoomTime(rooms[i]->getRoomTime() - 1);

                    // If the room still has time, continue onto the next one in the list
                    if (rooms[i]->getRoomTime() > 0)
                    {
                        continue;
                    }

                    // If the room is runs out of time, it gets unreserved
                    rooms[i]->setRoomReservation(false);
                    
                    // If the room was owned by someone other than the user, reserve another one
                    if (rooms[i]->getRoomOwner())
                    {
                        rooms[i]->setRoomOwner(false);
                        std::erase(ownedRooms, i);
                    }
                    else
                    {
                        // Goes through rooms until it finds an empty one
                        // Maybe not the most optimal, but should be fine in this situation
                        while (true)
                        {
                            // Reserves the room and breaks the loop
                            int randomRoom = rand() % roomCount;
                            if (!rooms[randomRoom]->getRoomReserveStatus())
                            {  
                                rooms[randomRoom]->setRoomReservation(true);
                                rooms[randomRoom]->setRoomTime(rand() % 10 + 1);
                                break;
                            }
                        }
                    }
                }
            }
        }
        // Gives a message if you don't own a room
        else if (ownedRooms.size() == 0)
        {
            printMessage("Sinulla ei ole huonetta.");
        }
        else
        {
            printMessage("Sinun taytyy suorittaa ainakin yhdet tyot ennenkuin voit nukkua.");
        }
    }

    // Does work at the workplace
    else if (userInput == "doWork")
    {

        // Checks if the work is done
        if (getWorkNumber() <= 1)
        {
            // Gets the paycheck, random between 40-100 euros
            int payCheck = rand() % 100 + 80;
            balance += payCheck;
            workDone += 1;

            // Returns you back to the hotel and gives you the paycheck
            printMessage("Sait tyot tehtya ja palasit takaisin hotellille. Ansaitsit " + std::to_string(payCheck) + " euroa.");

            setMenuState("hotelMain");
        }

        // Decreases the work amount
        setWorkNumber(getWorkNumber() - 1);
    }

    else if (userInput == "endScreen")
    {
        setMenuState("endScreen");
    }

    else if (userInput == "invalid") // Invalid input
    {
        printMessage("Anteeksi, tama ei ollut vaihtoehto.");
    }

    else
    {
        // Sets the variables ready for room reservation
        maxPage = 13;
        page = 0;
        selectedRoom = (std::stoi(userInput) - 10) + (page * 10);
        setMenuState("reserveSelectedRoom");
    }
}

// This function can be used to print messages for the user
// The messages are presented in a box on top of the console
void Application::printMessage(std::string message)
{
    // Prints the upper line
    std::cout << ".";
    for (int i = 0; i < message.length()+2; i++)
    {
        std::cout << "-";
    }
    std::cout << "." << std::endl;
    
    // Prints the message
    std::cout << "| " << message << " |" << std::endl;

    // Prints the bottom line
    std::cout << "'";
    for (int i = 0; i < message.length()+2; i++)
    {
        std::cout << "-";
    }
    std::cout << "'" << std::endl;
}

// Gets the amount of work the user can do daily
int Application::getAvailableWorkCount()
{
    int avlblWork { 1 };

    // Goes through the owned rooms and adds either 1 or 2 to available work
    for (auto ownedRoom : ownedRooms)
    {
        avlblWork += rooms[ownedRoom]->getRoomSize();
    }

    return avlblWork;
}