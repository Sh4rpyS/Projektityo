#include "coreApplication.h"

void Application::start()
{
    // Welcomes the user
    printWelcomeMessage();

    // Creates a seed for the random numbers based on time
    srand(time(NULL));

    std::map<int, std::tuple<std::string, std::string>> inputOptions;

    // Main loop, ending the loop stops the application
    while (getRunState())
    {
        // Prints the balance of the user
        printMessage("Current balance: " + std::to_string(balance) + " euros.");

        if (getMenuState() == "hotelMain")
        {
            // Stores all the input options for modularity and better checking
            // Includes an ID (This is the one that user chooses), which then contains a tuple with the title and the action
            inputOptions = {
                {1, std::tuple("Varaa huone", "reserveRoom")},
                {2, std::tuple("Lunasta huoneen avain", "getKey")},
                {3, std::tuple("Mene huoneeseen", "enterRoom")},
                {4, std::tuple("Lopeta", "quit")}
            };
        }
        else if (getMenuState() == "hotelReserve")
        {
            inputOptions = {
                {1, std::tuple("Varaa huone", "reserveRoom")},
                {2, std::tuple("Palaa aulaan", "back")}
            };
        }
        else if (getMenuState() == "hotelKey")
        {
            inputOptions = {
                {1, std::tuple("Palaa aulaan", "back")}
            };
        }
        else if (getMenuState() == "room")
        {
            inputOptions = {
                {1, std::tuple("Kay toissa", "work")},
                {2, std::tuple("Maksa laskut", "payBills")},
                {3, std::tuple("Lopeta varaus ja palauta avain", "returnKey")},
                {4, std::tuple("Palaa aulaan", "back")}
            };
        }
        else if (getMenuState() == "work")
        {
            printMessage("Do work: " + std::to_string(getWorkNumber()) + " times.");
            inputOptions = {
                {1, std::tuple("Tee Toita", "doWork")},
                {2, std::tuple("Lahde pois toista", "back")}
            };
        }

        // Get the user input and process it
        processUserInput(printAndGetUserInput(inputOptions));
    }
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
        setMenuState("hotelReserve");
    }

    // You can receive the key for your room here
    else if (userInput == "getKey")
    {
        setMenuState("hotelKey");
    }

    // This lets you into your rooms
    else if (userInput == "enterRoom")
    {
        setMenuState("room");
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
            // Gets the paycheck, random between 90-150 euros
            int payCheck = rand() % 60 + 90;
            balance += payCheck;

            // Returns you back to the hotel and gives you the paycheck
            printMessage("Sait tyot tehtya ja palasit takaisin hotellille. Ansaitsit " + std::to_string(payCheck) + " euroa.");
            setMenuState("hotelMain");
        }

        // Decreases the work amount
        setWorkNumber(getWorkNumber() - 1);
    }

    // This pays the bills that comes for the hotelroom
    else if (userInput == "payBills")
    {

    }

    // This can be used for leaving the hotelroom, meaning you will lose the access to the room
    else if (userInput == "returnKey")
    {

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