#include "coreApplication.h"

void Application::start()
{
    // Welcomes the user
    printWelcomeMessage();

    // Main loop, ending the loop stops the application
    while (getRunState())
    {
        if (getMenuState() == "hotelMain")
        {
            std::map<int, std::tuple<std::string, std::string>> inputOptions = {
                {1, std::tuple("Varaa huone", "reserveRoom")},
                {2, std::tuple("Lunasta huoneen avain", "getKey")},
                {3, std::tuple("Mene huoneeseen", "enterRoom")},
                {4, std::tuple("Poistu ja mene toihin", "work")},
                {5, std::tuple("Lopeta", "quit")}
            };
            // Get the user input and process it
            processUserInput(printAndGetUserInput(inputOptions));
        }
        else if (getMenuState() == "hotelReserve")
        {
            
        }
        else if (getMenuState() == "hotelKey")
        {
            
        }
        else if (getMenuState() == "room")
        {
            
        }
        else if (getMenuState() == "work")
        {
            
        }
    }
}

void Application::stop()
{
    runState = false;
}

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

std::string Application::printAndGetUserInput(std::map<int, std::tuple<std::string, std::string>> inputOptions)
{
    // Stores all the input options for modularity and better checking
    // Includes an ID (This is the one that user chooses), which then contains a tuple with the title and the action

    /*
    std::map<int, std::tuple<std::string, std::string>> inputOptions = {
        {1, std::tuple("Varaa huone", "reserveRoom")},
        {2, std::tuple("Lunasta huoneen avain", "getKey")},
        {3, std::tuple("Mene huoneeseen", "enterRoom")},
        {4, std::tuple("Poistu ja mene toihin", "work")},
        {5, std::tuple("Lopeta", "quit")}
    };
    */

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
    else if (userInput == "reserveRoom")
    {
        setMenuState("hotelReserve");
    }
    else if (userInput == "getKey")
    {
        setMenuState("hotelKey");
    }
    else if (userInput == "enterRoom")
    {
        setMenuState("room");
    }
    else if (userInput == "work")
    {
        setMenuState("work");
    }
    else // Invalid input
    {
        printMessage("Anteeksi, tama ei ollut vaihtoehto.");
    }
}

void Application::printMessage(std::string message)
{
    std::cout << ".";
    for (int i = 0; i < message.length(); i++)
    {
        std::cout << "-";
    }
    std::cout << "." << std::endl;
    
    std::cout << "|" << message << "|" << std::endl;

    std::cout << "'";
    for (int i = 0; i < message.length(); i++)
    {
        std::cout << "-";
    }
    std::cout << "'" << std::endl;
}

void Application::setMenuState(std::string state)
{
    menuState = state;
}

std::string Application::getMenuState()
{
    return menuState;
}