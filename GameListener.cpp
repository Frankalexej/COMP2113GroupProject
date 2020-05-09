#include "GameListener.h"
#include <termio.h>
#include <stdio.h>
#include <iostream>
#include <fstream>

int GameListener::scanKeyboard() {
    int in;
    struct termios new_settings;
    struct termios stored_settings;
    tcgetattr(0, &stored_settings);
    new_settings = stored_settings;
    new_settings.c_lflag &= (~ICANON);
    new_settings.c_cc[VTIME] = 0;
    tcgetattr(0, &stored_settings);
    new_settings.c_cc[VMIN] = 1;
    tcsetattr(0, TCSANOW, &new_settings);

    in = getchar();

    tcsetattr(0, TCSANOW, &stored_settings);
    return in;
}

GameListener::GameListener(KeyboardSetting* keyboard, ScreenManager* screen, Map* map, GameMediator* mediator)
    :keyboard(keyboard), screen(screen), map(map), mediator(mediator) {}
ifstream GameListener::listenStartPage()
{
    ifstream fin;
    system("clear");
    printf("\033[?25l");    // hide cmd cursor
    system("stty -echo");   // hide user input
    printf("\33[2K\tSTART NEW GAME\n\33[2K\tLOAD GAME\n\33[2K\tEXIT\n\33[2K");  // \33[2K cleans the current line
    printf("\033[1;1H");    // move cursor to position 1,1 (= 0,0)
    printf(CURSOR);
    int y = 0;  // records the position of cursor
    // ArrowCursor not used here, because it is only one-dimensional, no need to use that
    while (1)   // infinit loop to listen to keyboard
    {
        unsigned char ch = scanKeyboard();  // listen to keyboard
        if (ch == this->keyboard->cursorUp->keyCode) {  // for keys used please refer to KeyBoardSetting.h
            if (y > 0) {
                y--;
                printf("\033[1;1H");
                printf("\33[2K\tSTART NEW GAME\n\33[2K\tLOAD GAME\n\33[2K\tEXIT\n\33[2K");
                printf("\033[%d;1H", y + 1);
                printf(CURSOR);
            }
        }

        if (ch == this->keyboard->cursorDown->keyCode) {
            if (y < 2) {
                y++;
                printf("\033[1;1H");
                printf("\33[2K\tSTART NEW GAME\n\33[2K\tLOAD GAME\n\33[2K\tEXIT\n\33[2K");
                printf("\033[%d;1H", y + 1);
                printf(CURSOR);
            }
        }

        if (ch == this->keyboard->nextStep->keyCode) {
            if (y == 2) {
                system("clear");        // clears cmd
                printf("\033[?25h");    // show cmd cursor
                system("stty echo");    // show user input
                exit(1);    // exit program
                return fin;
            }
            string saveName;
            if (y == 0) {
                system("clear");
                printf("\033[?25h");    // show cmd cursor
                system("stty echo");    // show user input
                printf("Please enter map name: ");
                cin >> saveName;    // reads in saveName(fileName)
                saveName = "./maps/" + saveName + ".txt";
            }
            else if (y == 1) {
                system("clear");
                printf("\033[?25h");    // show cmd cursor
                system("stty echo");    // show user input
                printf("Please enter saving name: ");
                cin >> saveName;
                saveName = "./savings/" + saveName + ".txt";
            }
            fin.open(saveName);
            if (!fin.is_open()) {
                system("clear");
                printf("Error! Please try again.");
                while (1)
                {
                    if (scanKeyboard()) {
                        printf("\33[2K\tSTART NEW GAME\n\33[2K\tLOAD GAME\n\33[2K\tEXIT\n\33[2K");
                        printf("\033[%d;1H", y + 1);
                        printf(CURSOR);
                        break;
                    }
                }
            }
            return fin;
        }
    }
}

