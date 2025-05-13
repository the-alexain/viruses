#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "Player.hpp"
#include "Vitamin.hpp"
#include "Enemy.hpp"
#include "VitaminGenerator.hpp"
#include "ConsoleWriting.hpp"
#include "Button.hpp"
#include "Generator.hpp"
#include <vector>
#include <iostream>
#include <cmath>

using namespace sf;
using namespace std;

template<typename T> T clampAbsolute(T value, T limit) {
    T posLimit = abs(limit);
    if (value > posLimit) value = posLimit;
    else if (value < -posLimit) value = -posLimit;
    return value;
}

enum Alignment {
    LEFT = -1,
    RIGHT = 2,
    TOP = -3,
    BOTTOM = 4,
    CENTER = 0
};


void GUISetPosition(GameObject *object, View *viewUI, int kInterface = 1, int x = 0, int y = 0, int margin = 0, GameObject *alignObject = NULL,
                    Alignment marginAlign = Alignment::TOP, Alignment widthAlign = Alignment::CENTER, Alignment heightAlign = Alignment::CENTER)
{
    
    float xc, yc = 0;
    if (widthAlign == 0) {
        xc = viewUI->getCenter().x;
    }
    else if (widthAlign == Alignment::RIGHT) {
        xc = viewUI->getSize().x - object->w/2;
    }
    else if (widthAlign == Alignment::LEFT) {
        xc = object->w/2;
    }
    
    if (heightAlign == 0) {
        yc = viewUI->getCenter().y;
    }
    else if (heightAlign == Alignment::TOP) {
        yc = object->h/2;
    }
    else if (heightAlign == Alignment::BOTTOM) {
        yc = viewUI->getSize().y - object->h/2;
    }
    
    
    
    if (margin != 0) {
        if (marginAlign == Alignment::TOP) {
            xc = alignObject->x;
            yc = alignObject->y - alignObject->h/2 - object->h/2 - margin * kInterface;
        }
        else if (marginAlign == Alignment::BOTTOM) {
            xc = alignObject->x;
            yc = alignObject->y + alignObject->h/2 + object->h/2 + margin * kInterface;
        }
        
        else if (marginAlign == Alignment::RIGHT) {
            xc = alignObject->x + alignObject->w/2 + object->w/2 + margin * kInterface;
            yc = alignObject->y;
        }
        else if (marginAlign == Alignment::LEFT) {
            xc = alignObject->x - alignObject->w/2 - object->w/2 - margin * kInterface;
            yc = alignObject->y;
        }
    }
    object->setPosition(xc + x, yc + y);
}


