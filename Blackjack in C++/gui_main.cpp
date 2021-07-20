#ifndef UNICODE
#define UNICODE
#endif 
#include <iostream>
#include <windows.h>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h> 
#include "player.h"
#include "deck.h"
#define MAX_STRING_SIZE 64

#define hitButton 1
#define standButton 2
#define doubleButton 3
#define changeBetButton 4

//Create custom font
static HFONT s_hFont = NULL;

std::wstring converter(bool type, int num);

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

//Return true if a button has been pressed, otherwise false
int ifPressed (bool isPressed[4]);
void clearInput(bool isPressed[4]);
//Identifier for if button has been pressed
bool isPressed[4] = {
    false,      //hit button
    false,      //stand button
    false,      //double button
    false       //change bet button
};

int WINAPI WinMain(HINSTANCE currentInstance, HINSTANCE previousInstance, PSTR cmdLine, INT cmdCount)
{
    /* --------------------------------------------------------------------  */
    /* First, initalize all windows needed to run the program. This include:
        - Main window
        - Hit button window
        - Stand button window
        - Double button window
        - Change bet button window
        - Player balance text window
        - Player name text window
        - Player hand value text window
        - Player cards windows
        - Dealer hand value text window
        - Dealer cards windows 
    /* --------------------------------------------------------------------  */

    // Register the window class.
    const wchar_t CLASS_NAME[]  = L"Sample Window Class";
    
    WNDCLASS wc = { };

    wc.lpfnWndProc   = WindowProc;
    wc.hInstance     = currentInstance;
    wc.lpszClassName = CLASS_NAME;

    RegisterClass(&wc);

    // Create the window.

    HWND hwndMain = CreateWindowEx(
        0,                              // Optional window styles.
        CLASS_NAME,                     // Window class
        L"Learn to Program Windows",    // Window text
        WS_OVERLAPPEDWINDOW,            // Window style

        // Size and position
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,

        NULL,       // Parent window    
        NULL,       // Menu
        currentInstance,  // Instance handle
        NULL        // Additional application data
        );

    if (hwndMain == NULL)
    {
        return 0;
    }

    
    HWND hwndNameWindow = CreateWindow( 
    L"BORDER",  // Predefined class; Unicode assumed 
    L"Name: ",      // Button text 
    WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
    10,         // x position 
    10,         // y position 
    100,        // Button width
    100,        // Button height
    hwndMain,     // Parent window
    (HMENU)hitButton,       // No menu.
    (HINSTANCE)GetWindowLongPtr(hwndMain, GWLP_HINSTANCE), 
    NULL);      // Pointer not needed.


    HWND hwndHitButton = CreateWindow( 
    L"BUTTON",  // Predefined class; Unicode assumed 
    L"Hit/Play",      // Button text 
    WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
    250,         // x position 
    500,         // y position 
    100,        // Button width
    100,        // Button height
    hwndMain,     // Parent window
    (HMENU)hitButton,       // No menu.
    (HINSTANCE)GetWindowLongPtr(hwndMain, GWLP_HINSTANCE), 
    NULL);      // Pointer not needed.

    HWND hwndDoubleButton = CreateWindow( 
    L"BUTTON",  // Predefined class; Unicode assumed 
    L"Double",      // Button text 
    WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
    550,         // x position 
    500,         // y position 
    100,        // Button width
    100,        // Button height
    hwndMain,     // Parent window
    (HMENU)doubleButton,       // No menu.
    (HINSTANCE)GetWindowLongPtr(hwndMain, GWLP_HINSTANCE), 
    NULL);      // Pointer not needed.

    HWND hwndStandButton = CreateWindow( 
    L"BUTTON",  // Predefined class; Unicode assumed 
    L"Stand",      // Button text 
    WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
    400,         // x position 
    500,         // y position 
    100,        // Button width
    100,        // Button height
    hwndMain,     // Parent window
    (HMENU)standButton,       // No menu.
    (HINSTANCE)GetWindowLongPtr(hwndMain, GWLP_HINSTANCE), 
    NULL);      // Pointer not needed.

    HWND hwndChangeBetButton = CreateWindow( 
    L"BUTTON",  // Predefined class; Unicode assumed 
    L"Change Bet",      // Button text 
    WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,  // Styles 
    700,         // x position 
    500,         // y position 
    100,        // Button width
    100,        // Button height
    hwndMain,     // Parent window
    (HMENU)changeBetButton,       // No menu.
    (HINSTANCE)GetWindowLongPtr(hwndMain, GWLP_HINSTANCE), 
    NULL);      // Pointer not needed.

    


    HWND displayBalanceWindow = CreateWindow(
    L"STATIC",
    L"Balance: ",
     WS_TABSTOP | WS_VISIBLE | WS_CHILD,
    50,
    150,
    150,
    30,
    hwndMain,
    NULL,
    (HINSTANCE)GetWindowLongPtr(hwndMain, GWLP_HINSTANCE),
    NULL);

    HWND displayNameWindow = CreateWindow(
    L"STATIC",
    L"Name: ",
     WS_TABSTOP | WS_VISIBLE | WS_CHILD,
    50,
    100,
    150,
    30,
    hwndMain,
    NULL,
    (HINSTANCE)GetWindowLongPtr(hwndMain, GWLP_HINSTANCE),
    NULL);

    
    HWND displayBetWindow = CreateWindow(
    L"STATIC",
    L"Bet: ",
     WS_TABSTOP | WS_VISIBLE | WS_CHILD,
    50,
    200,
    150,
    30,
    hwndMain,
    NULL,
    (HINSTANCE)GetWindowLongPtr(hwndMain, GWLP_HINSTANCE),
    NULL);


    HWND displayTextWindow = CreateWindow(
    L"STATIC",
    L"Blackjack Casino",
     WS_TABSTOP | WS_VISIBLE | WS_CHILD,
    300,
    250,
    300,
    60,
    hwndMain,
    NULL,
    (HINSTANCE)GetWindowLongPtr(hwndMain, GWLP_HINSTANCE),
    NULL);

    //Arr of all window classes
    HWND windowList[] = {
        hwndMain,
        hwndNameWindow,
        hwndHitButton,
        hwndDoubleButton,
        hwndStandButton,
        hwndChangeBetButton
    };

    //Identifier to button that has been pressed
    int pressed = 1;

    /* --------------------------------------------------------------------  */
    /* All windows have been initalize. Begin with logic for blackjack game. */
    /* --------------------------------------------------------------------  */


    /* Recieve all player input from terminal stream */
    std::cout << "What is your name?: \n";
    std::string name;
    std::cin >> name;
    std::string displayname = "Name: " + name;
    std::wstring displaynametemp = std::wstring(displayname.begin(), displayname.end());
    SetWindowText(displayNameWindow, displaynametemp.c_str());
    std::cout << "How much money would you like to start with?\n";
    int balance;
    std::cin >> balance;
    SetWindowText(displayBalanceWindow, converter(true, balance).c_str());
    std::cout << "What will be your current bet?\n";
    int bet;
    std::cin >> bet;
    SetWindowText(displayBetWindow, converter(false, bet).c_str());

    /*Initalize player, dealer, and deck classes */
    Player *p = new Player(name, balance);
    Player *dl = new Player();
    Deck *d = new Deck();
    d->shuffle();

    /* Display the window after the user has entered the game */
    ShowWindow(hwndMain, cmdCount);
    /*Welcome message to the user through the terminal.
    Note: this will later be changed to window messages. 
    Will establish independent window that will change text,
    based on the events in the game. This window will also 
    display the invitation to the game. */
    //SetWindowText(displayTextWindow, TEXT("/////WELCOME TO BLACKJACK CASINO//////"));
    SetWindowText(displayTextWindow, L"WELCOME TO BLACKJACK CASINO");
    std::cout << "/////WELCOME TO BLACKJACK CASINO//////\n";
    delay(2);

    /* --------------------------------------------------------------------  */
    /*          This is the main game loop. Only exits on game stop.         */
    /* --------------------------------------------------------------------  */

     while (p->getBalance() > 0) {

        std::cout << "Would you like to change the bet?" << std::endl;
        std::cout << "If not proceed by clicking play!" << std::endl;

        clearInput(isPressed);
        MSG msg = { };
        while (GetMessage(&msg, NULL, 0, 0))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
            pressed = ifPressed(isPressed);
            /* Depending on what button the user has clicked, the game continues:

                -Hit/Play: If the user has clicked on the hit/play button, they
                will leave the message loop and continue on with the game
                
                -Change Bet: IF the user clicks on the change bet button they 
                are prompted what they would like to change the bet size to
                in the console. Once they change the bet, they are informed
                of their decision, then must click the play button again.

                -Stand or Double: Since stand/double is not a valid option 
                in this situation the user is informed of this invalid decision 
                through the console and will be stuck in this loop until 
                hit/play is clicked

            */
            switch (pressed) {
                case 0:
                    std::cout << "The user has decided starts the game" << std::endl;
                    isPressed[0] = false;
                    break;
                case 3:
                    std::cout << "The user has decided to change the bet size" << std::endl;
                    delay(2);
                    std::cout << "What do you want to change your bet to?" << std::endl;
                    std::cin >> bet;
                    delay(2);
                    SetWindowText(displayBetWindow, converter(true, bet).c_str());
                    std::cout << "The user has changed the bet to " << bet << std::endl;
                    std::cout << "Please click play when you are ready to play!" << std::endl;
                    isPressed[3] = false;
                    break;
                default : 
                    if (pressed != -1) {
                        std::cout << "Please choose a valid option" << std::endl;
                        isPressed[1] = false;
                        isPressed[2] = false;
                    }
                    break;
            }
            if (pressed == 0) {
                break;
            }
        }


        //The game will commence with the dealer being given his two cards
        // and the dealer recieving his one.
        std::cout << "Let the game begin\n";
        delay(1);
        std::cout << bet << " dollars have been taken from your account\n";
        delay(1);
        p->setBalance(p->getBalance() - bet);
        SetWindowText(displayBalanceWindow, converter(true, p->getBalance()).c_str());
        std::cout << "New Balance: " << p->getBalance() << std::endl;
        //Give player first and second card and take card out of the deck
        p->hit(d);
        delay(2);
        p->hit(d);
        delay(2);
        //Give dealer his first card
        dl->hit(d);
        delay(2);
        dl->hiddenhit(d);

        bool pbust = false;
        bool dbust = false;
        bool playon = true;
        /* -------------------------------------------------------------------------------  */
        /* Time for user to make his decision on his turn on whether to hit, stand, double  */
        /* -------------------------------------------------------------------------------  */
        
        //If the user hits blackjack, skip steps where the user hits
        if (p->checkBlackjack()) {
        } else {
            std::cout << "What would you like to do?\n";
            std::cout << "H: Hit, S: Stand: D: Double\n";
            clearInput(isPressed);
            while (GetMessage(&msg, NULL, 0, 0))
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
                pressed = ifPressed(isPressed);
                switch(pressed) {
                    case 0: 
                        isPressed[0] = false;
                        break;
                    case 1: 
                        isPressed[1] = false;
                        break;
                    case 2: 
                        isPressed[2] = false;
                        break;
                    default :
                        if (pressed != -1) {
                            std::cout << "Please choose a valid option" << std::endl;
                            isPressed[3] = false;
                        }
                        break;
                }
                if (pressed == 0 || pressed == 1 || pressed == 2) {
                    break;
                }
            }
            if (pressed == 0 || pressed == 2) {
                //If the user doubles display this message
                if (pressed == 2) {
                    printf("User has doubled!\n");
                    delay(2);
                    p->setBalance(p->getBalance() - 2*bet);
                    SetWindowText(displayBalanceWindow, converter(true, p->getBalance()).c_str());
                    std::cout << bet << " dollars have been taken from your account" << std::endl;
                    std::cout << "New Balance: " << p->getBalance() << std::endl;
                    delay(2);
                    p->hit(d);
                    p->adjustAce();
                    delay(2);
                    if (p->getHandValue() > 21) {
                        std::cout << "User has bust with " << p->getHandValue() << std::endl;
                        delay(2);
                        pbust = true;
                    } else if (p->checkBlackjack()) {
                        delay(1);
                    }
                //If the user hits display this message
                } else {
                    std::cout << "User has hit!\n";
                    delay(2);
                    p->setBalance(p->getBalance() - bet);
                    SetWindowText(displayBalanceWindow, converter(true, p->getBalance()).c_str());
                    std::cout << bet << " dollars have been taken from your account" << std::endl;
                    std::cout << "New Balance: " << p->getBalance() << std::endl;
                    //Loop for the user to play on
                    while (playon) {
                        p->hit(d);
                        p->adjustAce();
                        delay(2);
                        //If User busts then exit loop and check dealers hand
                        if (p->getHandValue() > 21) {
                            std::cout << "User has bust with " << p->getHandValue() << std::endl;
                            delay(2);
                            pbust = true;
                            break;
                        //If the user gets blackjack exit loop and check dealers hand
                        } else if (p->checkBlackjack()) {
                            delay(2);
                            playon = false;
                        }
                        //Ask the user if he wants to hit again or stand
                        std::cout << "What would you like to do?\n";
                        std::cout << "H: Hit, S: Stand\n";
                        clearInput(isPressed);
                        while (GetMessage(&msg, NULL, 0, 0))
                        {
                            TranslateMessage(&msg);
                            DispatchMessage(&msg);
                            pressed = ifPressed(isPressed);
                            switch (pressed) {
                                case 0: 
                                    isPressed[0] = false;
                                    break;
                                case 1:
                                    isPressed[1] = false;
                                    break;
                                default :
                                    if (pressed != -1) {
                                        isPressed[2] = false;
                                        isPressed[3] = false;
                                        std::cout << "Please choose a valid option" << std::endl;
                                    } 
                                    break;   
                            }
                            if (pressed == 0 || pressed == 1) {
                                break;
                            }
                        }

                        //If user decides to hit again repeat this loop
                        if (pressed = 0) {
                            std::cout << "User hits\n";
                        //If user decides to stand exit loop and check dealers hand
                        } else {
                            std::cout << "User has stood\n";
                            playon = false;
                        }
                    }
                }
            //If the user stands, do nothing and check the dealers hand
            } else {
                std::cout << "User has stood\n";
                delay(2);
            }
        }
        //User has completed his move, let the dealer get his cards
        //If user has bust, do not check dealers hand and reset deck
        if (pbust == false) {
            std::cout << "Dealer will stand until 17\n";
            delay(2);
            std::cout << "Dealer reveals his hidden card\n";
            delay(2);
            dl->revealHidden();
            //Dealer keeps drawing cards until he busts or get >= 17
            while (dl->getHandValue() < 17 && !dbust) {
                dl->hit(d);
                dl->adjustAce();
                delay(2);
                //If the dealer busts exit the loop
                if (dl->getHandValue() > 21) {
                    std::cout << "Dealer has bust!, the user wins!\n";
                    delay(2);
                    //Credit the users account
                    p->setBalance(p->getBalance() + 2*bet);
                    SetWindowText(displayBalanceWindow, converter(true, p->getBalance()).c_str());
                    std::cout << "The user has been creditted " << 2*bet << std::endl;
                    delay(2);
                    dbust = true;
                }
            }
        }
        //If neither the dealer or the player has busts, compare their two hands and decide a winner
        if (!pbust && !dbust) {
            //If the player wins 
            if (dl->getHandValue() < p->getHandValue()) {
                std::cout << "Dealer loses, player wins " << 2*bet << std::endl;
                p->setBalance(p->getBalance() + 2*bet);
                SetWindowText(displayBalanceWindow, converter(true, p->getBalance()).c_str());
                delay(2);
            //If the dealer wins 
            } else if (dl->getHandValue() > p->getHandValue()) {
                std::cout << "Dealer wins, player loses!\n";
                delay(2);
            //If the dealer and player tie
            } else {
                std::cout << "There is a push!\n";
                p->setBalance(p->getBalance() + bet);
                SetWindowText(displayBalanceWindow, converter(true, p->getBalance()).c_str());
                delay(2);
            }
        }
        //Check if player has a negative balance, tell him he is out of money and must leave.
        if (p->getBalance() <= 0) {
            std::cout << "It seems like your you've run out of money. Thanks for playing, better luck next time\n";
        }
        //Reset the players hand
        //Reset the deck
        d->resetDeck();
        p->resetPlayer();
        dl->resetPlayer();
        //Give a message to the player if he wants to continue
        std::cout << "Your updated balance is: " << p->getBalance() << std::endl;
        std::cout << "Would you like to play another hand? (Play for yes/Stand for no)\n";
        while (GetMessage(&msg, NULL, 0, 0))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
            pressed = ifPressed(isPressed);
            switch (pressed) {
                case 0: 
                    isPressed[0] = false;
                    break;
                case 1:
                    isPressed[1] = false;
                    break;
                default :
                    if (pressed != -1) {
                        isPressed[2] = false;
                        isPressed[3] = false;
                        std::cout << "Please choose a valid option" << std::endl;
                    } 
                    break;   
            }
            if (pressed == 0 || pressed == 1) {
                break;
            }
        }
        //Closing statement to the player
        if (pressed == 1) {
            std::cout << "Thank you for playing today: " << p->getName() << ", you ended today with a final balance of: "<< p->getBalance() << std::endl;
            delay(2);
            if (p->getBalance() < balance) {
                std::cout << "You lost " << balance - p->getBalance() << " dollars today. Better luck next time\n";
                delay(2);
            } else {
                std::cout << "Congratulations, you won " << p->getBalance() - balance << " dollars today. We hope you come back!\n";
                delay(2);
            }
            //While loop condition is until player balance is < 0, therefore to exit give player negative balance
            p->setBalance(-1);
        } else {
            std::cout << "Your balance is: " << p->getBalance() << ". We will deal you another hand\n";
            delay(4);
        }
    }
    return 0;

}


LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {

    //If hit button is pressed
    case WM_COMMAND:
        switch(LOWORD(wParam)) {
            case hitButton: {
                isPressed[0] = true;
                return 0;
            }
            case standButton: {
                isPressed[1] = true;
                return 0;
            }
            case doubleButton: {
                isPressed[2] = true;
                return 0;
            }
            case changeBetButton: {
                isPressed[3] = true;
                return 0;
            }
        }

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);
            FillRect(hdc, &ps.rcPaint, (HBRUSH) (COLOR_WINDOW+1));

            EndPaint(hwnd, &ps);
        }
        return 0;

    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

std::wstring converter(bool type, int num) {
    if (type) {
        //returning balance string
        std::string display;
        display.clear();
        display = "Balance: " + std::to_string(num);
        return std::wstring(display.begin(), display.end());
    } else {
        //returning bet string
        std::string display;
        display.clear();
        display = "Bet: " + std::to_string(num);
        return std::wstring(display.begin(), display.end());
    }
    return L"errored";
}