void GameListener::listenQuit()
{
    // similar to listenStartPage()
    ofstream fou;
    system("clear");
    printf("\33[2K\tSAVE AND EXIT\n\33[2K\tEXIT");
    printf("\033[1;1H");
    printf(CURSOR);
    int y = 0;
    while (1)
    {
        unsigned char ch = scanKeyboard();
        if (ch == this->keyboard->cursorUp->keyCode) {
            if (y > 0) {
                y--;
                printf("\033[1;1H");
                printf("\33[2K\tSAVE AND EXIT\n\33[2K\tEXIT");
                printf("\033[%d;1H", y + 1);
                printf(CURSOR);
            }
        }

        if (ch == this->keyboard->cursorDown->keyCode) {
            if (y < 1) {
                y++;
                printf("\033[1;1H");
                printf("\33[2K\tSAVE AND EXIT\n\33[2K\tEXIT");
                printf("\033[%d;1H", y + 1);
                printf(CURSOR);
            }
        }

        if (ch == this->keyboard->formerStep->keyCode) {
            this->screen->refreshMain(this->mediator->isTurn, this->mediator->getMoney());
            break;
        }

        if (ch == this->keyboard->nextStep->keyCode) {
            printf("\033[?25h");    // show cmd cursor
            system("stty echo");    // show user input
            if (!y) {
                system("clear");
                printf("Please enter saving name: ");
                string saveName;
                cin >> saveName;
                saveName = "./savings/" + saveName + ".txt";
                fou.open(saveName);
                this->map->saveMap(fou, this->mediator->isTurn, this->mediator->AMoney, this->mediator->BMoney);
            }
            system("clear");
            exit(1);
        }
    }
}

void GameListener::listenMain()
{
    // main game page
    system("clear");
    printf("\033[?25l");    // hide cmd cursor
    system("stty -echo");   // hide user input
    this->screen->refreshMain(this->mediator->isTurn, this->mediator->getMoney());
    while (1) {
        unsigned char ch = scanKeyboard();
        if (ch == keyboard->exit->keyCode) this->listenQuit();  // on Esc down
        // cursor movement
        else if (ch == keyboard->cursorLeft->keyCode) {
            if (this->screen->moveLeft(false)) this->screen->refreshMain(this->mediator->isTurn, this->mediator->getMoney());
        }
        else if (ch == keyboard->cursorRight->keyCode) {
            if (this->screen->moveRight(false)) this->screen->refreshMain(this->mediator->isTurn, this->mediator->getMoney());
        }
        else if (ch == keyboard->cursorUp->keyCode) {
            if (this->screen->moveUp(false)) this->screen->refreshMain(this->mediator->isTurn, this->mediator->getMoney());
        }
        else if (ch == keyboard->cursorDown->keyCode) {
            if (this->screen->moveDown(false)) this->screen->refreshMain(this->mediator->isTurn, this->mediator->getMoney());
        }
        // nextStep
        else if (ch == keyboard->nextStep->keyCode) {
            this->screen->printPointOccupierInfo(this->mediator->isTurn);   // print more info
            if (this->screen->printShadowedRegion(this->mediator->isTurn)) {    // print shadowed region, only forward to listenPos() when there is any operation available
                bool posResult = this->listenPos(); // true on can-go-to-next-turn operations (troop movement, pruduction, lifeRecovery), false on unsuccessful operations or formerStep
                system("clear");
                if (posResult) {    // if on can-go-to-next-turn operations
                    if (this->mediator->nextTurn()) {   // next turn
                        // one round is counted as one A operation and one B operation
                        // new rounds always start with A, only accumulate money and judge winning at the end (beginning) of rounds
                        int result = this->AccMoney();
                        if (result) this->listenGameEnd(result);
                    }
                }
                this->screen->refreshMain(this->mediator->isTurn, this->mediator->getMoney());  // refresh
            }
        }
        else if (ch == keyboard->skip->keyCode) {   // skip is simply do nothing
            if (this->mediator->nextTurn()) {
                int result = this->AccMoney();
                if (result) this->listenGameEnd(result);
            }
            this->screen->refreshMain(this->mediator->isTurn, this->mediator->getMoney());
        }
        else continue;
    }
}

