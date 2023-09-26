#include "coreApplication.h"

void Application::start()
{
    // Welcomes the user
    printWelcomeMessage();

    // Main loop, ending the loop stops the application
    while (getRunState())
    {
        // Gets the start user input
        int userStartInput = getStartUserInput();
        processStartUserInput(userStartInput);
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
    }
}

int Application::getStartUserInput()
{
    // Stores all the input options for modularity and better checking
    std::map<int, std::string> inputOptions = {
        {1, "Varaa huone"},
        {2, "Lunasta huoneen avain"},
        {3, "Mene huoneeseen"},
        {4, "Lopeta"}
    };

    std::cout << std::endl << "Valitse toiminto:" << std::endl;

    // Loops through the possible input options and presents them
    for (auto inputOption : inputOptions)
    {
        std::cout << inputOption.first << ": " << inputOption.second << std::endl;
    }

    // Gets the user input
    std::cout << "Choice: ";
    int inputValue;
    std::cin >> inputValue;

    // Check if the input is not found in the options or is not a number
    if (inputOptions.find(inputValue) == inputOptions.end() || std::cin.fail())
    {
        // Clears the input and ignores it
        std::cin.clear();
        std::cin.ignore();

        // 0 will make the application ask again
        return 0;
    }

    // Returns the user input for further inspection
    return inputValue;
}

void Application::processStartUserInput(int userInput)
{
    // Clears the screen
    system("cls");

    switch (userInput)
    {
        case 0:
            std::cout << "Anteeksi, tama ei ollut vaihtoehto." << std::endl;
            break;
        case 4:
            stop();
            break;

    }
}