int main(int, char const**) {
    int windowW = 1200;
    int windowH = 1000;
    float dt, kZoomX, kZoomY, kInterface, distance = 0;
    float border = 10000;
    float safeArea = 2000;
    
    RenderWindow window(VideoMode(windowW, windowH), "Viruses");
    View v{FloatRect(0, 0 , windowW, windowH)};
    View vDefault{FloatRect(0, 0 , windowW, windowH)}; // GUI
    vDefault.setCenter(windowW/2, windowH/2);
    
    v.zoom(2.5);
    
    kZoomX = v.getSize().x / window.getSize().x;
    kZoomY = v.getSize().y / window.getSize().y;
    
    Button playButton{"/Users/alex/Desktop/WORK/КОЛЛЕДЖ/ИНФОРМАТИКА/Game/Viruses/Viruses/assets/buttons/play.png"};
    Button continueButton{"/Users/alex/Desktop/WORK/КОЛЛЕДЖ/ИНФОРМАТИКА/Game/Viruses/Viruses/assets/buttons/continue.png"};
    Button consoleButton{"/Users/alex/Desktop/WORK/КОЛЛЕДЖ/ИНФОРМАТИКА/Game/Viruses/Viruses/assets/buttons/console.png"};
    Button escapeButton{"/Users/alex/Desktop/WORK/КОЛЛЕДЖ/ИНФОРМАТИКА/Game/Viruses/Viruses/assets/buttons/escape.png"};
    Button againButton{"/Users/alex/Desktop/WORK/КОЛЛЕДЖ/ИНФОРМАТИКА/Game/Viruses/Viruses/assets/buttons/agaij.png"};
    
    GameObject title(0, 0, 0, "/Users/alex/Desktop/WORK/КОЛЛЕДЖ/ИНФОРМАТИКА/Game/Viruses/Viruses/assets/title.png");
    GameObject lost{0, 0, 0, "/Users/alex/Desktop/WORK/КОЛЛЕДЖ/ИНФОРМАТИКА/Game/Viruses/Viruses/assets/buttons/lost.png"};
    GameObject win{0, 0, 0, "/Users/alex/Desktop/WORK/КОЛЛЕДЖ/ИНФОРМАТИКА/Game/Viruses/Viruses/assets/buttons/win.png"};
    win.sprite.setColor(Color(164, 115, 202));
    lost.sprite.setColor(Color(255, 0, 0));
    
    
    RectangleShape pauseScreen{Vector2f(windowW, windowH)};
    RectangleShape damageScreen{Vector2f(windowW, windowH)};
    RectangleShape winScreen{Vector2f(windowW, windowH)};
    
    RectangleShape left{Vector2f(border / 2, border * 4)};
    RectangleShape right{Vector2f(border / 2, border * 4)};
    RectangleShape top{Vector2f(border * 4, border  / 2)};
    RectangleShape bottom{Vector2f(border * 4, border  / 2)};
    
    left.setPosition(-border - left.getSize().x, -left.getSize().y / 2);
    right.setPosition(border, -right.getSize().y / 2);
    
    top.setPosition(-top.getSize().x / 2, -border - top.getSize().y);
    bottom.setPosition(-top.getSize().x / 2, border);

    
    Clock countdownDamage;
    countdownDamage.restart().asSeconds();
    
    pauseScreen.setFillColor(Color(0, 0, 0, 50));
    damageScreen.setFillColor(Color(255, 0, 0, 50));
    winScreen.setFillColor(Color(164, 115, 202, 50));
    
    Generator g{};
    Player p{100, 100, &g};
    
    VitaminFood vf{600, 100, 0, 30};
    
    int lastHp = p.health;
    
    vector<Vitamin*> vitamins;
    vitamins.push_back(&vf);
    Enemy virus{-1000, -1000, &p, &countdownDamage, &vitamins, &window};
    
    Vector2i mpos;
    
    Clock clock;
    Clock countdown;
    countdown.restart().asSeconds();
    
    Font font;
    Font defaultFont;
    font.loadFromFile("/Users/alex/Desktop/WORK/КОЛЛЕДЖ/ИНФОРМАТИКА/Game/Viruses/Viruses/assets/minecraft-five-bold.ttf");
    defaultFont.loadFromFile("/System/Library/Fonts/Supplemental/Arial.ttf");
    Text hp("hp", font, 18);
    Text degradation("dg", font, 18);
    
    hp.setFillColor(Color::Black);
    degradation.setFillColor(Color(164, 115, 202));
    
    Text textConsole("> ", defaultFont, 14);
    Text consoleMessage("[TEST]", defaultFont, 14);
    textConsole.setFillColor(Color::Black);
    consoleMessage.setFillColor(Color::Black);
    
    bool DEBUG = false;
    bool CONSOLE = false;
    bool GAME = true;
    bool PAUSE = false;
    bool isMove = false;
    bool isDamage = false;
    bool god = false;
    int gameMode = 1; // 0 - game 1 - menu 2 - lost 3 - win 4 - pause;
    
    string command = "";
    
    Console console{&DEBUG, &p, &consoleMessage, &god};
    
    kInterface = (float)windowW/1920.f;
    
    VitaminGenerator vg{&p, &window, &vitamins, &g};

    if (GAME) {
        
        if (gameMode == 0) {
            vg.generator();
            v.zoom(1.8);
        }
        
        while (window.isOpen()) {
            dt = clock.restart().asSeconds();
            
            if (gameMode != 1) {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    if (!PAUSE) {
                        isMove = true;
                        p.targetC = window.mapPixelToCoords(mpos, v);

                        float rot = atan( (p.x - virus.x) / (p.y - virus.y)) * 57.3 - 180; // rotate virus
                        if ((virus.y - p.y) > 0) rot -= 180;
                        
                        virus.setRotate(rot);
                    }
                }
                else {
                    isMove = false;
                }
                
                Event event;
                while (window.pollEvent(event))
                {
                    if (event.type == Event::Closed) {
                        window.close();
                    }
                    
                    else if (event.type == Event::MouseButtonReleased) {
                        if (event.mouseButton.button == sf::Mouse::Left) {
                            if (PAUSE) {
                                if (gameMode == 2 || gameMode == 3) {
                                    if (mpos.x >= (againButton.x - (againButton.w * kInterface)/2)) {
                                        if (mpos.x <= (againButton.x + (againButton.w * kInterface)/2)) {
                                            PAUSE = false;
                                            p.x = 0;
                                            p.y = 0;
                                            virus.x = -1000;
                                            virus.y = -1000;
                                            p.health = 100;
                                            p.degratation = 0;
                                            gameMode = 0;
                                            p.sprite.setScale(1, 1);
                                            p.pickupRadius = 100;
                                        }
                                    }
                                }
                                
                                else if (gameMode == 4) {
                                    if (mpos.x >= (continueButton.x - (continueButton.w * kInterface)/2)) {
                                        if (mpos.x <= (continueButton.x + (continueButton.w * kInterface)/2)) {
                                            if (mpos.y >= (escapeButton.y - (escapeButton.h * kInterface)/2)) {
                                                if (mpos.y <= (escapeButton.y + (escapeButton.h * kInterface)/2)) {
                                                    gameMode = 1;
                                                }
                                            }
                                            
                                            else if (mpos.y >= (consoleButton.y - (consoleButton.h * kInterface)/2)) {
                                                if (mpos.y <= (consoleButton.y + (consoleButton.h * kInterface)/2)) {
                                                    PAUSE = !PAUSE;
                                                    gameMode = 0;
                                                    CONSOLE = true;
                                                    continue;
                                                }
                                            }
                                            
                                            else if (mpos.y >= (continueButton.y - (continueButton.h * kInterface)/2)) {
                                                if (mpos.y <= (continueButton.y + (continueButton.h * kInterface)/2)) {
                                                    PAUSE = !PAUSE;
                                                    gameMode = 0;
                                                    continue;
                                                }
                                            }
                                            
                                        }
                                    }
                                }
                            }
                        }
                    }
                    
                    else if (event.type == Event::KeyReleased) {
                        if (event.key.code == Keyboard::Escape) {
                            if (gameMode != 2) {
                                if (PAUSE) {
                                    gameMode = 0;
                                }
                                else {
                                    gameMode = 4;
                                }
                                PAUSE = !PAUSE;
                                continue;
                            }
                        }
                    }
                    
                    if (event.type == Event::MouseWheelScrolled) {
                        if (!PAUSE) {
                            if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel) {
                                if (event.mouseWheelScroll.delta > 0) {
                                    v.zoom(0.99);
                                }
                                else {
                                    if (kZoomX < 7) {
                                        v.zoom(1.01);
                                    }
                                }
                                
                                kZoomX = v.getSize().x / window.getSize().x;
                                kZoomY = v.getSize().y / window.getSize().y;
                            }
                        }
                    }
                    
                    else if (event.type == Event::KeyPressed) {
                        if (event.key.code == Keyboard::G) {
                            //                            vg.generate();
                        }
                        
                        if (event.key.code == Keyboard::Tilde) {
                            CONSOLE = true;
                        }
                    }
                    
                    else if(event.type == sf::Event::TextEntered) {
                        if (CONSOLE) {
                            if (event.text.unicode == 10) {
                                CONSOLE = false;
                                console.run(command);
                                command = "";
                                
                            }
                            else if (event.text.unicode == 8) {
                                if (command.size() != 0) {
                                    command.pop_back();
                                }
                            }
                            else {
                                command += event.text.unicode;
                            }
                            
                            if (event.text.unicode == 96) {
                                if (command.size() == 1) {
                                    if (command[0] == '`') {
                                        command = "";
                                    }
                                }
                                
                            }
                            textConsole.setString("> " + command);
                        }
                    }
                    
                    else if (event.type == Event::MouseMoved) {
                        mpos = Mouse::getPosition(window);
                        
                        if (!PAUSE) {
                            float rot = 0;
                            float b = (float)mpos.x - (float)window.getSize().x/2; // x
                            float a = (float)mpos.y - (float)window.getSize().y/2; // y
                            
                            
                            rot = atan2(a, b) * 180 / 3.14159f;
                            
                            p.setRotate(-rot - 90);
                        }
                    }
                }
                
                
                window.clear(Color(255, 255, 255, 255));
                
                v.setCenter(p.x, p.y);
                window.setView(v); // VIEW: GAME
                
                console.msg(vector<float>{dt, (float)p.x, (float)p.y, (float)p.speed, (float)vitamins.size(), (float)p.rotation, (float)mpos.y - window.getSize().y/2}, vector<string>{"dt", "x", "y",
                    "s", "objs", "mx", "my"});
                
                virus.targetC = Vector2f{(float)p.x, (float)p.y};
                
                if (gameMode == 0) {
                    p.moveAndSlide(dt);
                    virus.moveAndSlide(dt);
                    
                    p.update();
                    virus.update();
                    
                    p.x = clampAbsolute(p.x, border);
                    p.y = clampAbsolute(p.y, border);
                }
                
                if (p.x > -border && p.x < -border + safeArea) { // left
                    left.setFillColor(Color(255, 0, 0, 100 * (abs(p.x) / border - ((border - safeArea) / border)) * 5));
                }
                else if (p.x < border && p.x > border - safeArea) { // right
                    right.setFillColor(Color(255, 0, 0, 100 * (abs(p.x) / border - ((border - safeArea) / border)) * 5));
                }
                
                if (p.y < -border + safeArea && p.y > -border) { // top
                    top.setFillColor(Color(255, 0, 0, 100 * (abs(p.y) / border - ((border - safeArea) / border)) * 5));
                }
                else if (p.y > border - safeArea && p.y < border) { // bottom
                    bottom.setFillColor(Color(255, 0, 0, 100 * (abs(p.y) / border - ((border - safeArea) / border)) * 5));
                }
                
                p.updateVitamins(&vitamins, window, &countdown, &dt);
                
                window.draw(p.sprite);
                window.draw(virus.sprite);
                
                /// BORDERS
                window.draw(left);
                window.draw(right);
                window.draw(top);
                window.draw(bottom);
                
                window.setView(vDefault); // VIEW: GUI
                
                hp.setString("HP: " + to_string(p.health));
                hp.setPosition(30 * kInterface, vDefault.getSize().y - 200 * kInterface);
                
                degradation.setString("DG: " + to_string(p.degratation));
                degradation.setPosition(30 * kInterface, vDefault.getSize().y - 100 * kInterface);
                consoleMessage.setPosition(30 * kInterface, 60 * kInterface);
                
                window.draw(consoleMessage);
                window.draw(hp);
                window.draw(degradation);
                
                if (PAUSE) { // display PAUSE
                    if (gameMode == 2) {
                        damageScreen.setFillColor(Color(255, 0, 0, 50));
                        window.draw(damageScreen);
                        
                        againButton.sprite.setScale(kInterface, kInterface);
                        lost.sprite.setScale(kInterface, kInterface);
                        lost.sprite.setColor(Color(255, 0, 0, 255));
                        
                        GUISetPosition(&againButton, &vDefault, kInterface, 0, 50);
                        GUISetPosition(&lost, &vDefault, kInterface, 0, 0, 300, &againButton);
                        
                        window.draw(againButton.sprite);
                        window.draw(lost.sprite);
                    }
                    
                    else if (gameMode == 3) {
                        window.draw(winScreen);
                        
                        againButton.sprite.setScale(kInterface, kInterface);
                        win.sprite.setScale(kInterface, kInterface);
                        
                        GUISetPosition(&againButton, &vDefault, kInterface, 0, 50);
                        GUISetPosition(&win, &vDefault, kInterface, 0, 0, 300, &againButton);
                        
                        window.draw(againButton.sprite);
                        window.draw(win.sprite);
                    }
                    
                    else if (gameMode == 4) {
                        //            pauseScreen.setPosition(-pauseScreen.getSize().x/2, -pauseScreen.getSize().x/2);
                        window.draw(pauseScreen);
                        
                        // BUTTONS
                        consoleButton.sprite.setScale(kInterface, kInterface);
                        continueButton.sprite.setScale(kInterface, kInterface);
                        escapeButton.sprite.setScale(kInterface, kInterface);
                        
                        GUISetPosition(&consoleButton, &vDefault, kInterface);
                        GUISetPosition(&continueButton, &vDefault, kInterface, 0, 0, 100, &consoleButton);
                        GUISetPosition(&escapeButton, &vDefault, kInterface, 0, 0, 100, &consoleButton, Alignment::BOTTOM);
                        
                        consoleButton.update();
                        continueButton.update();
                        escapeButton.update();
                        
                        
                        window.draw(continueButton.sprite);
                        window.draw(consoleButton.sprite);
                        window.draw(escapeButton.sprite);
                        
                        if (DEBUG) {
                            window.draw(consoleButton.centerDebug);
                            window.draw(continueButton.centerDebug);
                            window.draw(escapeButton.centerDebug);
                        }
                    }
                }
                
                if (CONSOLE) {
                    textConsole.setPosition(30 * kInterface, 100 * kInterface);
                    window.draw(textConsole);
                    
                }
                if (gameMode == 0) {
                    
                    if (p.health - lastHp != 0) {
                        p.isDamage = true;
                        lastHp = p.health;
                    }
                    
                    if (p.health <= 0) {
                        gameMode = 2;
                        PAUSE = true;
                    }
                    
                    if (p.degratation >= 100) {
                        gameMode = 3;
                        PAUSE = true;
                    }
                    
                    if (p.isDamage) {
                        damageScreen.setFillColor(Color(255, 0, 0, 50 * countdownDamage.getElapsedTime().asSeconds() ));
                        window.draw(damageScreen);
                    }
                }
                
                window.setView(v);
                if (DEBUG) {
                    window.draw(p.centerDebug);
                }
                
                if (god) {
                    p.health = p.maxHealth;
                }
                
                window.display();
            }
            
            else {
                
                title.sprite.setScale(0.5 * kInterface, 0.5 * kInterface);
                playButton.sprite.setScale(kInterface, kInterface);
                escapeButton.sprite.setScale(kInterface, kInterface);
                
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    
                }
                
                Event event;
                while (window.pollEvent(event))
                {
                    if (event.type == Event::Closed) {
                        window.close();
                    }
                    
                    else if (event.type == Event::MouseButtonReleased) {
                        if (event.mouseButton.button == sf::Mouse::Left) {
                            mpos = Mouse::getPosition(window);
                            if (mpos.x >= (playButton.x - (playButton.w * kInterface)/2)) {
                                if (mpos.x <= (playButton.x + (playButton.w * kInterface)/2)) {
                                    if (mpos.y >= (escapeButton.y - (escapeButton.h * kInterface)/2)) {
                                        if (mpos.y <= (escapeButton.y + (escapeButton.h * kInterface)/2)) {
                                            window.close();
                                        }
                                    }
                                    
                                    else if (mpos.y >= (playButton.y - (playButton.h * kInterface)/2)) {
                                        if (mpos.y <= (playButton.y + (playButton.h * kInterface)/2)) {
                                            
                                            vg.generator();
                                            v.zoom(1.8);
                                            
                                            gameMode = 0;
                                            PAUSE = false;
                                            p.x = 0;
                                            p.y = 0;
                                            virus.x = -1000;
                                            virus.y = -1000;
                                            p.health = 100;
                                            p.degratation = 0;
                                            p.sprite.setScale(1, 1);
                                            p.pickupRadius = 100;
                                            
                                            
                                            continue;
                                        }
                                    }
                                    
                                }
                            }
                        }
                    }
                    
                }
                
                GUISetPosition(&playButton, &vDefault, kInterface);
                GUISetPosition(&escapeButton, &vDefault, kInterface, 0, 0, 80, &playButton, Alignment::BOTTOM);
                GUISetPosition(&title, &vDefault, kInterface, 0, 0, 500, &playButton, Alignment::TOP);
                
                
                window.clear(Color(255, 255, 255, 255));
                window.setView(vDefault);
                
                window.draw(title.sprite);
                window.draw(playButton.sprite);
                window.draw(escapeButton.sprite);
                
                window.display();
            }
            
            
        }
    }
}
