#include "coreApplication.h"

void Application::start()
{
    // Welcomes the user
    printWelcomeMessage();

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

    std::map<int, std::tuple<std::string, std::string>> inputOptions;

    // Main loop, ending the loop stops the application
    while (getRunState())
    {
        // Prints the balance of the user
        printMessage("Saldo: " + std::to_string(balance) + " euroa.");

        if (getMenuState() == "hotelMain")
        {
            // Stores all the input options for modularity and better checking
            // Includes an ID (This is the one that user chooses), which then contains a tuple with the title and the action
            inputOptions = {
                {1, std::tuple("Varaa huone", "reserveRoom")},
                {2, std::tuple("Hallitse huoneita", "manageRooms")},
                {3, std::tuple("Kay toissa", "work")},
                {4, std::tuple("Lopeta", "quit")}
            };
        }

        else if (getMenuState() == "reserveRoom")
        {
            // Prints the available rooms
            printMessage(std::to_string(getFreeRoomCount()) + "/" + std::to_string(getRoomCount()) + " huonetta vapaana.");

            inputOptions = {
                {1, std::tuple("Varaa yhden henkilon huone", "reserveRoomSingle")},
                {2, std::tuple("Varaa kahden henkilon huone", "reserveRoomDouble")},
                {3, std::tuple("Palaa aulaan", "back")}
            };
        }

        else if (getMenuState() == "manageRooms")
        {
            inputOptions = {
                {1, std::tuple("Palaa aulaan", "back")}
            };
        }

        else if (getMenuState() == "work")
        {
            printMessage("Tee toita: " + std::to_string(getWorkNumber()) + " kertaa.");
            inputOptions = {
                {1, std::tuple("Tee Toita", "doWork")},
                {2, std::tuple("Lahde pois toista", "back")}
            };
        }

        // Get the user input and process it
        processUserInput(printAndGetUserInput(inputOptions));
    }
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
        if (roomCount > (int)roomCount/2)
        {
            roomSize = 2;
        }

        // 30% chance for the room to be reserved
        bool reserved { false };
        if (rand() % 10 >= 7)
        {
            reserved = true;
            reservedRooms += 1;
        }

        rooms[i] = new Room(reserved, roomSize, (i + 1));
    }

    freeRooms = roomCount - reservedRooms;
}

std::map<int, Room*> Application::getRooms(bool reserveStatus, int roomSize)
{
    std::map<int, Room*> collectedRooms;
    int roomCounter { 0 };

    for (auto room : rooms)
    {
        if (room.second->getRoomReserveStatus() == reserveStatus && room.second->getRoomSize() == roomSize)
        {
            collectedRooms[roomCounter] = room.second; 
        }
    }

    return collectedRooms;
}

// Stops the application
void Application::stop()
{
    runState = false;
}

// Gets the application status, whether the application is running or not
bool Application::getRunState()
{
    return runState;
}

// This function will be run once when the application is run to welcome the user
void Application::printWelcomeMessage()
{
    while (true)
    {
        std::string blankInput { " " };

        std::cout << "Tervetuloa hotelliin!" << std::endl;
        std::cout << "Voit aloittaa esimerkiksi varaamalla huoneen, tai jos sinulla on jo varaus, voit lunastaa huoneesi avaimen." << std::endl;

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

    // This lets you into your rooms
    else if (userInput == "manageRooms")
    {
        setMenuState("manageRooms");
    }

    // Makes you go to your workplace
    else if (userInput == "work")
    {
        setMenuState("work");
        setWorkNumber(rand() % 8 + 4);
    }

    // Does work at the workplace
    else if (userInput == "doWork")
    {

        // Checks if the work is done
        if (getWorkNumber() <= 1)
        {
            // Gets the paycheck, random between 40-100 euros
            int payCheck = rand() % 60 + 40;
            balance += payCheck;

            // Returns you back to the hotel and gives you the paycheck
            printMessage("Sait tyot tehtya ja palasit takaisin hotellille. Ansaitsit " + std::to_string(payCheck) + " euroa.");
            setMenuState("hotelMain");
        }

        // Decreases the work amount
        setWorkNumber(getWorkNumber() - 1);
    }

    else // Invalid input
    {
        printMessage("Anteeksi, tama ei ollut vaihtoehto.");
    }
}

// This function can be used to print messages for the user
// The messages are presented in a box on top of the console
void Application::printMessage(std::string message)
{
    // Prints the upper line
    std::cout << ".";
    for (int i = 0; i < message.length(); i++)
    {
        std::cout << "-";
    }
    std::cout << "." << std::endl;
    
    // Prints the message
    std::cout << "|" << message << "|" << std::endl;

    // Prints the bottom line
    std::cout << "'";
    for (int i = 0; i < message.length(); i++)
    {
        std::cout << "-";
    }
    std::cout << "'" << std::endl;
}

// Sets the user's room
void Application::setMenuState(std::string state)
{
    menuState = state;
}

// Gets the room the user is in
std::string Application::getMenuState()
{
    return menuState;
}

// Can be used to change the number used in work
void Application::setWorkNumber(int number)
{
    randomWorkNumber = number;
}

// Returns the work number
int Application::getWorkNumber()
{
    return randomWorkNumber;
}

// Gets the overall room count
int Application::getRoomCount()
{
    return roomCount;
}

// Gets the amount of reserved rooms
int Application::getReservedRoomCount()
{
    return reservedRooms;
}

// Gets the amount of free rooms
int Application::getFreeRoomCount()
{
    return freeRooms;
}