bool GameListener::listenPos()
{
    this->screen->followCursor();   // brings posCur to position of cursor
    while (1) {
        unsigned char ch = scanKeyboard();
        if (ch == keyboard->exit->keyCode) this->listenQuit();
        else if (ch == keyboard->cursorLeft->keyCode) {
            if (this->screen->moveLeft(true)) this->screen->refreshShadow(this->mediator->isTurn);
        }
        else if (ch == keyboard->cursorRight->keyCode) {
            if (this->screen->moveRight(true)) this->screen->refreshShadow(this->mediator->isTurn);
        }
        else if (ch == keyboard->cursorUp->keyCode) {
            if (this->screen->moveUp(true)) this->screen->refreshShadow(this->mediator->isTurn);
        }
        else if (ch == keyboard->cursorDown->keyCode) {
            if (this->screen->moveDown(true)) this->screen->refreshShadow(this->mediator->isTurn);
        }
        else if (ch == keyboard->nextStep->keyCode) {
            Point* p = this->map->getPointAt(this->screen->cursor->x, this->screen->cursor->y);
            // if recover life or set factory
            if (this->screen->cursorsMeet()) {  // cursor remain on original position for lifeRecovery or setFactory(engineer only)
                int money = this->mediator->getMoney();
                int restMoney;
                if (p->getType() == "eng") restMoney = this->map->setFactory(p, money);
                else {
                    restMoney = this->map->lifeRecover(p, money);
                }
                if (restMoney != money) {   // whether spent money to judge whether operation successful
                    this->mediator->setMoney(restMoney);
                    return true;
                }
            }
            else {
                // factory / capital production
                if (p->getType() == "fbrk" || p->getType() == "cap") {
                    int x = this->screen->posCur->x;
                    int y = this->screen->posCur->y;
                    if (this->map->canTo(p, x, y)) {
                        string type = this->listenProduction(); // go to listen what troop to produce
                        if (type == "skip") return true;
                        if (type == "last") continue;   // on formerStep down
                        int money = this->mediator->getMoney();
                        int restMoney;
                        restMoney = this->map->newTroopto(money, p->getSide(), type, x, y);
                        if (restMoney != money) {
                            this->mediator->setMoney(restMoney);
                            return true;
                        }
                    }
                }
                // move
                else if (this->map->moveTo(p, this->screen->posCur->x, this->screen->posCur->y)) return true;   // for troop movement
            }
            this->screen->refreshShadow(this->mediator->isTurn);
        }
        // skip
        else if (ch == keyboard->skip->keyCode) return true;
        // return to cursor layer
        else if (ch == keyboard->formerStep->keyCode) {
            return false;
        }
        else continue;
    }
}


string GameListener::listenProduction() {
    while (1)
    {
        unsigned char ch = scanKeyboard();
        if (ch == keyboard->exit->keyCode) this->listenQuit();
        if (ch == this->keyboard->soldier->keyCode) return "sol";
        if (ch == this->keyboard->engineer->keyCode) return "eng";
        if (ch == this->keyboard->lav->keyCode) return "lav";
        if (ch == this->keyboard->tank->keyCode) return "tank";
        if (ch == this->keyboard->formerStep->keyCode) return "last";
        if (ch == this->keyboard->skip->keyCode) return "skip";
    }
}

void GameListener::listenGameEnd(int result)
{
    if (result == -2) this->screen->printEndInfo();
    else this->screen->printEndInfo(result == 1);
    while (1)
    {
        unsigned char ch = scanKeyboard();
        if (ch) {
            printf("\033[?25h");    // show cmd cursor
            system("stty echo");    // show user input
            system("clear");
            exit(1);
        }
    }
}

int GameListener::AccMoney()
{
    int AMoneyAcc = 0, BMoneyAcc = 0;
    int ACapStill = 0, BCapStill = 0;
    // only factories and capitals can accumulate money
    for (int y = 0; y < this->map->getHeight(); y++)
    {
        for (int x = 0; x < this->map->getWidth(); x++)
        {
            Point* p = this->map->getPointAt(x, y);
            if (p->getType() == "fbrk") (p->getSide() ? AMoneyAcc : BMoneyAcc) += p->getWas();
            else if (p->getType() == "cap") {
                (p->getSide() ? ACapStill : BCapStill)++;
                (p->getSide() ? AMoneyAcc : BMoneyAcc) += p->getWas();
            }
        }
    }
    // if capital occupied (i.e. no more your capital), game ends
    if (ACapStill == 0 && BCapStill == 0) return -2;
    if (ACapStill == 0) return -1;
    if (BCapStill == 0) return 1;

    this->mediator->accMoney(AMoneyAcc, BMoneyAcc);
    return 0;
}
